//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#ifndef _TVECTOR3_H_
#define _TVECTOR3_H_

namespace Tubras
{
    class TVector3 : public Ogre::Vector3
    {
    public:
        inline TVector3() : Ogre::Vector3() {}

        inline TVector3( const TReal fX, const TReal fY, const TReal fZ ) : 
        Ogre::Vector3(fX, fY, fZ) {}

        inline explicit TVector3( const TReal afCoordinate[3] ) :
        Ogre::Vector3(afCoordinate) {}

        inline explicit TVector3( const int afCoordinate[3] ) :
        Ogre::Vector3(afCoordinate) {}

        inline explicit TVector3( TReal* const r ) :
        Ogre::Vector3(r) {}

        inline explicit TVector3( const TReal scaler ) :
        Ogre::Vector3(scaler) {}

        inline TVector3( const TVector3& rkVector ) : 
        Ogre::Vector3(rkVector) {}

        inline TVector3( const Ogre::Vector3& rkVector ) :
        Ogre::Vector3(rkVector) {}

        inline friend TVector3 operator * ( const TReal fScalar, const TVector3& rkVector )
        {
            return TVector3(
                fScalar * rkVector.x,
                fScalar * rkVector.y,
                fScalar * rkVector.z);
        }

        inline TVector3& operator *= ( const TReal fScalar )
        {
            x *= fScalar;
            y *= fScalar;
            z *= fScalar;
            return *this;
        }

        inline TVector3& operator *= ( const TVector3& rkVector )
        {
            x *= rkVector.x;
            y *= rkVector.y;
            z *= rkVector.z;

            return *this;
        }




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