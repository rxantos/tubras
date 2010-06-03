//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __I_TIMING_SOURCE_H_INCLUDED__
#define __I_TIMING_SOURCE_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        class ITimingSource
        {

        public:
            /**
            * Starts the TimingSource
            */
            virtual void start() = 0;

            /**
            * Stops the TimingSource
            */
            virtual void stop() = 0;

            /**
            * Sets the delay between callback events. This 
            * will be called by Animator if its
            * {@link Animator#setResolution(int) setResolution(int)}
            * method is called. Note that the actual resolution may vary,
            * according to the resolution of the timer used by the framework as well
            * as system load and configuration; this value should be seen more as a
            * minimum resolution than a guaranteed resolution.
            * @param resolution delay, in milliseconds, between 
            * each timing event callback.
            * @throws IllegalArgumentException resolution must be >= 0
            * @see Animator#setResolution(int)
            */
            virtual void setResolution(int resolution) = 0;

            /**
            * Sets delay which should be observed by the 
            * TimingSource after a call to {@link #start()}. Some timers may not be
            * able to adhere to specific resolution requests
            * @param delay delay, in milliseconds, to pause before
            * starting timing events.
            * @throws IllegalArgumentException resolution must be >= 0
            * @see Animator#setStartDelay(int)
            */
            virtual void setStartDelay(int delay) = 0;

            /**
            * Adds an ITimingEventListener to the set of listeners that
            * receive timing events from this TimingSource.
            * @param listener the listener to be added.
            */
            void addEventListener(ITimingEventListener* listener) {
                if(Listeners.binary_search(listener) < 0)
                    Listeners.push_back(listener);
            }

            /**
            * Removes an ITimingEventListener from the set of listeners that
            * receive timing events from this TimingSource.
            * @param listener the listener to be removed.
            */
            void removeEventListener(ITimingEventListener* listener) {
                s32 idx = Listeners.binary_search(listener);
                if(idx >= 0)
                    Listeners.erase(idx);
            }

        protected:

            /**
            * Subclasses call this method to post timing events to this
            * object's {@link ITimingEventListener} objects.
            */
            void timingEvent() {
                
                for (u32 i=0; i< Listeners.size(); i++) {
                    Listeners[i]->timingSourceEvent(this);
                }                
            }

            core::array<ITimingEventListener *> Listeners;

        };
    }
}
#endif
