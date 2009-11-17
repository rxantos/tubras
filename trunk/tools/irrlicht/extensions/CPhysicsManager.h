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
    public:
        CPhysicsManager() {};

        void setAttributes(irr::io::IAttributes* userData, struct CPhysicsAttributes& attr);

#ifdef USE_BULLET
        void addPhysicsObject(io::IAttributes* userData,
            btDiscreteDynamicsWorld* dynamicWorld,
            irr::scene::ISceneNode* node,);
#elif USE_IRRPHYSX
        void addPhysicsObject(io::IAttributes* userData,
            IPhysxManager* physxManager, 
            irr::scene::ISceneNode* node);
#else // Irrlicht
        void addPhysicsObject(irr::io::IAttributes* userData,
            irr::scene::ISceneManager* sceneManager, 
            irr::scene::ISceneNode* node,
            irr::scene::IMetaTriangleSelector* world,
            irr::scene::IMetaTriangleSelector* triggerWorld);
#endif

        void setGravity(f32 value) {m_gravity = value;}
        void stepSimulation(irr::f32 time);
    };
}
#endif