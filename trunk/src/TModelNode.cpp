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
    //                          T M o d e l N o d e
    //-----------------------------------------------------------------------
    TModelNode::TModelNode(string name, string resourceGroup, string filename, 
        TSceneNode* parent,bool isStatic) : TSceneNode(name,parent)

    {
        m_static = isStatic;
        m_entity = getApplication()->getRenderEngine()->getSceneManager()->createEntity(name+"Mesh",filename);
        m_entity->setCastShadows(false);
        m_node->attachObject(m_entity);
    }

    //-----------------------------------------------------------------------
    //                         ~ T M o d e l N o d e
    //-----------------------------------------------------------------------
    TModelNode::~TModelNode()
    {

        getApplication()->getRenderEngine()->getSceneManager()->destroyMovableObject(m_entity->getName(),"Entity");
    }

    //-----------------------------------------------------------------------
    //                        g e t S u b E n t i t y
    //-----------------------------------------------------------------------
    Ogre::SubEntity* TModelNode::getSubEntity(unsigned int index) const
    {
        return m_entity->getSubEntity(index);
    }

    //-----------------------------------------------------------------------
    //                        g e t S u b E n t i t y
    //-----------------------------------------------------------------------
    Ogre::SubEntity* TModelNode::getSubEntity(string name ) const
    {
        return m_entity->getSubEntity(name);
    }

    //-----------------------------------------------------------------------
    //                    a t t a c h P h y s i c s N o d e
    //-----------------------------------------------------------------------
    void TModelNode::attachPhysicsNode(TPhysicsNode* node)
    {
    }

    //-----------------------------------------------------------------------
    //                    a t t a c h P h y s i c s N o d e
    //-----------------------------------------------------------------------
    void TModelNode::attachPhysicsNode(TShapeType shapeType,float mass)
    {
        TAABox aabb;
        TPhysicsNode*       pnode;
        TColliderShape*     shape=NULL;

        switch(shapeType)
        {
        case stBox:
            aabb = m_entity->getBoundingBox();
            shape = new TColliderBox(aabb);

            break;
        case stSphere:
            break;
        case stCone:
            break;
        case stConvex:
            break;
        case stCylinder:
            break;
        };

        if(shape)
            pnode = new TPhysicsNode(getName()+"::pnode",this,shape,mass);
    }


}