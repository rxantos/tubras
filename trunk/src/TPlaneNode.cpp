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
    TPlaneNode::TPlaneNode(f32 size, TVector3 normal, ISceneNode* parent, ISceneManager* mgr, s32 id,
        const TVector3& position,
        const TVector3& rotation,
        const TVector3& scale) :
    TSceneNode(parent,mgr,id,position,rotation,scale),
        m_size(size)
    {
        m_material.Wireframe = false;
        m_material.Lighting = false;
        normal.normalize();

        TVector3 p1(-size,size,0),p2(size,size,0),p3(size,-size,0),p4(-size,-size,0);
        if(normal.equals(TVector3::UNIT_Y))
        {
            p1 = TVector3(-size,0,-size);
            p2 = TVector3(size,0,-size);
            p3 = TVector3(size,0,size);
            p4 = TVector3(-size,0,size);
        } else if(normal.equals(TVector3::UNIT_X))
        {
            p1 = TVector3(0,size,-size);
            p2 = TVector3(0,size,size);
            p3 = TVector3(0,-size,size);
            p4 = TVector3(0,-size,-size);
        }


        m_vertices[0] = TVertex(p1, normal,TColour(255,255,255),TVector2(0,1));
        m_vertices[1] = TVertex(p2, normal,TColour(255,255,255),TVector2(1,1));
        m_vertices[2] = TVertex(p3, normal,TColour(255,255,255),TVector2(1,0));
        m_vertices[3] = TVertex(p4, normal,TColour(255,255,255),TVector2(0,0));

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
		u16 indices[] = {	0,2,1, 0,3,2	};
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(m_material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawIndexedTriangleList(&m_vertices[0], 4, &indices[0], 2);
    }

}