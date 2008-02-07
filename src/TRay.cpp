//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay() : line3df()
    {
        m_magnitude = 1.f;
        m_endPoint = start + (end * m_magnitude);
    }

    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay(const TVector3& origin, const TVector3& direction, const TReal magnitude)
        : line3df(origin, direction)
    {
        m_magnitude = magnitude;
        m_endPoint  = start + (end * magnitude);
    }

    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay(const line3df& oRay,const TReal magnitude)
        : line3df(oRay.start,oRay.end)
    {
        m_magnitude = magnitude;
        m_endPoint = start + (end * m_magnitude);
    }

    //-----------------------------------------------------------------------
    //                            ~ T R a y 
    //-----------------------------------------------------------------------
    TRay::~TRay()
    {
    }
}

