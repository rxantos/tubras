//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TCOLLIDERPLANE_H_
#define __TCOLLIDERPLANE_H_

namespace Tubras
{

    class TColliderPlane : public TColliderShape
    {
    protected:
        btStaticPlaneShape*     m_plane;

    public:
        TColliderPlane(TVector3 normal, float constant=0.f);
        virtual ~TColliderPlane();

    };

}


#endif
