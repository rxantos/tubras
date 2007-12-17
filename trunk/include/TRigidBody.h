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
        TVector3				m_offset;

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
        TVector3 getCenterOfMassPosition();
        void setRestitution(TReal value);
        void setDamping(TReal linearDamping, TReal angularDamping);

    };

}


#endif
