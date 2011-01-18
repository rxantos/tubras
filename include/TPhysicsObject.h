//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TDYNAMICNODE_H_
#define _TDYNAMICNODE_H_

namespace Tubras
{
    class TPhysicsObject : public btDefaultMotionState
    {
        friend class TPhysicsManager;
    protected:

        TString                 m_name;
        ISceneNode*             m_sceneNode;
        btRigidBody*            m_rigidBody;
        TCollisionShape*        m_shape;
        float                   m_mass;
        bool                    m_sensor;
        bool                    m_ghost;
        short                   m_groupMask;
        short                   m_collisionMask;
        TVector3                m_offset;
        bool                    m_allowDeactivation;

    protected:
        TPhysicsObject (const TString& name, ISceneNode* sceneNode,
            TCollisionShape* bodyShape, float mass=0.0f,
            bool isSensor=false, bool isGhost=false, short groupMask=0, short collisionMask=0, 
            TVector3 colliderOffset=TVector3_ZERO);

        ~TPhysicsObject();

    public:
        btRigidBody* getRigidBody() {return m_rigidBody;};

        TCollisionShape* getCollisionShape() {return m_shape;};
        virtual void setActivationState(int value);
        virtual void applyImpulse(const TVector3& impulse, const TVector3& rel_pos);
        virtual void getCenterOfMassPosition(TVector3& out);
        virtual void setRestitution(TReal value);
        virtual void setFriction(TReal value);
        virtual void setDamping(TReal linearDamping, TReal angularDamping);
        virtual void setLinearVelocity(const TVector3& value);
        virtual void setKinematic(bool value);
        
        virtual ISceneNode* getSceneNode() {return m_sceneNode;}
        virtual void setSceneNode(ISceneNode* value) {m_sceneNode = value;}

        const TString getName() {return m_name;}
        float getMass() {return m_mass;}

        void allowDeactivation(bool value);
        void setAllowDeactivation(bool value) {m_allowDeactivation = value;}
        virtual bool deactivationCallback(void*	userPointer) {return m_allowDeactivation;}

        bool isActive() {return m_rigidBody->isActive();}
        void activate() {m_rigidBody->activate();}

        void setCollisionFlags(int value) {m_rigidBody->setCollisionFlags(value);}
        int getCollisionFlags() {return m_rigidBody->getCollisionFlags();}

        short getGroupMask() {return m_groupMask;}
        short getCollisionMask() {return m_collisionMask;}

	    virtual void getWorldTransform(btTransform& centerOfMassWorldTrans ) const;
	    virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans);

        void disable();
        void enable();
    };
}
#endif
