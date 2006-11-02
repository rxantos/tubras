//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                          T P l a n e N o d e
    //-----------------------------------------------------------------------
    TPlaneNode::TPlaneNode(string name, TSceneNode* parent,size_t size,TVector3 normal) : TSceneNode(name,parent)
    {
        TVector3  upVector;

        m_size = size;

        Ogre::MovablePlane plane( normal, 0 );

        if(normal == TVector3::UNIT_Y)
            upVector = TVector3::UNIT_X;
        else if(normal == TVector3::UNIT_X)
            upVector = TVector3::UNIT_Y;
        else upVector = TVector3::UNIT_Z;

        Ogre::MeshManager::getSingleton().createPlane(name + "::plane",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            m_size,m_size,1,1,true,1,m_size/4,m_size/4,upVector);

        m_planeEntity = getRenderEngine()->getSceneManager()->createEntity(name + "::Entity",name+"::plane");
		m_planeEntity->setCastShadows(false);
        getNode()->attachObject(m_planeEntity);

    }

    //-----------------------------------------------------------------------
    //                         ~ T P l a n e N o d e
    //-----------------------------------------------------------------------
    TPlaneNode::~TPlaneNode()
    {
    }

    //-----------------------------------------------------------------------
    //                      s e t M a t e r i a l N a m e
    //-----------------------------------------------------------------------
    void TPlaneNode::setMaterialName(string matName)
    {
        m_planeEntity->setMaterialName(matName);
    }
}