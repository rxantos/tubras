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
#ifndef _TDYNAMICNODE_H_
#define _TDYNAMICNODE_H_

namespace Tubras
{
    class TColliderShape;
    class TRigidBody;
    enum  TBodyType;

    class TDynamicNode : public TSceneNode
    {
        TRigidBody*             m_body;
        TColliderShape*         m_shape;
        float                   m_mass;
        bool                    m_isDynamic;

    public:
        TDynamicNode (const TString& name, TSceneNode *parent,TColliderShape* shape,float mass=0.0f,
            TBodyType bodyType=btDynamic,TVector3 colliderOffset=TVector3::ZERO);
        virtual ~TDynamicNode();
        TRigidBody* getRigidBody() {return m_body;};
        TColliderShape* getColliderShape() {return m_shape;};
        virtual bool isDynamic();
        virtual void synchronizeMotionState();
        virtual void allowDeactivation(bool value);
        virtual void setActivationState(int newState);
        virtual void applyImpulse(const TVector3& impulse, const TVector3& rel_pos);
        virtual TVector3 getCenterOfMassPosition();
        virtual void setRestitution(TReal value);
        virtual void setFriction(TReal value);
        virtual void setDamping(TReal linearDamping, TReal angularDamping);
        virtual void setLinearVelocity(const TVector3& value);

    };


}
#endif