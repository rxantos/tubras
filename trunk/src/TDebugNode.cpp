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
    //                           T P l a n e N o d e
    //-----------------------------------------------------------------------
    TDebugNode::TDebugNode(ISceneNode* parent) : TSceneNode(parent),
        m_vertices(0),
        m_vcount(0),
        m_indices(0),
        m_icount(0),
        m_vmax(1000)              // start with 100 vertices = 50 lines
    {
        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_material.DiffuseColor = TColour::White;
        m_material.AmbientColor = TColour::White;
		m_driver = SceneManager->getVideoDriver();

        m_vertices = (S3DVertex*)malloc(sizeof(S3DVertex)*m_vmax);
        m_indices = (u32*)malloc(sizeof(m_indices)*m_vmax);
        m_aabb.reset(0.f,0.f,0.f);
    }

    //-----------------------------------------------------------------------
    //                          ~ T P l a n e N o d e
    //-----------------------------------------------------------------------
    TDebugNode::~TDebugNode()
    {
        if(m_vertices)
            free(m_vertices);
        if(m_indices)
            free(m_indices);
    }

    //-----------------------------------------------------------------------
    //                            a d d L i n e
    //-----------------------------------------------------------------------
    void TDebugNode::addLine(const TVertex& v1, const TVertex& v2)
    {
        if((m_vcount+2) >= m_vmax)
        {
            m_vmax += 1000;
            m_vertices = (S3DVertex*)realloc(m_vertices,sizeof(S3DVertex)*m_vmax);
            m_indices = (u32*)realloc(m_indices,sizeof(m_indices)*m_vmax);
        }

        m_vertices[m_vcount++] = v1;
        m_vertices[m_vcount++] = v2;
        m_indices[m_icount] = m_icount++;
        m_indices[m_icount] = m_icount++;

        m_aabb.addInternalPoint(v1.Pos);
        m_aabb.addInternalPoint(v2.Pos);
    }

    //-----------------------------------------------------------------------
    //                                r e s e t
    //-----------------------------------------------------------------------
    void TDebugNode::reset()
    {
        m_vcount = 0;
        m_icount = 0;
        m_aabb.reset(0.f,0.f,0.f);
    }

    //-----------------------------------------------------------------------
    //                   O n R e g i s t e r S c e n e N o d e
    //-----------------------------------------------------------------------
    void TDebugNode::OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();        
    }

    //-----------------------------------------------------------------------
    //                       g e t M a t e r i a l C o u n t
    //-----------------------------------------------------------------------
    u32 TDebugNode::getMaterialCount() const
	{
		return 1;
	}

    //-----------------------------------------------------------------------
    //                          g e t M a t e r i a l 
    //-----------------------------------------------------------------------
    SMaterial& TDebugNode::getMaterial(u32 i)
	{
		return m_material;
	}	

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TDebugNode::render()
    {
		m_driver->setMaterial(m_material);
		m_driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        m_driver->drawVertexPrimitiveList(m_vertices,m_vcount,m_indices,
            m_icount/2,EVT_STANDARD,EPT_LINES,EIT_32BIT);
    }
}

