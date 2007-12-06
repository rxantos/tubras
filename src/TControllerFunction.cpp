//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
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
