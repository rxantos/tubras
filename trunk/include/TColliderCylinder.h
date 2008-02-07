//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TCOLLIDERCYLINDER_H_
#define __TCOLLIDERCYLINDER_H_

namespace Tubras
{

    class TColliderCylinder : public TColliderShape
    {
    protected:

    public:
        TColliderCylinder(TVector3 halfExtents);
        virtual ~TColliderCylinder();


    };

}


#endif
