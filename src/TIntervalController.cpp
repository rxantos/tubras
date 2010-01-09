//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                  T I n t e r v a l C o n t r o l l e r
    //-----------------------------------------------------------------------
    TIntervalController::TIntervalController(const TString& name, float start, 
        float stop, float duration, TBlendType blendType, 
        TString startedEvent, TString stoppedEvent) : TController(name, 0, 0, startedEvent, stoppedEvent),
        m_duration(duration),
        m_start(start), 
        m_stop(stop), 
        m_length(m_stop-m_start),
        m_elapsed(0.f),
        m_current(m_start),
        m_blendType(blendType)
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
        if(!m_active)
            return;

        m_elapsed += value;

        float d = computeDelta(m_elapsed);

        m_current = m_start + d * (m_stop - m_start);

        intervalUpdate(m_current);

        if(m_current >= m_stop)
        {
            stop();
        }
    }

    //-----------------------------------------------------------------------
    //                TGUIImageColorInterval::intervalUpdate
    //-----------------------------------------------------------------------
    void TGUIImageColorInterval::intervalUpdate(float current)
    {
        TColorInterval::intervalUpdate(current);
        m_element->setColor(m_color);
    }

}
