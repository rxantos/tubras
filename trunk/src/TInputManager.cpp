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

using namespace OIS;
namespace Tubras
{
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

        if( InputManager::getSingletonPtr() )
        {
            if(m_lpKeyboard)
                InputManager::getSingletonPtr()->destroyInputObject( m_lpKeyboard );
            if(m_lpMouse)
                InputManager::getSingletonPtr()->destroyInputObject( m_lpMouse );

            //for(int i = 0; i < 4; ++i)
            //	InputManager::getSingletonPtr()->destroyInputObject( g_joys[i] );

            InputManager::destroyInputSystem();

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

        pl.insert(std::make_pair( std::string("WINDOW"), wnd.str() ));

        //Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
        pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));

        string doShow = getApplication()->getConfigFile()->getSetting("ShowMouseCursor","Options");
        if(doShow == "true")
            pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
        else pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_EXCLUSIVE")));

        //This never returns null.. it will raise an exception on errors

        m_InputManager = InputManager::createInputSystem(pl);
        m_pInputHandler = new TInputHandler();
        if(m_pInputHandler->Initialize())
            return 1;


        std::cout << "Input Manager [" << m_InputManager->inputSystemName() << "]" 
            << "\n Numer of Mice: " << m_InputManager->numMice()
            << "\n Number of Keyboards: " << m_InputManager->numKeyBoards()
            << "\n Number of Joys/Pads = " << m_InputManager->numJoysticks() << "\n\n";

        if( m_InputManager->numKeyBoards() > 0 )
        {
            m_lpKeyboard = (Keyboard*)m_InputManager->createInputObject( OISKeyboard, true );
            std::cout << "Created buffered keyboard\n";
            m_lpKeyboard->setEventCallback( m_pInputHandler );
        }

        if( m_InputManager->numMice() > 0 )
        {

            m_lpMouse = (Mouse*)m_InputManager->createInputObject( OISMouse, true );
            std::cout << "Created buffered mouse\n";
            m_lpMouse->setEventCallback( m_pInputHandler );

            const OIS::MouseState &ms = m_lpMouse->getMouseState();
            ms.width = 100;
            ms.height = 100;			
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                             C a p t u r e 
    //-----------------------------------------------------------------------
    int TInputManager::capture()
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

