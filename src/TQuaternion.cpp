#include "tubras.h"


namespace Tubras
{
    //-----------------------------------------------------------------------
    //                        t o E u l e r D e g r e e s
    //-----------------------------------------------------------------------
    void TQuaternion::toEulerDegrees(vector3df& euler) const
    {
        toEuler(euler);
        euler.X = TMath::RadiansToDegrees(euler.X);
        euler.Y = TMath::RadiansToDegrees(euler.Y);
        euler.Z = TMath::RadiansToDegrees(euler.Z);
    }

}

