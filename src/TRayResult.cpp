//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T R a y R e s u l t
    //-----------------------------------------------------------------------
    TRayResult::TRayResult() 
    {
        m_closestHitFraction = 0.f;
        m_hitNormalWorld = TVector3_ZERO;
        m_hitPointWorld = TVector3_ZERO;
        m_bulletCollisionObject = 0;
        m_collisionObject = 0;
    }

    TRayResult::TRayResult(TBTRayCallback& callback) 
    {
        m_hasHit = callback.hasHit();
        if(m_hasHit)
        {
            m_bulletCollisionObject = callback.m_collisionObject;
            m_collisionObject = (TPhysicsObject*) m_bulletCollisionObject->getUserPointer();
            m_closestHitFraction = callback.m_closestHitFraction;
            m_hitNormalWorld.set(callback.m_hitNormalWorld[0], callback.m_hitNormalWorld[1], callback.m_hitNormalWorld[2]);
            m_hitPointWorld.set(callback.m_hitPointWorld[0], callback.m_hitPointWorld[1], callback.m_hitPointWorld[2]);
        }
        else
        {
            m_closestHitFraction = 0.f;
            m_hitNormalWorld = TVector3_ZERO;
            m_hitPointWorld = TVector3_ZERO;
            m_bulletCollisionObject = 0;
            m_collisionObject = 0;
        }
    }

    //-----------------------------------------------------------------------
    //                      ~ T R a y R e s u l t
    //-----------------------------------------------------------------------
    TRayResult::~TRayResult()
    {
    }
}

