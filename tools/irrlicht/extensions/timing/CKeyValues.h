//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __C_KEY_VALUES_H_INCLUDED__
#define __C_KEY_VALUES_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        /**
        * Stores a list of values that correspond to the times in a {@link
        * KeyTimes} object.  These structures are then used to create a
        * {@link KeyFrames} object, which is then used to create a
        * {@link PropertySetter} for the purposes of modifying an object's
        * property over time.
        * <p>
        * At each of the times in {@link KeyTimes}, the property will take
        * on the corresponding value in the KeyValues object.  Between these
        * times, the property will take on a value based on the interpolation
        * information stored in the KeyFrames object and the {@link 
        * Evaluator} for the type of the values in KeyValues.
        * <p>
        * This class has built-in support for various known types, as defined
        * in {@link Evaluator}.
        * <p>
        * For a simple example using KeyValues to create a KeyFrames and 
        * PropertySetter object, see the class header comments in 
        * {@link PropertySetter}.
        * 
        */

        template <class T>
        class CKeyValues : public virtual IReferenceCounted
        {
        private:
            core::array<T> values;
            IEvaluator<T>* evaluator;
            T startValue;
        public:
            /**
            * Constructs a KeyValues object from one or more values.  The
            * internal Evaluator is automatically determined by the
            * type of the parameters.
            * 
            * @param params the values to interpolate between.  If there is only
            * one parameter, this is assumed to be a "to" animation where the
            * first value is dynamically determined at runtime when the animation
            * is started.
            * @throws IllegalArgumentException if an {@link Evaluator} cannot be 
            * found that can interpolate between the value types supplied
            */
            CKeyValues(IEvaluator<T>* evaluator, core::array<T>& params) 
                : evaluator(0) {
                    if (params.size() == 0) {
                        //throw new IllegalArgumentException(
                        //    "params array must have at least one element");
                    }
                    if (params.size() == 1) {
                        // this is a "to" animation; set first element to null
                        values.push_back(0);
                    }
                    for(u32 i=0; i<params.size(); i++)
                    {
                        values.push_back(params[i]);
                    }
                    this->evaluator = evaluator;
                    this->evaluator->grab();
                    startValue = values[0];
            }

            virtual ~CKeyValues() {
                if(evaluator)
                    evaluator->drop();
            }

            /**
            * Returns the number of values stored in this object.
            *
            * @return the number of values stored in this object
            */
            int getSize() {
                return values.size();
            }

            /**
            * Called at start of animation; sets starting value in simple
            * "to" animations.
            */
            void setStartValue(T startValue) {
                if (isToAnimation()) {
                    this.startValue = startValue;
                }
            }

            /**
            * Utility method for determining whether this is a "to" animation
            * (true if the first value is null).
            */
            bool isToAnimation() {
                return (values[0] == 0);
            }

            /**
            * Returns value calculated from the value at the lower index, the
            * value at the upper index, the fraction elapsed between these 
            * endpoints, and the evaluator set up by this object at construction
            * time.
            */
            void getValue(int i0, int i1, T& out, float fraction) {
                T lowerValue = values[i0];
                if (lowerValue == 0) {
                    // "to" animation
                    lowerValue = startValue;
                }
                if (i0 == i1) {
                    // trivial case
                    out = lowerValue;
                } else {
                    T v0 = lowerValue;
                    T v1 = values[i1];
                    evaluator->evaluate(v0, v1, out, fraction);
                }
            }

        };
    }
}
#endif
