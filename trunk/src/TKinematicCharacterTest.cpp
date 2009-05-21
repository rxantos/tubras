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
    static btVector3 upAxisDirection[3] = { btVector3(1.0f, 0.0f, 0.0f), btVector3(0.0f, 1.0f, 0.0f), btVector3(0.0f, 0.0f, 1.0f) };

    class TKinematicClosestNotMeConvexResultCallback : public btCollisionWorld::ClosestConvexResultCallback
    {
    public:
        TKinematicClosestNotMeConvexResultCallback (btCollisionObject* me) : btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0))
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



    //-----------------------------------------------------------------------
    //                   T K i n e m a t i c C h a r a c t e r
    //-----------------------------------------------------------------------
    TKinematicCharacterTest::TKinematicCharacterTest(btPairCachingGhostObject* ghostObject,
        btConvexShape* convexShape,btScalar stepHeight, int upAxis) : btKinematicCharacterController(
        ghostObject, convexShape, stepHeight, upAxis),
        m_jumping(false)
    {

    }

    //-----------------------------------------------------------------------
    //                  ~ T K i n e m a t i c C h a r a c t e r
    //-----------------------------------------------------------------------
    TKinematicCharacterTest::~TKinematicCharacterTest()
    {
    }

    //-----------------------------------------------------------------------
    //                r e c o v e r F r o m P e n e t r a t i o n
    //-----------------------------------------------------------------------
    bool TKinematicCharacterTest::recoverFromPenetration ( btCollisionWorld* collisionWorld)
    {
        bool penetration = false;

        collisionWorld->getDispatcher()->dispatchAllCollisionPairs(m_ghostObject->getOverlappingPairCache(), collisionWorld->getDispatchInfo(), collisionWorld->getDispatcher());

        m_currentPosition = m_ghostObject->getWorldTransform().getOrigin();

        btScalar maxPen = btScalar(0.0);
        for (int i = 0; i < m_ghostObject->getOverlappingPairCache()->getNumOverlappingPairs(); i++)
        {
            m_manifoldArray.resize(0);

            btBroadphasePair* collisionPair = &m_ghostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];

            if (collisionPair->m_algorithm)
                collisionPair->m_algorithm->getAllContactManifolds(m_manifoldArray);


            for (int j=0;j<m_manifoldArray.size();j++)
            {
                btPersistentManifold* manifold = m_manifoldArray[j];
                btScalar directionSign = manifold->getBody0() == m_ghostObject ? btScalar(-1.0) : btScalar(1.0);

                btRigidBody* body1 = (btRigidBody*)manifold->getBody1();
                if(body1->isStaticObject())
                {
                    for (int p=0;p<manifold->getNumContacts();p++)
                    {
                        const btManifoldPoint&pt = manifold->getContactPoint(p);

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
                }
                else
                {
                    for (int p=0;p<manifold->getNumContacts();p++)
                    {
                        const btManifoldPoint&pt = manifold->getContactPoint(p);

                        if (pt.getDistance() < 0.0)
                        {
                            if (pt.getDistance() < maxPen)
                            {
                                maxPen = pt.getDistance();
                                //m_touchingNormal = pt.m_normalWorldOnB * directionSign;//??

                            }
                            //m_currentPosition += pt.m_normalWorldOnB * directionSign * pt.getDistance() * btScalar(0.2);
                            //penetration = true;
                        } else {
                            //printf("touching %f\n", pt.getDistance());
                        }
                    }
                }

                //manifold->clearManifold();
            }
        }
        btTransform newTrans = m_ghostObject->getWorldTransform();
        newTrans.setOrigin(m_currentPosition);
        m_ghostObject->setWorldTransform(newTrans);
        //	printf("m_touchingNormal = %f,%f,%f\n",m_touchingNormal[0],m_touchingNormal[1],m_touchingNormal[2]);
        return penetration;
    }

    //-----------------------------------------------------------------------
    //                   updateTargetPositionBasedOnCollision
    //-----------------------------------------------------------------------
    void TKinematicCharacterTest::updateTargetPositionBasedOnCollision (const btVector3& hitNormal, 
        btScalar tangentMag, btScalar normalMag)
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

    //-----------------------------------------------------------------------
    //                              s t e p U p
    //-----------------------------------------------------------------------
    void TKinematicCharacterTest::stepUp (btCollisionWorld* collisionWorld)
    {
        // phase 1: up
        btTransform start, end;
        m_targetPosition = m_currentPosition + upAxisDirection[m_upAxis] * m_stepHeight;

        start.setIdentity ();
        end.setIdentity ();

        /* FIXME: Handle penetration properly */
        start.setOrigin (m_currentPosition + upAxisDirection[m_upAxis] * btScalar(0.1f));
        end.setOrigin (m_targetPosition);

        TKinematicClosestNotMeConvexResultCallback callback (m_ghostObject);
        callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
        callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

        if (m_useGhostObjectSweepTest)
        {
            m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
        }
        else
        {
            collisionWorld->convexSweepTest (m_convexShape, start, end, callback);
        }

        if (callback.hasHit() && callback.m_hitCollisionObject->isStaticObject())
        {
            // we moved up only a fraction of the step height
            m_currentStepOffset = m_stepHeight * callback.m_closestHitFraction;
            m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);
        } else {
            m_currentStepOffset = m_stepHeight;
            m_currentPosition = m_targetPosition;
        }
    }

    //-----------------------------------------------------------------------
    //                           s t e p D o w n
    //-----------------------------------------------------------------------
    void TKinematicCharacterTest::stepDown (btCollisionWorld* collisionWorld, btScalar dt)
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

        TKinematicClosestNotMeConvexResultCallback callback (m_ghostObject);
        callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
        callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

        if (m_useGhostObjectSweepTest)
        {
            m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
        } else
        {
            collisionWorld->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
        }

        if (callback.hasHit() && callback.m_hitCollisionObject->isStaticObject())
        {
            // we dropped a fraction of the height -> hit floor
            m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);
        } else {
            // we dropped the full height

            m_currentPosition = m_targetPosition;
        }
    }	

    //-----------------------------------------------------------------------
    //                 s t e p F o r w a r d A n d S t r a f e
    //-----------------------------------------------------------------------
    void TKinematicCharacterTest::stepForwardAndStrafe (btCollisionWorld* collisionWorld, const btVector3& walkMove)
    {
        btVector3 originalDir = walkMove.normalized();
        if (walkMove.length() < SIMD_EPSILON)
        {
            originalDir.setValue(0.f,0.f,0.f);
        }
        //	printf("originalDir=%f,%f,%f\n",originalDir[0],originalDir[1],originalDir[2]);
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
            if (originalDir.dot(m_touchingNormal) > btScalar(0.0))
                updateTargetPositionBasedOnCollision (m_touchingNormal);
        }

        int maxIter = 10;

        while (fraction > btScalar(0.01) && maxIter-- > 0)
        {
            start.setOrigin (m_currentPosition);
            end.setOrigin (m_targetPosition);

            TKinematicClosestNotMeConvexResultCallback callback (m_ghostObject);
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
                if(callback.m_hitCollisionObject->isStaticObject())
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
                        if (currentDir.dot(originalDir) <= btScalar(0.0))
                        {
                            break;
                        }
                    } else
                    {
                        //				printf("currentDir: don't normalize a zero vector\n");
                        break;
                    }
                }
            } else {
                // we moved whole way
                m_currentPosition = m_targetPosition;
            }

            //	if (callback.m_closestHitFraction == 0.f)
            //		break;

        }
    }

    //-----------------------------------------------------------------------
    //                            p r e S t e p
    //-----------------------------------------------------------------------
    void TKinematicCharacterTest::preStep (  btCollisionWorld* collisionWorld)
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

    //-----------------------------------------------------------------------
    //                         p l a y e r S t e p
    //-----------------------------------------------------------------------
    void TKinematicCharacterTest::playerStep ( btCollisionWorld* collisionWorld, btScalar dt)
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

    //-----------------------------------------------------------------------
    //                         u p d a t e A c t i o n
    //-----------------------------------------------------------------------
    void TKinematicCharacterTest::updateAction( btCollisionWorld* collisionWorld,
        btScalar deltaTime)
    {
        //preStep ( collisionWorld);

        /* preStep functionality without penetration recovery */
        m_touchingContact = false;
        m_currentPosition = m_ghostObject->getWorldTransform().getOrigin();
        m_targetPosition = m_currentPosition;
        /* end preStep functionality */


        playerStep (collisionWorld, deltaTime);
    }
}
