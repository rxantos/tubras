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
    //                           T A x i s N o d e
    //-----------------------------------------------------------------------
    TAxisNode::TAxisNode(ISceneNode* parent, s32 id, f32 size, 
        bool full, bool labels) : TSceneNode(parent)
    {
        m_full = full;
        f32 start=-size;

        if(!full)
            start = 0.f;

        ISceneManager* smgr = getApplication()->getSceneManager();
        IGUIEnvironment* gmgr = getApplication()->getGUIManager();

        m_xLine = new TLineNode(this, -1,TVector3(start,0,0),TVector3(size,0,0),TColor(255,0,0) );

        m_yLine = new TLineNode(this, -1, TVector3(0,start,0),TVector3(0,size,0),TColor(0,255,0));

        m_zLine = new TLineNode(this, -1, TVector3(0,0,start),TVector3(0,0,size),TColor(0,0,255));

        if(labels)
        {
            dimension2d<f32> tsize(0.3f,0.3f);
            IBillboardTextSceneNode* tnode;
            tnode = smgr->addBillboardTextSceneNode(gmgr->getBuiltInFont(),L"X+",m_xLine,tsize,
                TVector3(size+0.2f,0,0),-1,TColor::Red,TColor::Red);

            tnode = smgr->addBillboardTextSceneNode(gmgr->getBuiltInFont(),L"Y+",m_yLine,tsize,
                TVector3(0,size+0.2f,0),-1,TColor::Green,TColor::Green);

            tnode = smgr->addBillboardTextSceneNode(gmgr->getBuiltInFont(),L"Z+",m_zLine,tsize,
                TVector3(0,0,size+0.2f),-1,TColor::Blue,TColor::Blue);
        }

        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_material.DiffuseColor = TColor(255,255,255);

        
        m_aabb.reset(m_xLine->start());
        m_aabb.addInternalPoint(m_xLine->end());
        m_aabb.addInternalPoint(m_yLine->start());
        m_aabb.addInternalPoint(m_yLine->end());
        m_aabb.addInternalPoint(m_zLine->start());
        m_aabb.addInternalPoint(m_zLine->end());
    }

    //-----------------------------------------------------------------------
    //                          ~ T A x i s N o d e
    //-----------------------------------------------------------------------
    TAxisNode::~TAxisNode()
    {
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
        driver->draw3DLine(m_start,m_end,m_color);
        */
    }
}

