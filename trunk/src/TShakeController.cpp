//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T S h a k e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TShakeController::TShakeController(TString name, ISceneNode* node, float duration,
        float magnitude, bool easeInOut) : TIntervalController(name,0.f,duration,duration,easeInOut ? btEaseInOut : btNoBlend),
            m_duration(duration),
            m_magnitude(magnitude),
            m_easeInOut(easeInOut),
            m_shakeDelta(0)
    {
        setNode(node);
    }

    //-----------------------------------------------------------------------
    //                       ~ T S h a k e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TShakeController::~TShakeController()
    {
    }

    //-----------------------------------------------------------------------
    //                              s t a r t
    //-----------------------------------------------------------------------
    void TShakeController::start(u32 startTime)
    {
        m_nodeStartPos = m_node->getAbsolutePosition();
        m_shakeDelta = 0;
    }

    //-----------------------------------------------------------------------
    //                              s t o p
    //-----------------------------------------------------------------------
    void TShakeController::stop()
    {
        //
        // reset to original position
        //
        m_node->setPosition(m_nodeStartPos);
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TShakeController::update(float value)
    {
        TIntervalController::update(value);
        m_shakeDelta += value;

        if(m_shakeDelta >= 40)
        {
            TVector3 v(m_random.getRandomUniform(-m_magnitude,m_magnitude),
                m_random.getRandomUniform(-m_magnitude,m_magnitude),
                m_random.getRandomUniform(-m_magnitude,m_magnitude));
            m_node->setPosition(m_nodeStartPos + v);
            m_shakeDelta = 0;
        }

        if( m_elapsed < m_duration)
        {
            return;
        }

        stop();
    }
}

