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
    //
    //
    // btMatrix3x3 uses an array of 3 btVector3's to store homogeneous rotation info:
    //        btVector3      m_el[3];
    //
    // which means m_el[0] = xx   xy   xz
    //             m_el[1] = yx   yy   yz
    //             m_el[2] = zx   zy   zz
    // 
    //
    // bullet transform (btTransform) is row major 3x3 with the translation in
    // the 4th column:
    //        1  0  0  TX
    //        0  1  0  TY
    //        0  0  1  TZ
    // bullet uses a btMatrix3x3 (m_basis) for rotation and a btVector3 (m_origin)
    // for translation.
    //
    // TMatrix4 (irrlicht matrix4/CMatrix4) is row major 4x4 with translations in the 
    // 4th row:
    //        1  0  0  0
    //        0  1  0  0
    //        0  0  1  0
    //        TX TY TZ 1
    //

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

        static btVector3 IrrToBullet(const TVector3 vec)
        {
            return btVector3(vec.X, vec.Y, -vec.Z);
        };

        static btTransform IrrToBullet(const TMatrix4& mat4)
        {
            btTransform result;
            btScalar* pm = (btScalar*) mat4.pointer();

            result.getBasis().setValue(pm[0],pm[1],pm[2],
                                       pm[4],pm[5],pm[6],
                                       pm[8],pm[9],pm[10]);

            result.getOrigin().setValue(pm[12],pm[13],pm[14]);
            return result;
        }

        static TMatrix4 BulletToIrr(const btTransform& trans)
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

        static TVector3 BulletToIrr(const btVector3& vec)
        {
            return TVector3(vec.getX(),vec.getY(),-vec.getZ());
        }
    };
}

#endif


