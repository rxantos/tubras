//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TVECTOR3_H_
#define _TVECTOR3_H_

namespace Tubras
{
    class TVector3 : public vector3df
    {
    public:
        TVector3();
        TVector3(f32 nx, f32 ny, f32 nz) : vector3df(nx,ny,nz) {}
        TVector3(const vector3d<f32>& other) : vector3df(other) {}
        TVector3 toRadians();
        TVector3 toDegrees();

        // special points
        static const TVector3 ZERO;
        static const TVector3 UNIT_X;
        static const TVector3 UNIT_Y;
        static const TVector3 UNIT_Z;
        static const TVector3 NEGATIVE_UNIT_X;
        static const TVector3 NEGATIVE_UNIT_Y;
        static const TVector3 NEGATIVE_UNIT_Z;
        static const TVector3 UNIT_SCALE;
    };



} 
#endif
