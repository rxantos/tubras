#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ios>
#include "irrlicht.h"

// define one of the following
// #define USE_BULLET
// #define USE_IRRPHYSX
#define USE_IRR         // collision/triggers only - no dynamics.

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

typedef rect<s32> rectd;
typedef std::ostringstream StrStream;

// collision/physics library dependent variables
#ifdef USE_BULLET
#elseif USE_IRRPHYSX
#else // Irrlicht
static ISceneCollisionManager* m_collisionManager=0;
static IMetaTriangleSelector* m_world=0;
static IMetaTriangleSelector* m_triggers=0;
static ISceneNodeAnimatorCollisionResponse* m_character=0;
#endif

#define WINDOW_SIZE_X       800
#define WINDOW_SIZE_Y       600
#define DEVICE_BPP          24

enum EBodyType {btStatic, btDynamic, btKinematic, btSoft};
enum EShapeType {stBox, stPlane, stSphere, stCone, stCylinder, stConvexMesh, stConcaveMesh};
struct PhysicsAttributes
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


static IrrlichtDevice*      m_device;
static IVideoDriver*        m_videoDriver;
static ISceneManager*       m_sceneManager;
static IFileSystem*         m_fileSystem;
static IEventReceiver*      m_eventReceiver;
static IGUIEnvironment*     m_gui;
static IGUIFont*            m_defaultFont=0;
static IGUIFont*            m_monoFont=0;
static ICameraSceneNode*    m_camera;
static bool                 m_running=true;
static bool                 m_displayPhysicsDebug=false;
static int                  m_capNumber=1;

static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 

void _addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData);

//-----------------------------------------------------------------------------
//                             E v e n t R e c e i v e r
//-----------------------------------------------------------------------------
class EventReceiver : public IEventReceiver
{
    bool OnEvent(const SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            printf("Key: %d, down: %d\n", event.KeyInput.Key, event.KeyInput.PressedDown);
            if( !event.KeyInput.PressedDown ) // key up?
            {
                switch(event.KeyInput.Key)
                {
                case KEY_ESCAPE:
                    m_running = false;
                    return true;
                case KEY_SNAPSHOT:
                    {
                        IImage* image = m_videoDriver->createScreenShot();
                        char buf[32];

                        sprintf(buf,"cap%.2d.png",m_capNumber++);

                        m_videoDriver->writeImageToFile(image,buf);

                        image->drop();
                        break;
                    }
                default:
                    break;
                }

            }
            return false;
    }

public:
    bool suppressEvents;
    EventReceiver() : IEventReceiver() {}

};

//-----------------------------------------------------------------------------
//                       U s e r D a t a S e r i a l i z e r
//-----------------------------------------------------------------------------
class UserDataSerializer : public ISceneUserDataSerializer
{
public:
    void OnCreateNode(ISceneNode* node) {}
	
    //-------------------------------------------------------------------------
    //                        O n R e a d U s e r D a t a
    //-------------------------------------------------------------------------
	void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
    {
        stringc sname = forSceneNode->getName();
        static bool physicsEnabled = false;

        // save the root (scene) attributes.
        if(sname == "root")
        {
            physicsEnabled = userData->getAttributeAsBool("Physics.Enabled");
            //
            // turn gravity on
            //
            if(physicsEnabled)
            {
                f32 gravity=-9.8f;
                if(userData->existsAttribute("Gravity"))
                    gravity = userData->getAttributeAsFloat("Gravity");
                //m_physicsManager.setGravity(gravity);
            }

            return;
        }

        ESCENE_NODE_TYPE type = forSceneNode->getType();
        if(type == ESNT_MESH)
        {
            IMeshSceneNode* mnode = reinterpret_cast<IMeshSceneNode*>(forSceneNode);
            if(physicsEnabled)
            {
                _addPhysicsObject(mnode, userData);
            }

            if(mnode && userData->existsAttribute("HWHint") &&
                !userData->getAttributeAsBool("Physics.Ghost"))
            {
                E_HARDWARE_MAPPING  mapping=EHM_NEVER;
                E_BUFFER_TYPE buffertype=EBT_NONE;

                IMesh* mesh = mnode->getMesh();

                stringc smapping = userData->getAttributeAsString("HWHint");
                if(smapping == "static")
                    mapping = EHM_STATIC;
                else if(smapping == "dynamic")
                    mapping = EHM_DYNAMIC;
                else if(smapping == "stream")
                    mapping = EHM_STREAM;

                stringc sbuffertype = userData->getAttributeAsString("HWType");
                if(sbuffertype == "vertex")
                    buffertype = EBT_VERTEX;
                else if(sbuffertype == "index")
                    buffertype = EBT_INDEX;
                else if(sbuffertype == "vertexindex")
                    buffertype = EBT_VERTEX_AND_INDEX;

                if((mapping != EHM_NEVER) && (buffertype != EBT_NONE))
                    mesh->setHardwareMappingHint(mapping, buffertype);
            }
        }
        else if(type == ESNT_CAMERA)
        {
            /*
            PCamCharInfo    pci = new CamCharInfo;
            pci->camera = reinterpret_cast<ICameraSceneNode*>(forSceneNode);
            pci->width = getConfig()->getFloat("physics.characterWidth", 1.f);
            pci->height = getConfig()->getFloat("physics.characterHeight", 2.f);
            pci->stepHeight = getConfig()->getFloat("physics.characterStepHeight", 0.35f);
            pci->jumpSpeed = getConfig()->getFloat("physics.characterJumpSpeed", 0.3f);

            if(userData->existsAttribute("Character.Width"))
                pci->width = userData->getAttributeAsFloat("Character.Width");
            if(userData->existsAttribute("Character.Height"))
                pci->height = userData->getAttributeAsFloat("Character.Height");
            if(userData->existsAttribute("Character.JumpSpeed"))
                pci->jumpSpeed = userData->getAttributeAsFloat("Character.JumpSpeed");
            if(userData->existsAttribute("Character.StepHeight"))
                pci->stepHeight = userData->getAttributeAsFloat("Character.StepHeight");
            m_cameras.push_back(pci);
            */

        }

    }

	io::IAttributes* createUserData(ISceneNode* forSceneNode) { return 0;}

};

//-----------------------------------------------------------------------------
//                           _ c r e a t e D e v i c e
//-----------------------------------------------------------------------------
static IrrlichtDevice* _createDevice()
{
    m_eventReceiver = new EventReceiver();
    SIrrlichtCreationParameters cp;
    cp.DriverType = m_driverType;
    cp.WindowSize = dimension2du(WINDOW_SIZE_X,WINDOW_SIZE_Y);
    cp.Bits = DEVICE_BPP;
    cp.Fullscreen = false;
    cp.Vsync = false;
    cp.Stencilbuffer = false;
    cp.AntiAlias = false;
    cp.EventReceiver = m_eventReceiver;
    cp.WindowId = 0;

    return createDeviceEx(cp);
}

//-----------------------------------------------------------------------------
//                   _ d i s p l a y P h y s i c s D e b u g
//-----------------------------------------------------------------------------
void _displayPhysicsDebug()
{
}

//-------------------------------------------------------------------------
//                     _ s e t P h y s i c s A t t r i b u t e s
//-------------------------------------------------------------------------
void _setPhysicsAttributes(irr::io::IAttributes* userData, struct PhysicsAttributes& attr)
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
    else if(sBodyType == "sensor")
        attr.trigger = true;
}

#ifdef USE_BULLET
//-------------------------- Bullet specific functions ------------------------
int _initPhysicsLibrary()
{
}
void _addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData)
{
}
void _stepSimulation(irr::u32 deltaMS)
{
}
#elif USE_IRRPHYSX
//-------------------------- IRRPHYSX specific functions ------------------------
int _initPhysicsLibrary()
{
}
void _addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData)
{
}
void _stepSimulation(irr::u32 deltaMS)
{
}
#else
//------------------------- Irrlicht specific functions -----------------------
//-----------------------------------------------------------------------------
//                       _ i n i t P h y s i c s L i b r a r y
//-----------------------------------------------------------------------------
int _initPhysicsLibrary()
{
    m_collisionManager = m_sceneManager->getSceneCollisionManager();

    m_world = m_sceneManager->createMetaTriangleSelector();

    vector3df ellipsoid(2,5,2);
    vector3df gravity(0,-0.1f, 0);

    m_triggers = m_sceneManager->createMetaTriangleSelector();


    m_character =   m_sceneManager->createCollisionResponseAnimator(m_world, m_camera, ellipsoid, gravity);


    // set default "character" size
    m_character->setEllipsoidRadius(vector3df(1.f, 2.f, 1.f));
    m_character->setGravity(vector3df(0.f, -9.8f, 0.f));
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
    if(!attr.trigger)
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
//                        _ s t e p S i m u l a t i o n
//-----------------------------------------------------------------------------
void _stepSimulation(irr::u32 deltaMS)
{
}
#endif


//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib") 
#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup") 
#endif
int main(int argc, char* argv[])
{
    stringc sceneDirectory, saveDir;
    irr::io::path sceneFileName;
    UserDataSerializer serializer;

    if(argc < 2)
    {
        printf("error scene file name missing:\n");
        printf("    irrbPhysics <input scene filename>\n");
        return -1;
    }

    // initialize Irrlicht
    m_device = _createDevice();
    if(!m_device)
        return -1;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();
#ifdef USE_BULLET
    m_device->setWindowCaption(L"irrb Collision/Physics example - Using Bullet");
#elif USE_IRRPHYSX
    m_device->setWindowCaption(L"irrb Collision/Physics example - Using IrrPhysx");
#else
    m_device->setWindowCaption(L"irrb Collision/Physics example - Using Irrlicht");
#endif
    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 100.0f, 100.0f);
    m_camera->setPosition(vector3df(0,10,0));

    // init physics library
    _initPhysicsLibrary();

    // load scene
    sceneFileName = argv[1];   
    sceneDirectory = m_fileSystem->getFileDir(sceneFileName);

    saveDir = m_fileSystem->getWorkingDirectory();
    m_fileSystem->changeWorkingDirectoryTo(sceneDirectory);

    m_sceneManager->loadScene(sceneFileName.c_str(), &serializer);

    m_fileSystem->changeWorkingDirectoryTo(saveDir);

    if(!m_sceneManager->getActiveCamera())
    {
    }


    ITimer* timer = m_device->getTimer();
    u32 current, last = timer->getRealTime();
    u32 delta = 0;

    while(m_device->run() && m_running)
    {
        // calc seconds since last frame
        current = timer->getRealTime();
        delta = current-last;
        last = current;

        m_videoDriver->beginScene(true, true, SColor(255,100,101,140));

        // update collision/physics simulation
        _stepSimulation(delta);

        m_sceneManager->drawAll();
        m_gui->drawAll();

        if(m_displayPhysicsDebug)
            _displayPhysicsDebug();

        m_videoDriver->endScene();
    }

    m_device->drop();
    delete m_eventReceiver;    

    return 0;
}

