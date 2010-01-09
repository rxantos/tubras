//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _CPHYSICSMANAGER_H_
#define _CPHYSICSMANAGER_H_
#include "irrlicht.h"
#ifdef USE_BULLET
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btIDebugDraw.h>
#include <../Extras/ConvexDecomposition/ConvexDecomposition.h>
#include <../Extras/ConvexDecomposition/ConvexBuilder.h>
#elif USE_PHYSX
#include "IrrPhysx.h"
#include "ShapeCreation.h"
#else // irrlicht
#endif
namespace irr
{
    enum EBodyType {btStatic, btDynamic, btKinematic, btSoft};
    enum EShapeType {stBox, stPlane, stSphere, stCone, stCylinder, stConvexMesh, stConcaveMesh};

    struct CPhysicsAttributes
    {
        EBodyType       BodyType;
        EShapeType      Shapetype;
        f32             mass;
        f32             radius;
        f32             friction;
        f32             restitution;
        bool            visible;
        bool            ghost;
        bool            trigger;

    };

    class CPhysicsManager
    {
    private:
        f32         m_gravity;
        irr::scene::ISceneManager* m_sceneManager;
#ifdef USE_BULLET
#elif USE_IRRPHYSX
        IPhysxManager* m_physxManager;
        core::array<SPhysxAndNodePair*> m_objects;
#else // Irrlicht
        irr::scene::ISceneCollisionManager* m_collisionManager;
        irr::ITimer* m_timer;
        irr::scene::IMetaTriangleSelector* m_world;
        irr::scene::IMetaTriangleSelector* m_triggers;
        irr::scene::ISceneNodeAnimatorCollisionResponse* m_response;
#endif

    public:
        CPhysicsManager() {};

        void setAttributes(irr::io::IAttributes* userData, struct CPhysicsAttributes& attr);
        bool processEvent(const SEvent &  event);


#ifdef USE_BULLET
        void addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData);
        void setBulletVars()
        {
        }
        void stepBullet(irr::u32 deltaMS);
#elif USE_IRRPHYSX
        void addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData);
        void setIrrPhysxVars()
        {
        }
        void stepIrrPhysx(irr::u32 deltaMS);
#else // Irrlicht
        void addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData);

        void setIrrlichtVars(irr::scene::ISceneManager* sceneManager,
            irr::ITimer* timer,
            irr::scene::ISceneCollisionManager* collisionManager,
            irr::scene::IMetaTriangleSelector* world,
            irr::scene::IMetaTriangleSelector* triggers,
            irr::scene::ISceneNodeAnimatorCollisionResponse* response
            )
        {
            m_sceneManager = sceneManager;
            m_timer = timer;
            m_collisionManager = collisionManager;
            m_world = world;
            m_triggers = triggers;
            m_response = response;
        }
        void stepIrrlicht(irr::u32 deltaMS);
#endif

        void displayDebug();
        void setGravity(f32 value) {m_gravity = value;}
        void stepSimulation(irr::u32 deltaMS);
    };
}
#endif