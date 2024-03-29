//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TSCRIPTSTATE_H_
#define _TSCRIPTSTATE_H_

namespace Tubras
{

    /**
    TState Class.
    @remarks
        A class inherited from TState is also an event handler.  This doesn't mean
        events are automatically sent to the inherited class.  Instead, the class
        contains the ability to receive events.
    */
    class TScriptState : TState
    {
    protected:
        TString             m_name;
        TApplication*       m_app;
        lua_State*          m_lua;

        TStateInfo          m_info;
        int                 m_rInit;
        int                 m_rEnter;
        int                 m_rExit;
        int                 m_rPause;
        int                 m_rResume;
        int                 m_rReset;

    protected:
        int callStateFunc(int ref);

    public:
        TScriptState(const TString& name, lua_State* L, int ref_init, int ref_enter, 
            int ref_exit, int ref_pause, int ref_resume, int ref_reset);
        virtual ~TScriptState();

        TString getName() {return m_name;};

        virtual int initialize();

        virtual int Enter();
        virtual TStateInfo* Exit();
        virtual int Reset();
        virtual int Pause();
        virtual int Resume(TStateInfo* prevStateInfo);

        //
        // management convenience functions
        //
        int changeState(const TString& stateName);
        int pushState(const TString& stateName);
        int popState();

    };

}
#endif
