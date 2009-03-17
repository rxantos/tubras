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
    TDynamicWorld::TDynamicWorld() : btIDebugDraw(), TDObject()
    {
        m_debugMode = PDM_NoDebug;
        m_maxProxies = 32766;
        m_maxOverlap = 65535;
        m_debugObject = 0;
        m_gravity = TVector3::ZERO;

        m_collisionConfig = new btDefaultCollisionConfiguration();
        m_dispatcher = new	btCollisionDispatcher(m_collisionConfig);

        btVector3 worldAabbMin(-10000,-10000,-10000);
        btVector3 worldAabbMax(10000,10000,10000);

        m_broadPhase = new btAxisSweep3(worldAabbMin,worldAabbMax,m_maxProxies);
        m_solver = new btSequentialImpulseConstraintSolver;

        m_world = new btDiscreteDynamicsWorld(m_dispatcher,m_broadPhase,m_solver,m_collisionConfig);

        btVector3 bgravity;
        TIBConvert::IrrToBullet(m_gravity,bgravity);
        m_world->setGravity(bgravity);
        m_world->setDebugDrawer(this);

    }

    //-----------------------------------------------------------------------
    //                      ~ T D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld::~TDynamicWorld()
    {
        // delete dynamic nodes

        while(m_nodes.getSize())
        {
            TDynamicNodeList::Iterator itr = m_nodes.begin();
            destroyDynamicNode(*itr);
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
        TVector3 v1;
        TIBConvert::BulletToIrr(from,v1);
        TVector3 v2;
        TIBConvert::BulletToIrr(to,v2);

        // handle bullet simplex debug color bug...
        TColor scolor((u32)color.x(), (u32)color.y(), (u32)color.z());
        TVertex vert1(v1,v1,scolor,TVector2());
        TVertex vert2(v2,v2,scolor,TVector2());
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
                ISceneManager* sm = getApplication()->getSceneManager();
                m_debugObject =  (TDebugNode*)sm->addSceneNode("TDebugNode",0);
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

    int	 TDynamicWorld::getDebugMode() const 
    { 
        return m_debugMode;
    }


    //-----------------------------------------------------------------------
    //                        r e p o r t W a r n i n g
    //-----------------------------------------------------------------------
    void TDynamicWorld::reportErrorWarning(const char* warningString)
    {
        TStrStream msg;
        msg << "DynamicWorld: " << warningString;
        getApplication()->logMessage(msg.str().c_str());
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
    //                       a d d D y n a m i c N o d e
    //-----------------------------------------------------------------------
    void TDynamicWorld::addDynamicNode(TDynamicNode* node)
    {
        m_world->addRigidBody(node->getRigidBody()->getBulletRigidBody());
        m_nodes.push_back(node);
    }

    //-----------------------------------------------------------------------
    //                   d e s t r o y D y n a m i c N o d e
    //-----------------------------------------------------------------------
    void TDynamicWorld::destroyDynamicNode(TDynamicNode* node)
    {
        TDynamicNodeList::Iterator itr = m_nodes.begin();
        while(itr != m_nodes.end())
        {
            if(*itr == node)
            {
                delete node;
                m_nodes.erase(itr);
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
        btVector3 b;
        TIBConvert::IrrToBullet(value,b);
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
            TDynamicNode* pn = (TDynamicNode*) body->getUserPointer();
            pn->getRigidBody()->allowDeactivation(value);
        }
    }

    //-----------------------------------------------------------------------
    //                              r a y T e s t
    //-----------------------------------------------------------------------
    TRayResult TDynamicWorld::rayTest(const TRay& ray)
    {
        btVector3 rayFrom,rayTo;
        TIBConvert::IrrToBullet(ray.start,rayFrom);
        TIBConvert::IrrToBullet(ray.end,rayTo);

        btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);
        m_world->rayTest(rayFrom,rayTo,rayCallback);

        TRayResult rr(rayCallback);
        return rr;
    }

    //-----------------------------------------------------------------------
    //                              s t e p
    //-----------------------------------------------------------------------
    void TDynamicWorld::step(u32 delta)
    {
        
        
        m_world->stepSimulation(delta/1000.f);

        //
        // synchronize motion states
        //
        TDynamicNodeList::Iterator itr = m_nodes.begin();
        while(itr != m_nodes.end())
        {
            (*itr)->synchronizeMotionState();
            ++itr;
        }

        if(m_debugObject)
        {
            m_debugObject->reset();
            m_world->debugDrawWorld();
        }
    }
}

