#include "main.h"

#ifdef USE_BULLET
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btConvexHull.h>
#include <../Extras/ConvexDecomposition/ConvexDecomposition.h>
#include <../Extras/ConvexDecomposition/ConvexBuilder.h>
#pragma comment(lib, "BulletCollision.lib") 
#pragma comment(lib, "BulletDynamics.lib") 
#pragma comment(lib, "LinearMath.lib") 


static btDefaultCollisionConfiguration* collisionConfig = 0;
static btCollisionDispatcher* dispatcher = 0;
static btAxisSweep3* broadPhase = 0;
static btSequentialImpulseConstraintSolver* solver = 0;
static btDiscreteDynamicsWorld* m_bulletWorld=0;

static core::array<btCollisionObject*> m_triggers;
extern CDebugNode* m_debugNode;

// bullet debug interface
class DebugDraw : public btIDebugDraw
{
    int  m_debugMode;

	void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
    {
        vector3df v1(from.m_floats[0], from.m_floats[1], from.m_floats[2]);
        vector3df v2(to.m_floats[0], to.m_floats[1], to.m_floats[2]);

        // handle bullet simplex debug color bug...
        u32 r = (u32)color.x(), g = (u32) color.y(), b = (u32) color.z();

        SColor scolor;
        if( (r > 1) || (g > 1) || (b > 1))
            scolor.set(255, r, g, b);
        else
            scolor.set(255, (u32)(color.x() * 255.f), (u32)(color.y() * 255.f), (u32)(color.z() * 255.f));

        S3DVertex vert1(v1,v1,scolor,vector2df());
        S3DVertex vert2(v2,v2,scolor,vector2df());
        m_debugNode->addLine(vert1,vert2);
    }

    void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) {}
    void	reportErrorWarning(const char* warningString)  {}
    void	draw3dText(const btVector3& location,const char* textString) {}
    void	setDebugMode(int debugMode) {m_debugMode = debugMode;}
    int		getDebugMode() const {return m_debugMode;}

};

///This class sychronizes the world transform between Bullet rigid bodies and their accompanying Irrlicht nodes
class MotionState : public btDefaultMotionState
{
	scene::ISceneNode* m_node;
public:

	MotionState(scene::ISceneNode* node)
		:m_node(node)
	{
	}

    static void getRotationDegreesDivScale(const irr::core::matrix4& inmat, irr::core::vector3df& out) 
	{
        const irr::core::matrix4 &mat = inmat;
        const f32* M = mat.pointer();

        f32 SX = sqrtf(M[0] * M[0] + M[1] * M[1] + M[2] * M[2]);
        f32 SY = sqrtf(M[4] * M[4] + M[5] * M[5] + M[6] * M[6]);
        f32 SZ = sqrtf(M[8] * M[8] + M[9] * M[9] + M[10] * M[10]);

		f32 Y = -asin(mat(0,2) / SX);
		const f32 C = cos(Y);
		Y *= RADTODEG;

		f32 rotx, roty, X, Z;

		if (fabs(C)>ROUNDING_ERROR_f64)
		{
			const f32 invC = (f32)(1.0/C);
			rotx = mat(2,2) / SZ * invC;
			roty = mat(1,2) / SY * invC;
			X = atan2( roty, rotx ) * RADTODEG;
			rotx = mat(0,0) / SX * invC;
			roty = mat(0,1) / SX * invC;
			Z = atan2( roty, rotx ) * RADTODEG;
		}
		else
		{
			X = 0.0;
			rotx = mat(1,1) / SY;
			roty = -mat(1,0) / SY;
			Z = atan2( roty, rotx ) * RADTODEG;
		}

		// fix values that get below zero
		// before it would set (!) values to 360
		// that where above 360:
		if (X < 0.0) X += 360.0;
		if (Y < 0.0) Y += 360.0;
		if (Z < 0.0) Z += 360.0;

        out.set(X, Y, Z);
	}

    // Converts a Bullet quaternion to an Irrlicht euler angle
    void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler) {
        btScalar W = TQuat.getW();
        btScalar X = TQuat.getX();
        btScalar Y = TQuat.getY();
        btScalar Z = TQuat.getZ();
        float WSquared = W * W;
        float XSquared = X * X;
        float YSquared = Y * Y;
        float ZSquared = Z * Z;

        TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
        TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
        TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
        TEuler *= core::RADTODEG;
    }


	// synchronizes world transform from user to physics - invoked on object init and per frame
    // for kinematic objects.
	virtual void	getWorldTransform(btTransform& centerOfMassWorldTrans ) const 
	{
		centerOfMassWorldTrans = m_graphicsWorldTrans;


        if(!m_node)
            return;

        m_node->updateAbsolutePosition();

        core::vector3df pos,rot(0,0,0);
        pos = m_node->getAbsolutePosition();
        getRotationDegreesDivScale(m_node->getAbsoluteTransformation(), rot);

        core::quaternion iquat;
        core::vector3df rrot = rot * core::DEGTORAD;
        iquat.set(rrot);

        btQuaternion bquat(iquat.X, iquat.Y, iquat.Z, iquat.W);
        btVector3 bpos(pos.X, pos.Y, pos.Z);

        centerOfMassWorldTrans.setRotation(bquat);
        centerOfMassWorldTrans.setOrigin(bpos);


	}

	///synchronizes world transform from physics to user
	///Bullet only calls the update of worldtransform for active objects
	virtual void	setWorldTransform(const btTransform& centerOfMassWorldTrans)
	{
		m_startWorldTrans = centerOfMassWorldTrans;
		m_graphicsWorldTrans = centerOfMassWorldTrans;

		const btVector3& Point = centerOfMassWorldTrans.getOrigin();
		m_node->setPosition(core::vector3df((f32)Point[0], (f32)Point[1], (f32)Point[2]));

		// Set rotation
		btVector3 EulerRotation;
		QuaternionToEuler(centerOfMassWorldTrans.getRotation(), EulerRotation);
		m_node->setRotation(core::vector3df(EulerRotation[0], EulerRotation[1], EulerRotation[2]));
	}

};


//-----------------------------------------------------------------------------
//                       _ i n i t P h y s i c s L i b r a r y
//-----------------------------------------------------------------------------
int _initPhysicsLibrary()
{
    btVector3 worldAabbMin(-1000,-1000,-1000);
    btVector3 worldAabbMax(1000,1000,1000);

    btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfig);
    btAxisSweep3* broadPhase = new btAxisSweep3(worldAabbMin,worldAabbMax);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    m_bulletWorld = new btDiscreteDynamicsWorld(dispatcher,broadPhase,solver,collisionConfig);

    m_bulletWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

    m_bulletWorld->setDebugDrawer(new DebugDraw());
    return 0;
}

//-----------------------------------------------------------------------------
//                       _ a d d P h y s i c s O b j e c t
//-----------------------------------------------------------------------------
void _addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData)
{
    struct PhysicsAttributes attr;
    scene::IMesh* mesh=0;

    switch(node->getType())
    {
    case scene::ESNT_ANIMATED_MESH:
        mesh =  static_cast<scene::IAnimatedMeshSceneNode*>(node)->getMesh();
        break;
    case scene::ESNT_MESH:
        mesh =  static_cast<scene::IMeshSceneNode*>(node)->getMesh();
        break;
    } 
    if(!mesh)
    {
        printf("Error creating physics object - Mesh is NULL for %s\n", node->getName());
        return;
    }

    // convert .irr node "UserData" to PhysicsAttributes structure
    _setPhysicsAttributes(userData, attr);

    node->OnRegisterSceneNode();
    node->updateAbsolutePosition();
    core::aabbox3d<f32> aabb = node->getBoundingBox();
    core::vector3df iExtent = aabb.getExtent();
    core::vector3df iHalfExtent = iExtent / 2.f;

    btCollisionShape* shape=0;
    btVector3 halfExtents(iHalfExtent.X, iHalfExtent.Y, iHalfExtent.Z);

    // create collision shape based on PhysicsAttributes shape
    switch(attr.Shapetype)
    {
    case stBox:
        {
            shape = new btBoxShape(halfExtents);
        }
        break;
    case stPlane:
        {
        }
        break;
    case stSphere:
        {
            shape = new btSphereShape(halfExtents.x());
        }
        break;
    case stCone:
        {
            shape = new btConeShape(halfExtents.x(), halfExtents.y());
        }
        break;
    case stCylinder:
        {
            shape = new btCylinderShape(halfExtents);
        }
        break;    
    case stConvexMesh:
        {
        }
        break;
    case stConcaveMesh:
        {
        }
        break;
    }

    if(!shape)
    {
        printf("undefined shape for: %s\n", node->getName());
        return;
    }

    // calculate local intertia for dynamic objects
    btVector3 localInertia(0,0,0);
    if (attr.mass != 0.f && attr.BodyType == btDynamic)
        shape->calculateLocalInertia(attr.mass,localInertia);

    btRigidBody* rigidBody = new btRigidBody(attr.mass, new MotionState(node), 
        shape, localInertia);
    rigidBody->setUserPointer(node);

    int cflags = rigidBody->getCollisionFlags();
    rigidBody->setCollisionFlags(0);
    if(attr.BodyType == btStatic)
        rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
    else if(attr.BodyType == btKinematic)
        rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);   

    if(attr.trigger)
    {
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
        m_triggers.push_back(rigidBody);
    }

    m_bulletWorld->addRigidBody(rigidBody);

    // collision only ?
    if(!attr.visible)
    {
        // turn off visibility
        node->setVisible(false);
    }
}

//-----------------------------------------------------------------------------
//                   _ d i s p l a y P h y s i c s D e b u g
//-----------------------------------------------------------------------------
void _displayPhysicsDebug()
{
}

//-----------------------------------------------------------------------------
//                               _ j u m p 
//-----------------------------------------------------------------------------
void _jump()
{
}

//-----------------------------------------------------------------------------
//                        _ s t e p S i m u l a t i o n
//-----------------------------------------------------------------------------
void _stepSimulation(irr::u32 deltaMS, bool debug)
{
    m_bulletWorld->stepSimulation(deltaMS*0.001f);

    if(debug && m_debugNode)
    {
        m_debugNode->reset();
        m_bulletWorld->debugDrawWorld();
    }
}

#endif
