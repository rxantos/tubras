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
        m_dnode = NULL;

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
        m_dnode = NULL;        
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
    void TSceneNode::attachObject(TModelNode* node)
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
    void TSceneNode::detachObject(TModelNode* node)
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
    //                           r e p a r e n t T o
    //-----------------------------------------------------------------------
    void TSceneNode::reparentTo(TSceneNode* newParent)
    {        
        if(m_parent && m_parent->getParentNode())
        {
            m_parent->getParentNode()->removeChild(m_node);
        }
        m_parent = newParent;
        m_parent->addChild(this);
    }

    //-----------------------------------------------------------------------
    //                           s e t P a r e n t
    //-----------------------------------------------------------------------
    void TSceneNode::setParent(TSceneNode* newParent)
    {        
        m_parent = newParent;
        m_parent->addChild(this);
    }

    //-----------------------------------------------------------------------
    //                        m o v e R e l a t i v e
    //-----------------------------------------------------------------------
    void TSceneNode::moveRelative(TVector3& vec)
    {
        TQuaternion quat = m_node->getOrientation();
        TVector3 trans = quat * vec;
        TVector3 pos = m_node->getPosition();
        pos = pos + trans;
        setPos(pos);
    }

    //-----------------------------------------------------------------------
    //                              p i t c h 
    //-----------------------------------------------------------------------
    void TSceneNode::pitch(TRadian& rad)
    {
        m_node->pitch(rad);
    }

    //-----------------------------------------------------------------------
    //                                y a w
    //-----------------------------------------------------------------------
    void TSceneNode::yaw(TRadian& rad,Ogre::Node::TransformSpace relativeTo)
    {
        m_node->yaw(rad,relativeTo);
    }

    //-----------------------------------------------------------------------
    //                              m o v e
    //-----------------------------------------------------------------------
    void TSceneNode::move(const TVector3& vec)
    {
        setPos(getPos() + vec);
    }

    //-----------------------------------------------------------------------
    //                            l o o k A t
    //-----------------------------------------------------------------------
    void TSceneNode::lookAt (const TVector3 &targetPoint, Ogre::Node::TransformSpace relativeTo, 
        const TVector3 &localDirectionVector)
    {
        m_node->lookAt(targetPoint,relativeTo,localDirectionVector);
    }

    //-----------------------------------------------------------------------
    //                            l o o k A t
    //-----------------------------------------------------------------------
    void TSceneNode::lookAt (const TVector3& targetPoint)
    {
        TVector3 realPosition = getPos();

        m_node->setDirection(targetPoint - realPosition);
    }

    //-----------------------------------------------------------------------
    //                            l o o k A t
    //-----------------------------------------------------------------------
    void TSceneNode::lookAt (float x, float y, float z)
    {
        TVector3 vTemp( x, y, z );
        this->lookAt(vTemp);
    }

    //-----------------------------------------------------------------------
    //                       g e t O r i e n t a t i o n
    //-----------------------------------------------------------------------
    TQuaternion TSceneNode::getOrientation(void)
    {
        return m_node->getOrientation();
    }

    //-----------------------------------------------------------------------
    //                g e t D e r i v e d O r i e n t a t i o n
    //-----------------------------------------------------------------------
    TQuaternion TSceneNode::getDerivedOrientation (void)
    {
        return m_node->_getDerivedOrientation();
    }

    //-----------------------------------------------------------------------
    //                  g e t D e r i v e d P o s i t i o n 
    //-----------------------------------------------------------------------
    TVector3 TSceneNode::getDerivedPosition (void)
    {
        return m_node->_getDerivedPosition();
    }

    //-----------------------------------------------------------------------
    //                     g e t D e r i v e d S c a l e
    //-----------------------------------------------------------------------
    TVector3 TSceneNode::getDerivedScale (void)
    {
        return m_node->_getDerivedScale();
    }

    //-----------------------------------------------------------------------
    //                      s e t F i x e d Y a w A x i s
    //-----------------------------------------------------------------------
    void TSceneNode::setFixedYawAxis (bool useFixed, const TVector3& fixedAxis)
    {
        m_node->setFixedYawAxis(useFixed,fixedAxis);
    }

    //-----------------------------------------------------------------------
    //                      s e t O r i e n t a t i o n 
    //-----------------------------------------------------------------------
    void TSceneNode::setOrientation (const TQuaternion &q)
    {
        m_node->setOrientation(q);
    }

    //-----------------------------------------------------------------------
    //                            s e t P o s 
    //-----------------------------------------------------------------------
    void TSceneNode::setPos(const TVector3& pos) 
    {
        m_node->setPosition(pos);
    }

    //-----------------------------------------------------------------------
    //                            s e t P o s 
    //-----------------------------------------------------------------------
    void TSceneNode::setPos(TReal x, TReal y, TReal z) 
    {
        setPos(TVector3(x,y,z));
    }

    //-----------------------------------------------------------------------
    //                            g e t P o s 
    //-----------------------------------------------------------------------
    TVector3 TSceneNode::getPos(void) const
    {
        return m_node->getPosition();
    }

    //-----------------------------------------------------------------------
    //                          a d d C h i l d
    //-----------------------------------------------------------------------
    void TSceneNode::addChild(TSceneNode* node) 
    {
        m_node->addChild(node->getNode());
        m_children.insert(TChildNodeMap::value_type(node->getName(), node));
    }

    //-----------------------------------------------------------------------
    //                    g e t C h i l d I t e r a t o r
    //-----------------------------------------------------------------------
    TSceneNode::TChildNodeIterator TSceneNode::getChildIterator()
    {
        return TChildNodeIterator(m_children.begin(), m_children.end());
    }

    //-----------------------------------------------------------------------
    //                    a t t a c h D y n a m i c N o d e
    //-----------------------------------------------------------------------
    void TSceneNode::attachDynamicNode(TDynamicNode* node)
    {
        m_dnode = node;
    }
}
