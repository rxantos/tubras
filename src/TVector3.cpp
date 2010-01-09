//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {

    const TVector3 TVector3::ZERO( 0, 0, 0 );

    const TVector3 TVector3::UNIT_X( 1, 0, 0 );
    const TVector3 TVector3::UNIT_Y( 0, 1, 0 );
    const TVector3 TVector3::UNIT_Z( 0, 0, 1 );
    const TVector3 TVector3::NEGATIVE_UNIT_X( -1,  0,  0 );
    const TVector3 TVector3::NEGATIVE_UNIT_Y(  0, -1,  0 );
    const TVector3 TVector3::NEGATIVE_UNIT_Z(  0,  0, -1 );
    const TVector3 TVector3::UNIT_SCALE(1, 1, 1);

    //-----------------------------------------------------------------------
    //                           T V e c t o r 3
    //-----------------------------------------------------------------------
    TVector3 TVector3::toRadians() 
    {
        return TVector3(DegreesToRadians(X),
            DegreesToRadians(Y),DegreesToRadians(Z));
    }

    TVector3 TVector3::toDegrees() 
    {
        return TVector3(RadiansToDegrees(X),
            RadiansToDegrees(Y),RadiansToDegrees(Z));
    }
}

