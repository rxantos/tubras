//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TTIMER_H_
#define _TTIMER_H_

namespace Tubras
{
    class TTimer : public IReferenceCounted
    {
        friend class TApplication;
    private:
        irr::ITimer*        m_timer;

        TTimer(irr::ITimer* itimer);
        ~TTimer();

        /** Resets timer */
        void reset();

    public:

        /** Returns milliseconds since initialisation or last reset */
        unsigned long getMilliseconds();

    };
} 
#endif
