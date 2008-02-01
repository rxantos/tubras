//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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

        m_motionState = new TMotionState(TIBConvert::IrrToBullet(startTransform));
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
        m_body->setLinearVelocity(TIBConvert::IrrToBullet(value));
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
        m_body->applyImpulse(TIBConvert::IrrToBullet(impulse),
            TIBConvert::IrrToBullet(rel_pos));
    }

    //-----------------------------------------------------------------------
    //               g e t C e n t er O f M a s s P o s i t i o n
    //-----------------------------------------------------------------------
    TVector3 TRigidBody::getCenterOfMassPosition()
    {
        return TIBConvert::BulletToIrr(m_body->getCenterOfMassPosition());
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

