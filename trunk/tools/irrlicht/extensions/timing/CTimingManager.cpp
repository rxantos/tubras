//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "CTimingManager.h"
namespace irr
{
    namespace timing
    {
        CTimingManager* CTimingManager::TheManager = 0;


        CTimingManager* CTimingManager::getInstance(IrrlichtDevice* device) {
            if(TheManager == 0)
            {
                TheManager = new CTimingManager(device);
            }
            return TheManager;
        }

        template <>
        CKeyValues<u8>* CTimingManager::createKeyValues(core::array<u8>& params)
        {
            return new CKeyValues<u8>(params, new CEvaluatorU8());
        }

        template <>
        CKeyValues<s8>* CTimingManager::createKeyValues(core::array<s8>& params)
        {
            return new CKeyValues<s8>(params, new CEvaluatorS8());
        }

        template <>
        CKeyValues<u16>* CTimingManager::createKeyValues(core::array<u16>& params)
        {
            return new CKeyValues<u16>(params, new CEvaluatorU16());
        }

        template <>
        CKeyValues<s16>* CTimingManager::createKeyValues(core::array<s16>& params)
        {
            return new CKeyValues<s16>(params, new CEvaluatorS16());
        }

        template <>
        CKeyValues<u32>* CTimingManager::createKeyValues(core::array<u32>& params)
        {
            return new CKeyValues<u32>(params, new CEvaluatorU32());
        }

        template <>
        CKeyValues<s32>* CTimingManager::createKeyValues(core::array<s32>& params)
        {
            return new CKeyValues<s32>(params, new CEvaluatorS32());
        }

        template <>
        CKeyValues<f32>* CTimingManager::createKeyValues(core::array<f32>& params)
        {
            return new CKeyValues<f32>(params, new CEvaluatorF32());
        }

        template <>
        CKeyValues<f64>* CTimingManager::createKeyValues(core::array<f64>& params)
        {
            return new CKeyValues<f64>(params, new CEvaluatorF64());
        }

        template <>
        CKeyValues<SColor>* CTimingManager::createKeyValues(core::array<SColor>& params)
        {
            return new CKeyValues<SColor>(params, new CEvaluatorSColor());
        }

        template <>
        CKeyValues<core::vector2df>* CTimingManager::createKeyValues(core::array<core::vector2df>& params)
        {
            return new CKeyValues<core::vector2df>(params, new CEvaluatorVector2df());
        }

        template <>
        CKeyValues<core::vector2di>* CTimingManager::createKeyValues(core::array<core::vector2di>& params)
        {
            return new CKeyValues<core::vector2di>(params, new CEvaluatorVector2di());
        }

        template <>
        CKeyValues<core::vector3df>* CTimingManager::createKeyValues(core::array<core::vector3df>& params)
        {
            return new CKeyValues<core::vector3df>(params, new CEvaluatorVector3df());
        }

        template <>
        CKeyValues<core::vector3di>* CTimingManager::createKeyValues(core::array<core::vector3di>& params)
        {
            return new CKeyValues<core::vector3di>(params, new CEvaluatorVector3di());
        }


        template <>
        CKeyValues<core::line2di>* CTimingManager::createKeyValues(core::array<core::line2di>& params)
        {
            return new CKeyValues<core::line2di>(params, new CEvaluatorLine2di());
        }


        template <>
        CKeyValues<core::line2df>* CTimingManager::createKeyValues(core::array<core::line2df>& params)
        {
            return new CKeyValues<core::line2df>(params, new CEvaluatorLine2df());
        }


        template <>
        CKeyValues<core::rectf>* CTimingManager::createKeyValues(core::array<core::rectf>& params)
        {
            return new CKeyValues<core::rectf>(params, new CEvaluatorRectf());
        }

        template <>
        CKeyValues<core::recti>* CTimingManager::createKeyValues(core::array<core::recti>& params)
        {
            return new CKeyValues<core::recti>(params, new CEvaluatorRecti());
        }

        template <>
        CKeyValues<core::quaternion>* CTimingManager::createKeyValues(core::array<core::quaternion>& params)
        {
            return new CKeyValues<core::quaternion>(params, new CEvaluatorQuat());
        }

        template <>
        CKeyValues<core::matrix4>* CTimingManager::createKeyValues(core::array<core::matrix4>& params)
        {
            return new CKeyValues<core::matrix4>(params, new CEvaluatorMatrix4());
        }

        template <>
        CKeyValues<core::dimension2df>* CTimingManager::createKeyValues(core::array<core::dimension2df>& params)
        {
            return new CKeyValues<core::dimension2df>(params, new CEvaluatorDimension2df());
        }

        template <>
        CKeyValues<core::dimension2di>* CTimingManager::createKeyValues(core::array<core::dimension2di>& params)
        {
            return new CKeyValues<core::dimension2di>(params, new CEvaluatorDimension2di());
        }

        template <>
        CKeyValues<core::dimension2du>* CTimingManager::createKeyValues(core::array<core::dimension2du>& params)
        {
            return new CKeyValues<core::dimension2du>(params, new CEvaluatorDimension2du());
        }           

        void CTimingManager::tick()
        {
            for(u32 i=0; i<Animators.size(); i++)
            {
                Animators[i]->tick();
            }

        }

        IAnimator* CTimingManager::createAnimator(int duration, ITimingTarget* target, double repeatCount, 
            RepeatBehavior repeatBehavior, ITimingSource* timer)
        {
            if(!timer)
                timer = new CTimingSource(Device->getTimer());

            IAnimator* result = new CAnimator(duration, timer, target, repeatCount, repeatBehavior);
            Animators.push_back(result);
            return result;
        }

    }
}

