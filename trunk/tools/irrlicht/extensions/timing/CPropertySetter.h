//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on the "Timing Framework" by Chet Haase & others: 
//      https://timingframework.dev.java.net/
//-----------------------------------------------------------------------------
#ifndef __C_PROPERTY_SETTER_H_INCLUDED__
#define __C_PROPERTY_SETTER_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        /**
        * This class enables automating animation of object properties.
        * The class is a TimingTarget, and should be used as a target of
        * timing events from an Animator.  These events will be used to 
        * change a specified property over time, according to how the
        * PropertySetter is constructed.
        * <p>
        * For example, here is an animation of the "background" property
        * of some object "obj" from blue to red over a period of one second:
        * <pre>
        *  PropertySetter ps = new PropertySetter(obj, "background", Color.BLUE, 
        *                                         Color.RED);
        *  Animator anim = new Animator(1000, ps);
        *  anim.start();
        * </pre>
        * Here is the same animation, created using one of the utility
        * factory methods that returns an animator:
        * <pre>
        *  Animator animator = PropertySetter.createAnimator(1000, obj, "background", 
        *                                                    Color.BLUE, Color.RED);
        *  anim.start();
        * </pre>
        * <p>
        * More complex animations can be created by passing in multiple values
        * for the property to take on, for example:
        * <pre>
        *  Animator animator = PropertySetter.createAnimator(1000, obj, "background", 
        *                                                    Color.BLUE, Color.RED, 
        *                                                    Color.GREEN);
        *  anim.start();
        * </pre>
        * It is also possible to define more involved and tightly-controlled
        * steps in the animation, including the times between the values and
        * how the values are interpolated by using the constructor that takes
        * a {@link KeyFrames} object.  KeyFrames defines the fractional times at which
        * an object takes on specific values, the values to assume at those times,
        * and the method of interpolation between those values.  For example,
        * here is the same animation as above, specified through KeyFrames, where the
        * RED color will be set 10% of the way through the animation (note that
        * we are not setting an Interpolator, so the timing intervals will use the
        * default LinearInterpolator):
        * <pre>
        *  KeyValues vals = KeyValues.create(Color.BLUE, Color.RED, Color.GREEN);
        *  KeyTimes times = new KeyTimes(0.0f, .1f, 1.0f);
        *  KeyFrames frames = new KeyFrames(vals, times);
        *  Animator animator = PropertySetter.createAnimator(1000, obj, "background", 
        *                                                    frames);
        *  anim.start();
        * </pre>
        *
        */
        template<class T>
        class CPropertySetter : public virtual IReferenceCounted, public ITimingTarget
        {
            friend class CTimingManager;
        private:
            T&          out;
            CKeyFrames<T>* keyFrames;

        protected:

            CPropertySetter(T& out, CKeyFrames<T>* keyFrames) : out(out),
                keyFrames(keyFrames)
            {
            }

        public:

            void setStartValue(T& value)
            {
            }

            void setValue(float fraction)
            {
                keyFrames->getValue(fraction, out);
            }

            virtual void timingEvent(float fraction) {}

            virtual void begin() {}

            virtual void end() {}

            virtual void repeat() {}

        };

    }
}
#endif
