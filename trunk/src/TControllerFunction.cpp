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
    //                    T C o n t r o l l e r F u n c t i o n
    //-----------------------------------------------------------------------
    TControllerFunction::TControllerFunction()
    {
        m_value = 0.0;
    }

    //-----------------------------------------------------------------------
    //                   ~ T C o n t r o l l e r F u n c t i o n
    //-----------------------------------------------------------------------
    TControllerFunction::~TControllerFunction()
    {
    }

    //-----------------------------------------------------------------------
    //                              s t e p
    //-----------------------------------------------------------------------
    float TPassThroughControllerFunction::step(float deltaTime)
    {
        return m_value = (deltaTime / 1000);
    }

    //-----------------------------------------------------------------------
    //               T W a v e C o n t r o l l e r F u n c t i o n
    //-----------------------------------------------------------------------
    TWaveControllerFunction::TWaveControllerFunction(TWaveformType wType, float base,  float frequency, 
        float phase, float amplitude, float dutyCycle)
        : TControllerFunction()
    {
        m_waveType = wType;
        m_base = base;
        m_frequency = frequency;
        m_phase = phase;
        m_amplitude = amplitude;
        m_dutyCycle = dutyCycle;
        m_elapsed = 0;
    }

    //-----------------------------------------------------------------------
    //                              s t e p
    //-----------------------------------------------------------------------
    float TWaveControllerFunction::step(float deltaTime)
    {

        m_elapsed += ((deltaTime / 1000.0f) * m_frequency);
        while(m_elapsed > 1.0)
            m_elapsed -= 1.0;
        while(m_elapsed < 0.0)
            m_elapsed += 1.0;

        float input = m_elapsed;
        float output;

        // Calculate output in -1..1 range
        switch (m_waveType)
        {
        case WFT_SINE:
            output = sin(TRadian(input * TMath::TWO_PI).valueRadians());
            break;
        case WFT_TRIANGLE:
            if (input < 0.25)
                output = input * 4;
            else if (input >= 0.25 && input < 0.75)
                output = (float) (1.0 - ((input - 0.25) * 4.0));
            else
                output = (float) (((input - 0.75) * 4.0) - 1.0);

            break;
        case WFT_SQUARE:
            if (input <= 0.5)
                output = 1.0;
            else
                output = -1.0;
            break;
        case WFT_SAWTOOTH:
            output = (input * 2) - 1;
            break;
        case WFT_INVERSE_SAWTOOTH:
            output = -((input * 2) - 1);
            break;
        case WFT_PWM:
            if( input <= m_dutyCycle )
                output = 1.0;
            else
                output = -1.0;
            break;
        };

        m_value =  m_amplitude * output;
        return m_value;
    }
}
