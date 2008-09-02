//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
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

using namespace OIS;
namespace Tubras
{
    const char *g_DeviceType[6] = {"OISUnknown", "OISKeyboard", "OISMouse", "OISJoyStick",
							       "OISTablet", "OISOther"};


    //-----------------------------------------------------------------------
    //                       T I n p u t M a n a g e r
    //-----------------------------------------------------------------------
    TInputManager::TInputManager(size_t window_handle) : m_InputManager(0)
    {

        m_WindowHandle = window_handle;
        m_lpKeyboard = NULL;
        m_lpMouse = NULL;

    }

    //-----------------------------------------------------------------------
    //                      ~T I n p u t M a n a g e r
    //-----------------------------------------------------------------------
    TInputManager::~TInputManager()
    {

        if( m_InputManager )
        {
            if(m_lpKeyboard)
                m_InputManager->destroyInputObject( m_lpKeyboard );
            if(m_lpMouse)
                m_InputManager->destroyInputObject( m_lpMouse );
            InputManager::destroyInputSystem(m_InputManager);

            if(m_pInputHandler)
            {
                delete m_pInputHandler;
                m_pInputHandler = NULL;
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
        wnd << (unsigned int)m_WindowHandle; 

        pl.insert(std::make_pair( TString("WINDOW"), wnd.str() ));

        //Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
        pl.insert(std::make_pair(TString("w32_mouse"), TString("DISCL_FOREGROUND" )));

        TString doShow = getApplication()->getConfigFile()->getSetting("ShowMouseCursor","Options");
        if(doShow == "true")
            pl.insert(std::make_pair(TString("w32_mouse"), TString("DISCL_NONEXCLUSIVE")));
        else pl.insert(std::make_pair(TString("w32_mouse"), TString("DISCL_EXCLUSIVE")));

        //This never returns null.. it will raise an exception on errors

        m_InputManager = InputManager::createInputSystem(pl);
        m_pInputHandler = new TInputHandler();
        if(m_pInputHandler->Initialize())
            return 1;


        std::cout << "Input Manager [" << m_InputManager->inputSystemName() << "]" 
            << "\n Numer of Mice: " << m_InputManager->numMice()
            << "\n Number of Keyboards: " << m_InputManager->numKeyboards()
            << "\n Number of Joys/Pads = " << m_InputManager->numJoySticks() << "\n\n";

        m_lpMouse = 0;
        m_lpKeyboard = 0;


		//Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
        m_lpKeyboard = static_cast<Keyboard*>(m_InputManager->createInputObject( OISKeyboard, true ));
        m_lpKeyboard->setEventCallback( m_pInputHandler );
		m_lpMouse = static_cast<Mouse*>(m_InputManager->createInputObject( OISMouse, true ));
        m_lpMouse->setEventCallback( m_pInputHandler );
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
        InputManager::DeviceList list = m_InputManager->listFreeDevices();
        for( InputManager::DeviceList::iterator i = list.begin(); i != list.end(); ++i )
        {
            std::cout << "\n\tDevice: " << g_DeviceType[i->first] << " Vendor: " << i->second;
            if( i->first == OISKeyboard && m_lpKeyboard == 0 )
            {	//Create keyboard
                m_lpKeyboard = (Keyboard*)m_InputManager->createInputObject( OISKeyboard, true );
                m_lpKeyboard->setEventCallback( m_pInputHandler );
            }
            else if( i->first == OISMouse && m_lpMouse == 0 )
            {	//Create mouse and adjust window size
                m_lpMouse = (Mouse*)m_InputManager->createInputObject( OISMouse, true );
                m_lpMouse->setEventCallback( m_pInputHandler );
                const MouseState &ms = m_lpMouse->getMouseState();
                ms.width = 100;
                ms.height = 100;
            }
        }

        //This uses at most 4 joysticks - use old way to create (i.e. disregard vendor
        //and just create first joysticks in list).
        m_numSticks = std::min(m_InputManager->getNumberOfDevices(OISJoyStick), 4);

        for( int i = 0; i < m_numSticks; ++i )
        {
            m_lpJoys[i] = (JoyStick*)m_InputManager->createInputObject( OISJoyStick, true );
            m_lpJoys[i]->setEventCallback( m_pInputHandler );
        }
        */

        return result;
    }

    //-----------------------------------------------------------------------
    //                        s e t S c r e e n S i z e
    //-----------------------------------------------------------------------
    void TInputManager::setDisplaySize(int width, int height)
    {
        m_lpMouse->getMouseState().width = width;
        m_lpMouse->getMouseState().height = height;
    }

    //-----------------------------------------------------------------------
    //                              s t e p 
    //-----------------------------------------------------------------------
    int TInputManager::step()
    {
        int result=0;

        if(m_lpKeyboard)
            m_lpKeyboard->capture();
        if(m_lpMouse)
            m_lpMouse->capture();

        return result;
    }

    //-----------------------------------------------------------------------
    //                        s e t G U I E n a b l e d
    //-----------------------------------------------------------------------
    void TInputManager::setGUIEnabled(bool enabled)
    {
        m_pInputHandler->setGUIEnabled(enabled);
    }

    //-----------------------------------------------------------------------
    //                     s e t G U I E x c l u s i v e
    //-----------------------------------------------------------------------
    void TInputManager::setGUIExclusive(bool exclusive)
    {
        m_pInputHandler->setGUIExclusive(exclusive);
    }

    //-----------------------------------------------------------------------
    //                         i s K e y D o w n 
    //-----------------------------------------------------------------------
	bool TInputManager::isKeyDown(OIS::KeyCode key)
	{
		return m_lpKeyboard->isKeyDown(key);
	}



}
