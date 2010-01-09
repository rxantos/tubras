//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TINPUTHANDLER_H_
#define _TINPUTHANDLER_H_
namespace Tubras
{

    class TApplication;
    class TEventManager;

    typedef TArray<IGUIEnvironment*> TGUIList;

    class TInputHandler : public IEventReceiver
    {
        friend class TInputManager;

    private:
        u32                 m_inputMode;
        TEventManager*      m_eventManager;
        TInputBinder*       m_binder;
        ICursorControl*     m_cursorControl;
        TGUIList            m_guiList;
        TGUICursor*         m_guiCursor;
        vector2di           m_curPos;
        vector2di           m_relPos;
        vector2di           m_centerPos;
        bool                m_cursorVisible;
        bool                m_cursorCentered;
        TEvent*             m_kpEvent;
        TEvent*             m_krEvent;
        TEvent*             m_mmEvent;
        TEvent*             m_mpEvent;
        TEvent*             m_mrEvent;
        bool                m_keyStates[KEY_KEY_CODES_COUNT];

    private:
        TInputHandler();
        ~TInputHandler();

    public:
	    bool OnEvent(const SEvent& event);

        bool isKeyDown(EKEY_CODE key) {return m_keyStates[key];}
        void setCursorVisible(bool value);
        bool getCursorVisible() {return m_cursorVisible;}
        void setCursorCentered(bool value);
        bool getCursorCentered() {return m_cursorCentered;}

        u32 getInputMode() {return m_inputMode;}
        void setInputMode(u32 value) {m_inputMode = value;}

        bool addGUIEnvironment(IGUIEnvironment* env);
        bool removeGUIEnvironment(IGUIEnvironment* env);

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
