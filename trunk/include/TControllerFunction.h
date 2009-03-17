//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TCONTROLLERFUNCTION_H_
#define _TCONTROLLERFUNCTION_H_

namespace Tubras
{
    /** Enumerates the wave types usable with the wave controller function. */
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
    Controller class - Inspired by both the Ogre & Panda3D controller classes.

    Creating a controller automatically registers it with the Controller Manager.  The manager 
    automatically deletes registered controllers when the manager itself is destroyed.

    If you would like to remove a controller that is no longer needed:
    1. Invoke TControllerManager::remove()
    2. Delete the controller manually

    */

    class TControllerFunction : public TDObject
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

