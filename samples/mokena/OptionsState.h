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
#ifndef _OPTIONSSTATE_H_
#define _OPTIONSSTATE_H_

class TOptionsState : public Tubras::TState
{
private:
    Tubras::TSound*             gui_rollover, *gui_click;
    TGUI::TGImage*              m_GUIMenu;
    TGUI::TGImage*              m_optionsDlg;
    Tubras::TEventDelegate*     m_toggleDelegate;
    const TGUI::TGCursor*       m_mouseCursor;

    struct TPlayOptions         m_playOptions;

    //
    // gui controls
    //
    TGUI::TGCheckBox*           m_bgMusicEnabled;
    TGUI::TGSpinEdit*           m_bgMusicVolume;
    TGUI::TGComboBox*           m_difficulty;
    TGUI::TGComboBox*           m_theme;

    TGUI::TGImageButton*        m_saveButton;
    TGUI::TGImageButton*        m_cancelButton;
    bool                        m_doSave;
    bool                        m_doCancel;

private:
    void setOptions();
    void saveOptions();
public:
    TOptionsState();
    virtual ~TOptionsState();

    virtual int initialize();
    int quitApp(Tubras::TSEvent event);
    int saveClicked(Tubras::TSEvent event);
    int cancelClicked(Tubras::TSEvent event);
    int mouseEnter(Tubras::TSEvent event);
    int mouseDown(Tubras::TSEvent event);

    struct TPlayOptions* getOptions() {return &m_playOptions;};

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
