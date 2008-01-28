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
    //                        T S h a k e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TShakeController::TShakeController(TString name, ISceneNode* node, float duration,
        float magnitude, bool easeInOut) : TIntervalController(name,0.f,duration,duration,0,0,easeInOut ? btEaseInOut : btNoBlend),
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

        setEnabled(false);
    }

}