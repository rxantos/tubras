//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on the "Timing Framework" by Chet Haase & others: 
//      https://timingframework.dev.java.net/
//-----------------------------------------------------------------------------
#ifndef __I_TIMING_TARGET_H_INCLUDED__
#define __I_TIMING_TARGET_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        class ITimingTarget
        {
        public:
            /**
            * This method will receive all of the timing events from an Animator
            * during an animation.  The fraction is the percent elapsed (0 to 1)
            * of the current animation cycle.
            * @param fraction the fraction of completion between the start and
            * end of the current cycle.  Note that on reversing cycles
            * ({@link Animator.Direction#BACKWARD}) the fraction decreases
            * from 1.0 to 0 on backwards-running cycles.  Note also that animations
            * with a duration of {@link Animator#INFINITE INFINITE} will call
            * timingEvent with an undefined value for fraction, since there is
            * no fraction that makes sense if the animation has no defined length.
            * @see Animator.Direction
            */
            virtual void timingEvent(float fraction) = 0;

            /**
            * Called when the Animator's animation begins.  This provides a chance
            * for targets to perform any setup required at animation start time.
            */
            virtual void begin() = 0;

            /**
            * Called when the Animator's animation ends
            */
            virtual void end() = 0;

            /**
            * Called when the Animator repeats the animation cycle
            */
            virtual void repeat() = 0;

        };

        /**
        * Implements the {@link TimingTarget} interface, providing stubs for all
        * TimingTarget methods.  Subclasses may extend this adapter rather than
        * implementing the TimingTarget interface if they only care about a 
        * subset of the events that TimingTarget provides.  For example, 
        * sequencing animations may only require monitoring the 
        * {@link TimingTarget#end} method, so subclasses of this adapter
        * may ignore the other methods such as timingEvent.
        *
        */
        class CTimingTargetAdapter : public ITimingTarget {
            /**
            * This method will receive all of the timing events from an Animator
            * during an animation.  The fraction is the percent elapsed (0 to 1)
            * of the current animation cycle.
            * @param fraction the fraction of completion between the start and
            * end of the current cycle.  Note that on reversing cycles
            * ({@link Animator.Direction#BACKWARD}) the fraction decreases
            * from 1.0 to 0 on backwards-running cycles.  Note also that animations
            * with a duration of {@link Animator#INFINITE INFINITE} will call
            * timingEvent with an undefined value for fraction, since there is
            * no fraction that makes sense if the animation has no defined length.
            * @see Animator.Direction
            */
            virtual void timingEvent(float fraction) {}

            /**
            * Called when the Animator's animation begins.  This provides a chance
            * for targets to perform any setup required at animation start time.
            */
            virtual void begin() {}

            /**
            * Called when the Animator's animation ends
            */
            virtual void end() {}

            /**
            * Called when the Animator repeats the animation cycle
            */
            virtual void repeat() {}

        };
    }
}
#endif
