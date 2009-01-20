//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TCOLOR_H_
#define _TCOLOR_H_

namespace Tubras
{
    class TColor : public SColor
    {
    public:
        TColor();
        TColor(SColor& c) 
        {
            setRed(c.getRed());
            setGreen(c.getGreen());
            setBlue(c.getBlue());
            setAlpha(c.getAlpha());
        }

        TColor(const SColor& c) 
        {
            setRed(c.getRed());
            setGreen(c.getGreen());
            setBlue(c.getBlue());
            setAlpha(c.getAlpha());
        }

        TColor& operator=(SColor& c)
        {
            setRed(c.getRed());
            setGreen(c.getGreen());
            setBlue(c.getBlue());
            setAlpha(c.getAlpha());
            return *this;
        }

        TColor& operator=(const SColor& c)
        {
            setRed(c.getRed());
            setGreen(c.getGreen());
            setBlue(c.getBlue());
            setAlpha(c.getAlpha());
            return *this;
        }

        inline TColor(u32 r, u32 g, u32 b) : SColor(255,r,g,b) {}
        inline TColor(u32 r, u32 g, u32 b, u32 a) : SColor(a,r,g,b) {}
        inline TColor(u32 c) : SColor(c) {}

        static const TColor White;
        static const TColor Black;
        static const TColor Gray;
        static const TColor Red;
        static const TColor Green;
        static const TColor Blue;

    };
} 
#endif
