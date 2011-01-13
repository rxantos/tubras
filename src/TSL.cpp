//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#include <stdlib.h>
#define _fcvt fcvt
#define strnicmp strncasecmp
#endif

#ifdef WIN32
#define SEPARATOR   '\\'
#else
#define SEPARATOR   '/'
#endif

#define PROGNAME	"luaval"	        /* default program name */
#define	OUTPUT		PROGNAME ".out"	    /* default output file */

namespace Tubras
{
    // Because we are only using for "configuration", we really don't
    // need the standard libaries except for the base & package library
    // which is used to implement "require". Not including these
    // libraries saves ~50k. ~30k less than "isl".
    static const luaL_Reg lualibs[] = 
    {
        {"", luaopen_base},
        {LUA_LOADLIBNAME, luaopen_package},
        //        {LUA_TABLIBNAME, luaopen_table},
        //        {LUA_IOLIBNAME, luaopen_io},
        //        {LUA_OSLIBNAME, luaopen_os},
        //        {LUA_STRLIBNAME, luaopen_string},
        //        {LUA_MATHLIBNAME, luaopen_math},
        //        {LUA_DBLIBNAME, luaopen_debug},
        {NULL, NULL}
    };

    irr::core::vector2di TSL::m_defVector2di=irr::core::vector2di();
    irr::core::vector2df TSL::m_defVector2df=irr::core::vector2df();
    irr::video::SColor   TSL::m_defColor=irr::video::SColor();
    irr::core::vector3df TSL::m_defVector3df=irr::core::vector3df();
    irr::core::rect<irr::s32> TSL::m_defRects32=irr::core::rect<irr::s32>();
    irr::video::SMaterial m_defMaterial;
    irr::video::SMaterialLayer m_defMaterialLayer;

    //-------------------------------------------------------------------------
    //                                 T S L
    //-------------------------------------------------------------------------
    TSL::TSL(): L(0), m_overrides(0), m_animator(0), m_emptyNode(0)
    {
    }

    //-------------------------------------------------------------------------
    //                                ~ T S L
    //-------------------------------------------------------------------------
    TSL::~TSL() 
    {
        if(m_overrides)
            m_overrides->drop();

        if(m_animator)
            m_animator->drop();

        for ( SYMMAP::Iterator itr = m_matDefs.getIterator(); !itr.atEnd(); itr++)
        {
            SYMDATA*  pdata = itr->getValue();
            irr::video::SMaterial* p = (irr::video::SMaterial*)pdata->typeData;
            delete p;
            delete pdata;
        }
        for ( SYMMAP::Iterator itr = m_layDefs.getIterator(); !itr.atEnd(); itr++)
        {
            SYMDATA*  pdata = itr->getValue();
            irr::video::SMaterialLayer* p = (irr::video::SMaterialLayer*)pdata->typeData;
            if(pdata->userData)
                pdata->userData->drop();
            delete p;
            delete pdata;
        }
        if(L)
            lua_close(L);
    }

    //-------------------------------------------------------------------------
    //                           t s l _ p r i n t
    //-------------------------------------------------------------------------
    static int tsl_print (lua_State *L) {
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
        if(getApplication())
            getApplication()->logMessage(LOG_INFO, msg.c_str());
        else fprintf(stdout, msg.c_str());
        return 0;
    }

    //---------------------------------------------------------------------------
    //                            _ d u m p S t a c k
    //---------------------------------------------------------------------------
    void TSL::_dumpStack()
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
    //                         _ d u m p T a b l e
    //-------------------------------------------------------------------------
    void TSL::_dumpTable()
    {

        int top = lua_gettop(L);
        lua_pushnil(L);          
        printf("\n---------------  Table Dump ---------------\n");
        while (lua_next(L, -2)) 
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
        printf("----------------  End Dump ----------------\n");
    }

    //-------------------------------------------------------------------------
    //                             _ f i n d K e y
    //-------------------------------------------------------------------------
    bool TSL::_findKey(irr::core::stringc key, bool caseInsensitive)
    {
        TValue* result = 0;

        int top = lua_gettop(L);

        lua_pushnil(L);          
        while (lua_next(L, top)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc lkey, lvalue;
            if(lua_type(L, -2) == LUA_TSTRING)
            {
                lkey = lua_tostring(L, -2);
                if(key == lkey)
                {
                    // remove 'key', leaving 'value' at the top of
                    // the stack.
                    lua_remove(L, -2);
                    return true;
                }
            }

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);
        }

        return false;
    }

    //-------------------------------------------------------------------------
    //                       _ p a r s e r L U A E r r o r
    //-------------------------------------------------------------------------
    void TSL::_parseLUAError(const irr::core::stringc& lmsg, irr::core::stringc& fileName, int& line, 
        irr::core::stringc& emsg)
    {
        irr::core::stringc sline="";

        irr::s32 pos = lmsg.findFirst(':');
        if(pos < 0)
            return;

#ifdef TUBRAS_PLATFORM_WINDOWS
        if(lmsg[pos+1] == '/')
            pos = lmsg.findNext(':', pos+1);
#endif

        fileName = lmsg.subString(0,pos);

        for(irr::s32 i=pos+1; i<(irr::s32)lmsg.size(); i++)
        {
            irr::c8 c = lmsg[i];
            if(c == ':')
            {
                pos = i;
                break;
            }
            sline += c;
        }

        line = atoi(sline.c_str());

        while( (pos < (irr::s32)lmsg.size()) && ((lmsg[pos] == ' ') || (lmsg[pos] == ':')))
            ++pos;

        emsg = lmsg.subString(pos, lmsg.size());
    }

    //-------------------------------------------------------------------------
    //                         _ o p e n L u a L i b s
    //-------------------------------------------------------------------------
    void TSL::_openLuaLibs()
    {
        const luaL_Reg *lib;
        /* call open functions from 'loadedlibs' and set results to global table */
        for (lib = lualibs; lib->func; lib++) {
            luaL_requiref(L, lib->name, lib->func, 1);
            lua_pop(L, 1);  /* remove lib */
        }
    }

    //-------------------------------------------------------------------------
    //                         _ e x t r a c t D i r 
    //-------------------------------------------------------------------------
    irr::core::stringc TSL::_extractDir(irr::core::stringc filename)
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
    int  TSL::_splitName(irr::core::stringc name, SSTACK& nameStack)
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
    TValue* TSL::_getObject(SSTACK& nameStack)
    {
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
        SSTACK::Iterator itr = nameStack.begin();
        nameStack.erase(itr);

        if(!_findKey(name, true))
        {
            lua_settop(L, 0);
            return 0;
        }

        // more items?
        if(nameStack.getSize())
        {
            return _getObject(nameStack);
        }

        // remove all stack elements except the top (result) 
        while(lua_gettop(L) > 1)
            lua_remove(L, -2);

        return L->ci->func + 1;
    }

    //-------------------------------------------------------------------------
    //                       _ s e t P a c k a g e P a t h
    //-------------------------------------------------------------------------
    void TSL::_setPackagePath()
    {
        irr::core::stringc cpath = _getTableFieldString("package","path");
        irr::core::stringc dir = _extractDir(m_scriptName);
        irr::core::stringc npath;
        irr::core::stringc ext;

        irr::core::getFileNameExtension(ext, m_scriptName);

        if(dir == ".")
            dir += "/";

        npath = dir;
        npath += "?.lua;";
        npath += dir;
        npath += "?.tsl;";
        //
        // if script file extension not ".lua" or ".tsl", then add it.
        //
        if(!ext.equals_ignore_case(".lua") &&
            !ext.equals_ignore_case(".tsl") )
        {
            npath += dir;
            npath += "?";
            npath += ext;
            npath += ";";
        }
        npath += cpath;
        _setTableFieldString("package","path",npath.c_str());
    }

    //-------------------------------------------------------------------------
    //                  _ g e t T a b l e F i e l d S t r i n g
    //-------------------------------------------------------------------------
    const char* TSL::_getTableFieldString (const char* table, const char *key) 
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
    bool TSL::_setTableFieldString (const char* table, const char *key, const char* value)
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
    void* TSL::_pushValue(const irr::core::stringc varName)
    {
        SSTACK nameStack;
        _splitName(varName, nameStack);
        return _getObject(nameStack);
    }

    //-------------------------------------------------------------------------
    //                 _ t a b l e K e y s N u m e r i c
    //-------------------------------------------------------------------------
    bool TSL::_tableKeysNumeric()
    {
        lua_pushnil(L);          
        while (lua_next(L, -2)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            int n = lua_gettop(L);

            irr::core::stringc key, value;
            if(lua_type(L, -2) != LUA_TNUMBER)
            {
                lua_pop(L, 2);
                return false;
            }
            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);

            n = lua_gettop(L);
            const char* name = lua_typename(L, -2);
            name = lua_typename(L, -1);
            
                
        }        
        return true;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t I n t e g e r V a l u e
    //-------------------------------------------------------------------------
    bool TSL::_getIntegerValue(const char *fieldName, irr::u32& result)
    {
        bool rval=true;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);
        if(lua_isnil(L,-1))
            rval = false;
        else
            result = (irr::u32) lua_tonumber(L, -1);
        lua_pop(L, 1);
        return rval;
    }

    //-------------------------------------------------------------------------
    //                      _ g e t F l o a t V a l u e
    //-------------------------------------------------------------------------
    bool TSL::_getFloatValue(const char *fieldName, irr::f32& result)
    {
        bool rval=true;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);
        if(lua_isnil(L,-1))
            rval = false;
        else
            result = (irr::f32) lua_tonumber(L, -1);
        lua_pop(L, 1);
        return rval;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t S t r i n g V a l u e
    //-------------------------------------------------------------------------
    bool TSL::_getStringValue(const char* fieldName, irr::core::stringc& result)
    {
        bool rval=true;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);
        if(lua_isnil(L,-1))
            rval = false;
        else
            result = lua_tostring(L, -1);
        lua_pop(L, 1);
        return rval;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t B o o l V a l u e
    //-------------------------------------------------------------------------
    bool TSL::_getBoolValue(const char* fieldName, bool& result)
    {
        bool rval=true;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);

        if(lua_isnil(L,-1))
            rval = false;
        else
            result = lua_toboolean(L, -1) ? true : false;

        lua_pop(L, 1);
        return rval;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t C o l o r V a l u e
    //-------------------------------------------------------------------------
    irr::video::SColor TSL::_getColorValue()
    {
        irr::video::SColor result=0;
        int top=lua_gettop(L);

        switch(lua_type(L, top))
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
                    int count = lua_rawlen(L, top);
                    for(int i=1; i<=count; i++)
                    {
                        lua_rawgeti (L, top, i);
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
                    irr::u32 i;
                    if(_getIntegerValue("red", i))
                        result.setRed(i);
                    else if(_getIntegerValue("r", i))
                        result.setRed(i);
                    if(_getIntegerValue("green", i))
                        result.setGreen(i);
                    else if(_getIntegerValue("g", i))
                        result.setGreen(i);
                    if(_getIntegerValue("blue", i))
                        result.setBlue(i);
                    else if(_getIntegerValue("b", i))
                        result.setBlue(i);
                    if(_getIntegerValue("alpha", i))
                        result.setAlpha(i);
                    else if(_getIntegerValue("a", i))
                        result.setAlpha(i);
                }
                break;
            }
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t C o l o r V a l u e
    //-------------------------------------------------------------------------
    bool TSL::_getColorValue(const char *fieldName, irr::video::SColor& result)
    {
        bool rval=true;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);

        if(lua_isnil(L,-1))
            rval = false;
        else
            result = _getColorValue();

        lua_pop(L, 1);
        return rval;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t M a t r i x V a l u e
    //-------------------------------------------------------------------------
    irr::core::matrix4 TSL::_getMatrixValue()
    {
        irr::core::matrix4 result;
        int top=lua_gettop(L);
        int type=lua_type(L, top);

        if(type == LUA_TTABLE)
        {
            if(_tableKeysNumeric())  // numeric indexes only?
            {
                int count = lua_rawlen(L, -1);
                count = count > 3 ? 3 : count;
                for(int i=1; i<=count; i++)
                {
                    lua_rawgeti (L, -1, i);
                    irr::core::vector3df v = _getVector3dfValue();                    
                    switch(i)
                    {
                    case 1:
                        result.setTranslation(v); break;
                    case 2:
                        result.setRotationDegrees(v); break;
                    case 3:
                        result.setScale(v); break;
                    };                    
                    lua_pop(L, 1);
                }
            }
            else 
            {
                irr::core::vector3df vec;

                if(_getVector3dfValue("translation", vec))
                    result.setTranslation(vec);
                else if(_getVector3dfValue("t", vec))
                    result.setTranslation(vec);

                if(_getVector3dfValue("rotation", vec))
                    result.setRotationDegrees(vec);
                else if(_getVector3dfValue("r", vec))
                    result.setRotationDegrees(vec);

                if(_getVector3dfValue("scale", vec))
                    result.setScale(vec);
                else if(_getVector3dfValue("s", vec))
                    result.setScale(vec);
            }
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t M a t r i x V a l u e
    //-------------------------------------------------------------------------
    irr::core::matrix4 TSL::_getMatrixValue(const char* fieldName)
    {
        irr::core::matrix4 result;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);

        result = _getMatrixValue();

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                    _ g e t R e c t f 3 2 V a l u e
    //-------------------------------------------------------------------------
    irr::core::rect<irr::f32> TSL::_getRectf32Value()
    {
        irr::core::rect<irr::f32> result;
        int top = lua_gettop(L);
        if(_tableKeysNumeric())
        {
            int count = lua_rawlen(L, top);
            count = count > 4 ? 4 : count;
            for(int i=1; i<=count; i++)
            {
                lua_rawgeti (L, top, i);
                irr::f32 fv = (irr::f32) lua_tonumber(L, -1);
                switch(i)
                {
                case 1:                    
                    result.UpperLeftCorner.X = fv; break;
                case 2:
                    result.UpperLeftCorner.Y = fv; break;
                case 3:
                    result.LowerRightCorner.X = fv; break;
                case 4:
                    result.LowerRightCorner.Y = fv; break;
                }
                lua_pop(L, 1);
            }
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                    _ g e t R e c t f 3 2 V a l u e
    //-------------------------------------------------------------------------
    bool TSL::_getRectf32Value(const char*varName, irr::core::rect<irr::f32>& result)
    {
        bool rvalue=true;

        lua_pushstring(L, varName);
        lua_gettable(L, -2);  /* get table[key] */
        if (lua_istable(L, lua_gettop(L)))
        {
            result = _getRectf32Value();
        }
        else rvalue = false;
        lua_pop(L, 1);
        return rvalue;
    }

    //-------------------------------------------------------------------------
    //                   _ g e t V e c t o r 3 d f V a l u e
    //-------------------------------------------------------------------------
    irr::core::vector3df TSL::_getVector3dfValue()
    {
        int top = lua_gettop(L);
        irr::core::vector3df result = irr::core::vector3df();
        if(_tableKeysNumeric())
        {
            int count = lua_rawlen(L, top);
            count = count > 3 ? 3 : count;
            for(int i=1; i<=count; i++)
            {
                lua_rawgeti (L, top, i);
                irr::f32 fv = (irr::f32) lua_tonumber(L, -1);
                if(i == 1)
                    result.X = fv;
                else if(i==2)
                    result.Y = fv;
                else
                    result.Z = fv;
                lua_pop(L, 1);
            }
        }
        else
        {
            lua_pushstring(L, "x");
            lua_gettable(L, top);
            result.X = (irr::f32) lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y");
            lua_gettable(L, top);
            result.Y = (irr::f32) lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "z");
            lua_gettable(L, top);
            result.Z = (irr::f32) lua_tonumber(L, -1);
            lua_pop(L, 1);
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                   _ g e t V e c t o r 3 d f V a l u e
    //-------------------------------------------------------------------------
    bool TSL::_getVector3dfValue(const char *varName, irr::core::vector3df& result)
    {
        bool rvalue=true;

        lua_pushstring(L, varName);
        lua_gettable(L, -2);  /* get table[key] */
        if (lua_istable(L, lua_gettop(L)))
        {
            result = _getVector3dfValue();
        }
        else rvalue = false;
        lua_pop(L, 1);
        return rvalue;
    }

    //-------------------------------------------------------------------------
    //                   _ g e t V e c t o r 2 d f V a l u e
    //-------------------------------------------------------------------------
    bool TSL::_getVector2dfValue(const char *varName, irr::core::vector2df& result)
    {
        irr::core::vector3df temp;
        bool rvalue=true;

        lua_pushstring(L, varName);
        lua_gettable(L, -2);  /* get table[key] */
        if (lua_istable(L, lua_gettop(L)))
        {
            temp = _getVector3dfValue();
            result.X = temp.X;
            result.Y = temp.Y;
        }
        else rvalue = false;
        lua_pop(L, 1);
        return rvalue;
    }

    //-------------------------------------------------------------------------
    //                       _ g e t L a y e r D a t a
    //-------------------------------------------------------------------------
    TSL::SYMDATA* TSL::_getLayerData(irr::core::stringc materialName, irr::u32 layerNum)
    {
        irr::core::stringc layerName = materialName;
        layerName += ".layer";
        layerName += layerNum;

        SYMMAP::Node* node = m_layDefs.find(layerName);
        if(!node)
            return 0;

        return node->getValue();
    }

    //-------------------------------------------------------------------------
    //                     _ g e t M a t e r i a l L a y e r
    //-------------------------------------------------------------------------
    irr::video::SMaterialLayer* TSL::_getMaterialLayerValue(irr::IrrlichtDevice* device, 
        irr::core::stringc varName)
    {
        irr::core::vector3df vec;
        AMLParms aparms;
        bool hasAnim=false;
        SYMDATA* pdata;

        SYMMAP::Node* node = m_layDefs.find(varName);
        if(node)
        {
            pdata = node->getValue();
            if(pdata->type == stMaterialLayer)
                return (irr::video::SMaterialLayer*) pdata->typeData;
            return 0;
        }

        irr::video::IVideoDriver* videoDriver = device->getVideoDriver();
        irr::scene::ISceneManager* sceneManager = device->getSceneManager();

        irr::video::SMaterialLayer* result=new irr::video::SMaterialLayer();

        pdata = new SYMDATA();
        pdata->type = stMaterialLayer;
        pdata->typeData = result;


        irr::core::stringc texture="";
        _getStringValue("Texture", texture);
        if(texture.size())
            result->Texture = videoDriver->getTexture(texture);

        irr::u32 ival;
        bool bval;
        if(_getIntegerValue("TextureWrap", ival))
        {
            result->TextureWrapU = (irr::video::E_TEXTURE_CLAMP) ival;
            result->TextureWrapV = (irr::video::E_TEXTURE_CLAMP) ival;
        }
        if(_getIntegerValue("TextureWrapU", ival))
            result->TextureWrapU = (irr::video::E_TEXTURE_CLAMP) ival;
        if(_getIntegerValue("TextureWrapV", ival))
            result->TextureWrapV = (irr::video::E_TEXTURE_CLAMP) ival;

        if(_getBoolValue("BilinearFilter",bval))
            result->BilinearFilter = bval;
        if(_getBoolValue("TrilinearFilter",bval))
            result->TrilinearFilter = bval;
        if(_getIntegerValue("AnisotropicFilter", ival))
            result->AnisotropicFilter = ival;
        if(_getIntegerValue("LODBias", ival))
            result->LODBias = ival;

        result->setTextureMatrix(_getMatrixValue("TextureMatrix"));

        // transform matrix overrides
        irr::core::vector2df scale, offset, center, rotation;

        if(!_getVector2dfValue("Scale", scale))
        {
            scale.X = 1.f;
            scale.Y = 1.f;
        }

        if(!_getVector2dfValue("Offset", offset))
        {
            vec = result->getTextureMatrix().getTranslation();
            offset.X = vec.X;
            offset.Y = vec.Y;
        }

        if(!_getVector2dfValue("Center", center))
        {
            center.X = 0.0;
            center.Y = 0.0;
        }

        _getFloatValue("Rotation", aparms.orotation);

        if(_getVector2dfValue("AScroll", aparms.scroll))
            hasAnim = true;

        if(_getVector2dfValue("AScale", aparms.scale))
            hasAnim = true;

        if(_getFloatValue("ARotation", aparms.rotation))
        {
            aparms.rcenter.X = 0.5f;
            aparms.rcenter.Y = 0.5f;
            hasAnim = true;
        }

        _getVector2dfValue("ACenter", aparms.rcenter);

        if(hasAnim)
        {
            if(!m_emptyNode)
            {
                m_emptyNode = sceneManager->addEmptySceneNode(0, 0);
                m_emptyNode->setName("_emptyTSL_");
                m_animator = new TSceneNodeAnimatorMaterialLayer();
                m_emptyNode->addAnimator(m_animator);
            }
            aparms.cscale = scale;
            AMLParms* pparms = new AMLParms(aparms);
            pdata->userData = pparms;
        }

        irr::core::matrix4 tmat;
        aparms.orotation *= irr::core::DEGTORAD;
        tmat.buildTextureTransform(aparms.orotation, center, offset, scale);
        result->setTextureMatrix(tmat);

        m_layDefs[varName] = pdata;

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t M a t e r i a l
    //-------------------------------------------------------------------------
    irr::video::SMaterial* TSL::_getMaterialValue(irr::IrrlichtDevice* device, 
        irr::core::stringc varName)
    {
        irr::core::stringc scopedLayerName;

        SYMDATA* pdata;

        SYMMAP::Node* node = m_matDefs.find(varName);
        if(node)
        {
            pdata = node->getValue();
            if(pdata->type == stMaterial)
                return (irr::video::SMaterial*) pdata->typeData;
            return &m_defMaterial;
        }

        irr::video::SMaterial* result = new irr::video::SMaterial();
        pdata = new SYMDATA();
        pdata->type = stMaterial;
        pdata->typeData = result;

        irr::u32 ival;
        bool btemp;
        if(_getIntegerValue("MaterialType", ival))
            result->MaterialType = (irr::video::E_MATERIAL_TYPE) ival;
        _getColorValue("AmbientColor", result->AmbientColor);
        _getColorValue("DiffuseColor", result->DiffuseColor);
        _getColorValue("EmissiveColor", result->EmissiveColor);
        _getColorValue("SpecularColor", result->SpecularColor);
        _getFloatValue("Shininess", result->Shininess);
        _getFloatValue("MaterialTypeParam", result->MaterialTypeParam);
        _getFloatValue("MaterialTypeParam2", result->MaterialTypeParam2);
        _getFloatValue("Thickness", result->Thickness );
        if(_getIntegerValue("ZBuffer", ival))
            result->ZBuffer = ival;
        if(_getIntegerValue("AntiAliasing", ival))
            result->AntiAliasing = ival;
        if(_getIntegerValue("ColorMask", ival))
            result->ColorMask = ival;
        if(_getBoolValue("Wireframe", btemp))
            result->Wireframe = btemp;
        if(_getBoolValue("PointCloud", btemp))
            result->PointCloud = btemp;
        if(_getBoolValue("GouraudShading", btemp ))
            result->GouraudShading = btemp;
        if(_getBoolValue("Lighting", btemp))
            result->Lighting = btemp;
        if(_getBoolValue("ZWriteEnable", btemp ))
            result->ZWriteEnable = btemp;
        if(_getBoolValue("BackfaceCulling", btemp))
            result->BackfaceCulling = btemp;
        if(_getBoolValue("FrontfaceCulling", btemp))
            result->FrontfaceCulling = btemp;
        if(_getBoolValue("FogEnable", btemp))
            result->FogEnable = btemp;
        if(_getBoolValue("NormalizeNormals", btemp))
            result->NormalizeNormals = btemp;
        //
        // assign layers if defined
        //
        irr::video::SMaterialLayer* layer;
        lua_pushstring(L, "layer1");
        lua_gettable(L, -2);
        if(lua_type(L, lua_gettop(L)) == LUA_TTABLE)
        {
            scopedLayerName = varName;
            scopedLayerName += ".layer1";
            layer = _getMaterialLayerValue(device, scopedLayerName);
            if(layer)
                result->TextureLayer[0] = *layer;
        }
        lua_pop(L, 1);

        lua_pushstring(L, "layer2");
        lua_gettable(L, -2);
        if(lua_type(L, lua_gettop(L)) == LUA_TTABLE)
        {
            scopedLayerName = varName;
            scopedLayerName += ".layer2";
            layer = _getMaterialLayerValue(device, scopedLayerName);
            if(layer)
                result->TextureLayer[1] = *layer;
        }
        lua_pop(L, 1);

        lua_pushstring(L, "layer3");
        lua_gettable(L, -2);
        if(lua_type(L, lua_gettop(L)) == LUA_TTABLE)
        {
            scopedLayerName = varName;
            scopedLayerName += ".layer3";
            layer = _getMaterialLayerValue(device, scopedLayerName);
            if(layer)
                result->TextureLayer[2] = *layer;
        }
        lua_pop(L, 1);

        lua_pushstring(L, "layer4");
        lua_gettable(L, -2);
        if(lua_type(L, lua_gettop(L)) == LUA_TTABLE)
        {
            scopedLayerName = varName;
            scopedLayerName += ".layer4";
            layer = _getMaterialLayerValue(device, scopedLayerName);
            if(layer)
                result->TextureLayer[3] = *layer;
        }
        lua_pop(L, 1);

        m_matDefs[varName] = pdata;

        return result;
    }

    //-------------------------------------------------------------------------
    //                _ s e t G E L C o m m o n A t t r i b u t e s
    //-------------------------------------------------------------------------
    void TSL::_setGELCommonAttributes(irr::gui::IGUIElement* pel)
    {
        bool tbool;
        irr::u32 ival;
        irr::core::stringc scval;
        irr::core::stringw swval;
        irr::core::rect<irr::f32> bounds(0,0,.2f,.2f);
        irr::core::vector2df vec2;

        if(_getIntegerValue("id",ival))
            pel->setID(ival);

        if(_getStringValue("text", scval))
        {  
            swval = scval;
            pel->setText(swval.c_str());
        }

        if(_getBoolValue("visible", tbool))
            pel->setVisible(tbool);

        _getRectf32Value("bounds", bounds);

        pel->setRelativePositionProportional(bounds);
    }

    //-------------------------------------------------------------------------
    //                _ a d d G U I E l e m e n t C h i l d r e n
    //-------------------------------------------------------------------------
    int TSL::_addGUIElementChildren(irr::IrrlichtDevice* device, 
        irr::core::stringc varName, irr::gui::IGUIElement* parent)
    {
        int result=0;

        int top = lua_gettop(L);

        lua_pushnil(L);          
        while (lua_next(L, -2)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc key, value;
            if(lua_type(L, -2) == LUA_TSTRING)
            {
                key = lua_tostring(L, -2);

                if(lua_type(L, -1) == LUA_TTABLE)
                {
                    irr::u32 itype;
                    if(_getIntegerValue("_itype", itype) && 
                        itype == ITYPE_GUIELEMENT)
                    {
                        irr::core::stringc cname = varName;
                        cname += ".";
                        cname += key;
                        _getGUIElementValue(device, cname, parent);
                    }
                }
            }

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                    _ g e t G U I E l e m e n t V a l u e
    //-------------------------------------------------------------------------
    irr::gui::IGUIElement* TSL::_getGUIElementValue(irr::IrrlichtDevice* device, 
        irr::core::stringc varName, irr::gui::IGUIElement* parent)
    {
        SYMDATA* pdata;
        irr::gui::IGUIElement* result=0;
        irr::core::rect<irr::s32> irect(0,0,0,0);
        irr::gui::IGUIEnvironment* gui = device->getGUIEnvironment();
        irr::gui::EGUI_ELEMENT_TYPE etype;
        irr::u32 ival;


        SYMMAP::Node* node = m_guiDefs.find(varName);
        if(node)
        {
            pdata = node->getValue();
            return (irr::gui::IGUIElement*) pdata->typeData;
        }

        // element type defined?
        if(!_getIntegerValue("_etype", ival))
            return 0;
        etype = (irr::gui::EGUI_ELEMENT_TYPE)ival;

        pdata = new SYMDATA();
        pdata->type = stGUIElement;

        switch(etype)
        {
        case irr::gui::EGUIET_BUTTON:
            result = gui->addButton(irect);
            break;
        case irr::gui::EGUIET_CHECK_BOX:
            result = gui->addCheckBox(false, irect);
            break;
        case irr::gui::EGUIET_COMBO_BOX:
            result = gui->addComboBox(irect);
            break;
        case irr::gui::EGUIET_CONTEXT_MENU:
            result = gui->addContextMenu(irect);
            break;
        case irr::gui::EGUIET_MENU:
            result = gui->addMenu();
            break;
        case irr::gui::EGUIET_EDIT_BOX:
            result = gui->addEditBox(L"", irect);
            break;
        case irr::gui::EGUIET_FILE_OPEN_DIALOG:
            result = gui->addFileOpenDialog();
            break;
        case irr::gui::EGUIET_COLOR_SELECT_DIALOG:
            result = gui->addColorSelectDialog();
            break;
        case irr::gui::EGUIET_IN_OUT_FADER:
            result = gui->addInOutFader();
            break;
        case irr::gui::EGUIET_IMAGE:
            result = gui->addImage(irect);
            break;
        case irr::gui::EGUIET_LIST_BOX:
            result = gui->addListBox(irect);
            break;
        case irr::gui::EGUIET_MESH_VIEWER:
            result = gui->addMeshViewer(irect);
            break;
        case irr::gui::EGUIET_MESSAGE_BOX:
            result = gui->addMessageBox(L"");
            break;
        case irr::gui::EGUIET_MODAL_SCREEN:
            result = gui->addModalScreen(0);
            break;
        case irr::gui::EGUIET_SCROLL_BAR:
            result = gui->addScrollBar(false, irect);
            break;
        case irr::gui::EGUIET_SPIN_BOX:
            result = gui->addSpinBox(L"", irect);
            break;
        case irr::gui::EGUIET_STATIC_TEXT:
            result = gui->addStaticText(L"", irect);
            break;
        case irr::gui::EGUIET_TAB:
            result = gui->addTab(irect);
            break;
        case irr::gui::EGUIET_TAB_CONTROL:
            result = gui->addTabControl(irect);
            break;
        case irr::gui::EGUIET_TABLE:
            result = gui->addTable(irect);
            break;
        case irr::gui::EGUIET_TOOL_BAR:
            result = gui->addToolBar();
            break;
        case irr::gui::EGUIET_WINDOW:
            result = gui->addWindow(irect);            
            // window specific attributes

            break;
        default:
            
            return 0;
            break;
        };

        pdata->typeData = result;
        if(parent)
            parent->addChild(result);

        _setGELCommonAttributes(result);

        _addGUIElementChildren(device, varName, result);
        // todo - iterate and instantiate children

        m_guiDefs[varName] = pdata;

        return result;
    }

    //-------------------------------------------------------------------------
    //                       _ g e t S t r i n g M a p
    //-------------------------------------------------------------------------
    void TSL::_getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID)
    {
        int top = lua_gettop(L);
        lua_pushnil(L);          
        while (lua_next(L, -2)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc key, value;
            if(lua_type(L, -2) == LUA_TSTRING)
            {
                key = lua_tostring(L, -2);
                int vtype = lua_type(L, -1);
                irr::core::stringc sid;
                sid = key;
                if(scopedID)
                {
                    sid = varName;
                    sid += ".";
                    sid += key;
                }
                switch(vtype)
                {
                case LUA_TTABLE:
                    _getStringMap(sid, out, true);
                    break;
                case LUA_TSTRING:
                    out[sid] = lua_tostring(L, -1);    
                    break;
                case LUA_TNUMBER:
                    out[sid] = _fcvt(lua_tonumber(L, -1), 4, 0, 0);
                    break;
                case LUA_TBOOLEAN:
                    out[sid] = lua_toboolean(L, -1) ? "true" : "false";
                    break;
                }
            }

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);
        }
    }

    //-------------------------------------------------------------------------
    //                      _ g e t S t r i n g A r r a y
    //-------------------------------------------------------------------------
    void TSL::_getStringArray(irr::core::array<irr::core::stringc>& out)
    {
        int top = lua_gettop(L);
        lua_pushnil(L);          
        while (lua_next(L, -2)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc value;
            int vtype = lua_type(L, -1);
            switch(vtype)
            {
            case LUA_TSTRING:
                out.push_back(lua_tostring(L, -1));
                break;
            case LUA_TNUMBER:
                out.push_back(_fcvt(lua_tonumber(L, -1), 4, 0, 0));
                break;
            case LUA_TBOOLEAN:
                out.push_back(lua_toboolean(L, -1) ? "true" : "false");
                break;
            }

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);
        }
    }

    //-------------------------------------------------------------------------
    //                            g e t F l o a t
    //-------------------------------------------------------------------------
    irr::f32 TSL::getFloat(const irr::core::stringc varName, const irr::f32 defValue)
    {
        irr::f32 result = defValue;

        if(m_overrides && m_overrides->existsAttribute(varName.c_str()))
        {
            result = m_overrides->getAttributeAsFloat(varName.c_str());
            return result;
        }

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt_)
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
    int TSL::getInteger(const irr::core::stringc varName, const int defValue)
    {
        int result = defValue;

        if(m_overrides && m_overrides->existsAttribute(varName.c_str()))
        {
            result = m_overrides->getAttributeAsInt(varName.c_str());
            return result;
        }

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt_)
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
    bool TSL::getBool(const irr::core::stringc varName, const bool defValue)
    {
        bool result = defValue;

        if(m_overrides && m_overrides->existsAttribute(varName.c_str()))
        {
            result = m_overrides->getAttributeAsBool(varName.c_str());
            return result;
        }

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt_)
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
    irr::core::stringc TSL::getString(const irr::core::stringc varName, 
        const irr::core::stringc defValue)
    {
        irr::core::stringc result = defValue;

        if(m_overrides && m_overrides->existsAttribute(varName.c_str()))
        {
            result = m_overrides->getAttributeAsString(varName.c_str());
            return result;
        }

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        switch(value->tt_)
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
    bool TSL::isAnimatedMaterial(irr::core::stringc materialName)
    { 
        SYMDATA* pdata;
        SYMMAP::Node* node = m_matDefs.find(materialName);
        if(!node)
            return false;

        pdata = _getLayerData(materialName, 1);
        if(pdata && pdata->userData)
            return true;

        pdata = _getLayerData(materialName, 2);
        if(pdata && pdata->userData)
            return true;

        pdata = _getLayerData(materialName, 3);
        if(pdata && pdata->userData)
            return true;

        pdata = _getLayerData(materialName, 4);
        if(pdata && pdata->userData)
            return true;

        return false;
    }

    //-------------------------------------------------------------------------
    //                       a d d A n i m a t i o n R e f    
    //-------------------------------------------------------------------------
    void TSL::addAnimationRef(irr::core::stringc materialName, irr::video::SMaterial& ref)
    {
        if(!m_animator)
            return;

        SYMDATA* pdata;
        SYMMAP::Node* node = m_matDefs.find(materialName);
        if(!node)
            return;

        pdata = _getLayerData(materialName, 1);
        if(pdata && pdata->userData)
            m_animator->addMaterialRef(materialName + ".layer1", ref.TextureLayer[0], 
            (AMLParms*)pdata->userData);

        pdata = _getLayerData(materialName, 2);
        if(pdata && pdata->userData)
            m_animator->addMaterialRef(materialName + ".layer2", ref.TextureLayer[0], 
            (AMLParms*)pdata->userData);

        pdata = _getLayerData(materialName, 3);
        if(pdata && pdata->userData)
            m_animator->addMaterialRef(materialName + ".layer3", ref.TextureLayer[0], 
            (AMLParms*)pdata->userData);

        pdata = _getLayerData(materialName, 4);
        if(pdata && pdata->userData)
            m_animator->addMaterialRef(materialName + ".layer4", ref.TextureLayer[0], 
            (AMLParms*)pdata->userData);
    }

    //-------------------------------------------------------------------------
    //                        g e t S t r i n g A r r a y   
    //-------------------------------------------------------------------------
    bool TSL::getStringArray(const irr::core::stringc varName, 
        irr::core::array<irr::core::stringc>& out)
    {
        bool result=false;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return false;

        if(value->tt_ == LUA_TTABLE)
        {
            _getStringArray(out);
            result = true;
        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                          g e t S t r i n g M a p
    //-------------------------------------------------------------------------
    bool TSL::getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID)
    {
        bool result=false;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return false;

        if(value->tt_ == LUA_TTABLE)
        {
            _getStringMap(varName, out, scopedID);
            result = true;
        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                          g e t M a t e r i a l
    //-------------------------------------------------------------------------
    bool TSL::getMaterial(irr::IrrlichtDevice* device, 
        const irr::core::stringc varName, irr::video::SMaterial& result)
    {
        bool rvalue=false;
        irr::video::SMaterial* pmat=&result;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return false;

        if(value->tt_ == LUA_TTABLE)
        {
            pmat = _getMaterialValue(device, varName);
            result = *pmat;
            rvalue = true;
        }

        lua_pop(L, 1);
        return rvalue;
    }

    //-------------------------------------------------------------------------
    //                     g e t M a t e r i a l L a y e r      
    //-------------------------------------------------------------------------
    const irr::video::SMaterialLayer& TSL::getMaterialLayer(irr::IrrlichtDevice* device, 
        const irr::core::stringc varName)
    {
        irr::video::SMaterialLayer* pmatlayer = &m_defMaterialLayer;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return m_defMaterialLayer;

        if(value->tt_ == LUA_TTABLE)
        {
            pmatlayer = _getMaterialLayerValue(device, varName);
        }

        lua_pop(L, 1);
        return *pmatlayer;
    }

    //-------------------------------------------------------------------------
    //                        g e t G U I E l e m e n t     
    //-------------------------------------------------------------------------
    irr::gui::IGUIElement* TSL::getGUIElement(irr::IrrlichtDevice* device, 
        const irr::core::stringc varName)
    {
        irr::gui::IGUIElement* result=0;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return 0;

        if(value->tt_ == LUA_TTABLE)
        {
            result = _getGUIElementValue(device, varName);
        }

        lua_pop(L, 1);

        return result;
    }

    //-------------------------------------------------------------------------
    //                          g e t M a t r i x
    //-------------------------------------------------------------------------
    const irr::core::matrix4 TSL::getMatrix(const irr::core::stringc varName)
    {
        irr::core::matrix4 result=irr::core::IdentityMatrix;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        result = _getMatrixValue();

        lua_pop(L, 1);

        _dumpStack();

        return result;
    }

    //-------------------------------------------------------------------------
    //                           g e t C o l o r
    //-------------------------------------------------------------------------
    const irr::video::SColor TSL::getColor(const irr::core::stringc varName,
        irr::video::SColor defValue)
    {
        irr::video::SColor& result=defValue;

        if(m_overrides && m_overrides->existsAttribute(varName.c_str()))
        {
            result = m_overrides->getAttributeAsColor(varName.c_str());
            return result;
        }

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        result = _getColorValue();

        lua_pop(L, 1);

        return result;
    }

    //-------------------------------------------------------------------------
    //                        g e t V e c t o r 2 d i    
    //-------------------------------------------------------------------------
    irr::core::vector2di TSL::getVector2di(const irr::core::stringc varName,
        const irr::core::vector2di defValue)
    {
        irr::core::vector2di result=defValue;
        irr::core::vector3df temp;

        if(m_overrides && m_overrides->existsAttribute(varName.c_str()))
        {
            irr::core::position2di temp = m_overrides->getAttributeAsPosition2d(varName.c_str());
            result.X = temp.X;
            result.Y = temp.Y;
            return result;
        }

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        if(value->tt_ == LUA_TTABLE)
        {
            temp = _getVector3dfValue();
            result.X = (irr::s32) temp.X;
            result.Y = (irr::s32) temp.Y;

        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                        g e t V e c t o r 3 d f  
    //-------------------------------------------------------------------------
    irr::core::vector3df TSL::getVector3df(const irr::core::stringc varName,
        const irr::core::vector3df& defValue)
    {
        irr::core::vector3df result=defValue;

        if(m_overrides && m_overrides->existsAttribute(varName.c_str()))
        {
            result = m_overrides->getAttributeAsVector3d(varName.c_str());
            return result;
        }

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        if(value->tt_ == LUA_TTABLE)
        {
            result = _getVector3dfValue();
        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                           g e t R e c t s 3 2
    //-------------------------------------------------------------------------
    irr::core::rect<irr::s32> TSL::getRects32(const irr::core::stringc varName,
        const irr::core::rect<irr::s32> defValue)
    {
        irr::core::rect<irr::s32> result=defValue;
        irr::core::rect<irr::f32> temp;

        int top = lua_gettop(L);

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        top = lua_gettop(L);
        if(value->tt_ == LUA_TTABLE)
        {
            temp = _getRectf32Value();
            result.UpperLeftCorner.X = (irr::s32) temp.UpperLeftCorner.X;
            result.UpperLeftCorner.Y = (irr::s32) temp.UpperLeftCorner.Y;
            result.LowerRightCorner.X = (irr::s32) temp.LowerRightCorner.X;
            result.LowerRightCorner.Y = (irr::s32) temp.LowerRightCorner.Y;
        }

        lua_pop(L, 1);
        return result;

        return result;
    }

    //-------------------------------------------------------------------------
    //                        g e t D i m e n s i o n 2 d i  
    //-------------------------------------------------------------------------
    irr::core::dimension2di TSL::getDimension2di(const irr::core::stringc varName, 
        const irr::core::dimension2di defValue)
    {
        irr::core::dimension2di result=defValue;
        irr::core::vector3df temp;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        if(value->tt_ == LUA_TTABLE)
        {
            temp = _getVector3dfValue();
            result.Width = (irr::s32) temp.X;
            result.Height = (irr::s32) temp.Y;

        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                        g e t D i m e n s i o n 2 d u
    //-------------------------------------------------------------------------
    irr::core::dimension2du TSL::getDimension2du(const irr::core::stringc varName, 
        const irr::core::dimension2du defValue)
    {
        irr::core::dimension2du result=defValue;
        irr::core::vector3df temp;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        if(value->tt_ == LUA_TTABLE)
        {
            temp = _getVector3dfValue();
            result.Width = (irr::u32) temp.X;
            result.Height = (irr::u32) temp.Y;

        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                 s e t O v e r r i d e A t t r i b u t e s
    //-------------------------------------------------------------------------
    void TSL::setOverrideAttributes(irr::io::IAttributes* value)
    {
        if(m_overrides)
            m_overrides->drop();
        m_overrides = value;
        m_overrides->grab();
    }

    //-------------------------------------------------------------------------
    //                            l o a d S c r i p t
    //-------------------------------------------------------------------------
    TSLStatus TSL::loadScript(const irr::core::stringc fileName, 
        const bool dumpST, const bool dumpOI,
        TSLErrorHandler* errorHandler)
    {
        TSLStatus result;

        FILE* f = fopen(fileName.c_str(), "rb");
        if(!f)
        {
            return E_NO_FILE;
        }

        fseek(f, 0L, SEEK_END );
        long endPos = ftell( f );
        fseek(f, 0L, SEEK_SET);

        void* buffer = malloc(endPos+1);
        memset(buffer,0,endPos+1);
        size_t bytesRead = fread(buffer, endPos, 1, f);
        fclose( f );

        result = loadScript((const char*)buffer, endPos, fileName, dumpST, dumpOI, errorHandler);
        free(buffer);
        return result;
    }

    //-------------------------------------------------------------------------
    //                            l o a d S c r i p t
    //-------------------------------------------------------------------------
    TSLStatus TSL::loadScript(const char* buffer, size_t bufferLength, 
        const irr::core::stringc name, 
        const bool dumpST, const bool dumpOI,
        TSLErrorHandler* errorHandler)
    {
        TSLStatus result = E_OK;

        m_scriptName = name;

        L=luaL_newstate();
        if (L==NULL)
        {
            return E_OUT_OF_MEMORY;
        }

        // suspend collection during init
        lua_gc(L, LUA_GCSTOP, 0);  
        //_openLuaLibs();
        luaL_openlibs(L);  
        lua_gc(L, LUA_GCRESTART, 0);

        // mod package path to include original script location
        _setPackagePath();

        // "print" output will be sent to the application log and stdout
        lua_pushcfunction(L, tsl_print);
        lua_setglobal(L, "print");

        // syntax checking
        if(luaL_loadbuffer(L, buffer, bufferLength, name.c_str()) != 0)
        {
            irr::core::stringc msg = "TSL Load Error: ";
            irr::core::stringc lmsg = lua_tostring(L, -1);
            irr::core::stringc name, emsg;
            int line;

            _parseLUAError(lmsg, name, line, emsg);

            msg += emsg;
            if(errorHandler)
                errorHandler->handleScriptError(name, line, E_BAD_SYNTAX, msg);
#ifdef _DEBUG
            _dumpStack();
#endif
            return E_BAD_SYNTAX;
        }

        // no syntax errors so execute - loaded module is a function
        // at the top of the stack.
        if (lua_pcall(L,0,0,0) != 0)  
        {
            irr::core::stringc msg = "TSL Execution Error: ";
            irr::core::stringc lmsg = lua_tostring(L, -1);
            irr::core::stringc name, emsg;
            int line;

            _parseLUAError(lmsg, name, line, emsg);

            msg += emsg;
            if(errorHandler)
                errorHandler->handleScriptError(name, line, E_BAD_INPUT, msg);
#ifdef _DEBUG
            _dumpStack();
#endif
            return E_BAD_INPUT;
        }

        if(dumpST)
        {
            lua_getglobal(L, "_G");
            _dumpTable();
            lua_pop(L, 1);
        }

        //_dumpStack();

        return result;
    }

}
