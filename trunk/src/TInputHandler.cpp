//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

#ifdef TUBRAS_PLATFORM_WIN32
	#if !defined ( _WIN32_WCE )
		#include <io.h>
		#include <direct.h>
	#endif
#else
	#include <unistd.h>
	#include <limits.h>
	#include <stdlib.h>
#endif
#include <errno.h>
#include <stdio.h>

using namespace OIS;

static Tubras::TString scancodes[]=
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

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                       T I n p u t H a n d l e r 
    //-----------------------------------------------------------------------
    TInputHandler::TInputHandler() : m_eventManager(getEventManager()),
        m_GUIEnabled(false),
        m_GUIExclusive(false),
        m_binder(0),
        m_kpEvent(0),
        m_krEvent(0),
        m_mmEvent(0),
        m_mpEvent(0),
        m_mrEvent(0)
    {
    }

    //-----------------------------------------------------------------------
    //                     ~ T I n p u t H a n d l e r 
    //-----------------------------------------------------------------------
    TInputHandler::~TInputHandler()
    {
        if(m_binder)
            delete m_binder;

        if(m_kpEvent)
            m_kpEvent->drop();
        if(m_krEvent)
            m_krEvent->drop();
        if(m_mmEvent)
            m_mmEvent->drop();
        if(m_mpEvent)
            m_mpEvent->drop();
        if(m_mrEvent)
            m_mrEvent->drop();
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

        m_binder = new TInputBinder();
        if(m_binder->initialize())
            result = 1;

        m_kpEvent= new TEvent();
        m_kpEvent->addIntParameter(0);
        m_kpEvent->addIntParameter(0);

        m_krEvent= new TEvent();
        m_krEvent->addIntParameter(0);
        m_krEvent->addIntParameter(0);

        m_mmEvent = new TEvent("input.mouse.move");
        m_mmEvent->addPointerParameter(0);

        m_mpEvent= new TEvent();
        m_mpEvent->addPointerParameter(0);

        m_mrEvent= new TEvent();
        m_mrEvent->addPointerParameter(0);

        return result;
    }

    //-----------------------------------------------------------------------
    //                           k e y P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::keyPressed( const OIS::KeyEvent& arg ) 
    {

        if(m_GUIEnabled)
        {
            //TGUI::TGSystem::getSingleton().injectKeyDown( arg.key, arg.text );
            if(m_GUIExclusive)
                return true;
        }        

        TString sKeyString = "key.down.";
        sKeyString += scancodes[arg.key];
        m_kpEvent->setName(sKeyString);
        m_kpEvent->getParameter(0)->setIntValue(arg.key);
        m_kpEvent->getParameter(1)->setIntValue(1);

        m_eventManager->send(m_kpEvent);

        m_binder->processKey(sKeyString);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        k e y R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::keyReleased( const OIS::KeyEvent& arg ) 
    {
        if(m_GUIEnabled)
        {
            //TGUI::TGSystem::getSingleton().injectKeyUp( arg.key, arg.text );
            if(m_GUIExclusive)
                return true;
        }

        TString sKeyString = "key.up.";
        sKeyString += scancodes[arg.key];
        m_krEvent->setName(sKeyString);
        m_krEvent->getParameter(0)->setIntValue(arg.key);
        m_krEvent->getParameter(1)->setIntValue(1);

        m_eventManager->send(m_krEvent);

        m_binder->processKey(sKeyString);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        m o u s e M o v e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mouseMoved( const OIS::MouseEvent &arg ) {

        if(m_GUIEnabled)
        {
            //TGUI::TGSystem::getSingleton().injectMouseMove( arg.state.X.rel, arg.state.Y.rel );
            if(m_GUIExclusive)
                return true;
        }


        m_mmEvent->getParameter(0)->setPointerValue((void*)&arg);

        m_eventManager->send(m_mmEvent);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        m o u s e P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
        char buf[100];

        if(m_GUIEnabled)
        {
            //TGUI::TGSystem::getSingleton().injectMouseButtonDown(arg.state.X.rel,arg.state.Y.rel,id);
            if(m_GUIExclusive)
                return true;
        }

        sprintf(buf,"%d",id);
        TString sID = buf;

        TString eventMsg = "input.mouse.down.";
        eventMsg += sID;
        m_mpEvent->setName(eventMsg);
        m_mpEvent->getParameter(0)->setPointerValue((void *)&arg);
        m_eventManager->send(m_mpEvent);

        return true;
    }

    //-----------------------------------------------------------------------
    //                      m o u s e R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
        char buf[100];

        if(m_GUIEnabled)
        {
            //TGUI::TGSystem::getSingleton().injectMouseButtonUp(arg.state.X.rel,arg.state.Y.rel,id);
            if(m_GUIExclusive)
                return true;
        }
        sprintf(buf,"%d",id);
        TString sID = buf;

        TString eventMsg = "input.mouse.up.";
        eventMsg += sID;

        m_mrEvent->setName(eventMsg);
        m_mrEvent->getParameter(0)->setPointerValue((void *)&arg);
        m_eventManager->send(m_mrEvent);

        return true;
    }

    //-----------------------------------------------------------------------
    //                      b u t t o n P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::buttonPressed( const OIS::JoyStickEvent &arg, int button ) {
        std::cout << "Joy ButtonPressed: " << button << "\n";
        //m_pInput->type = OISMouse;
        return true;
    }

    //-----------------------------------------------------------------------
    //                      b u t t o n R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::buttonReleased( const OIS::JoyStickEvent &arg, int button ) {
        std::cout << "Joy ButtonReleased: " << button << "\n";
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

