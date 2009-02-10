//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                  T O s c i l l a t e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TOscillateController::TOscillateController(const TString& name, ISceneNode* node, float velocity,
        float amplitude, TVector3 axis) : TController(name, node, 
        new TWaveControllerFunction(WFT_SINE,0,velocity,1,amplitude,0.5))
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

