//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#include "tubras.h"
#include "stdlib.h"

using namespace OIS;

static string scancodes[]=
{
    "0x00","esc","1","2","3","4","5","6","7","8","9","0",
    "-","=","back","tab",
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
    "webhome","numpadcomma", "0xb4","divide", "0xb6","sysrq","rmenu",
    "0xb9","0xba","0xbb","0xbc","0xbd","0xbe", "0xbf","0xc0","0xc1",
    "0xc2","0xc3","0xc4","pause","0xc6","home","up","pgup","0xca",
    "left", "0xcc","right", "0xce","end","down","pgdown","insert",
    "delete","0xd4","0xd5","0xd6","0xd7","0xd8","0xd9","0xda","lwin",
    "rwin","apps","power","sleep","0xe0","0xe1","0xe2","wake", "0xe4",
    "websearch","webfavorites","webstop","webforward","webback",
    "mycomputer","mail","mediaselect"
};

namespace Tubras
{

    //-----------------------------------------------------------------------
    //         c o n v e r t O I S M o u s e B u t t o n T o C e g u i
    //-----------------------------------------------------------------------
    CEGUI::MouseButton convertOISMouseButtonToCegui(int buttonID)
    {
        switch (buttonID)
        {
        case 0: return CEGUI::LeftButton;
        case 1: return CEGUI::RightButton;
        case 2:	return CEGUI::MiddleButton;
        case 3: return CEGUI::X1Button;
        default: return CEGUI::LeftButton;
        }
    }


    //-----------------------------------------------------------------------
    //                       T I n p u t H a n d l e r 
    //-----------------------------------------------------------------------
    TInputHandler::TInputHandler()
    {

        m_pApplication = getApplication();
        m_pTimer = m_pApplication->getGlobalClock();
        m_eventManager = getEventManager();
        m_GUIEnabled = false;
        m_GUIExclusive = false;

    }

    //-----------------------------------------------------------------------
    //                     ~ T I n p u t H a n d l e r 
    //-----------------------------------------------------------------------
    TInputHandler::~TInputHandler()
    {

    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r 
    //-----------------------------------------------------------------------
    template<> TInputHandler* TSingleton<TInputHandler>::ms_Singleton = 0;

    TInputHandler* TInputHandler::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n 
    //-----------------------------------------------------------------------
    TInputHandler& TInputHandler::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }

    //-----------------------------------------------------------------------
    //                          I n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TInputHandler::Initialize()
    {
        int result=0;

        return result;
    }

    //-----------------------------------------------------------------------
    //                           k e y P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::keyPressed( const OIS::KeyEvent& arg ) 
    {

        if(m_GUIEnabled)
        {
            CEGUI::System::getSingleton().injectKeyDown( arg.key );
            CEGUI::System::getSingleton().injectChar( arg.text );
            if(m_GUIExclusive)
                return true;
        }        

        string sKeyString = "key.down." + scancodes[arg.key];
        TSEvent event;
        event.bind(new TEvent(sKeyString));
        event->addIntParameter(arg.key);            // key
        event->addIntParameter(1);                  // state 1=down
        m_eventManager->send(event);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        k e y R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::keyReleased( const OIS::KeyEvent& arg ) 
    {
        if(m_GUIEnabled)
        {
            CEGUI::System::getSingleton().injectKeyUp( arg.key );
            if(m_GUIExclusive)
                return true;
        }

        string sKeyString = "key.up." + scancodes[arg.key];
        TSEvent event;
        event.bind(new TEvent(sKeyString));
        event->addIntParameter(arg.key);            // key
        event->addIntParameter(0);                  // state 0=up
        m_eventManager->send(event);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        m o u s e M o v e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mouseMoved( const OIS::MouseEvent &arg ) {

        if(m_GUIEnabled)
        {
            CEGUI::System::getSingleton().injectMouseMove( arg.state.relX, arg.state.relY );
            if(m_GUIExclusive)
                return true;
        }

        TSEvent event;
        event.bind(new TEvent("input.mouse.move"));
        event->addPointerParameter((void *)&arg);
        m_eventManager->send(event);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        m o u s e P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
        char buf[100];

        if(m_GUIEnabled)
        {
            CEGUI::System::getSingleton().injectMouseButtonDown(convertOISMouseButtonToCegui(id));
            if(m_GUIExclusive)
                return true;
        }
        _itoa(id,buf,10);
        string sID = buf;

        string eventMsg = "input.mouse.down." + sID;
        TSEvent event;
        event.bind(new TEvent(eventMsg));
        event->addPointerParameter((void *)&arg);
        m_eventManager->send(event);
        return true;
    }

    //-----------------------------------------------------------------------
    //                      m o u s e R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
        char buf[100];

        if(m_GUIEnabled)
        {
            CEGUI::System::getSingleton().injectMouseButtonUp(convertOISMouseButtonToCegui(id));
            if(m_GUIExclusive)
                return true;
        }
        _itoa(id,buf,10);
        string sID = buf;

        string eventMsg = "input.mouse.up." + sID;

        TSEvent event;
        event.bind(new TEvent(eventMsg));
        event->addPointerParameter((void *)&arg);

        m_eventManager->send(event);

        return true;
    }

    //-----------------------------------------------------------------------
    //                      b u t t o n P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::buttonPressed( const OIS::JoyStickEvent &arg, int button ) {
        std::cout << "Joy ButtonPressed: " << button << " time[" << arg.timeStamp << "]\n";
        //m_pInput->type = OISMouse;
        return true;
    }

    //-----------------------------------------------------------------------
    //                      b u t t o n R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::buttonReleased( const OIS::JoyStickEvent &arg, int button ) {
        std::cout << "Joy ButtonReleased: " << button << " time[" << arg.timeStamp << "]\n";
        //m_pInput->type = OISMouse;
        return true;
    }

    //-----------------------------------------------------------------------
    //                          a x i s M o v e d
    //-----------------------------------------------------------------------
    bool TInputHandler::axisMoved( const OIS::JoyStickEvent &arg, int axis )
    {
        //std::cout << "\nJoy Axis: " << axis 
        //	  << " absolute X: " << arg.state.mAxes[axis].abX 
        //	  << " absolute Y: " << arg.state.mAxes[axis].abY
        //	  << " absolute Z: " << arg.state.mAxes[axis].abZ << std::endl;
        //m_pInput->type = OISJoyStick;
        return true;
    }

    //-----------------------------------------------------------------------
    //                           p o v M o v e d
    //-----------------------------------------------------------------------
    bool TInputHandler::povMoved( const OIS::JoyStickEvent &arg, int pov )
    {
        /*
        std::cout << "Joy POV (" << pov + 1 
        << ") Moved.Value = " << arg.state.mPOV[pov] << std::endl;
        m_pInput->type = OISJoyStick;
        */
        return true;
    }



}

