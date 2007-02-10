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
#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_

class TMenuState : public Tubras::TState
{
private:
    Ogre::SceneNode*    m_parent;
    Tubras::TSound*     m_sound1;
    Tubras::TSound*     m_sound2;
    Tubras::TSound*     m_ambientSound;
    Tubras::TSound* gui_rollover, *gui_click;
    TGUI::TGScreen* m_GUIScreen;
    TGUI::TGImage* m_GUIMenu;
    Tubras::TFunctionInterval* m_finterval;
    int slideDirection;
    Tubras::TEventDelegate* m_toggleDelegate;
    const TGUI::TGCursor* m_mouseCursor;

    TGUI::TGImageButton* m_playButton;
    TGUI::TGImageButton* m_quitButton;
    TGUI::TGImageButton* m_optionsButton;
    bool m_doQuit;
    bool m_doPlay;
    bool m_doOptions;
    bool m_centerMouse;

public:
    TMenuState();
    virtual ~TMenuState();

    virtual int initialize();
    int quitApp(Tubras::TSEvent event);
    void slideMenu(double T, void* userData);
    int slideDone(Tubras::TSEvent event);
    int playClicked(Tubras::TSEvent event);
    int quitClicked(Tubras::TSEvent event);
    int optionsClicked(Tubras::TSEvent event);
    int mouseEnter(Tubras::TSEvent event);
    int mouseDown(Tubras::TSEvent event);

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
