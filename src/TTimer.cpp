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
    //-----------------------------------------------------------------------
    //                             T T i m e r
    //-----------------------------------------------------------------------
    TTimer::TTimer(irr::ITimer* itimer)
    {
        m_timer = itimer;
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
    }

    //-----------------------------------------------------------------------
    //                       g e t M i l l i S e c o n d s
    //-----------------------------------------------------------------------
    unsigned long TTimer::getMilliSeconds()
    {
        return m_timer->getTime();
    }

    //-----------------------------------------------------------------------
    //                       g e t M i c r o S e c o n d s
    //-----------------------------------------------------------------------
    unsigned long TTimer::getMicroSeconds()
    {
        return m_timer->getTime();
    }
}

