//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {

    const TVector3 TVector3::ZERO( 0, 0, 0 );

    const TVector3 TVector3::UNIT_X( 1, 0, 0 );
    const TVector3 TVector3::UNIT_Y( 0, 1, 0 );
    const TVector3 TVector3::UNIT_Z( 0, 0, 1 );
    const TVector3 TVector3::NEGATIVE_UNIT_X( -1,  0,  0 );
    const TVector3 TVector3::NEGATIVE_UNIT_Y(  0, -1,  0 );
    const TVector3 TVector3::NEGATIVE_UNIT_Z(  0,  0, -1 );
    const TVector3 TVector3::UNIT_SCALE(1, 1, 1);

    //-----------------------------------------------------------------------
    //                           T V e c t o r 3
    //-----------------------------------------------------------------------
    TVector3 TVector3::toRadians() 
    {
        return TVector3(DegreesToRadians(X),
            DegreesToRadians(Y),DegreesToRadians(Z));
    }

    TVector3 TVector3::toDegrees() 
    {
        return TVector3(RadiansToDegrees(X),
            RadiansToDegrees(Y),RadiansToDegrees(Z));
    }

    //-------------------------------------------------------------------
    //                          L V e c t o r 3
    //-------------------------------------------------------------------
    LVector3::LVector3(TVector3& other)
    {
        m_ptr = new TVector3(other);
    }

    LVector3::LVector3(lua_State* L)
    {
        f32 x=0.f, y=0.f, z=0.f;
        int top = lua_gettop(L);

        if(top > 0)
            x = (f32)lua_tonumber(L, 1);
        if(top > 1)
            y = (f32)lua_tonumber(L, 2);
        if(top > 2)
            z = (f32)lua_tonumber(L, 3);

        m_ptr = new TVector3(x, y , z);
    }

    //-------------------------------------------------------------------
    //                       g e t P r o p e r t y
    //-------------------------------------------------------------------
    int LVector3::getProperty(lua_State* L, const char* propName)
    {
        int result = 1;
        if(!strcmp(propName, "x"))
            lua_pushnumber(L, m_ptr->X);
        else if(!strcmp(propName, "y"))
            lua_pushnumber(L, m_ptr->Y);
        else if(!strcmp(propName, "z"))
            lua_pushnumber(L, m_ptr->Z);
        else
            result = 0;

        return result;
    }

    //-------------------------------------------------------------------
    //                       s e t P r o p e r t y
    //-------------------------------------------------------------------
    int LVector3::setProperty(lua_State* L, const char* propName, const TValue* propValue)
    {
        int result = 1;
        if(!strcmp(propName, "x"))
            m_ptr->X = (f32)propValue->value.n;
        else if(!strcmp(propName, "y"))
            m_ptr->Y = (f32)propValue->value.n;
        else if(!strcmp(propName, "z"))
            m_ptr->Z = (f32)propValue->value.n;
        else
            result = 0;

        return result;
    }

    //-------------------------------------------------------------------
    //                      _ _ t o s t r i n g
    //-------------------------------------------------------------------
    int LVector3::__tostring(lua_State* L)
    {
        char result[64];
        sprintf(result, "TVector3: 0x%x {%.2f, %.2f, %.2f}", this,
            m_ptr->X, m_ptr->Y, m_ptr->Z);
        lua_pushstring(L, result);
        return 1;
    }

    //-------------------------------------------------------------------
    //                           _ _ m a t h
    //-------------------------------------------------------------------
    int LVector3::__math(lua_State* L, const TValue* ovalue, 
        LProxyBase<TVector3>* other, LPMathOp op)
    {
        TVector3 result;

        if(other)
        {
            switch(op)
            {
            case oAdd: result = *m_ptr + *other->m_ptr; break;
            case oSub: result = *m_ptr - *other->m_ptr; break;
            case oMul: result = *m_ptr * *other->m_ptr; break;
            case oDiv: result = *m_ptr / *other->m_ptr; break;
            case oNeg: result = *m_ptr * -1.f;
            };
        }
        else if(ovalue->tt == LUA_TNUMBER)
        {
            switch(op)
            {
            case oAdd: result = *m_ptr + (f32)ovalue->value.n; break;
            case oSub: result = *m_ptr - (f32)ovalue->value.n; break;
            case oMul: result = *m_ptr * (f32)ovalue->value.n; break;
            case oDiv: result = *m_ptr / (f32)ovalue->value.n; break;
            case oNeg: result = *m_ptr * -1.f;
            };
        }
        else
        {
            getApplication()->logMessage(LOG_WARNING, "Ignoring non-scalar math to TVector3");
            result = *m_ptr;
        }

        push_to_lua(L, new LVector3(result));
        return 1;
    }

    const char LVector3::className[] = "TVector3";
    const TLuaProxy<LVector3>::RegType LVector3::Register[] = {
        { "normalize", &LVector3::normalize },
        { 0 }};
}

