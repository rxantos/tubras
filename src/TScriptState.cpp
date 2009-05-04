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
    //-----------------------------------------------------------------------
    //                            T S t a t e
    //-----------------------------------------------------------------------
    TScriptState::TScriptState(const TString& name, lua_State* L, int ref_init, 
        int ref_enter,  int ref_exit, int ref_pause, int ref_resume, int ref_reset) : TState(name),
        m_lua(L),
        m_rInit(ref_init),
        m_rEnter(ref_enter),
        m_rExit(ref_exit),
        m_rPause(ref_pause),
        m_rResume(ref_resume),
        m_rReset(ref_reset)       
    {
    }

    //-----------------------------------------------------------------------
    //                            ~T S t a t e
    //-----------------------------------------------------------------------
    TScriptState::~TScriptState()
    {
    }

    //-----------------------------------------------------------------------
    //                       c a l l S t a t e F u n c
    //-----------------------------------------------------------------------
    int TScriptState::callStateFunc(int ref)
    {
        int result=0;

        if(ref <= 0)
            return 0;

        lua_rawgeti(m_lua, LUA_REGISTRYINDEX, ref);
        if(lua_type(m_lua,-1) != LUA_TFUNCTION)
            return 0;

        // call the function
        if (lua_pcall(m_lua, 0, 1, 0) != 0)
        {
            getApplication()->logMessage(LOG_ERROR, "Error calling function TScriptState:: %d %s",
                ref, lua_tostring(m_lua, -1));
            return 1;
        }

        if(lua_isnumber(m_lua, -1))
        {
            result = lua_tointeger(m_lua, -1);
        }

        lua_pop(m_lua, 1);  

        return result;
    }


    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TScriptState::initialize()
    {
        int result;

        result = TState::initialize();

        return callStateFunc(m_rInit);

    }

    //-----------------------------------------------------------------------
    //                              E n t e r
    //-----------------------------------------------------------------------
    int TScriptState::Enter()
    {
        return callStateFunc(m_rEnter);
    }

    //-----------------------------------------------------------------------
    //                               E x i t
    //-----------------------------------------------------------------------
    TStateInfo* TScriptState::Exit()
    {
        callStateFunc(m_rExit);
        return &m_info;
    }

    //-----------------------------------------------------------------------
    //                              R e s e t
    //-----------------------------------------------------------------------
    int TScriptState::Reset()
    {
        return callStateFunc(m_rReset);;
    }

    //-----------------------------------------------------------------------
    //                              P a u s e 
    //-----------------------------------------------------------------------
    int TScriptState::Pause()
    {
        return callStateFunc(m_rPause);;
    }

    //-----------------------------------------------------------------------
    //                              R e s u m e
    //-----------------------------------------------------------------------
    int TScriptState::Resume(TStateInfo* prevStateInfo)
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                       c h a n g e S t a t e
    //-----------------------------------------------------------------------
    int TScriptState::changeState(const TString& stateName)
    {
        return m_app->changeState(stateName);
    }

    //-----------------------------------------------------------------------
    //                         p u s h S t a t e
    //-----------------------------------------------------------------------
    int TScriptState::pushState(const TString& stateName)
    {
        return m_app->pushState(stateName);
    }

    //-----------------------------------------------------------------------
    //                          p o p S t a t e
    //-----------------------------------------------------------------------
    int TScriptState::popState()
    {
        return m_app->popState();
    }


}
