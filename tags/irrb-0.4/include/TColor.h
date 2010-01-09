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

		//! Subtracts two colors, result is clamped to 0..255 values
		/** \param other Color to add to this color
		\return Addition of the two colors, clamped to 0..255 values */
		TColor operator-(const SColor& other) const
		{
            u32 a = core::max_<u32>(other.getAlpha()-getAlpha(),0);
            u32 r = core::max_<u32>(other.getRed()-getRed(),0);
            u32 g = core::max_<u32>(other.getGreen()-getGreen(),0);
            u32 b = core::max_<u32>(other.getBlue()-getBlue(),0);

            return TColor(r, g, b, a);
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
        static const TColor Transparent;

    };
} 
#endif
