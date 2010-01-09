//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {

    const TColor TColor::White(255,255,255,255);
    const TColor TColor::Black(0,0,0,255);
    const TColor TColor::Gray(128,128,128,255);
    const TColor TColor::Red(255,0,0,255);
    const TColor TColor::Green(0,255,0,255);
    const TColor TColor::Blue(0,0,255,255);
    const TColor TColor::Transparent(0,0,0,0);


    //-----------------------------------------------------------------------
    //                            T C o l o u r
    //-----------------------------------------------------------------------
    TColor::TColor() : SColor(255,255,255,255)
    {
    }
}

