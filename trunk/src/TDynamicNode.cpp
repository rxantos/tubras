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
    //                        T D y n a m i c N o d e
    //-----------------------------------------------------------------------
    TDynamicNode::TDynamicNode (string name, TSceneNode *parent, TColliderShape* shape,
		float mass,TBodyType bodyType) : TSceneNode(name,parent)
    {
        TMatrix4 startTransform;

		m_isDynamic = true;
        m_mass = mass;
		if(m_mass == 0.0f)
			m_isDynamic = false;

        parent->getTransform(&startTransform);        
        m_body = new TRigidBody(mass,startTransform,shape,bodyType,this);
        TPhysicsManager::getSingleton().getWorld()->addDynamicNode(this);
		parent->attachDynamicNode(this);
    }

    //-----------------------------------------------------------------------
    //                       ~ T D y n a m i c N o d e
    //-----------------------------------------------------------------------
    TDynamicNode::~TDynamicNode()
    {
        if(m_body)
            delete m_body;

	}

    //-----------------------------------------------------------------------
    //                           i s D y n a m i c
    //-----------------------------------------------------------------------
	bool TDynamicNode::isDynamic()
	{
		return m_body->isDynamic();
	}

    //-----------------------------------------------------------------------
    //               s y n c h r o n i z e M o t i o n S t a t e
    //-----------------------------------------------------------------------
	void TDynamicNode::synchronizeMotionState()
	{
        TSceneNode* parent = getParent();
		btRigidBody* body = getRigidBody()->getBulletRigidBody();
        btDefaultMotionState* motionState = (btDefaultMotionState*)body->getMotionState();

        if(body->isKinematicObject())
        {
            string name = parent->getName();
        }

		if(!body->isStaticOrKinematicObject())
		{
                btTransform t;
                motionState->getWorldTransform(t);
                TMatrix4 mat4 = TOBConvert::BulletToOgre(t);


                TQuaternion q = mat4.extractQuaternion();                
                TVector3 pos = mat4.getTrans();

                parent->setPos(pos);
                parent->setOrientation(q);				
		}
		else 
		{
            
			TMatrix4 mat4;
			parent->getTransform(&mat4);
			body->setCenterOfMassTransform(TOBConvert::OgreToBullet(mat4));
            
		}
	}


}