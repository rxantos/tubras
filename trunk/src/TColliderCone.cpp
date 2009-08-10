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
    //                        T C o l l i d e r C o n e
    //-----------------------------------------------------------------------
    TColliderCone::TColliderCone(ISceneNode* node) : TColliderShape()
    {
        TAABBox aabb = node->getBoundingBox();
        TVector3 hs = aabb.getHalfSize();
        btScalar radius=hs.X;
        btScalar height=hs.Y * 2.f;
        m_shape = new btConeShape(radius, height);

    }

    //-----------------------------------------------------------------------
    //                       ~ T C o l l i d e r C o n e
    //-----------------------------------------------------------------------
    TColliderCone::~TColliderCone()
    {
    }
}

