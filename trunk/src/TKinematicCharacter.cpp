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
    //                   T K i n e m a t i c C h a r a c t e r
    //-----------------------------------------------------------------------
    TKinematicCharacter::TKinematicCharacter(btPairCachingGhostObject* ghostObject,
        btConvexShape* convexShape,btScalar stepHeight, int upAxis) : btKinematicCharacterController(
        ghostObject, convexShape, stepHeight, upAxis),
        m_jumping(false)
    {

    }

    //-----------------------------------------------------------------------
    //                  ~ T K i n e m a t i c C h a r a c t e r
    //-----------------------------------------------------------------------
    TKinematicCharacter::~TKinematicCharacter()
    {
    }

    //-----------------------------------------------------------------------
    //                         u p d a t e A c t i o n
    //-----------------------------------------------------------------------
    void TKinematicCharacter::updateAction( btCollisionWorld* collisionWorld,btScalar deltaTime)
	{
		preStep ( collisionWorld);
		playerStep (collisionWorld, deltaTime);
	}

    //-----------------------------------------------------------------------
    //                r e c o v e r F r o m P e n e t r a t i o n
    //-----------------------------------------------------------------------
    bool TKinematicCharacter::recoverFromPenetration ( btCollisionWorld* collisionWorld)
    {
        return btKinematicCharacterController::recoverFromPenetration(collisionWorld);
    }

    //-----------------------------------------------------------------------
    //                              s t e p U p
    //-----------------------------------------------------------------------
	void TKinematicCharacter::stepUp (btCollisionWorld* collisionWorld)
    {
        btKinematicCharacterController::stepUp(collisionWorld);
    }

    //-----------------------------------------------------------------------
    //                   updateTargetPositionBasedOnCollision
    //-----------------------------------------------------------------------
	void TKinematicCharacter::updateTargetPositionBasedOnCollision (const btVector3& hit_normal, 
        btScalar tangentMag, btScalar normalMag)
    {
        btKinematicCharacterController::updateTargetPositionBasedOnCollision(hit_normal,
            tangentMag, normalMag);
    }

    //-----------------------------------------------------------------------
    //                 s t e p F o r w a r d A n d S t r a f e
    //-----------------------------------------------------------------------
	void TKinematicCharacter::stepForwardAndStrafe (btCollisionWorld* collisionWorld, const btVector3& walkMove)
    {
        btKinematicCharacterController::stepForwardAndStrafe(collisionWorld, walkMove);
    }

    //-----------------------------------------------------------------------
    //                           s t e p D o w n
    //-----------------------------------------------------------------------
	void TKinematicCharacter::stepDown (btCollisionWorld* collisionWorld, btScalar dt)
    {
        btKinematicCharacterController::stepDown(collisionWorld, dt);
    }	

    //-----------------------------------------------------------------------
    //                            p r e S t e p
    //-----------------------------------------------------------------------
    void TKinematicCharacter::preStep (  btCollisionWorld* collisionWorld)
    {
        btKinematicCharacterController::preStep(collisionWorld);
    }

    //-----------------------------------------------------------------------
    //                         p l a y e r S t e p
    //-----------------------------------------------------------------------
	void TKinematicCharacter::playerStep ( btCollisionWorld* collisionWorld, btScalar dt)
    {
        // btKinematicCharacterController::playerStep(collisionWorld, dt);

        btTransform xform;
        xform = m_ghostObject->getWorldTransform ();

        stepUp (collisionWorld);
        stepForwardAndStrafe (collisionWorld, m_walkDirection);
        stepDown (collisionWorld, dt);

        xform.setOrigin (m_currentPosition);
        m_ghostObject->setWorldTransform (xform);

    }

}
