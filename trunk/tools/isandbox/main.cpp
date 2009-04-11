#include "irrlicht.h"
#include "CGUISceneNode.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#include <assert.h>

#define WINDOW_SIZE_X       800
#define WINDOW_SIZE_Y       600
#define DEVICE_BPP          24

static IrrlichtDevice*      m_device;
static IVideoDriver*        m_videoDriver;
static ISceneManager*       m_sceneManager;
static IFileSystem*         m_fileSystem;
static IEventReceiver*      m_eventReceiver;
static IGUIEnvironment*     m_gui;
static IGUIFont*            m_defaultFont=0;
static IGUIFont*            m_monoFont=0;
static ICameraSceneNode*    m_camera;
static IMetaTriangleSelector* m_world;
static ISceneNodeAnimatorCollisionResponse* m_collisionResponse;
static bool                 m_running=true;
static int                  m_capNumber=1;

static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 

IGUIEnvironment* getGUI()
{
    return m_gui;
}

void logTestString(irr::core::stringc str)
{
    printf(str.c_str());
}

//-----------------------------------------------------------------------------
//                             E v e n t R e c e i v er
//-----------------------------------------------------------------------------
// used to suppress/enable engine debug messages
class EventReceiver : public IEventReceiver
{
    bool OnEvent(const SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
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
//                               _ i n i t
//-----------------------------------------------------------------------------
static void _init()
{

    //
    // set up the default font
    //        
    stringc fontFolder = "media/fnt/";
    stringc defFonts = fontFolder + "defaults.zip";
    if(m_fileSystem->existFile(defFonts.c_str()))
    {
        m_fileSystem->addZipFileArchive(defFonts.c_str());
        m_defaultFont = m_gui->getFont("tdeffont.xml");
        if(m_defaultFont)
        {
            m_defaultFont->grab();
            m_gui->getSkin()->setFont(m_defaultFont);
        }
        m_monoFont = m_gui->getFont("monospace.xml");
        if(m_monoFont)
        {
            m_monoFont->grab();
        }
    }

}

//-----------------------------------------------------------------------------
//                         _ c r e a t e S c e n e
//-----------------------------------------------------------------------------
static int _createScene()
{
    int result=0;
    static SKeyMap keyMap[]={
        {EKA_MOVE_FORWARD, KEY_KEY_W},
        {EKA_STRAFE_LEFT, KEY_KEY_A},
        {EKA_MOVE_BACKWARD, KEY_KEY_S},
        {EKA_STRAFE_RIGHT, KEY_KEY_D},
        {EKA_JUMP_UP, KEY_SPACE}
    };

    m_world = m_sceneManager->createMetaTriangleSelector();

    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.03f, -1,keyMap,5,true,0.005f);
    m_camera->setPosition(vector3df(0,10,0));

    /*
    scene::ISceneNode* n = m_sceneManager->addCubeSceneNode();
    if (n)
    {
    n->setMaterialTexture(0, m_videoDriver->getTexture("data/tex/t351sml.jpg"));
    n->setMaterialFlag(video::EMF_LIGHTING, false);
    scene::ISceneNodeAnimator* anim =
    m_sceneManager->createFlyCircleAnimator(core::vector3df(0,0,30), 20.0f);
    if (anim)
    {
    n->addAnimator(anim);
    anim->drop();
    }
    }
    */


    IGUIStaticText* stext = getGUI()->addStaticText(L" ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 ",
        rect<s32>(50,200,350,225),false,false,0,true);
    stext->setBackgroundColor(SColor(129,128,0,0));
    stext->setOverrideColor(SColor(255,255,255,255));

    stext = getGUI()->addStaticText(L" ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 ",
        rect<s32>(50,250,350,275),false,false,0,true);
    stext->setBackgroundColor(SColor(128,0,255,0));
    stext->setOverrideColor(SColor(255,255,255,255));

    IAnimatedMesh* pmesh;
    /*
    pmesh  = m_sceneManager->getMesh("data/mdl/Cube.irrmesh");
    if(pmesh)
    {
    IAnimatedMeshSceneNode* node = m_sceneManager->addAnimatedMeshSceneNode(pmesh, 0);   
    pmesh->setMaterialFlag(EMF_LIGHTING,false);
    node->setPosition(vector3df(0,0,30));
    node->setVisible(true);
    } 
    */

    SMaterial* mat = new SMaterial();
    ITexture* tex = m_videoDriver->getTexture("media/tex/floor.png");
    mat->setTexture(0,tex);
    // causes static text background to disappear.
    mat->MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;

    mat->setFlag(EMF_LIGHTING,false);
    mat->setFlag(EMF_BACK_FACE_CULLING, false);
    mat->getTextureMatrix(0).setTextureScale(50.0,50.0);

    dimension2d<f32> tileSize(50,50);
    dimension2d<u32> tileCount(6,6);
    pmesh = m_sceneManager->addHillPlaneMesh("testHillPlane"
        ,tileSize,tileCount,mat);
    IAnimatedMeshSceneNode* pnode;
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    ITriangleSelector* selector = m_sceneManager->createTriangleSelector(pmesh, pnode);
    m_world->addTriangleSelector(selector);

    m_collisionResponse = m_sceneManager->createCollisionResponseAnimator(m_world,m_camera,
        vector3df(2.f,5.f,2.f),
        vector3df(0,-.005f,0));
    m_camera->addAnimator(m_collisionResponse);

    return result;
}

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib") 
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 
#endif
int main(int argc, char* argv[])
{

    m_device = _createDevice();
    if(!m_device)
        return 0;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    m_device->setWindowCaption(L"GUISceneNode");

    _init();
    if(_createScene())
        return 1;

    while(m_device->run() && m_running)
    {
        m_videoDriver->beginScene(true, true, SColor(255,100,101,140));

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();
    }

    if(m_defaultFont)
        m_defaultFont->drop();
    if(m_monoFont)
        m_monoFont->drop();
    m_device->drop();
    delete m_eventReceiver;    

    return 0;
}

