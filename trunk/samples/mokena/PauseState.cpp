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
#include "mokena.h"

#define SLIDE_DURATION 0.9f

TPauseState::TPauseState() : TState("pauseState")
{
}

TPauseState::~TPauseState()
{
}

int TPauseState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_parent = sm->getRootSceneNode()->createChildSceneNode("PauseParent");

    m_parent->flipVisibility();

    m_finterval = new Tubras::TFunctionInterval("PauseslideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TPauseState::animateMenu));

    m_finterval->setDoneEvent("PauseslideDone");
    acceptEvent("PauseslideDone",EVENT_DELEGATE(TPauseState::animateDone));
    acceptEvent("key.down.esc",EVENT_DELEGATE(TPauseState::escape));

    TGUI::TGSystem* system = getGUISystem();

    m_frame = new TGUI::TGImage(0,"PauseMenu", "menusheet.png");
    m_frame->setPos(1.0f,0.0f);
    m_frame->setSize(0.5f,1.0f);

    m_window = new TGUI::TGWindow(0,"","Paused");
    //
    // window constructors with a null parent defaults the parent to the active screen.
    // ensure we our parent is really null - we'll hook into the playstate gui
    // when we're activated.
    //
    m_window->center();
    m_window->moveRel(m_window->x1, m_window->y1-100);
    m_window->resize(190, 200);
    m_window->setResizeEnabled(true);
    m_window->reParent(0);        


    m_parent->flipVisibility();
    disableEvents(this);

    return 0;
}

//-----------------------------------------------------------------------
//                            e s c a p e
//-----------------------------------------------------------------------
int TPauseState::escape(Tubras::TSEvent event)
{
    popState();
    return 1;   // eat the event
}

int TPauseState::mouseDown(Tubras::TSEvent event)
{
    if(m_finterval->isPlaying())
        return 0;

    /*
    m_finterval->start();
    if(slideDirection < 0)
    sound1->play();
    else sound2->play();
    */
    return 0;
}

int TPauseState::quitApp(Tubras::TSEvent event)
{
    m_app->stopRunning();
    return 0;
}

int TPauseState::animateDone(Tubras::TSEvent event)
{
    return 0;
}


void TPauseState::animateMenu(double T, void* userData)
{
    /*
    double value;
    if(slideDirection > 0)
        value = 0.5f + ((T / SLIDE_DURATION) * 0.5f);
    else value = 1.0f - ((T / SLIDE_DURATION) * 0.5f);
    m_frame->setPos(value,0.f);
    */
}

/*
int TPauseState::quitClicked(Tubras::TSEvent event)
{
   
    m_doQuit = true;
    m_finterval->start();
    sound2->play();    
   
    return true;
}
*/

/*
int TPauseState::playClicked(Tubras::TSEvent event)
{
    m_doPlay = true;
    m_finterval->start();
    sound2->play();
    return 0;
}
*/

int TPauseState::Enter()
{
    //
    // do this so mouse show works the first time around (sets d_wndWithMouse)
    //
    //m_doPlay = false;
    //m_doQuit = false;
    m_parent->flipVisibility();
    m_window->reParent(getGUIManager()->getSystem()->getActiveScreen());
    m_window->setVisible(true);
    setGUIEnabled(true);
    m_window->makeExclusive();
    m_finterval->start();
    //sound1->play();
    enableEvents(this);
    return 0;
}

Tubras::TStateInfo* TPauseState::Exit()
{
    m_parent->flipVisibility();
    m_window->makeExclusive(false);
    m_window->setVisible(false);
    m_window->reParent(0);

    disableEvents(this);
    return &m_info;
}

int TPauseState::Reset()
{
    return 0;
}

int TPauseState::Pause()
{
    Exit();

    return 0;
}

int TPauseState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    Enter();
    return 0;
}


