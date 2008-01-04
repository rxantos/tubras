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

#ifndef __TOBCONVERT_H_
#define __TOBCONVERT_H_

namespace Tubras
{
    class TOBConvert
    {
    public:
        static btTransform OgreToBullet(const TMatrix4 mat4)
        {
            TMatrix3 mat3;
            mat4.extract3x3Matrix(mat3);
            return btTransform(OgreToBullet(mat3),OgreToBullet(mat4.getTrans()));
        };

        static btVector3   OgreToBullet(const TVector3 vec)
        {
            return btVector3(vec.x,vec.y,vec.z);
        };

        static btMatrix3x3 OgreToBullet(const TMatrix3 mat3)
        {
            return btMatrix3x3(mat3[0][0],mat3[0][1],mat3[0][2],
                mat3[1][0],mat3[1][1],mat3[1][2],
                mat3[2][0],mat3[2][1],mat3[2][2]);
        };

        static TMatrix4    BulletToOgre(const btTransform& trans)
        {
            btMatrix3x3 bmat3 = trans.getBasis();
            btVector3 vec3 = trans.getOrigin();
            return TMatrix4(bmat3[0][0],bmat3[0][1],bmat3[0][2],vec3.getX(),
                bmat3[1][0],bmat3[1][1],bmat3[1][2],vec3.getY(),
                bmat3[2][0],bmat3[2][1],bmat3[2][2],vec3.getZ(),
                0,0,0,1);
        };

        static TVector3    BulletToOgre(const btVector3& vec)
        {
            return TVector3(vec.getX(),vec.getY(),vec.getZ());
        }
        static TMatrix3    BulletToOgre(const btMatrix3x3& mat);
    };
}

#endif


