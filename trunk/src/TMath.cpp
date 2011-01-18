//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    const f32 TMath::PI = f32( 4.0 * atan( 1.0 ) );
    const f32 TMath::TWO_PI = f32( 2.0 * PI );
    const f32 TMath::HALF_PI = f32( 0.5 * PI );
    const f32 TMath::DEGTORAD   = PI / 180.0f;
    const f32 TMath::RADTODEG   = 180.0f / PI;


    
    //-----------------------------------------------------------------------
    //                              T M a t h 
    //-----------------------------------------------------------------------
    TMath::TMath()
    {
    }

    void TMath::DegreesToRadians(TVector3& v)
    {
        v.X = v.X * TMath::DEGTORAD;
        v.Y = v.Y * TMath::DEGTORAD;
        v.Z = v.Z * TMath::DEGTORAD;
    }

    void TMath::RadiansToDegrees(TVector3& v)
    {
        v.X = v.X * TMath::RADTODEG;
        v.Y = v.Y * TMath::RADTODEG;
        v.Z = v.Z * TMath::RADTODEG;
    }

}


