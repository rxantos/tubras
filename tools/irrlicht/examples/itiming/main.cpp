//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "main.h"
#include <assert.h>

#define WINDOW_SIZE_X       1024
#define WINDOW_SIZE_Y       768
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
static scene::IMeshSceneNode*   m_cubeNode=0;
static bool                 m_running=true;
static CTextOverlay*        m_debugOverlay;
static int                  m_capNumber=1;
static timing::IAnimator*      m_animator1;
static timing::CTimingManager* m_timingManager;
static timing::IAnimator*   m_animators[10]={0,0,0,0,0,0,0,0,0,0};
static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 
static SKeyMap keyMap[]={
    {EKA_MOVE_FORWARD, KEY_KEY_W},
    {EKA_STRAFE_LEFT, KEY_KEY_A},
    {EKA_MOVE_BACKWARD, KEY_KEY_S},
    {EKA_STRAFE_RIGHT, KEY_KEY_D}
    //{EKA_JUMP_UP, KEY_SPACE}
};

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
        {
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
                }
            }
            else { // key down
                switch(event.KeyInput.Key)
                {
                case KEY_KEY_0: // run all animators
                    for(int i=0; i<10; i++)
                    {
                        if(m_animators[i])
                            m_animators[i]->start();
                    }
                    break;
                case KEY_KEY_1:
                    if(m_animators[0])
                        m_animators[0]->start();
                    break;
                case KEY_KEY_2:
                    if(m_animators[1])
                        m_animators[1]->start();
                    break;
                case KEY_KEY_3:
                    if(m_animators[2])
                        m_animators[2]->start();
                    break;
                case KEY_KEY_4:
                    if(m_animators[3])
                        m_animators[3]->start();
                    break;
                default:
                    break;
                }

            }
        }
        return false;
    }

public:
    EventReceiver() : IEventReceiver() {}
};

class AnimationTarget1 : public CTimingTargetAdapter
{
    void begin()
    {
        printf("AnimationTarget1::begin()\n");
    }

    void end()
    {
        printf("AnimationTarget1::end()\n");
    }
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
    cp.Vsync = true;
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
    m_timingManager = timing::CTimingManager::getInstance(m_device);    

    m_device->getCursorControl()->setVisible(false);

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
    m_debugOverlay->addItem("Frame: Avg(0.0) Min(0.0) Max(0.0)", EGUIA_CENTER);

    m_debugOverlay->setVisible(true);

    m_device->setWindowCaption(L"idebug");

    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.2f, -1, keyMap, 5, false, 0.075f);
    m_camera->setPosition(vector3df(0,15,-40));


    SMaterial* mat = new SMaterial();
    ITexture* tex = m_videoDriver->getTexture("../data/tex/floor.png");
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

    m_cubeNode = m_sceneManager->addCubeSceneNode();
    m_cubeNode->setPosition(core::vector3df(0,5,0));

    if (m_cubeNode)
    {
        m_cubeNode->setMaterialTexture(0, m_videoDriver->getTexture("../data/tex/t351sml.jpg"));
        m_cubeNode->setMaterialFlag(video::EMF_LIGHTING, true);
        video::SMaterial& mat = m_cubeNode->getMesh()->getMeshBuffer(0)->getMaterial();
        //video::SMaterial& mat = m_cubeNode->getMaterial(0);
        //mat.DiffuseColor = video::SColor(255, 0, 0 , 0);
        //mat.AmbientColor = video::SColor(255, 0, 0 , 0);
        mat.EmissiveColor = video::SColor(255, 255, 255 , 255);
        mat.setFlag(video::EMF_COLOR_MATERIAL, true);
    }



    return true;

}

//-----------------------------------------------------------------------------
//                                  t e s t 1
//-----------------------------------------------------------------------------
void test1()
{

    f32 f1=0.f, f2=10.f, f3;
    CEvaluatorF32* eval = new CEvaluatorF32();
    CEvaluatorSColor* ceval = new CEvaluatorSColor();
    eval->evaluate(f1, f2, f3, 0.75);
    core::array<f32> values,times;
    core::array<SColor> cvalues;
    core::array<IInterpolator*> interpolators;

    // keyframe interpolation tests

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

    CKeyValues<f32>* keyValues = m_timingManager->createKeyValues(values);

    CKeyTimes* keyTimes = new CKeyTimes(times);
    CKeyFrames<f32>* keyFrames = new CKeyFrames<f32>(keyValues, keyTimes, interpolators);
    CKeyFrames<f32>* keyFrames2 = new CKeyFrames<f32>(keyValues, keyTimes);
    CKeyFrames<f32>* keyFrames3 = new CKeyFrames<f32>(keyValues);

    // 0
    int interval = keyFrames->getInterval(0.f);
    // 0
    interval = keyFrames->getInterval(0.5f);
    // 1
    interval = keyFrames->getInterval(0.6f);

    f32 out;
    keyFrames->getValue(0.1f, out);
    keyFrames->getValue(0.21f, out);
    keyFrames->getValue(0.25f, out);
    keyFrames->getValue(0.5f, out);
    keyFrames->getValue(0.51f, out);
    keyFrames->getValue(0.6f, out);
    keyFrames->getValue(1.f, out);

    // SColor interpolation
    SColor* pcolor = new SColor(255);
    cvalues.push_back(*pcolor);
    pcolor = new SColor(255, 255, 255, 0);
    cvalues.push_back(*pcolor);
    pcolor = new SColor(255, 128, 0, 128);
    cvalues.push_back(*pcolor);
    CKeyValues<SColor>* ckeyValues = m_timingManager->createKeyValues(cvalues);
    CKeyFrames<SColor>* ckeyFrames = new CKeyFrames<SColor>(ckeyValues, keyTimes);
    SColor colorOut;
    ckeyFrames->getValue(0.25f, colorOut);

    //
    // create an animator with a duration of 2.5 seconds and simple ITimingTarget
    // that logs "begin" & "end" events.
    //
    /*
    m_animator1 = m_timingManager->createAnimator(2500, new AnimationTarget1());

    IAnimator* animator = m_timingManager->createPropertyAnimator(1000, out, keyValues);

    animator = m_timingManager->createPropertyAnimator(3000, colorOut, ckeyValues);
    // or
    animator = m_timingManager->createPropertyAnimator(4000, colorOut, ckeyFrames);
    */
}

//-----------------------------------------------------------------------------
//                                  t e s t 2
//-----------------------------------------------------------------------------
void test2()
{
    core::array<core::vector3df> values;
    core::array<f32> times;
    core::array<IInterpolator*> interpolators;

    // position animation test on cube scene node using default linear interpolation

    // value range (0..x)
    values.push_back(core::vector3df(0,5,0));
    values.push_back(core::vector3df(-20,45.f,0));
    values.push_back(core::vector3df(135.f,5.f,100));
    values.push_back(core::vector3df(0.f,5.f,0.f));

    // time range (0..1)
    times.push_back(0.f);
    times.push_back(0.25f);
    times.push_back(0.8f);
    times.push_back(1.f);

    CKeyValues<core::vector3df>* keyValues = m_timingManager->createKeyValues(values);
    CKeyTimes* keyTimes = new CKeyTimes(times);

    CKeyFrames<vector3df>* keyFrames = new CKeyFrames<core::vector3df>(keyValues, keyTimes);

    m_animators[0] = m_timingManager->createPropertyAnimator(1000, 
        (irr::core::vector3df& )m_cubeNode->getPosition(), keyFrames);
    m_animators[0]->setRepeatCount(3);    
}

//-----------------------------------------------------------------------------
//                                  t e s t 3
//-----------------------------------------------------------------------------
void test3()
{
    core::array<video::SColor> values;
    core::array<f32> times;
    core::array<IInterpolator*> interpolators;

    // color animation test on cube scene node using default linear interpolation

    // value range
    values.push_back(video::SColor(255, 255, 255, 255));
    values.push_back(video::SColor(255, 255, 0, 0));
    values.push_back(video::SColor(255, 0, 255, 0));
    values.push_back(video::SColor(255, 0, 0, 255));
    values.push_back(video::SColor(255, 255, 255, 255));

    // time range (0..1)
    times.push_back(0.f);
    times.push_back(0.25f);
    times.push_back(0.5f);
    times.push_back(0.75f);
    times.push_back(1.f);

    CKeyValues<video::SColor>* keyValues = m_timingManager->createKeyValues(values);
    CKeyTimes* keyTimes = new CKeyTimes(times);

    CKeyFrames<video::SColor>* keyFrames = new CKeyFrames<video::SColor>(keyValues, keyTimes);

    m_animators[1] = m_timingManager->createPropertyAnimator(3000, 
        m_cubeNode->getMesh()->getMeshBuffer(0)->getMaterial().EmissiveColor, keyFrames);
    m_animators[1]->setEndBehavior(irr::timing::HOLD);
}

//-----------------------------------------------------------------------------
//                                  t e s t 4
//-----------------------------------------------------------------------------
void test4()
{
    core::array<core::vector3df> values;
    core::array<f32> times;
    core::array<IInterpolator*> interpolators;

    // scale animation test on cube scene node using default linear interpolation

    // value range (0..x)
    values.push_back(core::vector3df(1.f,1.f,1.f));
    values.push_back(core::vector3df(1.f,6.f,0.5f));
    values.push_back(core::vector3df(2.f,1.f,3.f));
    values.push_back(core::vector3df(1.f,1.f,1.f));

    // time range (0..1)
    times.push_back(0.f);
    times.push_back(0.15f);
    times.push_back(0.5f);
    times.push_back(1.f);

    CKeyValues<core::vector3df>* keyValues = m_timingManager->createKeyValues(values);
    CKeyTimes* keyTimes = new CKeyTimes(times);

    CKeyFrames<vector3df>* keyFrames = new CKeyFrames<core::vector3df>(keyValues, keyTimes);

    m_animators[2] = m_timingManager->createPropertyAnimator(750, 
        (irr::core::vector3df& )m_cubeNode->getScale(), keyFrames);
    m_animators[2]->setRepeatCount(2);
}

//-----------------------------------------------------------------------------
//                                  t e s t 5
//-----------------------------------------------------------------------------
void test5()
{
    core::array<core::vector3df> values;
    core::array<f32> times;
    core::array<IInterpolator*> interpolators;

    // rotation animation test on cube scene node using default linear interpolation

    // value range (0..x)
    values.push_back(core::vector3df(0.f,0.f,0.f));
    values.push_back(core::vector3df(0.f,0.f,90.f));
    values.push_back(core::vector3df(0.f,0.f,190.f));
    values.push_back(core::vector3df(0.f,0.f,360.f));

    // time range (0..1)
    times.push_back(0.f);
    times.push_back(0.15f);
    times.push_back(0.85f);
    times.push_back(1.f);

    CKeyValues<core::vector3df>* keyValues = m_timingManager->createKeyValues(values);
    CKeyTimes* keyTimes = new CKeyTimes(times);

    CKeyFrames<vector3df>* keyFrames = new CKeyFrames<core::vector3df>(keyValues, keyTimes);

    m_animators[3] = m_timingManager->createPropertyAnimator(1500, 
        (irr::core::vector3df& )m_cubeNode->getRotation(), keyFrames);
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
    char buf[256];
    s32 fpsMin=0, fpsMax=0;

    _init();

    test1();
    test2();
    test3();
    test4();
    test5();

    while(m_device->run() && m_running)
    {
        m_videoDriver->beginScene(true, true, SColor(255,100,101,140));
        m_timingManager->tick();

        //m_cubeNode->updateAbsolutePosition();

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();
        irr::core::stringc stats;
        s32 fps = m_videoDriver->getFPS();
        if(fps > 30)
        {
            if(!fpsMin || (fps < fpsMin))
                fpsMin = fps;
            if(fps > fpsMax)
                fpsMax = fps;
        }
        sprintf(buf, "Frame: Avg(%d) Min(%d) Max(%d)", fps, fpsMin, fpsMax);
        stats = buf;
        m_debugOverlay->updateItem(0,stats); 
    }

    if(m_defaultFont)
        m_defaultFont->drop();
    if(m_monoFont)
        m_monoFont->drop();
    m_device->drop();
    delete m_eventReceiver;    


    return 0;
}

