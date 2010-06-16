//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on the "Timing Framework" by Chet Haase & others: 
//      https://timingframework.dev.java.net/
//-----------------------------------------------------------------------------
#ifndef __C_ANIMATOR_H_INCLUDED__
#define __C_ANIMATOR_H_INCLUDED__
#include "irrlicht.h"
using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

#include "ITimingEventListener.h"
#include "ITimingSource.h"
#include "IEvaluator.h"
#include "IInterpolator.h"
#include "ITimingTarget.h"
#include "IAnimator.h"
#include "CLinearInterpolator.h"


namespace irr
{
    namespace timing
    {
#ifdef INFINITE
#undef INFINITE
#endif
        class CAnimator : public IAnimator, public ITimingTarget, public ITimingEventListener
        {
            friend class CTimingManager;

        private:
            ITimingSource* timer;    

            core::array<ITimingTarget*> targets; // Animators may have multiple targets

            long startTime;	    // Tracks original Animator start time
            long currentStartTime;  // Tracks start time of current cycle
            int currentCycle;   // Tracks number of cycles so far
            bool intRepeatCount;  // for typical cases
            // of repeated cycles
            bool timeToStop;     // This gets triggered during
            // fraction calculation
            bool hasBegun;
            long pauseBeginTime;        // Used for pause/resume
            bool running;        // Used for isRunning()

            // Private variables to hold the internal "envelope" values that control
            // how the cycle is started, ended, and repeated.
            double repeatCount;
            int startDelay;
            RepeatBehavior repeatBehavior;
            EndBehavior endBehavior;

            // Private variables to hold the internal values of the base
            // animation (the cycle)
            int duration;
            int resolution;
            float acceleration;
            float deceleration;
            float startFraction;
            Direction direction;// Direction of each cycle
            IInterpolator* interpolator;

            /**
            * Private utility to throw an exception if the animation is running.  This
            * is used by all of the property-setting methods to ensure that the
            * properties are not being changed mid-stream.
            */

            void throwExceptionIfRunning() {
                if (isRunning()) {
                    //throw new IllegalStateException("Cannot perform this operation " +
                    //    "while Animator is running");
                }
            }

        protected:
            /**
            * Constructor that sets the most common properties of a 
            * repeating animation.
            * @param duration the length of each animation cycle, in milliseconds.
            * This value can also be {@link #INFINITE} for animations that have no
            * end.  Note that fractions sent out with such unending animations will
            * be undefined since there is no fraction of an infinitely long cycle.
            * @param repeatCount the number of times the animation cycle will repeat.
            * This is a positive value, which allows a non-integral number
            * of repetitions (allowing an animation to stop mid-cycle, for example).
            * This value can also be {@link #INFINITE}, indicating that the animation
            * will continue repeating forever, or until manually stopped.
            * @param repeatBehavior {@link RepeatBehavior} of each successive
            * cycle.  A value of 0 is equivalent to RepeatBehavior.REVERSE.
            * @param target TimingTarget object that will be called with
            * all timing events.  0 is acceptable, but no timingEvents will be
            * sent to any targets without future calls to {@link #addTarget}.
            * @throws IllegalArgumentException if any parameters have invalid
            * values
            * @see Animator#INFINITE
            * @see Direction
            * @see EndBehavior
            */
            CAnimator(int duration, ITimingSource* timer, ITimingTarget* target=0, double repeatCount=1.0, 
                RepeatBehavior repeatBehavior=irr::timing::REVERSE);

        public:

            void tick();

            void validateRepeatCount(double repeatCount);

            double intRound(double r) {
                return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
            }



            /**
            * Returns the initial direction for the animation.
            * @return direction that the initial animation cycle will be moving
            */
            Direction getStartDirection();

            /**
            * Sets the startDirection for the initial animation cycle.  The default 
            * startDirection is {@link Direction#FORWARD FORWARD}.
            * 
            * @param startDirection initial animation cycle direction
            * @see #isRunning()
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            */
            void setStartDirection(Direction startDirection);

            /**
            * Returns the interpolator for the animation.
            * @return interpolator that the initial animation cycle uses
            */
            IInterpolator* getInterpolator() ;

            /**
            * Sets the interpolator for the animation cycle.  The default 
            * interpolator is {@link LinearInterpolator}.
            * @param interpolator the interpolation to use each animation cycle
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            */
            void setInterpolator(IInterpolator* interpolator);

            /**
            * Sets the fraction of the timing cycle that will be spent accelerating
            * at the beginning. The default acceleration value is 0 (no acceleration).
            * @param acceleration value from 0 to 1
            * @throws IllegalArgumentException acceleration value must be between 0 and
            * 1, inclusive. 
            * @throws IllegalArgumentException acceleration cannot be greater than
            * (1 - deceleration)
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            * @see #setDeceleration(float)
            */
            void setAcceleration(float acceleration);

            /**
            * Sets the fraction of the timing cycle that will be spent decelerating
            * at the end. The default deceleration value is 0 (no deceleration).
            * @param deceleration value from 0 to 1
            * @throws IllegalArgumentException deceleration value must be between 0 and
            * 1, inclusive. 
            * @throws IllegalArgumentException deceleration cannot be greater than
            * (1 - acceleration)
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            * @see #setAcceleration(float)
            */
            void setDeceleration(float deceleration);

            /**
            * Returns the current value of acceleration property
            * @return acceleration value
            */
            float getAcceleration();

            /**
            * Returns the current value of deceleration property
            * @return deceleration value
            */
            float getDeceleration();

            /**
            * Adds a TimingTarget to the list of targets that get notified of each
            * timingEvent.  This can be done at any time before, during, or after the
            * animation has started or completed; the new target will begin
            * having its TimingTarget methods called as soon as it is added.
            * If <code>target</code> is already on the list of targets in this Animator, it
            * is not added again (there will be only one instance of any given
            * target in any Animator's list of targets).
            * @param target TimingTarget to be added to the list of targets that
            * get notified by this Animator of all timing events. Target cannot
            * be 0.
            */
            void addTarget(ITimingTarget* target);

            /**
            * Removes the specified TimingTarget from the list of targets that get
            * notified of each timingEvent.  This can be done at any time before,
            * during, or after the animation has started or completed; the 
            * target will cease having its TimingTarget methods called as soon
            * as it is removed.
            * @param target TimingTarget to be removed from the list of targets that
            * get notified by this Animator of all timing events.
            */
            void removeTarget(ITimingTarget* target);

            /**
            * Returns the current resolution of the animation. This helps 
            * determine the maximum frame rate at which the animation will run.
            * @return the resolution, in milliseconds, of the timer
            */
            int getResolution();

            /**
            * Sets the resolution of the animation
            * @param resolution the amount of time between timing events of the
            * animation, in milliseconds.  Note that the actual resolution may vary,
            * according to the resolution of the timer used by the framework as well
            * as system load and configuration; this value should be seen more as a
            * minimum resolution than a guaranteed resolution.
            * @throws IllegalArgumentException resolution must be >= 0
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            */
            void setResolution(int resolution);

            /**
            * Returns the duration of the animation.
            * @return the length of the animation, in milliseconds. A
            * return value of -1 indicates an {@link #INFINITE} duration.
            */
            int getDuration();

            /**
            * Sets the duration for the animation
            * @param duration the length of the animation, in milliseconds.  This
            * value can also be {@link #INFINITE}, meaning the animation will run
            * until manually stopped.
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            * @see #stop()
            */
            void setDuration(int duration);

            /**
            * Returns the number of times the animation cycle will repeat.
            * @return the number of times the animation cycle will repeat.
            */
            double getRepeatCount();

            /**
            * Sets the number of times the animation cycle will repeat. The default
            * value is 1.
            * @param repeatCount Number of times the animation cycle will repeat.
            * This value may be >= 1 or {@link #INFINITE} for animations that repeat 
            * indefinitely.  The value may be fractional if the animation should
            * stop at some fractional point.
            * @throws IllegalArgumentException if repeatCount is not >=1 or 
            * INFINITE.
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            */
            void setRepeatCount(double repeatCount);

            /**
            * Returns the amount of delay prior to starting the first animation
            * cycle after the call to {@link #start}.
            * @return the duration, in milliseconds, between the call
            * to start the animation and the first animation cycle actually 
            * starting.
            * @see #start
            */
            int getStartDelay();

            /**
            * Sets the duration of the initial delay between calling {@link #start}
            * and the start of the first animation cycle. The default value is 0 (no 
            * delay).
            * @param startDelay the duration, in milliseconds, between the call
            * to start the animation and the first animation cycle actually 
            * starting. This value must be >= 0.
            * @throws IllegalArgumentException if startDelay is < 0
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            */
            void setStartDelay(int startDelay);

            /**
            * Returns the {@link RepeatBehavior} of the animation. The default
            * behavior is REVERSE, meaning that the animation will reverse direction
            * at the end of each cycle.
            * @return whether the animation will repeat in the same
            * direction or will reverse direction each time.
            */
            RepeatBehavior getRepeatBehavior();

            /**
            * Sets the {@link RepeatBehavior} of the animation.
            * @param repeatBehavior the behavior for each successive cycle in the
            * animation.  A 0 behavior is equivalent to specifying the default:
            * REVERSE.  The default behaviors is HOLD.
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            */
            void setRepeatBehavior(RepeatBehavior repeatBehavior);

            /**
            * Returns the {@link EndBehavior} of the animation, either HOLD to 
            * retain the final value or RESET to take on the initial value. The 
            * default behavior is HOLD.
            * @return the behavior at the end of the animation
            */
            EndBehavior getEndBehavior();

            /**
            * Sets the behavior at the end of the animation.
            * @param endBehavior the behavior at the end of the animation, either
            * HOLD or RESET.  A 0 value is equivalent to the default value of
            * HOLD.
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning
            */
            void setEndBehavior(EndBehavior endBehavior);

            /**
            * Returns the fraction that the first cycle will start at.
            * @return fraction between 0 and 1 at which the first cycle will start.
            */
            float getStartFraction();

            /**
            * Sets the initial fraction at which the first animation cycle will
            * begin.  The default value is 0.
            * @param startFraction
            * @see #isRunning()
            * @throws IllegalArgumentException if startFraction is less than 0
            * or greater than 1
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            */
            void setStartFraction(float startFraction);

            /**
            * Starts the animation
            * @throws IllegalStateException if animation is already running; this
            * command may only be run prior to starting the animation or 
            * after the animation has ended
            */
            void start();

            /**
            * Returns whether this Animator object is currently running
            */
            bool isRunning();

            /**
            * This method is optional; animations will always stop on their own
            * if Animator is provided with appropriate values for
            * duration and repeatCount in the constructor.  But if the application 
            * wants to stop the timer mid-stream, this is the method to call.
            * This call will result in calls to the <code>end()</code> method
            * of all TimingTargets of this Animator.
            * @see #cancel()
            */
            void stop();

            /**
            * This method is like the {@link #stop} method, only this one will
            * not result in a calls to the <code>end()</code> method in all 
            * TimingTargets of this Animation; it simply cancels the Animator
            * immediately.
            * @see #stop()
            */
            void cancel();

            /**
            * This method pauses a running animation.  No further events are sent to
            * TimingTargets. A paused animation may be d again by calling the
            * {@link #resume} method.  Pausing a non-running animation has no effect.
            * 
            * @see #resume()
            * @see #isRunning()
            */
            void pause();

            /**
            * This method resumes a paused animation.  Resuming an animation that
            * is not paused has no effect.
            *
            * @see #pause()
            */
            void resume();

        protected:
            //
            // TimingTarget implementations
            // Note that Animator does not actually implement TimingTarget directly;
            // it does not want to make public methods of these events.  But it uses
            // the same methods internally to propagate the events to all of the
            // Animator's targets.
            //

            /**
            * Internal timingEvent method that sends out the event to all targets
            */
            void timingEvent(float fraction);

            /**
            * Internal begin event that sends out the event to all targets
            */
            void begin();

            /**
            * Internal end event that sends out the event to all targets
            */
            void end();

            /**
            * Internal repeat event that sends out the event to all targets
            */
            void repeat();

            /**
            * This method calculates a new fraction value based on the
            * acceleration and deceleration settings of Animator.  It then
            * passes this value through the interpolator (by default, 
            * a LinearInterpolator) before returning it to the caller (who
            * will then call the timingEvent() methods in the TimingTargets
            * with this fraction).
            */
            float timingEventPreprocessor(float fraction);

            /**
            * Returns the total elapsed time for the current animation.
            * @param currentTime value of current time to use in calculating
            * elapsed time.
            * @return the total time elapsed between the time
            * the Animator started and the supplied currentTime.
            */
            long getTotalElapsedTime(long currentTime);

            /**
            * Returns the total elapsed time for the current animation.  Calculates
            * current time.
            * @return the total time elapsed between the time
            * the Animator started and the current time.
            */
            long getTotalElapsedTime();

            /**
            * Returns the elapsed time for the current animation cycle.
            * @param currentTime value of current time to use in calculating
            * elapsed time.
            * @return the time elapsed between the time
            * this cycle started and the supplied currentTime.
            */
            long getCycleElapsedTime(long currentTime);

            /**
            * Returns the elapsed time for the current animation cycle. Calculates
            * current time.
            * @return the time elapsed between the time
            * this cycle started and the current time.
            */
            long getCycleElapsedTime();

            /**
            * This method calculates and returns the fraction elapsed of the current
            * cycle based on the current time
            * @return fraction elapsed of the current animation cycle
            */
            float getTimingFraction();

            /**
            * Sets a new TimingSource that will supply the timing 
            * events to this Animator. Animator uses an internal
            * TimingSource by default and most developers will probably not
            * need to change this default behavior. But for those wishing to
            * supply their own timer, this method can be called to
            * tell Animator to use a different TimingSource instead. Setting a
            * new TimingSource implicitly removes this Animator as a listener
            * to any previously-set TimingSource object.
            * 
            * @param timer the object that will provide the
            * timing events to Animator. A value of <code>0</code> is
            * equivalent to telling Animator to use its default internal
            * TimingSource object.
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended.
            */
            void setTimer(ITimingSource* timer);

            /*
            * null event handler.
            */
            void timingSourceEvent(ITimingSource* timingSource);
        };
    }
}
#endif
