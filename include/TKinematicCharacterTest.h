//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TKINEMATICCHARACTERTEST_H_
#define _TKINEMATICCHARACTERTEST_H_

namespace Tubras
{

    class TKinematicCharacterTest : public btKinematicCharacterController
    {
    protected:
        bool                m_jumping;
    protected:
        virtual bool recoverFromPenetration ( btCollisionWorld* collisionWorld);
        virtual void stepUp (btCollisionWorld* collisionWorld);
        virtual void updateTargetPositionBasedOnCollision (const btVector3& hit_normal, btScalar tangentMag = btScalar(0.0), btScalar normalMag = btScalar(1.0));
        virtual void stepForwardAndStrafe (btCollisionWorld* collisionWorld, const btVector3& walkMove);
        virtual void stepDown (btCollisionWorld* collisionWorld, btScalar dt);

    public:
        TKinematicCharacterTest(btPairCachingGhostObject* ghostObject,btConvexShape* convexShape,btScalar stepHeight, int upAxis = 1);
        virtual ~TKinematicCharacterTest();
        virtual void updateAction( btCollisionWorld* collisionWorld,btScalar deltaTime);
        void preStep (  btCollisionWorld* collisionWorld);
        void playerStep ( btCollisionWorld* collisionWorld, btScalar dt);
    };

}

#endif

