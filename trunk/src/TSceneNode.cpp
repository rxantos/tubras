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

    TSceneNode::TSceneNode (string name, TSceneNode *parent)
    {
        m_parent = parent;

        if(!m_parent)
        {
            m_parent = getApplication()->getRenderEngine()->getRootNode();
        }
        m_node = m_parent->getNode()->createChildSceneNode();

    }

    TSceneNode::TSceneNode(string name, TSceneNode *parent, Ogre::SceneNode* node)
    {
        m_parent = parent;
        m_node = node;
    }


    void TSceneNode::get_transform(TMatrix4 *transform)
    {
        m_node->getWorldTransforms(transform);
    }

    void TSceneNode::get_transform(TMatrix4* transform,TSceneNode* other)
    {
        other->getNode()->getWorldTransforms(transform);
    }

    TSceneNode* TSceneNode::createChildSceneNode(string name)
    {
        return new TSceneNode(name,this);
    }

    void TSceneNode::rotate(const Ogre::Quaternion& q, Ogre::Node::TransformSpace relativeTo)
    {
        m_node->rotate(q,relativeTo);
    }

    void TSceneNode::attachObject(Ogre::MovableObject* obj)
    {
        m_node->attachObject(obj);

    }

    void TSceneNode::flipVisibility(bool cascade)
    {

        m_node->flipVisibility(cascade);
    }

    void TSceneNode::reparentTo(TSceneNode* newParent)
    {
        if(m_parent->getParentNode())
        {
            m_parent->getParentNode()->removeChild(m_node);
        }
        m_parent = newParent;
        m_parent->addChild(this);
    }


}
