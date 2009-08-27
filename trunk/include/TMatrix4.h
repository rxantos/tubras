//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TMATRIX4_H_
#define _TMATRIX4_H_

namespace Tubras
{
    class TMatrix4 : public irr::core::matrix4
    {
    public:

        TMatrix4( eConstructor constructor = EM4CONST_IDENTITY ) : irr::core::matrix4(constructor) {}
        TMatrix4( const matrix4& other,eConstructor constructor = EM4CONST_COPY) : irr::core::matrix4(other,constructor) {}

        static void getRotationDegreesDivScale(const irr::core::matrix4& inmat, irr::core::vector3df& out) 
	{
        const irr::core::matrix4 &mat = inmat;
        const f32* M = mat.pointer();

        f32 SX = sqrtf(M[0] * M[0] + M[1] * M[1] + M[2] * M[2]);
        f32 SY = sqrtf(M[4] * M[4] + M[5] * M[5] + M[6] * M[6]);
        f32 SZ = sqrtf(M[8] * M[8] + M[9] * M[9] + M[10] * M[10]);

		f32 Y = -asin(mat(0,2) / SX);
		const f32 C = cos(Y);
		Y *= RADTODEG;

		f32 rotx, roty, X, Z;

		if (fabs(C)>ROUNDING_ERROR_f64)
		{
			const f32 invC = (f32)(1.0/C);
			rotx = mat(2,2) / SZ * invC;
			roty = mat(1,2) / SY * invC;
			X = atan2( roty, rotx ) * RADTODEG;
			rotx = mat(0,0) / SX * invC;
			roty = mat(0,1) / SX * invC;
			Z = atan2( roty, rotx ) * RADTODEG;
		}
		else
		{
			X = 0.0;
			rotx = mat(1,1) / SY;
			roty = -mat(1,0) / SY;
			Z = atan2( roty, rotx ) * RADTODEG;
		}

		// fix values that get below zero
		// before it would set (!) values to 360
		// that where above 360:
		if (X < 0.0) X += 360.0;
		if (Y < 0.0) Y += 360.0;
		if (Z < 0.0) Z += 360.0;

        out.set(X, Y, Z);
	}



    };
} 
#endif
