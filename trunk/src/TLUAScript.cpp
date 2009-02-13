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
#ifdef SCRIPTING_ENABLED

// #include lua headers
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lapi.h"

#include "ldo.h"
#include "lfunc.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lstring.h"
#include "lundump.h"
}


extern "C" {
    int luaopen_tubras(lua_State* L);
}

namespace Tubras
{
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

    int testFunc(int v)
    {
        printf("testFunc: %d", v);
        return 2;
    }

    using namespace std;

    //-----------------------------------------------------------------------
    //                           T L U A S c r i p t
    //-----------------------------------------------------------------------
    TLUAScript::TLUAScript()
    {
    }

    //-----------------------------------------------------------------------
    //                         ~ T L U A S c r i p t
    //-----------------------------------------------------------------------
    TLUAScript::~TLUAScript()
    {
        if(m_lua)
            lua_close(m_lua);

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
    //                       t u b r a s _ p r i n t
    //-------------------------------------------------------------------------
    static int tubras_print (lua_State *L) {
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
            if (i>1) fputs("\t", stdout);
            fputs(s, stdout);
            lua_pop(L, 1);  /* pop result */
        }
        fputs("\n", stdout);
        return 0;
    }

    //-------------------------------------------------------------------------
    //                          _ p a r s e r L U A E r r o r
    //-------------------------------------------------------------------------
    void TLUAScript::_parseLUAError(stringc& lmsg, stringc& fileName, int& line, 
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
    //                            _ d u m p S t a c k
    //---------------------------------------------------------------------------
    void TLUAScript::_dumpStack()
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
    //                         _ d u m p T a b l e
    //-------------------------------------------------------------------------
    void TLUAScript::_dumpTable()
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
    //                  _ g e t T a b l e F i e l d S t r i n g
    //-------------------------------------------------------------------------
    const char* TLUAScript::_getTableFieldString (const char* table, const char *key) 
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
    //                  _ s e t T a b l e F i e l d S t r i n g
    //-------------------------------------------------------------------------
    bool TLUAScript::_setTableFieldString (const char* table, const char *key, const char* value)
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

    //-------------------------------------------------------------------------
    //                       _ s e t P a c k a g e P a t h
    //-------------------------------------------------------------------------
    void TLUAScript::_setPackagePath()
    {
        stringc cpath = _getTableFieldString("package","path");
        stringc dir = m_modPath;
        stringc npath;
        stringc ext;

        getFileNameExtension(ext, m_modName);
        if(!ext.size())
            ext = ".lua";

        if(dir == ".")
            dir += "/";

        npath = dir;
        npath += "?.lua;";
        //
        // add non ".lua" extensions.
        //
        if(!ext.equals_ignore_case(".lua") )
        {
            npath += dir;
            npath += "?";
            npath += ext;
            npath += ";";
        }
        npath += cpath;
        _setTableFieldString("package","path",npath.c_str());
    }


    //-------------------------------------------------------------------
    //                       p r i n t L U A E r r
    //-------------------------------------------------------------------
    void TLUAScript::printLUAErr()
    {
        return;
    }

    //-------------------------------------------------------------------
    //                        c h e c k E r r o r
    //-------------------------------------------------------------------
    int TLUAScript::checkError()
    {
        int result=0;

        return result;
    }

    //-------------------------------------------------------------------
    //                            u n R e f
    //-------------------------------------------------------------------
    int	TLUAScript::unRef(void *pobj)
    {

        if(!pobj)
            return 0;

        return 0;
    }

    //-------------------------------------------------------------------
    //                     i n h e r i t e d F r o m
    //-------------------------------------------------------------------
    bool TLUAScript::inheritedFrom(void* obj,TString cname)
    {

        return false;
    }

    //-------------------------------------------------------------------
    //                       g e t F u n c t i o n
    //-------------------------------------------------------------------
    void *TLUAScript::getFunction(void *pObj, TString funcname)
    {
        void* pFunc=0;

        return pFunc;
    }

    //-------------------------------------------------------------------
    //                       c a l l F u n c t i o n
    //-------------------------------------------------------------------
    SReturnValue* TLUAScript::callFunction(TString function, const char *fmt, ...)
    {
        SReturnValue* pResult=0;

        return pResult;
    }

    //-------------------------------------------------------------------
    //                       i n h e r i t s F r o m 
    //-------------------------------------------------------------------
    bool TLUAScript::inheritsFrom(const stringc className)
    {
        bool result=false;
        return result;
    }

    //-------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-------------------------------------------------------------------
    int TLUAScript::initialize(const stringc modPath, const stringc modName)
    {
        stringc ext;
        m_modPath = modPath;
        m_modName = modName;

        getFileNameExtension(ext, m_modName);
        if(!ext.size())
            m_modName += ".lua";

        m_modFile = m_modPath + m_modName;

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

        lua_getglobal(m_lua, "tubras");
        _dumpTable();
        lua_pop(m_lua, 1);

        // syntax checking
        if(luaL_loadfile(m_lua,m_modFile.c_str()) != 0)
        {
            stringc msg = "LSL Load Error: ";
            stringc lmsg = lua_tostring(m_lua, -1);
            stringc fileName, emsg;
            int line;

            _parseLUAError(lmsg, fileName, line, emsg);

            /*
            msg += emsg;
            if(errorHandler)
                errorHandler->handleError(fileName, line, E_BAD_SYNTAX, msg);
            */
#ifdef _DEBUG
            _dumpStack();
#endif
            return 1;
        }

        // no syntax errors so execute - loaded module is a function
        // at the top of the stack.
        if (lua_pcall(m_lua,0,0,0) != 0)  
        {
            irr::core::stringc msg = "LSL Execution Error: ";
            irr::core::stringc lmsg = lua_tostring(m_lua, -1);
            irr::core::stringc fileName, emsg;
            int line;

            _parseLUAError(lmsg, fileName, line, emsg);

            /*
            msg += emsg;
            if(errorHandler)
                errorHandler->handleError(fileName, line, E_BAD_INPUT, msg);
            */
#ifdef _DEBUG
            _dumpStack();
#endif
            return 1;
        }

        return 0;

    }
}
#endif
