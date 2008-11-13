//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
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
#include "lapi.h"

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
    irr::core::vector2di CLSL::m_defVector2di=irr::core::vector2di();
    irr::video::SColor   CLSL::m_defColor=irr::video::SColor();
    irr::core::vector3df CLSL::m_defVector3df=irr::core::vector3df();
    irr::core::rect<irr::s32> CLSL::m_defRects32=irr::core::rect<irr::s32>();

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
    //                            _ d u m p S t a c k
    //---------------------------------------------------------------------------
    void CLSL::_dumpStack()
    {
        int i;
        int top = lua_gettop(L);
        printf("\n---------------  Stack Dump ---------------\n");
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
    //                         _ d u m p G l o b a l s
    //-------------------------------------------------------------------------
    void CLSL::_dumpGlobals()
    {
        lua_getglobal(L, "_G");
        lua_pushnil(L);          
        while (lua_next(L, 1)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc key, value;
            if(lua_type(L, -2) == LUA_TSTRING)
            {
                key = lua_tostring(L, -2);
            }
            else 
            {
                key = lua_typename(L, lua_type(L, -2));
            }

            if(lua_type(L, -1) == LUA_TSTRING)
            {
                value = lua_tostring(L, -1);
            }
            else if(lua_type(L, -1) == LUA_TNUMBER)
            {
                value = "";
                value += lua_tonumber(L, -1);
            }
            else
                value = lua_typename(L, lua_type(L, -1));


            fprintf(stdout, "%s - %s\n", key.c_str(), value.c_str());

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);
        }
        lua_pop(L, 1);      // pop global (_G) table        
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
    //                           _ s p l i t N a m e
    //-------------------------------------------------------------------------
    int  CLSL::_splitName(irr::core::stringc name, SSTACK& nameStack)
    {
        irr::core::stringc wname = name;
        irr::s32 pos;
        nameStack.clear();

        while((pos = wname.findFirstChar(".", 1)) >= 0)
        {
            irr::core::stringc seg = wname.subString(0,pos);

            nameStack.push_back(seg);

            wname = wname.subString(pos+1,wname.size());
        }
        if(wname.size())
            nameStack.push_back(wname);

        return nameStack.getSize();
    }


    //-------------------------------------------------------------------------
    //                           _ g e t O b j e c t
    //-------------------------------------------------------------------------
    TValue* _getObject(lua_State* L, SSTACK& nameStack)
    {
        TValue* result=0;

        int top = lua_gettop(L);
        if(!top)
        {
            lua_getglobal(L, "_G");
            top = lua_gettop(L);
        }

        if(lua_type(L, top) != LUA_TTABLE)
        {
            lua_settop(L, 0);
            return 0;
        }

        irr::core::stringc name = (*(nameStack.begin())).c_str();
        nameStack.erase(nameStack.begin());

        lua_getfield(L, top, name.c_str());

        // not found?
        if(lua_gettop(L) == top)
        {
            lua_settop(L, 0);
            return 0;
        }

        // any more items?
        if(nameStack.getSize())
        {
            return _getObject(L, nameStack);
        }

        result = L->base + top;

        // reset the stack and push the result on top
        lua_settop(L, 0);
        luaA_pushobject(L, result);
        return result;

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
    //                          _ p u s h V a l u e
    //-------------------------------------------------------------------------
    void* CLSL::_pushValue(const irr::core::stringc varName)
    {
        SSTACK nameStack;
        _splitName(varName, nameStack);
        return _getObject(L, nameStack);
    }

    //-------------------------------------------------------------------------
    //                         _ p r i n t T a b l e
    //-------------------------------------------------------------------------
    void CLSL::_printTable()
    {
        fprintf(stdout, "\ntable:\n");
        lua_pushnil(L);          
        while (lua_next(L, 1)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc key, value;
            if(lua_type(L, -2) == LUA_TSTRING)
            {
                key = lua_tostring(L, -2);
            }
            else if(lua_type(L, -2) == LUA_TNUMBER)
            {
                key = lua_typename(L, lua_type(L, -2));
                key += ": ";
                key += (int)lua_tonumber(L, -2);
            }
            else 
            {
                key = lua_typename(L, lua_type(L, -2));
            }

            if(lua_type(L, -1) == LUA_TSTRING)
            {
                value = lua_tostring(L, -1);
            }
            else if(lua_type(L, -1) == LUA_TNUMBER)
            {
                value = "";
                value += lua_tonumber(L, -1);
            }
            else
                value = lua_typename(L, lua_type(L, -1));


            fprintf(stdout, "%s - %s\n", key.c_str(), value.c_str());

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);
        }
    }

    //-------------------------------------------------------------------------
    //                 _ t a b l e K e y s N u m e r i c
    //-------------------------------------------------------------------------
    bool CLSL::_tableKeysNumeric()
    {
        lua_pushnil(L);          
        while (lua_next(L, 1)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc key, value;
            if(lua_type(L, -2) != LUA_TNUMBER)
            {
                lua_pop(L, 2);
                return false;
            }
            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);
        }        
        return true;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t F i e l d I n t
    //-------------------------------------------------------------------------
    irr::u32 CLSL::_getFieldInt(char *fieldName)
    {
        irr::u32 result;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);
        result = (irr::u32) lua_tonumber(L, -1);
        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                            g e t F l o a t
    //-------------------------------------------------------------------------
    irr::f32 CLSL::getFloat(const irr::core::stringc varName, const irr::f32 defValue)
    {
        irr::f32 result = defValue;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt)
        {
        case LUA_TSTRING:
            {
                break;
            }
        case LUA_TNUMBER:
            {
                result = (irr::f32)lua_tonumber(L, -1);
                break;
            }
        case LUA_TBOOLEAN:
            {
                int b = lua_toboolean(L, -1);
                if(b)
                    result = 1;
                else result = 0;
                break;
            }
        }

        lua_pop(L, 1);      // pop returned value
        return result;
    }

    //-------------------------------------------------------------------------
    //                          g e t I n t e g e r
    //-------------------------------------------------------------------------
    int CLSL::getInteger(const irr::core::stringc varName, const int defValue)
    {
        int result = defValue;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt)
        {
        case LUA_TSTRING:
            {
                break;
            }
        case LUA_TNUMBER:
            {
                result = (int)lua_tonumber(L, -1);
                break;
            }
        case LUA_TBOOLEAN:
            {
                int b = lua_toboolean(L, -1);
                if(b)
                    result = 1;
                else result = 0;
                break;
            }
        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                             g e t B o o l
    //-------------------------------------------------------------------------
    bool CLSL::getBool(const irr::core::stringc varName, const bool defValue)
    {
        bool result = defValue;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt)
        {
        case LUA_TSTRING:
            {
                irr::core::stringc s = lua_tostring(L, -1);
                result = false;
                if(s.equals_ignore_case("true"))
                    result = true;
                break;
            }
        case LUA_TNUMBER:
            {
                double n = lua_tonumber(L, -1);
                result = true;
                if(n == 0)
                    result = false;
                break;
            }
        case LUA_TBOOLEAN:
            {
                int b = lua_toboolean(L, -1);
                if(b)
                    result = true;
                else result = false;
                break;
            }
        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                             g e t S t r i n g
    //-------------------------------------------------------------------------
    irr::core::stringc CLSL::getString(const irr::core::stringc varName, 
        const irr::core::stringc defValue)
    {
        irr::core::stringc result = defValue;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt)
        {
        case LUA_TSTRING:
            {
                result = lua_tostring(L, -1);
                break;
            }
        case LUA_TNUMBER:
            {
                double n = lua_tonumber(L, -1);
                char buf[128];
                sprintf(buf,"%f", n);
                break;
            }
        case LUA_TBOOLEAN:
            {
                int b = lua_toboolean(L, -1);
                if(b)
                    result = "true";
                else result = "false";
                break;
            }
        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                     i s A n i m a t e d M a t e r i a l   
    //-------------------------------------------------------------------------
    bool CLSL::isAnimatedMaterial(irr::core::stringc materialName)
    { 
        bool result=false;

        return result;
    }

    //-------------------------------------------------------------------------
    //                       a d d A n i m a t i o n R e f    
    //-------------------------------------------------------------------------
    void CLSL::addAnimationRef(irr::core::stringc materialName, irr::video::SMaterial& ref)
    {
    }

    //-------------------------------------------------------------------------
    //                        g e t S t r i n g A r r a y   
    //-------------------------------------------------------------------------
    irr::core::array<irr::core::stringc> CLSL::getStringArray(const irr::core::stringc varName)
    {
        irr::core::array<irr::core::stringc> result;
        return result;
    }

    //-------------------------------------------------------------------------
    //                          g e t S t r i n g M a p
    //-------------------------------------------------------------------------
    bool CLSL::getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID)
    {
        bool result=false;
        return result;
    }


    //-------------------------------------------------------------------------
    //                          g e t M a t e r i a l
    //-------------------------------------------------------------------------
    const irr::video::SMaterial& CLSL::getMaterial(irr::IrrlichtDevice* device, 
        const irr::core::stringc varName)
    {
        const irr::video::SMaterial& result=irr::video::SMaterial();

        return result;
    }

    //-------------------------------------------------------------------------
    //                     g e t M a t e r i a l L a y e r      
    //-------------------------------------------------------------------------
    const irr::video::SMaterialLayer& CLSL::getMaterialLayer(irr::IrrlichtDevice* device, 
        const irr::core::stringc varName)
    {
        const irr::video::SMaterialLayer& result = irr::video::SMaterialLayer();
        return result;
    }

    //-------------------------------------------------------------------------
    //                        g e t G U I E l e m e n t     
    //-------------------------------------------------------------------------
    irr::gui::IGUIElement* CLSL::getGUIElement(irr::IrrlichtDevice* device, 
        const irr::core::stringc varName)
    {
        irr::gui::IGUIElement* result=0;
        return result;
    }

    //-------------------------------------------------------------------------
    //                          g e t M a t r i x
    //-------------------------------------------------------------------------
    const irr::core::matrix4& CLSL::getMatrix(const irr::core::stringc varName)
    {
        const irr::core::matrix4& result=irr::core::matrix4();
        return result;
    }

    //-------------------------------------------------------------------------
    //                           g e t C o l o r
    //-------------------------------------------------------------------------
    const irr::video::SColor& CLSL::getColor(const irr::core::stringc varName,
        irr::video::SColor defValue)
    {
        irr::video::SColor& result=defValue;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt)
        {
        case LUA_TNUMBER:
            {
                irr::u32 n = (irr::u32)lua_tonumber(L, -1);
                result.setRed((n & 0xFF000000) >> 24);
                result.setGreen((n & 0x00FF0000) >> 16);
                result.setBlue((n & 0x0000FF00) >> 8);
                result.setAlpha(n & 0x000000FF);
                break;
            }
        case LUA_TTABLE:
            {
                if(_tableKeysNumeric())  // numeric indexes only?
                {
                    int count = luaL_getn(L, -1);
                    for(int i=1; i<=count; i++)
                    {
                        lua_rawgeti (L, -1, i);
                        switch(i)
                        {
                        case 1:
                            result.setRed((irr::u32)lua_tonumber(L,-1)); break;
                        case 2:
                            result.setGreen((irr::u32)lua_tonumber(L,-1)); break;
                        case 3:
                            result.setBlue((irr::u32)lua_tonumber(L,-1)); break;
                        case 4:
                            result.setAlpha((irr::u32)lua_tonumber(L,-1)); break;
                        };
                        lua_pop(L, 1);
                    }
                }
                else 
                {
                    result.setRed(_getFieldInt("red"));
                    result.setGreen(_getFieldInt("green"));
                    result.setBlue(_getFieldInt("blue"));
                    result.setAlpha(_getFieldInt("alpha"));
                }
                break;
            }
        }
        lua_pop(L, 1);

        return result;
    }

    //-------------------------------------------------------------------------
    //                        g e t V e c t o r 2 d i    
    //-------------------------------------------------------------------------
    irr::core::vector2di CLSL::getVector2di(const irr::core::stringc varName,
        const irr::core::vector2di defValue)
    {
        irr::core::vector2di result=defValue;
        return result;
    }

    //-------------------------------------------------------------------------
    //                        g e t V e c t o r 3 d f  
    //-------------------------------------------------------------------------
    irr::core::vector3df CLSL::getVector3df(const irr::core::stringc varName,
        const irr::core::vector3df& defValue)
    {
        irr::core::vector3df result=defValue;
        return result;
    }

    //-------------------------------------------------------------------------
    //                           g e t R e c t s 3 2
    //-------------------------------------------------------------------------
    irr::core::rect<irr::s32> CLSL::getRects32(const irr::core::stringc varName,
        const irr::core::rect<irr::s32> defValue)
    {
        irr::core::rect<irr::s32> result=defValue;
        return result;
    }

    //-------------------------------------------------------------------------
    //                        g e t D i m e n s i o n 2 d i  
    //-------------------------------------------------------------------------
    irr::core::dimension2di CLSL::getDimension2di(const irr::core::stringc varName, 
        const irr::core::dimension2di defValue)
    {
        irr::core::dimension2di result=defValue;
        return result;
    }

    //-------------------------------------------------------------------------
    //                            l o a d S c r i p t
    //-------------------------------------------------------------------------
    CLSLStatus CLSL::loadScript(const irr::core::stringc fileName, 
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

        if(dumpST)
            _dumpGlobals();

        // parse definitions...

        _dumpStack();

        return result;
    }

}