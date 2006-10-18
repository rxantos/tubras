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

#ifndef _TSCENENODE_H_
#define _TSCENENODE_H_

namespace Tubras
{
    class TCollisionNode;

    class TSceneNode : public TObject
    {
    protected:
        string				m_name;
        TSceneNode*         m_parent;
        Ogre::SceneNode*    m_node;
        TCollisionNode*     m_cnode;

    public:
        TSceneNode (string name, TSceneNode *parent=NULL);
        TSceneNode (string name, TSceneNode *parent, Ogre::SceneNode* node);
        virtual ~TSceneNode();

        Ogre::SceneNode* getNode() {return m_node;};
        TSceneNode* getParent() {return m_parent;};
        Ogre::SceneNode* getParentNode() {return m_parent->getNode();};

        void addChild(TSceneNode* node) {m_node->addChild(node->getNode());};
        TSceneNode* createChildSceneNode(string name);
        string getName() {return m_name;};

        virtual void attachObject(TModelNode* node);
        virtual void attachObject(Ogre::MovableObject* node);
        virtual void detachObject(TModelNode* node);

        virtual void attachCollisionNode(TCollisionNode* cnode);

        virtual void reparentTo(TSceneNode* newParent);

        virtual void flipVisibility(bool cascade = true);

        virtual void setPos(const TVector3& pos) {m_node->setPosition(pos);};
        virtual void setPos(TReal x, TReal y, TReal z) {m_node->setPosition(x,y,z);};

        void getTransform(TMatrix4* transform); 
        void getTransform(TMatrix4* transform,TSceneNode* other); 

        void moveRelative(TVector3& vec);
        void pitch(TRadian& rad);
        void yaw(TRadian& rad);

        virtual void rotate(const Ogre::Quaternion& q, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);

    };

}
#endif

