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
            TQuaternion iquat;
            TVector3 rrot = rot * TMath::DEGTORAD;
            iquat.set(rrot);

            btQuaternion bquat(iquat.X, iquat.Y, iquat.Z, iquat.W);
            btVector3 bpos(pos.X, pos.Y, pos.Z);

            result.setRotation(bquat);
            result.setOrigin(bpos);
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
                org.x(), org.y(), org.z(), 1
            };


            result.setM((const f32*)&mat);
        }

        //-----------------------------------------------------------------------
        //               B->I    btVector3 -> TVector3
        //-----------------------------------------------------------------------
        /*
        static void BulletToIrr(const btVector3& in, TVector3& result)
        {
            result.set(in.getX(),in.getY(),in.getZ());
        }
        */

        //-----------------------------------------------------------------------
        //               I->B    TVector3 -> btVector3
        //-----------------------------------------------------------------------
        /*
        static void IrrToBullet(const TVector3& in, btVector3& result)
        {
            result.setX(in.X);
            result.setY(in.Y);
            result.setZ(in.Z);
        }
        */

        //-----------------------------------------------------------------------
        //               I->B    btQuaternion -> btVector3
        //-----------------------------------------------------------------------
        static void quaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler) {
            btScalar W = TQuat.getW();
            btScalar X = TQuat.getX();
            btScalar Y = TQuat.getY();
            btScalar Z = TQuat.getZ();
            float WSquared = W * W;
            float XSquared = X * X;
            float YSquared = Y * Y;
            float ZSquared = Z * Z;

            TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
            TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
            TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
            TEuler *= core::RADTODEG;
        }

    };
}

#endif


