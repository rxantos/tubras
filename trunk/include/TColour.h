//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TCOLOUR_H_
#define _TCOLOUR_H_

namespace Tubras
{
    class TColour : public SColor
    {
    public:
        TColour();
        TColour(SColor& c) 
        {
            setRed(c.getRed());
            setGreen(c.getGreen());
            setBlue(c.getBlue());
            setAlpha(c.getAlpha());
        }
        inline TColour(u32 r, u32 g, u32 b) : SColor(255,r,g,b) {}
        inline TColour(u32 r, u32 g, u32 b, u32 a) : SColor(a,r,g,b) {}
        inline TColour(u32 c) : SColor(c) {}

        static const TColour White;
        static const TColour Black;
        static const TColour Gray;
        static const TColour Red;
        static const TColour Green;
        static const TColour Blue;

    };
} 
#endif
