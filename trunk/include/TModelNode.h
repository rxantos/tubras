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
#ifndef _TMODELNODE_H_
#define _TMODELNODE_H_

namespace Tubras
{
    class TModelNode : public TSceneNode
    {
    protected:
        Ogre::Entity*           m_entity;
        bool                    m_static;

    public:
        TModelNode(TString name, TString resourceGroup, TString filename, TSceneNode* parent,bool isStatic=true);
        TModelNode(TString name, Ogre::Entity* entity, TSceneNode* parent,bool isStatic=true);
        virtual ~TModelNode();

        void setEntity(Ogre::Entity* value) {m_entity = value;}
        Ogre::Entity*	 getEntity(){return m_entity;};
        Ogre::SubEntity* getSubEntity(unsigned int index) const;
        Ogre::SubEntity* getSubEntity(TString name ) const;

        TModelNode* clone(TString newName);

    };

}

#endif