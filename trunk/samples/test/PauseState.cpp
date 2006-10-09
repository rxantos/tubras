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
#include "test.h"
#include "cegui/elements/ceguiframewindow.h"

#define SLIDE_DURATION 0.9f

TPauseState::TPauseState() : TState("pauseState")
{
    slideDirection = -1;
    m_doQuit = false;
    m_doPlay = false;
}

TPauseState::~TPauseState()
{
    if(sound1)
        delete sound1;
    if(sound2)
        delete sound2;
    if(ambientSound)
        delete ambientSound;

    if(m_finterval)
        delete m_finterval;

    if(m_GUIRoot)
    {
        CEGUI::WindowManager::getSingleton().destroyWindow(m_GUIRoot);
    }

}

int TPauseState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_parent = sm->getRootSceneNode()->createChildSceneNode("PauseParent");

    sound1 = loadSound("General", "slideout.ogg");
    sound2 = loadSound("General", "slidein.ogg");
    ambientSound = loadSound("General", "ambient.ogg");
    ambientSound->setLoop(true);

    m_parent->flipVisibility();

    m_finterval = new Tubras::TFunctionInterval("PauseslideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TPauseState::slideMenu));

    m_finterval->setDoneEvent("PauseslideDone");
    acceptEvent("PauseslideDone",EVENT_DELEGATE(TPauseState::slideDone));

    CEGUI::System* system = getGUISystem();

    system->setMouseMoveScaling(1.2);

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    m_GUIRoot = wmgr.createWindow("DefaultWindow", "Pauseroot");

    system->setDefaultMouseCursor(
                (CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
    //
    // do this so mouse show works the first time around (sets d_wndWithMouse)
    //
    system->injectMouseMove(0,0);

    CEGUI::MouseCursor::getSingleton().hide();
    system->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");

    m_GUIRoot->setVisible(true);
    
    CEGUI::Imageset* imageset = CEGUI::ImagesetManager::getSingleton().createImagesetFromImageFile("PauseBackground", "menusheet.png");
    m_frame = wmgr.createWindow("TaharezLook/StaticImage", "pausebackground_wnd");
    m_frame->setProperty("Image", "set:PauseBackground image:full_image"); 
    m_GUIRoot->addChildWindow(m_frame);
    m_frame->setPosition(CEGUI::UVector2(CEGUI::UDim(0.99,0), CEGUI::UDim(0.0f,0)));
    m_frame->setSize( CEGUI::UVector2(CEGUI::UDim(0.5f,0), CEGUI::UDim(1.0f,0)));
    m_frame->setProperty("FrameEnabled", "false");
    m_frame->setProperty("BackgroundEnabled", "false");

    //
    // playButton setup 
    //
    m_playButton = NULL;
    m_quitButton = NULL;

    m_parent->flipVisibility();
    m_GUIRoot->setVisible(false);

    return 0;
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

int TPauseState::slideDone(Tubras::TSEvent event)
{
    if(slideDirection < 0)
        slideDirection = 1;
    else slideDirection = -1;
    if(m_doQuit)
        m_app->stopRunning();
    else if(m_doPlay)
        changeState("playState");
    else
    {
        CEGUI::MouseCursor::getSingleton().show();
        ambientSound->play();
    }
    return 0;
}


void TPauseState::slideMenu(double T, void* userData)
{
    double value;
    if(slideDirection > 0)
        value = 0.5f + ((T / SLIDE_DURATION) * 0.5f);
    else value = 1.0f - ((T / SLIDE_DURATION) * 0.5f);
    m_frame->setPosition(CEGUI::UVector2(CEGUI::UDim(value,0), CEGUI::UDim(0.0f,0)));
}

int TPauseState::toggleMouse(Tubras::TSEvent event)
{

    logMessage("toggleMouse event");
    if(CEGUI::MouseCursor::getSingleton().isVisible())
        CEGUI::MouseCursor::getSingleton().hide();
    else CEGUI::MouseCursor::getSingleton().show();
    return 0;
}


bool TPauseState::handleMouseButtonEnter(const CEGUI::EventArgs& event)
{
    gui_rollover->play();
    return true;
}

bool TPauseState::handleMouseButtonDown(const CEGUI::EventArgs& event)
{
    gui_click->play();
    return true;
}

int TPauseState::quitClicked(Tubras::TSEvent event)
{
    m_doQuit = true;
    m_finterval->start();
    sound2->play();    
    return true;
}

int TPauseState::playClicked(Tubras::TSEvent event)
{
    m_doPlay = true;
    m_finterval->start();
    sound2->play();
    return 0;
}

int TPauseState::Enter()
{
    getGUISystem()->setGUISheet(m_GUIRoot);
    //
    // do this so mouse show works the first time around (sets d_wndWithMouse)
    //
    getGUISystem()->injectMouseMove(0,0);
    m_doPlay = false;
    m_doQuit = false;
    m_parent->flipVisibility();
    setGUIEnabled(true);
    m_GUIRoot->setVisible(true);
    m_finterval->start();
    sound1->play();
    m_mouseDelegate->setEnabled(true);
    return 0;
}

Tubras::TStateInfo* TPauseState::Exit()
{
    m_parent->flipVisibility();
    setGUIEnabled(false);
    CEGUI::MouseCursor::getSingleton().hide();

    CEGUI::System::getSingleton().injectTimePulse(0.1);
    CEGUI::System::getSingleton().getGUISheet()->hide();

    m_mouseDelegate->setEnabled(false);
    ambientSound->stop();
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


