//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on the "Timing Framework" by Chet Haase & others: 
//      https://timingframework.dev.java.net/
//-----------------------------------------------------------------------------
#ifndef __I_TIMING_EVENT_LISTENER_H_INCLUDED__
#define __I_TIMING_EVENT_LISTENER_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        class ITimingSource;

        class ITimingEventListener
        {
        public:
            /**
            * This method is called by the {@link ITimingSource} object while the
            * timer is running.
            *
            * @param timingSource the object that generates the timing events.
            */
            virtual void timingSourceEvent(ITimingSource* timingSource) = 0;

	        //bool operator==(const ITimingEventListener& other) const { return (this == &other); }

        };
    }
}
#endif
