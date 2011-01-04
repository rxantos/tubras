//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TVECTOR3_H_
#define _TVECTOR3_H_

namespace Tubras
{
    //typedef vector3df TVector3;

    
    class TVector3 : public vector3df
    {
    public:
        TVector3(f32 nx=0.f, f32 ny=0.f, f32 nz=0.f) : vector3df(nx,ny,nz) {}
        TVector3(const vector3d<f32>& other) : vector3df(other) {}
        TVector3 toRadians();
        TVector3 toDegrees();
        ~TVector3() {}

        TVector3* operator=(const irr::core::vector3df& other) { X = other.X; Y = other.Y; Z = other.Z; return this; }

		TVector3 operator+(const TVector3 other) const { return TVector3(X + other.X, Y + other.Y, Z + other.Z); }
		TVector3& operator+=(const TVector3& other) { X+=other.X; Y+=other.Y; Z+=other.Z; return *this; }


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
