//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
