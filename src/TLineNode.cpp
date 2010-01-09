//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T L i n e N o d e
    //-----------------------------------------------------------------------
    TLineNode::TLineNode(ISceneNode* parent, s32 id,
            const TVector3& start, const TVector3& end, 
            const TColor& color) : TSceneNode(parent, id)
    {
        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_material.DiffuseColor = color;
        set(start, end, color);
    }

    //-----------------------------------------------------------------------
    //                          ~ T L i n e N o d e
    //-----------------------------------------------------------------------
    TLineNode::~TLineNode()
    {
    }

    //-----------------------------------------------------------------------
    //                                s e t
    //-----------------------------------------------------------------------
    void TLineNode::set(const TVector3& start, const TVector3& end, 
        const TColor& color)
    {
        m_start = start;
        m_end = end;
        m_color = color;
        m_aabb.reset(m_start);
        m_aabb.addInternalPoint(m_end);
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
        driver->draw3DLine(m_start,m_end,m_color);
    }
}

