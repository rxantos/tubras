//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "main.h"

#ifdef USE_IRR
static ISceneCollisionManager* m_collisionManager=0;
static IMetaTriangleSelector* m_world=0;
static IMetaTriangleSelector* m_triggers=0;
static ISceneNodeAnimatorCollisionResponse* m_character=0;
static bool m_debug=false;

extern IrrlichtDevice*      m_device;
extern IVideoDriver*        m_videoDriver;
extern ISceneManager*       m_sceneManager;
extern IFileSystem*         m_fileSystem;
extern IEventReceiver*      m_eventReceiver;
extern IGUIEnvironment*     m_gui;
extern ICameraSceneNode*    m_camera;
extern ISceneNodeAnimatorCameraFPS* m_fpsAnimator;
extern f32                  m_moveSpeed;
extern f32                  m_jumpSpeed;
extern vector3df            m_gravity;


//-----------------------------------------------------------------------------
//                       _ i n i t P h y s i c s L i b r a r y
//-----------------------------------------------------------------------------
int _initPhysicsLibrary()
{
    vector3df ellipsoid(2,5,2);

    m_collisionManager = m_sceneManager->getSceneCollisionManager();
    m_world = m_sceneManager->createMetaTriangleSelector();
    m_character =  m_sceneManager->createCollisionResponseAnimator(m_world, m_camera, ellipsoid, m_gravity);
    m_camera->addAnimator(m_character);

    // later we will test for collisions against all geometry added to m_triggers.
    m_triggers = m_sceneManager->createMetaTriangleSelector();


    // set default "character" (response animator) size
    m_character->setEllipsoidRadius(vector3df(1.f, 2.f, 1.f));
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

    irr::scene::ITriangleSelector* selector = m_sceneManager->createTriangleSelector(mesh, node);
    if(!attr.sensor)
        m_world->addTriangleSelector(selector);
    else
        m_triggers->addTriangleSelector(selector);

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
    m_debug = value;
}

//-----------------------------------------------------------------------------
//                            _ s e t G r a v i t y
//-----------------------------------------------------------------------------
void _setGravity(f32 value)
{
    m_gravity.Y = value;
    if(m_character)
        m_character->setGravity(m_gravity);
}

//-----------------------------------------------------------------------------
//                         _ s e t J u m p S p e e d
//-----------------------------------------------------------------------------
void _setJumpSpeed(f32 jumpSpeed)
{
    m_jumpSpeed = jumpSpeed;
}

//-----------------------------------------------------------------------------
//                     _ s e t M a x J u m p H e i g h t
//-----------------------------------------------------------------------------
void _setMaxJumpHeight(f32 maxJumpHeight)
{
    
}

//-----------------------------------------------------------------------------
//                                _ j u m p
//-----------------------------------------------------------------------------
void _jump()
{
    if(!m_character->isFalling())
        m_character->jump(m_jumpSpeed);
}

//-----------------------------------------------------------------------------
//                                _ c a n J u m p
//-----------------------------------------------------------------------------
bool _canJump()
{
    return !m_character->isFalling();
}

//-----------------------------------------------------------------------------
//                                _w a r p
//-----------------------------------------------------------------------------
void _warp(vector3df pos)
{
    m_camera->setPosition(pos);
    m_camera->updateAbsolutePosition();
}

//-----------------------------------------------------------------------------
//                   _ d i s p l a y P h y s i c s D e b u g
//-----------------------------------------------------------------------------
void _displayPhysicsDebug()
{
    irr::core::triangle3df* tris, *tri;
    core::matrix4 transform;
    video::IVideoDriver* driver = m_sceneManager->getVideoDriver();
    s32 outCount;
    s32 tcount  = m_world->getTriangleCount();
    bool matSet=false;

    irr::video::SMaterial mat;

    mat.Wireframe = false;
    mat.Lighting = false;

    // collision (green)
    if(tcount)
    {
        driver->setMaterial(mat);
        matSet = true;
        tri = 
        tris = (irr::core::triangle3df*) malloc(sizeof(irr::core::triangle3df) * tcount);
        m_world->getTriangles(tris, tcount, outCount, &transform);
        video::SColor color(255, 0, 255, 0);

        for(int i=0; i<outCount; i++)
        {            
            driver->draw3DLine(tri->pointA, tri->pointB, color);
            driver->draw3DLine(tri->pointB, tri->pointC, color);
            driver->draw3DLine(tri->pointA, tri->pointC, color);
            ++tri;
        }
        free(tris);
    }

    // triggers (yellow)
    tcount  = m_triggers->getTriangleCount();
    if(!tcount)
        return;

    if(!matSet)
        driver->setMaterial(mat);
    tri = 
    tris = (irr::core::triangle3df*) malloc(sizeof(irr::core::triangle3df) * tcount);
    m_triggers->getTriangles(tris, tcount, outCount);
    video::SColor color(255, 255, 255, 0);

    for(int i=0; i<outCount; i++)
    {
        driver->draw3DLine(tri->pointA, tri->pointB, color);
        driver->draw3DLine(tri->pointB, tri->pointC, color);
        driver->draw3DLine(tri->pointA, tri->pointC, color);
        ++tri;
    }
    free(tris);
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
void _stepSimulation(irr::u32 deltaMS)
{
    static bool firstUpdate=true;
    static core::vector3df lastPosition;
    static scene::ISceneNode* activeTrigger=0;

    // check for collision against "trigger" geometry
    scene::ISceneNode* node=0;
    core::vector3df directionAndSpeed;
    core::triangle3df triout;
    core::vector3df hitPosition;
    bool falling;
    core::vector3df currentPosition = m_sceneManager->getActiveCamera()->getAbsolutePosition();
    if(firstUpdate)
    {
        lastPosition = currentPosition;
        firstUpdate = false;
    }

    directionAndSpeed.set(0.1f, 0.1f, 0.f); // ...
    lastPosition  = currentPosition;

    m_collisionManager->getCollisionResultPosition(
        m_triggers, 
        currentPosition,
        m_character->getEllipsoidRadius(),
        directionAndSpeed,
        triout,
        hitPosition,
        falling,
        node);

    // hit?
    if(node)
    {
        if(node != activeTrigger)
        {
            // enter event
            SEvent event;
            event.UserEvent.UserData1 = TRIGGER_ENTER;
            event.UserEvent.UserData2 = (s32)node;
            m_sceneManager->postEventFromUser(event);
            activeTrigger = (scene::ISceneNode*) node;
        }
    }
    else if(activeTrigger)  // no collisions and previous = exit
    {
        // exit event
        SEvent event;
        event.UserEvent.UserData1 = TRIGGER_EXIT;
        event.UserEvent.UserData2 = (s32)activeTrigger;
        m_sceneManager->postEventFromUser(event);
        activeTrigger = 0;
    }

    if(m_debug)
        _displayPhysicsDebug();

}
#endif