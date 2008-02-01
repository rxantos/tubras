//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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
    TVertex::TVertex(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz, TColour c, f32 tu, f32 tv) :
    S3DVertex(x,y,z,nx,ny,nz,c,tu,tv)
    {
    }

    //-----------------------------------------------------------------------
    //                             T V e r t e x
    //-----------------------------------------------------------------------
    TVertex::TVertex(const TVector3& pos, const TVector3& normal,TColour colour, const TVector2& tcoords) :
    S3DVertex(pos,normal,colour,tcoords)
    {
    }
}

