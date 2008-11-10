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
    void CLSL::dumpStack(lua_State* L) 
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

        // syntax checking
        if(luaL_loadfile(L,m_scriptName.c_str()) != 0)
        {
            fprintf(stderr,"Load Error: '%s'", lua_tostring(L, -1));
            dumpStack(L);
            return lsl::E_BAD_SYNTAX;
        }

        // no syntax errors so execute
        if (lua_pcall(L,0,0,0) != 0)  
        {
            fprintf(stderr,"Execution Error: '%s'", lua_tostring(L, -1));
            dumpStack(L);
            return lsl::E_BAD_INPUT;
        }

        // parse definitions...
        

        return result;
    }

}