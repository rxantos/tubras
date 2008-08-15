//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "irrlicht.h"
#include "COIS.h"
#ifndef _IRR_WINDOWS_API_
#ifdef _IRR_COMPILE_WITH_X11_
#include <X11/Xlib.h>
#endif
#endif

using namespace irr::core;
using namespace OIS;
const char* wmDeleteWindow = "WM_DELETE_WINDOW";
const char *g_DeviceType[6] = {"OISUnknown", "OISKeyboard", "OISMouse", "OISJoyStick",
"OISTablet", "OISOther"};

// FF force type
static stringc SForce[] =
{
    "UnknownForce",
    "ConstantForce",
    "RampForce",
    "PeriodicForce",
    "ConditionalForce",
    "CustomForce"
};

// Type of FF effect
static stringc SType[] =
{
    "Unknown",      //UnknownForce
    "Constant",     //ConstantForce
    "Ramp",         //RampForce
    "Square",       //PeriodicForce
    "Triangle",     //PeriodicForce
    "Sine",         //PeriodicForce
    "SawToothUp",   //PeriodicForce
    "SawToothDown", //PeriodicForce
    "Friction",     //ConditionalForce
    "Damper",       //ConditionalForce
    "Inertia",      //ConditionalForce
    "Spring",       //ConditionalForce
    "Custom"        //CustomForce
};

// used for debugging key codes
static stringc scancodes[]=
{
    "0x00","esc","1","2","3","4","5","6","7","8","9","0",
    "minus","equal","back","tab",
    "q","w","e","r","t","y","u","i","o","p",
    "lbracket","rbracket","return","lcontrol",
    "a","s","d","f","g","h","j","k","l",
    "semicolon","apostrophe","grave","lshift","backslash",
    "z","x","c","v","b","n","m",
    "comma","period","slash","rshift","multiply","lmenu","space","capital",
    "f1","f2","f3","f4","f5","f6","f7","f8","f9","f10",
    "numlock","scroll","numpad7","numpad8","numpad9","subtract",
    "numpad4","numpad5","numpad6","add","numpad1","numpad2","numpad3",
    "numpad0","decimal","0x54","0x55","oem_102","f11","f12","0x59",										
    "0x5a","0x5b","0x5c","0x5d","0x5e","0x5f","0x60","0x61","0x62",
    "0x63","f13","f14","f15","0x67","0x68","0x69","0x6a","0x6b",
    "0x6c","0x6d","0x6e","0x6f","kana","0x71","0x72","abnt_c1",
    "0x74","0x75","0x76","0x77","0x78","convert", "0x7a","noconvert", 
    "0x7c","yen","abnt_c2","0x7f","0x80","0x81","0x82","0x83","0x84",
    "0x85","0x86","0x87","0x88","0x89","0x8a","0x8b","0x8c",
    "numpadequals","0x8e","0x8f","prevtrack","at","colon","underline",
    "kanji","stop","ax","unlabeled", "0x98","nexttrack", "0x9a",
    "0x9b","numpadenter","rcontrol", "0x9e", "0x9f","mute","calculater",
    "playpause", "0xa3","mediastop","0xa5","0xa6","0xa7","0xa8","0xa9",
    "0xaa","0xab","0xac","0xad","volumedown", "0xaf","volumeup", "0xb1",
    "webhome","numpadcomma", "0xb4","divide", "0xb6","prtscr","rmenu",
    "0xb9","0xba","0xbb","0xbc","0xbd","0xbe", "0xbf","0xc0","0xc1",
    "0xc2","0xc3","0xc4","pause","0xc6","home","up","pgup","0xca",
    "left", "0xcc","right", "0xce","end","down","pgdown","insert",
    "delete","0xd4","0xd5","0xd6","0xd7","0xd8","0xd9","0xda","lwin",
    "rwin","apps","power","sleep","0xe0","0xe1","0xe2","wake", "0xe4",
    "websearch","webfavorites","webstop","webforward","webback",
    "mycomputer","mail","mediaselect"
};


//-----------------------------------------------------------------------
//                              C O I S
//-----------------------------------------------------------------------
COIS::COIS(IrrlichtDevice* idevice, bool showCursor, bool buffered, bool debugEnabled) : m_inputManager(0),
m_device(idevice),
m_windowHandle(0),
m_display(0),
m_buffered(buffered),
m_debugEnabled(debugEnabled),
m_GUIEnabled(false),
m_GUIExclusive(false),
m_showCursor(showCursor),
m_keyboard(0),
m_mouse(0),
m_numSticks(0)
#ifdef _IRR_WINDOWS_
,m_oldWndProc(0)
#endif
{
    for(u32 i=0;i<MAX_JOYS;i++)
    {
        m_joys[i] = 0;
        m_ff[i] = 0;
    }
}

//-----------------------------------------------------------------------
//                             ~ C O I S
//-----------------------------------------------------------------------
COIS::~COIS()
{

    if( m_inputManager )
    {
        if(m_keyboard)
            m_inputManager->destroyInputObject( m_keyboard );
        if(m_mouse)
            m_inputManager->destroyInputObject( m_mouse );
        InputManager::destroyInputSystem(m_inputManager);
    }

#ifdef _IRR_WINDOWS_
    // restore wndproc
    SetWindowLongPtr((HWND)m_windowHandle, GWLP_WNDPROC, m_oldWndProc);
#endif

}

//-----------------------------------------------------------------------
//                            _ w n d P r o c
//-----------------------------------------------------------------------
#ifdef _IRR_WINDOWS_
LRESULT COIS::_wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
#endif

//-----------------------------------------------------------------------
//                          i n i t i a l i z e 
//-----------------------------------------------------------------------
int COIS::initialize()
{
    int result=0;
    unsigned int* p=(unsigned int*)&m_windowHandle;
    char buf[32];
    ParamList pl;

    if(!m_device)
        return 1;

    m_gui = m_device->getGUIEnvironment();

#ifdef _IRR_WINDOWS_
    //
    // replace irrlicht wndproc with ours to make ois work properly. 
    //
    HWND hwnd = (HWND)(m_device->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd);
    m_oldWndProc = GetWindowLongPtr(hwnd, GWL_WNDPROC);
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)_wndProc);
    m_windowHandle = (void *)hwnd;
    //Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
    pl.insert(std::make_pair("w32_mouse", "DISCL_FOREGROUND"));

    if(m_showCursor)
        pl.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));
    else pl.insert(std::make_pair("w32_mouse", "DISCL_EXCLUSIVE"));
#else

    m_windowHandle = (void *)m_device->getVideoDriver()->getExposedVideoData().OpenGLLinux.X11WindowId;
    m_display = (int)m_device->getVideoDriver()->getExposedVideoData().OpenGLLinux.X11Display;
    pl.insert(std::make_pair("x11_keyboard_grab","false"));
    if(m_showCursor)
    {
        pl.insert(std::make_pair("x11_mouse_grab","false"));
        pl.insert(std::make_pair("x11_mouse_hide","false"));
    }
    else
    {
        pl.insert(std::make_pair("x11_mouse_grab","true"));
        pl.insert(std::make_pair("x11_mouse_hide","true"));
    }
#endif


    sprintf(buf,"%u",*p);
    pl.insert(std::make_pair( "WINDOW", buf ));


    //This never returns null.. it will raise an exception on errors

    m_inputManager = InputManager::createInputSystem(pl);

    unsigned int v = m_inputManager->getVersionNumber();

    if(m_debugEnabled)
    {
        printf("OIS Version: %d.%d.%d\n", (v>>16 ),((v>>8) & 0x000000FF),(v & 0x000000FF));
        printf("Release Name: %s\n", m_inputManager->getVersionName().c_str());
        printf("Manager: %s\n", m_inputManager->inputSystemName().c_str());
        printf("Total Keyboards: %d\n", m_inputManager->getNumberOfDevices(OISKeyboard));
        printf("Total Mice: %d\n", m_inputManager->getNumberOfDevices(OISMouse));
        printf("Total JoySticks: %d\n", m_inputManager->getNumberOfDevices(OISJoyStick));
    }

    //List all devices
    OIS::DeviceList list = m_inputManager->listFreeDevices();
    for( DeviceList::iterator i = list.begin(); i != list.end(); ++i )
        if(m_debugEnabled)
            printf("   Device: %s, Vendor %s\n",g_DeviceType[i->first],i->second.c_str());

    //Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
    m_keyboard = static_cast<Keyboard*>(m_inputManager->createInputObject( OISKeyboard, m_buffered ));
    m_mouse = static_cast<Mouse*>(m_inputManager->createInputObject( OISMouse, m_buffered ));

    m_keyboard->setEventCallback( this );
    m_mouse->setEventCallback( this );

    try
    {
        //This demo uses at most MAX_JOYS joysticks
        m_numSticks = m_inputManager->getNumberOfDevices(OISJoyStick);
        if(m_numSticks > MAX_JOYS)
            m_numSticks = MAX_JOYS;
        for( u32 i = 0; i < m_numSticks; ++i )
        {
            m_joys[i] = (JoyStick*)m_inputManager->createInputObject( OISJoyStick, m_buffered );
            m_joys[i]->setEventCallback( this );

            if(m_debugEnabled)
                printf("\nJoystick %d - ", i+1);
            //Check for FF, if so, dump info
            m_ff[i] = (ForceFeedback*)m_joys[i]->queryInterface( Interface::ForceFeedback );
            if( m_ff[i] )
            {
                if(m_debugEnabled)
                    printf(" Has FF Support!, Effects:\n");
                const ForceFeedback::SupportedEffectList &list = m_ff[i]->getSupportedEffects();
                ForceFeedback::SupportedEffectList::const_iterator i = list.begin(),
                    e = list.end();
                if(m_debugEnabled)
                {
                    for( ; i != e; ++i)
                    {
                        printf("   Force=%s, Type=%s\n",SForce[i->first].c_str(),SType[i->second].c_str());
                    }
                }
            }
            else if(m_debugEnabled)

                printf("No FF Support\n");
        }
    }
    catch(OIS::Exception &ex)
    {
        if(m_debugEnabled)
            printf("Exception raised on joystick creation: %s\n", ex.eText);
    }

    //
    // set OIS display size
    //
    dimension2di dims = m_device->getVideoDriver()->getScreenSize();
    setDisplaySize(dims.Width,dims.Height);

    return result;
}

//-----------------------------------------------------------------------
//                     h a s F o r c e F e e d b a c k
//-----------------------------------------------------------------------
bool COIS::hasForceFeedback(u32 stickNumber)
{
    if( stickNumber > MAX_JOYS)
        return false;

    return (m_ff[stickNumber] != 0);
}

//-----------------------------------------------------------------------
//                        s e t S c r e e n S i z e
//-----------------------------------------------------------------------
void COIS::setDisplaySize(int width, int height)
{
    m_mouse->getMouseState().width = width;
    m_mouse->getMouseState().height = height;
}

//-----------------------------------------------------------------------
//                              c a p t u r e
//-----------------------------------------------------------------------
int COIS::capture()
{
    int result=0;

    if(m_keyboard)
        m_keyboard->capture();
    if(m_mouse)
        m_mouse->capture();
    for(u32 i=0; i<m_numSticks; i++)
    {
        m_joys[i]->capture();
    }

    return result;
}

//-----------------------------------------------------------------------
//                         i s K e y D o w n 
//-----------------------------------------------------------------------
bool COIS::isKeyDown(OIS::KeyCode key)
{
    return m_keyboard->isKeyDown(key);
}

//-----------------------------------------------------------------------
//                           k e y P r e s s e d
//-----------------------------------------------------------------------
bool COIS::keyPressed( const OIS::KeyEvent& arg ) 
{

    if(m_GUIEnabled)
    {
        irr::SEvent event;
        event.EventType = irr::EET_KEY_INPUT_EVENT;
        event.KeyInput.Key = (irr::EKEY_CODE)arg.key;
        event.KeyInput.Char = arg.text;
        event.KeyInput.PressedDown = true;
        event.KeyInput.Shift = m_keyboard->isModifierDown(OIS::Keyboard::Shift);
        event.KeyInput.Control = m_keyboard->isModifierDown(OIS::Keyboard::Ctrl);

        if (m_gui)
            m_gui->postEventFromUser(event);

        if(m_GUIExclusive)
            return true;
    }        

    if(m_debugEnabled)
    {
        stringc info = "key.down.";
        info += scancodes[arg.key];
        printf("OIS: %s\n", info.c_str());
    }

    return false;
}

//-----------------------------------------------------------------------
//                        k e y R e l e a s e d
//-----------------------------------------------------------------------
bool COIS::keyReleased( const OIS::KeyEvent& arg ) 
{
    if(m_GUIEnabled)
    {
        irr::SEvent event;
        event.EventType = irr::EET_KEY_INPUT_EVENT;
        event.KeyInput.Key = (irr::EKEY_CODE)arg.key;
        event.KeyInput.Char = arg.text;
        event.KeyInput.PressedDown = false;
        event.KeyInput.Shift = m_keyboard->isModifierDown(OIS::Keyboard::Shift);
        event.KeyInput.Control = m_keyboard->isModifierDown(OIS::Keyboard::Ctrl);

        if (m_gui)
            m_gui->postEventFromUser(event);
        if(m_GUIExclusive)
            return true;
    }

    if(m_debugEnabled)
    {
        stringc info = "key.up.";
        info += scancodes[arg.key];
        printf("OIS: %s\n", info.c_str());
    }

    return false;
}

//-----------------------------------------------------------------------
//                        m o u s e M o v e d
//-----------------------------------------------------------------------
bool COIS::mouseMoved( const OIS::MouseEvent &arg ) {

    if(m_GUIEnabled)
    {
        irr::SEvent event;
        event.EventType = irr::EET_MOUSE_INPUT_EVENT;
        event.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
        event.MouseInput.X = arg.state.X.abs;
        event.MouseInput.Y = arg.state.Y.abs;

        if (m_gui)
            m_gui->postEventFromUser(event);

        if(m_GUIExclusive)
            return true;
    }

    if(m_debugEnabled)
    {
        printf("OIS: mouse.move (%d,%d)\n", arg.state.X.abs, arg.state.Y.abs);
    }

    return false;
}

//-----------------------------------------------------------------------
//                        m o u s e P r e s s e d
//-----------------------------------------------------------------------
bool COIS::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {

    static EMOUSE_INPUT_EVENT mxlat[]=
    {EMIE_LMOUSE_PRESSED_DOWN,EMIE_RMOUSE_PRESSED_DOWN,EMIE_MMOUSE_PRESSED_DOWN,
    EMIE_LMOUSE_PRESSED_DOWN,EMIE_LMOUSE_PRESSED_DOWN,EMIE_LMOUSE_PRESSED_DOWN,
    EMIE_LMOUSE_PRESSED_DOWN,EMIE_LMOUSE_PRESSED_DOWN};

    if(m_GUIEnabled)
    {
        irr::SEvent event;
        event.EventType = irr::EET_MOUSE_INPUT_EVENT;
        event.MouseInput.Event = mxlat[id];
        event.MouseInput.X = arg.state.X.abs;
        event.MouseInput.Y = arg.state.Y.abs;

        if (m_gui)
            m_gui->postEventFromUser(event);

        if(m_GUIExclusive)
            return true;
    }

    if(m_debugEnabled)
    {
        printf("OIS: mouse.pressed(%d) (%d,%d)\n", id, arg.state.X.abs, arg.state.Y.abs);
    }
    return false;
}

//-----------------------------------------------------------------------
//                      m o u s e R e l e a s e d
//-----------------------------------------------------------------------
bool COIS::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
    static EMOUSE_INPUT_EVENT mxlat[]=
    {EMIE_LMOUSE_LEFT_UP,EMIE_RMOUSE_LEFT_UP,EMIE_MMOUSE_LEFT_UP,
    EMIE_LMOUSE_LEFT_UP,EMIE_LMOUSE_LEFT_UP,EMIE_LMOUSE_LEFT_UP,
    EMIE_LMOUSE_LEFT_UP,EMIE_LMOUSE_LEFT_UP};

    if(m_GUIEnabled)
    {
        irr::SEvent event;
        event.EventType = irr::EET_MOUSE_INPUT_EVENT;
        event.MouseInput.Event = mxlat[id];
        event.MouseInput.X = arg.state.X.abs;
        event.MouseInput.Y = arg.state.Y.abs;

        if (m_gui)
            m_gui->postEventFromUser(event);
        if(m_GUIExclusive)
            return true;
    }

    if(m_debugEnabled)
    {
        printf("OIS: mouse.released(%d) (%d,%d)\n", id, arg.state.X.abs, arg.state.Y.abs);
    }

    return false;
}

//-----------------------------------------------------------------------
//                      b u t t o n P r e s s e d
//-----------------------------------------------------------------------
bool COIS::buttonPressed( const OIS::JoyStickEvent &arg, int button ) {


    if(m_debugEnabled)
    {
        printf("OIS: joy.buttonPressed(%d)\n", button);
    }
    return true;
}

//-----------------------------------------------------------------------
//                      b u t t o n R e l e a s e d
//-----------------------------------------------------------------------
bool COIS::buttonReleased( const OIS::JoyStickEvent &arg, int button ) {
    if(m_debugEnabled)
    {
        printf("OIS: joy.buttonReleased(%d)\n", button);
    }
    return false;
}

//-----------------------------------------------------------------------
//                          a x i s M o v e d
//-----------------------------------------------------------------------
bool COIS::axisMoved( const OIS::JoyStickEvent &arg, int axis )
{
    if(m_debugEnabled)
    {
        printf("OIS: joy.axisMoved(%d) (%s)\n", axis,
            arg.state.mAxes[axis].abs);
    }
    return false;
}

//-----------------------------------------------------------------------
//                           p o v M o v e d
//-----------------------------------------------------------------------
bool COIS::povMoved( const OIS::JoyStickEvent &arg, int pov )
{
    if(m_debugEnabled)
    {
        printf("OIS: joy.povMoved(%d), direction=%s\n", arg.state.mPOV[pov].direction);
    }
    return true;
}
