//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __C_TIMING_SOURCE_H_INCLUDED__
#define __C_TIMING_SOURCE_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        class CTimingSource : public ITimingSource
        {
        private:
            irr::ITimer* timer; // Irrlicht timer
            u32     startTime, resolution, delay;
            bool    running;

        public:
            CTimingSource(ITimer* timer) : timer(timer),
                startTime(0), 
                resolution(20),
                delay(0),
                running(false)
            {                
            }

            void start() {
                running = true;
                startTime = timer->getRealTime();
            }

            void stop() {
                running = false;
            }

            u32 getRealTime() {
                return timer->getRealTime();
            }

            void tick() {
                if(!running)
                    return;

                // may need to tick ITimer - for now, assuming already ticked by run()...
                u32 currentTime = timer->getRealTime();
                if((currentTime - startTime) >= resolution)
                {
                    startTime = currentTime;
                    timingEvent();
                }
            }

            void setResolution(int resolution) {
                this->resolution = resolution;
            }

            void setStartDelay(int delay) {
                this->delay = delay;
            }

        };
    }
}
#endif
