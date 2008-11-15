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

    irr::core::vector2di CLSL::m_defVector2di=irr::core::vector2di();
    irr::video::SColor   CLSL::m_defColor=irr::video::SColor();
    irr::core::vector3df CLSL::m_defVector3df=irr::core::vector3df();
    irr::core::rect<irr::s32> CLSL::m_defRects32=irr::core::rect<irr::s32>();
    irr::video::SMaterial m_defMaterial;
    irr::video::SMaterialLayer m_defMaterialLayer;

    //-------------------------------------------------------------------------
    //                                C L S L
    //-------------------------------------------------------------------------
    CLSL::CLSL(): m_emptyNode(0)
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
    //                         _ d u m p T a b l e
    //-------------------------------------------------------------------------
    void CLSL::_dumpTable()
    {
        int top = lua_gettop(L);

        lua_pushnil(L);          
        while (lua_next(L, top)) 
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
    }


    //-------------------------------------------------------------------------
    //                         _ o p e n L u a L i b s
    //-------------------------------------------------------------------------
    void CLSL::_openLuaLibs()
    {
        const luaL_Reg *lib = lualibs;
        for (; lib->func; lib++) 
        {
            lua_pushcfunction(L, lib->func);
            lua_pushstring(L, lib->name);
            lua_call(L, 1, 0);
        }
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
        int top = lua_gettop(L);
        lua_pushnil(L);          
        while (lua_next(L, top)) 
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
    //                     _ g e t I n t e g e r V a l u e
    //-------------------------------------------------------------------------
    irr::u32 CLSL::_getIntegerValue(char *fieldName)
    {
        irr::u32 result;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);
        result = (irr::u32) lua_tonumber(L, -1);
        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                      _ g e t F l o a t V a l u e
    //-------------------------------------------------------------------------
    bool CLSL::_getFloatValue(char *fieldName, irr::f32& result)
    {
        bool rval=true;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);
        if(lua_isnil(L,-1))
            rval = false;
        result = (irr::f32) lua_tonumber(L, -1);
        lua_pop(L, 1);
        return rval;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t S t r i n g V a l u e
    //-------------------------------------------------------------------------
    irr::core::stringc CLSL::_getStringValue(char* fieldName)
    {
        irr::core::stringc result;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);
        result = lua_tostring(L, -1);
        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t B o o l V a l u e
    //-------------------------------------------------------------------------
    bool CLSL::_getBoolValue(char* fieldName)
    {
        bool result;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);
        result = lua_toboolean(L, -1) ? true : false;
        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t C o l o r V a l u e
    //-------------------------------------------------------------------------
    irr::video::SColor CLSL::_getColorValue()
    {
        irr::video::SColor result;
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
                    int count = luaL_getn(L, top);
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
                    result.setRed(_getIntegerValue("red"));
                    result.setGreen(_getIntegerValue("green"));
                    result.setBlue(_getIntegerValue("blue"));
                    result.setAlpha(_getIntegerValue("alpha"));
                }
                break;
            }
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t C o l o r V a l u e
    //-------------------------------------------------------------------------
    irr::video::SColor CLSL::_getColorValue(char *fieldName)
    {
        irr::video::SColor result;
        lua_pushstring(L, fieldName);
        lua_gettable(L, -2);

        result = _getColorValue();

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t M a t r i x V a l u e
    //-------------------------------------------------------------------------
    irr::core::matrix4 CLSL::_getMatrixValue()
    {
        irr::core::matrix4 result;
        int top=lua_gettop(L);
        int type=lua_type(L, top);

        if(type == LUA_TTABLE)
        {
            if(_tableKeysNumeric())  // numeric indexes only?
            {
                int count = luaL_getn(L, -1);
                count = count > 3 ? 3 : count;
                for(int i=1; i<=count; i++)
                {
                    lua_rawgeti (L, -1, i);
                    irr::core::vector3df v = _getVector3dfValue();                    
                    switch(i)
                    {
                    case 1:
                        result.setRotationDegrees(v);
                    case 2:
                        result.setTranslation(v);
                    case 3:
                        result.setScale(v);
                    };                    
                    lua_pop(L, 1);
                }
            }
            else 
            {
                result.setRotationDegrees(_getVector3dfValue("rotation"));
                result.setTranslation(_getVector3dfValue("translation"));
                result.setScale(_getVector3dfValue("scale"));
            }
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                     _ g e t M a t r i x V a l u e
    //-------------------------------------------------------------------------
    irr::core::matrix4 CLSL::_getMatrixValue(char* fieldName)
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
    irr::core::rect<irr::f32> CLSL::_getRectf32Value()
    {
        irr::core::rect<irr::f32> result;
        int top = lua_gettop(L);
        if(_tableKeysNumeric())
        {
            int count = luaL_getn(L, top);
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
    //                   _ g e t V e c t o r 3 d f V a l u e
    //-------------------------------------------------------------------------
    irr::core::vector3df CLSL::_getVector3dfValue()
    {
        int top = lua_gettop(L);
        irr::core::vector3df result = irr::core::vector3df();
        if(_tableKeysNumeric())
        {
            int count = luaL_getn(L, top);
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
    irr::core::vector3df CLSL::_getVector3dfValue(char *varName)
    {
        irr::core::vector3df result;

        lua_pushstring(L, varName);
        lua_gettable(L, -2);  /* get table[key] */
        if (lua_istable(L, lua_gettop(L)))
        {
            result = _getVector3dfValue();
        }
        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                   _ g e t V e c t o r 2 d f V a l u e
    //-------------------------------------------------------------------------
    bool CLSL::_getVector2dfValue(const char *varName, irr::core::vector2df& result)
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
    CLSL::SYMDATA* CLSL::_getLayerData(irr::core::stringc materialName, irr::u32 layerNum)
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
    irr::video::SMaterialLayer* CLSL::_getMaterialLayerValue(irr::IrrlichtDevice* device, 
        irr::core::stringc varName)
    {
        irr::core::vector3df vec;
        lsl::AMLParms aparms;
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
        

        result->TextureWrap = (irr::video::E_TEXTURE_CLAMP) _getIntegerValue("clampmode");

        irr::core::stringc texture = this->_getStringValue("texture");
        if(texture.size())
            result->Texture = videoDriver->getTexture(texture);

        result->BilinearFilter = _getBoolValue("bilinear");
        result->TrilinearFilter = _getBoolValue("trilinear");
        result->AnisotropicFilter = _getBoolValue("anisotropic");

        result->setTextureMatrix(_getMatrixValue("transform"));

        // transform matrix overrides
        irr::core::vector2df scale, offset, center, rotation;
        
        if(!_getVector2dfValue("scale", scale))
        {
            scale.X = 1.f;
            scale.Y = 1.f;
        }

        if(!_getVector2dfValue("offset", offset))
        {
            vec = result->getTextureMatrix().getTranslation();
            offset.X = vec.X;
            offset.Y = vec.Y;
        }

        if(!_getVector2dfValue("center", center))
        {
            center.X = 0.0;
            center.Y = 0.0;
        }

        if(!_getVector2dfValue("rotation", rotation))
        {
            vec = result->getTextureMatrix().getRotationDegrees();
            rotation.X = vec.X;
        }

        if(_getVector2dfValue("ascroll", aparms.scroll))
            hasAnim = true;

        if(_getVector2dfValue("ascale", aparms.scale))
            hasAnim = true;

        if(_getFloatValue("arotation", aparms.rotation))
            hasAnim = true;

        if(_getVector2dfValue("acenter", aparms.center))
            hasAnim = true;

        if(hasAnim)
        {
            if(!m_emptyNode)
            {
                m_emptyNode = sceneManager->addEmptySceneNode(0, 0);
                m_emptyNode->setName("_emptyISL_");
                m_animator = new lsl::CSceneNodeAnimatorMaterialLayer();
                m_emptyNode->addAnimator(m_animator);
            }
            aparms.cscale = scale;
            lsl::AMLParms* pparms = new lsl::AMLParms(aparms);
            pdata->userData = pparms;
        }

        irr::core::matrix4 tmat;
        tmat.buildTextureTransform(rotation.X * irr::core::DEGTORAD, center, offset, scale);
        result->setTextureMatrix(tmat);

        m_layDefs[varName] = pdata;

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t M a t e r i a l
    //-------------------------------------------------------------------------
    irr::video::SMaterial* CLSL::_getMaterialValue(irr::IrrlichtDevice* device, 
        irr::core::stringc varName)
    {
        irr::core::stringc scopedLayerName;

        SYMDATA* pdata;

        SYMMAP::Node* node = m_matDefs.find(varName);
        if(node)
        {
            pdata = node->getValue();
            if(pdata->type == stMaterialLayer)
                return (irr::video::SMaterial*) pdata->typeData;
            return 0;
        }

        irr::video::SMaterial* result = new irr::video::SMaterial();
        pdata = new SYMDATA();
        pdata->type = stMaterial;
        pdata->typeData = result;

        result->MaterialType = (irr::video::E_MATERIAL_TYPE) _getIntegerValue("type");
        result->AmbientColor = _getColorValue("ambient");
        result->DiffuseColor = _getColorValue("diffuse");
        result->EmissiveColor = _getColorValue("emissive");
        result->SpecularColor = _getColorValue("specular");
        _getFloatValue("shininess", result->Shininess);
        _getFloatValue("parm1", result->MaterialTypeParam);
        _getFloatValue("parm2", result->MaterialTypeParam2);
        _getFloatValue("thickness", result->Thickness );
        result->GouraudShading = _getBoolValue("gouraud");
        result->Lighting = _getBoolValue("lighting");
        result->ZWriteEnable = _getBoolValue("zwriteenable");
        result->BackfaceCulling = _getBoolValue("backfaceculling");
        result->FrontfaceCulling = _getBoolValue("frontfaceculling");
        result->FogEnable = _getBoolValue("fogenabled");
        result->NormalizeNormals = _getBoolValue("normalizenormals");
        result->ZBuffer = _getIntegerValue("zbuffer");

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
            if(layer = _getMaterialLayerValue(device, scopedLayerName))
                result->TextureLayer[0] = *layer;
        }
        lua_pop(L, 1);

        lua_pushstring(L, "layer2");
        lua_gettable(L, -2);
        if(lua_type(L, lua_gettop(L)) == LUA_TTABLE)
        {
            scopedLayerName = varName;
            scopedLayerName += ".layer2";
            if(layer = _getMaterialLayerValue(device, scopedLayerName))
                result->TextureLayer[1] = *layer;
        }
        lua_pop(L, 1);

        lua_pushstring(L, "layer3");
        lua_gettable(L, -2);
        if(lua_type(L, lua_gettop(L)) == LUA_TTABLE)
        {
            scopedLayerName = varName;
            scopedLayerName += ".layer3";
            if(layer = _getMaterialLayerValue(device, scopedLayerName))
                result->TextureLayer[2] = *layer;
        }
        lua_pop(L, 1);

        lua_pushstring(L, "layer4");
        lua_gettable(L, -2);
        if(lua_type(L, lua_gettop(L)) == LUA_TTABLE)
        {
            scopedLayerName = varName;
            scopedLayerName += ".layer4";
            if(layer = _getMaterialLayerValue(device, scopedLayerName))
                result->TextureLayer[3] = *layer;
        }
        lua_pop(L, 1);

        m_matDefs[varName] = pdata;

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
    void CLSL::addAnimationRef(irr::core::stringc materialName, irr::video::SMaterial& ref)
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
            (lsl::AMLParms*)pdata->userData);

        pdata = _getLayerData(materialName, 2);
        if(pdata && pdata->userData)
            m_animator->addMaterialRef(materialName + ".layer2", ref.TextureLayer[0], 
            (lsl::AMLParms*)pdata->userData);

        pdata = _getLayerData(materialName, 3);
        if(pdata && pdata->userData)
            m_animator->addMaterialRef(materialName + ".layer3", ref.TextureLayer[0], 
            (lsl::AMLParms*)pdata->userData);

        pdata = _getLayerData(materialName, 4);
        if(pdata && pdata->userData)
            m_animator->addMaterialRef(materialName + ".layer4", ref.TextureLayer[0], 
            (lsl::AMLParms*)pdata->userData);
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
        irr::video::SMaterial* pmat=&m_defMaterial;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return m_defMaterial;

        if(value->tt == LUA_TTABLE)
        {
            pmat = _getMaterialValue(device, varName);
        }

        lua_pop(L, 1);
        return *pmat;
    }

    //-------------------------------------------------------------------------
    //                     g e t M a t e r i a l L a y e r      
    //-------------------------------------------------------------------------
    const irr::video::SMaterialLayer& CLSL::getMaterialLayer(irr::IrrlichtDevice* device, 
        const irr::core::stringc varName)
    {
        irr::video::SMaterialLayer* pmatlayer = &m_defMaterialLayer;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return m_defMaterialLayer;

        if(value->tt == LUA_TTABLE)
        {
            pmatlayer = _getMaterialLayerValue(device, varName);
        }

        lua_pop(L, 1);
        return *pmatlayer;
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
        irr::core::matrix4& result=irr::core::matrix4();

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
    const irr::video::SColor& CLSL::getColor(const irr::core::stringc varName,
        irr::video::SColor defValue)
    {
        irr::video::SColor& result=defValue;

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
    irr::core::vector2di CLSL::getVector2di(const irr::core::stringc varName,
        const irr::core::vector2di defValue)
    {
        irr::core::vector2di result=defValue;
        irr::core::vector3df temp;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        if(value->tt == LUA_TTABLE)
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
    irr::core::vector3df CLSL::getVector3df(const irr::core::stringc varName,
        const irr::core::vector3df& defValue)
    {
        irr::core::vector3df result=defValue;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        if(value->tt == LUA_TTABLE)
        {
            result = _getVector3dfValue();
        }

        lua_pop(L, 1);
        return result;
    }

    //-------------------------------------------------------------------------
    //                           g e t R e c t s 3 2
    //-------------------------------------------------------------------------
    irr::core::rect<irr::s32> CLSL::getRects32(const irr::core::stringc varName,
        const irr::core::rect<irr::s32> defValue)
    {
        irr::core::rect<irr::s32> result=defValue;
        irr::core::rect<irr::f32> temp;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        if(value->tt == LUA_TTABLE)
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
    irr::core::dimension2di CLSL::getDimension2di(const irr::core::stringc varName, 
        const irr::core::dimension2di defValue)
    {
        irr::core::dimension2di result=defValue;
        irr::core::vector3df temp;

        TValue* value = (TValue*)_pushValue(varName);
        if(!value)
            return result;

        if(value->tt == LUA_TTABLE)
        {
            temp = _getVector3dfValue();
            result.Width = (irr::s32) temp.X;
            result.Height = (irr::s32) temp.Y;

        }

        lua_pop(L, 1);
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
        _openLuaLibs();
        //luaL_openlibs(L);  
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
        {
            lua_getglobal(L, "_G");
            _dumpTable();
            lua_pop(L, 1);
        }

        //_dumpStack();

        return result;
    }

}