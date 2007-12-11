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

#ifndef __TIBCONVERT_H_
#define __TIBCONVERT_H_

namespace Tubras
{
    class TIBConvert
    {
    public:
        static btTransform IrrToBullet(const TMatrix4 mat4)
        {
            const f32* data = mat4.pointer();

            btMatrix3x3 mat3(data[0,0],data[0,1],data[0,2],
                             data[1,0],data[1,1],data[1,2],
                             data[2,0],data[2,1],data[2,2]);

            return btTransform (mat3,IrrToBullet(mat4.getTranslation()));
        };

        static btVector3   IrrToBullet(const TVector3 vec)
        {
            return btVector3(vec.X,vec.Y,vec.Z);
        };

        static TMatrix4    BulletToIrr(const btTransform& trans)
        {
            btMatrix3x3 bas = trans.getBasis();
            btVector3 org = trans.getOrigin();
            btVector3 row0=bas.getRow(0),row1=bas.getRow(1),row2=bas.getRow(2);
            
            f32 mat[16]={
                row0.x(),row0.y(),row0.z(),0,
                row1.x(),row1.y(),row1.z(),0,
                row2.x(),row2.y(),row2.z(),0,
                org.x(), org.y(), org.z(), 1};

            TMatrix4 mat4;
            mat4.setM((const f32*)&mat);


            return mat4;
        };

        static TVector3    BulletToIrr(const btVector3& vec)
        {
            return TVector3(vec.getX(),vec.getY(),vec.getZ());
        }
    };
}

#endif


