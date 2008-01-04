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
TScoreEntryState::TScoreEntryState() : TState("scoreEntryState"),
m_frame(0)
{
}

//-----------------------------------------------------------------------
//                         ~ T P a u s e S t a t e
//-----------------------------------------------------------------------
TScoreEntryState::~TScoreEntryState()
{
    //
    // specifically track/delete the pause dialog because 
    // we dynamically assign the parent at runtime
    //
    if(m_frame)
        delete m_frame;
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TScoreEntryState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_parent = sm->getRootSceneNode()->createChildSceneNode("ScoreEntryParent");

    m_parent->flipVisibility();

    m_finterval = new Tubras::TFunctionInterval("ScoreslideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TScoreEntryState::animateMenu));

    Tubras::TEventDelegate* resumeEvent = EVENT_DELEGATE(TScoreEntryState::resume);
    m_finterval->setDoneEvent("ScoreslideDone");
    acceptEvent("ScoreslideDone",EVENT_DELEGATE(TScoreEntryState::animateDone));
    acceptEvent("key.down.esc",resumeEvent);
    acceptEvent("gui.saveScoreButton.mouseClicked",resumeEvent);

    Tubras::TEventDelegate* ed = EVENT_DELEGATE(TScoreEntryState::mouseEnter);
    acceptEvent("gui.saveScoreButton.mouseEnter",ed);

    ed = EVENT_DELEGATE(TScoreEntryState::mouseDown);
    acceptEvent("gui.saveScoreButton.mouseDown",ed);

    m_guiRollover = loadSound("GUI_rollover.ogg");
    m_guiClick = loadSound("GUI_click.ogg");
    m_ambientSound = loadSound("ambient.ogg");
    m_ambientSound->setLoop(true);

    TGUI::TGSystem* system = getGUISystem();

    m_frame = new TGUI::TGImage(0,"ScoreEntryDlg", "newScoreDlg.png");
    m_frame->center();
    m_frame->reParent(0);

    TGUI::TGImageButton* b = new TGUI::TGImageButton(m_frame,"saveScoreButton","savebutton.png");
    b->setSize(0.3f,0.28f);
    b->center();
    b->moveRel(b->x1,b->y1+80);

    TGUI::TGLabel* text = new TGUI::TGLabel(m_frame,"","Enter Name:");
    text->setPos(0.1f,0.54f);
    text->setSize(1.2f,0.2f);
    text->setAlignment(TGUI::alLeft);

    m_nameEdit = new TGUI::TGEditBox(m_frame,"nameEdit");
    m_nameEdit->setSize(0.5f,0.14f);
    m_nameEdit->setPos(0.4f, 0.5f);


    m_parent->flipVisibility();
    disableEvents(this);

    return 0;
}

//-----------------------------------------------------------------------
//                          m o u s e E n t e r
//-----------------------------------------------------------------------
int TScoreEntryState::mouseEnter(Tubras::TSEvent event)
{
    m_guiRollover->play();
    return 1;
}

//-----------------------------------------------------------------------
//                          m o u s e D o w n
//-----------------------------------------------------------------------
int TScoreEntryState::mouseDown(Tubras::TSEvent event)
{
    m_guiClick->play();
    return 1;
}

//-----------------------------------------------------------------------
//                            r e s u m e
//-----------------------------------------------------------------------
int TScoreEntryState::resume(Tubras::TSEvent event)
{
    m_info.m_returnCode = 1;
    popState();
    return 1;   // eat the event
}

//-----------------------------------------------------------------------
//                         e x i t T o M e n u
//-----------------------------------------------------------------------
int TScoreEntryState::exitToMenu(Tubras::TSEvent event)
{
    m_info.m_returnCode = 0;
    popState();
    return 1;   // eat the event
}


//-----------------------------------------------------------------------
//                         a n i m a t e D o n e
//-----------------------------------------------------------------------
int TScoreEntryState::animateDone(Tubras::TSEvent event)
{
    return 0;
}

//-----------------------------------------------------------------------
//                         a n i m a t e M e n u
//-----------------------------------------------------------------------
void TScoreEntryState::animateMenu(double T, void* userData)
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
int TScoreEntryState::Enter()
{
    m_parent->flipVisibility();
    m_frame->reParent(getGUIManager()->getSystem()->getActiveScreen());
    m_frame->center();
    m_frame->moveRel(m_frame->x1, m_frame->y1-70);
    m_nameEdit->setText("");
    m_frame->setVisible(true);
    setGUIEnabled(true);
    m_frame->makeExclusive();
    m_frame->setFocusedChild(m_nameEdit);
    m_finterval->start();
    m_ambientSound->play();
    enableEvents(this);
    return 0;
}

//-----------------------------------------------------------------------
//                              E x i t
//-----------------------------------------------------------------------
Tubras::TStateInfo* TScoreEntryState::Exit()
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
int TScoreEntryState::Reset()
{
    return 0;
}

//-----------------------------------------------------------------------
//                             P a u s e
//-----------------------------------------------------------------------
int TScoreEntryState::Pause()
{
    Exit();

    return 0;
}

//-----------------------------------------------------------------------
//                             R e s u m e
//-----------------------------------------------------------------------
int TScoreEntryState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    Enter();
    return 0;
}


