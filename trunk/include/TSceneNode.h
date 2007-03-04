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

#ifndef _TSCENENODE_H_
#define _TSCENENODE_H_

namespace Tubras
{
    enum  TShapeType;

    class TSceneNode : public TObject
    {
    public:

        typedef HashMap<TString, TSceneNode*> TChildNodeMap;
        typedef Ogre::MapIterator<TChildNodeMap> TChildNodeIterator;


    protected:
        TChildNodeMap       m_children;
        TString				m_name;
        TSceneNode*         m_parent;
        Ogre::SceneNode*    m_node;
        TDynamicNode*       m_dnode;
        bool                m_movementEnabled;
        void*               m_userData;

    public:
        TSceneNode (TString name, TSceneNode *parent=NULL);
        TSceneNode (TString name, TSceneNode *parent, Ogre::SceneNode* node);
        virtual ~TSceneNode();

        Ogre::SceneNode* getNode() {return m_node;};
        TSceneNode* getParent() {return m_parent;};
        Ogre::SceneNode* getParentNode() {return m_parent->getNode();};

        void addChild(TSceneNode* node);
        TSceneNode* createChildSceneNode(TString name);
        TString getName() {return m_name;};

        virtual TSceneNode::TChildNodeIterator getChildIterator();


        virtual void attachObject(TModelNode* node);
        virtual void attachObject(Ogre::MovableObject* node);
        virtual void detachObject(TModelNode* node);

        void attachDynamicNode(TDynamicNode* node);

        virtual void reparentTo(TSceneNode* newParent);
        virtual void setParent(TSceneNode* newParent);

        virtual void flipVisibility(bool cascade = true);

        virtual void enableMovement(bool value) {m_movementEnabled = value;};
        virtual bool getMovementEnabled() {return m_movementEnabled;};

        virtual void setPos(const TVector3& pos);
        virtual void setPos(TReal x, TReal y, TReal z);
        virtual TVector3 getPos(void) const;

        void getTransform(TMatrix4* transform); 
        void getTransform(TMatrix4* transform,TSceneNode* other); 
        TQuaternion getOrientation(void);
        TQuaternion getDerivedOrientation (void);
        TVector3 	getDerivedPosition (void);
        TVector3 	getDerivedScale (void);

        void setFixedYawAxis (bool useFixed, const TVector3& fixedAxis=TVector3::UNIT_Y);

        virtual void setOrientation (const TQuaternion &q);

        virtual void setHpr(TReal heading, TReal pitch, TReal roll);
        virtual void resetOrientation();

        void move(const TVector3& vec);
        void moveRelative(TVector3& vec);
        void pitch(TRadian& rad);
        void yaw(TRadian& rad,Ogre::Node::TransformSpace relativeTo=Ogre::Node::TS_LOCAL);

        void lookAt (const TVector3& targetPoint, Ogre::Node::TransformSpace relativeTo, const TVector3 &localDirectionVector=TVector3::NEGATIVE_UNIT_Z);
        void lookAt (const TVector3& targetPoint);
        void lookAt (float x, float y, float z);

        virtual void rotate(const Ogre::Quaternion& q, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
        virtual void synchronizeMotionState() {}

        virtual bool isDynamic() {return false;}

        void setUserData(void* value) {m_userData = value;}
        void* getUserData() {return m_userData;}

    };

}
#endif

