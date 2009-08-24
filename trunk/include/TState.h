//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TSTATE_H_
#define _TSTATE_H_

namespace Tubras
{
    class TStateInfo
    {
    public:
        int     m_returnCode;

    };

    typedef TMap<TString, TState*> TStateMap;
    typedef TMap<TString, TState*>::Iterator TStateMapItr;
    typedef TList<TState*> TStateStack;

    /**
    TState Class.
    @remarks
        A class inherited from TState is also an event handler.  This doesn't mean
        events are automatically sent to the inherited class.  Instead, the class
        contains the ability to receive events.
    */
    class TState : public TDelegate
    {
    protected:
        TString             m_name;
        TApplication*       m_app;
        TStateInfo          m_info;

    public:
        TState(const TString& name);
        virtual ~TState();

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
