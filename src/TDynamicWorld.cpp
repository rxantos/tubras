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
    //                       T D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld::TDynamicWorld() : btIDebugDraw(), TDelegate()
    {
        m_debugMode = PDM_NoDebug;
        m_maxProxies = 32766;
        m_maxOverlap = 65535;
        m_debugObject = 0;
        m_gravity = TVector3::ZERO;

        m_collisionConfig = new btDefaultCollisionConfiguration();
        m_collisionConfig->setConvexConvexMultipointIterations();
        m_dispatcher = new	btCollisionDispatcher(m_collisionConfig);

        btVector3 worldAabbMin(-10000,-10000,-10000);
        btVector3 worldAabbMax(10000,10000,10000);

        m_broadPhase = new btDbvtBroadphase();
        m_solver = new btSequentialImpulseConstraintSolver;

        m_world = new btDiscreteDynamicsWorld(m_dispatcher,m_broadPhase,m_solver,m_collisionConfig);

        m_ghostCallback = new btGhostPairCallback();
        m_world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(m_ghostCallback);

        btVector3 bgravity(m_gravity.X, m_gravity.Y, m_gravity.Z);
        m_world->setGravity(bgravity);
        m_world->setDebugDrawer(this);

    }

    //-----------------------------------------------------------------------
    //                      ~ T D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld::~TDynamicWorld()
    {
        m_world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(0);
        delete m_ghostCallback;

        // delete dynamic nodes
        while(m_objects.getSize())
        {
            TPhysicsObjectList::Iterator itr = m_objects.begin();
            destroyPhysicsObject(*itr);
        }

        if(m_world)
            delete m_world;

        if(m_dispatcher)
            delete m_dispatcher;
        if(m_broadPhase)
            delete m_broadPhase;
        if(m_solver)
            delete m_solver;
        if(m_collisionConfig)
            delete m_collisionConfig;
    }

    //-----------------------------------------------------------------------
    //                           d r a w L i n e
    //-----------------------------------------------------------------------
    void TDynamicWorld::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
    {
        TVector3 v1(from.m_floats[0], from.m_floats[1], from.m_floats[2]);
        TVector3 v2(to.m_floats[0], to.m_floats[1], to.m_floats[2]);

        // handle bullet simplex debug color bug...
        u32 r = (u32)color.x(), g = (u32) color.y(), b = (u32) color.z();

        TColor scolor;
        if( (r > 1) || (g > 1) || (b > 1))
            scolor.set(255, r, g, b);
        else
            scolor.set(255, (u32)(color.x() * 255.f), (u32)(color.y() * 255.f), (u32)(color.z() * 255.f));

        TVertex vert1(v1,v1,scolor,TVector2f());
        TVertex vert2(v2,v2,scolor,TVector2f());
        m_debugObject->addLine(vert1,vert2);
    }

    //-----------------------------------------------------------------------
    //                      d r a w C o n t a c t P o i n t
    //-----------------------------------------------------------------------
    void TDynamicWorld::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,float distance,int lifeTime,const btVector3& color)
    {
    }

    //-----------------------------------------------------------------------
    //                          d r a w 3 d T e x t
    //-----------------------------------------------------------------------
    void TDynamicWorld::draw3dText(const btVector3& location,const char* textString)
    {
    }

    //-----------------------------------------------------------------------
    //                        s e t D e b u g M o d e
    //-----------------------------------------------------------------------
    void TDynamicWorld::setDebugMode(int debugMode)
    {
        
        m_debugMode = (TDebugPhysicsMode)debugMode;
        if(m_debugMode)
        {
            if(!m_debugObject)
            {
                m_debugObject =  new TDebugNode(0);
            }
        }
        if(m_debugObject)
        {
            if(m_debugMode)
                m_debugObject->setVisible(true);
            else 
            {
                if(m_debugObject)
                {
                    m_debugObject->reset();
                    m_debugObject->setVisible(false);
                }
            }
        }
        
    }

    //-----------------------------------------------------------------------
    //                        g e t D e b u g M o d e
    //-----------------------------------------------------------------------
    int	 TDynamicWorld::getDebugMode() const 
    { 
        return m_debugMode;
    }

    //-----------------------------------------------------------------------
    //                        r e p o r t W a r n i n g
    //-----------------------------------------------------------------------
    void TDynamicWorld::reportErrorWarning(const char* warningString)
    {
        getApplication()->logMessage(LOG_WARNING, "DynamicWorld: %s", warningString);
    }

    //-----------------------------------------------------------------------
    //                        t o g g l e D e b u g
    //-----------------------------------------------------------------------
    void TDynamicWorld::toggleDebug()
    {
        if(getDebugMode())
        {
            setDebugMode(PDM_NoDebug);
        }
        else
        {
            setDebugMode(PDM_DrawWireframe);
        }
    }

    //-----------------------------------------------------------------------
    //                    a d d P h y s i c s O b j e c t
    //-----------------------------------------------------------------------
    void TDynamicWorld::addPhysicsObject(TPhysicsObject* object)
    {
        m_world->addRigidBody(object->getRigidBody(), object->getGroupMask(), 
            object->getCollisionMask());
        m_objects.push_back(object);
        if(object->getBodyType() == btKinematic)
        {
            m_kinematicObjects.push_back(object);
        }
    }

    //-----------------------------------------------------------------------
    //                   d e s t r o y D y n a m i c N o d e
    //-----------------------------------------------------------------------
    void TDynamicWorld::destroyPhysicsObject(TPhysicsObject* object)
    {
        TPhysicsObjectList::Iterator itr = m_objects.begin();
        while(itr != m_objects.end())
        {
            if(*itr == object)
            {
                delete object;
                m_objects.erase(itr);
                break;
            }
            ++itr;
        }
    }

    //-----------------------------------------------------------------------
    //                          s e t G r a v i t y
    //-----------------------------------------------------------------------
    void TDynamicWorld::setGravity(const TVector3& value)
    {
        m_gravity = value;
        btVector3 b(value.X, value.Y, value.Z);
        m_world->setGravity(b);
    }

    //-----------------------------------------------------------------------
    //                          g e t G r a v i t y
    //-----------------------------------------------------------------------
    TVector3 TDynamicWorld::getGravity()
    {
        return m_gravity;
    }

    //-----------------------------------------------------------------------
    //                     a l l o w D e a c t i v a t i o n
    //-----------------------------------------------------------------------
    void TDynamicWorld::allowDeactivation(bool value)
    {

        int numObjects = m_world->getNumCollisionObjects();
        for (int i=0;i<numObjects;i++)
        {
            btCollisionObject* colObj = m_world->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(colObj);
            TPhysicsObject* po = (TPhysicsObject*) body->getUserPointer();
            po->allowDeactivation(value);
        }
    }

    //-----------------------------------------------------------------------
    //                              r a y T e s t
    //-----------------------------------------------------------------------
    TRayResult TDynamicWorld::rayTest(const TRay& ray)
    {
        btVector3 rayFrom(ray.start.X, ray.start.Y, ray.start.Z);
        btVector3 rayTo(ray.end.X, ray.end.Y, ray.end.Z);

        btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);
        m_world->rayTest(rayFrom,rayTo,rayCallback);

        TRayResult rr(rayCallback);
        return rr;
    }

    //-----------------------------------------------------------------------
    //                    a c t i v a t e A l l O b j e c ts
    //-----------------------------------------------------------------------
    void TDynamicWorld::activateAllObjects()
    {
        TPhysicsObjectList::Iterator itr = m_objects.begin();

        while(itr != m_objects.end())
        {
            TPhysicsObject* o = *itr;
            if(o->getBodyType() == btDynamic && !o->isActive())
                o->activate();
            ++itr;
        }        
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TDynamicWorld::update(const u32 deltaTime)
    {                
        
        m_world->stepSimulation((f32)deltaTime * 0.001f);

        //
        // report collisions
        //
        /*
        int numManifolds = m_world->getDispatcher()->getNumManifolds();
        for (int i=0;i<numManifolds;i++)
        {
            btPersistentManifold* contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);
            btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
            btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
            btRigidBody* rbA = btRigidBody::upcast(obA);
            btRigidBody* rbB = btRigidBody::upcast(obB);

            TPhysicsObject* oa = static_cast<TPhysicsObject*>(obA->getUserPointer());
            TPhysicsObject* ob = static_cast<TPhysicsObject*>(obB->getUserPointer());
            TString sdbg = "Collision:\n";

            if(oa)
            {
                sdbg += "   A: ";
                sdbg += oa->getName();
                if(rbA)
                {
                    sdbg += ", ActivationState=";
                    sdbg += rbA->getActivationState();
                }
                sdbg += "\n";
            }
            else 
            {
                sdbg += "   A: null\n";
            }

            if(ob)
            {
                sdbg += "   B: ";
                sdbg += ob->getName();
                if(rbB)
                {
                    sdbg += ", ActivationState=";
                    sdbg += rbB->getActivationState();
                }
                sdbg += "\n";
            }
            else 
            {
                sdbg += "   B: null\n";
            }
            */

            /*
            if(oa && (rbA->getActivationState() == ACTIVE_TAG)  &&
                ob && (rbB->getActivationState() == ACTIVE_TAG))
            {
                getApplication()->logMessage(LOG_INFO, "Collision: %s <-> %s", oa->getName().c_str(), 
                    ob->getName().c_str());
            }
            */

            //getApplication()->logMessage(LOG_INFO, sdbg.c_str());

        /*
            int numContacts = contactManifold->getNumContacts();
            for (int j=0;j<numContacts;j++)
            {
                btManifoldPoint& pt = contactManifold->getContactPoint(j);
                if (pt.getDistance()<0.f)
                {
                    const btVector3& ptA = pt.getPositionWorldOnA();
                    const btVector3& ptB = pt.getPositionWorldOnB();
                    const btVector3& normalOnB = pt.m_normalWorldOnB;
                }
            }
        }
        */
    


        if(m_debugObject)
        {
            m_debugObject->reset();
            m_world->debugDrawWorld();
        }
    }
}

