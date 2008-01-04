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

#ifndef _TGUIMANAGER_H_
#define _TGUIMANAGER_H_

namespace Tubras
{

    class TGUIManager : public Tubras::TSingleton<Tubras::TGUIManager>, public TObject
    {
    protected:
        TGUI::TGRenderer*         m_GUIRenderer;
        TGUI::TGSystem*           m_GUISystem;
        TString					  m_GUISchemeName;
        TString					  m_GUILookName;
        TGUI::TGLogger*           m_GUILogger;

    protected:
        bool eventHook(const TGUI::TGEventArgs& args);

    public:
        TGUIManager();
        virtual ~TGUIManager();
        static TGUIManager& getSingleton(void);
        static TGUIManager* getSingletonPtr(void);
        int initialize(Ogre::RenderWindow* window, Ogre::SceneManager* sceneMgr, TString defaultFont);

        TGUI::TGSystem*  getSystem() {return m_GUISystem;};
        TGUI::TGRenderer* getRenderer() {return m_GUIRenderer;};

        inline TString getLookName() {return m_GUILookName;};
        void injectTimePulse(float timeElapsed);

    };
}
#endif
