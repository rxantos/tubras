#include "cisl.h"

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

typedef rect<f32> rectf;
typedef rect<s32> rectd;

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

static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 
isl::CISL*                  m_isl=0;

// why?...
namespace irr
{
namespace core
{
	const matrix4 IdentityMatrix(matrix4::EM4CONST_IDENTITY);
}
} // end namespace irr

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

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
            }
        }

		return false;
	}
};


//-----------------------------------------------------------------------------
//                           _ c r e a t e D e v i c e
//-----------------------------------------------------------------------------
static IrrlichtDevice* _createDevice()
{
    SIrrlichtCreationParameters cp;
    
    cp.DriverType = (irr::video::E_DRIVER_TYPE) m_isl->getInteger("video.driver", EDT_OPENGL);
    cp.WindowSize = m_isl->getDimension2di("video.windowsize");
    cp.Bits = m_isl->getInteger("video.bits", 24);
    cp.Fullscreen = m_isl->getBool("video.fullscreen", false);
    cp.Vsync = m_isl->getBool("video.vsync", false);
    cp.Stencilbuffer = m_isl->getBool("video.stencilbuffer", false);
    cp.AntiAlias = m_isl->getBool("video.antialias", false);
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
        {EKA_MOVE_FORWARD, (irr::EKEY_CODE)m_isl->getInteger("keymap.forward", KEY_UP)},
        {EKA_STRAFE_LEFT, (irr::EKEY_CODE)m_isl->getInteger("keymap.left", KEY_LEFT)},
        {EKA_MOVE_BACKWARD, (irr::EKEY_CODE)m_isl->getInteger("keymap.backward", KEY_DOWN)},
        {EKA_STRAFE_RIGHT, (irr::EKEY_CODE)m_isl->getInteger("keymap.right", KEY_RIGHT)},
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
    pnode->getMaterial(0) = m_isl->getMaterial(m_device, "floor");
    if(m_isl->isAnimatedMaterial("floor"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_isl->addAnimationRef("floor", pnode->getMaterial(0));
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

    pmesh = m_sceneManager->addHillPlaneMesh("testPlane1" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0, 25, 100));
    pnode->setRotation(vector3df(-90, 0, 0));
    //
    // this COPIES the materials and material layer parameters.  it doesn't set
    // a reference... so in order for animation (if any) to work we need to 
    // add a "ref" to the material owned by the node.  kludge, but it works
    // without having to modify the engine source.
    //
    pnode->getMaterial(0) = m_isl->getMaterial(m_device, "testPlane1");
    if(m_isl->isAnimatedMaterial("testPlane1"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_isl->addAnimationRef("testPlane1", pnode->getMaterial(0));
    }
    
    IBillboardSceneNode* bnode = m_sceneManager->addBillboardSceneNode();
    bnode->setPosition(vector3df(0,0,15));
    mat2.EmissiveColor = SColor(255, 200, 128, 128);
    bnode->getMaterial(0) = m_isl->getMaterial(m_device, "billboard1");
    
    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 
        m_isl->getFloat("options.rotateSpeed",100.0f), 
        m_isl->getFloat("options.moveSpeed",50.0f), 
        -1, &kmap[0], 4, false);

    m_camera->setPosition(vector3df(0,10,0));

    //
    // GUI element instantiation
    //
    irr::gui::IGUIElement* el = m_isl->getGUIElement(m_device, "testWindow");

}

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Missing isl script parameter.\n");
        return -1;
    }

    //
    // parse the script passed on the command line
    //
    m_isl = new isl::CISL();
    if(m_isl->parseScript(argv[1]) != isl::E_OK)
    {
        printf("Error parsing script.\n");
        return -1;
    }

    m_device = _createDevice();
    if(!m_device)
        return -1;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    irr::core::stringw caption = m_isl->getString("video.caption","testisl v0.1").c_str();
    m_device->setWindowCaption(caption.c_str());

    _createScene();

    m_device->getCursorControl()->setVisible(m_isl->getBool("options.showcursor",false));

    while(m_device->run() && m_running)
    {
        m_videoDriver->beginScene(true, true, SColor(0,200,200,200));

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();
    }

    delete m_isl;
    m_device->drop();

    return 0;
}
