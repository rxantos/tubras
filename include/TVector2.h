//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TVECTOR2_H_
#define _TVECTOR2_H_

namespace Tubras
{
    class TVector2 : public vector2df
    {
    public:
        TVector2();
        TVector2(f32 nx, f32 ny) : vector2df(nx,ny) {}
        TVector2(const TVector2& other) : vector2df(other) {}


    };
} 
#endif
