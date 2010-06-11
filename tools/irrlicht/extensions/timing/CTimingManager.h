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
        };
    }
}
#endif
