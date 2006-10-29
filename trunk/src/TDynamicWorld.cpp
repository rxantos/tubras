//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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

        m_dispatcher = new	btCollisionDispatcher();

        btVector3 worldAabbMin(-10000,-10000,-10000);
        btVector3 worldAabbMax(10000,10000,10000);

        m_broadPhase = new btAxisSweep3(worldAabbMin,worldAabbMax,m_maxProxies);
        m_solver = new btSequentialImpulseConstraintSolver;
		//m_solver->SetFrictionSolverFunc(frictionModel,USER_CONTACT_SOLVER_TYPE1,USER_CONTACT_SOLVER_TYPE1);

        m_world = new btDiscreteDynamicsWorld(m_dispatcher,m_broadPhase,m_solver);
        m_world->setGravity(btVector3(0,0,0));
        m_world->setDebugDrawer(this);
    }

    //-----------------------------------------------------------------------
    //                      ~ T D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld::~TDynamicWorld()
    {
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
			m_debugObject->setVisible(m_debugMode ? true : false);
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
    //                        a d d R i g i d B o d y
    //-----------------------------------------------------------------------
    void TDynamicWorld::addRigidBody(TRigidBody* body)
    {
        m_world->addRigidBody(body->getBody());
    }

    //-----------------------------------------------------------------------
    //                          s e t G r a v i t y
    //-----------------------------------------------------------------------
    void TDynamicWorld::setGravity(float value)
    {
        m_gravity = value;
        m_world->setGravity(btVector3(0,value,0));
    }

    //-----------------------------------------------------------------------
    //                          g e t G r a v i t y
    //-----------------------------------------------------------------------
    float TDynamicWorld::getGravity()
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
			TPhysicsNode* pn = (TPhysicsNode*) body->m_userObjectPointer;
			pn->getBody()->allowDeactivation(value);
		}
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

        m_world->stepSimulation(delta);

		//
		// synchronize motion states
		//
		int numObjects = m_world->getNumCollisionObjects();
		for (int i=0;i<numObjects;i++)
		{
			btCollisionObject* colObj = m_world->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(colObj);

			if (body && body->getMotionState())
			{
				//
				// todo: make this more efficient...
				//
				TPhysicsNode* pn = (TPhysicsNode*) body->m_userObjectPointer;
				TSceneNode* sn = pn->getParent();

				btDefaultMotionState* motionState = (btDefaultMotionState*)body->getMotionState();
				btTransform t;
				motionState->getWorldTransform(t);
				TMatrix4 mat4 = TOBConvert::BulletToOgre(t);

				TQuaternion q = mat4.extractQuaternion();
				TVector3 pos = mat4.getTrans();

				sn->setPos(pos);
				sn->setOrientation(q);				
			}
		}

        if(m_debugMode)
        {
            m_debugObject->end();
        }
    }

}