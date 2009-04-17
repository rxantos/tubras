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
    //                       T R a y R e s u l t
    //-----------------------------------------------------------------------
    TRayResult::TRayResult(TBTRayCallback& callback) 
    {
        m_hasHit = callback.hasHit();
        if(m_hasHit)
        {
            m_collisionObject = callback.m_collisionObject;
            m_collisionNode = (TDynamicNode*) m_collisionObject->getUserPointer();
            m_closestHitFraction = callback.m_closestHitFraction;
            m_hitNormalWorld.set(callback.m_hitNormalWorld[0], callback.m_hitNormalWorld[1], callback.m_hitNormalWorld[2]);
            m_hitPointWorld.set(callback.m_hitPointWorld[0], callback.m_hitPointWorld[1], callback.m_hitPointWorld[2]);
        }
        else
        {
            m_closestHitFraction = 0.f;
            m_hitNormalWorld = TVector3::ZERO;
            m_hitPointWorld = TVector3::ZERO;
            m_collisionObject = 0;
            m_collisionNode = 0;
        }
    }

    //-----------------------------------------------------------------------
    //                      ~ T R a y R e s u l t
    //-----------------------------------------------------------------------
    TRayResult::~TRayResult()
    {
    }
}

