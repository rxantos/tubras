//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                      T C o l l i d e r P l a n e
    //-----------------------------------------------------------------------
    TColliderPlane::TColliderPlane(TVector3 normal, float constant) : TColliderShape()
    {
		m_shape =
        m_plane = new btStaticPlaneShape(TIBConvert::IrrToBullet(normal),constant);
        m_plane->setLocalScaling(btVector3(1,0,1));
        

    }

    //-----------------------------------------------------------------------
    //                      T C o l l i d e r P l a n e
    //-----------------------------------------------------------------------
    TColliderPlane::~TColliderPlane()
    {
    }
}

