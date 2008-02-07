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

    const TColour TColour::White(255,255,255,255);
    const TColour TColour::Black(0,0,0,255);
    const TColour TColour::Gray(128,128,128,255);
    const TColour TColour::Red(255,0,0,255);
    const TColour TColour::Green(0,255,0,255);
    const TColour TColour::Blue(0,0,255,255);


    //-----------------------------------------------------------------------
    //                            T C o l o u r
    //-----------------------------------------------------------------------
    TColour::TColour() : SColor(255,255,255,255)
    {
    }
}

