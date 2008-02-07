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
    //                        T C o l l i d e r B o x
    //-----------------------------------------------------------------------
    TColliderBox::TColliderBox(TAABBox box) : TColliderShape()
    {
        TVector3 hs = box.getHalfSize();
        const btVector3 halfExtents(hs.X,hs.Y,hs.Z);
        m_shape = new btBoxShape(halfExtents);
    }

    //-----------------------------------------------------------------------
    //                        T C o l l i d e r B o x
    //-----------------------------------------------------------------------
    TColliderBox::TColliderBox(ISceneNode* node)
    {
        TAABBox aabb = node->getBoundingBox();
        TVector3 hs = aabb.getHalfSize();
        btVector3 halfExtents(hs.X,hs.Y,hs.Z);
        m_shape = new btBoxShape(halfExtents);
    }


    //-----------------------------------------------------------------------
    //                       ~ T C o l l i d e r B o x
    //-----------------------------------------------------------------------
    TColliderBox::~TColliderBox()
    {
    }
}

