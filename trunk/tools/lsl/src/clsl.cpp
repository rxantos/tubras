#include "clsl.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define luac_c
#define LUA_CORE

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "ldo.h"
#include "lfunc.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lstring.h"
#include "lundump.h"
}

#ifdef WIN32
#define SEPARATOR   '\\'
#else
#define SEPARATOR   '/'
#endif

#define PROGNAME	"luaval"	        /* default program name */
#define	OUTPUT		PROGNAME ".out"	    /* default output file */

namespace lsl
{
    //-------------------------------------------------------------------------
    //                                C L S L
    //-------------------------------------------------------------------------
    CLSL::CLSL()
    {
    }

    //-------------------------------------------------------------------------
    //                               ~ C L S L
    //-------------------------------------------------------------------------
    CLSL::~CLSL()
    {
    }

    //---------------------------------------------------------------------------
    //                             d u m p S t a c k
    //---------------------------------------------------------------------------
    void CLSL::_dumpStack()
    {
        int i;
        int top = lua_gettop(L);
        printf("---------------  Stack Dump ---------------\n");
        for (i = 1; i <= top; i++) 
        {  
            int t = lua_type(L, i);
            switch (t) 
            {
            case LUA_TSTRING:  /* strings */
                printf("STRING: `%s'\n", lua_tostring(L, i));
                break;

            case LUA_TBOOLEAN:  /* booleans */
                printf("BOOLEAN: %s\n",lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                printf("NUMBER: %g\n", lua_tonumber(L, i));
                break;

            default:  /* other values */
                printf("%s\n", lua_typename(L, t));
                break;
            }
        }
        printf("----------------  End Dump ----------------\n");
    }

    //-------------------------------------------------------------------------
    //                         _ e x t r a c t D i r 
    //-------------------------------------------------------------------------
    irr::core::stringc CLSL::_extractDir(irr::core::stringc filename)
    {
        irr::core::stringc result="";
        // find last forward or backslash
        irr::s32 lastSlash = filename.findLast('/');
        const irr::s32 lastBackSlash = filename.findLast('\\');
        lastSlash = lastSlash > lastBackSlash ? lastSlash : lastBackSlash;

        if ((irr::u32)lastSlash < filename.size())
            return filename.subString(0, lastSlash+1);
        else
            return ".";
    }

    //-------------------------------------------------------------------------
    //                       _ s e t P a c k a g e P a t h
    //-------------------------------------------------------------------------
    void CLSL::_setPackagePath()
    {
        irr::core::stringc cpath = _getTableFieldString("package","path");
        irr::core::stringc dir = _extractDir(m_scriptName);
        irr::core::stringc npath;

        npath = dir;
        npath += "?.lua;";
        npath += dir;
        npath += "?.lsl;";
        npath += cpath;
        _setTableFieldString("package","path",npath.c_str());
    }

    //-------------------------------------------------------------------------
    //                  _ g e t T a b l e F i e l d S t r i n g
    //-------------------------------------------------------------------------
    const char* CLSL::_getTableFieldString (const char* table, const char *key) 
    {
        const char* result=0;
        int top,t;

        lua_getglobal(L, table);
        top = lua_gettop(L);
        t = lua_type(L, top);
        if(t != LUA_TTABLE)
        {
            lua_pop(L,1);
            return 0;
        }

        lua_pushstring(L, key);
        lua_gettable(L, -2);  /* get table[key] */
        if (!lua_isstring(L, -1))
        {
            fprintf(stdout,"Table key is not a string: %s\n",key);
            lua_pop(L, 1);
            lua_pop(L, 1);
            return 0;
        }
        result = lua_tostring(L, -1);
        lua_pop(L, 1);  // pop int value
        lua_pop(L, 1);  // pop table

        return result;
    }

    //-------------------------------------------------------------------------
    //                  _ s e t T a b l e F i e l d S t r i n g
    //-------------------------------------------------------------------------
    bool CLSL::_setTableFieldString (const char* table, const char *key, const char* value)
    {
        int top,t;

        lua_getglobal(L, table);
        top = lua_gettop(L);
        t = lua_type(L, top);
        if(t != LUA_TTABLE)
        {
            lua_pop(L,1);
            return false;
        }

        lua_pushstring(L, key);
        lua_pushstring(L, value);
        lua_settable(L, -3);
        lua_pop(L, 1);  // pop table

        return true;
    }

    //-------------------------------------------------------------------------
    //                           p a r s e S c r i p t
    //-------------------------------------------------------------------------
    CLSLStatus CLSL::parseScript(const irr::core::stringc fileName, 
            const bool dumpST, const bool dumpOI,
            const CLSLErrorHandler& errorHandler)
    {
        CLSLStatus result = lsl::E_OK;

        m_scriptName = fileName;

        L=lua_open();
        if (L==NULL)
        {
            return lsl::E_OUT_OF_MEMORY;
        }

        // suspend collection during init
        lua_gc(L, LUA_GCSTOP, 0);  
        luaL_openlibs(L);  
        lua_gc(L, LUA_GCRESTART, 0);

        // mod package path to include original script location
        _setPackagePath();

        // syntax checking
        if(luaL_loadfile(L,m_scriptName.c_str()) != 0)
        {
            fprintf(stderr,"Load Error: '%s'", lua_tostring(L, -1));
            _dumpStack();
            return lsl::E_BAD_SYNTAX;
        }

        // no syntax errors so execute - loaded module is a function
        // at the top of the stack.
        if (lua_pcall(L,0,0,0) != 0)  
        {
            fprintf(stderr,"Execution Error: '%s'", lua_tostring(L, -1));
            _dumpStack();
            return lsl::E_BAD_INPUT;
        }

        // parse definitions...
        

        return result;
    }

}