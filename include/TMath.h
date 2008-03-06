//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TMATH_H_
#define _TMATH_H_

namespace Tubras
{
    class TMath
    {
    public:
        TMath();

        static const f32 PI;
        static const f32 TWO_PI;
        static const f32 RECIPROCAL_PI;
        static const f32 HALF_PI;
        static const f32 DEGTORAD;
        static const f32 RADTODEG;
    };

    static inline f32 DegreesToRadians(f32 degrees) { return degrees * TMath::DEGTORAD; }
    static inline f32 RadiansToDegrees(f32 radians) { return radians * TMath::RADTODEG; }

}
#endif
