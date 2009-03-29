//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TINTERVALCONTROLLER_H_
#define _TINTERVALCONTROLLER_H_

namespace Tubras
{
    class TIntervalController : public TController
    {
    protected:
        TIntervalDelegate*      m_delegate;
        const void*             m_userData;
        float                   m_duration;
        float                   m_start;
        float                   m_stop;
        float                   m_length;
        float                   m_elapsed;
        float                   m_current;
        TBlendType              m_blendType;

    protected:
        float computeDelta(float t);

    public:
        TIntervalController(const TString& name, float start, float stop, float duration, 
            TIntervalDelegate* delegate,const void* userData=0, TBlendType blendType=btNoBlend, 
            TString startedEvent="", TString finishedEvent="");

        virtual ~TIntervalController();

        virtual void start() 
        {
            TController::start();
            m_elapsed = 0.f;
        }

        virtual void update(float deltaTime);
    };

    typedef TIntervalController TInterval;

    #define INTERVAL_DELEGATE(member) new Tubras::TIntervalDelegate(this,(Tubras::TIntervalDelegateFunction)&member)
}

#endif

