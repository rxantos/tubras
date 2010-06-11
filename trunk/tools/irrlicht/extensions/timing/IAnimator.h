//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on the "Timing Framework" by Chet Haase & others: 
//      https://timingframework.dev.java.net/
//-----------------------------------------------------------------------------
#ifndef __I_ANIMATOR_H_INCLUDED__
#define __I_ANIMATOR_H_INCLUDED__
namespace irr
{
    namespace timing
    {
#ifdef INFINITE
#undef INFINITE
#endif
        const int INFINITE=-1;

        /**
        * EndBehavior determines what happens at the end of the animation.
        * @see #setEndBehavior
        */
        enum EndBehavior {
            /** Timing sequence will maintain its final value at the end */
            HOLD,
            /** Timing sequence should reset to the initial value at the end */
            RESET,
        };

        /**
        * Direction is used to set the initial direction in which the
        * animation starts.
        * 
        * @see #setStartDirection
        */
        enum Direction {
            /**
            * cycle proceeds forward
            */
            FORWARD,
            /** cycle proceeds backward */
            BACKWARD,
        };

        /**
        * RepeatBehavior determines how each successive cycle will flow.
        * @see #setRepeatBehavior
        */
        enum RepeatBehavior {
            /** 
            * Each repeated cycle proceeds in the same direction as the 
            * previous one 
            */
            LOOP,
            /** 
            * Each cycle proceeds in the opposite direction as the 
            * previous one
            */
            REVERSE,
        };

        class IAnimator : virtual public IReferenceCounted
        {
        public:

            virtual void tick() = 0;

            /**
            * Returns the initial direction for the animation.
            * @return direction that the initial animation cycle will be moving
            */
            virtual Direction getStartDirection() = 0;

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
            virtual void setStartDirection(Direction startDirection) = 0;

            /**
            * Returns the interpolator for the animation.
            * @return interpolator that the initial animation cycle uses
            */
            virtual IInterpolator* getInterpolator()  = 0;

            /**
            * Sets the interpolator for the animation cycle.  The default 
            * interpolator is {@link LinearInterpolator}.
            * @param interpolator the interpolation to use each animation cycle
            * @throws IllegalStateException if animation is already running; this
            * parameter may only be changed prior to starting the animation or 
            * after the animation has ended
            * @see #isRunning()
            */
            virtual void setInterpolator(IInterpolator* interpolator) = 0;

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
            virtual void setAcceleration(float acceleration) = 0;

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
            virtual void setDeceleration(float deceleration) = 0;

            /**
            * Returns the current value of acceleration property
            * @return acceleration value
            */
            virtual float getAcceleration() = 0;

            /**
            * Returns the current value of deceleration property
            * @return deceleration value
            */
            virtual float getDeceleration() = 0;

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
            virtual void addTarget(ITimingTarget* target) = 0;

            /**
            * Removes the specified TimingTarget from the list of targets that get
            * notified of each timingEvent.  This can be done at any time before,
            * during, or after the animation has started or completed; the 
            * target will cease having its TimingTarget methods called as soon
            * as it is removed.
            * @param target TimingTarget to be removed from the list of targets that
            * get notified by this Animator of all timing events.
            */
            virtual void removeTarget(ITimingTarget* target) = 0;

            /**
            * Returns the current resolution of the animation. This helps 
            * determine the maximum frame rate at which the animation will run.
            * @return the resolution, in milliseconds, of the timer
            */
            virtual int getResolution() = 0;

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
            virtual void setResolution(int resolution) = 0;

            /**
            * Returns the duration of the animation.
            * @return the length of the animation, in milliseconds. A
            * return value of -1 indicates an {@link #INFINITE} duration.
            */
            virtual int getDuration() = 0;

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
            virtual void setDuration(int duration) = 0;

            /**
            * Returns the number of times the animation cycle will repeat.
            * @return the number of times the animation cycle will repeat.
            */
            virtual double getRepeatCount() = 0;

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
            virtual void setRepeatCount(double repeatCount) = 0;

            /**
            * Returns the amount of delay prior to starting the first animation
            * cycle after the call to {@link #start}.
            * @return the duration, in milliseconds, between the call
            * to start the animation and the first animation cycle actually 
            * starting.
            * @see #start
            */
            virtual int getStartDelay() = 0;

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
            virtual void setStartDelay(int startDelay) = 0;

            /**
            * Returns the {@link RepeatBehavior} of the animation. The default
            * behavior is REVERSE, meaning that the animation will reverse direction
            * at the end of each cycle.
            * @return whether the animation will repeat in the same
            * direction or will reverse direction each time.
            */
            virtual RepeatBehavior getRepeatBehavior() = 0;

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
            virtual void setRepeatBehavior(RepeatBehavior repeatBehavior) = 0;

            /**
            * Returns the {@link EndBehavior} of the animation, either HOLD to 
            * retain the final value or RESET to take on the initial value. The 
            * default behavior is HOLD.
            * @return the behavior at the end of the animation
            */
            virtual EndBehavior getEndBehavior() = 0;

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
            virtual void setEndBehavior(EndBehavior endBehavior) = 0;

            /**
            * Returns the fraction that the first cycle will start at.
            * @return fraction between 0 and 1 at which the first cycle will start.
            */
            virtual float getStartFraction() = 0;

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
            virtual void setStartFraction(float startFraction) = 0;

            /**
            * Starts the animation
            * @throws IllegalStateException if animation is already running; this
            * command may only be run prior to starting the animation or 
            * after the animation has ended
            */
            virtual void start() = 0;

            /**
            * Returns whether this Animator object is currently running
            */
            virtual bool isRunning() = 0;

            /**
            * This method is optional; animations will always stop on their own
            * if Animator is provided with appropriate values for
            * duration and repeatCount in the constructor.  But if the application 
            * wants to stop the timer mid-stream, this is the method to call.
            * This call will result in calls to the <code>end()</code> method
            * of all TimingTargets of this Animator.
            * @see #cancel()
            */
            virtual void stop() = 0;

            /**
            * This method is like the {@link #stop} method, only this one will
            * not result in a calls to the <code>end()</code> method in all 
            * TimingTargets of this Animation; it simply cancels the Animator
            * immediately.
            * @see #stop()
            */
            virtual void cancel() = 0;

            /**
            * This method pauses a running animation.  No further events are sent to
            * TimingTargets. A paused animation may be d again by calling the
            * {@link #resume} method.  Pausing a non-running animation has no effect.
            * 
            * @see #resume()
            * @see #isRunning()
            */
            virtual void pause() = 0;

            /**
            * This method resumes a paused animation.  Resuming an animation that
            * is not paused has no effect.
            *
            * @see #pause()
            */
            virtual void resume() = 0;

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
            virtual void timingEvent(float fraction) = 0;

            /**
            * Internal begin event that sends out the event to all targets
            */
            virtual void begin() = 0;

            /**
            * Internal end event that sends out the event to all targets
            */
            virtual void end() = 0;

            /**
            * Internal repeat event that sends out the event to all targets
            */
            virtual void repeat() = 0;

            /**
            * This method calculates a new fraction value based on the
            * acceleration and deceleration settings of Animator.  It then
            * passes this value through the interpolator (by default, 
            * a LinearInterpolator) before returning it to the caller (who
            * will then call the timingEvent() methods in the TimingTargets
            * with this fraction).
            */
            virtual float timingEventPreprocessor(float fraction) = 0;

            /**
            * Returns the total elapsed time for the current animation.
            * @param currentTime value of current time to use in calculating
            * elapsed time.
            * @return the total time elapsed between the time
            * the Animator started and the supplied currentTime.
            */
            virtual long getTotalElapsedTime(long currentTime) = 0;

            /**
            * Returns the total elapsed time for the current animation.  Calculates
            * current time.
            * @return the total time elapsed between the time
            * the Animator started and the current time.
            */
            virtual long getTotalElapsedTime() = 0;

            /**
            * Returns the elapsed time for the current animation cycle.
            * @param currentTime value of current time to use in calculating
            * elapsed time.
            * @return the time elapsed between the time
            * this cycle started and the supplied currentTime.
            */
            virtual long getCycleElapsedTime(long currentTime) = 0;

            /**
            * Returns the elapsed time for the current animation cycle. Calculates
            * current time.
            * @return the time elapsed between the time
            * this cycle started and the current time.
            */
            virtual long getCycleElapsedTime() = 0;

            /**
            * This method calculates and returns the fraction elapsed of the current
            * cycle based on the current time
            * @return fraction elapsed of the current animation cycle
            */
            virtual float getTimingFraction() = 0;

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
            virtual void setTimer(ITimingSource* timer) = 0;

            /*
            * null event handler.
            */
            virtual void timingSourceEvent(ITimingSource* timingSource) {}


        };
    }
}
#endif
