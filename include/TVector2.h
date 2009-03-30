//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TVECTOR2_H_
#define _TVECTOR2_H_

namespace Tubras
{
    typedef vector2df TVector2;
    //typedef vector2df TVector2df;
    
    class TVector2df : public vector2df
    {
    public:
        TVector2df();
        TVector2df(f32 nx, f32 ny) : vector2df(nx,ny) {}
        TVector2df(const TVector2df& other) : vector2df(other) {}
        TVector2df(const vector2df& other) : vector2df(other) {}
        TVector2df* operator=(const irr::core::vector2df& other)
        {
            this->X = other.X;
            this->Y = other.Y;
            return this;
        }

        TVector2df* operator=(const TVector2df& other)
        {
            this->X = other.X;
            this->Y = other.Y;
            return this;
        }

    };
    
} 
#endif
