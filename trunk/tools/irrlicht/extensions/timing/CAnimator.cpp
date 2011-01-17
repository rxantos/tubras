//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on the "Timing Framework" by Chet Haase & others: 
//      https://timingframework.dev.java.net/
//-----------------------------------------------------------------------------
#include "CAnimator.h"

namespace irr 
{
    namespace timing
    {

        CAnimator::CAnimator(int duration, core::stringc name, 
            double repeatCount, RepeatBehavior repeatBehavior,
            ITimingTarget* target, ITimingSource* timer) : timer(timer),
            name(name),
            currentCycle(0),
            intRepeatCount(true),
            timeToStop(false),
            hasBegun(false),
            pauseBeginTime(0),
            running(false),
            repeatCount(repeatCount),
            startDelay(0),
            repeatBehavior(repeatBehavior),
            endBehavior(irr::timing::HOLD),
            duration(duration),
            resolution(10),
            acceleration(0.f),
            deceleration(0.f),
            startFraction(0.f),
            startDirection(irr::timing::FORWARD),
            direction(irr::timing::FORWARD),
            interpolator(new CLinearInterpolator())
        {
            addTarget(target);


            this->timer->addEventListener(this);
            this->timer->setResolution(resolution);
            // Create internal Timer object
            //swingTimer = new SwingTimingSource();
            //timer = swingTimer;
            // First, check for bad parameters
            validateRepeatCount(repeatCount);
            this->repeatCount = repeatCount;

            // Set convenience variable: do we have an integer number of cycles?
            intRepeatCount = intRound(repeatCount) == repeatCount;
        }    

        void CAnimator::tick()
        {
            timer->tick();
        }

        /**
        * Used to specify unending duration or repeatCount
        * @see #setDuration
        * @see #setRepeatCount
        * */           
        void CAnimator::validateRepeatCount(double repeatCount) {
            if (repeatCount < 1 && repeatCount != INFINITE) {
                //throw new IllegalArgumentException("repeatCount (" + repeatCount + 
                //    ") cannot be <= 0");
            }
        }

        /**
        * Returns the initial direction for the animation.
        * @return direction that the initial animation cycle will be moving
        */
        Direction CAnimator::getStartDirection() {
            return startDirection;
        }

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
        void CAnimator::setStartDirection(Direction startDirection) {
            throwExceptionIfRunning();
            this->startDirection = startDirection;
        }

        /**
        * Returns the interpolator for the animation.
        * @return interpolator that the initial animation cycle uses
        */
        IInterpolator* CAnimator::getInterpolator() {
            return interpolator;
        }

        /**
        * Sets the interpolator for the animation cycle.  The default 
        * interpolator is {@link LinearInterpolator}.
        * @param interpolator the interpolation to use each animation cycle
        * @throws IllegalStateException if animation is already running; this
        * parameter may only be changed prior to starting the animation or 
        * after the animation has ended
        * @see #isRunning()
        */
        void CAnimator::setInterpolator(IInterpolator* interpolator) {
            this->interpolator = interpolator;
        }

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
        void CAnimator::setAcceleration(float acceleration) {
            throwExceptionIfRunning();
            if (acceleration < 0 || acceleration > 1.0f) {
                //throw new IllegalArgumentException("Acceleration value cannot lie" +
                //    " outside [0,1] range");
            }
            if (acceleration > (1.0f - deceleration)) {
                //throw new IllegalArgumentException("Acceleration value cannot be" +
                //    " greater than (1 - deceleration)");
            }
            this->acceleration = acceleration;
        }

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
        void CAnimator::setDeceleration(float deceleration) {
            throwExceptionIfRunning();
            if (deceleration < 0 || deceleration > 1.0f) {
                //throw new IllegalArgumentException("Deceleration value cannot lie" +
                //    " outside [0,1] range");
            }
            if (deceleration > (1.0f - acceleration)) {
                //throw new IllegalArgumentException("Deceleration value cannot be" +
                //    " greater than (1 - acceleration)");
            }
            this->deceleration = deceleration;
        }

        /**
        * Returns the current value of acceleration property
        * @return acceleration value
        */
        float CAnimator::getAcceleration() {
            return acceleration;
        }

        /**
        * Returns the current value of deceleration property
        * @return deceleration value
        */
        float CAnimator::getDeceleration() {
            return deceleration;
        }

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
        void CAnimator::addTarget(ITimingTarget* target) {
            if (target) {

                if (targets.binary_search(target) < 0) {
                    targets.push_back(target);
                }
            }
        }

        /**
        * Removes the specified TimingTarget from the list of targets that get
        * notified of each timingEvent.  This can be done at any time before,
        * during, or after the animation has started or completed; the 
        * target will cease having its TimingTarget methods called as soon
        * as it is removed.
        * @param target TimingTarget to be removed from the list of targets that
        * get notified by this Animator of all timing events.
        */
        void CAnimator::removeTarget(ITimingTarget* target) {
            s32 idx = targets.binary_search(target);
            if(idx >=0)
                targets.erase(idx);
        }

        /**
        * Returns the current resolution of the animation. This helps 
        * determine the maximum frame rate at which the animation will run.
        * @return the resolution, in milliseconds, of the timer
        */
        int CAnimator::getResolution() {
            return resolution;
        }

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
        void CAnimator::setResolution(int resolution) {
            if (resolution < 0) {
                //throw new IllegalArgumentException("resolution must be >= 0");
            }
            throwExceptionIfRunning();
            this->resolution = resolution;
            timer->setResolution(resolution);
        }

        /**
        * Returns the duration of the animation.
        * @return the length of the animation, in milliseconds. A
        * return value of -1 indicates an {@link #INFINITE} duration.
        */
        int CAnimator::getDuration() {
            return duration;
        }

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
        void CAnimator::setDuration(int duration) {
            throwExceptionIfRunning();
            this->duration = duration;
        }

        /**
        * Returns the number of times the animation cycle will repeat.
        * @return the number of times the animation cycle will repeat.
        */
        double CAnimator::getRepeatCount() {
            return repeatCount;
        }

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
        void CAnimator::setRepeatCount(double repeatCount) {
            validateRepeatCount(repeatCount);
            throwExceptionIfRunning();
            this->repeatCount = repeatCount;
        }

        /**
        * Returns the amount of delay prior to starting the first animation
        * cycle after the call to {@link #start}.
        * @return the duration, in milliseconds, between the call
        * to start the animation and the first animation cycle actually 
        * starting.
        * @see #start
        */
        int CAnimator::getStartDelay() {
            return startDelay;
        }

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
        void CAnimator::setStartDelay(int startDelay) {
            if (startDelay < 0) {
                //throw new IllegalArgumentException("startDelay (" + startDelay + 
                //    ") cannot be < 0");
            }
            throwExceptionIfRunning();
            this->startDelay = startDelay;
            timer->setStartDelay(startDelay);
        }

        /**
        * Returns the {@link RepeatBehavior} of the animation. The default
        * behavior is REVERSE, meaning that the animation will reverse direction
        * at the end of each cycle.
        * @return whether the animation will repeat in the same
        * direction or will reverse direction each time.
        */
        RepeatBehavior CAnimator::getRepeatBehavior() {
            return repeatBehavior;
        }

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
        void CAnimator::setRepeatBehavior(RepeatBehavior repeatBehavior) {
            throwExceptionIfRunning();
            this->repeatBehavior = repeatBehavior;
        }

        /**
        * Returns the {@link EndBehavior} of the animation, either HOLD to 
        * retain the final value or RESET to take on the initial value. The 
        * default behavior is HOLD.
        * @return the behavior at the end of the animation
        */
        EndBehavior CAnimator::getEndBehavior() {
            return endBehavior;
        }

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
        void CAnimator::setEndBehavior(EndBehavior endBehavior) {
            throwExceptionIfRunning();
            this->endBehavior = endBehavior;
        }

        /**
        * Returns the fraction that the first cycle will start at.
        * @return fraction between 0 and 1 at which the first cycle will start.
        */
        float CAnimator::getStartFraction() {
            return startFraction;
        }

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
        void CAnimator::setStartFraction(float startFraction) {
            if (startFraction < 0 || startFraction > 1.0f) {
                //throw new IllegalArgumentException("initialFraction must be " +
                //    "between 0 and 1");
            }
            throwExceptionIfRunning();
            this->startFraction = startFraction;
        }

        /**
        * Starts the animation
        * @throws IllegalStateException if animation is already running; this
        * command may only be run prior to starting the animation or 
        * after the animation has ended
        */
        void CAnimator::start() {
            throwExceptionIfRunning();
            hasBegun = false;
            running = true;
            // Initialize start time variables to current time
            //startTime = (System.nanoTime() / 1000000) + getStartDelay();
            startTime = timer->getRealTime() + getStartDelay();
            direction = startDirection;
            if (duration != INFINITE &&
                ((direction == FORWARD && startFraction > 0.0f) ||
                (direction == BACKWARD && startFraction < 1.0f))) 
            {
                    float offsetFraction = (direction == FORWARD) ? startFraction : (1.0f - startFraction);
                    long startDelta = (long)(duration * offsetFraction);
                    startTime -= startDelta;
            }
            currentStartTime = startTime;
            timer->start();
        }

        /**
        * Returns whether this Animator object is currently running
        */
        bool CAnimator::isRunning() {
            return running;
        }

        /**
        * This method is optional; animations will always stop on their own
        * if Animator is provided with appropriate values for
        * duration and repeatCount in the constructor.  But if the application 
        * wants to stop the timer mid-stream, this is the method to call.
        * This call will result in calls to the <code>end()</code> method
        * of all TimingTargets of this Animator.
        * @see #cancel()
        */
        void CAnimator::stop() {
            timer->stop();
            end();
            timeToStop = false;
            running = false;
            pauseBeginTime = 0;
        }

        /**
        * This method is like the {@link #stop} method, only this one will
        * not result in a calls to the <code>end()</code> method in all 
        * TimingTargets of this Animation; it simply cancels the Animator
        * immediately.
        * @see #stop()
        */
        void CAnimator::cancel() {
            timer->stop();
            timeToStop = false;
            running = false;
            pauseBeginTime = 0;
        }

        /**
        * This method pauses a running animation.  No further events are sent to
        * TimingTargets. A paused animation may be d again by calling the
        * {@link #resume} method.  Pausing a non-running animation has no effect.
        * 
        * @see #resume()
        * @see #isRunning()
        */
        void CAnimator::pause() {
            if (isRunning()) {
                pauseBeginTime = timer->getRealTime();
                running = false;
                timer->stop();
            }
        }

        /**
        * This method resumes a paused animation.  Resuming an animation that
        * is not paused has no effect.
        *
        * @see #pause()
        */
        void CAnimator::resume() {
            if (pauseBeginTime > 0) {
                long pauseDelta = timer->getRealTime() - pauseBeginTime;
                startTime += pauseDelta;
                currentStartTime += pauseDelta;
                timer->start();
                pauseBeginTime = 0;
                running = true;
            }
        }

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
        void CAnimator::timingEvent(float fraction) {
            for (u32 i = 0; i < targets.size(); ++i) {
                ITimingTarget* target = targets[i];
                target->timingEvent(fraction);
            }
            if (timeToStop) {
                stop();
            }
        }

        /**
        * Internal begin event that sends out the event to all targets
        */
        void CAnimator::begin() {
            printf("CAnimator::begin() %p\n", this);
            for (u32 i = 0; i < targets.size(); ++i) {
                ITimingTarget* target = targets[i];
                target->begin();
            }
        }

        /**
        * Internal end event that sends out the event to all targets
        */
        void CAnimator::end() {
            printf("CAnimator::end() %p\n", this);
            for (u32 i = 0; i < targets.size(); ++i) {
                ITimingTarget* target = targets[i];
                target->end();
            }
        }

        /**
        * Internal repeat event that sends out the event to all targets
        */
        void CAnimator::repeat() {
            printf("CAnimator::repeat() %p\n", this);
            for (u32 i = 0; i < targets.size(); ++i) {
                ITimingTarget* target = targets[i];
                target->repeat();
            }
        }

        /**
        * This method calculates a new fraction value based on the
        * acceleration and deceleration settings of Animator.  It then
        * passes this value through the interpolator (by default, 
        * a LinearInterpolator) before returning it to the caller (who
        * will then call the timingEvent() methods in the TimingTargets
        * with this fraction).
        */
        float CAnimator::timingEventPreprocessor(float fraction) {
            // First, take care of acceleration/deceleration factors
            if (acceleration != 0 || deceleration != 0.0f) {
                // See the SMIL 2.0 specification for details on this
                // calculation
                float runRate = 1.0f / (1.0f - acceleration/2.0f - 
                    deceleration/2.0f);
                if (fraction < acceleration) {
                    float averageRunRate = runRate * (fraction / acceleration) / 2;
                    fraction *= averageRunRate;
                } else if (fraction > (1.0f - deceleration)) {
                    // time spent in deceleration portion
                    float tdec = fraction - (1.0f - deceleration);
                    // proportion of tdec to total deceleration time
                    float pdec  = tdec / deceleration;
                    fraction = runRate * (1.0f - ( acceleration / 2) -
                        deceleration + tdec * (2 - pdec) / 2);
                } else {
                    fraction = runRate * (fraction - (acceleration / 2));
                }
                // clamp fraction to [0,1] since above calculations may
                // cause rounding errors
                if (fraction < 0) {
                    fraction = 0;
                } else if (fraction > 1.0f) {
                    fraction = 1.0f;
                }
            }
            // run the result through the current interpolator
            return interpolator->interpolate(fraction);
        }

        /**
        * Returns the total elapsed time for the current animation.
        * @param currentTime value of current time to use in calculating
        * elapsed time.
        * @return the total time elapsed between the time
        * the Animator started and the supplied currentTime.
        */
        long CAnimator::getTotalElapsedTime(long currentTime) {
            return (currentTime - startTime);
        }

        /**
        * Returns the total elapsed time for the current animation.  Calculates
        * current time.
        * @return the total time elapsed between the time
        * the Animator started and the current time.
        */
        long CAnimator::getTotalElapsedTime() {
            long currentTime = timer->getRealTime();
            return getTotalElapsedTime(currentTime);
        }

        /**
        * Returns the elapsed time for the current animation cycle.
        * @param currentTime value of current time to use in calculating
        * elapsed time.
        * @return the time elapsed between the time
        * this cycle started and the supplied currentTime.
        */
        long CAnimator::getCycleElapsedTime(long currentTime) {
            return (currentTime - currentStartTime);
        }

        /**
        * Returns the elapsed time for the current animation cycle. Calculates
        * current time.
        * @return the time elapsed between the time
        * this cycle started and the current time.
        */
        long CAnimator::getCycleElapsedTime() {
            long currentTime = timer->getRealTime();
            return getCycleElapsedTime(currentTime);
        }

        /**
        * This method calculates and returns the fraction elapsed of the current
        * cycle based on the current time
        * @return fraction elapsed of the current animation cycle
        */
        float CAnimator::getTimingFraction() {
            long currentTime = timer->getRealTime();
            long cycleElapsedTime = getCycleElapsedTime(currentTime);
            long totalElapsedTime = getTotalElapsedTime(currentTime);
            double currentCycle = (double)totalElapsedTime / duration;
            float fraction;

            if (!hasBegun) {
                // Call begin() first time after calling start()
                begin();
                hasBegun = true;
            }
            if ((duration != INFINITE) && (repeatCount != INFINITE) && 
                (currentCycle >= repeatCount)) 
            {
                // Envelope done: stop based on end behavior
                switch (endBehavior) 
                {
                case HOLD:
                    // Make sure we send a final end value
                    if (intRepeatCount) 
                    {
                        // If supposed to run integer number of cycles, hold
                        // on integer boundary
                        if (direction == BACKWARD) 
                        {
                            // If we were traveling backward, hold on 0
                            fraction = 0.0f;
                        } 
                        else 
                        {
                            fraction = 1.0f;
                        }
                    } 
                    else 
                    {
                        // hold on final value instead
                        fraction = core::min_(1.0f, 
                            ((float)cycleElapsedTime / duration));
                    }
                    break;
                case RESET:
                    // RESET requires setting the final value to the start value
                    fraction = 0.0f;
                    break;
                default:
                    fraction = 0.0f;
                    // should not reach here
                    break;
                }
                timeToStop = true;
            } 
            else if ((duration != INFINITE) && (cycleElapsedTime > duration)) 
            {
                // Cycle end: Time to stop or change the behavior of the timer
                long actualCycleTime = cycleElapsedTime % duration;
                fraction = (float)actualCycleTime / duration;
                // Set new start time for this cycle
                currentStartTime = currentTime - actualCycleTime;

                if (repeatBehavior == REVERSE) 
                {
                    bool oddCycles =  ((int)(cycleElapsedTime / duration) % 2) > 0;
                    if (oddCycles) 
                    {
                        // reverse the direction
                        direction = (direction == FORWARD) ? BACKWARD : FORWARD;
                    }
                    if (direction == BACKWARD) 
                    {
                        fraction = 1.0f - fraction;
                    }
                }
                repeat();
            } 
            else 
            {
                // mid-stream: calculate fraction of animation between
                // start and end times and send fraction to target
                fraction = 0.0f;
                if (duration != INFINITE) {
                    // Only limited duration animations need a fraction
                    fraction = (float)cycleElapsedTime / duration;
                    if (direction == BACKWARD) {
                        // If this is a reversing cycle, want to know inverse
                        // fraction; how much from start to finish, not 
                        // finish to start
                        fraction = (1.0f - fraction);
                    }
                    // Clamp fraction in case timing mechanism caused out of 
                    // bounds value
                    fraction = core::clamp(fraction, 0.f, 1.f);
                }
            }
            return timingEventPreprocessor(fraction);
        }

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
        void CAnimator::setTimer(ITimingSource* timer) {
            //throwExceptionIfRunning();
            /*
            if (this->timer != swingTimer) {
            // Remove this Animator from any previously-set external timer
            this->timer.removeEventListener(timingSourceTarget);
            }
            */
            if (timer != 0) {
                this->timer = timer;
                timer->addEventListener(this);
            }
            // sync this new timer with existing timer properties
            this->timer->setResolution(resolution);
            this->timer->setStartDelay(startDelay);
        }

        void CAnimator::timingSourceEvent(ITimingSource* timingSource) {
            // Make sure that we are being called by the current timer
            // and that the animation is actually running
            if ((timer == timingSource) && running) {
                timingEvent(getTimingFraction());
            }
        }
    }
}