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
namespace irr
{
    namespace timing
    {
        class CTimingManager
        {
        private:
            static CTimingManager*  TheManager;
        private:
            CTimingManager() {}
        public:
            static CTimingManager* getInstance() {
                if(TheManager == 0)
                    TheManager = new CTimingManager();
                return TheManager;
            }

        };
    }
}
#endif
