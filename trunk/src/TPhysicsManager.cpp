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
        m_playerController(0),
        m_timer(0),
        m_irrCollision(0)
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
        if(m_irrWorld)
            m_irrWorld->drop();
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TPhysicsManager::initialize()
    {
        m_timer = getApplication()->getGlobalClock();
        m_world = new TDynamicWorld();
        m_world->initialize();

        m_csType = cstBullet;

        TString csType = getApplication()->getConfig()->getString("physics.collisionSystem","Bullet");
        if(csType.equals_ignore_case("irrlicht"))
        {
            m_csType = cstIrrlicht;
            m_irrWorld = getApplication()->getSceneManager()->createMetaTriangleSelector();

            m_irrCollision = getApplication()->getSceneManager()->createCollisionResponseAnimator(m_irrWorld, 0);
            float width = getApplication()->getConfig()->getFloat("physics.characterWidth", 1.f);
            float height = getApplication()->getConfig()->getFloat("physics.characterHeight", 2.f);

            TVector3 radius(width,height,width);
            m_irrCollision->setEllipsoidRadius(radius);
            m_irrCollision->setGravity(vector3df(0.f, -0.1f, 0.f));
        }

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
    void TPhysicsManager::update(const f32 deltaTime)
    {
        if(m_irrCollision)
        {
            if(m_playerController->getMode() != pcmGod)
                m_irrCollision->animateNode(m_playerController->getCharacterSceneNode(),m_timer->getMilliSeconds());
            return;
        }
        else m_world->update(deltaTime);

    }
}

