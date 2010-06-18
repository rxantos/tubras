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
#include "CPropertySetter.h"

namespace irr
{
    namespace timing
    {
        class CTimingManager
        {
        private:
            static CTimingManager*  TheManager;
            IrrlichtDevice* Device;
            core::array<IAnimator*> Animators;
        private:
            CTimingManager(IrrlichtDevice* device) : Device(device) {}
        public:
            static CTimingManager* getInstance(IrrlichtDevice* device);

            void tick();

            IAnimator* createAnimator(int duration, core::stringc name="", double repeatCount=1.0, 
                RepeatBehavior repeatBehavior=irr::timing::REVERSE, 
                ITimingTarget* target=0, ITimingSource* timer=0);

            template <class T>
            IAnimator* createPropertyAnimator(int duration, T& out, CKeyFrames<T>* keyFrames, 
                core::stringc name="", double repeatCount=1.0, 
                RepeatBehavior repeatBehavior=irr::timing::REVERSE)
            {
                CPropertySetter<T>* ps = new CPropertySetter<T>(out, keyFrames);
                return createAnimator(duration, name, repeatCount, repeatBehavior, ps);
            }

            template <class T>
            IAnimator* createPropertyAnimator(int duration, T& out, CKeyValues<T>* values,
                core::stringc name="", double repeatCount=1.0, 
                RepeatBehavior repeatBehavior=irr::timing::REVERSE)
            {
                CKeyFrames<T>* keyFrames = new CKeyFrames<T>(values);
                return createPropertyAnimator(duration, out, keyFrames, name, repeatCount,
                    repeatBehavior);
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

        };

        template <>
        CKeyValues<u8>* CTimingManager::createKeyValues(core::array<u8>& params);

        template <>
        CKeyValues<s8>* CTimingManager::createKeyValues(core::array<s8>& params);

        template <>
        CKeyValues<u16>* CTimingManager::createKeyValues(core::array<u16>& params);

        template <>
        CKeyValues<s16>* CTimingManager::createKeyValues(core::array<s16>& params);

        template <>
        CKeyValues<u32>* CTimingManager::createKeyValues(core::array<u32>& params);

        template <>
        CKeyValues<s32>* CTimingManager::createKeyValues(core::array<s32>& params);

        template <>
        CKeyValues<f32>* CTimingManager::createKeyValues(core::array<f32>& params);

        template <>
        CKeyValues<f64>* CTimingManager::createKeyValues(core::array<f64>& params);

        template <>
        CKeyValues<SColor>* CTimingManager::createKeyValues(core::array<SColor>& params);

        template <>
        CKeyValues<core::vector2df>* CTimingManager::createKeyValues(core::array<core::vector2df>& params);

        template <>
        CKeyValues<core::vector2di>* CTimingManager::createKeyValues(core::array<core::vector2di>& params);

        template <>
        CKeyValues<core::vector3df>* CTimingManager::createKeyValues(core::array<core::vector3df>& params);

        template <>
        CKeyValues<core::vector3di>* CTimingManager::createKeyValues(core::array<core::vector3di>& params);

        template <>
        CKeyValues<core::line2di>* CTimingManager::createKeyValues(core::array<core::line2di>& params);

        template <>
        CKeyValues<core::line2df>* CTimingManager::createKeyValues(core::array<core::line2df>& params);

        template <>
        CKeyValues<core::rectf>* CTimingManager::createKeyValues(core::array<core::rectf>& params);

        template <>
        CKeyValues<core::recti>* CTimingManager::createKeyValues(core::array<core::recti>& params);

        template <>
        CKeyValues<core::quaternion>* CTimingManager::createKeyValues(core::array<core::quaternion>& params);

        template <>
        CKeyValues<core::matrix4>* CTimingManager::createKeyValues(core::array<core::matrix4>& params);

        template <>
        CKeyValues<core::dimension2df>* CTimingManager::createKeyValues(core::array<core::dimension2df>& params);

        template <>
        CKeyValues<core::dimension2di>* CTimingManager::createKeyValues(core::array<core::dimension2di>& params);

        template <>
        CKeyValues<core::dimension2du>* CTimingManager::createKeyValues(core::array<core::dimension2du>& params);
    }
}
#endif

