//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __C_LINEAR_INTERPOLATOR_H_INCLUDED__
#define __C_LINEAR_INTERPOLATOR_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        /**
        * This class implements the Interpolator interface by providing a
        * simple interpolate function that simply returns the value that
        * it was given. The net effect is that callers will end up calculating
        * values linearly during intervals.
        * <p>
        * Because there is no variation to this class, it is a singleton and
        * is referenced by using the {@link #getInstance} static method.
        */
        class CLinearInterpolator : public IInterpolator
        {
        public:

            /**
            * This method always returns the value it was given, which will cause
            * callers to calculate a linear interpolation between boundary values.
            * @param fraction a value between 0 and 1, representing the elapsed
            * fraction of a time interval (either an entire animation cycle or an 
            * interval between two KeyTimes, depending on where this Interpolator has
            * been set)
            * @return the same value passed in as <code>fraction</code>
            */
            float interpolate(float fraction) {
                return fraction;
            }

        };
    }
}
#endif
