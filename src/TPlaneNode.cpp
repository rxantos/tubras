//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T P l a n e N o d e
    //-----------------------------------------------------------------------
    TPlaneNode::TPlaneNode(ISceneNode* parent, s32 id, TVector2 size, 
            TVector3 rotation, TColor color) : TSceneNode(parent, id)
    {
        m_size = size;
        f32 m_halfSizeX = size.X/2.f;
        f32 m_halfSizeY = size.Y/2.f;

        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_material.BackfaceCulling = false;

        TVector3 p1(-m_halfSizeX, m_halfSizeY, 0);
        TVector3 p2(m_halfSizeX, m_halfSizeY, 0);
        TVector3 p3(m_halfSizeX, -m_halfSizeY, 0);
        TVector3 p4(-m_halfSizeX, -m_halfSizeY, 0);

        TVector3 normal(0,0,1);

        core::matrix4 mat;
        mat.setRotationDegrees(rotation);
        mat.transformVect(p1);
        mat.transformVect(p2);
        mat.transformVect(p3);
        mat.transformVect(p4);
        mat.transformVect(normal);
        normal.normalize();


        m_vertices[0] = TVertex(p1, normal, color, TVector2f(0,1));
        m_vertices[1] = TVertex(p2, normal, color, TVector2f(1,1));
        m_vertices[2] = TVertex(p3, normal, color, TVector2f(1,0));
        m_vertices[3] = TVertex(p4, normal, color, TVector2f(0,0));

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

