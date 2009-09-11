//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TDYNAMICWORLD_H_
#define __TDYNAMICWORLD_H_

namespace Tubras
{
    class TRigidBody;

    enum TDebugPhysicsMode
    {
        PDM_NoDebug=0,
        PDM_DrawWireframe = 1,
        PDM_DrawAabb=2,
        PDM_DrawFeaturesText=4,
        PDM_DrawContactPoints=8,
        PDM_NoDeactivation=16,
        PDM_NoHelpText = 32,
        PDM_DrawText=64,
        PDM_ProfileTimings = 128,
        PDM_EnableSatComparison = 256,
        PDM_DisableBulletLCP = 512,
        PDM_EnableCCD = 1024,
        PDM_MAX_DEBUG_DRAW_MODE
    };

    typedef TList<TPhysicsObject*>       TPhysicsObjectList;

    class TDynamicWorld :   public btIDebugDraw, public TDelegate
    {
    protected:
        btDiscreteDynamicsWorld*    m_world;
        btCollisionDispatcher*      m_dispatcher;
        btDefaultCollisionConfiguration* m_collisionConfig;
        btBroadphaseInterface*      m_broadPhase;
        btConstraintSolver*         m_solver;
        TVector3                    m_gravity;
        btGhostPairCallback*        m_ghostPairCallback;
        int                         m_maxProxies;
        int                         m_maxOverlap;
        TDebugPhysicsMode           m_debugMode;
        TPhysicsObjectList          m_objects;
        TPhysicsObjectList          m_kinematicObjects;
        u32                         m_subSteps;
        f32                         m_orgTimeStep;
        f32                         m_fixedTimeStep;

        TDebugNode*                 m_debugObject;

        f32                         m_simulationSpeed;
        TPlayerController*          m_playerController;

    public:
        TDynamicWorld();
        virtual ~TDynamicWorld();

        //
        // debug functionality
        //
        void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
        void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,float distance,int lifeTime,const btVector3& color);
	    void draw3dText(const btVector3& location,const char* textString);

        void setDebugMode(int debugMode);
        int	 getDebugMode() const;
        void reportErrorWarning(const char* warningString);
        void toggleDebug();

        int initialize();

        void setPlayerController(TPlayerController* value);
        
        TPhysicsObjectList getPhysicsObjects() {return m_objects;}

        btDiscreteDynamicsWorld* getBulletWorld() {return m_world;}

        void setGravity(const TVector3& value);
        TVector3 getGravity();

        void setSimulationSpeed(f32 value) {
            m_simulationSpeed = value;
        }
        f32 getSimulationSpeed() {return m_simulationSpeed;}

        void allowDeactivation(bool value);

        void addPhysicsObject(TPhysicsObject* object);
        void destroyPhysicsObject(TPhysicsObject* object);

        TRayResult rayTest(const TRay& ray);

        void activateAllObjects();

        void update(const f32 deltaTime);
    };
}

#endif
