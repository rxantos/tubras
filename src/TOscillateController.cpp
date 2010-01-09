//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                  T O s c i l l a t e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TOscillateController::TOscillateController(const TString& name, ISceneNode* node, float velocity,
        float amplitude, TVector3 axis) : TController(name, 
        new TWaveControllerFunction(WFT_SINE,0,velocity,1,amplitude,0.5), node)
    {
        m_axis = axis;
        m_velocity = velocity;
        m_amplitude = amplitude;
        m_currentPos = m_node->getPosition();
    }

    //-----------------------------------------------------------------------
    //                 ~ T O s c i l l a t e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TOscillateController::~TOscillateController()
    {
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TOscillateController::update(float value)
    {
        TVector3 adjust = m_axis * value;

        m_node->setPosition(m_currentPos + adjust);
    }
}

