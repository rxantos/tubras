//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "tubras.h"
#ifdef _IRR_LINUX_PLATFORM_
#ifdef _IRR_COMPILE_WITH_X11_
#include <X11/Xlib.h>
#endif
#endif

using namespace OIS;
namespace Tubras
{
    const char* wmDeleteWindow = "WM_DELETE_WINDOW";
    const char *g_DeviceType[6] = {"OISUnknown", "OISKeyboard", "OISMouse", "OISJoyStick",
        "OISTablet", "OISOther"};


    //-----------------------------------------------------------------------
    //                       T I n p u t M a n a g e r
    //-----------------------------------------------------------------------
    TInputManager::TInputManager(u32 window_handle, u32 window_display) : m_inputManager(0),
        m_windowHandle(window_handle),
        m_display(window_display),
        m_inputHandler(0),
        m_keyboard(0),
        m_mouse(0)
    {
    }

    //-----------------------------------------------------------------------
    //                      ~T I n p u t M a n a g e r
    //-----------------------------------------------------------------------
    TInputManager::~TInputManager()
    {

        if( m_inputManager )
        {
            if(m_keyboard)
                m_inputManager->destroyInputObject( m_keyboard );
            if(m_mouse)
                m_inputManager->destroyInputObject( m_mouse );
            InputManager::destroyInputSystem(m_inputManager);

            if(m_inputHandler)
            {
                delete m_inputHandler;
                m_inputHandler = 0;
            }
        }
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r 
    //-----------------------------------------------------------------------
    template<> TInputManager* TSingleton<TInputManager>::ms_Singleton = 0;

    TInputManager* TInputManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n 
    //-----------------------------------------------------------------------
    TInputManager& TInputManager::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }

    //-----------------------------------------------------------------------
    //                          I n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TInputManager::initialize()
    {
        int result=0;

        ParamList pl;
        std::stringstream wnd;
        wnd << (unsigned int)m_windowHandle; 

        pl.insert(std::make_pair( "WINDOW", wnd.str() ));

#ifdef WIN32
        //Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
        pl.insert(std::make_pair("w32_mouse", "DISCL_FOREGROUND"));

        bool doShow = getApplication()->getConfig()->getBool("showcursor","options");
        if(doShow)
            pl.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));
        else pl.insert(std::make_pair("w32_mouse", "DISCL_EXCLUSIVE"));
#else
        pl.insert(std::make_pair("x11_keyboard_grab","false"));
        pl.insert(std::make_pair("x11_mouse_grab","true"));
        pl.insert(std::make_pair("x11_mouse_hide","true"));
        XSelectInput((Display*)m_display,m_windowHandle, StructureNotifyMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);        
#endif

        //This never returns null.. it will raise an exception on errors

        m_inputManager = InputManager::createInputSystem(pl);
        m_inputHandler = new TInputHandler();
        if(m_inputHandler->Initialize())
            return 1;       

        unsigned int v = m_inputManager->getVersionNumber();
        std::cout << "OIS Version: " << (v>>16 ) << "." << ((v>>8) & 0x000000FF) << "." << (v & 0x000000FF)
            << "\nRelease Name: " << m_inputManager->getVersionName()
            << "\nManager: " << m_inputManager->inputSystemName()
            << "\nTotal Keyboards: " << m_inputManager->getNumberOfDevices(OISKeyboard)
            << "\nTotal Mice: " << m_inputManager->getNumberOfDevices(OISMouse)
            << "\nTotal JoySticks: " << m_inputManager->getNumberOfDevices(OISJoyStick);

        //List all devices
        OIS::DeviceList list = m_inputManager->listFreeDevices();
        for( DeviceList::iterator i = list.begin(); i != list.end(); ++i )
            std::cout << "\n\tDevice: " << g_DeviceType[i->first] << " Vendor: " << i->second;

        m_mouse = 0;
        m_keyboard = 0;


        //Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
        m_keyboard = static_cast<Keyboard*>(m_inputManager->createInputObject( OISKeyboard, true ));
        m_keyboard->setEventCallback( m_inputHandler );
        m_mouse = static_cast<Mouse*>(m_inputManager->createInputObject( OISMouse, true ));
        m_mouse->setEventCallback( m_inputHandler );
        /*
        try {
        mJoy = static_cast<JoyStick*>(mInputManager->createInputObject( OISJoyStick, bufferedJoy ));
        }
        catch(...) {
        mJoy = 0;
        }
        */

        /*

        //List all devices, and create keyboard & mouse if found (we could do it the old way
        //also, but just want to show how to create using vendor name).
        InputManager::DeviceList list = m_inputManager->listFreeDevices();
        for( InputManager::DeviceList::iterator i = list.begin(); i != list.end(); ++i )
        {
        std::cout << "\n\tDevice: " << g_DeviceType[i->first] << " Vendor: " << i->second;
        if( i->first == OISKeyboard && m_keyboard == 0 )
        {	//Create keyboard
        m_keyboard = (Keyboard*)m_inputManager->createInputObject( OISKeyboard, true );
        m_keyboard->setEventCallback( m_inputHandler );
        }
        else if( i->first == OISMouse && m_mouse == 0 )
        {	//Create mouse and adjust window size
        m_mouse = (Mouse*)m_inputManager->createInputObject( OISMouse, true );
        m_mouse->setEventCallback( m_inputHandler );
        const MouseState &ms = m_mouse->getMouseState();
        ms.width = 100;
        ms.height = 100;
        }
        }

        //This uses at most 4 joysticks - use old way to create (i.e. disregard vendor
        //and just create first joysticks in list).
        m_numSticks = std::min(m_inputManager->getNumberOfDevices(OISJoyStick), 4);

        for( int i = 0; i < m_numSticks; ++i )
        {
        m_lpJoys[i] = (JoyStick*)m_inputManager->createInputObject( OISJoyStick, true );
        m_lpJoys[i]->setEventCallback( m_inputHandler );
        }
        */

        return result;
    }

    //-----------------------------------------------------------------------
    //                        s e t S c r e e n S i z e
    //-----------------------------------------------------------------------
    void TInputManager::setDisplaySize(int width, int height)
    {
        m_mouse->getMouseState().width = width;
        m_mouse->getMouseState().height = height;
    }

    //-----------------------------------------------------------------------
    //                              s t e p 
    //-----------------------------------------------------------------------
    int TInputManager::step()
    {

        int result=0;
        if(m_keyboard)
            m_keyboard->capture();
        if(m_mouse)
            m_mouse->capture();

        return result;
    }

    //-----------------------------------------------------------------------
    //                        s e t G U I E n a b l e d
    //-----------------------------------------------------------------------
    void TInputManager::setGUIEnabled(bool enabled)
    {
        m_inputHandler->setGUIEnabled(enabled);
    }

    //-----------------------------------------------------------------------
    //                     s e t G U I E x c l u s i v e
    //-----------------------------------------------------------------------
    void TInputManager::setGUIExclusive(bool exclusive)
    {
        m_inputHandler->setGUIExclusive(exclusive);
    }

    //-----------------------------------------------------------------------
    //                         i s K e y D o w n 
    //-----------------------------------------------------------------------
    bool TInputManager::isKeyDown(OIS::KeyCode key)
    {
        return m_keyboard->isKeyDown(key);
    }
}

