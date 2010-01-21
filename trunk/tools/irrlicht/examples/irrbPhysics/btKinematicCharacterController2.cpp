/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2008 Erwin Coumans  http://bulletphysics.com

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/


#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "LinearMath/btIDebugDraw.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletCollision/CollisionShapes/btMultiSphereShape.h"
#include "BulletCollision/BroadphaseCollision/btOverlappingPairCache.h"
#include "BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"
#include "LinearMath/btDefaultMotionState.h"
#include "btKinematicCharacterController2.h"
#include "main.h" // temp incl for debug functions

static btVector3 upAxisDirection[3] = { btVector3(1.0f, 0.0f, 0.0f), btVector3(0.0f, 1.0f, 0.0f), btVector3(0.0f, 0.0f, 1.0f) };
static unsigned int didx=0;
static unsigned int mdidx=0;

// static helper method
static btVector3
getNormalizedVector(const btVector3& v)
{
    btVector3 n = v.normalized();
    if (n.length() < SIMD_EPSILON) {
        n.setValue(0, 0, 0);
    }
    return n;
}


///@todo Interact with dynamic objects,
///Ride kinematicly animated platforms properly
///More realistic (or maybe just a config option) falling
/// -> Should integrate falling velocity manually and use that in stepDown()
///Support jumping
///Support ducking
class btKinematicClosestNotMeRayResultCallback : public btCollisionWorld::ClosestRayResultCallback
{
public:
    btKinematicClosestNotMeRayResultCallback (btCollisionObject* me) : btCollisionWorld::ClosestRayResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0))
    {
        m_me = me;
    }

    virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace)
    {
        if (rayResult.m_collisionObject == m_me)
            return 1.0;

        return ClosestRayResultCallback::addSingleResult (rayResult, normalInWorldSpace);
    }
protected:
    btCollisionObject* m_me;
};

class btKinematicClosestNotMeConvexResultCallback : public btCollisionWorld::ClosestConvexResultCallback
{
public:
    btKinematicClosestNotMeConvexResultCallback (btCollisionObject* me) : btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0))
    {
        m_me = me;
    }

    virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult,bool normalInWorldSpace)
    {
        if (convexResult.m_hitCollisionObject == m_me)
            return 1.0;

        return ClosestConvexResultCallback::addSingleResult (convexResult, normalInWorldSpace);
    }
protected:
    btCollisionObject* m_me;
};

/*
* Returns the reflection direction of a ray going 'direction' hitting a surface with normal 'normal'
*
* from: http://www-cs-students.stanford.edu/~adityagp/final/node3.html
*/
btVector3 btKinematicCharacterController2::computeReflectionDirection (const btVector3& direction, const btVector3& normal)
{
    return direction - (btScalar(2.0) * direction.dot(normal)) * normal;
}

/*
* Returns the portion of 'direction' that is parallel to 'normal'
*/
btVector3 btKinematicCharacterController2::parallelComponent (const btVector3& direction, const btVector3& normal)
{
    btScalar magnitude = direction.dot(normal);
    return normal * magnitude;
}

/*
* Returns the portion of 'direction' that is perpindicular to 'normal'
*/
btVector3 btKinematicCharacterController2::perpindicularComponent (const btVector3& direction, const btVector3& normal)
{
    return direction - parallelComponent(direction, normal);
}

btKinematicCharacterController2::btKinematicCharacterController2 (btPairCachingGhostObject* ghostObject,btConvexShape* convexShape,btScalar stepHeight, int upAxis)
{
    m_upAxis = upAxis;
    m_addedMargin = 0.02f;
    m_walkDirection.setValue(0,0,0);
    m_useGhostObjectSweepTest = true;
    m_ghostObject = ghostObject;
    m_stepHeight = stepHeight;
    m_turnAngle = btScalar(0.0);
    m_convexShape=convexShape;	
    m_useWalkDirection = true;	// use walk direction by default, legacy behavior
    m_velocityTimeInterval = 0.0;
}

btKinematicCharacterController2::~btKinematicCharacterController2 ()
{
}

btPairCachingGhostObject* btKinematicCharacterController2::getGhostObject()
{
    return m_ghostObject;
}

bool btKinematicCharacterController2::recoverFromPenetration ( btCollisionWorld* collisionWorld)
{

    bool penetration = false;
    didx = 0; // reset debug index

    // "actions" (::updateAction()) are executed at the end of Pipeline so at this point,
    // the ghost object "pair cache" contains Broadphase overlapping pairs (AABB). The 
    // Broadphase overlaps are calculated for each simulation step:
    //      internalSingleStepSimulation() ->
    //          preformDiscreteCollisionDetection() -> (collision world specific)
    //              updateAabbs() ->
    //                  (other aabb calls updateHandle(), sortMinUp()) ->
    //                      possible calls to m_ghostObject->add/removeOverlappingPair() 
    //
    // dispatchCollisionPairs() performs the Narrowphase calculations for generating contact point data 
    // on overlapping AABB pairs.
    //

    int totalAabbPairs = m_ghostObject->getOverlappingPairCache()->getNumOverlappingPairs();
    char buf[64];
    sprintf(buf, "Overlapping Aabb Count: %d", totalAabbPairs);  // the number of object aabb's that overlap with us
    _updateDebugText(didx++, buf);


    collisionWorld->getDispatcher()->dispatchAllCollisionPairs(m_ghostObject->getOverlappingPairCache(), collisionWorld->getDispatchInfo(), collisionWorld->getDispatcher());

    m_currentPosition = m_ghostObject->getWorldTransform().getOrigin();

    int mcount=0,cpcount=0;
    btScalar maxPen = btScalar(0.0);
    for (int i = 0; i < m_ghostObject->getOverlappingPairCache()->getNumOverlappingPairs(); i++)
    {
        m_manifoldArray.resize(0);

        btBroadphasePair* collisionPair = &m_ghostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];

        if (collisionPair->m_algorithm)
            collisionPair->m_algorithm->getAllContactManifolds(m_manifoldArray);

        mcount += m_manifoldArray.size();

        for (int j=0;j<m_manifoldArray.size();j++)
        {
            btPersistentManifold* manifold = m_manifoldArray[j];
            cpcount += manifold->getNumContacts();

            btScalar directionSign = manifold->getBody0() == m_ghostObject ? btScalar(-1.0) : btScalar(1.0);
            for (int p=0;p<manifold->getNumContacts();p++)
            {
                const btManifoldPoint&pt = manifold->getContactPoint(p);

                sprintf(buf, "CP%d Normal:(%.1f, %1.f, %1.f)", p+1, pt.m_normalWorldOnB[0],
                    pt.m_normalWorldOnB[1], pt.m_normalWorldOnB[2]);
                _updateDebugText(didx++, buf);

                sprintf(buf, "CP%d Dist: %.4f", p+1, pt.m_distance1);
                _updateDebugText(didx++, buf);

                if (pt.getDistance() < 0.0)
                {
                    if (pt.getDistance() < maxPen)
                    {
                        maxPen = pt.getDistance();
                        m_touchingNormal = pt.m_normalWorldOnB * directionSign;//??

                    }
                    m_currentPosition += pt.m_normalWorldOnB * directionSign * pt.getDistance() * btScalar(0.2);
                    penetration = true;
                } else {
                    //printf("touching %f\n", pt.getDistance());
                }
            }

            //manifold->clearManifold();
        }
    }

    sprintf(buf, "Contact Manifold Count: %d", mcount);
    _updateDebugText(didx++, buf);

    sprintf(buf, "Contact Point Count: %d", cpcount);
    _updateDebugText(didx++, buf);

    _updateDebugText(didx++, "");

    _updateDebugText(didx++, "Ghost->Aabb Overlaps:");
    for(int i=0; i<totalAabbPairs; i++)
    {
        btBroadphasePair& collisionPair = m_ghostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];
        btRigidBody* rbody = btRigidBody::upcast((btCollisionObject*)collisionPair.m_pProxy1->m_clientObject);
        if(rbody)
        {
            ISceneNode* node = (ISceneNode*) rbody->getUserPointer();
            sprintf(buf,"    %s", node->getName());
            _updateDebugText(didx++, buf);
        }
    }

    btTransform newTrans = m_ghostObject->getWorldTransform();
    newTrans.setOrigin(m_currentPosition);
    m_ghostObject->setWorldTransform(newTrans);
    //	printf("m_touchingNormal = %f,%f,%f\n",m_touchingNormal[0],m_touchingNormal[1],m_touchingNormal[2]);
    return penetration;
}

void btKinematicCharacterController2::stepUp ( btCollisionWorld* world)
{
    // phase 1: up

    btTransform start, end;
    m_targetPosition = m_currentPosition + upAxisDirection[m_upAxis] * m_stepHeight;

    start.setIdentity ();
    end.setIdentity ();

    /* FIXME: Handle penetration properly */
    start.setOrigin (m_currentPosition + upAxisDirection[m_upAxis] * btScalar(0.1f));
    end.setOrigin (m_targetPosition);

    btKinematicClosestNotMeConvexResultCallback callback (m_ghostObject);
    callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
    callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

    if (m_useGhostObjectSweepTest)
    {
        m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, world->getDispatchInfo().m_allowedCcdPenetration);
    }
    else
    {
        world->convexSweepTest (m_convexShape, start, end, callback);
    }

    if (callback.hasHit())
    {
        // we moved up only a fraction of the step height
        m_currentStepOffset = m_stepHeight * callback.m_closestHitFraction;
        m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);
    } else {
        m_currentStepOffset = m_stepHeight;
        m_currentPosition = m_targetPosition;
    }
}

void btKinematicCharacterController2::updateTargetPositionBasedOnCollision (const btVector3& hitNormal, btScalar tangentMag, btScalar normalMag)
{
    btVector3 movementDirection = m_targetPosition - m_currentPosition;
    btScalar movementLength = movementDirection.length();
    if (movementLength>SIMD_EPSILON)
    {
        movementDirection.normalize();

        btVector3 reflectDir = computeReflectionDirection (movementDirection, hitNormal);
        reflectDir.normalize();

        btVector3 parallelDir, perpindicularDir;

        parallelDir = parallelComponent (reflectDir, hitNormal);
        perpindicularDir = perpindicularComponent (reflectDir, hitNormal);

        m_targetPosition = m_currentPosition;
        if (0)//tangentMag != 0.0)
        {
            btVector3 parComponent = parallelDir * btScalar (tangentMag*movementLength);
            //			printf("parComponent=%f,%f,%f\n",parComponent[0],parComponent[1],parComponent[2]);
            m_targetPosition +=  parComponent;
        }

        if (normalMag != 0.0)
        {
            btVector3 perpComponent = perpindicularDir * btScalar (normalMag*movementLength);
            //			printf("perpComponent=%f,%f,%f\n",perpComponent[0],perpComponent[1],perpComponent[2]);
            m_targetPosition += perpComponent;
        }
    } else
    {
        //		printf("movementLength don't normalize a zero vector\n");
    }
}

void btKinematicCharacterController2::stepForwardAndStrafe ( btCollisionWorld* collisionWorld, const btVector3& walkMove)
{
    // printf("m_normalizedDirection=%f,%f,%f\n",
    // 	m_normalizedDirection[0],m_normalizedDirection[1],m_normalizedDirection[2]);
    // phase 2: forward and strafe
    btTransform start, end;
    m_targetPosition = m_currentPosition + walkMove;
    start.setIdentity ();
    end.setIdentity ();

    btScalar fraction = 1.0;
    btScalar distance2 = (m_currentPosition-m_targetPosition).length2();
    //	printf("distance2=%f\n",distance2);

    if (m_touchingContact)
    {
        if (m_normalizedDirection.dot(m_touchingNormal) > btScalar(0.0))
            updateTargetPositionBasedOnCollision (m_touchingNormal);
    }

    int maxIter = 10;

    while (fraction > btScalar(0.01) && maxIter-- > 0)
    {
        start.setOrigin (m_currentPosition);
        end.setOrigin (m_targetPosition);

        btKinematicClosestNotMeConvexResultCallback callback (m_ghostObject);
        callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
        callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;


        btScalar margin = m_convexShape->getMargin();
        m_convexShape->setMargin(margin + m_addedMargin);


        if (m_useGhostObjectSweepTest)
        {
            m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
        } else
        {
            collisionWorld->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
        }

        m_convexShape->setMargin(margin);


        fraction -= callback.m_closestHitFraction;

        if (callback.hasHit())
        {	
            // we moved only a fraction
            btScalar hitDistance = (callback.m_hitPointWorld - m_currentPosition).length();
            if (hitDistance<0.f)
            {
                //				printf("neg dist?\n");
            }

            /* If the distance is farther than the collision margin, move */
            if (hitDistance > m_addedMargin)
            {
                //				printf("callback.m_closestHitFraction=%f\n",callback.m_closestHitFraction);
                m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);
            }

            updateTargetPositionBasedOnCollision (callback.m_hitNormalWorld);
            btVector3 currentDir = m_targetPosition - m_currentPosition;
            distance2 = currentDir.length2();
            if (distance2 > SIMD_EPSILON)
            {
                currentDir.normalize();
                /* See Quake2: "If velocity is against original velocity, stop ead to avoid tiny oscilations in sloping corners." */
                if (currentDir.dot(m_normalizedDirection) <= btScalar(0.0))
                {
                    break;
                }
            } else
            {
                //				printf("currentDir: don't normalize a zero vector\n");
                break;
            }
        } else {
            // we moved whole way
            m_currentPosition = m_targetPosition;
        }

        //	if (callback.m_closestHitFraction == 0.f)
        //		break;

    }
}

void btKinematicCharacterController2::stepDown ( btCollisionWorld* collisionWorld, btScalar dt)
{
    btTransform start, end;

    // phase 3: down
    btVector3 step_drop = upAxisDirection[m_upAxis] * m_currentStepOffset;
    btVector3 gravity_drop = upAxisDirection[m_upAxis] * m_stepHeight; 
    m_targetPosition -= (step_drop + gravity_drop);

    start.setIdentity ();
    end.setIdentity ();

    start.setOrigin (m_currentPosition);
    end.setOrigin (m_targetPosition);

    btKinematicClosestNotMeConvexResultCallback callback (m_ghostObject);
    callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
    callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

    if (m_useGhostObjectSweepTest)
    {
        m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
    } else
    {
        collisionWorld->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
    }

    if (callback.hasHit())
    {
        // we dropped a fraction of the height -> hit floor
        m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);
    } else {
        // we dropped the full height

        m_currentPosition = m_targetPosition;
    }
}



void btKinematicCharacterController2::setWalkDirection
(
 const btVector3& walkDirection
 )
{
    m_useWalkDirection = true;
    m_walkDirection = walkDirection;
    m_normalizedDirection = getNormalizedVector(m_walkDirection);
}



void btKinematicCharacterController2::setVelocityForTimeInterval
(
 const btVector3& velocity,
 btScalar timeInterval
 )
{
    //	printf("setVelocity!\n");
    //	printf("  interval: %f\n", timeInterval);
    //	printf("  velocity: (%f, %f, %f)\n",
    //	    velocity.x(), velocity.y(), velocity.z());

    m_useWalkDirection = false;
    m_walkDirection = velocity;
    m_normalizedDirection = getNormalizedVector(m_walkDirection);
    m_velocityTimeInterval = timeInterval;
}



void btKinematicCharacterController2::reset ()
{
}

void btKinematicCharacterController2::warp (const btVector3& origin)
{
    btTransform xform;
    xform.setIdentity();
    xform.setOrigin (origin);
    m_ghostObject->setWorldTransform (xform);
}

///btActionInterface interface
void btKinematicCharacterController2::updateAction( btCollisionWorld* collisionWorld,btScalar deltaTime)
{
    didx = 0; // reset debug index
    preStep ( collisionWorld);
    playerStep (collisionWorld, deltaTime);
}



void btKinematicCharacterController2::preStep (  btCollisionWorld* collisionWorld)
{

    int numPenetrationLoops = 0;
    m_touchingContact = false;

    while (recoverFromPenetration (collisionWorld))
    {
        numPenetrationLoops++;
        m_touchingContact = true;
        if (numPenetrationLoops > 4)
        {
            //			printf("character could not recover from penetration = %d\n", numPenetrationLoops);
            break;
        }
    }


    m_currentPosition = m_ghostObject->getWorldTransform().getOrigin();
    m_targetPosition = m_currentPosition;
    //	printf("m_targetPosition=%f,%f,%f\n",m_targetPosition[0],m_targetPosition[1],m_targetPosition[2]);


}

void btKinematicCharacterController2::playerStep (  btCollisionWorld* collisionWorld, btScalar dt)
{
    //	printf("playerStep(): ");
    //	printf("  dt = %f", dt);

    // quick check...
    if (!m_useWalkDirection && m_velocityTimeInterval <= 0.0) {
        //		printf("\n");
        return;		// no motion
    }

    btTransform xform;
    xform = m_ghostObject->getWorldTransform ();

    //	printf("walkDirection(%f,%f,%f)\n",walkDirection[0],walkDirection[1],walkDirection[2]);
    //	printf("walkSpeed=%f\n",walkSpeed);

    stepUp (collisionWorld);

    if (m_useWalkDirection) {
        stepForwardAndStrafe (collisionWorld, m_walkDirection);
    } else {
        //printf("  time: %f", m_velocityTimeInterval);
        // still have some time left for moving!
        btScalar dtMoving =
            (dt < m_velocityTimeInterval) ? dt : m_velocityTimeInterval;
        m_velocityTimeInterval -= dt;

        // how far will we move while we are moving?
        btVector3 move = m_walkDirection * dtMoving;

        // printf("  dtMoving: %f", dtMoving);

        // okay, step
        stepForwardAndStrafe(collisionWorld, move);
    }
    stepDown (collisionWorld, dt);

    // printf("\n");

    xform.setOrigin (m_currentPosition);
    m_ghostObject->setWorldTransform (xform);
}

void btKinematicCharacterController2::setFallSpeed (btScalar fallSpeed)
{
    m_fallSpeed = fallSpeed;
}

void btKinematicCharacterController2::setJumpSpeed (btScalar jumpSpeed)
{
    m_jumpSpeed = jumpSpeed;
}

void btKinematicCharacterController2::setMaxJumpHeight (btScalar maxJumpHeight)
{
    m_maxJumpHeight = maxJumpHeight;
}

bool btKinematicCharacterController2::canJump () const
{
    return onGround();
}

void btKinematicCharacterController2::jump ()
{
    if (!canJump())
        return;

#if 0
    currently no jumping.
        btTransform xform;
    m_rigidBody->getMotionState()->getWorldTransform (xform);
    btVector3 up = xform.getBasis()[1];
    up.normalize ();
    btScalar magnitude = (btScalar(1.0)/m_rigidBody->getInvMass()) * btScalar(8.0);
    m_rigidBody->applyCentralImpulse (up * magnitude);
#endif
}

bool btKinematicCharacterController2::onGround () const
{
    return true;
}


void	btKinematicCharacterController2::debugDraw(btIDebugDraw* debugDrawer)
{
}