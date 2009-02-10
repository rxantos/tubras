//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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
    // for my own sanity...
    //
    // Irrlicht -> Left Handed Coordinate System (+Z into the screen)
    //   Bullet -> Right Handed Coordinate System (+Z out of the screen)
    //
    // Row Major:
    // xx   xy   xz   0     <-- x-vector m[0], m[1], m[2]
    // yx   yy   yz   0     <-- y-vector m[4], m[5], m[6]
    // zx   zy   zz   0     <-- z-vector m[8], m[9], m[10]
    // tx   ty   tz   1     <-- translation-vector m[12], m[13], m[14]
    //
    // Col Major:
    // xx   yx   zx   tx    
    // xy   yy   zy   ty 
    // xz   yz   zz   tz
    //  0    0    0    1
    //
    // 1st col x-vector m[0], m[4], m[8]
    // 2nd col y-vector m[1], m[5], m[9]
    // 3rd col z-vector m[2], m[6], m[10]
    // 4th col translation-vector m[3], m[7], m[11]
    //
    // btMatrix3x3 uses an array of 3 btVector3's to store homogeneous rotation info:
    //        btVector3      m_el[3];
    //
    // which means m_el[0] = xx   xy   xz     // feels "Row" oriented
    //             m_el[1] = yx   yy   yz
    //             m_el[2] = zx   zy   zz
    // 
    // btMatrix3x3.getOpenGLSubMatrix(btScalar* M), expects M[12], and returns
    // a Column major matrix (X vector = M[0], M[4], M[9] (xx,xy,xz)
    //
    // btMatrix3x3.setFromOpenGLSubMatrix(btScalar* M) expects the same input 
    // as that supplied to getOpenGLSubMatrix.
    //
    // btTransform (bullet transform) uses a btMatrix3x3 (m_basis) for rotation 
    // and a btVector3 (m_origin) for translation.  It doesn't contain a method
    // for extracting the full transform into memory.  Instead, you have to
    // work with the individual m_basis and m_origin variables.
    //
    // TMatrix4 (irrlicht matrix4/CMatrix4) is row major 4x4 with translations in the 
    // 4th row:
    //        xx  xy  xz  0
    //        yx  yy  yz  0
    //        zx  zy  zz  0
    //        tx  ty  tz  1
    //

    class TIBConvert
    {
    public:
        //-----------------------------------------------------------------------
        //               I->B    (pos,rotation) -> btTransform
        //-----------------------------------------------------------------------
        static void IrrToBullet(const TVector3& pos, const TVector3& rot  /*degrees*/, btTransform& result)
        {
            btQuaternion quat(DegreesToRadians(rot.Y * -1.f),DegreesToRadians(rot.X * -1.f),
                DegreesToRadians(rot.Z));

            btVector3 bpos;
            IrrToBullet(pos,bpos);
            result.setRotation(quat);
            result.setOrigin(bpos);
        }

        //-----------------------------------------------------------------------
        //               I->B    TMatrix4 -> btTransform (NOT WORKING)
        //-----------------------------------------------------------------------
        static void IrrToBullet(const TMatrix4& mat4, btTransform& result)
        {
            TQuaternion q(mat4);
            btQuaternion bq(q.X,q.Y,-q.Z,q.W);            
            //bq.inverse();

            btMatrix3x3 mat3(bq);

            result.setBasis(mat3);

            TVector3 pos = mat4.getTranslation();
            result.getOrigin().setValue(pos.X,pos.Y,-pos.Z);

        }

        //-----------------------------------------------------------------------
        //               B->I    btTransform -> TMatrix4 (NOT WORKING)
        //-----------------------------------------------------------------------
        static void BulletToIrr(const btTransform& trans, TMatrix4& result)
        {
            btMatrix3x3 bas = trans.getBasis();
            btVector3 org = trans.getOrigin();
            btVector3 row0=bas.getRow(0),row1=bas.getRow(1),row2=bas.getRow(2);

            f32 mat[16]={
                row0.x(),row0.y(),row0.z(),0,
                row1.x(),row1.y(),row1.z(),0,
                row2.x(),row2.y(),row2.z(),0,
                org.x(), org.y(), -org.z(), 1
            };


            result.setM((const f32*)&mat);
        }

        //-----------------------------------------------------------------------
        //               B->I    btVector3 -> TVector3
        //-----------------------------------------------------------------------
        static void BulletToIrr(const btVector3& in, TVector3& result)
        {
            result.set(in.getX(),in.getY(),-in.getZ());
        }

        //-----------------------------------------------------------------------
        //               I->B    TVector3 -> btVector3
        //-----------------------------------------------------------------------
        static void IrrToBullet(const TVector3& in, btVector3& result)
        {
            result.setX(in.X);
            result.setY(in.Y);
            result.setZ(-in.Z);
        }

        //-----------------------------------------------------------------------
        //               I->B    btQuaternion -> btVector3
        //-----------------------------------------------------------------------
        // credit: Nomad, found in bullet forum
        static void quaternionToEulerZXY(const btQuaternion &quat,btVector3 &euler)
        {
            f32 w=quat.getW();   f32 x=quat.getX();   f32 y=quat.getY();   f32 z=quat.getZ();
            double sqw = w*w; double sqx = x*x; double sqy = y*y; double sqz = z*z;
            euler.setZ(btScalar((atan2(2.0 * (x*y + z*w),(sqx - sqy - sqz + sqw)))));
            euler.setX(btScalar((atan2(2.0 * (y*z + x*w),(-sqx - sqy + sqz + sqw)))));
            euler.setY(btScalar((asin(-2.0 * (x*z - y*w)))));
        }

        // Converts a quaternion to an euler angle
        static void quaternionToEulerXYZ(const btQuaternion &quat, btVector3 &euler) {
            btScalar W = quat.getW();
            btScalar X = quat.getX();
            btScalar Y = quat.getY();
            btScalar Z = quat.getZ();
            float WSquared = W * W;
            float XSquared = X * X;
            float YSquared = Y * Y;
            float ZSquared = Z * Z;

            euler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
            euler.setY(asinf(-2.0f * (X * Z - Y * W)));
            euler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
            euler *= TMath::RADTODEG;
        }

    };
}

#endif


