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
    //                        T P h y s i c s O b j e c t
    //-----------------------------------------------------------------------
    TPhysicsObject::TPhysicsObject (const TString& name, ISceneNode *sceneNode, TColliderShape* shape,
        float mass,TBodyType bodyType, TVector3 colliderOffset) : btDefaultMotionState()
    {
        m_name = name;
        m_sceneNode = sceneNode;

        if(bodyType == btDynamic || bodyType == btKinematic)
            m_isDynamic = true;
        else 
            m_isDynamic = false;
        m_mass = mass;

        m_mass = mass;
        m_shape = shape;
        m_bodyType = bodyType;
        m_offset = colliderOffset;

        m_sceneNode->updateAbsolutePosition();

        // set initial motion state transforms
        TMatrix4 startTransform(m_sceneNode->getAbsoluteTransformation());
        TVector3 pos,rot;
        rot = startTransform.getRotationDegrees();
        pos = startTransform.getTranslation();
        btTransform xform;
        TIBConvert::IrrToBullet(pos,rot,xform);
		m_startWorldTrans =
		m_graphicsWorldTrans = xform;

        m_isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (m_isDynamic)
            shape->calculateLocalInertia(mass,localInertia);

        m_rigidBody = new btRigidBody(m_mass,this,m_shape->getShape(),localInertia);
        m_rigidBody->setUserPointer(this);

        if(m_bodyType == btStatic)
            setCollisionFlags(getCollisionFlags() | btRigidBody::CF_STATIC_OBJECT);

        else if(m_bodyType == btKinematic)
            setCollisionFlags(getCollisionFlags() | btRigidBody::CF_KINEMATIC_OBJECT);

        if(m_bodyType == btDynamic)
        {
            m_groupMask = short(btBroadphaseProxy::DefaultFilter);
            m_collisionMask = short(btBroadphaseProxy::AllFilter);
        }
        else
        {
            m_groupMask = short(btBroadphaseProxy::StaticFilter);
            m_collisionMask = short(btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);
        }

        getApplication()->getPhysicsManager()->getWorld()->addPhysicsObject(this);
    }

    //-----------------------------------------------------------------------
    //                        T P h y s i c s O b j e c t
    //-----------------------------------------------------------------------
    TPhysicsObject::TPhysicsObject (const TString& name, ISceneNode* sceneNode,TColliderShape* shape,
            short groupMask, short collisionMask, float mass, TBodyType bodyType,
            TVector3 colliderOffset)
    {
        m_sceneNode = sceneNode;

        if(bodyType == btDynamic || bodyType == btKinematic)
            m_isDynamic = true;
        else 
            m_isDynamic = false;
        m_mass = mass;

        m_mass = mass;
        m_shape = shape;
        m_bodyType = bodyType;
        m_offset = colliderOffset;

        m_sceneNode->updateAbsolutePosition();

        // set initial motion state transforms
        TMatrix4 startTransform(m_sceneNode->getAbsoluteTransformation());
        TVector3 pos,rot;
        rot = startTransform.getRotationDegrees();
        pos = startTransform.getTranslation();
        btTransform xform;
        TIBConvert::IrrToBullet(pos,rot,xform);
		m_startWorldTrans =
		m_graphicsWorldTrans = xform;

        m_isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (m_isDynamic)
            shape->calculateLocalInertia(mass,localInertia);

        m_rigidBody = new btRigidBody(m_mass,this,m_shape->getShape(),localInertia);
        m_rigidBody->setUserPointer(this);

        if(m_bodyType == btStatic)
            setCollisionFlags(getCollisionFlags() | btRigidBody::CF_STATIC_OBJECT);
        else if(m_bodyType == btKinematic)
            setCollisionFlags(getCollisionFlags() | btRigidBody::CF_KINEMATIC_OBJECT);

        m_groupMask = groupMask;
        m_collisionMask = collisionMask;

        getApplication()->getPhysicsManager()->getWorld()->addPhysicsObject(this);
    }

    //-----------------------------------------------------------------------
    //                       ~ T P h y s i c s O b j e c t
    //-----------------------------------------------------------------------
    TPhysicsObject::~TPhysicsObject()
    {
        if(m_rigidBody)
        {
            getApplication()->getPhysicsManager()->getWorld()->getBulletWorld()->removeRigidBody(m_rigidBody);
            delete m_rigidBody;
        }
        if(m_shape)
            delete m_shape;
    }

    //-----------------------------------------------------------------------
    //                             d i s a b l e 
    //-----------------------------------------------------------------------
    void TPhysicsObject::disable()
    {
        if(m_rigidBody->isInWorld())
            getApplication()->getPhysicsManager()->getWorld()->getBulletWorld()->removeRigidBody(m_rigidBody);
    }

    //-----------------------------------------------------------------------
    //                              e n a b l e 
    //-----------------------------------------------------------------------
    void TPhysicsObject::enable()
    {
        if(!m_rigidBody->isInWorld())
            getApplication()->getPhysicsManager()->getWorld()->getBulletWorld()->addRigidBody(m_rigidBody);
    }

    //-----------------------------------------------------------------------
    //               s y n c h r o n i z e M o t i o n S t a t e
    //-----------------------------------------------------------------------
    void TPhysicsObject::synchronizeMotionState()
    {
        if(m_rigidBody->isKinematicObject())
        {
            if(m_rigidBody->getActivationState() != ISLAND_SLEEPING)
            {                
                m_sceneNode->updateAbsolutePosition();

                TVector3 pos,rot;
                pos = m_sceneNode->getAbsolutePosition();
                rot = m_sceneNode->getAbsoluteTransformation().getRotationDegrees();

                TIBConvert::IrrToBullet(pos, rot, m_graphicsWorldTrans);
            }
        }
    }

    //-----------------------------------------------------------------------
    //                   g e t W o r l d T r a n s f o r m
    //-----------------------------------------------------------------------
    void TPhysicsObject::getWorldTransform(btTransform& centerOfMassWorldTrans) const
    {
        if(m_isDynamic)
            centerOfMassWorldTrans = m_graphicsWorldTrans;
        else
        {
            m_sceneNode->updateAbsolutePosition();

            TVector3 pos,rot(0,0,0);
            pos = m_sceneNode->getAbsolutePosition();
            //rot = m_sceneNode->getAbsoluteTransformation().getRotationDegrees();

            TIBConvert::IrrToBullet(pos, rot, centerOfMassWorldTrans);
        }
    }

    //-----------------------------------------------------------------------
    //                   s e t W o r l d T r a n s f o r m
    //-----------------------------------------------------------------------
    void TPhysicsObject::setWorldTransform(const btTransform& centerOfMassWorldTrans)
    {
        if(!m_isDynamic)
            return;

        if(m_rigidBody->getActivationState() == ISLAND_SLEEPING)
            return;

		m_startWorldTrans = centerOfMassWorldTrans;
		m_graphicsWorldTrans = centerOfMassWorldTrans;

        // update scene node transformation
        const btVector3& pos = m_graphicsWorldTrans.getOrigin();
        m_sceneNode->setPosition(core::vector3df((f32)pos[0], (f32)pos[1], (f32)pos[2]));
        btVector3 EulerRotation;
        TIBConvert::quaternionToEuler(m_graphicsWorldTrans.getRotation(), EulerRotation);
        m_sceneNode->setRotation(core::vector3df(EulerRotation[0], EulerRotation[1], EulerRotation[2]));
    }

    //-----------------------------------------------------------------------
    //                 s e t A c t i v a t i o n S t a t e
    //-----------------------------------------------------------------------
    void TPhysicsObject::setActivationState(int value)
    {
        m_rigidBody->setActivationState(value);
    }

    //-----------------------------------------------------------------------
    //                    a l l o w D e a c t i v a t i o n
    //-----------------------------------------------------------------------
    void TPhysicsObject::allowDeactivation(bool value)
    {
        m_allowDeactivation = value;
        if(value)
        {
            m_rigidBody->forceActivationState(ACTIVE_TAG);
            m_rigidBody->activate();
        }
        else m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
    }

    //-----------------------------------------------------------------------
    //                        a p p l y I m p u l s e
    //-----------------------------------------------------------------------
    void TPhysicsObject::applyImpulse(const TVector3& impulse, const TVector3& rel_pos)
    {
        btVector3 bpos(rel_pos.X, rel_pos.Y, rel_pos.Z);
        btVector3 bimpulse(impulse.X, impulse.Y, impulse.Z);
        m_rigidBody->applyImpulse(bimpulse,bpos);
    }

    //-----------------------------------------------------------------------
    //              g e t C e n t e r O f M a s s P o s i t i o n
    //-----------------------------------------------------------------------
    void TPhysicsObject::getCenterOfMassPosition(TVector3& out)
    {
        const btVector3 pos = m_rigidBody->getCenterOfMassPosition();
        out.set(pos[0], pos[1], pos[2]);
    }

    //-----------------------------------------------------------------------
    //                      s e t R e s t i t u t i o n
    //-----------------------------------------------------------------------
    void TPhysicsObject::setRestitution(TReal value)
    {
        m_rigidBody->setRestitution(value);
    }

    //-----------------------------------------------------------------------
    //                         s e t F r i c t i o n
    //-----------------------------------------------------------------------
    void TPhysicsObject::setFriction(TReal value)
    {
        m_rigidBody->setFriction(value);
    }

    //-----------------------------------------------------------------------
    //                        s e t D a m p i n g
    //-----------------------------------------------------------------------
    void TPhysicsObject::setDamping(TReal linearDamping, TReal angularDamping)
    {
        m_rigidBody->setDamping(linearDamping, angularDamping);
    }

    //-----------------------------------------------------------------------
    //                   s e t L i n e a r V e l o c i t y
    //-----------------------------------------------------------------------
    void TPhysicsObject::setLinearVelocity(const TVector3& value)
    {
        btVector3 bvec(value.X, value.Y, value.Z);
        m_rigidBody->setLinearVelocity(bvec);
    }

}

