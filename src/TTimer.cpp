//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include <algorithm>

namespace Tubras {
#ifndef mymin
    #define mymin(a,b) (a > b ? a : b)
#endif

    //-----------------------------------------------------------------------
    //                             T T i m e r
    //-----------------------------------------------------------------------
    TTimer::TTimer()
    {
#ifdef TUBRAS_PLATFORM_WIN32
        QueryPerformanceFrequency(&mClockFrequency);
#endif
        reset();
    }

    //-----------------------------------------------------------------------
    //                            ~ T T i m e r
    //-----------------------------------------------------------------------
    TTimer::~TTimer()
    {
    }

    //-----------------------------------------------------------------------
    //                               r e s e t
    //-----------------------------------------------------------------------
    void TTimer::reset()
    {
#ifdef TUBRAS_PLATFORM_WIN32
        QueryPerformanceCounter(&mStartTime);
        mStartTick = GetTickCount();
        mPrevElapsedTime = 0;
#else
        gettimeofday(&mStartTime, 0);
#endif
    }

    //-----------------------------------------------------------------------
    //                       g e t M i l l i S e c o n d s
    //-----------------------------------------------------------------------
    unsigned long TTimer::getMilliSeconds()
    {
#ifdef TUBRAS_PLATFORM_WIN32
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        LONGLONG elapsedTime = currentTime.QuadPart - 
            mStartTime.QuadPart;

        // Compute the number of millisecond ticks elapsed.
        unsigned long msecTicks = (unsigned long)(1000 * elapsedTime / 
            mClockFrequency.QuadPart);

        // Check for unexpected leaps in the Win32 performance counter.  
        // (This is caused by unexpected data across the PCI to ISA 
        // bridge, aka south bridge.  See Microsoft KB274323.)
        unsigned long elapsedTicks = GetTickCount() - mStartTick;
        signed long msecOff = (signed long)(msecTicks - elapsedTicks);
        if (msecOff < -100 || msecOff > 100)
        {
            // Adjust the starting time forwards.
            LONGLONG msecAdjustment = mymin(msecOff * 
                mClockFrequency.QuadPart / 1000, elapsedTime - 
                mPrevElapsedTime);
            mStartTime.QuadPart += msecAdjustment;
            elapsedTime -= msecAdjustment;

            // Recompute the number of millisecond ticks elapsed.
            msecTicks = (unsigned long)(1000 * elapsedTime / 
                mClockFrequency.QuadPart);
        }

        // Store the current elapsed time for adjustments next time.
        mPrevElapsedTime = elapsedTime;

        return msecTicks;
#else
        struct timeval currentTime;
        gettimeofday(&currentTime, 0);
        return (currentTime.tv_sec - mStartTime.tv_sec) * 1000 + 
            (currentTime.tv_usec - mStartTime.tv_usec) / 1000;
#endif 
    }

    //-----------------------------------------------------------------------
    //                       g e t M i c r o S e c o n d s
    //-----------------------------------------------------------------------
    unsigned long TTimer::getMicroSeconds()
    {
#ifdef TUBRAS_PLATFORM_WIN32
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        LONGLONG elapsedTime = currentTime.QuadPart - 
            mStartTime.QuadPart;

        // Compute the number of millisecond ticks elapsed.
        unsigned long msecTicks = (unsigned long)(1000 * elapsedTime / 
            mClockFrequency.QuadPart);

        // Check for unexpected leaps in the Win32 performance counter.  
        // (This is caused by unexpected data across the PCI to ISA 
        // bridge, aka south bridge.  See Microsoft KB274323.)
        unsigned long elapsedTicks = GetTickCount() - mStartTick;
        signed long msecOff = (signed long)(msecTicks - elapsedTicks);
        if (msecOff < -100 || msecOff > 100)
        {
            // Adjust the starting time forwards.
            LONGLONG msecAdjustment = mymin(msecOff * 
                mClockFrequency.QuadPart / 1000, elapsedTime - 
                mPrevElapsedTime);
            mStartTime.QuadPart += msecAdjustment;
            elapsedTime -= msecAdjustment;
        }

        // Store the current elapsed time for adjustments next time.
        mPrevElapsedTime = elapsedTime;

        // Convert to microseconds.
        unsigned long usecTicks = (unsigned long)(1000000 * elapsedTime / 
            mClockFrequency.QuadPart);

        return usecTicks;
#else
        struct timeval currentTime;
        gettimeofday(&currentTime, 0);
        return (currentTime.tv_sec - mStartTime.tv_sec) * 1000000 + 
            (currentTime.tv_usec - mStartTime.tv_usec);
#endif
    }
}

