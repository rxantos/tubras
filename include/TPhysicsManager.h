//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TPHYSICSMANAGER_H_
#define __TPHYSICSMANAGER_H_

namespace Tubras
{
    typedef TList<TPhysicsObject*>       TPhysicsObjectList;

    class TPhysicsManager : public btIDebugDraw, public TDelegate
    {
        friend class TApplication;
        typedef void (TPhysicsManager::*TPMUpdateDelegate)(const f32);
    protected:
        TPhysicsMode            m_mode;
        TString					m_userDebugString;
        TPlayerController*      m_playerController;
        TTimer*                 m_timer;
        TPMUpdateDelegate       m_updater;
        IMetaTriangleSelector*  m_irrWorld;
        ISceneNodeAnimatorCollisionResponse* m_irrCollision;
        TCollisionSystemType    m_csType;


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

    protected:
        TPhysicsManager();
        virtual ~TPhysicsManager();
        void updateBullet(const f32 deltaTime);
        void updateIrrlicht(const f32 deltaTime);

        int initialize();

    public:

        void setUserDebugString(const TString& value);

        void setPlayerController(TPlayerController* value);

        TPlayerController* getPlayerController() {return m_playerController;}

        void setSimulationSpeed(f32 value) {m_simulationSpeed = value;}
        f32 getSimulationSpeed() {return m_simulationSpeed;}

        TCollisionSystemType getCollisionSystemType() {return m_csType;}

        btDiscreteDynamicsWorld* getBulletWorld() {return m_bulletWorld;};
        IMetaTriangleSelector* getIrrWorld() {return m_irrWorld;}

        //
        // Bullet debug functionality
        //
        void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
        void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,float distance,int lifeTime,const btVector3& color);
	    void draw3dText(const btVector3& location,const char* textString);

        void setDebugMode(int debugMode);
        int	 getDebugMode() const;
        void reportErrorWarning(const char* warningString);
        void dumpBulletProfile(CProfileIterator* profileIterator, int spacing);
        void toggleDebug();
        TPhysicsObjectList getPhysicsObjects() {return m_objects;}

        void setGravity(const TVector3& value);
        TVector3 getGravity();

        void allowDeactivation(bool value);

        void addPhysicsObject(TPhysicsObject* object);
        void destroyPhysicsObject(TPhysicsObject* object);

        TRayResult rayTest(const TRay& ray);

        void activateAllObjects();

        void update(const f32 delta);

    };
}


#endif
