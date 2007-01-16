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
//                      T O p t i o n s S t a t e
//-----------------------------------------------------------------------
TOptionsState::TOptionsState() : TState("optionsState")
{
    slideDirection = -1;
    m_doSave = false;
    m_doCancel = false;
}

//-----------------------------------------------------------------------
//                      ~ T O p t i o n s S t a t e
//-----------------------------------------------------------------------
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

//-----------------------------------------------------------------------
//                          i n i t i a l i z e
//-----------------------------------------------------------------------
int TOptionsState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_parent = sm->getRootSceneNode()->createChildSceneNode("OptionsParent");

    sound1 = loadSound("slideout.ogg");
    sound2 = loadSound("slidein.ogg");
    gui_rollover = loadSound("GUI_rollover.ogg");
    gui_click = loadSound("GUI_click.ogg");
    ambientSound = loadSound("ambient.ogg");
    ambientSound->setLoop(true);

    m_parent->flipVisibility();

    m_finterval = new Tubras::TFunctionInterval("OptionsslideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TOptionsState::slideMenu));

    m_finterval->setDoneEvent("app.OptionsslideDone");
    acceptEvent("app.OptionsslideDone",EVENT_DELEGATE(TOptionsState::slideDone));

    TGUI::TGSystem* system = getGUISystem();

    m_GUIScreen = new TGUI::TGScreen(system->getActiveScreen(),"OptionsScreen");

    setGUICursorVisible(false);


    //system->setDefaultFont((CEGUI::utf8*)"BlueHighway-16");

    m_GUIScreen->hide();

    //
    // menu background (window with a background image)
    //
    m_GUIMenu = new TGUI::TGImage(m_GUIScreen,"OptionsMenu","optionssheet.png");
    m_GUIMenu->setPos(1.0f,0.0f);
    m_GUIMenu->setSize(0.5f,1.0f);


    //
    // saveButton setup 
    //

    m_saveButton = new TGUI::TGImageButton(m_GUIMenu,"saveButton","savebutton.png");
    m_saveButton->setPos(0.25f,0.75f);
    m_saveButton->setSize(0.25f,0.10f);
    acceptEvent("gui.saveButton.mouseClicked",EVENT_DELEGATE(TOptionsState::saveClicked));

    //
    // cancelButton setup 
    //

    m_cancelButton = new TGUI::TGImageButton(m_GUIMenu,"cancelButton","cancelbutton.png");
    m_cancelButton->setPos(0.57f,0.75f);
    m_cancelButton->setSize(0.35f,0.10f);
    acceptEvent("gui.cancelButton.mouseClicked",EVENT_DELEGATE(TOptionsState::cancelClicked));

    Tubras::TEventDelegate* ed = EVENT_DELEGATE(TMenuState::mouseEnter);
    acceptEvent("gui.saveButton.mouseEnter",ed);
    acceptEvent("gui.cancelButton.mouseEnter",ed);

    ed = EVENT_DELEGATE(TMenuState::mouseDown);
    acceptEvent("gui.saveButton.mouseDown",ed);
    acceptEvent("gui.cancelButton.mouseDown",ed);


    //
    // Background music enabled checkbox
    //

    TGUI::TGLabel*  text;

    text = new TGUI::TGLabel(m_GUIMenu,"","Background Music:");
    text->setPos(0.1f,0.3f);
    text->setSize(0.4f,0.05f);
    text->setAlignment(TGUI::alRight);

    TGUI::TGCheckBox* cb = new TGUI::TGCheckBox(m_GUIMenu);
    cb->setPos(0.55f,0.3f);
    cb->setSize(0.6f,0.03f);

    //
    // volume spinner
    //
    text = new TGUI::TGLabel(m_GUIMenu,"","Volume:");
    text->setPos(0.1f,0.4f);
    text->setSize(0.4f,0.05f);
    text->setAlignment(TGUI::alRight);

    TGUI::TGSpinEdit* sp = new TGUI::TGSpinEdit(m_GUIMenu);
    sp->setPos(0.55f,0.395f);
    sp->setSize(0.25f,0.04f);
    sp->setMaximumValue(100.0f);
    sp->setMinimumValue(0.0f);
    sp->setCurrentValue(100.0f);

    //
    // difficulty combo box
    //
    text = new TGUI::TGLabel(m_GUIMenu,"", "Difficulty:");
    text->setPos(0.1f,0.5f);
    text->setSize(0.4f,0.05f);
    text->setAlignment(TGUI::alRight);

    TGUI::TGComboBox* cb2;

    cb2 = new TGUI::TGComboBox(m_GUIMenu);
    cb2->setPos(0.55f,0.495f);
    cb2->setSize(0.35f,0.04f);

    cb2->addItem("Easy");
    cb2->addItem("Normal");
    cb2->addItem("Hard");

    cb2->setText("Normal");

    cb2->setStyle(TGUI::CBS_DROPDOWN_LIST);

    //
    // theme combo box
    //

    text = new TGUI::TGLabel(m_GUIMenu,"","Theme:");
    text->setPos(0.1f,0.6f);
    text->setSize(0.4f,0.05f);
    text->setAlignment(TGUI::alRight);

    cb2 = new TGUI::TGComboBox(m_GUIMenu);
    cb2->setPos(0.55f,0.595f);
    cb2->setSize(0.35f,0.04f);
    cb2->setText("Random");
    cb2->setStyle(TGUI::CBS_DROPDOWN_LIST);

    cb2->addItem("Random");
    cb2->addItem("Sequential");
    cb2->addItem("Star Field");
    m_parent->flipVisibility();

    return 0;
}

//-----------------------------------------------------------------------
//                         q u i t A p p
//-----------------------------------------------------------------------
int TOptionsState::quitApp(Tubras::TSEvent event)
{
    m_app->stopRunning();
    return 0;
}

//-----------------------------------------------------------------------
//                          m o u s e E n t e r
//-----------------------------------------------------------------------
int TOptionsState::mouseEnter(Tubras::TSEvent event)
{
    gui_rollover->play();
    return 1;
}

//-----------------------------------------------------------------------
//                          m o u s e D o w n
//-----------------------------------------------------------------------
int TOptionsState::mouseDown(Tubras::TSEvent event)
{
    gui_click->play();
    return 1;
}

//-----------------------------------------------------------------------
//                        s l i d e D o n e
//-----------------------------------------------------------------------
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
        setGUICursorVisible(true);
        ambientSound->play();
    }
    return 0;
}


//-----------------------------------------------------------------------
//                         s l i d e M e n u
//-----------------------------------------------------------------------
void TOptionsState::slideMenu(double T, void* userData)
{
    double value;
    if(slideDirection > 0)
        value = 0.5f + ((T / SLIDE_DURATION) * 0.5f);
    else value = 1.0f - ((T / SLIDE_DURATION) * 0.5f);
    m_GUIMenu->setPos(value,0.0f);
}

//-----------------------------------------------------------------------
//                      s a v e C l i c k e d
//-----------------------------------------------------------------------
int TOptionsState::saveClicked(Tubras::TSEvent)
{
    m_doSave = true;
    m_finterval->start();
    sound2->play();
    return 0;
}

//-----------------------------------------------------------------------
//                     c a n c e l C l i c k e d
//-----------------------------------------------------------------------
int TOptionsState::cancelClicked(Tubras::TSEvent)
{
    m_doCancel = true;
    m_finterval->start();
    sound2->play();
    return 0;
}

//-----------------------------------------------------------------------
//                           E n t e r
//-----------------------------------------------------------------------
int TOptionsState::Enter()
{
    m_GUIScreen->show();
    //
    // do this so mouse show works the first time around (sets d_wndWithMouse)
    //
    m_doSave = false;
    m_doCancel = false;
    m_parent->flipVisibility();
    setGUIEnabled(true);

    int cx = m_app->getRenderEngine()->getRenderWindow()->getWidth() / 2;
    int cy = m_app->getRenderEngine()->getRenderWindow()->getHeight() / 2;


    m_finterval->start();
    sound1->play();
    return 0;
}

//-----------------------------------------------------------------------
//                             E x i t 
//-----------------------------------------------------------------------
Tubras::TStateInfo* TOptionsState::Exit()
{
    m_GUIScreen->hide();
    m_parent->flipVisibility();
    setGUIEnabled(false);

    ambientSound->stop();
    return &m_info;
}

//-----------------------------------------------------------------------
//                             R e s e t
//-----------------------------------------------------------------------
int TOptionsState::Reset()
{
    return 0;
}

//-----------------------------------------------------------------------
//                             P a u s e
//-----------------------------------------------------------------------
int TOptionsState::Pause()
{
    Exit();

    return 0;
}

//-----------------------------------------------------------------------
//                           R e s u m e
//-----------------------------------------------------------------------
int TOptionsState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    Enter();
    return 0;
}


