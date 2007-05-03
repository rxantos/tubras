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
    Tubras::TSceneNode* m_parent;
    Tubras::TSound*     m_ambientSound;
    Tubras::TSound*     m_guiRollover;
    Tubras::TSound*     m_guiClick;
    TGUI::TGScreen*     m_GUIScreen;
    TGUI::TGImage*      m_GUIMenu;
    TGUI::TGImage*      m_mokena;
    TGUI::TGImage*      m_mokenas;
    Tubras::TCardNode*      m_background;

    Tubras::TFunctionInterval* m_fiUp;
    Tubras::TFunctionInterval* m_fiDown;
    size_t              m_upID;
    Tubras::TEventDelegate* m_toggleDelegate;
    const TGUI::TGCursor* m_mouseCursor;
    TGUI::TGImage*      m_scoreDlg;

    TGUI::TGImageButton* m_playButton;
    TGUI::TGImageButton* m_quitButton;
    TGUI::TGImageButton* m_optionsButton;
    bool                m_doQuit;
    bool                m_doPlay;
    bool                m_doOptions;
    bool                m_centerMouse;

public:
    TMenuState();
    virtual ~TMenuState();

    virtual int initialize();
    int quitApp(Tubras::TSEvent event);
    void alphaUp(double T, void* userData);
    void alphaDn(double T, void* userData);

    int alphaDone(Tubras::TSEvent event);
    int playClicked(Tubras::TSEvent event);
    int quitClicked(Tubras::TSEvent event);
    int optionsClicked(Tubras::TSEvent event);
    int mouseEnter(Tubras::TSEvent event);
    int mouseDown(Tubras::TSEvent event);

    TGUI::TGImage* getGUIMenu() {return m_GUIMenu;}

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
