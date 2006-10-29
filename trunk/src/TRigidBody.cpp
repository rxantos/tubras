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
    //                          T R i g i d B o d y
    //-----------------------------------------------------------------------
    TRigidBody::TRigidBody(float mass,TMatrix4& startTransform,TColliderShape* shape,void* userData) 
    {

        m_mass = mass;
        m_shape = shape;
        m_body = NULL;

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        m_isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (m_isDynamic)
            shape->calculateLocalInertia(mass,localInertia);

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

        m_motionState = new btDefaultMotionState(TOBConvert::OgreToBullet(startTransform));
        m_body = new btRigidBody(m_mass,m_motionState,m_shape->getShape(),localInertia);
        m_body->m_userObjectPointer = userData;
		m_body->setFriction(5.0f);

        TPhysicsManager::getSingleton().getWorld()->addRigidBody(this);
    }

    //-----------------------------------------------------------------------
    //                         ~ T R i g i d B o d y
    //-----------------------------------------------------------------------
    TRigidBody::~TRigidBody()
    {
    }

    //-----------------------------------------------------------------------
    //                    a l l o w D e a c t i v a t i o n
    //-----------------------------------------------------------------------
	void TRigidBody::allowDeactivation(bool value)
	{
		if(value)
		{
			m_body->ForceActivationState(ACTIVE_TAG);
			m_body->activate();
		}
		else m_body->SetActivationState(DISABLE_DEACTIVATION);
	}


}