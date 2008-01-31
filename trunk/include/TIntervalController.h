//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#ifndef _TINTERVALCONTROLLER_H_
#define _TINTERVALCONTROLLER_H_

namespace Tubras
{


    class TIntervalController : public TController
    {
    protected:
        TIntervalDelegate*      m_delegate;
        void*                   m_userData;
        float                   m_duration;
        float                   m_start;
        float                   m_stop;
        float                   m_length;
        float                   m_elapsed;
        float                   m_current;
        bool                    m_finished;
        TBlendType              m_blendType;
        TString                 m_finishedEvent;

    protected:
        float computeDelta(float t);


    public:
        TIntervalController(const TString& name, float start, float stop, float duration, 
            TIntervalDelegate* delegate,void* userData=0, TBlendType blendType=btNoBlend, TString finishedEvent="");

        virtual ~TIntervalController();

        void setFinishedEvent(const TString& value) {m_finishedEvent = value;}
        TString getFinishedEvent() {return m_finishedEvent;}

        virtual void update(float deltaTime);
    };

    typedef TIntervalController TInterval;

    #define INTERVAL_DELEGATE(member) new Tubras::TIntervalDelegate(this,(Tubras::TIntervalDelegateFunction)&member)
}

#endif

