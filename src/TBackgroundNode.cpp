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

namespace Tubras {
    //-----------------------------------------------------------------------
    //                       T B a c k g r o u n d N o d e
    //-----------------------------------------------------------------------
    TBackgroundNode::TBackgroundNode(ISceneNode* parent) : TSceneNode(parent)
    {
        setVisible(false);        
    }

    //-----------------------------------------------------------------------
    //                      ~ T B a c k g r o u n d N o d e
    //-----------------------------------------------------------------------
    TBackgroundNode::~TBackgroundNode()
    {
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TBackgroundNode::initialize()
    {
        m_size = 1.f;
        TColor color=TColor::White;

        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_material.ZBuffer = 0;

        TVector3 p0(-m_size,m_size,-1),p1(m_size,m_size,-1);
        TVector3 p2(-m_size,-m_size,-1),p3(m_size,-m_size,-1);

        m_vertices[0] = S3DVertex2TCoords(p0, TVector3::UNIT_Z, 
            color, vector2d<f32>(0,0));
        m_vertices[1] = S3DVertex2TCoords(p1, TVector3::UNIT_Z, 
            color, vector2d<f32>(1,0));
        m_vertices[2] = S3DVertex2TCoords(p2, TVector3::UNIT_Z, 
            color, vector2d<f32>(0,1));
        m_vertices[3] = S3DVertex2TCoords(p3, TVector3::UNIT_Z, 
            color, vector2d<f32>(1,1));

        m_aabb.reset(m_vertices[0].Pos);
        for (s32 i=1; i<4; ++i)
            m_aabb.addInternalPoint(m_vertices[i].Pos);

        return 0;
    }

    //-----------------------------------------------------------------------
    //                   O n R e g i s t e r S c e n e N o d e
    //-----------------------------------------------------------------------
    void TBackgroundNode::OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();        
    }

    //-----------------------------------------------------------------------
    //                       g e t M a t e r i a l C o u n t
    //-----------------------------------------------------------------------
    u32 TBackgroundNode::getMaterialCount() const
    {
        return 1;
    }

    //-----------------------------------------------------------------------
    //                          g e t M a t e r i a l 
    //-----------------------------------------------------------------------
    SMaterial& TBackgroundNode::getMaterial(u32 i)
    {
        return m_material;
    }	

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TBackgroundNode::render()
    {
        u16 indices[] = {	0,1,2, 1,3,2	};
        video::IVideoDriver* driver = SceneManager->getVideoDriver();

        driver->setMaterial(m_material);

        driver->setTransform(video::ETS_WORLD, IdentityMatrix);
        driver->setTransform(video::ETS_VIEW, IdentityMatrix);
        driver->setTransform(video::ETS_PROJECTION, IdentityMatrix);

        driver->drawIndexedTriangleList(&m_vertices[0], 4, &indices[0], 2);
    }
}

