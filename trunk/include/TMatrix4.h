//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TMATRIX4_H_
#define _TMATRIX4_H_

namespace Tubras
{
    class TMatrix4 : public irr::core::matrix4
    {
    public:

        TMatrix4( eConstructor constructor = EM4CONST_IDENTITY ) : irr::core::matrix4(constructor) {}
        TMatrix4( const matrix4& other,eConstructor constructor = EM4CONST_COPY) : irr::core::matrix4(other,constructor) {}

    };
} 
#endif
