//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __TRAYRESULT_H_
#define __TRAYRESULT_H_

namespace Tubras
{
    typedef btCollisionWorld::ClosestRayResultCallback TBTRayCallback;

    class TRayResult 
    {
        friend class TPhysicsManager;

    protected:
        bool                m_hasHit;
        TReal               m_closestHitFraction;
        btCollisionObject*  m_bulletCollisionObject;
        TPhysicsObject*     m_collisionObject;
        TVector3            m_hitNormalWorld;
        TVector3            m_hitPointWorld;

        TRayResult();
        TRayResult(TBTRayCallback& callback);

    public:
        virtual ~TRayResult();

        bool hasHit() {return m_hasHit;}
        TPhysicsObject*     getCollisionObject() {return m_collisionObject;}
        btCollisionObject*  getBulletCollisionObject() {return m_bulletCollisionObject;}
        TVector3 getHitNormalWorld() {return m_hitNormalWorld;}
        TVector3 getHitPointWorld() {return m_hitPointWorld;}
    };

}

#endif
