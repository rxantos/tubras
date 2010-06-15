//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on the "Timing Framework" by Chet Haase & others: 
//      https://timingframework.dev.java.net/
//-----------------------------------------------------------------------------
#ifndef __C_TIMING_MANAGER_H_INCLUDED__
#define __C_TIMING_MANAGER_H_INCLUDED__
#include "irrlicht.h"
using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

#include "ITimingEventListener.h"
#include "ITimingSource.h"
#include "IEvaluator.h"
#include "IInterpolator.h"
#include "ITimingTarget.h"
#include "IAnimator.h"
#include "CTimingSource.h"
#include "CKeyTimes.h"
#include "CKeyValues.h"
#include "CLinearInterpolator.h"
#include "CKeyInterpolators.h"
#include "CKeyFrames.h"
#include "CDiscreteInterpolator.h"  
#include "CSplineInterpolator.h"
#include "CAnimator.h"


namespace irr
{
    namespace timing
    {
        class CTimingManager
        {
        private:
            static CTimingManager*  TheManager;
            ITimingSource* InternalTimer;
            core::array<IAnimator*> Animators;
        private:
            CTimingManager(ITimingSource* timer) : InternalTimer(timer) {}
        public:
            static CTimingManager* getInstance(IrrlichtDevice* device);

            void tick();

            IAnimator* createAnimator(int duration, ITimingTarget* target=0, double repeatCount=1.0, 
                RepeatBehavior repeatBehavior=irr::timing::REVERSE, ITimingSource* timer=0);

            template <class T>
            IAnimator* createPropertyAnimator(int duration, T& out, CKeyFrames<T>* keyFrames)
            {
                CPropertySetter<T>* ps = new CPropertySetter<T>(out, keyFrames);
                return createAnimator(duration, ps);
            }

            template <class T>
            IAnimator* createPropertyAnimator(int duration, T& out, CKeyValues<T>* values)
            {
                CKeyFrames<T>* keyFrames = new CKeyFrames<T>(values);
                return createPropertyAnimator(duration, out, keyFrames);

            }

            template <class T>
            CKeyValues<T>* createKeyValues(core::array<T>& params, IEvaluator<T>* evaluator)
            {
                return new CKeyValues<T>(params, evaluator);
            }

            template <class T>
            CKeyValues<T>* createKeyValues(core::array<T>& params)
            {
                return 0;
            }

            template <>
            CKeyValues<u8>* createKeyValues(core::array<u8>& params)
            {
                return new CKeyValues<u8>(params, new CEvaluatorU8());
            }

            template <>
            CKeyValues<s8>* createKeyValues(core::array<s8>& params)
            {
                return new CKeyValues<s8>(params, new CEvaluatorS8());
            }

            template <>
            CKeyValues<u16>* createKeyValues(core::array<u16>& params)
            {
                return new CKeyValues<u16>(params, new CEvaluatorU16());
            }

            template <>
            CKeyValues<s16>* createKeyValues(core::array<s16>& params)
            {
                return new CKeyValues<s16>(params, new CEvaluatorS16());
            }

            template <>
            CKeyValues<u32>* createKeyValues(core::array<u32>& params)
            {
                return new CKeyValues<u32>(params, new CEvaluatorU32());
            }

            template <>
            CKeyValues<s32>* createKeyValues(core::array<s32>& params)
            {
                return new CKeyValues<s32>(params, new CEvaluatorS32());
            }

            template <>
            CKeyValues<f32>* createKeyValues(core::array<f32>& params)
            {
                return new CKeyValues<f32>(params, new CEvaluatorF32());
            }

            template <>
            CKeyValues<f64>* createKeyValues(core::array<f64>& params)
            {
                return new CKeyValues<f64>(params, new CEvaluatorF64());
            }

            template <>
            CKeyValues<SColor>* createKeyValues(core::array<SColor>& params)
            {
                return new CKeyValues<SColor>(params, new CEvaluatorSColor());
            }

            template <>
            CKeyValues<core::vector2df>* createKeyValues(core::array<core::vector2df>& params)
            {
                return new CKeyValues<core::vector2df>(params, new CEvaluatorVector2df());
            }

            template <>
            CKeyValues<core::vector2di>* createKeyValues(core::array<core::vector2di>& params)
            {
                return new CKeyValues<core::vector2di>(params, new CEvaluatorVector2di());
            }

            template <>
            CKeyValues<core::vector3df>* createKeyValues(core::array<core::vector3df>& params)
            {
                return new CKeyValues<core::vector3df>(params, new CEvaluatorVector3df());
            }

            template <>
            CKeyValues<core::vector3di>* createKeyValues(core::array<core::vector3di>& params)
            {
                return new CKeyValues<core::vector3di>(params, new CEvaluatorVector3di());
            }

            
            template <>
            CKeyValues<core::line2di>* createKeyValues(core::array<core::line2di>& params)
            {
                return new CKeyValues<core::line2di>(params, new CEvaluatorLine2di());
            }

           
            template <>
            CKeyValues<core::line2df>* createKeyValues(core::array<core::line2df>& params)
            {
                return new CKeyValues<core::line2df>(params, new CEvaluatorLine2df());
            }
            

            template <>
            CKeyValues<core::rectf>* createKeyValues(core::array<core::rectf>& params)
            {
                return new CKeyValues<core::rectf>(params, new CEvaluatorRectf());
            }

            template <>
            CKeyValues<core::recti>* createKeyValues(core::array<core::recti>& params)
            {
                return new CKeyValues<core::recti>(params, new CEvaluatorRecti());
            }

            template <>
            CKeyValues<core::quaternion>* createKeyValues(core::array<core::quaternion>& params)
            {
                return new CKeyValues<core::quaternion>(params, new CEvaluatorQuat());
            }

            template <>
            CKeyValues<core::matrix4>* createKeyValues(core::array<core::matrix4>& params)
            {
                return new CKeyValues<core::matrix4>(params, new CEvaluatorMatrix4());
            }

            template <>
            CKeyValues<core::dimension2df>* createKeyValues(core::array<core::dimension2df>& params)
            {
                return new CKeyValues<core::dimension2df>(params, new CEvaluatorDimension2df());
            }

            template <>
            CKeyValues<core::dimension2di>* createKeyValues(core::array<core::dimension2di>& params)
            {
                return new CKeyValues<core::dimension2di>(params, new CEvaluatorDimension2di());
            }

            template <>
            CKeyValues<core::dimension2du>* createKeyValues(core::array<core::dimension2du>& params)
            {
                return new CKeyValues<core::dimension2du>(params, new CEvaluatorDimension2du());
            }           

        };
    }
}
#endif
