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
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                  T I n t e r v a l C o n t r o l l e r
    //-----------------------------------------------------------------------
    TIntervalController::TIntervalController(const TString& name, float start, float stop, float duration, 
        TIntervalDelegate* delegate, void* userData, TBlendType blendType, TString finishedEvent) : TController(name, 0),
        m_start(start), 
        m_stop(stop), 
        m_duration(duration),
        m_elapsed(0.f),
        m_length(m_stop-m_start),
        m_delegate(delegate),
        m_userData(userData),
        m_finished(false),
        m_current(m_start),
        m_blendType(blendType),
        m_finishedEvent(finishedEvent)
    {
    }

    //-----------------------------------------------------------------------
    //                 ~ T I n t e r v a l C o n t r o l l e r
    //-----------------------------------------------------------------------
    TIntervalController::~TIntervalController()
    {
    }

    //-----------------------------------------------------------------------
    //                      c o m p u t e D e l t a 
    //-----------------------------------------------------------------------
    float TIntervalController::computeDelta(float t)
    {
        float duration = m_duration;
        if (duration == 0.0) {
            // If duration is 0, the lerp works as a set.  Thus, the delta is
            // always 1.0, the terminating value.
            return 1.0;
        }
        t /= duration;
        t = min_<float>(max_<float>(t, 0.0), 1.0);

        switch (m_blendType) 
        {
        case btEaseIn:
            {
                double t2 = t * t;
                return (float)(((3.0 * t2) - (t2 * t)) * 0.5);
            }
        case btEaseOut:
            {
                double t2 = t * t;
                return (float)(((3.0 * t) - (t2 * t)) * 0.5);
            }
        case btEaseInOut:
            {
                double t2 = t * t;
                return (float)((3.0 * t2) - (2.0 * t * t2));
            }
        default:
            return t;
        }
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TIntervalController::update(float value)
    {
        if(m_finished)
            return;

        m_elapsed += value;

        float d = computeDelta(m_elapsed);

        m_current = m_start + d * (m_stop - m_start);

        m_delegate->Execute(m_current,m_userData);

        if(m_current >= m_stop)
        {
            m_finished = true;
            m_manager->stop(this);
        }
    }
}