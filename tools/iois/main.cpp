//-----------------------------------------------------------------------------
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

#define ID_DBGCONSOLE       101
#define ID_ALPHA            102

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
static IGUIListBox*         m_mlistbox = 0;
static IGUICheckBox*        m_cb1 = 0;


static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 

//-----------------------------------------------------------------------------
//                                 M y O I S
//-----------------------------------------------------------------------------
class MyOIS: public COIS, public IEventReceiver
{
protected:
    OIS::Effect*        m_effect;
    bool                m_effectActive;
public:
    MyOIS(IrrlichtDevice* idevice, bool showCursor=true, bool buffered=true,
        bool enableDebug=true) : COIS(idevice, showCursor, buffered, enableDebug) 
    {
        m_effectActive = false;
        m_effect = new OIS::Effect(OIS::Effect::ConstantForce, OIS::Effect::Constant);
    };


    //
    // starts/stops a "constant" force feedback effect on device 0
    //
    void toggleFF()
    {
        if(hasForceFeedback(0))
        {
            if(!m_effectActive)
                getFF(0)->upload(m_effect);
            else
                getFF(0)->remove(m_effect);

            m_effectActive = m_effectActive ? false : true;
        }
    }

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
	virtual bool OnEvent(const SEvent& event);
};

//-----------------------------------------------------------------------------
//                             k e y P r e s s e d
//-----------------------------------------------------------------------------
bool MyOIS::keyPressed(const OIS::KeyEvent& arg )
{
    // add debug info to listbox
    stringw temp = "key.down.";
    temp += getKeyString(arg.key).c_str();
    m_listbox->setSelected(m_listbox->addItem(temp.c_str()));

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

    case OIS::KC_F:
        toggleFF();        
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
    // add debug info to listbox
    stringw temp = "key.up.";
    temp += getKeyString(arg.key).c_str();
    m_listbox->setSelected(m_listbox->addItem(temp.c_str()));

    //
    // for default gui handling
    //
    if(COIS::keyReleased(arg))
        return true;

    return false;
}

//-----------------------------------------------------------------------------
//                            m o u s e M o v e d
//-----------------------------------------------------------------------------
bool MyOIS::mouseMoved( const OIS::MouseEvent &arg )
{
    stringw temp = "mouse.move (";
    temp += arg.state.X.abs;
    temp += ",";
    temp += arg.state.Y.abs;
    temp += ",";
    temp += arg.state.Z.abs;
    temp += ")";
    m_mlistbox->setSelected(m_mlistbox->addItem(temp.c_str()));
    if(m_mlistbox->getItemCount() > 200)
    {
        for(int i=0; i<50; i++)
        {
            m_mlistbox->removeItem(0);
        }
    }

    return COIS::mouseMoved(arg);
}
//-----------------------------------------------------------------------------
//                            m o u s e P r e s s e d
//-----------------------------------------------------------------------------
bool MyOIS::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    stringw temp = "mouse.pressed (";
    temp += id;
    temp += ") (";
    temp += arg.state.X.abs;
    temp += ",";
    temp += arg.state.Y.abs;
    temp += ")";
    m_mlistbox->setSelected(m_mlistbox->addItem(temp.c_str()));
    return COIS::mousePressed(arg, id);
}

//-----------------------------------------------------------------------------
//                          m o u s e R e l e a s e d 
//-----------------------------------------------------------------------------
bool MyOIS::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
{
    stringw temp = "mouse.released (";
    temp += id;
    temp += ") (";
    temp += arg.state.X.abs;
    temp += ",";
    temp += arg.state.Y.abs;
    temp += ")";
    m_mlistbox->setSelected(m_mlistbox->addItem(temp.c_str()));
    return COIS::mouseReleased(arg, id);
}
bool MyOIS::buttonPressed( const OIS::JoyStickEvent &arg, int button ) 
{
    if(button == 7)
        toggleFF();

    return COIS::buttonPressed(arg, button);
}
bool MyOIS::buttonReleased( const OIS::JoyStickEvent &arg, int button ) 
{
    if(button == 7)
        toggleFF();

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
//                              O n E v e n t
//-----------------------------------------------------------------------------
bool MyOIS::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();

        switch(event.GUIEvent.EventType)
        {
        case EGET_CHECKBOX_CHANGED:
            setDebugEnabled(m_cb1->isChecked());
            break;
        case EGET_SCROLL_BAR_CHANGED:
            if (id == ID_ALPHA)
            {
                s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();

                for (u32 i=0; i<EGDC_COUNT ; ++i)
                {
                    SColor col = m_gui->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
                    col.setAlpha(pos);
                    m_gui->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
                }

            }
            break;

        };
    }

    return false;
}


//-----------------------------------------------------------------------------
//                            _ c r e a t e G U I 
//-----------------------------------------------------------------------------
static void _createGUI()
{
	m_gui->addStaticText(L"Transparent Control:", rect<s32>(50,20,250,40), true);
	IGUIScrollBar* scrollbar = m_gui->addScrollBar(true, rect<s32>(50, 45, 250, 60), 0, ID_ALPHA);
	scrollbar->setMax(255);
	scrollbar->setPos(255);

    m_cb1 = m_gui->addCheckBox(true, rect<s32>(300, 20, 500, 40), 0, ID_DBGCONSOLE, L"Print Debug Info To Console");

	m_gui->addEditBox(L"Editable Text", rect<s32>(50, 80, 250, 100));

	m_gui->addStaticText(L"Key Logging ListBox:", rect<s32>(50,110,250,130), true);
	m_listbox = m_gui->addListBox(rect<s32>(50, 130, 250, 500), 0, -1, true);
    m_listbox->setAutoScrollEnabled(true);

	m_gui->addStaticText(L"Mouse Logging ListBox:", rect<s32>(300,110,500,130), true);
	m_mlistbox = m_gui->addListBox(rect<s32>(300, 130, 500, 500), 0, -1, true);
    m_mlistbox->setAutoScrollEnabled(true);

    // turn up the alpha for skin colors
    for (u32 i=0; i<EGDC_COUNT ; ++i)
    {
        SColor col = m_gui->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
        col.setAlpha(255);
        m_gui->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
    }
}

//-----------------------------------------------------------------------------
//                           _ c r e a t e D e v i c e
//-----------------------------------------------------------------------------
static IrrlichtDevice* _createDevice()
{
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

#if defined(_IRR_LINUX_PLATFORM_) && defined(_IRR_USE_LINUX_DEVICE_)
    cp.IgnoreInput = true;
#endif

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

    m_device->setEventReceiver(m_ois);

    m_sceneManager->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    while(m_device->run() && m_running)
    {
        // capture input
        m_ois->capture();

        m_videoDriver->beginScene(true, true, SColor(0,200,200,200));

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();
    }

    delete m_ois;
    m_device->drop();

    return 0;
}
