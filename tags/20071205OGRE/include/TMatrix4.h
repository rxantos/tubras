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

#ifndef _TMATRIX4_H_
#define _TMATRIX4_H_

namespace Tubras
{
    class TMatrix4 : public Ogre::Matrix4
    {
    public:
        inline TMatrix4() : Ogre::Matrix4() {}

        inline TMatrix4(
            TReal m00, TReal m01, TReal m02, TReal m03,
            TReal m10, TReal m11, TReal m12, TReal m13,
            TReal m20, TReal m21, TReal m22, TReal m23,
            TReal m30, TReal m31, TReal m32, TReal m33 ) : Ogre::Matrix4(m00, m01, m02, m03,
            m10, m11, m12, m13, 
            m20, m21, m22, m23, 
            m30, m31, m32, m33) {}
            
        /** Creates a standard 4x4 transformation matrix with a zero translation part from a rotation/scaling 3x3 matrix.
         */

        inline TMatrix4(const TMatrix3& m3x3) : Ogre::Matrix4(m3x3) {}

        /** Creates a standard 4x4 transformation matrix with a zero translation part from a rotation/scaling Quaternion.
         */
        
        inline TMatrix4(const TQuaternion& rot) : Ogre::Matrix4((const Ogre::Quaternion&)rot) {}

        inline TQuaternion extractQuaternion() const
        {
          TMatrix3 m3x3;
          extract3x3Matrix(m3x3);
          return TQuaternion(m3x3);
        }

        inline void getPos(TVector3& v)
        {
            v.x = m[0][3];
            v.y = m[1][3];
            v.z = m[2][3];
        }

        inline TVector3 getHpr()
        {
            TVector3    hpr;
            TQuaternion quat=extractQuaternion();

            hpr.x = Ogre::Degree(quat.getYaw()).valueDegrees();
            hpr.y = Ogre::Degree(quat.getPitch()).valueDegrees();
            hpr.z = Ogre::Degree(quat.getRoll()).valueDegrees();

            return hpr;
        }


        
    };
}

#endif