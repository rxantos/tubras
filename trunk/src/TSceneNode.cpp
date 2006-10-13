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
    //                          T S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode::TSceneNode (string name, TSceneNode *parent) : TObject()
    {
        m_name = name;
        m_parent = parent;

        if(!name.compare("root3d"))
            return;

        if(!m_parent)
        {
            m_parent = getApplication()->getRenderEngine()->getRootNode();
        }
        m_node = m_parent->getNode()->createChildSceneNode(name);
        getApplication()->getRenderEngine()->addSceneNode(name,this);

    }

    //-----------------------------------------------------------------------
    //                          T S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode::TSceneNode(string name, TSceneNode *parent, Ogre::SceneNode* node) : TObject()
    {
        m_parent = parent;
        m_node = node;
        
    }

    //-----------------------------------------------------------------------
    //                         ~ T S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode::~TSceneNode()
    {
        if(!m_name.empty())
            getApplication()->getRenderEngine()->destroySceneNode(m_node->getName());
    }

    //-----------------------------------------------------------------------
    //                          g e t T r a n s f o r m
    //-----------------------------------------------------------------------
    void TSceneNode::getTransform(TMatrix4 *transform)
    {
        m_node->getWorldTransforms(transform);
    }

    //-----------------------------------------------------------------------
    //                          g e t T r a n s f o r m
    //-----------------------------------------------------------------------
    void TSceneNode::getTransform(TMatrix4* transform,TSceneNode* other)
    {
        other->getNode()->getWorldTransforms(transform);
    }

    //-----------------------------------------------------------------------
    //                  c r e a t e C h i l d S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode* TSceneNode::createChildSceneNode(string name)
    {
        return new TSceneNode(name,this);
    }

    //-----------------------------------------------------------------------
    //                          a t t a c h O b j e c t
    //-----------------------------------------------------------------------
    void TSceneNode::attachObject(TEntityNode* node)
    {
        m_node->attachObject(node->getEntity());
    }

    //-----------------------------------------------------------------------
    //                          a t t a c h O b j e c t
    //-----------------------------------------------------------------------
    void TSceneNode::attachObject(Ogre::MovableObject* node)
    {
        m_node->attachObject(node);
    }

    //-----------------------------------------------------------------------
    //                          d e t a c h O b j e c t
    //-----------------------------------------------------------------------
    void TSceneNode::detachObject(TEntityNode* node)
    {
        m_node->attachObject(node->getEntity());
    }

    //-----------------------------------------------------------------------
    //                             r o t a t e
    //-----------------------------------------------------------------------
    void TSceneNode::rotate(const Ogre::Quaternion& q, Ogre::Node::TransformSpace relativeTo)
    {
        m_node->rotate(q,relativeTo);
    }

    //-----------------------------------------------------------------------
    //                        f l i p V i s i b i l i t y
    //-----------------------------------------------------------------------
    void TSceneNode::flipVisibility(bool cascade)
    {

        m_node->flipVisibility(cascade);
    }

    //-----------------------------------------------------------------------
    //                       g e t T r a n s f o r m
    //-----------------------------------------------------------------------
    void TSceneNode::reparentTo(TSceneNode* newParent)
    {
        if(m_parent->getParentNode())
        {
            m_parent->getParentNode()->removeChild(m_node);
        }
        m_parent = newParent;
        m_parent->addChild(this);
    }

    //-----------------------------------------------------------------------
    //                  a t t a c h C o l l i s i o n N o d e
    //-----------------------------------------------------------------------
    void TSceneNode::attachCollisionNode(TCollisionNode* cnode)
    {
        m_cnode = cnode;
    }



}
