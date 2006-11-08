//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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

#ifndef _TCONTROLLERFUNCTION_H_
#define _TCONTROLLERFUNCTION_H_

namespace Tubras
{
    /** Enumerates the wave types usable with the Ogre engine. */
    enum TWaveformType
    {
        /// Standard sine wave which smoothly changes from low to high and back again.
        WFT_SINE,
        /// An angular wave with a constant increase / decrease speed with pointed peaks.
        WFT_TRIANGLE,
        /// Half of the time is spent at the min, half at the max with instant transition between.
        WFT_SQUARE,
        /// Gradual steady increase from min to max over the period with an instant return to min at the end.
        WFT_SAWTOOTH,
        /// Gradual steady decrease from max to min over the period, with an instant return to max at the end.
        WFT_INVERSE_SAWTOOTH,
        /// Pulse Width Modulation. Works like WFT_SQUARE, except the high to low transition is controlled by duty cycle. 
        /// With a duty cycle of 50% (0.5) will give the same output as WFT_SQUARE.
        WFT_PWM
    };


    /**
    TController Class.
    @remarks
    Controller class - a variation of Ogre::Controller.

    Creating a controller automatically registers it with the Controller Manager.  The manager 
    automatically deletes registered controllers when the manager itself is destroyed.

    If you would like to remove a controller that is no longer needed:
    1. Invoke TControllerManager::remove()
    2. Delete the controller manually

    */

    class TControllerFunction : public TObject
    {
    protected:
        float                   m_value;
    public:
        TControllerFunction();
        virtual ~TControllerFunction();

        virtual float step(float deltaTime) {return m_value;};
        float getValue() {return m_value;};
        virtual void setValue(float value) {m_value = value;};
    };

    class TPassThroughControllerFunction : public TControllerFunction
    {
    public:
        virtual float step(float value);
    };

    class TWaveControllerFunction : public TControllerFunction
    {
    protected:
        TWaveformType           m_waveType;
        float                   m_base;
        float                   m_frequency;
        float                   m_phase;
        float                   m_amplitude;
        float                   m_dutyCycle;
        float                   m_elapsed;
    public:
        TWaveControllerFunction(TWaveformType wType, float base = 0, float frequency = 1, 
            float phase = 0, float amplitude = 1, float dutyCycle = 0.5);

        virtual float step(float value);
    };
}
#endif