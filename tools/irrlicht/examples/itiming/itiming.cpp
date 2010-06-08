//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "itiming.h"
#include <assert.h>

#define WINDOW_SIZE_X       640
#define WINDOW_SIZE_Y       480
#define DEVICE_BPP          32

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
static CTextOverlay*        m_debugOverlay;
static int                  m_capNumber=1;

//static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 

using namespace irr::timing;

IGUIEnvironment* getGUI()
{
    return m_gui;
}

void logTestString(irr::core::stringc str)
{
    printf(str.c_str());
}

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
    EventReceiver() : IEventReceiver() {}
};

//-----------------------------------------------------------------------------
//                           _ i n i t
//-----------------------------------------------------------------------------
static bool _init()
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

    m_device = createDeviceEx(cp);
    if(!m_device)
        return false;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    //
    // set up the default font
    //        
    stringc fontFolder = "../data/fnt/";
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
            //m_gui->getSkin()->setFont(m_monoFont);
        }
    }




    //
    // setup debug overlay
    //
    m_debugOverlay = new CTextOverlay("DebugInfo",rectf(0.25f,0.005f,0.75f,0.05f));
    m_debugOverlay->addItem("Node: Pos(x,y,z) Hpr(x,y,z) Dir(x,y,z)", EGUIA_CENTER);
    m_debugOverlay->addItem("Frame: Avg(0.0) Min(0.0) Max(0.0)", EGUIA_CENTER);
    m_debugOverlay->addItem("Visible Debug Data:", EGUIA_CENTER);

    m_debugOverlay->setVisible(true);

    m_device->setWindowCaption(L"idebug");

    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 100.0f, 100.0f);
    m_camera->setPosition(vector3df(0,10,0));


    SMaterial* mat = new SMaterial();
    ITexture* tex = m_videoDriver->getTexture("data/tex/grid.tga");
    mat->setTexture(0,tex);
    // causes static text background to disappear.
    mat->MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;

    mat->setFlag(EMF_LIGHTING,false);
    mat->getTextureMatrix(0).setTextureScale(50.0,50.0);

    dimension2d<f32> tileSize(50,50);
    dimension2d<u32> tileCount(6,6);
    IAnimatedMesh* pmesh = m_sceneManager->addHillPlaneMesh("testHillPlane"
        ,tileSize,tileCount,mat);
    IAnimatedMeshSceneNode* pnode;
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);

    return true;

}

//-----------------------------------------------------------------------------
//                                  t e s t 1
//-----------------------------------------------------------------------------
void test1()
{

    timing::CTimingManager* timingMgr = timing::CTimingManager::getInstance();
    
    f32 f1=0.f, f2=10.f, f3;
    CEvaluatorF32* eval = new CEvaluatorF32();
    eval->evaluate(f1, f2, f3, 0.75);
    core::array<f32> values,times;
    core::array<IInterpolator*> interpolators;

    // a single interpolator will be used across all key frames.
    interpolators.push_back(new CLinearInterpolator());

    // value range (0..x)
    values.push_back(0.f);
    values.push_back(5.f);
    values.push_back(0.f);

    // time range (0..1)
    times.push_back(0.f);
    times.push_back(0.5f);
    times.push_back(1.f);

    CKeyValues<f32>* keyValues = new CKeyValues<f32>(eval,values);
    CKeyTimes* keyTimes = new CKeyTimes(times);
    CKeyFrames<f32>* keyFrames = new CKeyFrames<f32>(keyValues, keyTimes, interpolators);

    // 0
    int interval = keyFrames->getInterval(0.f);
    // 1
    interval = keyFrames->getInterval(0.21f);
    // 2
    interval = keyFrames->getInterval(0.6f);

    f32 out;
    keyFrames->getValue(0.1f, out);
    keyFrames->getValue(0.21f, out);
    keyFrames->getValue(0.25f, out);
    keyFrames->getValue(0.5f, out);
    keyFrames->getValue(0.51f, out);
    keyFrames->getValue(0.6f, out);
    keyFrames->getValue(1.f, out);
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

    _init();

    test1();

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

