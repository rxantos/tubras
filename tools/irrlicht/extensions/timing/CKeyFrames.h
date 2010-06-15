//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on the "Timing Framework" by Chet Haase & others: 
//      https://timingframework.dev.java.net/
//-----------------------------------------------------------------------------
#ifndef __C_KEY_FRAMES_H_INCLUDED__
#define __C_KEY_FRAMES_H_INCLUDED__
#include "os.h"
namespace irr
{
    namespace timing
    {
        /**
        *
        * KeyFrames holds information about the times at which values are sampled
        * (KeyTimes) and the values at those times (KeyValues).  It also holds
        * information about how to interpolate between these values for
        * times that lie between the sampling points.
        */
        template <class T>
        class CKeyFrames : public virtual IReferenceCounted
        {
        private:
            CKeyValues<T>* keyValues;
            CKeyTimes* keyTimes;
            CKeyInterpolators* interpolators;

        public:
            /** 
            * Simplest variation; determine keyTimes based on even division of
            * 0-1 range based on number of keyValues.  This constructor
            * assumes LINEAR interpolation.
            * @param keyValues values that will be assumed at each time in keyTimes
            */
            CKeyFrames(CKeyValues<T>* keyValues) {
                init(keyValues, (CKeyTimes*)0, (const irr::core::array<IInterpolator*> &) 0);
            }

            /**
            * This variant takes both keyValues (values at each
            * point in time) and keyTimes (times at which values are sampled).
            * @param keyValues values that the animation will assume at each of the
            * corresponding times in keyTimes
            * @param keyTimes times at which the animation will assume the
            * corresponding values in keyValues
            * @throws IllegalArgumentException keyTimes and keySizes must have the
            * same number of elements since these structures are meant to have
            * corresponding entries; an exception is thrown otherwise.
            */
            CKeyFrames(CKeyValues<T>* keyValues, CKeyTimes* keyTimes) {
                init(keyValues, keyTimes, (const irr::core::array<IInterpolator*> &) 0);
            }

            /**
            * Utility constructor that assumes even division of times according to
            * size of keyValues and interpolation according to interpolators 
            * parameter.
            * @param keyValues values that the animation will assume at each of the
            * corresponding times in keyTimes
            * @param interpolators collection of Interpolators that control 
            * the calculation of values in each of the intervals defined by keyFrames.
            * If this value is null, a {@link LinearInterpolator} will be used
            * for all intervals.  If there is only one interpolator, that interpolator
            * will be used for all intervals.  Otherwise, there must be a number of
            * interpolators equal to the number of intervals (which is one less than
            * the number of keyTimes).
            * @throws IllegalArgumentException The number of interpolators must either
            * be zero (interpolators == null), one, or one less than the size of 
            * keyTimes.
            */
            CKeyFrames(CKeyValues<T>* keyValues, core::array<IInterpolator*>& interpolators) {
                init(keyValues, 0, interpolators);
            }

            /**
            * Full constructor: caller provides
            * an instance of all key* structures which will be used to calculate
            * between all times in the keyTimes list.  A null interpolator parameter
            * is equivalent to calling {@link KeyFrames#KeyFrames(KeyValues, KeyTimes)}.
            * @param keyValues values that the animation will assume at each of the
            * corresponding times in keyTimes
            * @param keyTimes times at which the animation will assume the
            * corresponding values in keyValues
            * @param interpolators collection of Interpolators that control 
            * the calculation of values in each of the intervals defined by keyFrames.
            * If this value is null, a {@link LinearInterpolator} will be used
            * for all intervals.  If there is only one interpolator, that interpolator
            * will be used for all intervals.  Otherwise, there must be a number of
            * interpolators equal to the number of intervals (which is one less than
            * the number of keyTimes).
            * @throws IllegalArgumentException keyTimes and keyValues must have the
            * same number of elements since these structures are meant to have
            * corresponding entries; an exception is thrown otherwise.
            * @throws IllegalArgumentException The number of interpolators must either
            * be zero (interpolators == null), one, or one less than the size of 
            * keyTimes.
            */
            CKeyFrames(CKeyValues<T>* keyValues, CKeyTimes* keyTimes,
                const core::array<IInterpolator*>& interpolators) {
                    init(keyValues, keyTimes, interpolators);
            }

            virtual ~CKeyFrames()
            {
                if(keyValues)
                    keyValues->drop();
                if(keyTimes)
                    keyTimes->drop();
                if(interpolators)
                    interpolators->drop();
            }

            /**
            * Utility function called by constructors to perform common
            * initialization chores
            */
            void init(CKeyValues<T>* keyValues, CKeyTimes* keyTimes,
                const core::array<IInterpolator*>& interpolators) {
                    int numFrames = keyValues->getSize();
                    // If keyTimes null, create our own
                    if (keyTimes == 0) {
                        core::array<f32> keyTimesArray;
                        float timeVal = 0.0f;
                        keyTimesArray.push_back(timeVal);
                        for (int i = 1; i < (numFrames - 1); ++i) {
                            timeVal += (1.0f / (numFrames - 1));
                            keyTimesArray.push_back(timeVal);
                        }
                        keyTimesArray.push_back(1.f);
                        this->keyTimes = new CKeyTimes(keyTimesArray);
                    } else {
                        this->keyTimes = keyTimes;
                        this->keyTimes->grab();
                    }
                    this->keyValues = keyValues;
                    this->keyValues->grab();
                    if (numFrames != this->keyTimes->getSize()) {
                        os::Printer::log("keyValues and keyTimes must be of equal size");
                        return;
                    }
                    if (interpolators != 0 && 
                        (interpolators.size() != (numFrames - 1)) &&
                        (interpolators.size() != 1)) {
			            os::Printer::log("interpolators must be " 
                                "either null (implying interpolation for all intervals), " 
                                "a single interpolator (which will be used for all " 
                                "intervals), or a number of interpolators equal to " 
                                "one less than the number of times.");
                        return;

                    }
                    this->interpolators = new CKeyInterpolators(numFrames - 1, interpolators);
            }

            /*
            Class getType() {
                return keyValues.getType();
            }
            */

            CKeyValues<T>* getKeyValues() {
                return keyValues;
            }

            CKeyTimes* getKeyTimes() {
                return keyTimes;
            }

            /**
            * Returns time interval that contains this time fraction
            */
            int getInterval(float fraction) {
                return keyTimes->getInterval(fraction);
            }

            /**
            * Returns a value for the given fraction elapsed of the animation
            * cycle.  Given the fraction, this method will determine what
            * interval the fraction lies within, how much of that interval has
            * elapsed, what the boundary values are (from KeyValues), what the
            * interpolated fraction is (from the Interpolator for the interval),
            * and what the final interpolated intermediate value is (using the
            * appropriate Evaluator).
            * This method will call into the Interpolator for the time interval
            * to get the interpolated method. To ensure that future operations
            * succeed, the value received from the interpolation will be clamped
            * to the interval [0,1].
            */
            void getValue(float fraction, T& out) {
                // First, figure out the real fraction to use, given the
                // interpolation type and keyTimes
                int interval = getInterval(fraction);
                float t0 = keyTimes->getTime(interval);
                float t1 = keyTimes->getTime(interval + 1);
                float t = (fraction - t0) / (t1 - t0);
                float interpolatedT = interpolators->interpolate(interval, t);
                // clamp to avoid problems with buggy Interpolators
                if (interpolatedT < 0.f) {
                    interpolatedT = 0.f;
                } else if (interpolatedT > 1.f) {
                    interpolatedT = 1.f;
                }
                keyValues->getValue(interval, (interval+1), out, interpolatedT);
            }
        };
    }
}
#endif
