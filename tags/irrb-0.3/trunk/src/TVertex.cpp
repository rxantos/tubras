//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                             T V e r t e x
    //-----------------------------------------------------------------------
    TVertex::TVertex() : S3DVertex()
    {
    }

    //-----------------------------------------------------------------------
    //                             T V e r t e x
    //-----------------------------------------------------------------------
    TVertex::TVertex(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz, TColor c, f32 tu, f32 tv) :
    S3DVertex(x,y,z,nx,ny,nz,c,tu,tv)
    {
    }

    //-----------------------------------------------------------------------
    //                             T V e r t e x
    //-----------------------------------------------------------------------
    TVertex::TVertex(const TVector3& pos, const TVector3& normal,TColor color, const TVector2& tcoords) :
    S3DVertex(pos,normal,color,tcoords)
    {
    }
}

