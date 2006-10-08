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

#ifndef _TSTATE_H_
#define _TSTATE_H_

namespace Tubras
{
    class TApplication;
    class TSound;
    class TWindow;

    class TStateInfo
    {
    public:
        int     m_returnCode;

    };

    /**
    TState Class.
    @remarks
        A class inherited from TState is also an event handler.  This doesn't mean
        events are automatically sent to the inherited class.  Instead, the class
        contains the ability to receive events.
    */
    class TState : public TObject
    {
    protected:
        string              m_name;
        bool                m_GUIEnabled;
        
        TStateInfo          m_info;

    public:
        TState(string name);
        virtual ~TState();

        string getName() {return m_name;};

        virtual int initialize();

        virtual int Enter();
        virtual TStateInfo* Exit();
        virtual int Reset();
        virtual int Pause();
        virtual int Resume(TStateInfo* prevStateInfo);

        //
        // GUI convenience function
        //
        void setGUIEnabled(bool enabled);
        void setGUIExclusive(bool exclusive);
        inline bool getGUIEnabled() {return m_GUIEnabled;};
        CEGUI::System* getGUISystem();
        CEGUI::Renderer* getGUIRenderer();
        TWindow* getGUISheet();
        TRenderEngine* getRenderEngine();

        //
        // management convenience functions
        //
        int changeState(string stateName);
        int pushState(string stateName);
        int popState();

    };
}
#endif
