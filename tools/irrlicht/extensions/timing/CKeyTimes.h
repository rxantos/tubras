//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __C_KEY_TIMES_H_INCLUDED__
#define __C_KEY_TIMES_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        /**
        * Stores a list of times from 0 to 1 (the elapsed fraction of an animation
        * cycle) that are used in calculating interpolated
        * values for PropertySetter given a matching set of KeyValues and
        * Interpolators for those time intervals.  In the simplest case, a
        * KeyFrame will consist of just two times in KeyTimes: 0 and 1.
        */
        class CKeyTimes : public virtual IReferenceCounted
        {
        private:
            core::array<f32> times;

        public:
            CKeyTimes() {}
            /** 
            * Creates a new instance of KeyTimes.  Times should be in increasing
            * order and should all be in the range [0,1], with the first value
            * being zero and the last being 1
            * @throws IllegalArgumentException Time values must be ordered in
            * increasing value, the first value must be 0 and the last value
            * must be 1
            */
            CKeyTimes(core::array<f32>& times) {
                if (times[0] != 0) {
                    //throw new IllegalArgumentException("First time value must" +
                    //    " be zero");
                }
                if (times[times.size() - 1] != 1.0f) {
                    //throw new IllegalArgumentException("Last time value must" +
                    //    " be one");
                }
                float prevTime = 0;
                for (u32 i=0; i<times.size(); i++) {
                    float time = times[i];
                    if (time < prevTime) {
                        //throw new IllegalArgumentException("Time values must be" +
                        //    " in increasing order");
                    }
                    this->times.push_back(time);
                    prevTime = time;
                }
            }

            core::array<float> getTimes() {
                return times;
            }

            int getSize() {
                return times.size();
            }

            /**
            * Returns time interval that contains this time fraction
            */
            int getInterval(f32 fraction) {
                int prevIndex = 0;
                for (u32 i = 1; i < times.size(); ++i) {
                    float time = times[i];
                    if (time >= fraction) { 
                        // inclusive of start time at next interval.  So fraction==1
                        // will return the final interval (times.size() - 1)
                        return prevIndex;
                    }
                    prevIndex = i;
                }
                return prevIndex;
            }

            f32 getTime(int index) {
                return times[index];
            }
        };
    }
}
#endif
