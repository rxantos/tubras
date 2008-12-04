#include "clsl.h"
using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

typedef rect<f32> rectf;
typedef rect<s32> rectd;

enum RENDERMODE {rmNormal, rmWire};

#define DEVICE_BPP          24

#define ID_DBGCONSOLE       101
#define ID_ALPHA            102
#define ID_MAGNITUDE        103

static IrrlichtDevice*      m_device;
static IVideoDriver*        m_videoDriver;
static ISceneManager*       m_sceneManager;
static IFileSystem*         m_fileSystem;
static IGUIEnvironment*     m_gui;
static ICameraSceneNode*    m_camera;
static bool                 m_running=true;
static int                  m_capNumber=1;
static void*                m_windowHandle;
static u32                  m_display;
static RENDERMODE           m_renderMode = rmNormal;

static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 
lsl::CLSL*                  m_lsl=0;


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup")
#endif


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
            case rmNormal:
                mat.setFlag(EMF_WIREFRAME,false);
                mat.setFlag(EMF_POINTCLOUD,false);
                break;
            case rmWire:
                mat.setFlag(EMF_WIREFRAME,true);
                mat.setFlag(EMF_POINTCLOUD,false);
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

void toggleRenderMode()
{
    m_renderMode = m_renderMode == rmNormal ? rmWire : rmNormal;
    updateRenderMode(m_sceneManager->getRootSceneNode());
}

class EventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
        if(event.EventType == EET_KEY_INPUT_EVENT)
        {
            switch(event.KeyInput.Key)
            {
            case KEY_ESCAPE:
                m_running = false;
                return true;
            case KEY_F3:
                if(event.KeyInput.PressedDown)
                {
                    toggleRenderMode();
                    return true;
                }
            }

        }

		return false;
	}
};

class ScriptErrorHandler : public lsl::ILSLErrorHandler
{
public:
    int handleError(irr::core::stringc fileName, int line, int code, irr::core::stringc errMessage)
    {
        printf("CLSL Error (%d), line: %d, message: %s\n",code, line, errMessage.c_str());
        return 0;
    }
};

//-----------------------------------------------------------------------------
//                           _ c r e a t e D e v i c e
//-----------------------------------------------------------------------------
static IrrlichtDevice* _createDevice()
{
    SIrrlichtCreationParameters cp;
    
    cp.DriverType = (irr::video::E_DRIVER_TYPE) m_lsl->getInteger("video.driver", EDT_OPENGL);
    cp.WindowSize = m_lsl->getDimension2di("video.windowsize");
    cp.Bits = m_lsl->getInteger("video.bits", 24);
    cp.Fullscreen = m_lsl->getBool("video.fullscreen", false);
    cp.Vsync = m_lsl->getBool("video.vsync", false);
    cp.Stencilbuffer = m_lsl->getBool("video.stencilbuffer", false);
    cp.AntiAlias = m_lsl->getBool("video.antialias", false);
    cp.EventReceiver = new EventReceiver();
    cp.WindowId = 0;

    return createDeviceEx(cp);
}

//-----------------------------------------------------------------------------
//                           _ c r e a t e S c e n e
//-----------------------------------------------------------------------------
static void _createScene()
{
    dimension2df tileSize(50,50);
    dimension2d<u32> tileCount(6,6);
    SKeyMap kmap[] = 
    {
        {EKA_MOVE_FORWARD, (irr::EKEY_CODE)m_lsl->getInteger("keymap.forward", KEY_UP)},
        {EKA_STRAFE_LEFT, (irr::EKEY_CODE)m_lsl->getInteger("keymap.left", KEY_LEFT)},
        {EKA_MOVE_BACKWARD, (irr::EKEY_CODE)m_lsl->getInteger("keymap.backward", KEY_DOWN)},
        {EKA_STRAFE_RIGHT, (irr::EKEY_CODE)m_lsl->getInteger("keymap.right", KEY_RIGHT)},
    };

    SMaterial mat, mat2;
    
    IAnimatedMesh* pmesh = m_sceneManager->addHillPlaneMesh("floorPlane"
        ,tileSize,tileCount);
    IAnimatedMeshSceneNode* pnode;
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0,-5, 0));
    //
    // this COPIES the materials and material layer parameters.  it doesn't set
    // a reference... so in order for animation (if any) to work we need to 
    // add a "ref" to the material owned by the node.  kludge, but it works
    // without having to modify the engine source.
    //
    if(m_lsl->getMaterial(m_device, "floor",pnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("floor"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("floor", pnode->getMaterial(0));
    }

    //
    // solid color using 2x2 image and "emissive"
    //
    u8* data = new u8[2 * 2 * 4]; 
    IImage* image = m_videoDriver->createImageFromData(ECF_A8R8G8B8, dimension2d<s32>(2,2), data);
    image->fill(SColor(255, 255, 255, 255));
    ITexture* tex = m_videoDriver->addTexture("__WHITE2X2__",image);
    image->drop();

    mat2.MaterialType = EMT_SOLID;
    mat2.setFlag(EMF_LIGHTING, true);
    mat2.setTexture(0,tex);
    mat2.setFlag(EMF_BACK_FACE_CULLING , false);
    mat2.EmissiveColor = SColor(255, 255, 0, 255);

    tileSize.Width = 30;
    tileSize.Height = 30;
    tileCount.Width = 2;
    tileCount.Height = 2;

    //
    // plane that contains a semi-transparent red pattern
    //
    pmesh = m_sceneManager->addHillPlaneMesh("redpattern" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0, 25, 100));
    pnode->setRotation(vector3df(-90, 0, 0));
    //
    // this COPIES the materials and material layer parameters.  it doesn't set
    // a reference... so in order for animation (if any) to work we need to 
    // add a "ref" to the material owned by the node.  kludge, but it works
    // without having to modify the engine source.
    //
    if(m_lsl->getMaterial(m_device, "redpattern",pnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("redpattern"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("redpattern", pnode->getMaterial(0));
    }

    //
    // cube
    //
    IMeshSceneNode* cnode = m_sceneManager->addCubeSceneNode();
    cnode->setScale(core::vector3df(10.0,10.0,10.0));
    cnode->setPosition(vector3df(0, -60, 0));
    if(m_lsl->getMaterial(m_device, "cubemat",cnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("cubemat"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("cubemat", cnode->getMaterial(0));
    }

    //
    // left/right spheres
    //
    cnode = m_sceneManager->addSphereSceneNode();
    cnode->setScale(core::vector3df(2.0,2.0,2.0));
    cnode->setPosition(vector3df(-90, 40, 100));
    if(m_lsl->getMaterial(m_device, "leftSphere",cnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("leftSphere"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("leftSphere", cnode->getMaterial(0));
    }

    cnode = m_sceneManager->addSphereSceneNode();
    cnode->setScale(core::vector3df(2.0,2.0,2.0));
    cnode->setPosition(vector3df(90, 40, 100));
    if(m_lsl->getMaterial(m_device, "rightSphere",cnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("rightSphere"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("rightSphere", cnode->getMaterial(0));
    }

    //
    // left/right panel backgrounds
    //
    tileSize.Width = 20;
    tileSize.Height = 20;
    tileCount.Width = 1;
    tileCount.Height = 1;
    pmesh = m_sceneManager->addHillPlaneMesh("leftPanelBG" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(-45, 25, 100));
    pnode->setRotation(vector3df(-90, -45, 0));
 
    if(m_lsl->getMaterial(m_device, "leftPanelBG",pnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("leftPanelBG"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("leftPanelBG", pnode->getMaterial(0));
    }

    pmesh = m_sceneManager->addHillPlaneMesh("rightPanelBG" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(45, 25, 100));
    pnode->setRotation(vector3df(-90, 45, 0));
 
    if(m_lsl->getMaterial(m_device, "rightPanelBG",pnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("rightPanelBG"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("rightPanelBG", pnode->getMaterial(0));
    }

    //
    // left/right panel foregrounds
    //
    tileSize.Width = 15;
    tileSize.Height = 15;
    pmesh = m_sceneManager->addHillPlaneMesh("leftPanelFG" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(-44.6f, 25.f, 99.98f));
    pnode->setRotation(vector3df(-90, -45, 0));
 
    if(m_lsl->getMaterial(m_device, "leftPanelFG",pnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("leftPanelFG"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("leftPanelFG", pnode->getMaterial(0));
    }


    pmesh = m_sceneManager->addHillPlaneMesh("rightPanelFG" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(44.6f, 25.f, 99.98f));
    pnode->setRotation(vector3df(-90.f, 45.f, 0.f));
 
    if(m_lsl->getMaterial(m_device, "rightPanelFG",pnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("rightPanelFG"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("rightPanelFG", pnode->getMaterial(0));
    }

    //
    // leaf billboard
    //
    IBillboardSceneNode* bnode = m_sceneManager->addBillboardSceneNode();
    bnode->setSize(core::dimension2d<f32>(28, 28));
    bnode->setPosition(vector3df(0,8,15));
    mat2.EmissiveColor = SColor(255, 200, 128, 128);
    if(m_lsl->getMaterial(m_device, "leafbillboard",bnode->getMaterial(0)) &&
       m_lsl->isAnimatedMaterial("leafbillboard"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("leafbillboard", bnode->getMaterial(0));
    }

    //
    // "the world is mine" background & foreground
    //
    tileSize.Width = 1;
    tileSize.Height = 1;
    tileCount.Width = 140;
    tileCount.Height = 40;
    pmesh = m_sceneManager->addHillPlaneMesh("twimbg" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0, 25, 150));
    pnode->setRotation(vector3df(-90, 0, 0));
    m_lsl->getMaterial(m_device, "twimbg",pnode->getMaterial(0));

    pmesh = m_sceneManager->addHillPlaneMesh("twimfg" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0, 25, 149.98f));
    pnode->setRotation(vector3df(-90, 0, 0));
    pnode->setScale(vector3df(0.96f, 1.f, 1.f));
    m_lsl->getMaterial(m_device, "twimfg",pnode->getMaterial(0));
    if(m_lsl->isAnimatedMaterial("twimfg"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_lsl->addAnimationRef("twimfg", pnode->getMaterial(0));
    }

    
    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 
        m_lsl->getFloat("options.rotateSpeed",100.0f), 
        m_lsl->getFloat("options.moveSpeed",50.0f), 
        -1, &kmap[0], 4, false);

    m_camera->setPosition(vector3df(0,10,0));


    /*
    IGUIStaticText* stext = m_gui->addStaticText(L" F3 - Toggle Wire",
        rect<s32>(5, 5, 100, 25),false,false,0,false);
    stext->setOverrideColor(SColor(255,255,255,255));
    */

    //
    // GUI element instantiation
    //
    irr::gui::IGUIElement* el = m_lsl->getGUIElement(m_device, "helpText");
    // make this scriptable
    ((IGUIStaticText*)el)->setOverrideColor(SColor(255, 255, 255, 255));

    el = m_lsl->getGUIElement(m_device, "testWindow");
}

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	int lastFPS=-1, fps;
    irr::core::stringc sname = "lsltest.lsl";
    ScriptErrorHandler ehandler;

    if(argc >= 2)
    {
        sname = argv[1];
    }

    //
    // parse the script passed on the command line
    //
    m_lsl = new lsl::CLSL();
    if(m_lsl->loadScript(sname, false, false, &ehandler) != lsl::E_OK)
    {
        printf("Error loading script.\n");
        return -1;
    }

    m_device = _createDevice();
    if(!m_device)
        return -1;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    irr::core::stringw caption = m_lsl->getString("video.caption","testlsl v0.1").c_str();
    m_device->setWindowCaption(caption.c_str());

    _createScene();

    m_device->getCursorControl()->setVisible(m_lsl->getBool("options.showCursor",false));

    SColor bgcolor = m_lsl->getColor("video.bgcolor");

    while(m_device->run() && m_running)
    {
        m_videoDriver->beginScene(true, true, bgcolor);

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();

		fps = m_videoDriver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = caption;
			str += " - FPS:";
			str += fps;

			m_device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}

    }

    delete m_lsl;
    m_device->drop();
    return 0;
}
