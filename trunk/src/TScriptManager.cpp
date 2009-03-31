//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include "swiglua.h"

static Tubras::TScriptManager* theScriptManager;
static FILE* logFile=0; // temporary startup log file
extern "C" {
    int luaopen_tubras(lua_State* L);
}

namespace Tubras
{
    template<> TScriptManager* TSingleton<TScriptManager>::ms_Singleton = 0;
    static const luaL_Reg lualibs[] = 
    {
        {"", luaopen_base},
        {LUA_LOADLIBNAME, luaopen_package},
        {LUA_TABLIBNAME, luaopen_table},
        {LUA_IOLIBNAME, luaopen_io},
        {LUA_OSLIBNAME, luaopen_os},
        {LUA_STRLIBNAME, luaopen_string},
        {LUA_MATHLIBNAME, luaopen_math},
        {LUA_DBLIBNAME, luaopen_debug},
        {NULL, NULL}
    };


    //-----------------------------------------------------------------------
    //                       T S c r i p t M a n a g e r
    //-----------------------------------------------------------------------
    TScriptManager::TScriptManager() : TDelegate(),
        m_eventDelegate(0),
        m_funcIntervalDelegate(0),
        m_mainScript(0),
        m_funcIntervalArgs(0)
    {
        theScriptManager = this;
    }

    //-----------------------------------------------------------------------
    //                      ~ T S c r i p t M a n a g e r
    //-----------------------------------------------------------------------
    TScriptManager::~TScriptManager()
    {

        TScriptMapItr itr = m_scripts.getIterator();

        while(!itr.atEnd())
        {
            TScript* script = itr->getValue();
            delete script;
            itr++;
        }

        m_scripts.clear();
        

        if(m_funcIntervalDelegate)
            delete m_funcIntervalDelegate;

        if(m_lua)
            lua_close(m_lua);

    }

    //-------------------------------------------------------------------------
    //                       t u b r a s _ p r i n t
    //-------------------------------------------------------------------------
    static int tubras_print (lua_State *L) {
        TString msg="(LUA) ";
        int n = lua_gettop(L);  /* number of arguments */
        int i;
        lua_getglobal(L, "tostring");
        for (i=1; i<=n; i++) {
            const char *s;
            lua_pushvalue(L, -1);  /* function to be called */
            lua_pushvalue(L, i);   /* value to print */
            lua_call(L, 1, 1);
            s = lua_tostring(L, -1);  /* get result */
            if (s == NULL)
                return luaL_error(L, LUA_QL("tostring") " must return a string to "
                LUA_QL("print"));
            if (i>1) 
                msg += "\t";
            msg += s;
            lua_pop(L, 1);  /* pop result */
        }
        getApplication()->logMessage(msg);
        return 0;
    }

    //-------------------------------------------------------------------------
    //                       _ s e t P a c k a g e P a t h
    //-------------------------------------------------------------------------
    void TScriptManager::_setPackagePath()
    {
        stringc cpath = getTableFieldString("package","path");
        stringc dir = m_scriptPath;
        stringc npath;
        stringc ext;

        npath = dir;
        npath += "?.lua;";
        npath += cpath;
        setTableFieldString("package","path",npath.c_str());
    }

    //-------------------------------------------------------------------------
    //                          _ p a r s e r L U A E r r o r
    //-------------------------------------------------------------------------
    void TScriptManager::parseLUAError(stringc& lmsg, stringc& fileName, int& line, 
                    stringc& emsg)
    {
        stringc sline="";

        s32 pos = lmsg.findFirst(':');
        if(pos < 0)
            return;

        fileName = lmsg.subString(0,pos);

        for(s32 i=pos+1; i<(irr::s32)lmsg.size(); i++)
        {
            c8 c = lmsg[i];
            if(c == ':')
            {
                pos = i;
                break;
            }
            sline += c;
        }

        line = atoi(sline.c_str());

        while( (pos < (s32)lmsg.size()) && ((lmsg[pos] == ' ') || (lmsg[pos] == ':')))
            ++pos;

        emsg = lmsg.subString(pos, lmsg.size());
    }

    //---------------------------------------------------------------------------
    //                             d u m p S t a c k
    //---------------------------------------------------------------------------
    void TScriptManager::dumpStack()
    {
        int i;
        int top = lua_gettop(m_lua);
        printf("\n---------------  Stack Dump ---------------\n");
        for (i = 1; i <= top; i++) 
        {  
            int t = lua_type(m_lua, i);
            switch (t) 
            {
            case LUA_TSTRING:  /* strings */
                printf("STRING: `%s'\n", lua_tostring(m_lua, i));
                break;

            case LUA_TBOOLEAN:  /* booleans */
                printf("BOOLEAN: %s\n",lua_toboolean(m_lua, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                printf("NUMBER: %g\n", lua_tonumber(m_lua, i));
                break;

            default:  /* other values */
                printf("%s\n", lua_typename(m_lua, t));
                break;
            }
        }
        printf("----------------  End Dump ----------------\n");
    }

    //-------------------------------------------------------------------------
    //                           d u m p T a b l e
    //-------------------------------------------------------------------------
    void TScriptManager::dumpTable()
    {
        int top = lua_gettop(m_lua);

        lua_pushnil(m_lua);          
        while (lua_next(m_lua, top)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc key, value;
            if(lua_type(m_lua, -2) == LUA_TSTRING)
            {
                key = lua_tostring(m_lua, -2);
            }
            else if(lua_type(m_lua, -2) == LUA_TNUMBER)
            {
                key = "index[";
                key += lua_tointeger(m_lua, -2);
                key += "]";

            }
            else 
            {
                key = lua_typename(m_lua, lua_type(m_lua, -2));
            }

            if(lua_type(m_lua, -1) == LUA_TSTRING)
            {
                value = lua_tostring(m_lua, -1);
            }
            else if(lua_type(m_lua, -1) == LUA_TNUMBER)
            {
                value = "";
                value += lua_tonumber(m_lua, -1);
            }
            else
                value = lua_typename(m_lua, lua_type(m_lua, -1));


            fprintf(stdout, "%s - %s\n", key.c_str(), value.c_str());

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(m_lua, 1);
        }
    }

    //-------------------------------------------------------------------------
    //                    g e t T a b l e F i e l d S t r i n g
    //-------------------------------------------------------------------------
    const char* TScriptManager::getTableFieldString (const char* table, const char *key) 
    {
        const char* result=0;
        int top,t;

        lua_getglobal(m_lua, table);
        top = lua_gettop(m_lua);
        t = lua_type(m_lua, top);
        if(t != LUA_TTABLE)
        {
            lua_pop(m_lua,1);
            return 0;
        }

        lua_pushstring(m_lua, key);
        lua_gettable(m_lua, -2);  /* get table[key] */
        if (!lua_isstring(m_lua, -1))
        {
            fprintf(stdout,"Table key is not a string: %s\n",key);
            lua_pop(m_lua, 1);
            lua_pop(m_lua, 1);
            return 0;
        }
        result = lua_tostring(m_lua, -1);
        lua_pop(m_lua, 1);  // pop int value
        lua_pop(m_lua, 1);  // pop table

        return result;
    }

    //-------------------------------------------------------------------------
    //                    s e t T a b l e F i e l d S t r i n g
    //-------------------------------------------------------------------------
    bool TScriptManager::setTableFieldString (const char* table, const char *key, const char* value)
    {
        int top,t;

        lua_getglobal(m_lua, table);
        top = lua_gettop(m_lua);
        t = lua_type(m_lua, top);
        if(t != LUA_TTABLE)
        {
            lua_pop(m_lua,1);
            return false;
        }

        lua_pushstring(m_lua, key);
        lua_pushstring(m_lua, value);
        lua_settable(m_lua, -3);
        lua_pop(m_lua, 1);  // pop table

        return true;
    }

    //-------------------------------------------------------------------
    //                      g e t R e t u r n I n t
    //-------------------------------------------------------------------
    int TScriptManager::getReturnInt()
    {
        int result=0;

        int top = lua_gettop(m_lua);
        if(top >= 1)
        {  
            int t = lua_type(m_lua, top);
            switch (t) 
            {
            case LUA_TSTRING:  /* strings */
                break;

            case LUA_TBOOLEAN:  /* booleans */
                if(lua_toboolean(m_lua,top))
                    result = 1;
                break;

            case LUA_TNUMBER:  /* numbers */
                result = (int)lua_tonumber(m_lua, top);
                break;

            default:  /* other values */
                break;
            }
        }

        // pop the return value
        lua_pop(m_lua,top);

        return result;
    }

    //-----------------------------------------------------------------------
    //                             l o g W r i t e
    //-----------------------------------------------------------------------
    int logWrite(char *line)
    {
        int newline=line[strlen(line)-1]=='\n';
        if(newline)
            line[strlen(line)-1]='\0';

        // printf("logwrite(\"%s%s\")\n", line, newline?"\\n":"");

        Tubras::TString msg;
        msg = "Python: ";
        msg += line;

        if(getApplication())
        {
            if(logFile)
            {
                fclose(logFile);
                logFile = 0;
            }
            getApplication()->logMessage(msg.c_str());
        }
        else // application net yet available
        {
            if(logFile)
                fprintf(logFile,"%s\n",msg.c_str());
            else
                printf("%s\n",msg.c_str());
        }
        return 0;
    }

    //-----------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TScriptManager::initialize(TString scriptPath, TString scriptName, TString appEXE,
        int argc,const char **argv)
    {
        TString path;
        int rc=0;

        TString msg = "Initializing LUA Version: ";
        msg += LUA_RELEASE;
        getApplication()->logMessage(msg);

        m_scriptPath = scriptPath;
        m_scriptName = scriptName;        
        //
        // setup script delegates
        //
        m_eventDelegate = EVENT_DELEGATE(TScriptManager::handleEvent);
        m_funcIntervalDelegate = INTERVAL_DELEGATE(TScriptManager::functionInterval);

        m_lua = lua_open();
        // suspend collection during init
        lua_gc(m_lua, LUA_GCSTOP, 0);  

        // open LUA libraries
        const luaL_Reg *lib = lualibs;
        for (; lib->func; lib++) 
        {
            lua_pushcfunction(m_lua, lib->func);
            lua_pushstring(m_lua, lib->name);
            lua_call(m_lua, 1, 0);
        }

        lua_gc(m_lua, LUA_GCRESTART, 0);

        // mod package path to include original script location
        _setPackagePath();

        // "print" output will be sent to the application log and stdout
        lua_pushcfunction(m_lua, tubras_print);
        lua_setglobal(m_lua, "print");

        // init tubras swig interface
        luaopen_tubras(m_lua);

        // set global variables
        swig_type_info * type = SWIG_TypeQuery(m_lua, "TApplication *");
        SWIG_Lua_NewPointerObj(m_lua, (void *)getApplication(), type, 0);
        lua_setglobal(m_lua,"tse");

        m_mainScript = loadScript(m_scriptName);
        if(!m_mainScript)
            return 1;

        return rc;
    }

    //-----------------------------------------------------------------------
    //                    f u n c t i o n I n t e r v a l
    //-----------------------------------------------------------------------
    void TScriptManager::functionInterval(double T,void* userData)
    {
        int top = lua_gettop(m_lua);
        int ref = (int)(userData);

        // push the callback on the stack
        lua_rawgeti(m_lua, LUA_REGISTRYINDEX, ref);
        lua_pushnumber(m_lua, T);

        if (lua_pcall(m_lua,1,1,0) != 0)  
        {
            irr::core::stringc msg = "Error Invoking Event Callback";
            irr::core::stringc lmsg = lua_tostring(m_lua, -1);
            irr::core::stringc fileName, emsg;
            int line;

            parseLUAError(lmsg, fileName, line, emsg);

            /*
            msg += emsg;
            if(errorHandler)
                errorHandler->handleError(fileName, line, E_BAD_INPUT, msg);
            */

        }

        lua_settop(m_lua, top);
    }

    //-----------------------------------------------------------------------
    //                         h a n d l e E v e n t
    //-----------------------------------------------------------------------
    int TScriptManager::handleEvent(const TEvent* event)
    {
        int rc = 0;

        int top = lua_gettop(m_lua);

        int ref = (int)((TEvent*)event)->getUserData();


        // push the callback on the stack
        lua_rawgeti(m_lua, LUA_REGISTRYINDEX, ref);
        swig_type_info * type = SWIG_TypeQuery(m_lua, "TEvent *");
        SWIG_Lua_NewPointerObj(m_lua, (void *)event, type, 0);

        if (lua_pcall(m_lua,1,0,0) != 0)  
        {
            irr::core::stringc msg = "Error Invoking Event Callback";
            irr::core::stringc lmsg = lua_tostring(m_lua, -1);
            irr::core::stringc fileName, emsg;
            int line;

            parseLUAError(lmsg, fileName, line, emsg);

            /*
            msg += emsg;
            if(errorHandler)
                errorHandler->handleError(fileName, line, E_BAD_INPUT, msg);
            */
#ifdef _DEBUG
            dumpStack();
#endif
        }

        int result = getReturnInt();
        lua_settop(m_lua, top);
        return result;
    }

    //-----------------------------------------------------------------------
    //                         l o a d S c r i p t
    //-----------------------------------------------------------------------
    TScript* TScriptManager::loadScript(TString scriptName)
    {
        TScript* script = new TScript(this, m_lua);

        if(!script)
            return 0;

        if(script->initialize(m_scriptPath, scriptName))
        {
            script->drop();
            return 0;
        }

        m_scripts[scriptName] = script;
        return script;
    }

    //-----------------------------------------------------------------------
    //                        u n l o a d S c r i p t
    //-----------------------------------------------------------------------
    int TScriptManager::unloadScript(TScript* script)
    {
        return unloadScript(script->getModuleName());
    }

    //-----------------------------------------------------------------------
    //                        u n l o a d S c r i p t
    //-----------------------------------------------------------------------
    int TScriptManager::unloadScript(TString scriptName)
    {
        TScript* script;
        TScriptMapItr itr = m_scripts.find(scriptName);
        if(itr.atEnd())
            return 1;

        script = itr->getValue();
        m_scripts.delink(itr->getKey());

        script->drop();

        return 0;
    }

    //-----------------------------------------------------------------------
    //                       c r e a t e S t a t e s
    //-----------------------------------------------------------------------
    int TScriptManager::createStates()
    {        
        int result=0;

        if(m_mainScript->getStatesRef() > 0)
        {
            m_mainScript->initializeStates();
            getApplication()->setInitialState(m_mainScript->getInitialState());
        }
        return result;
    }



}
