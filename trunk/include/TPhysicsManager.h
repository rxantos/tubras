//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __TPHYSICSMANAGER_H_
#define __TPHYSICSMANAGER_H_

namespace Tubras
{
    class SRBConstraint
    {
    public:
        TString             Name;
        ISceneNode*         Node;
        TRBConstraintType   Type;
        TString             Target;
        TString             Child;
        btVector3           Pivot;
        btVector3           Axis;
    };

    typedef TList<SRBConstraint*>        TPhysicsConstraintList;
    typedef TList<TPhysicsObject*>      TPhysicsObjectList;
    class TPhysicsManager : public btIDebugDraw, public TDelegate
    {
        friend class TApplication;
        typedef void (TPhysicsManager::*TPMUpdateDelegate)(const f32);
    protected:
        TPhysicsMode                m_mode;
        TString					    m_userDebugString;
        TCharacterController*       m_characterController;
        TTimer*                     m_timer;
        TPMUpdateDelegate           m_updater;
        IMetaTriangleSelector*      m_irrWorld;
        IMetaTriangleSelector*      m_irrSensorWorld;
        ISceneCollisionManager*     m_irrCollisionManager;

        ISceneNodeAnimatorCollisionResponse* m_irrCollision;
        TCollisionSystemType        m_csType;

        const ISceneNode*           m_activeSensor;


        btDiscreteDynamicsWorld*    m_bulletWorld;
        btCollisionDispatcher*      m_dispatcher;
        btDefaultCollisionConfiguration* m_collisionConfig;
        btBroadphaseInterface*      m_broadPhase;
        btConstraintSolver*         m_solver;
        TVector3                    m_gravity;
        btGhostPairCallback*        m_ghostPairCallback;
        int                         m_maxProxies;
        int                         m_maxOverlap;
        TPhysicsDebugMode           m_debugMode;
        TPhysicsObjectList          m_objects;
        TPhysicsObjectList          m_kinematicObjects;
        u32                         m_subSteps;
        f32                         m_orgTimeStep;
        f32                         m_fixedTimeStep;

        TDebugNode*                 m_debugObject;
        f32                         m_simulationSpeed;
        f32                         m_dtHigh, m_dtLow, m_dtRunning;

    protected:
        TPhysicsManager();
        virtual ~TPhysicsManager();
        void updateBullet(const f32 deltaTime);
        void updateIrrlicht(const f32 deltaTime);
        void updateIrrlichtCollisionDebug();
        int initialize();

    public:

        void setUserDebugString(const TString& value);

        void setCharacterController(TCharacterController* value);
        TCharacterController* getCharacterController() {return m_characterController;}

        TCharacterControllerMode getCharacterControllerMode() {return m_characterController->getMode();}
        void setCharacterControllerMode(TCharacterControllerMode value);

        void setSimulationSpeed(f32 value) {m_simulationSpeed = value;}
        f32 getSimulationSpeed() {return m_simulationSpeed;}

        TCollisionSystemType getCollisionSystemType() {return m_csType;}

        btDiscreteDynamicsWorld* getBulletWorld() {return m_bulletWorld;};
        IMetaTriangleSelector* getIrrWorld() {return m_irrWorld;}

        //
        // Bullet debug functionality
        //
        void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
        void drawLine(const vector3df& from,const vector3df& to,const TColor& color);

        void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,float distance,int lifeTime,const btVector3& color);
	    void draw3dText(const btVector3& location,const char* textString);

        void setDebugMode(int debugMode);
        int	 getDebugMode() const;
        void reportErrorWarning(const char* warningString);
#ifndef BT_NO_PROFILE
        void dumpBulletProfile(CProfileIterator* profileIterator, int spacing);
#endif
        void toggleDebug();
        TPhysicsObjectList getPhysicsObjects() {return m_objects;}
        void jumpCharacter();
        void setCharacterAttributes(f32 width, f32 height, f32 stepHeight, f32 jumpSpeed);

        void setGravity(const TVector3& value);
        TVector3 getGravity();

        void allowDeactivation(bool value);

        TPhysicsObject* createObject(ISceneNode* snode,
            TPhysicsBodyShape bodyShape, f32 mass=0.f, f32 radius=0.f,
            bool isVisible=true, bool isGhost=false, bool isSensor=false, 
            f32 friction=0.f, f32 restitution=0.f);

        void addPhysicsObject(TPhysicsObject* object);
        void destroyPhysicsObject(TPhysicsObject* object);
        void addConstraints(const TPhysicsConstraintList& constraints);

        TPhysicsObject* getObjectFromNode(ISceneNode* node);

        TRayResult rayTest(const TRay& ray);

        void activateAllObjects();

        void update(const f32 delta);
    };
}


#endif
