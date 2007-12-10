//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T P l a n e N o d e
    //-----------------------------------------------------------------------
    TPlaneNode::TPlaneNode(ISceneNode* parent) : TSceneNode(parent)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T P l a n e N o d e
    //-----------------------------------------------------------------------
    TPlaneNode::~TPlaneNode()
    {
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TPlaneNode::initialize(f32 size, TVector3 normal, TColour colour)
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


        m_vertices[0] = TVertex(p1, m_normal,colour,TVector2(0,1));
        m_vertices[1] = TVertex(p2, m_normal,colour,TVector2(1,1));
        m_vertices[2] = TVertex(p3, m_normal,colour,TVector2(1,0));
        m_vertices[3] = TVertex(p4, m_normal,colour,TVector2(0,0));

        m_aabb.reset(m_vertices[0].Pos);
        for (s32 i=1; i<4; ++i)
            m_aabb.addInternalPoint(m_vertices[i].Pos);

        return 0;
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