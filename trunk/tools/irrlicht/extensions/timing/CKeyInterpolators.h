//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __C_KEY_INTERPOLATORS_H_INCLUDED__
#define __C_KEY_INTERPOLATORS_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        class CKeyInterpolators
        {
        private:
            core::array<IInterpolator*> interpolators;

        public:
            /**
            * Creates a new instance of CKeyInterpolators
            */
            CKeyInterpolators(u32 numIntervals, core::array<IInterpolator*>* interpolators) {
                if (interpolators == 0 || interpolators[0] == 0) {
                    for (u32 i = 0; i < numIntervals; ++i) {
                        this->interpolators.push_back(new CLinearInterpolator());
                    }
                } else if (interpolators->size() < numIntervals) {
                    for (u32 i = 0; i < numIntervals; ++i) {
                        this->interpolators.push_back((*interpolators)[0]);
                    }
                } else {
                    for (u32 i = 0; i < numIntervals; ++i) {
                        this->interpolators.push_back((*interpolators)[i]);
                    }
                }
            }

            float interpolate(int interval, float fraction) {
                return interpolators[interval]->interpolate(fraction);
            }

        };
    }
}
#endif
