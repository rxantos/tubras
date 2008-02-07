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
    //                    T C o l l i d e r C y l i n d e r
    //-----------------------------------------------------------------------
    TColliderCylinder::TColliderCylinder(TVector3 halfExtents) : TColliderShape()
    {
		m_shape = new btCylinderShape(TIBConvert::IrrToBullet(halfExtents));
    }

    //-----------------------------------------------------------------------
    //                   ~ T C o l l i d e r C y l i n d e r
    //-----------------------------------------------------------------------
    TColliderCylinder::~TColliderCylinder()
    {
    }
}

