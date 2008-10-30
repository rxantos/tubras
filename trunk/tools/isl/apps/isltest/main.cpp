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
CISL::CISL*                 m_isl=0;

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

#if defined(_IRR_LINUX_PLATFORM_) && defined(_IRR_USE_LINUX_DEVICE_)
    cp.IgnoreInput = true;
#endif

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
        {EKA_MOVE_FORWARD, KEY_KEY_W},
        {EKA_STRAFE_LEFT, KEY_KEY_A},
        {EKA_MOVE_BACKWARD, KEY_KEY_S},
        {EKA_STRAFE_RIGHT, KEY_KEY_D},
    };

    SMaterial mat, mat2;

    ITexture* tex = m_videoDriver->getTexture("tex/grid.tga");

    mat.setTexture(0,tex);
    mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    mat.setFlag(EMF_LIGHTING,false);
    mat.getTextureMatrix(0).setTextureScale(50.0,50.0);


    IAnimatedMesh* pmesh = m_sceneManager->addHillPlaneMesh("testHillPlane"
        ,tileSize,tileCount,&mat);
    IAnimatedMeshSceneNode* pnode;
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0,-5, 0));

    //
    // solid color using 2x2 image and "emissive"
    //
    u8* data = new u8[2 * 2 * 4]; 
    IImage* image = m_videoDriver->createImageFromData(ECF_A8R8G8B8, dimension2d<s32>(2,2), data);
    image->fill(SColor(255, 255, 255, 255));
    tex = m_videoDriver->addTexture("__WHITE2X2__",image);
    image->drop();

    SMaterial* pmat = m_isl->getMaterial(m_videoDriver,"mat1");

    mat2.MaterialType = EMT_SOLID;
    mat2.setFlag(EMF_LIGHTING, true);
    mat2.setTexture(0,tex);
    mat2.setFlag(EMF_BACK_FACE_CULLING , false);
    mat2.EmissiveColor = SColor(255, 255, 0, 255);

    tileSize.Width = 20;
    tileSize.Height = 10;
    tileCount.Width = 2;
    tileCount.Height = 2;

    pmesh = m_sceneManager->addHillPlaneMesh("testHillPlane2" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0, 15, 100));
    pnode->setRotation(vector3df(-90, 0, 0));
    pnode->getMaterial(0) = mat2;

    IBillboardSceneNode* bnode = m_sceneManager->addBillboardSceneNode();
    bnode->setPosition(vector3df(0,0,15));
    mat2.EmissiveColor = SColor(255, 200, 128, 128);
    bnode->getMaterial(0) = mat2;
    //bmat = *pmat;

    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 100.0f, 50.0f, -1, &kmap[0], 4, false);
    m_camera->setPosition(vector3df(0,10,0));

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
    m_isl = new CISL::CISL();
    if(m_isl->parseScript(argv[1]) != CISL::E_OK)
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

    _createScene();

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