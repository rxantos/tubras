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

