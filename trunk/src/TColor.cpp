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

namespace Tubras {

    const TColor TColor::White(255,255,255,255);
    const TColor TColor::Black(0,0,0,255);
    const TColor TColor::Gray(128,128,128,255);
    const TColor TColor::Red(255,0,0,255);
    const TColor TColor::Green(0,255,0,255);
    const TColor TColor::Blue(0,0,255,255);


    //-----------------------------------------------------------------------
    //                            T C o l o u r
    //-----------------------------------------------------------------------
    TColor::TColor() : SColor(255,255,255,255)
    {
    }
}

