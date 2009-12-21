#include "main.h"

#ifdef USE_BULLET

static btDefaultCollisionConfiguration* collisionConfig = 0;
static btCollisionDispatcher* dispatcher = 0;
static btAxisSweep3* broadPhase = = 0;
static btSequentialImpulseConstraintSolver* solver = 0;
static btDiscreteDynamicsWorld* m_bulletWorld=0;

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

    _setPhysicsAttributes(userData, attr);

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
//                        _ s t e p S i m u l a t i o n
//-----------------------------------------------------------------------------
void _stepSimulation(irr::u32 deltaMS)
{
}

#endif
