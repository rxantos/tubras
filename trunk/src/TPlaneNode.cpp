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

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T P l a n e N o d e
    //-----------------------------------------------------------------------
    TPlaneNode::TPlaneNode(ISceneNode* parent, s32 id, f32 size, 
            TVector3 normal, TColor color) : TSceneNode(parent, id)
    {
        m_size = size;
        m_normal = normal;
        f32 m_halfSize = size/2.f;

        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_normal.normalize();

        TVector3 p1(-m_halfSize,m_halfSize,0),p2(m_halfSize,m_halfSize,0),p3(m_halfSize,-m_halfSize,0),p4(-m_halfSize,-m_halfSize,0);
        if(m_normal.equals(TVector3::UNIT_Y))
        {
            p1 = TVector3(-m_halfSize,0,m_halfSize);
            p2 = TVector3(m_halfSize,0,m_halfSize);
            p3 = TVector3(m_halfSize,0,-m_halfSize);
            p4 = TVector3(-m_halfSize,0,-m_halfSize);
        } else if(m_normal.equals(TVector3::UNIT_X))
        {
            p1 = TVector3(0,m_halfSize,-m_halfSize);
            p2 = TVector3(0,m_halfSize,m_halfSize);
            p3 = TVector3(0,-m_halfSize,m_halfSize);
            p4 = TVector3(0,-m_halfSize,-m_halfSize);
        }


        m_vertices[0] = TVertex(p1, m_normal,color,TVector2f(0,1));
        m_vertices[1] = TVertex(p2, m_normal,color,TVector2f(1,1));
        m_vertices[2] = TVertex(p3, m_normal,color,TVector2f(1,0));
        m_vertices[3] = TVertex(p4, m_normal,color,TVector2f(0,0));

        m_aabb.reset(m_vertices[0].Pos);
        for (s32 i=1; i<4; ++i)
            m_aabb.addInternalPoint(m_vertices[i].Pos);

    }

    //-----------------------------------------------------------------------
    //                          ~ T P l a n e N o d e
    //-----------------------------------------------------------------------
    TPlaneNode::~TPlaneNode()
    {
    }

    //-----------------------------------------------------------------------
    //                   O n R e g i s t e r S c e n e N o d e
    //-----------------------------------------------------------------------
    void TPlaneNode::OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();        
    }

    //-----------------------------------------------------------------------
    //                       g e t M a t e r i a l C o u n t
    //-----------------------------------------------------------------------
    u32 TPlaneNode::getMaterialCount() const
	{
		return 1;
	}

    //-----------------------------------------------------------------------
    //                          g e t M a t e r i a l 
    //-----------------------------------------------------------------------
    SMaterial& TPlaneNode::getMaterial(u32 i)
	{
		return m_material;
	}	

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TPlaneNode::render()
    {
		u16 indices[] = {	0,1,2, 0,2,3	};
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(m_material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawIndexedTriangleList(&m_vertices[0], 4, &indices[0], 2);
    }
}

