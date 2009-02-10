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
    //                       T C o l l i d e r S h a p e
    //-----------------------------------------------------------------------
    TColliderShape::TColliderShape()
    {
        m_shape = NULL;
    }

    //-----------------------------------------------------------------------
    //                      ~ T C o l l i d e r S h a p e
    //-----------------------------------------------------------------------
    TColliderShape::~TColliderShape()
    {
		if(m_shape)
			delete m_shape;
    }

    //-----------------------------------------------------------------------
    //                 c a l c u l a t e L o c a l I n e r t i a
    //-----------------------------------------------------------------------
    void TColliderShape::calculateLocalInertia(float mass,btVector3& inertia)
    {
        m_shape->calculateLocalInertia(mass,inertia);
    }
}

