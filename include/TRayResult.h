//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
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
        btCollisionObject*  m_collisionObject;
        TDynamicNode*       m_collisionNode;
        TVector3            m_hitNormalWorld;
        TVector3            m_hitPointWorld;
        TRayResult(TBTRayCallback& callback);

    public:
        virtual ~TRayResult();

        bool hasHit() {return m_hasHit;}
        TDynamicNode*       getCollisionNode() {return m_collisionNode;}
        btCollisionObject*  getCollisionObject() {return m_collisionObject;}
        TVector3 getHitNormalWorld() {return m_hitNormalWorld;}
        TVector3 getHitPointWorld() {return m_hitPointWorld;}
    };

}

#endif
