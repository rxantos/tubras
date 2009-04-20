//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TRAYRESULT_H_
#define __TRAYRESULT_H_

namespace Tubras
{
    typedef btCollisionWorld::ClosestRayResultCallback TBTRayCallback;

    class TRayResult 
    {
        friend class TDynamicWorld;

    protected:
        bool                m_hasHit;
        TReal               m_closestHitFraction;
        btCollisionObject*  m_bulletCollisionObject;
        TPhysicsObject*     m_collisionObject;
        TVector3            m_hitNormalWorld;
        TVector3            m_hitPointWorld;
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
