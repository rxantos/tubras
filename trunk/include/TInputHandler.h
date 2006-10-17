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

#ifndef _TINPUTHANDLER_H_
#define _TINPUTHANDLER_H_
namespace Tubras
{

    class TApplication;
    class TEventManager;

    class TInputHandler : public Tubras::TSingleton<Tubras::TInputHandler>,
        public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener

    {
    private:
        TApplication*		m_pApplication;
        TTimer*             m_pTimer;
        TEventManager*      m_eventManager;
        TInputBinder*       m_binder;
        bool                m_GUIEnabled;
        bool                m_GUIExclusive;

    private:
        static TInputHandler& getSingleton(void);
        static TInputHandler* getSingletonPtr(void);
    public:
        TInputHandler();
        ~TInputHandler();
        void setGUIEnabled(bool enabled) {m_GUIEnabled = enabled;};
        void setGUIExclusive(bool exclusive) {m_GUIExclusive = exclusive;};
        int Initialize();
        virtual bool keyPressed( const OIS::KeyEvent& arg );
        virtual bool keyReleased( const OIS::KeyEvent& arg );
        virtual bool mouseMoved( const OIS::MouseEvent &arg );
        virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
        virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ); 
        virtual bool buttonPressed( const OIS::JoyStickEvent &arg, int button );
        virtual bool buttonReleased( const OIS::JoyStickEvent &arg, int button );
        virtual bool axisMoved( const OIS::JoyStickEvent &arg, int axis );
        virtual bool povMoved( const OIS::JoyStickEvent &arg, int pov );

    };
}
#endif
