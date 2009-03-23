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

namespace Tubras
{
    int testFunc(int v)
    {
        printf("testFunc: %d\n", v);
        return 2;
    }

    using namespace std;

    //-----------------------------------------------------------------------
    //                             T S c r i p t
    //-----------------------------------------------------------------------
    TScript::TScript(TScriptManager* manager, lua_State* lua) : m_manager(manager),
        m_lua(lua), m_initialState("")
    {
    }

    //-----------------------------------------------------------------------
    //                           ~ T S c r i p t
    //-----------------------------------------------------------------------
    TScript::~TScript()
    {
        /*
        for(MAP_SCRIPTFUNCS_ITR it=m_functions.getIterator();!it.atEnd();it++)
        {
            PyObject* obj = it->getValue();
            Py_DECREF(obj);
        }

        if(m_module)
        {
            Py_DECREF(m_module);
            m_module = 0;
        }
        */
    }

    //-------------------------------------------------------------------------
    //                         _ e x t r a c t D i r 
    //-------------------------------------------------------------------------
    stringc _extractDir(stringc filename)
    {
        stringc result="";
        // find last forward or backslash
        s32 lastSlash = filename.findLast('/');
        const s32 lastBackSlash = filename.findLast('\\');
        lastSlash = lastSlash > lastBackSlash ? lastSlash : lastBackSlash;

        if ((u32)lastSlash < filename.size())
            return filename.subString(0, lastSlash+1);
        else
            return ".";
    }

    //-------------------------------------------------------------------
    //                       p r i n t L U A E r r
    //-------------------------------------------------------------------
    void TScript::printLUAErr()
    {
        return;
    }

    //-------------------------------------------------------------------
    //                        c h e c k E r r o r
    //-------------------------------------------------------------------
    int TScript::checkError()
    {
        int result=0;

        return result;
    }

    //-------------------------------------------------------------------
    //                      g e t R e t u r n I n t
    //-------------------------------------------------------------------
    int TScript::getReturnInt()
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

    //-------------------------------------------------------------------
    //                            u n R e f
    //-------------------------------------------------------------------
    int	TScript::unRef(void *pobj)
    {

        if(!pobj)
            return 0;

        return 0;
    }

    //-------------------------------------------------------------------
    //                        h a s F u n c t i o n
    //-------------------------------------------------------------------
    bool TScript::hasFunction(TString functionName)
    {
        bool result=false;

        m_manager->dumpStack();
        lua_getglobal(m_lua, functionName.c_str());  /* function to be called */
        m_manager->dumpStack();

        if(lua_type(m_lua,-1) == LUA_TFUNCTION)
            result = true;

        lua_pop(m_lua,1);

        m_manager->dumpStack();
        return result;
    }

    //-------------------------------------------------------------------
    //                       c a l l F u n c t i o n
    //-------------------------------------------------------------------
    SReturnValue* TScript::callFunction(TString functionName, int resultCount, const char *fmt, ...)
    {
        SReturnValue* pResult=new SReturnValue();
        va_list             ap;
        const char          *p=fmt;
        int                 args=0;

        int top = lua_gettop(m_lua);
        // todo: func/ref table lookup 

        m_manager->dumpStack();

        lua_getglobal(m_lua, functionName.c_str());
        if(lua_type(m_lua,-1) != LUA_TFUNCTION)
            return 0;

        if(fmt)
        {
            //
            // Build parameter list
            //
            va_start(ap,fmt);
            args = (int) strlen(p);

            for(int i=0;*p;i++)
            {
                switch(*p)
                {
                case 's':
                    lua_pushstring(m_lua, va_arg(ap,const char *));
                    break;
                case 'i':
                    lua_pushinteger(m_lua, va_arg(ap, long));   
                    break;
                case 'f':
                    lua_pushnumber(m_lua, va_arg(ap, double)); 
                    break;
                case 'v':
                case 'p':
                    lua_pushlightuserdata(m_lua, va_arg(ap, void*));
                    break;
                }
                ++p;
            }
        }

        // call the function
        if (lua_pcall(m_lua, args, resultCount, 0) != 0)
        {
            TString msg = "Error calling function: ";
            msg += functionName;
            msg += " - ";
            msg += lua_tostring(m_lua, -1);
            getApplication()->logMessage(msg);
            return 0;
        }

        // parse return value
        if(resultCount)
        {
            if(lua_isnumber(m_lua, -1))
            {
                pResult->type = stNumber;
                pResult->dValue = lua_tonumber(m_lua, -1);
            }
            else if(lua_isstring(m_lua, -1)) 
            {
                pResult->type = stString;
                pResult->sValue = lua_tostring(m_lua, -1);
            }
            else if(lua_istable(m_lua, -1))
            {
                pResult->type = stTableRef;
                pResult->iTableRef = luaL_ref(m_lua, LUA_REGISTRYINDEX);
            }
        }

        // reset the stack
        lua_settop(m_lua, top);            
        return pResult;
    }

    //-------------------------------------------------------------------
    //                       c r e a t e S t a t e
    //-------------------------------------------------------------------
    int TScript::createState()
    {
        int result=0;
        TString name;
        int ref_init=0, ref_enter=0, ref_exit=0; 
        int ref_pause=0, ref_resume=0, ref_reset=0;

        lua_pushstring(m_lua, "name");
        lua_gettable(m_lua, -2);  
        if (lua_isstring(m_lua, -1))
            name = lua_tostring(m_lua, -1);
        lua_pop(m_lua, 1);  

        if(!m_initialState.size())
            m_initialState = name;

        lua_pushstring(m_lua, "initialize");
        lua_gettable(m_lua, -2);  
        if (lua_isfunction(m_lua, -1))
            ref_init = luaL_ref(m_lua, LUA_REGISTRYINDEX);
        else lua_pop(m_lua, 1);  

        lua_pushstring(m_lua, "enter");
        lua_gettable(m_lua, -2);  
        if (lua_isfunction(m_lua, -1))
            ref_enter = luaL_ref(m_lua, LUA_REGISTRYINDEX);
        else lua_pop(m_lua, 1);  

        lua_pushstring(m_lua, "exit");
        lua_gettable(m_lua, -2);  
        if (lua_isfunction(m_lua, -1))
            ref_exit = luaL_ref(m_lua, LUA_REGISTRYINDEX);
        else lua_pop(m_lua, 1);  

        lua_pushstring(m_lua, "pause");
        lua_gettable(m_lua, -2);  
        if (lua_isfunction(m_lua, -1))
            ref_pause = luaL_ref(m_lua, LUA_REGISTRYINDEX);
        else lua_pop(m_lua, 1);  

        lua_pushstring(m_lua, "resume");
        lua_gettable(m_lua, -2);  
        if (lua_isfunction(m_lua, -1))
            ref_resume = luaL_ref(m_lua, LUA_REGISTRYINDEX);
        else lua_pop(m_lua, 1);  

        lua_pushstring(m_lua, "reset");
        lua_gettable(m_lua, -2);  
        if (lua_isfunction(m_lua, -1))
            ref_reset = luaL_ref(m_lua, LUA_REGISTRYINDEX);
        else lua_pop(m_lua, 1);  

        TScriptState* state = new TScriptState(name, m_lua, ref_init, 
            ref_enter, ref_exit, ref_pause, ref_resume, ref_reset );

        return result;
    }

    //-------------------------------------------------------------------
    //                   i n i t i a l i z e S t a t e s
    //-------------------------------------------------------------------
    int TScript::initializeStates(SReturnValue* value)
    {
        int result=0;

        lua_rawgeti(m_lua, LUA_REGISTRYINDEX, value->iTableRef);
        if(!lua_istable(m_lua, -1))
            return 1;

        int top = lua_gettop(m_lua);
        lua_pushnil(m_lua);          
        while (lua_next(m_lua, top)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            if(lua_type(m_lua, -1) == LUA_TTABLE)
            {
                createState();
            }

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(m_lua, 1);
        }

        return result;
    }

    //-------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-------------------------------------------------------------------
    int TScript::initialize(const stringc modPath, const stringc modName)
    {
        stringc ext;
        m_modPath = modPath;
        m_modName = modName;

        getFileNameExtension(ext, m_modName);
        if(!ext.size())
            m_modName += ".lua";

        m_modFile = m_modPath + m_modName;

        // syntax checking
        if(luaL_loadfile(m_lua,m_modFile.c_str()) != 0)
        {
            stringc msg = "Script Load Error: ";
            stringc lmsg = lua_tostring(m_lua, -1);
            stringc fileName, emsg;
            int line;

            m_manager->parseLUAError(lmsg, fileName, line, emsg);

            getApplication()->logMessage(msg);
            emsg = "    ";
            emsg += lmsg;
            getApplication()->logMessage(emsg);

            /*
            msg += emsg;
            if(errorHandler)
                errorHandler->handleError(fileName, line, E_BAD_SYNTAX, msg);
            */
#ifdef _DEBUG
            m_manager->dumpStack();
#endif
            return 1;
        }

        // no syntax errors so execute - loaded module is a function
        // at the top of the stack.
        m_manager->dumpStack();
        if (lua_pcall(m_lua,0,1,0) != 0)  
        {
            irr::core::stringc msg = "Script Execution Error: ";
            irr::core::stringc lmsg = lua_tostring(m_lua, -1);
            irr::core::stringc fileName, emsg;
            int line;

            m_manager->parseLUAError(lmsg, fileName, line, emsg);

            getApplication()->logMessage(msg);
            emsg = "    ";
            emsg += lmsg;
            getApplication()->logMessage(emsg);

            /*
            msg += emsg;
            if(errorHandler)
                errorHandler->handleError(fileName, line, E_BAD_INPUT, msg);
            */
#ifdef _DEBUG
            m_manager->dumpStack();
#endif
            return 1;
        }

        return getReturnInt();
    }
}
