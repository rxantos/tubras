//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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

    class TInputHandler : public Tubras::TSingleton<Tubras::TInputHandler>, public IEventReceiver

    {
    private:
        TEventManager*      m_eventManager;
        TInputBinder*       m_binder;
        bool                m_GUIEnabled;
        bool                m_GUIExclusive;
        TEvent*             m_kpEvent;
        TEvent*             m_krEvent;
        TEvent*             m_mmEvent;
        TEvent*             m_mpEvent;
        TEvent*             m_mrEvent;
        bool                m_keyStates[KEY_KEY_CODES_COUNT];

    private:
        static TInputHandler& getSingleton(void);
        static TInputHandler* getSingletonPtr(void);
    public:
        TInputHandler();
        ~TInputHandler();

	    bool OnEvent(const SEvent& event);

        void setGUIEnabled(bool enabled) {m_GUIEnabled = enabled;};
        void setGUIExclusive(bool exclusive) {m_GUIExclusive = exclusive;};
        bool getGUIEnabled() {return m_GUIEnabled;}
        bool isKeyDown(EKEY_CODE key) {return m_keyStates[key];}
        int Initialize();
        virtual bool keyPressed( const struct SEvent& arg );
        virtual bool keyReleased( const struct SEvent& arg );
        virtual bool mouseMoved( const struct SEvent& arg );
        virtual bool mousePressed( const struct SEvent& arg);
        virtual bool mouseReleased( const struct SEvent& arg); 
        virtual bool buttonPressed( const struct SEvent& arg);
        virtual bool buttonReleased( const struct SEvent& arg);
        virtual bool axisMoved( const struct SEvent& arg);
        virtual bool povMoved( const struct SEvent& arg);

    };
}
#endif
