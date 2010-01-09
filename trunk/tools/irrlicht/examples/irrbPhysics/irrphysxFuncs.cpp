//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "main.h"

#ifdef USE_IRRPHYSX
#include "IrrPhysx.h"
#pragma comment(lib, "IrrPhysx.lib") 


using namespace IrrPhysx;

static IPhysxManager* m_physxManager;

extern IrrlichtDevice*      m_device;
#define NUM_TEXTURES 5
c8 textures[NUM_TEXTURES][256] = {	"../media/blue.JPG",
"../media/green.JPG",
"../media/pink.JPG",
"../media/red.JPG",
"../media/yellow.JPG"  };

//-------------------------------------------------------------------------
// code taken from irrPhysx ../commoncode/ so we don't have to include
// the source files...

// A struct to hold both the physical and visual representations of an object
struct SPhysxAndNodePair {

    SPhysxAndNodePair() {
        PhysxObject = NULL;
        SceneNode = NULL;
    }

    void updateTransformation() {
        if (PhysxObject->getType() == EOT_CLOTH) { // If it's a cloth we just need to update it (for tearing purposes)
            ((IClothPhysxObject*)PhysxObject)->update();
        } else { // Otherwise we update its transformation
            core::vector3df vec;
            // Update the node's position to that of the physx object
            PhysxObject->getPosition(vec);
            SceneNode->setPosition(vec);
            // Update the node's rotation to that of the physx object
            PhysxObject->getRotation(vec);
            SceneNode->setRotation(vec);
        }
    }

    IPhysxObject* PhysxObject;
    scene::ISceneNode* SceneNode;

};

static core::array<SPhysxAndNodePair*> m_objects;

// Creates a box at the specified position, of the specified size and with the specified intial velocity (useful for throwing it)
SPhysxAndNodePair* createBox(IPhysxManager* physxManager, scene::ISceneManager* smgr, video::IVideoDriver* driver, const core::vector3df& pos, const core::vector3df& scale, f32 density, core::vector3df* initialVelocity=0) {

    SPhysxAndNodePair* pair = new SPhysxAndNodePair;
    pair->PhysxObject = physxManager->createBoxObject(pos, core::vector3df(0,0,0), scale/2.0f, density, initialVelocity);
    pair->SceneNode = smgr->addCubeSceneNode(1, 0, -1, pos, core::vector3df(0,0,0), scale);
    pair->SceneNode->setMaterialTexture(0, driver->getTexture(textures[rand()%NUM_TEXTURES]));
    pair->SceneNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

    return pair;

}

// Create a stack of boxes, with the bottom row having the specified number of boxes
void createBoxStack(IPhysxManager* physxManager, scene::ISceneManager* smgr, video::IVideoDriver* driver, core::array<SPhysxAndNodePair*>& objects, f32 stackSize, f32 density, const core::vector3df& position) {

    const core::vector3df scale(4,4,4);
    const f32 spacing = -2.0f*physxManager->getSkinWidth();
    core::vector3df pos = position + core::vector3df(0.0f, scale.Y/2.0f, 0.0f);
    f32 offset = -stackSize * (scale.X + spacing) * 0.5f;

    while (stackSize > 0) {
        for (s32 i = 0 ; i < stackSize ; ++i) {
            pos.X = offset + (f32)i * (scale.X + spacing);
            objects.push_back(createBox(physxManager, smgr, driver, pos, scale, density));
        }

        offset += scale.X / 2.0f;
        pos.Y += (scale.Y + spacing);
        stackSize--;
    }

}

// Create a tower of the specified number of boxes
void createBoxTower(IPhysxManager* physxManager, scene::ISceneManager* smgr, video::IVideoDriver* driver, core::array<SPhysxAndNodePair*>& objects, f32 towerSize, f32 density, const core::vector3df& position) {

    const core::vector3df scale(4,4,4);
    const f32 spacing = -2.0f*physxManager->getSkinWidth();
    core::vector3df pos = position + core::vector3df(0.0f, scale.Y/2.0f, 0.0f);

    while (towerSize > 0) {
        objects.push_back(createBox(physxManager, smgr, driver, pos, scale, density));
        pos.Y += (scale.Y + spacing);
        towerSize--;
    }

}

// Creates a multishape actor from the bounding boxes of the meshbuffers in the specified mesh stuck together at the specified position, with the specified intial velocity (useful for throwing it)
SPhysxAndNodePair* createMeshBoundingBox(IPhysxManager* physxManager, scene::ISceneManager* smgr, video::IVideoDriver* driver, scene::IMesh* mesh, const core::vector3df& pos, const core::vector3df& scale, f32 density, core::vector3df* initialVelocity=0) {

    SPhysxAndNodePair* pair = new SPhysxAndNodePair;

    core::array<core::aabbox3df> boxes;
    core::aabbox3df box;
    for (u32 mb = 0 ; mb < mesh->getMeshBufferCount() ; ++mb) {
        scene::IMeshBuffer* buffer = mesh->getMeshBuffer(mb);
        core::aabbox3df box = buffer->getBoundingBox();
        box.MinEdge /= 2.0f;
        box.MinEdge *= scale;
        box.MaxEdge /= 2.0f;
        box.MaxEdge *= scale;
        boxes.push_back(box);
    }

    pair->PhysxObject = physxManager->createMultiShapeObject(boxes, core::array<SSphereDesc>(), core::array<SCapsuleDesc>(), pos, core::vector3df(0,0,0), density, initialVelocity);
    pair->SceneNode = smgr->addMeshSceneNode(mesh, 0, -1, pos, core::vector3df(0,0,0), scale);
    pair->SceneNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true); 

    return pair;

}

// Create a stack of meshes, with the bottom row having the specified number of cubes
void createMeshStack(IPhysxManager* physxManager, scene::ISceneManager* smgr, video::IVideoDriver* driver, core::array<SPhysxAndNodePair*>& objects, scene::IMesh* mesh, f32 stackSize, f32 density) {

    const core::vector3df meshSize = mesh->getBoundingBox().getExtent();
    const f32 spacing = -2.0f*physxManager->getSkinWidth();
    core::vector3df pos(0.0f, meshSize.Y/2.0f, 0.0f);
    f32 offset = -stackSize * (meshSize.X + spacing) * 0.5f;

    while (stackSize > 0) {
        for (s32 i = 0 ; i < stackSize ; ++i) {
            pos.X = offset + (f32)i * (meshSize.X + spacing);
            objects.push_back(createMeshBoundingBox(physxManager, smgr, driver, mesh, pos, core::vector3df(1,1,1), density));
        }

        offset += meshSize.X / 2.0f;
        pos.Y += (meshSize.Y + spacing);
        stackSize--;
    }

}

// Creates a sphere at the specified position, of the specified size and with the specified intial velocity (useful for throwing it)
SPhysxAndNodePair* createSphere(IPhysxManager* physxManager, scene::ISceneManager* smgr, video::IVideoDriver* driver, const core::vector3df& pos, f32 radius, f32 density, core::vector3df* initialVelocity) {

    SPhysxAndNodePair* pair = new SPhysxAndNodePair;
    pair->PhysxObject = physxManager->createSphereObject(pos, core::vector3df(0,0,0), radius, density, initialVelocity);
    pair->SceneNode = smgr->addSphereSceneNode(radius, 12, 0, -1, pos, core::vector3df(0, 0, 0), core::vector3df(1.0f, 1.0f, 1.0f));
    pair->SceneNode->setMaterialTexture(0, driver->getTexture(textures[rand()%NUM_TEXTURES]));
    pair->SceneNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true); 

    return pair;

}

// Create a sphere from the camera with an intial velocity to throw it into the scene
SPhysxAndNodePair* createSphereFromCamera(IPhysxManager* physxManager, scene::ISceneManager* smgr, video::IVideoDriver* driver, scene::ICameraSceneNode* camera, f32 radius, f32 density) {

    core::vector3df t = camera->getPosition();
    core::vector3df vel = camera->getTarget() - camera->getPosition();
    vel.normalize();
    vel*=200.0f;

    return createSphere(physxManager, smgr, driver, t, radius, density, &vel);

}

// Add a plane at the specified distance from the origin and the specified normal
void addPlane(IPhysxManager* physxManager, scene::ISceneManager* smgr, f32 d, const core::vector3df& normal) {

    // Add a plane with the specified parameters
    physxManager->createPlaneObject(d, normal);
    // Add a grid scene node to visually represent the floor
    /*
    scene::CGridSceneNode* grid = new scene::CGridSceneNode(smgr->getRootSceneNode(), smgr, -1, 25, 1000, video::SColor(255,0,200,0), 0);
    grid->setPosition(normal * d);
    grid->drop();
    */

}
//-----------------------------------------------------------------------------
//                       _ i n i t P h y s i c s L i b r a r y
//-----------------------------------------------------------------------------
int _initPhysicsLibrary()
{
    SSceneDesc sceneDesc;
    m_physxManager = createPhysxManager(m_device, sceneDesc);

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
//                       _ e n a b l e P h y s i c s D e b u g 
//-----------------------------------------------------------------------------
void _enablePhysicsDebug(bool value)
{
}

//-----------------------------------------------------------------------------
//                                _ j u m p
//-----------------------------------------------------------------------------
void _jump()
{
}

//-----------------------------------------------------------------------------
//                          _ h a n d l e E v e n t
//-----------------------------------------------------------------------------
bool _handleEvent(const SEvent& event)
{
    return false;
}

//-----------------------------------------------------------------------------
//                        _ s t e p S i m u l a t i o n
//-----------------------------------------------------------------------------
void _stepSimulation(irr::u32 deltaMS, bool debug)
{
}
#endif
