//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// based on Bullet's btClock class. See btQuickProf.h 
#ifndef _TTIMER_H_
#define _TTIMER_H_

namespace Tubras
{
    class TTimer : public IReferenceCounted
    {
        friend class TApplication;

    private:
#ifdef TUBRAS_PLATFORM_WINDOWS
        LARGE_INTEGER mClockFrequency;
        DWORD mStartTick;
        LONGLONG mPrevElapsedTime;
        LARGE_INTEGER mStartTime;
#else
        struct timeval mStartTime;
#endif

    public:
        TTimer();
        ~TTimer();

        void reset();

        /** Returns milliseconds since initialisation or last reset */
        unsigned long getMilliSeconds();

        /** Returns microseconds since initialisation or last reset */
        unsigned long getMicroSeconds();

        void getLocalTime(int* h, int* m, int* s, int* ms);

    };
} 
#endif
