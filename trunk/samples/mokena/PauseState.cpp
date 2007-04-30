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

//-----------------------------------------------------------------------
//                          T P a u s e S t a t e
//-----------------------------------------------------------------------
TPauseState::TPauseState() : TState("pauseState")
{
}

//-----------------------------------------------------------------------
//                         ~ T P a u s e S t a t e
//-----------------------------------------------------------------------
TPauseState::~TPauseState()
{
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TPauseState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_parent = sm->getRootSceneNode()->createChildSceneNode("PauseParent");

    m_parent->flipVisibility();

    m_finterval = new Tubras::TFunctionInterval("PauseslideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TPauseState::animateMenu));

    Tubras::TEventDelegate* resumeEvent = EVENT_DELEGATE(TPauseState::resume);
    m_finterval->setDoneEvent("PauseslideDone");
    acceptEvent("PauseslideDone",EVENT_DELEGATE(TPauseState::animateDone));
    acceptEvent("key.down.esc",resumeEvent);
    acceptEvent("gui.resumeButton.mouseClicked",resumeEvent);
    acceptEvent("gui.exitButton.mouseClicked",EVENT_DELEGATE(TPauseState::exitToMenu));

    Tubras::TEventDelegate* ed = EVENT_DELEGATE(TPauseState::mouseEnter);
    acceptEvent("gui.resumeButton.mouseEnter",ed);
    acceptEvent("gui.exitButton.mouseEnter",ed);

    ed = EVENT_DELEGATE(TPauseState::mouseDown);
    acceptEvent("gui.resumeButton.mouseDown",ed);
    acceptEvent("gui.exitButton.mouseDown",ed);


    m_guiRollover = loadSound("GUI_rollover.ogg");
    m_guiClick = loadSound("GUI_click.ogg");
    m_ambientSound = loadSound("ambient.ogg");
    m_ambientSound->setLoop(true);

    TGUI::TGSystem* system = getGUISystem();

    m_frame = new TGUI::TGImage(0,"PauseMenu", "pausedlg.png");
    m_frame->center();
    m_frame->reParent(0);

    TGUI::TGImageButton* b = new TGUI::TGImageButton(m_frame,"resumeButton","bresume.png");
    b->center();
    b->moveRel(b->x1,b->y1-40);

    b = new TGUI::TGImageButton(m_frame,"exitButton","bexit.png");
    b->center();
    b->moveRel(b->x1,b->y1+35);

    m_parent->flipVisibility();
    disableEvents(this);

    return 0;
}

//-----------------------------------------------------------------------
//                          m o u s e E n t e r
//-----------------------------------------------------------------------
int TPauseState::mouseEnter(Tubras::TSEvent event)
{
    m_guiRollover->play();
    return 1;
}

//-----------------------------------------------------------------------
//                          m o u s e D o w n
//-----------------------------------------------------------------------
int TPauseState::mouseDown(Tubras::TSEvent event)
{
    m_guiClick->play();
    return 1;
}

//-----------------------------------------------------------------------
//                            r e s u m e
//-----------------------------------------------------------------------
int TPauseState::resume(Tubras::TSEvent event)
{
    m_info.m_returnCode = 1;
    popState();
    return 1;   // eat the event
}

//-----------------------------------------------------------------------
//                         e x i t T o M e n u
//-----------------------------------------------------------------------
int TPauseState::exitToMenu(Tubras::TSEvent event)
{
    m_info.m_returnCode = 0;
    popState();
    return 1;   // eat the event
}


//-----------------------------------------------------------------------
//                         a n i m a t e D o n e
//-----------------------------------------------------------------------
int TPauseState::animateDone(Tubras::TSEvent event)
{
    return 0;
}

//-----------------------------------------------------------------------
//                         a n i m a t e M e n u
//-----------------------------------------------------------------------
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

//-----------------------------------------------------------------------
//                             E n t e r
//-----------------------------------------------------------------------
int TPauseState::Enter()
{
    m_parent->flipVisibility();
    m_frame->reParent(getGUIManager()->getSystem()->getActiveScreen());
    m_frame->center();
    m_frame->moveRel(m_frame->x1, m_frame->y1-70);
    m_frame->setVisible(true);
    setGUIEnabled(true);
    m_frame->makeExclusive();
    m_finterval->start();
    m_ambientSound->play();
    enableEvents(this);
    return 0;
}

//-----------------------------------------------------------------------
//                              E x i t
//-----------------------------------------------------------------------
Tubras::TStateInfo* TPauseState::Exit()
{
    disableEvents(this);
    m_parent->flipVisibility();
    m_frame->makeExclusive(false);
    m_frame->setVisible(false);
    m_frame->reParent(0);
    m_ambientSound->stop();

    return &m_info;
}

//-----------------------------------------------------------------------
//                             R e s e t
//-----------------------------------------------------------------------
int TPauseState::Reset()
{
    return 0;
}

//-----------------------------------------------------------------------
//                             P a u s e
//-----------------------------------------------------------------------
int TPauseState::Pause()
{
    Exit();

    return 0;
}

//-----------------------------------------------------------------------
//                             R e s u m e
//-----------------------------------------------------------------------
int TPauseState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    Enter();
    return 0;
}


