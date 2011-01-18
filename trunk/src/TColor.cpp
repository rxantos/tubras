//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {

    const TColor TColor::White(255,255,255,255);
    const TColor TColor::Black(0,0,0,255);
    const TColor TColor::Gray(128,128,128,255);
    const TColor TColor::Red(255,0,0,255);
    const TColor TColor::Green(0,255,0,255);
    const TColor TColor::Blue(0,0,255,255);
    const TColor TColor::Transparent(0,0,0,0);


    //-----------------------------------------------------------------------
    //                            T C o l o u r
    //-----------------------------------------------------------------------
    TColor::TColor() : SColor(255,255,255,255)
    {
    }

    LColor::LColor(TColor& other)
    {
        m_ptr = new TColor(other);
    }

    LColor::LColor(lua_State* L)
    {
        u32 r=0, g=0, b=0, a=255;
        int top = lua_gettop(L);

        if(top > 0)
            r = (u32)lua_tonumber(L, 1);
        if(top > 1)
            g = (u32)lua_tonumber(L, 2);
        if(top > 2)
            b = (u32)lua_tonumber(L, 3);
        if(top > 3)
            a = (u32)lua_tonumber(L, 4);

        m_ptr = new TColor(r, g, b, a);
    }

    //-------------------------------------------------------------------
    //                       g e t P r o p e r t y
    //-------------------------------------------------------------------
    int LColor::getProperty(lua_State* L, const char* propName)
    {
        int result = 1;
        if(!strcmp(propName, "r"))
            lua_pushnumber(L, m_ptr->getRed());
        else if(!strcmp(propName, "g"))
            lua_pushnumber(L, m_ptr->getGreen());
        else if(!strcmp(propName, "b"))
            lua_pushnumber(L, m_ptr->getBlue());
        else if(!strcmp(propName, "a"))
            lua_pushnumber(L, m_ptr->getAlpha());
        else
            result = 0;

        return result;
    }

    //-------------------------------------------------------------------
    //                       s e t P r o p e r t y
    //-------------------------------------------------------------------
    int LColor::setProperty(lua_State* L, const char* propName, const TValue* propValue)
    {
        int result = 1;
        if(!strcmp(propName, "r"))
            m_ptr->setRed((u32)propValue->value.n);
        else if(!strcmp(propName, "g"))
            m_ptr->setGreen((u32)propValue->value.n);
        else if(!strcmp(propName, "b"))
            m_ptr->setBlue((u32)propValue->value.n);
        else if(!strcmp(propName, "a"))
            m_ptr->setAlpha((u32)propValue->value.n);
        else
            result = 0;

        return result;
    }

    //-------------------------------------------------------------------
    //                      _ _ t o s t r i n g
    //-------------------------------------------------------------------
    int LColor::__tostring(lua_State* L)
    {
        char result[64];
        if(lua_gettop(L) > 1)
            sprintf(result, "TColor: 0x%p (%d, %d, %d, %d )", this,
                m_ptr->getRed(), m_ptr->getGreen(), m_ptr->getBlue(),
                m_ptr->getAlpha());
        else
            sprintf(result, "TColor: (%d, %d, %d, %d)",
                m_ptr->getRed(), m_ptr->getGreen(), m_ptr->getBlue(),
                m_ptr->getAlpha());
        lua_pushstring(L, result);
        return 1;
    }

    //-------------------------------------------------------------------
    //                           _ _ m a t h
    //-------------------------------------------------------------------
    int LColor::__math(lua_State* L, const TValue* ovalue, 
        LProxyBase<TColor>* other, LPMathOp op)
    {
        TColor result;

        if(other)
        {
            switch(op)
            {
            case oAdd: result = *m_ptr + *other->m_ptr; break;
            case oSub: result = *m_ptr - *other->m_ptr; break;
            //case oMul: result = *m_ptr * *other->m_ptr; break;
            //case oDiv: result = *m_ptr / *other->m_ptr; break;
            //case oNeg: result = *m_ptr * -1.f;
            };
        }
        else if(ovalue->tt == LUA_TNUMBER)
        {
            switch(op)
            {
            case oAdd: result = *m_ptr + (u32)ovalue->value.n; break;
            case oSub: result = *m_ptr - (u32)ovalue->value.n; break;
            //case oMul: result = *m_ptr * (u32)ovalue->value.n; break;
            //case oDiv: result = *m_ptr / (u32)ovalue->value.n; break;
            //case oNeg: result = *m_ptr * -1.f;
            };
        }
        else
        {
            getApplication()->logMessage(LOG_WARNING, "Ignoring non-scalar math on TVector3");
            result = *m_ptr;
        }

        push_to_lua<LColor>(L, new LColor(result));
        return 1;
    }

    //-------------------------------------------------------------------
    //                        _ _ c o m p a r e
    //-------------------------------------------------------------------
    int LColor::__compare(lua_State* L, LProxyBase<TColor>* other, LPCompareOp op)
    {
        bool result=false;

        switch(op)
        {
        case oEQ: result = *m_ptr == *other->m_ptr; break;
        case oLT: result = *m_ptr < *other->m_ptr; break;
        case oLE: result = (*m_ptr == *other->m_ptr) | (*m_ptr < *other->m_ptr); break;
        };

        lua_pushboolean(L, result);
        return 1;
    }


    template<> const char LProxyBase<TColor>::className[] = "TColor";
    const TLuaProxy<LColor>::RegType LColor::Register[] = {
        { "getLightness", &LColor::getLightness },
        { "getLuminance", &LColor::getLuminance },
        { "getLightness", &LColor::getAverage },
        { 0 }};

}
