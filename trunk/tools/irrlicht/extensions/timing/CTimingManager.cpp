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

                TheManager = new CTimingManager(new CTimingSource(device->getTimer()));
            }
            return TheManager;
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
                timer = InternalTimer;

            IAnimator* result = new CAnimator(duration, timer, target, repeatCount, repeatBehavior);
            Animators.push_back(result);
            return result;
        }



    }
}
