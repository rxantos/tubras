//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TQUATERNION_H_
#define _TQUATERNION_H_

namespace Tubras
{
    class TQuaternion : public quaternion
    {
    public:
        //! Default Constructor
        TQuaternion() : quaternion() {}

        //! Constructor
        TQuaternion(f32 x, f32 y, f32 z, f32 w) : quaternion(x,y,z,w) {}

        //! Constructor which converts euler angles (radians) to a quaternion
        TQuaternion(f32 x, f32 y, f32 z) : quaternion(x,y,z) {}

        //! Constructor which converts euler angles (radians) to a quaternion
        TQuaternion(const vector3df& vec) : quaternion(vec) {}

        //! Constructor which converts a matrix to a quaternion
        TQuaternion(const matrix4& mat) : quaternion(mat) {}

        //! Output this quaternion to a euler angle (degrees)
        void toEulerDegrees(vector3df& euler) const;

    };
} 
#endif
