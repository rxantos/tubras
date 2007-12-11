//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                       T D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld::TDynamicWorld()
    {
        m_debugMode = PDM_NoDebug;
        m_maxProxies = 32766;
        m_maxOverlap = 65535;
        m_debugObject = NULL;
        m_gravity = TVector3::ZERO;

        m_collisionConfig = new btDefaultCollisionConfiguration();
        m_dispatcher = new	btCollisionDispatcher(m_collisionConfig);

        btVector3 worldAabbMin(-10000,-10000,-10000);
        btVector3 worldAabbMax(10000,10000,10000);

        m_broadPhase = new btAxisSweep3(worldAabbMin,worldAabbMax,m_maxProxies);
        m_solver = new btSequentialImpulseConstraintSolver;
        //m_solver->SetFrictionSolverFunc(frictionModel,USER_CONTACT_SOLVER_TYPE1,USER_CONTACT_SOLVER_TYPE1);

        m_world = new btDiscreteDynamicsWorld(m_dispatcher,m_broadPhase,m_solver,m_collisionConfig);
        m_world->setGravity(TOBConvert::OgreToBullet(m_gravity));
        m_world->setDebugDrawer(this);

    }

    //-----------------------------------------------------------------------
    //                      ~ T D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld::~TDynamicWorld()
    {
        if(m_world)
            delete m_world;

        if(m_dispatcher)
            delete m_dispatcher;
        if(m_broadPhase)
            delete m_broadPhase;
        if(m_solver)
            delete m_solver;
    }

    //-----------------------------------------------------------------------
    //                           d r a w L i n e
    //-----------------------------------------------------------------------
    void TDynamicWorld::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
    {
        m_debugObject->colour(color.getX()/255.f,color.getY()/255.f,color.getZ()/255.f);
        m_debugObject->position(TOBConvert::BulletToOgre(from));
        m_debugObject->colour(color.getX()/255.f,color.getY()/255.f,color.getZ()/255.f);
        m_debugObject->position(TOBConvert::BulletToOgre(to));
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
                TSceneManager* sm = getSceneManager();
                m_debugObject =  sm->createManualObject("Physics::Debug"); 
                m_debugObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
                m_debugObject->colour(1,1,1);
                m_debugObject->position(TVector3(0,0,0));
                m_debugObject->colour(1,1,1);
                m_debugObject->position(TVector3(0,0,0));
                m_debugObject->end(); 
                getRenderEngine()->getRootNode()->attachObject(m_debugObject);
            }
        }
        if(m_debugObject)
        {
            if(m_debugMode)
                m_debugObject->setVisible(true);
            else 
            {
                getSceneManager()->destroyManualObject(m_debugObject);
                m_debugObject = NULL;
            }
        }
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
            setDebugMode(PDM_DrawWireframe | PDM_DrawContactPoints);
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
        TDynamicNodeList::iterator itr = m_nodes.begin();
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
    void TDynamicWorld::setGravity(TVector3 value)
    {
        m_gravity = value;
        m_world->setGravity(TOBConvert::OgreToBullet(m_gravity));
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
    TRayResult TDynamicWorld::rayTest(TRay ray)
    {
        bool rc=false;

        btVector3 rayFrom,rayTo;
        rayFrom = TOBConvert::OgreToBullet(ray.getOrigin());
        rayTo = TOBConvert::OgreToBullet(ray.getEndPoint());

        btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);
        m_world->rayTest(rayFrom,rayTo,rayCallback);

        TRayResult rr(rayCallback);
        return rr;
    }

    //-----------------------------------------------------------------------
    //                              s t e p
    //-----------------------------------------------------------------------
    void TDynamicWorld::step(float delta)
    {
        if(m_debugMode)
        {
            m_debugObject->beginUpdate(0);
        }

        m_world->stepSimulation(delta/1000.f);


        ///one way to draw all the contact points is iterating over contact manifolds / points:

        /*
        int numManifolds = m_world->getDispatcher()->getNumManifolds();
        if(!numManifolds)
        numManifolds = 0;
        for (int i=0;i<numManifolds;i++)
        {
        btPersistentManifold* contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
        btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
        contactManifold->refreshContactPoints(obA->getWorldTransform(),obB->getWorldTransform());

        int numContacts = contactManifold->getNumContacts();
        for (int j=0;j<numContacts;j++)
        {
        btManifoldPoint& pt = contactManifold->getContactPoint(j);

        //glBegin(GL_LINES);
        //glColor3f(1, 0, 1);

        btVector3 ptA = pt.getPositionWorldOnA();
        btVector3 ptB = pt.getPositionWorldOnB();

        //glVertex3d(ptA.x(),ptA.y(),ptA.z());
        //glVertex3d(ptB.x(),ptB.y(),ptB.z());
        //glEnd();
        }

        //you can un-comment out this line, and then all points are removed
        //contactManifold->clearManifold();	
        }
        */


        //
        // synchronize motion states
        //
        TDynamicNodeList::iterator itr = m_nodes.begin();
        while(itr != m_nodes.end())
        {
            (*itr)->synchronizeMotionState();
            ++itr;
        }

        if(m_debugMode)
        {
            m_debugObject->end();
        }
    }

}