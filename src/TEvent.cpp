//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                             T E v e n t
    //-----------------------------------------------------------------------
    TEvent::TEvent(const TString& name)
    {
        m_name = name;
        m_userData = NULL;
        m_id = getApplication()->getEventManager()->registerEvent(name);
    }

    //-----------------------------------------------------------------------
    //                             s e t N a m e
    //-----------------------------------------------------------------------
    u32 TEvent::setName(const TString &name)
    {
        m_name = name;
        m_id = getApplication()->getEventManager()->registerEvent(name);
        return m_id;
    }

    //-----------------------------------------------------------------------
    //                        g e t P a r a m e t e r
    //-----------------------------------------------------------------------
    TEventParameter* TEvent::getParameter(int n)
    {
        if((n < 0) || (n > (int)m_parameters.size()))
        {
            return 0;
        }

        return m_parameters[n];
    }

    //-------------------------------------------------------------------
    //                          L E v e n t
    //-------------------------------------------------------------------
    LEvent::LEvent(const TEvent* other)
    {
        m_ptr = (TEvent *)other;
    }

    LEvent::LEvent(lua_State* L)
    {
        f32 x=0.f, y=0.f, z=0.f;
        int top = lua_gettop(L);

        if(top > 0)
            x = (f32)lua_tonumber(L, 1);
        if(top > 1)
            y = (f32)lua_tonumber(L, 2);
        if(top > 2)
            z = (f32)lua_tonumber(L, 3);

        m_ptr = new TEvent();
    }

    LEvent::~LEvent()
    {
        if(m_ptr)
            printf("m_ptr: %p\n", m_ptr);

    }

    //-------------------------------------------------------------------
    //                       g e t P r o p e r t y
    //-------------------------------------------------------------------
    int LEvent::getProperty(lua_State* L, const char* propName)
    {
        int result = 1;
        if(!strcmp(propName, "id"))
            lua_pushnumber(L, m_ptr->getID());
        else
            result = 0;

        return result;
    }


    template<> const char LProxyBase<TEvent>::className[] = "TEvent";
    const TLuaProxy<LEvent>::RegType LEvent::Register[] = {
        { 0 }};

}
