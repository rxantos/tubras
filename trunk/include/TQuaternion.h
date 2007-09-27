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

#ifndef _TQUATERNION_H_
#define _TQUATERNION_H_

namespace Tubras
{
    class TQuaternion : public Ogre::Quaternion
    {
    public:
        inline TQuaternion (
            TReal fW = 1.0,
            TReal fX = 0.0, TReal fY = 0.0, TReal fZ = 0.0) : Ogre::Quaternion(fW,fX,fY,fZ) {}

        inline TQuaternion (const TQuaternion& rkQ) : Ogre::Quaternion((const Ogre::Quaternion&) rkQ) {}

        /// Construct a quaternion from a rotation matrix
        inline TQuaternion(const TMatrix3& rot) : Ogre::Quaternion(rot) {}

        /// Construct a quaternion from an angle/axis
        inline TQuaternion(const TRadian& rfAngle, const TVector3& rkAxis) : Ogre::Quaternion(rfAngle,rkAxis) {}
        /// Construct a quaternion from 3 orthonormal local axes
        inline TQuaternion(const TVector3& xaxis, const TVector3& yaxis, const TVector3& zaxis) :
        Ogre::Quaternion(xaxis,yaxis,zaxis) {}

        /// Construct a quaternion from 3 orthonormal local axes
        inline TQuaternion(const TVector3* akAxis) : Ogre::Quaternion(akAxis) {}

		/// Construct a quaternion from 4 manual w/x/y/z values
        inline TQuaternion(TReal* valptr) : Ogre::Quaternion(valptr) {}

        inline TQuaternion(Ogre::Quaternion quat) : Ogre::Quaternion(quat.w,quat.x,quat.y,quat.z) {}       


        inline TVector3 getHpr()
        {
            TVector3    hpr;

            hpr.x = getYaw().valueDegrees();
            hpr.y = getPitch().valueDegrees();
            hpr.z = getRoll().valueDegrees();

            return hpr;
        }

        inline void setHpr(float heading, float pitch, float roll)
        {
            TQuaternion h,p,r,q;
            h.FromAngleAxis(TRadian(TDegree(heading)),TVector3::UNIT_Y);
            p.FromAngleAxis(TRadian(TDegree(pitch)),TVector3::UNIT_X);
            r.FromAngleAxis(TRadian(TDegree(roll)),TVector3::UNIT_Z);

            q = h * p * r;
            w = q.w;
            x = q.x;
            y = q.y;
            z = q.z;
        }
    };
}

#endif