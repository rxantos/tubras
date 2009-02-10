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
    //                        T D y n a m i c N o d e
    //-----------------------------------------------------------------------
    TDynamicNode::TDynamicNode (const TString& name, ISceneNode *sceneNode, TColliderShape* shape,
        float mass,TBodyType bodyType,TVector3 colliderOffset) 
    {
        m_sceneNode = sceneNode;
        m_isDynamic = true;
        m_mass = mass;
        if(m_mass == 0.0f)
            m_isDynamic = false;

        m_sceneNode->updateAbsolutePosition();
        TMatrix4 startTransform(m_sceneNode->getAbsoluteTransformation());
        m_body = new TRigidBody(mass,startTransform,shape,bodyType,colliderOffset,this);
        m_brBody = m_body->getBulletRigidBody();
        TPhysicsManager::getSingleton().getWorld()->addDynamicNode(this);
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
        btMotionState* motionState = m_brBody->getMotionState();

        if(m_brBody->isStaticOrKinematicObject())
        {
            if(m_brBody->getActivationState() != ISLAND_SLEEPING)
            {                
                // this isn't working yet 

                m_sceneNode->updateAbsolutePosition();
                TMatrix4 mat4 = m_sceneNode->getAbsoluteTransformation();
                btTransform xform;
                TIBConvert::IrrToBullet(mat4,xform);
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
                btQuaternion quat = t.getRotation();
                btVector3 bpos = t.getOrigin();
                TVector3 pos;
                TIBConvert::BulletToIrr(t.getOrigin(),pos);
                irr::core::quaternion iquat(quat.x(),quat.y(),quat.z(),quat.w());
                TVector3 rot;
                iquat.toEuler(rot);
                rot.X = -RadiansToDegrees(rot.X);
                rot.Y = -RadiansToDegrees(rot.Y);
                rot.Z = RadiansToDegrees(rot.Z);            
                m_sceneNode->setPosition(pos);
                m_sceneNode->setRotation(rot);
            }
        }
    }

    //-----------------------------------------------------------------------
    //                 s e t A c t i v a t i o n S t a t e
    //-----------------------------------------------------------------------
    void TDynamicNode::setActivationState(int newState)
    {
        m_body->setActivationState(newState);
    }

    //-----------------------------------------------------------------------
    //                        a p p l y I m p u l s e
    //-----------------------------------------------------------------------
    void TDynamicNode::applyImpulse(const TVector3& impulse, const TVector3& rel_pos)
    {
        m_body->applyImpulse(impulse,rel_pos);
    }

    //-----------------------------------------------------------------------
    //              g e t C e n t e r O f M a s s P o s i t i o n
    //-----------------------------------------------------------------------
    void TDynamicNode::getCenterOfMassPosition(TVector3& out)
    {
        m_body->getCenterOfMassPosition(out);
    }

    //-----------------------------------------------------------------------
    //                      s e t R e s t i t u t i o n
    //-----------------------------------------------------------------------
    void TDynamicNode::setRestitution(TReal value)
    {
        m_body->setRestitution(value);
    }

    //-----------------------------------------------------------------------
    //                         s e t F r i c t i o n
    //-----------------------------------------------------------------------
    void TDynamicNode::setFriction(TReal value)
    {
        m_body->setFriction(value);
    }

    //-----------------------------------------------------------------------
    //                        s e t D a m p i n g
    //-----------------------------------------------------------------------
    void TDynamicNode::setDamping(TReal linearDamping, TReal angularDamping)
    {
        m_body->setDamping(linearDamping, angularDamping);
    }

    //-----------------------------------------------------------------------
    //                   s e t L i n e a r V e l o c i t y
    //-----------------------------------------------------------------------
    void TDynamicNode::setLinearVelocity(const TVector3& value)
    {
        m_body->setLinearVelocity(value);
    }

    //-----------------------------------------------------------------------
    //                    a l l o w D e a c t i v a t i o n
    //-----------------------------------------------------------------------
    void TDynamicNode::allowDeactivation(bool value)
    {
        m_body->allowDeactivation(value);
    }
}

