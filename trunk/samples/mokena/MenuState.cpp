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
#include "mokena.h"
#include "cegui/elements/ceguiframewindow.h"

#define SLIDE_DURATION 0.9f

//-----------------------------------------------------------------------
//                         T M e n u S t a t e
//-----------------------------------------------------------------------
TMenuState::TMenuState() : TState("menuState")
{
    slideDirection = -1;
    m_doQuit = false;
    m_doPlay = false;
    m_doOptions = false;
    m_centerMouse = true;
}

//-----------------------------------------------------------------------
//                        ~ T M e n u S t a t e
//-----------------------------------------------------------------------
TMenuState::~TMenuState()
{
    if(sound1)
        delete sound1;
    if(sound2)
        delete sound2;
    if(ambientSound)
        delete ambientSound;

    if(m_finterval)
        delete m_finterval;
}

//-----------------------------------------------------------------------
//                         i n i t i a l i z e 
//-----------------------------------------------------------------------
int TMenuState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    //
    // create a parent root node and initially make it invisible.
    //
    m_parent = sm->getRootSceneNode()->createChildSceneNode("MenuParent");
    m_parent->flipVisibility();

    sound1 = loadSound("General", "slideout.ogg");
    sound2 = loadSound("General", "slidein.ogg");
    ambientSound = loadSound("General", "ambient.ogg");
    ambientSound->setLoop(true);

    m_finterval = new Tubras::TFunctionInterval("slideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TMenuState::slideMenu));

    m_finterval->setDoneEvent("app.slideDone");
    acceptEvent("app.slideDone",EVENT_DELEGATE(TMenuState::slideDone));

    CEGUI::System* system = getGUISystem();
    system->setMouseMoveScaling(1.2);

    m_GUIRoot = new Tubras::TWindow(getGUISheet(), "root");
    m_GUIRoot->setVisible(true);
    
    m_frame = new Tubras::TStaticImage(m_GUIRoot,"background_wnd","menuSheet.png");
    m_frame->setPos(0.99,0.0);
    m_frame->setSize(0.5,1.0);

    //
    // playButton setup 
    //
    m_playButton = new Tubras::TImageButton(m_frame, "playButton","playbutton.png");
    m_playButton->setPos(0.35,0.25);
    m_playButton->setSize(0.40,0.20);
    acceptEvent("gui.playButton.clicked",EVENT_DELEGATE(TMenuState::playClicked));

    //
    // optionsButton setup 
    //
    m_optionsButton = new Tubras::TImageButton(m_frame,"optionsButton","optionsbutton.png");
    m_optionsButton->setPos(0.20,0.45);
    m_optionsButton->setSize(0.70,0.20);
    acceptEvent("gui.optionsButton.clicked",EVENT_DELEGATE(TMenuState::optionsClicked));

    //
    // quitButton setup 
    //
    m_quitButton = new Tubras::TImageButton(m_frame, "quitButton","quitbutton.png");
    m_quitButton->setPos(0.35,0.65);
    m_quitButton->setSize(0.40,0.20);
    acceptEvent("gui.quitButton.clicked",EVENT_DELEGATE(TMenuState::quitClicked));

    m_parent->flipVisibility();
    m_GUIRoot->setVisible(false);

    return 0;
}

//-----------------------------------------------------------------------
//                            q u i t A p p
//-----------------------------------------------------------------------
int TMenuState::quitApp(Tubras::TSEvent event)
{
    m_app->stopRunning();
    return 0;
}

//-----------------------------------------------------------------------
//                          s l i d e D o n e
//-----------------------------------------------------------------------
int TMenuState::slideDone(Tubras::TSEvent)
{
    if(slideDirection < 0)
        slideDirection = 1;
    else slideDirection = -1;
    if(m_doQuit)
        m_app->stopRunning();
    else if(m_doPlay)
        changeState("playState");
    else if(m_doOptions)
        pushState("optionsState");
    else
    {
        CEGUI::MouseCursor::getSingleton().show();
        ambientSound->play();
    }
    return 0;
}

//-----------------------------------------------------------------------
//                          s l i d e M e n u
//-----------------------------------------------------------------------
void TMenuState::slideMenu(double T, void* userData)
{
    double value;
    if(slideDirection > 0)
        value = 0.5f + ((T / SLIDE_DURATION) * 0.5f);
    else value = 1.0f - ((T / SLIDE_DURATION) * 0.5f);
    m_frame->setPos(value,0.0);
}

//-----------------------------------------------------------------------
//                          t o g g l e M o u s e
//-----------------------------------------------------------------------
int TMenuState::toggleMouse(Tubras::TSEvent)
{

    logMessage("toggleMouse event");
    if(CEGUI::MouseCursor::getSingleton().isVisible())
        CEGUI::MouseCursor::getSingleton().hide();
    else CEGUI::MouseCursor::getSingleton().show();
    return 0;
}

//-----------------------------------------------------------------------
//                          q u i t C l i c k e d
//-----------------------------------------------------------------------
int TMenuState::quitClicked(Tubras::TSEvent)
{
    m_doQuit = true;
    m_finterval->start();
    sound2->play();    
    return true;
}

//-----------------------------------------------------------------------
//                          p l a y C l i c k e d
//-----------------------------------------------------------------------
int TMenuState::playClicked(Tubras::TSEvent)
{
    m_doPlay = true;
    m_finterval->start();
    sound2->play();
    m_centerMouse = true;
    return 0;
}

//-----------------------------------------------------------------------
//                        o p t i o n s C l i c k e d
//-----------------------------------------------------------------------
int TMenuState::optionsClicked(Tubras::TSEvent)
{
    m_doOptions = true;
    m_finterval->start();
    sound2->play();
    return 0;
}

//-----------------------------------------------------------------------
//                               E n t e r
//-----------------------------------------------------------------------
int TMenuState::Enter()
{
    //
    // do this so mouse show works the first time around (sets d_wndWithMouse)
    //
    getGUISystem()->injectMouseMove(0,0);
    setGUIEnabled(true);

    //
    // disable bounding box display if previously enabled
    //
    getRenderEngine()->getSceneManager()->showBoundingBoxes(false);

    m_doPlay = false;
    m_doQuit = false;
    m_doOptions = false;
    m_parent->flipVisibility();

    int cx = m_app->getRenderEngine()->getRenderWindow()->getWidth() / 2;
    int cy = m_app->getRenderEngine()->getRenderWindow()->getHeight() / 2;
    if(m_centerMouse)
    {
        CEGUI::MouseCursor::getSingleton().setPosition(CEGUI::Point(cx,cy));
        m_centerMouse = false;
    }
    m_GUIRoot->setVisible(true);


    m_finterval->start();
    sound1->play();
    return 0;
}

//-----------------------------------------------------------------------
//                                E x i t
//-----------------------------------------------------------------------
Tubras::TStateInfo* TMenuState::Exit()
{
    m_parent->flipVisibility();
    setGUIEnabled(false);
    if(m_doPlay)
        CEGUI::MouseCursor::getSingleton().hide();

    CEGUI::System::getSingleton().injectTimePulse(0.1);
    m_GUIRoot->setVisible(false);

    ambientSound->stop();
    return &m_info;
}

//-----------------------------------------------------------------------
//                               R e s e t 
//-----------------------------------------------------------------------
int TMenuState::Reset()
{
    return 0;
}

//-----------------------------------------------------------------------
//                               P a u s e
//-----------------------------------------------------------------------
int TMenuState::Pause()
{
    Exit();

    return 0;
}

//-----------------------------------------------------------------------
//                               R e s u m e
//-----------------------------------------------------------------------
int TMenuState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    Enter();
    return 0;
}


