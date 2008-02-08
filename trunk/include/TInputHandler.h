//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
        TEventManager*      m_eventManager;
        TInputBinder*       m_binder;
        OIS::Keyboard*      m_keyboard;
        bool                m_GUIEnabled;
        bool                m_GUIExclusive;
        TEvent*             m_kpEvent;
        TEvent*             m_krEvent;
        TEvent*             m_mmEvent;
        TEvent*             m_mpEvent;
        TEvent*             m_mrEvent;

    private:
        static TInputHandler& getSingleton(void);
        static TInputHandler* getSingletonPtr(void);
    public:
        TInputHandler(OIS::Keyboard* keyboard);
        ~TInputHandler();
        void setGUIEnabled(bool enabled) {m_GUIEnabled = enabled;};
        void setGUIExclusive(bool exclusive) {m_GUIExclusive = exclusive;};
        bool getGUIEnabled() {return m_GUIEnabled;}
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
