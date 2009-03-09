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
    //                       T R o t a t e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TRotateController::TRotateController(TString name, ISceneNode* node, float velocity,
        TVector3 axis) : TController(name, node)
    {
        m_axis = axis;
        m_axis.normalize();
        m_velocity = velocity;
    }

    //-----------------------------------------------------------------------
    //                     ~ T R o t a t e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TRotateController::~TRotateController()
    {
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TRotateController::update(float value)
    {
        if(!m_node)
            return;

        TVector3 rotation = m_node->getRotation();        
        rotation += (m_axis * m_velocity * value);
        if(rotation.X > 360.0)
            rotation.X -= 360.f;
        if(rotation.Y > 360.0)
            rotation.Y -= 360.f;
        if(rotation.Z > 360.0)
            rotation.Z -= 360.f;
        m_node->setRotation(rotation);
    }
}

