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
//                         T M e n u S t a t e
//-----------------------------------------------------------------------
TMenuState::TMenuState() : TState("menuState"),
    m_slideDirection(-1),
    m_doQuit(false),
    m_doPlay(false),
    m_doOptions(false),
    m_centerMouse(true)
{
}

//-----------------------------------------------------------------------
//                        ~ T M e n u S t a t e
//-----------------------------------------------------------------------
TMenuState::~TMenuState()
{
}

//-----------------------------------------------------------------------
//                           a l p h a U p
//-----------------------------------------------------------------------
void TMenuState::alphaUp(double T, void* userData)
{
    m_mokenas->setAlpha(1.f - (T / 2.f));
}

//-----------------------------------------------------------------------
//                           a l p h a D n
//-----------------------------------------------------------------------
void TMenuState::alphaDn(double T, void* userData)
{
    m_mokenas->setAlpha(T / 2.f);
}

//-----------------------------------------------------------------------
//                          a l p h a D o n e
//-----------------------------------------------------------------------
int TMenuState::alphaDone(Tubras::TSEvent event)
{
    if(event->getID() == m_upID)
    {
        m_fiDown->start();
    }
    else
    {
        m_fiUp->start();
    }
    return 1;
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

    m_fiUp = new Tubras::TFunctionInterval("alphaUp",2.0,FUNCINT_DELEGATE(TMenuState::alphaUp));
    m_fiDown = new Tubras::TFunctionInterval("alphaDn",2.0,FUNCINT_DELEGATE(TMenuState::alphaDn));
    m_fiUp->setDoneEvent("alphaUp");
    m_fiDown->setDoneEvent("alphaDn");
    m_upID = acceptEvent("alphaUp",EVENT_DELEGATE(TMenuState::alphaDone));
    acceptEvent("alphaDn",EVENT_DELEGATE(TMenuState::alphaDone));

    m_slideOut = loadSound("slideout.ogg");
    m_slideOut->setVolume(.5f);
    m_slideIn = loadSound("slidein.ogg");
    m_slideIn->setVolume(.5f);
    m_ambientSound = loadSound("ambient.ogg");
    m_guiRollover = loadSound("GUI_rollover.ogg");
    m_guiClick = loadSound("GUI_click.ogg");
    m_ambientSound->setLoop(true);

    m_finterval = new Tubras::TFunctionInterval("slideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TMenuState::slideMenu));

    m_finterval->setDoneEvent("app.slideDone");
    acceptEvent("app.slideDone",EVENT_DELEGATE(TMenuState::slideDone));

    TGUI::TGSystem* system = getGUISystem();

    m_GUIScreen = new TGUI::TGScreen(system->getActiveScreen(),"menuScreen");
    //m_GUIScreen->activate();
    m_GUIScreen->setVisible(true);

    m_mokenas = new TGUI::TGImage(m_GUIScreen,"mokena","Mokenas.png");
    m_mokenas->setPos(-30,5);
    m_mokenas->setSize(0.6f,0.2f);

    m_mokena = new TGUI::TGImage(m_GUIScreen,"mokena","Mokena.png");
    m_mokena->setPos(-30,5);
    m_mokena->setSize(0.6f,0.2f);

    m_GUIMenu = new TGUI::TGImage(m_GUIScreen,"PlayMenu","menuSheet.png");
    m_GUIMenu->setPos(0.99f,0.0f);
    m_GUIMenu->setSize(0.5f,1.0f);

    //
    // playButton setup 
    //
    m_playButton = new TGUI::TGImageButton(m_GUIMenu,"playButton","playbutton.png");
    m_playButton->setPos(0.35f,0.25f);
    m_playButton->setSize(0.40f,0.20f);
    acceptEvent("gui.playButton.mouseClicked",EVENT_DELEGATE(TMenuState::playClicked));

    //
    // optionsButton setup 
    //
    m_optionsButton = new TGUI::TGImageButton(m_GUIMenu,"optionsButton","optionsbutton.png");
    m_optionsButton->setPos(0.20f,0.45f);
    m_optionsButton->setSize(0.70f,0.20f);
    acceptEvent("gui.optionsButton.mouseClicked",EVENT_DELEGATE(TMenuState::optionsClicked));

    //
    // quitButton setup 
    //
    m_quitButton = new TGUI::TGImageButton(m_GUIMenu,"quitButton","quitbutton.png");
    m_quitButton->setPos(0.35f,0.65f);
    m_quitButton->setSize(0.40f,0.20f);
    acceptEvent("gui.quitButton.mouseClicked",EVENT_DELEGATE(TMenuState::quitClicked));

    Tubras::TEventDelegate* ed = EVENT_DELEGATE(TMenuState::mouseEnter);
    acceptEvent("gui.playButton.mouseEnter",ed);
    acceptEvent("gui.optionsButton.mouseEnter",ed);
    acceptEvent("gui.quitButton.mouseEnter",ed);

    ed = EVENT_DELEGATE(TMenuState::mouseDown);
    acceptEvent("gui.playButton.mouseDown",ed);
    acceptEvent("gui.optionsButton.mouseDown",ed);
    acceptEvent("gui.quitButton.mouseDown",ed);

    m_parent->flipVisibility();
    m_GUIScreen->hide();

    return 0;
}

//-----------------------------------------------------------------------
//                          m o u s e E n t e r
//-----------------------------------------------------------------------
int TMenuState::mouseEnter(Tubras::TSEvent event)
{
    m_guiRollover->play();
    return 1;
}

//-----------------------------------------------------------------------
//                          m o u s e D o w n
//-----------------------------------------------------------------------
int TMenuState::mouseDown(Tubras::TSEvent event)
{
    m_guiClick->play();
    return 1;
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
    if(m_slideDirection < 0)
        m_slideDirection = 1;
    else m_slideDirection = -1;
    if(m_doQuit)
        m_app->stopRunning();
    else if(m_doPlay)
        changeState("playState");
    else if(m_doOptions)
        pushState("optionsState");
    else
    {
        setGUICursorVisible(true);
        if(m_ambientSound->status() != Tubras::TSound::PLAYING)
            m_ambientSound->play();
    }
    return 0;
}

//-----------------------------------------------------------------------
//                          s l i d e M e n u
//-----------------------------------------------------------------------
void TMenuState::slideMenu(double T, void* userData)
{
    double value;
    if(m_slideDirection > 0)
        value = 0.5f + ((T / SLIDE_DURATION) * 0.5f);
    else value = 1.0f - ((T / SLIDE_DURATION) * 0.5f);
    m_GUIMenu->setPos(value,0.0f);
}

//-----------------------------------------------------------------------
//                          q u i t C l i c k e d
//-----------------------------------------------------------------------
int TMenuState::quitClicked(Tubras::TSEvent)
{
    m_doQuit = true;
    m_finterval->start();
    m_slideIn->play();    
    return true;
}

//-----------------------------------------------------------------------
//                          p l a y C l i c k e d
//-----------------------------------------------------------------------
int TMenuState::playClicked(Tubras::TSEvent)
{
    m_doPlay = true;
    m_finterval->start();
    m_slideIn->play();
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
    m_slideIn->play();
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
    m_GUIScreen->activate();
    m_GUIScreen->show();
    setGUIEnabled(true);
    setGUICursorVisible(true);


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
        TGUI::TGSystem::getSingleton().getMouseCursor()->setPos(cx,cy);
        m_centerMouse = false;
    }
    m_finterval->start();
    m_slideOut->play();
    enableEvents(this);
    m_fiDown->start();
    return 0;
}

//-----------------------------------------------------------------------
//                                E x i t
//-----------------------------------------------------------------------
Tubras::TStateInfo* TMenuState::Exit()
{
    m_parent->flipVisibility();
    TGUI::TGSystem::getSingleton().injectTimePulse(0.1);

    if(m_doPlay)
    {
        setGUICursorVisible(false);
        setGUIEnabled(false);
        m_ambientSound->stop();
        m_GUIScreen->hide();
        disableEvents(this);
    }

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


