//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS 1

#include "irrlicht.h"
#include "COIS.h"

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

typedef rect<f32> rectf;
typedef rect<s32> rectd;
typedef std::ostringstream StrStream;

#define WINDOW_SIZE_X       800
#define WINDOW_SIZE_Y       600
#define DEVICE_BPP          24

static COIS*                m_ois;
static IrrlichtDevice*      m_device;
static IVideoDriver*        m_videoDriver;
static ISceneManager*       m_sceneManager;
static IFileSystem*         m_fileSystem;
static IGUIEnvironment*     m_gui;
static bool                 m_running=true;
static int                  m_capNumber=1;
static void*                m_windowHandle;
static u32                  m_display;
static IGUIListBox*         m_listbox = 0;


static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 

//-----------------------------------------------------------------------------
//                                 M y O I S
//-----------------------------------------------------------------------------
class MyOIS: public COIS
{
public:
    MyOIS(IrrlichtDevice* idevice, bool showCursor=true, bool buffered=true,
        bool enableDebug=true) : COIS(idevice, showCursor, buffered, enableDebug) {};

    // override default handlers
    bool keyPressed( const OIS::KeyEvent& arg );
    bool keyReleased( const OIS::KeyEvent& arg );
    bool mouseMoved( const OIS::MouseEvent &arg ); 
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool buttonPressed( const OIS::JoyStickEvent &arg, int button );
    bool buttonReleased( const OIS::JoyStickEvent &arg, int button );
    bool axisMoved( const OIS::JoyStickEvent &arg, int axis );
    bool povMoved( const OIS::JoyStickEvent &arg, int pov );
};

//-----------------------------------------------------------------------------
//                             k e y P r e s s e d
//-----------------------------------------------------------------------------
bool MyOIS::keyPressed(const OIS::KeyEvent& arg )
{
    //
    // for default gui handling
    //
    if(COIS::keyPressed(arg))
        return true;

    switch(arg.key)
    {
    case OIS::KC_ESCAPE:
        m_running = false;
        return true;

    case OIS::KC_SYSRQ: /* print screen */
        IImage* image = m_videoDriver->createScreenShot();
        char buf[32];

        sprintf(buf,"cap%.2d.png",m_capNumber++);

        m_videoDriver->writeImageToFile(image,buf);

        image->drop();
        break;
    }
    return false;
}

//-----------------------------------------------------------------------------
//                            k e y R e l e a s e d
//-----------------------------------------------------------------------------
bool MyOIS::keyReleased(const OIS::KeyEvent& arg )
{
    //
    // for default gui handling
    //
    if(COIS::keyReleased(arg))
        return true;

    return false;
}

bool MyOIS::mouseMoved( const OIS::MouseEvent &arg )
{
    return COIS::mouseMoved(arg);
}
bool MyOIS::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return COIS::mousePressed(arg, id);
}
bool MyOIS::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
{
    return COIS::mouseReleased(arg, id);
}
bool MyOIS::buttonPressed( const OIS::JoyStickEvent &arg, int button ) 
{
    return COIS::buttonPressed(arg, button);
}
bool MyOIS::buttonReleased( const OIS::JoyStickEvent &arg, int button ) 
{
    return COIS::buttonReleased(arg, button);
}
bool MyOIS::axisMoved( const OIS::JoyStickEvent &arg, int axis ) 
{
    return COIS::axisMoved(arg, axis);
}
bool MyOIS::povMoved( const OIS::JoyStickEvent &arg, int pov ) 
{
    return COIS::povMoved(arg, pov);
}

//-----------------------------------------------------------------------------
//                            _ c r e a t e G U I 
//-----------------------------------------------------------------------------
static void _createGUI()
{
	m_gui->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
	IGUIScrollBar* scrollbar = m_gui->addScrollBar(true, rect<s32>(150, 45, 350, 60), 0, 104);
	scrollbar->setMax(255);

	// set scrollbar position to alpha value of an arbitrary element
	scrollbar->setPos(m_gui->getSkin()->getColor(EGDC_WINDOW).getAlpha());

	m_gui->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
	m_listbox = m_gui->addListBox(rect<s32>(50, 140, 250, 210));
	m_gui->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

}

//-----------------------------------------------------------------------------
//                           _ c r e a t e D e v i c e
//-----------------------------------------------------------------------------
static IrrlichtDevice* _createDevice()
{
    //m_eventReceiver = new EventReceiver();
    SIrrlichtCreationParameters cp;
    cp.DriverType = m_driverType;
    cp.WindowSize = dimension2d<s32>(WINDOW_SIZE_X,WINDOW_SIZE_Y);
    cp.Bits = DEVICE_BPP;
    cp.Fullscreen = false;
    cp.Vsync = false;
    cp.Stencilbuffer = false;
    cp.AntiAlias = false;
    cp.EventReceiver = 0;
    cp.WindowId = 0;

    return createDeviceEx(cp);
}

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup") 
int main(int argc, char* argv[])
{
    MyOIS* m_ois;

    m_device = _createDevice();
    if(!m_device)
        return -1;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    //
    // init ois (device, show cursor, buffered, debug enabled)
    //
    m_ois = new MyOIS(m_device, true, true, true);
    if(m_ois->initialize())
        return 1;
    m_ois->setGUIEnabled(true);
    //m_ois->setGUIExclusive(true);

    m_device->setWindowCaption(L"OIS Example");

    _createGUI();

    m_sceneManager->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    while(m_device->run() && m_running)
    {
        // capture input
        m_ois->capture();

        m_videoDriver->beginScene(true, true, SColor(255,100,101,140));

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();
    }

    delete m_ois;
    m_device->drop();

    return 0;
}
