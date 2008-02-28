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
    //                           T L i n e N o d e
    //-----------------------------------------------------------------------
    TLineNode::TLineNode(ISceneNode* parent) : TSceneNode(parent)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T L i n e N o d e
    //-----------------------------------------------------------------------
    TLineNode::~TLineNode()
    {
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TLineNode::initialize(const TVector3& start, const TVector3& end, 
        const TColour& colour)
    {
        m_start = start;
        m_end = end;
        m_colour = colour;
        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_material.DiffuseColor = colour;
        m_aabb.reset(m_start);
        m_aabb.addInternalPoint(m_end);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                                s e t
    //-----------------------------------------------------------------------
    void TLineNode::set(const TVector3& start, const TVector3& end, 
        const TColour& colour)
    {
        initialize(start,end,colour);
    }

    //-----------------------------------------------------------------------
    //                   O n R e g i s t e r S c e n e N o d e
    //-----------------------------------------------------------------------
    void TLineNode::OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();        
    }

    //-----------------------------------------------------------------------
    //                       g e t M a t e r i a l C o u n t
    //-----------------------------------------------------------------------
    u32 TLineNode::getMaterialCount() const
	{
		return 1;
	}

    //-----------------------------------------------------------------------
    //                          g e t M a t e r i a l 
    //-----------------------------------------------------------------------
    SMaterial& TLineNode::getMaterial(u32 i)
	{
		return m_material;
	}	

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TLineNode::render()
    {
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(m_material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        driver->draw3DLine(m_start,m_end,m_colour);
    }
}

