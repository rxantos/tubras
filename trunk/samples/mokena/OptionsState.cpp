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

//-----------------------------------------------------------------------
//                      T O p t i o n s S t a t e
//-----------------------------------------------------------------------
TOptionsState::TOptionsState() : TState("optionsState")
{
    m_doSave = false;
    m_doCancel = false;
}

//-----------------------------------------------------------------------
//                      ~ T O p t i o n s S t a t e
//-----------------------------------------------------------------------
TOptionsState::~TOptionsState()
{

}

//-----------------------------------------------------------------------
//                          i n i t i a l i z e
//-----------------------------------------------------------------------
int TOptionsState::initialize()
{
    if(TState::initialize())
        return 1;

    //
    // read options from the registry
    //

    regOpenSection("options");
    m_playOptions.m_difficulty = regReadKey("difficulty",1);
    m_playOptions.m_bgMusic = regReadKey("bgmusic",1);
    m_playOptions.m_bgMusicVolume = regReadKey("bgmusicvolume",50);
    m_playOptions.m_theme = regReadKey("theme","Random");


    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    gui_rollover = loadSound("GUI_rollover.ogg");
    gui_click = loadSound("GUI_click.ogg");

    //
    // use the same GUI screen as the "menuState"
    //
    TMenuState* state = (TMenuState*) getState("menuState");
    m_GUIMenu = (TGUI::TGImage*) state->getGUIMenu();

    m_optionsDlg = new TGUI::TGImage(m_GUIMenu,"optionsDlg","optionsdlg.png");
    m_optionsDlg->center(false,true);
    m_optionsDlg->setSize(0.4f,0.65f);
    m_optionsDlg->setPos(0.52f,0.25f);



    //
    // saveButton setup 
    //

    m_saveButton = new TGUI::TGImageButton(m_optionsDlg,"saveButton","savebutton.png");
    m_saveButton->setPos(0.25f,0.75f);
    m_saveButton->setSize(0.25f,0.10f);
    acceptEvent("gui.saveButton.mouseClicked",EVENT_DELEGATE(TOptionsState::saveClicked));

    //
    // cancelButton setup 
    //

    m_cancelButton = new TGUI::TGImageButton(m_optionsDlg,"cancelButton","cancelbutton.png");
    m_cancelButton->setPos(0.57f,0.75f);
    m_cancelButton->setSize(0.35f,0.10f);
    acceptEvent("gui.cancelButton.mouseClicked",EVENT_DELEGATE(TOptionsState::cancelClicked));

    Tubras::TEventDelegate* ed = EVENT_DELEGATE(TOptionsState::mouseEnter);
    acceptEvent("gui.saveButton.mouseEnter",ed);
    acceptEvent("gui.cancelButton.mouseEnter",ed);

    ed = EVENT_DELEGATE(TOptionsState::mouseDown);
    acceptEvent("gui.saveButton.mouseDown",ed);
    acceptEvent("gui.cancelButton.mouseDown",ed);


    //
    // Background music enabled checkbox
    //

    TGUI::TGLabel*  text;

    text = new TGUI::TGLabel(m_optionsDlg,"","Background Music:");
    text->setPos(0.1f,0.3f);
    text->setSize(0.4f,0.05f);
    text->setAlignment(TGUI::alRight);

    m_bgMusicEnabled = new TGUI::TGCheckBox(m_optionsDlg);
    m_bgMusicEnabled->setPos(0.55f,0.3f);
    m_bgMusicEnabled->setSize(0.6f,0.03f);

    //
    // volume spinner
    //
    text = new TGUI::TGLabel(m_optionsDlg,"","Volume:");
    text->setPos(0.1f,0.4f);
    text->setSize(0.4f,0.05f);
    text->setAlignment(TGUI::alRight);

    m_bgMusicVolume = new TGUI::TGSpinEdit(m_optionsDlg);
    m_bgMusicVolume->setPos(0.55f,0.395f);
    m_bgMusicVolume->setSize(0.25f,0.04f);
    m_bgMusicVolume->setMaximumValue(100.0f);
    m_bgMusicVolume->setMinimumValue(0.0f);
    m_bgMusicVolume->setCurrentValue(100.0f);

    //
    // difficulty combo box
    //
    text = new TGUI::TGLabel(m_optionsDlg,"", "Difficulty:");
    text->setPos(0.1f,0.5f);
    text->setSize(0.4f,0.05f);
    text->setAlignment(TGUI::alRight);

    m_difficulty = new TGUI::TGComboBox(m_optionsDlg);
    m_difficulty->setPos(0.55f,0.495f);
    m_difficulty->setSize(0.35f,0.04f);

    m_difficulty->addItem("Easy");
    m_difficulty->addItem("Normal");
    m_difficulty->addItem("Hard");

    m_difficulty->setText("Normal");

    m_difficulty->setStyle(TGUI::CBS_DROPDOWN_LIST);

    //
    // theme combo box
    //

    text = new TGUI::TGLabel(m_optionsDlg,"","Theme:");
    text->setPos(0.1f,0.6f);
    text->setSize(0.4f,0.05f);
    text->setAlignment(TGUI::alRight);

    m_theme = new TGUI::TGComboBox(m_optionsDlg);
    m_theme->setPos(0.55f,0.595f);
    m_theme->setSize(0.35f,0.04f);
    m_theme->setText("Random");
    m_theme->setStyle(TGUI::CBS_DROPDOWN_LIST);

    m_theme->addItem("Random");
    m_theme->addItem("Sequential");

    //
    // iterate through the available themes and add them
    //
    Tubras::TThemeManager* tm;
    tm = getThemeManager();

    for(size_t i=0;i<tm->getThemeCount();i++)
    {
        m_theme->addItem(tm->getTheme(i)->getName());
    }

    m_optionsDlg->hide();

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
//                        s a v e O p t i o n s
//-----------------------------------------------------------------------
void TOptionsState::saveOptions()
{

    m_playOptions.m_bgMusic = m_bgMusicEnabled->getState();
    m_playOptions.m_bgMusicVolume = m_bgMusicVolume->getCurrentValue();
    Tubras::TString difficulty;
    difficulty = m_difficulty->getText();
    if(!difficulty.compare("Easy"))
        m_playOptions.m_difficulty = cmEasy;
    else if(!difficulty.compare("Normal"))
        m_playOptions.m_difficulty = cmNormal;
    else m_playOptions.m_difficulty = cmHard;
    m_playOptions.m_theme = m_theme->getText();

    regOpenSection("options");
    regWriteKey("difficulty",m_playOptions.m_difficulty);
    regWriteKey("bgmusic",m_playOptions.m_bgMusic);
    regWriteKey("bgmusicvolume",m_playOptions.m_bgMusicVolume);
    regWriteKey("theme",m_playOptions.m_theme);
}

//-----------------------------------------------------------------------
//                      s a v e C l i c k e d
//-----------------------------------------------------------------------
int TOptionsState::saveClicked(Tubras::TSEvent)
{
    m_doSave = true;
    return 1;
}

//-----------------------------------------------------------------------
//                     c a n c e l C l i c k e d
//-----------------------------------------------------------------------
int TOptionsState::cancelClicked(Tubras::TSEvent)
{
    m_doCancel = true;
    popState();
    return 1;
}

//-----------------------------------------------------------------------
//                        s e t O p t i o n s
//-----------------------------------------------------------------------
void TOptionsState::setOptions()
{
    if(m_playOptions.m_bgMusic)
        m_bgMusicEnabled->setState(true);
    else m_bgMusicEnabled->setState(false);

    m_bgMusicVolume->setCurrentValue(m_playOptions.m_bgMusicVolume);

    switch(m_playOptions.m_difficulty)
    {
    case cmEasy :
        m_difficulty->setText("Easy");
        break;
    case cmNormal :
        m_difficulty->setText("Normal");
        break;
    case cmHard :
        m_difficulty->setText("Hard");
        break;
    };

    m_theme->setText(m_playOptions.m_theme);
    
}

//-----------------------------------------------------------------------
//                           E n t e r
//-----------------------------------------------------------------------
int TOptionsState::Enter()
{
    
    m_doSave = false;
    m_doCancel = false;
    m_optionsDlg->show();

    setOptions();
    enableEvents(this);

    return 0;
}

//-----------------------------------------------------------------------
//                             E x i t 
//-----------------------------------------------------------------------
Tubras::TStateInfo* TOptionsState::Exit()
{
    m_optionsDlg->hide();
    disableEvents(this);

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


