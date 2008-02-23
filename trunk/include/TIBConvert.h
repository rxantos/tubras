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
        static btTransform IrrToBullet(TVector3 pos, TVector3 rot /*degrees*/)
        {
            rot.X *= -1.f;
            rot.Y *= -1.f;
            btQuaternion quat(DegreesToRadians(rot.Y),DegreesToRadians(rot.X),
                DegreesToRadians(rot.Z));

            return btTransform (quat,IrrToBullet(pos));
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


