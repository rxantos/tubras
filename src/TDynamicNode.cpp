//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
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

        TMatrix4 startTransform(m_sceneNode->getAbsoluteTransformation());
        m_body = new TRigidBody(mass,startTransform,shape,bodyType,colliderOffset,this);
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
        
        btRigidBody* body = getRigidBody()->getBulletRigidBody();
        btDefaultMotionState* motionState = (btDefaultMotionState*)body->getMotionState();

        if(body->isKinematicObject())
        {
            TString name = m_sceneNode->getName();
        }

        if(!body->isStaticOrKinematicObject())
        {
            btTransform t;
            motionState->getWorldTransform(t);
            TMatrix4 mat4 = TIBConvert::BulletToIrr(t);


            //TQuaternion q = mat4.extractQuaternion();                
            //TVector3 pos = mat4.getTrans();

            m_sceneNode->setPosition(mat4.getTranslation());
            m_sceneNode->setRotation(mat4.getRotationDegrees());
        }
        else 
        {

            TMatrix4 mat4;
            m_sceneNode->updateAbsolutePosition();
            TVector3 rot = m_sceneNode->getRotation();
            rot.X *= -1.f;
            rot.Y *= -1.f;
            TVector3 pos = m_sceneNode->getPosition();

            btQuaternion quat(DegreesToRadians(rot.Y),DegreesToRadians(rot.X),
                DegreesToRadians(rot.Z));
            btTransform xform(quat);
            xform.setOrigin(TIBConvert::IrrToBullet(pos));
            motionState->setWorldTransform(xform);            
            //mat4 = m_sceneNode->getAbsoluteTransformation();
            //mat4.setTranslation(getRigidBody()->getOffset());
            //motionState->setWorldTransform(TIBConvert::IrrToBullet(mat4));            
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
    TVector3 TDynamicNode::getCenterOfMassPosition()
    {
        return m_body->getCenterOfMassPosition();
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

