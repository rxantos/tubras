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
    //                    T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::TPhysicsManager() : TDelegate(),
        m_playerController(0)
    {
        m_mode = pmNone;
        m_world = NULL;
        //m_debugOverlay = NULL;
        m_userDebugString = "";
    }

    //-----------------------------------------------------------------------
    //                   ~ T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::~TPhysicsManager()
    {
        if(m_world)
            delete m_world;
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TPhysicsManager::initialize()
    {
        m_world = new TDynamicWorld();

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    s e t U s e r D e b u g S t r i n g
    //-----------------------------------------------------------------------
    void TPhysicsManager::setUserDebugString(const TString& value)
    {
        m_userDebugString = value;
    }

    //-----------------------------------------------------------------------
    //                              u p d a t e
    //-----------------------------------------------------------------------
    void TPhysicsManager::update(const u32 deltaTime)
    {
        m_world->update(deltaTime);
        if(m_playerController)
            m_playerController->updatePlayer();
    }
}

