#include "CPhysicsManager.h"

namespace irr 
{
    void CPhysicsManager::setAttributes(irr::io::IAttributes* userData, struct CPhysicsAttributes& attr)
    {
        EShapeType bodyShape=stConcaveMesh;
        EBodyType bodyType=btStatic;

        core::stringc sBodyType = userData->getAttributeAsString("Physics.BodyType");
        if(sBodyType == "none")
            return;

        core::stringc sBodyShape = userData->getAttributeAsString("Physics.BodyShape");
        attr.visible = true;
        if(userData->existsAttribute("Physics.Visible"))
            attr.visible = userData->getAttributeAsBool("Physics.Visible");

        attr.ghost = userData->getAttributeAsBool("Physics.Ghost");  
        attr.trigger = userData->getAttributeAsBool("Physics.Trigger"); // collision without restitution

        attr.mass = userData->getAttributeAsFloat("Physics.Mass");
        attr.friction = userData->getAttributeAsFloat("Physics.Friction");
        attr.restitution = userData->getAttributeAsFloat("Physics.Restitution");
        attr.radius=0.f;
        if(userData->existsAttribute("Physics.Radius"))
            attr.radius = userData->getAttributeAsFloat("Physics.Radius");

        if(sBodyShape.equals_ignore_case("box"))
        {
            bodyShape = stBox;               
        }
        else if(sBodyShape.equals_ignore_case("sphere"))
        {
            bodyShape = stSphere;
        }
        else if(sBodyShape.equals_ignore_case("cylinder"))
        {
            bodyShape = stCylinder;
        }
        else if(sBodyShape.equals_ignore_case("cone"))
        {
            bodyShape = stCone;
        }
        else if(sBodyShape.equals_ignore_case("convexmesh"))
        {
            bodyShape = stConvexMesh;
        }
        else if(sBodyShape.equals_ignore_case("concavemesh"))
        {
            bodyShape = stConcaveMesh;
        }

        if(sBodyType == "rigid")
            bodyType = btKinematic;
        else if(sBodyType == "dynamic")
            bodyType = btDynamic;

    }

#ifdef USE_BULLET
    //-------------------------------------------------------------------------
    //               a d d P h y s i c s O b j e c t - (Bullet)
    //-------------------------------------------------------------------------
    void CPhysicsManager::addPhysicsObject(io::IAttributes* attr,
        btDiscreteDynamicsWorld* dynamicWorld, 
        irr::scene::IMeshSceneNode* node)
    {
        struct CPhysicsAttributes attr;
        IMesh* mesh=0;

        switch(snode->getType())
        {
            case ESNT_ANIMATED_MESH:
                mesh =  static_cast<IAnimatedMeshSceneNode*>(node)->getMesh();
                break;
            case ESNT_MESH:
                mesh =  static_cast<IMeshSceneNode*>(node)->getMesh();
                break;
        } 
        if(!mesh)
        {
            printf("Error creating physics object - Mesh is NULL for %s\n", node->getName());
            return;
        }
        setAttributes(userData, attr);
    }
#elif USE_IRRPHYSX
    //-------------------------------------------------------------------------
    //               a d d P h y s i c s O b j e c t - (IrrPhysx)
    //-------------------------------------------------------------------------
    void CPhysicsManager::addPhysicsObject(irr::io::IAttributes* userData,
        IPhysxManager* physxManager,
        irr::scene::IMeshSceneNode* node)
    {
        struct CPhysicsAttributes attr;
        IMesh* mesh=0;

        switch(snode->getType())
        {
            case ESNT_ANIMATED_MESH:
                mesh =  static_cast<IAnimatedMeshSceneNode*>(node)->getMesh();
                break;
            case ESNT_MESH:
                mesh =  static_cast<IMeshSceneNode*>(node)->getMesh();
                break;
        } 
        if(!mesh)
        {
            printf("Error creating physics object - Mesh is NULL for %s\n", node->getName());
            return;
        }
        setAttributes(userData, attr);
    }
#else
    //-------------------------------------------------------------------------
    //               a d d P h y s i c s O b j e c t - (Irrlicht)
    //-------------------------------------------------------------------------
    void CPhysicsManager::addPhysicsObject(irr::io::IAttributes* userData,
        irr::scene::ISceneManager* sceneManager, 
        irr::scene::ISceneNode* node,
        irr::scene::IMetaTriangleSelector* world,
        irr::scene::IMetaTriangleSelector* triggers)
    {
        struct CPhysicsAttributes attr;
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
        setAttributes(userData, attr);

        irr::scene::ITriangleSelector* selector = sceneManager->createTriangleSelector(mesh, node);
        if(!attr.trigger)
            world->addTriangleSelector(selector);
        else
            triggers->addTriangleSelector(selector);

        // collision only ?
        if(!attr.visible)
        {
            // turn off visibility
            node->setVisible(false);
        }
    }
#endif

    //-------------------------------------------------------------------------
    //                         s t e p S i m u l a t i o n
    //-------------------------------------------------------------------------
    void CPhysicsManager::stepSimulation(irr::f32 time)
    {
    }

}
