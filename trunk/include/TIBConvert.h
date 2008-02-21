//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
            TMatrix4 m4 = mat4;
            TVector3 v3 = mat4.getRotationDegrees();
            v3.Z = -v3.Z;
            m4.setRotationDegrees(v3);

            const f32* data = m4.pointer();

            btMatrix3x3 mat3(data[0],data[1],data[2],
                             data[4],data[5],data[6],
                             data[8],data[9],data[10]);

            return btTransform (mat3,IrrToBullet(mat4.getTranslation()));
        };

        static btVector3   IrrToBullet(const TVector3 vec)
        {
            return btVector3(vec.X, vec.Y, -vec.Z);
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
            return TVector3(vec.getX(),vec.getY(),-vec.getZ());
        }
    };
}

#endif


