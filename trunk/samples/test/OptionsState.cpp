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

#define SLIDE_DURATION 0.9f

TOptionsState::TOptionsState() : TState("optionsState")
{
    slideDirection = -1;
    m_doSave = false;
    m_doCancel = false;
}

TOptionsState::~TOptionsState()
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

int TOptionsState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_parent = sm->getRootSceneNode()->createChildSceneNode("OptionsParent");

    sound1 = loadSound("General", "slideout.ogg");
    sound2 = loadSound("General", "slidein.ogg");
    ambientSound = loadSound("General", "ambient.ogg");
    ambientSound->setLoop(true);

    m_parent->flipVisibility();

    m_finterval = new Tubras::TFunctionInterval("OptionsslideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TOptionsState::slideMenu));

    m_finterval->setDoneEvent("app.OptionsslideDone");
    acceptEvent("app.OptionsslideDone",EVENT_DELEGATE(TOptionsState::slideDone));

    m_mouseDelegate = EVENT_DELEGATE(TOptionsState::mouseDown);
    acceptEvent("input.mousedown.0",m_mouseDelegate,NULL,0,false);

    CEGUI::System* system = getGUISystem();

    system->setMouseMoveScaling(1.2);

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    m_GUIRoot = new Tubras::TWindow(getGUISheet(), "OptionsRoot");

    system->setDefaultMouseCursor(
                (CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
    CEGUI::MouseCursor::getSingleton().hide();


    //CEGUI::Image* mouseImage = CEGUI::ImagesetManager::getSingleton().create

    system->setDefaultFont((CEGUI::utf8*)"BlueHighway-16");

    m_GUIRoot->setVisible(true);

    //
    // menu background (window with a background image)
    //
    m_frame = new Tubras::TStaticImage(m_GUIRoot,"OptionsBackground","optionssheet.png");
    m_frame->setPosition(1.0,0.0);
    m_frame->setSize(0.5,1.0);


    //
    // saveButton setup 
    //

    m_saveButton = new Tubras::TImageButton(m_frame,"saveButton","savebutton.png");
    m_saveButton->setPosition(0.25,0.75);
    m_saveButton->setSize(0.25,0.10);
    acceptEvent("gui.saveButton.clicked",EVENT_DELEGATE(TOptionsState::saveClicked));

    //
    // cancelButton setup 
    //

    m_cancelButton = new Tubras::TImageButton(m_frame,"cancelButton","cancelbutton.png");
    m_cancelButton->setPosition(0.57,0.75);
    m_cancelButton->setSize(0.35,0.10);
    acceptEvent("gui.cancelButton.clicked",EVENT_DELEGATE(TOptionsState::cancelClicked));


    //
    // Background music enabled
    //

    Tubras::TStaticText*  text;

    text = new Tubras::TStaticText(m_frame,"text1",
               "Background Music:","BlueHighway-16",
               Tubras::TWindow::horzRight);
    text->setPosition(0.1,0.3);
    text->setSize(0.4,0.05);
    text->setFrameEnabled(false);
    text->setBackgroundEnabled(false);

    
    Tubras::TCheckBox* cb = new Tubras::TCheckBox(m_frame,"cb1");
    cb->setPosition(0.55,0.275);
    cb->setSize(0.9,0.1);


    //
    // volume
    //
    text = new Tubras::TStaticText(m_frame,"text2",
               "Volume:","BlueHighway-16",
               Tubras::TWindow::horzRight);
    text->setPosition(0.1,0.4);
    text->setSize(0.4,0.05);
    text->setFrameEnabled(false);
    text->setBackgroundEnabled(false);

    Tubras::TSpinner* sp = new Tubras::TSpinner(m_frame, "sp1");
    sp->setPosition(0.55,0.4);
    sp->setSize(0.15,0.05);
    sp->setMaximumValue(100.0f);
    sp->setMinimumValue(0.0f);
    sp->setCurrentValue(100.0f);


    //
    // difficulty
    //
    text = new Tubras::TStaticText(m_frame, "text3",
               "Difficulty:","BlueHighway-16",
               Tubras::TWindow::horzRight);
    text->setPosition(0.1,0.5);
    text->setSize(0.4,0.05);
    text->setFrameEnabled(false);
    text->setBackgroundEnabled(false);

    Tubras::TComboBox* cb2;

    cb2 = new Tubras::TComboBox(m_frame,"cb2");
    cb2->setPosition(0.55,0.51);
    cb2->setSize(0.35,0.165);

    CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem("Easy", 1);
	itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    cb2->addItem(itemCombobox);

    itemCombobox = new CEGUI::ListboxTextItem("Normal", 2);
	itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    cb2->addItem(itemCombobox);
    itemCombobox->setSelected(true);
    cb2->setItemSelectState(itemCombobox,true);

    itemCombobox = new CEGUI::ListboxTextItem("Hard", 3);
	itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    cb2->addItem(itemCombobox);

    cb2->setText("Normal");

    cb2->setReadOnly(true);


    text = new Tubras::TStaticText(m_frame,"text4",
               "Theme:","BlueHighway-16",
               Tubras::TWindow::horzRight);
    text->setPosition(0.1,0.6);
    text->setSize(0.4,0.05);
    text->setFrameEnabled(false);
    text->setBackgroundEnabled(false);


    cb2 = new Tubras::TComboBox(m_frame,"cb3");
    cb2->setPosition(0.55,0.61);
    cb2->setSize(0.35,0.165);

    itemCombobox = new CEGUI::ListboxTextItem("Random", 1);
	itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    cb2->addItem(itemCombobox);

    itemCombobox = new CEGUI::ListboxTextItem("Sequential", 2);
	itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    cb2->addItem(itemCombobox);
    itemCombobox->setSelected(true);
    cb2->setItemSelectState(itemCombobox,true);

    itemCombobox = new CEGUI::ListboxTextItem("Star Field", 3);
	itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    cb2->addItem(itemCombobox);

    cb2->setText("Random");

    cb2->setReadOnly(true);


    //sl1->setText("Enable");
    //sl1->setFont("BlueHighway-16");


    m_parent->flipVisibility();
    m_GUIRoot->setVisible(false);

    return 0;
}

int TOptionsState::mouseDown(Tubras::TSEvent event)
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

int TOptionsState::quitApp(Tubras::TSEvent event)
{
    m_app->stopRunning();
    return 0;
}

int TOptionsState::slideDone(Tubras::TSEvent)
{
    if(slideDirection < 0)
        slideDirection = 1;
    else slideDirection = -1;
    if(m_doSave)
    {
        popState();
    }
    else if(m_doCancel)
        popState();
    else
    {
        CEGUI::MouseCursor::getSingleton().show();
        ambientSound->play();
    }
    return 0;
}


void TOptionsState::slideMenu(double T, void* userData)
{
    double value;
    if(slideDirection > 0)
        value = 0.5f + ((T / SLIDE_DURATION) * 0.5f);
    else value = 1.0f - ((T / SLIDE_DURATION) * 0.5f);
    m_frame->setPosition(value,0.0);
}

int TOptionsState::toggleMouse(Tubras::TSEvent)
{

    logMessage("toggleMouse event");
    if(CEGUI::MouseCursor::getSingleton().isVisible())
        CEGUI::MouseCursor::getSingleton().hide();
    else CEGUI::MouseCursor::getSingleton().show();
    return 0;
}


bool TOptionsState::handleMouseButtonEnter(const CEGUI::EventArgs& event)
{
    gui_rollover->play();
    return true;
}

bool TOptionsState::handleMouseButtonDown(const CEGUI::EventArgs& event)
{
    gui_click->play();
    return true;
}


int TOptionsState::saveClicked(Tubras::TSEvent)
{
    m_doSave = true;
    m_finterval->start();
    sound2->play();
    return 0;
}

int TOptionsState::cancelClicked(Tubras::TSEvent)
{
    m_doCancel = true;
    m_finterval->start();
    sound2->play();
    return 0;
}

int TOptionsState::Enter()
{
    m_GUIRoot->setVisible(true);
    //
    // do this so mouse show works the first time around (sets d_wndWithMouse)
    //
    getGUISystem()->injectMouseMove(0,0);
    m_doSave = false;
    m_doCancel = false;
    m_parent->flipVisibility();
    setGUIEnabled(true);

    int cx = m_app->getRenderEngine()->getRenderWindow()->getWidth() / 2;
    int cy = m_app->getRenderEngine()->getRenderWindow()->getHeight() / 2;


    m_finterval->start();
    sound1->play();
    m_mouseDelegate->setEnabled(true);
    return 0;
}

Tubras::TStateInfo* TOptionsState::Exit()
{
    m_GUIRoot->setVisible(false);
    m_parent->flipVisibility();
    setGUIEnabled(false);

    m_mouseDelegate->setEnabled(false);
    ambientSound->stop();
    return &m_info;
}

int TOptionsState::Reset()
{
    return 0;
}

int TOptionsState::Pause()
{
    Exit();

    return 0;
}

int TOptionsState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    Enter();
    return 0;
}


