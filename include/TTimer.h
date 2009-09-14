//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
#ifdef TUBRAS_PLATFORM_WIN32
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

    };
} 
#endif
