//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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

            btMatrix3x3 mat3(data[0],data[1],data[2],
                             data[4],data[5],data[6],
                             data[8],data[9],data[10]);

            return btTransform (mat3,IrrToBullet(mat4.getTranslation()));
        };

        static btVector3   IrrToBullet(const TVector3 vec)
        {
            return btVector3(vec.X,vec.Y,-vec.Z);
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


