#include "idebug.h"

#define WINDOW_SIZE_X       800
#define WINDOW_SIZE_Y       600
#define DEVICE_BPP          24

static IrrlichtDevice*      m_device;
static IVideoDriver*        m_videoDriver;
static ISceneManager*       m_sceneManager;
static IFileSystem*         m_fileSystem;
static IEventReceiver*      m_eventReceiver;
static IGUIEnvironment*     m_gui;
static bool                 m_running=true;

static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  // or EDT_DIRECT3D9


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
    //
    // we need to use a "real" renderer otherwise the 
    // material conversions won't work properly (all will
    // be set to EMT_SOLID with the null renderer).
    //
    // because of this, we create/use a hidden window to
    // maintain the appearence of a command line program.
    //
    m_eventReceiver = new EventReceiver();
    SIrrlichtCreationParameters cp;
    cp.DriverType = m_driverType;
    cp.WindowSize = dimension2d<s32>(WINDOW_SIZE_X,WINDOW_SIZE_Y);
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
//                                 m a i n
//-----------------------------------------------------------------------------
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 
int main(int argc, char* argv[])
{

    m_device = _createDevice();
    if(!m_device)
        return -1;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    m_device->setWindowCaption(L"idebug");

    m_sceneManager->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    while(m_device->run() && m_running)
    {
        m_videoDriver->beginScene(true, true, SColor(255,100,101,140));

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();
    }

    m_device->drop();
    delete m_eventReceiver;

    return 0;
}