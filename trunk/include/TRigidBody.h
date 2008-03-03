//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TRIGIDBODY_H_
#define _TRIGIDBODY_H_

namespace Tubras
{
    class TColliderShape;

    class TRigidBody 
    {
    protected:
        TColliderShape*         m_shape;
        TBodyType               m_bodyType;
        btRigidBody*            m_body;
        TMotionState*           m_motionState;
        float                   m_mass;
        bool                    m_isDynamic;
        TVector3                m_offset;

    public:
        TRigidBody(float mass,TMatrix4& startTransform,TColliderShape* shape,
            TBodyType bodyType=btDynamic,TVector3 offset=TVector3::ZERO, void* userData=NULL);
        virtual ~TRigidBody();

        btRigidBody* getBulletRigidBody() {return m_body;};
        btDefaultMotionState* getMotionState() {return m_motionState;};
        float getMass() {return m_mass;};
        TColliderShape* getShape() {return m_shape;};
        void allowDeactivation(bool value);
        void setLinearVelocity(TVector3 value);
        void setFriction(TReal value);
        int  getActivationState();
        void setActivationState(int value);
        void setCollisionFlags(int value) {m_body->setCollisionFlags(value);};
        int getCollisionFlags() {return m_body->getCollisionFlags();};
        bool isDynamic() {return m_body->isStaticObject() != true;};
        TVector3 getOffset() {return m_offset;};
        void setOffset(TVector3 offset) {m_offset = offset;};
        void applyImpulse(const TVector3& impulse, const TVector3& rel_pos);
        void getCenterOfMassPosition(TVector3& out);
        void setRestitution(TReal value);
        void setDamping(TReal linearDamping, TReal angularDamping);

    };

}


#endif
