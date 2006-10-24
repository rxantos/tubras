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
#ifndef _OPTIONSSTATE_H_
#define _OPTIONSSTATE_H_

class TOptionsState : public Tubras::TState
{
private:
    Ogre::SceneNode* m_parent;
    Tubras::TSound* sound1,* sound2, *ambientSound;
    Tubras::TWindow* m_GUIRoot;
    Tubras::TStaticImage* m_frame;
    Tubras::TFunctionInterval* m_finterval;
    int slideDirection;
    Tubras::TEventDelegate* m_toggleDelegate;
    const CEGUI::Image* m_mouseCursor;

    Tubras::TImageButton* m_saveButton;
    Tubras::TImageButton* m_cancelButton;
    bool m_doSave;
    bool m_doCancel;

public:
    TOptionsState();
    virtual ~TOptionsState();

    virtual int initialize();
    int quitApp(Tubras::TSEvent event);
    void slideMenu(double T, void* userData);
    int slideDone(Tubras::TSEvent event);
    int toggleMouse(Tubras::TSEvent event);
    int saveClicked(Tubras::TSEvent event);
    int cancelClicked(Tubras::TSEvent event);

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
