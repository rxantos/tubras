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
    //                           T A x i s N o d e
    //-----------------------------------------------------------------------
    TAxisNode::TAxisNode(ISceneNode* parent) : TSceneNode(parent)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T A x i s N o d e
    //-----------------------------------------------------------------------
    TAxisNode::~TAxisNode()
    {
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TAxisNode::initialize(f32 size)
    {
        m_xLine = (TLineNode*)getSceneManager()->addSceneNode("TLineNode",this);
        m_xLine->initialize(TVector3(-size,0,0),TVector3(size,0,0),TColour(255,0,0));

        m_yLine = (TLineNode*)getSceneManager()->addSceneNode("TLineNode",this);
        m_yLine->initialize(TVector3(0,-size,0),TVector3(0,size,0),TColour(0,255,0));

        m_zLine = (TLineNode*)getSceneManager()->addSceneNode("TLineNode",this);
        m_zLine->initialize(TVector3(0,0,-size),TVector3(0,0,size),TColour(0,0,255));

        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_material.DiffuseColor = TColour(255,255,255);

        /*
        m_aabb.reset(m_start);
        m_aabb.addInternalPoint(m_end);
        */
        return 0;
    }


    //-----------------------------------------------------------------------
    //                   O n R e g i s t e r S c e n e N o d e
    //-----------------------------------------------------------------------
    void TAxisNode::OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();        
    }

    //-----------------------------------------------------------------------
    //                       g e t M a t e r i a l C o u n t
    //-----------------------------------------------------------------------
    u32 TAxisNode::getMaterialCount() const
	{
		return 1;
	}

    //-----------------------------------------------------------------------
    //                          g e t M a t e r i a l 
    //-----------------------------------------------------------------------
    SMaterial& TAxisNode::getMaterial(u32 i)
	{
		return m_material;
	}	

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TAxisNode::render()
    {
        /*
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(m_material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        driver->draw3DLine(m_start,m_end,m_colour);
        */
    }
}

