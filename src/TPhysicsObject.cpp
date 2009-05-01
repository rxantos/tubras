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
        float mass,TBodyType bodyType,TVector3 colliderOffset) 
    {
        m_sceneNode = sceneNode;
        if(bodyType == btDynamic || bodyType == btKinematic)
            m_isDynamic = true;
        else 
            m_isDynamic = false;
        m_mass = mass;

        m_sceneNode->updateAbsolutePosition();
        TMatrix4 startTransform(m_sceneNode->getAbsoluteTransformation());
        m_body = new TRigidBody(mass,startTransform,shape,bodyType,colliderOffset,this);
        m_brBody = m_body->getBulletRigidBody();
        getApplication()->getPhysicsManager()->getWorld()->addPhysicsObject(this);
    }

    //-----------------------------------------------------------------------
    //                       ~ T P h y s i c s O b j e c t
    //-----------------------------------------------------------------------
    TPhysicsObject::~TPhysicsObject()
    {
        if(m_body)
            delete m_body;

    }

    //-----------------------------------------------------------------------
    //                           i s D y n a m i c
    //-----------------------------------------------------------------------
    bool TPhysicsObject::isDynamic()
    {
        return m_body->isDynamic();
    }

    //-----------------------------------------------------------------------
    //               s y n c h r o n i z e M o t i o n S t a t e
    //-----------------------------------------------------------------------
    void TPhysicsObject::synchronizeMotionState()
    {
        if(!m_isDynamic)
            return;

        btMotionState* motionState = m_brBody->getMotionState();

        if(m_brBody->isKinematicObject())
        {
            if(m_brBody->getActivationState() != ISLAND_SLEEPING)
            {                
                m_sceneNode->updateAbsolutePosition();

                TVector3 pos,rot;
                pos = m_sceneNode->getAbsolutePosition();
                rot = m_sceneNode->getAbsoluteTransformation().getRotationDegrees();

                btTransform xform;
                TIBConvert::IrrToBullet(pos, rot, xform);
                motionState->setWorldTransform(xform);
            }
        }
        else // dynamic
        {
            if(m_brBody->getActivationState() != ISLAND_SLEEPING)
            {
                //
                // todo: encode this into a TIBConvert function...
                //
                btTransform t;
                motionState->getWorldTransform(t);

		        const btVector3& pos = t.getOrigin();
		        m_sceneNode->setPosition(core::vector3df((f32)pos[0], (f32)pos[1], (f32)pos[2]));

		        // Set rotation
		        btVector3 EulerRotation;
                TIBConvert::quaternionToEuler(t.getRotation(), EulerRotation);
		        m_sceneNode->setRotation(core::vector3df(EulerRotation[0], EulerRotation[1], EulerRotation[2]));

            }
        }
    }

    //-----------------------------------------------------------------------
    //                 s e t A c t i v a t i o n S t a t e
    //-----------------------------------------------------------------------
    void TPhysicsObject::setActivationState(int newState)
    {
        m_body->setActivationState(newState);
    }

    //-----------------------------------------------------------------------
    //                        a p p l y I m p u l s e
    //-----------------------------------------------------------------------
    void TPhysicsObject::applyImpulse(const TVector3& impulse, const TVector3& rel_pos)
    {
        m_body->applyImpulse(impulse,rel_pos);
    }

    //-----------------------------------------------------------------------
    //              g e t C e n t e r O f M a s s P o s i t i o n
    //-----------------------------------------------------------------------
    void TPhysicsObject::getCenterOfMassPosition(TVector3& out)
    {
        m_body->getCenterOfMassPosition(out);
    }

    //-----------------------------------------------------------------------
    //                      s e t R e s t i t u t i o n
    //-----------------------------------------------------------------------
    void TPhysicsObject::setRestitution(TReal value)
    {
        m_body->setRestitution(value);
    }

    //-----------------------------------------------------------------------
    //                         s e t F r i c t i o n
    //-----------------------------------------------------------------------
    void TPhysicsObject::setFriction(TReal value)
    {
        m_body->setFriction(value);
    }

    //-----------------------------------------------------------------------
    //                        s e t D a m p i n g
    //-----------------------------------------------------------------------
    void TPhysicsObject::setDamping(TReal linearDamping, TReal angularDamping)
    {
        m_body->setDamping(linearDamping, angularDamping);
    }

    //-----------------------------------------------------------------------
    //                   s e t L i n e a r V e l o c i t y
    //-----------------------------------------------------------------------
    void TPhysicsObject::setLinearVelocity(const TVector3& value)
    {
        m_body->setLinearVelocity(value);
    }

    //-----------------------------------------------------------------------
    //                    a l l o w D e a c t i v a t i o n
    //-----------------------------------------------------------------------
    void TPhysicsObject::allowDeactivation(bool value)
    {
        m_body->allowDeactivation(value);
    }
}

