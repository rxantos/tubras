//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                     T C o l l i d e r S p h e r e
    //-----------------------------------------------------------------------
    TColliderSphere::TColliderSphere(TAABBox aabb) : TColliderShape()
    {
        TVector3 hs = aabb.getHalfSize();
        m_shape = new btSphereShape(hs.Y);
    }

    //-----------------------------------------------------------------------
    //                     T C o l l i d e r S p h e r e
    //-----------------------------------------------------------------------
    TColliderSphere::TColliderSphere(ISceneNode* node)
    {
        TAABBox aabb = node->getBoundingBox();
        TVector3 hs = aabb.getHalfSize();
        m_shape = new btSphereShape(hs.Y);
    }

    //-----------------------------------------------------------------------
    //                    ~ T C o l l i d e r S p h e r e
    //-----------------------------------------------------------------------
    TColliderSphere::~TColliderSphere()
    {
    }
}

