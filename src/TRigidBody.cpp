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
    //                          T R i g i d B o d y
    //-----------------------------------------------------------------------
    TRigidBody::TRigidBody(float mass,TMatrix4& startTransform,TColliderShape* shape,
        TBodyType bodyType,TVector3 offset,void* userData) 
    {

        m_mass = mass;
        m_shape = shape;
        m_body = NULL;
        m_bodyType = bodyType;
        m_offset = offset;

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        m_isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (m_isDynamic)
            shape->calculateLocalInertia(mass,localInertia);


        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

        m_motionState = new TMotionState(TOBConvert::OgreToBullet(startTransform));
        m_body = new btRigidBody(m_mass,m_motionState,m_shape->getShape(),localInertia);
        m_body->setUserPointer(userData);

        if(m_bodyType == btStatic)
            setCollisionFlags(getCollisionFlags() | btRigidBody::CF_STATIC_OBJECT);
        else if(m_bodyType == btKinematic)
            setCollisionFlags(getCollisionFlags() | btRigidBody::CF_KINEMATIC_OBJECT);

    }

    //-----------------------------------------------------------------------
    //                         ~ T R i g i d B o d y
    //-----------------------------------------------------------------------
    TRigidBody::~TRigidBody()
    {
        if(m_body)
        {
            TPhysicsManager::getSingleton().getWorld()->getBulletWorld()->removeRigidBody(m_body);
            delete m_body;
        }
        if(m_shape)
            delete m_shape;
        if(m_motionState)
            delete m_motionState;
    }

    //-----------------------------------------------------------------------
    //                    a l l o w D e a c t i v a t i o n
    //-----------------------------------------------------------------------
    void TRigidBody::allowDeactivation(bool value)
    {
        if(value)
        {
            m_body->forceActivationState(ACTIVE_TAG);
            m_body->activate();
        }
        else m_body->setActivationState(DISABLE_DEACTIVATION);
    }

    //-----------------------------------------------------------------------
    //                   g e t A c t i v a t i o n S t a t e
    //-----------------------------------------------------------------------
    int TRigidBody::getActivationState()
    {
        return m_body->getActivationState();
    }

    //-----------------------------------------------------------------------
    //                   s e t A c t i v a t i o n S t a t e
    //-----------------------------------------------------------------------
    void TRigidBody::setActivationState(int value)
    {
        return m_body->setActivationState(value);
    }

    //-----------------------------------------------------------------------
    //                    s e t L i n e a r V e l o c i t y
    //-----------------------------------------------------------------------
    void TRigidBody::setLinearVelocity(TVector3 value)
    {
        m_body->setLinearVelocity(TOBConvert::OgreToBullet(value));
    }

    //-----------------------------------------------------------------------
    //                         s e t F r i c t i o n
    //-----------------------------------------------------------------------
    void TRigidBody::setFriction(TReal value)
    {
        m_body->setFriction(value);
    }

    //-----------------------------------------------------------------------
    //                        a p p l y I m p u l s e
    //-----------------------------------------------------------------------
    void TRigidBody::applyImpulse(const TVector3& impulse, const TVector3& rel_pos)
    {
        m_body->applyImpulse(TOBConvert::OgreToBullet(impulse),
            TOBConvert::OgreToBullet(rel_pos));
    }

    //-----------------------------------------------------------------------
    //               g e t C e n t er O f M a s s P o s i t i o n
    //-----------------------------------------------------------------------
    TVector3 TRigidBody::getCenterOfMassPosition()
    {
        return TOBConvert::BulletToOgre(m_body->getCenterOfMassPosition());
    }

    //-----------------------------------------------------------------------
    //                      s e t R e s t i t u t i o n
    //-----------------------------------------------------------------------
    void TRigidBody::setRestitution(TReal value)
    {
        m_body->setRestitution(value);
    }

    //-----------------------------------------------------------------------
    //                        s e t D a m p i n g
    //-----------------------------------------------------------------------
    void TRigidBody::setDamping(TReal linearDamping, TReal angularDamping)
    {
        m_body->setDamping(linearDamping, angularDamping);
    }

}