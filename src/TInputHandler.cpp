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

		//char keyChar = (char)((OIS::Keyboard*)(arg.device))->lookupCharMapping(arg.key);

        if(m_GUIEnabled)
        {
            CEGUI::System::getSingleton().injectKeyDown( arg.key );
            CEGUI::System::getSingleton().injectChar( arg.text );
            if(m_GUIExclusive)
                return true;
        }        


		
		string sKeyString = "key.down." + ((OIS::Keyboard*)(arg.device))->getAsString(arg.key);
        TSEvent event;
        event.bind(new TEvent(sKeyString));
        event->addIntParameter(arg.key);            // key
        event->addIntParameter(1);                  // state 1=down
        m_eventManager->send(event);

        //m_pInput->type = OISKeyboard;
		//m_pInput->udm = IDOWN;
        //m_pInput->time = m_pTimer->getMilliseconds();
		//m_pInput->key = arg.key;
		//m_pInput->keyString = (char *)sKeyString.c_str();

        //m_pApplication->VOnInputProc(m_pInput);

		return true;
	}

    //-----------------------------------------------------------------------
    //                        k e y R e l e a s e d
    //-----------------------------------------------------------------------
	bool TInputHandler::keyReleased( const OIS::KeyEvent& arg ) 
	{
		//char keyChar = (char)((OIS::Keyboard*)(arg.device))->lookupCharMapping(arg.key);

        if(m_GUIEnabled)
        {
		    CEGUI::System::getSingleton().injectKeyUp( arg.key );
            if(m_GUIExclusive)
                return true;
        }
		
		string sKeyString = "key.up." + ((OIS::Keyboard*)(arg.device))->getAsString(arg.key);
        TSEvent event;
        event.bind(new TEvent(sKeyString));
        event->addIntParameter(arg.key);            // key
        event->addIntParameter(0);                  // state 0=up
        m_eventManager->send(event);

        /*
        m_pInput->type = OISKeyboard;
		m_pInput->udm = IUP;
        m_pInput->time = m_pTimer->getMilliseconds();
		m_pInput->key = arg.key;
		m_pInput->keyString = (char *)sKeyString.c_str();
        m_pApplication->VOnInputProc(m_pInput);
        */

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
        /*
        m_pInput->type = OISMouse;
		m_pInput->udm = IMOVE;
        m_pInput->time = m_pTimer->getMilliseconds();
        m_pInput->AbsX = arg.state.abX;
        m_pInput->AbsY = arg.state.abY;
        m_pInput->AbsZ = arg.state.abZ;
        m_pInput->RelX = arg.state.relX;
        m_pInput->RelY = arg.state.relY;
        m_pInput->RelZ = arg.state.relZ;
        */

        //m_pScript->input_MouseMoved(m_pInput);
        /*
		std::cout << "MouseMoved: abs(" << arg.state.abX << "," << arg.state.abY <<
			"," << arg.state.abZ << ") rel(" << arg.state.relX << "," << arg.state.relY <<
			"," << arg.state.relZ << ")\n";
            */
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
        /*
        m_pInput->type = OISMouse;
		m_pInput->udm = IDOWN;
        */
		// std::cout << "MousePressed: " << id << " time[" << arg.timeStamp << "]\n";
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
		// std::cout << "MouseReleased: " << id << " time[" << arg.timeStamp << "]\n";
        /*
        m_pInput->type = OISMouse;
		m_pInput->udm = IUP;
        */
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

