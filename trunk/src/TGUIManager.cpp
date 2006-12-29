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

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T G U I M a n a g e r
    //-----------------------------------------------------------------------
    TGUIManager::TGUIManager() : TObject()
    {
    }

    //-----------------------------------------------------------------------
    //                        ~T G U I M a n a g e r
    //-----------------------------------------------------------------------
    TGUIManager::~TGUIManager()
    {
        if(m_GUISystem)
            delete m_GUISystem;
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r 
    //-----------------------------------------------------------------------
    template<> TGUIManager* TSingleton<TGUIManager>::ms_Singleton = 0;

    TGUIManager* TGUIManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n 
    //-----------------------------------------------------------------------
    TGUIManager& TGUIManager::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }

    //-----------------------------------------------------------------------
    //                          I n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TGUIManager::initialize(Ogre::RenderWindow* window, Ogre::SceneManager* sceneMgr, string defaultFont)
    {
        int result=0;

        m_GUISystem = new TGUI::TGSystem(window,sceneMgr,defaultFont);

        m_GUIRenderer = m_GUISystem->getRenderer();

        m_GUILogger = m_GUISystem->getLogger();        

        m_GUISystem->setEventHook(TGEVENT_HANDLER(TGUIManager::eventHook));

        return result;
    }

    //-----------------------------------------------------------------------
    //                         e v e n t H o o k
    //-----------------------------------------------------------------------
    bool TGUIManager::eventHook(const TGUI::TGEventArgs& args)
    {
        TStrStream sEvent;
        sEvent << "gui." << args.m_control->getName() << "." << args.m_eventID;

        TSEvent evt;
        evt.bind(new TEvent(sEvent.str()));
        if(sendEvent(evt))
            return true;

        return false;
    }

    //-----------------------------------------------------------------------
    //                     i n j e c t T i m e P u l s e
    //-----------------------------------------------------------------------
    void TGUIManager::injectTimePulse(float timeElapsed)
    {
        return m_GUISystem->injectTimePulse(timeElapsed/1000.f);
    }

}