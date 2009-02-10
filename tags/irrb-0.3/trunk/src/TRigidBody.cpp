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

        TVector3 pos,rot;
        rot = startTransform.getRotationDegrees();
        pos = startTransform.getTranslation();
        btTransform xform;
        TIBConvert::IrrToBullet(pos,rot,xform);
        m_motionState = new TMotionState(xform);
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
        btVector3 bvec;
        TIBConvert::IrrToBullet(value, bvec);

        m_body->setLinearVelocity(bvec);
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
        btVector3 bpos,bimpulse;
        TIBConvert::IrrToBullet(rel_pos,bpos);
        TIBConvert::IrrToBullet(impulse,bimpulse);

        m_body->applyImpulse(bimpulse,bpos);
    }

    //-----------------------------------------------------------------------
    //               g e t C e n t er O f M a s s P o s i t i o n
    //-----------------------------------------------------------------------
    void TRigidBody::getCenterOfMassPosition(TVector3& out)
    {

        TIBConvert::BulletToIrr(m_body->getCenterOfMassPosition(),out);
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

