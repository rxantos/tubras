//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "main.h"

typedef rect<s32> rectd;
typedef std::ostringstream StrStream;

// collision/physics library dependent variables
#ifdef USE_BULLET
#elif USE_IRRPHYSX
#else // Irrlicht
#endif

#define WINDOW_SIZE_X       800
#define WINDOW_SIZE_Y       600
#define DEVICE_BPP          24

static SKeyMap keyMap[]={
    {EKA_MOVE_FORWARD, KEY_KEY_W},
    {EKA_STRAFE_LEFT, KEY_KEY_A},
    {EKA_MOVE_BACKWARD, KEY_KEY_S},
    {EKA_STRAFE_RIGHT, KEY_KEY_D}
    //{EKA_JUMP_UP, KEY_SPACE}
};

IrrlichtDevice*     m_device=0;
IVideoDriver*       m_videoDriver=0;
ISceneManager*      m_sceneManager=0;
IFileSystem*        m_fileSystem=0;
IEventReceiver*     m_eventReceiver=0;
IGUIEnvironment*    m_gui=0;
ICameraSceneNode*   m_camera=0;
ISceneNodeAnimatorCameraFPS* m_fpsAnimator=0;
CDebugNode*         m_debugNode=0;

static bool         m_running=true;
static bool         m_displayPhysicsDebug=false;
static int          m_capNumber=1;
static int          m_renderMode=0; // 0-normal, 1-wireframe, 2-pointcloud

f32                 m_moveSpeed=0.001f;
f32                 m_jumpSpeed=.075f;
extern vector3df    m_gravity(0,-1.f, 0);

static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 

void _addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData);

//-----------------------------------------------------------------------------
//                        u p d a t e R e n d e r M o d e    
//-----------------------------------------------------------------------------
void updateRenderMode(ISceneNode* node)
{
    if(!node)
        return;

    if(node->getMaterialCount())
    {
        for(u32 idx=0;idx<node->getMaterialCount();idx++)
        {
            SMaterial& mat = node->getMaterial(idx);

            switch(m_renderMode)
            {
            case 0:
                mat.setFlag(EMF_WIREFRAME,false);
                mat.setFlag(EMF_POINTCLOUD,false);
                break;
            case 1:
                mat.setFlag(EMF_WIREFRAME,true);
                mat.setFlag(EMF_POINTCLOUD,false);
                break;
            case 2:
                mat.setFlag(EMF_WIREFRAME,false);
                mat.setFlag(EMF_POINTCLOUD,true);
                break;
            }
        }
    }

    list<ISceneNode*> children = node->getChildren();
    list<ISceneNode*>::Iterator itr = children.begin();
    while(itr != children.end())
    {
        ISceneNode* child = *itr;
        updateRenderMode(child);
        itr++;
    }
}

//-----------------------------------------------------------------------------
//                             E v e n t R e c e i v e r
//-----------------------------------------------------------------------------
class EventReceiver : public IEventReceiver
{
    bool OnEvent(const SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        {
            printf("Key: %d, down: %d\n", event.KeyInput.Key, event.KeyInput.PressedDown);
            switch(event.KeyInput.Key)
            {
            case KEY_SPACE:
                {
                    if(event.KeyInput.PressedDown)
                        _jump();
                }
                return true;
            // adjust movement speed
            case KEY_LSHIFT:
            case KEY_SHIFT:
                {   
                    if(!m_fpsAnimator)
                        break;

                    if(event.KeyInput.PressedDown)
                    {
                        m_fpsAnimator->setMoveSpeed(m_moveSpeed * 3.f);
                    }
                    else
                    {
                        m_fpsAnimator->setMoveSpeed(m_moveSpeed);
                    }
                    return true;
                }
                break;

            // cycle render mode (normal/wireframe/pointcloud)
            case KEY_F3:
                {
                    if(event.KeyInput.PressedDown)
                    {
                        ++m_renderMode;
                        if(m_renderMode > 2)
                            m_renderMode = 0;
                        updateRenderMode(m_sceneManager->getRootSceneNode());
                        return true;
                    }                
                }
                break;

            // toggle physics debug
            case KEY_F4:
                if(!event.KeyInput.PressedDown)
                {
                    m_displayPhysicsDebug = m_displayPhysicsDebug ? false : true;
                    _enablePhysicsDebug(m_displayPhysicsDebug);
                    m_debugNode->setVisible(m_displayPhysicsDebug);
                    return true;
                }
                break;

            // screen shot
            case KEY_SNAPSHOT:
                {
                    if(!event.KeyInput.PressedDown) // key up
                    {
                        IImage* image = m_videoDriver->createScreenShot();
                        char buf[32];

                        sprintf(buf,"cap%.2d.png",m_capNumber++);

                        m_videoDriver->writeImageToFile(image,buf);

                        image->drop();
                    }
                    break;
                }

            // quit the app
            case KEY_ESCAPE:
                if(!event.KeyInput.PressedDown) // key up
                    m_running = false;
                return true;
            default:
                break;
            }
        }

        return _handleEvent(event);
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
                if(userData->existsAttribute("Gravity"))
                {
                    m_gravity.Y = userData->getAttributeAsFloat("Gravity");
                    _setGravity(m_gravity.Y);
                }
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
    cp.Vsync = true;
    cp.Stencilbuffer = false;
    cp.AntiAlias = 4;
    cp.EventReceiver = m_eventReceiver;
    cp.WindowId = 0;

    return createDeviceEx(cp);
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
        attr.Shapetype = stBox;               
    }
    else if(sBodyShape.equals_ignore_case("sphere"))
    {
        attr.Shapetype = stSphere;
    }
    else if(sBodyShape.equals_ignore_case("cylinder"))
    {
        attr.Shapetype = stCylinder;
    }
    else if(sBodyShape.equals_ignore_case("cone"))
    {
        attr.Shapetype = stCone;
    }
    else if(sBodyShape.equals_ignore_case("convexmesh"))
    {
        attr.Shapetype = stConvexMesh;
    }
    else if(sBodyShape.equals_ignore_case("concavemesh"))
    {
        attr.Shapetype = stConcaveMesh;
    }

    attr.BodyType = btStatic;
    if(sBodyType == "rigid")
        attr.BodyType = btKinematic;
    else if(sBodyType == "dynamic")
        attr.BodyType = btDynamic;
    else if(sBodyType == "sensor")
        attr.trigger = true;
}

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
    m_debugNode = new CDebugNode(m_sceneManager);

    // turn hardware cursor off
    m_device->getCursorControl()->setVisible(false);

#if defined(USE_BULLET)
    m_device->setWindowCaption(L"irrb Collision/Physics example - Using Bullet");
#elif defined(USE_IRRPHYSX)
    m_device->setWindowCaption(L"irrb Collision/Physics example - Using IrrPhysx");
#else
    m_device->setWindowCaption(L"irrb Collision/Physics example - Using Irrlicht");
#endif
    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 100.0f, m_moveSpeed, -1, keyMap, 5, true, m_jumpSpeed);
    m_camera->setPosition(vector3df(0,10,0));
    m_camera->setFOV(core::PI / 2.5f);
    m_camera->setNearValue(.1f);
    m_camera->setFarValue(1000.f);

    // save off animator
    core::list<ISceneNodeAnimator*>::ConstIterator anims=m_camera->getAnimators().begin();
    while(anims != m_camera->getAnimators().end())
    {
        if ((*anims)->getType() == ESNAT_CAMERA_FPS)
        {
            m_fpsAnimator = (ISceneNodeAnimatorCameraFPS*)*anims;
            break;
        }
        ++anims;
    }

    // init physics library
    _initPhysicsLibrary();

    // load scene
    sceneFileName = argv[1];   
    sceneDirectory = m_fileSystem->getFileDir(sceneFileName);

    saveDir = m_fileSystem->getWorkingDirectory();
    m_fileSystem->changeWorkingDirectoryTo(sceneDirectory);

    m_sceneManager->loadScene(sceneFileName.c_str(), &serializer);

    m_fileSystem->changeWorkingDirectoryTo(saveDir);

    // if the scene also contained a camera, set the active
    // camera to our fps camera and update the fps pos/rot.
    if(m_camera && (m_camera != m_sceneManager->getActiveCamera()))
    {
        ICameraSceneNode* anode = m_sceneManager->getActiveCamera();

        m_camera->setPosition(anode->getPosition());
        m_camera->setRotation(anode->getRotation());
        m_sceneManager->setActiveCamera(m_camera);
        _teleport(m_camera->getPosition());
    }

    ITimer* timer = m_device->getTimer();
    u32 current, last = timer->getRealTime();
    u32 delta = 0;

    while(m_device->run() && m_running)
    {
        m_videoDriver->beginScene(true, true, SColor(255,100,101,140));

        // calc milliseconds since last frame
        current = timer->getRealTime();
        delta = current-last;
        last = current;

        // update collision/physics simulation
        _stepSimulation(delta);

        m_sceneManager->drawAll();

        m_gui->drawAll();

        m_videoDriver->endScene();
    }

    m_device->drop();
    delete m_eventReceiver;    

    return 0;
}
