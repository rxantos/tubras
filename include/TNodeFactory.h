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

#ifndef _TNODEFACTORY_H_
#define _TNODEFACTORY_H_

namespace Tubras
{
    struct NodeInfo
    {
        TString name;
        u32     type;
    };

    class TNodeFactory : public ISceneNodeFactory
    {

    public:

        TNodeFactory();
        ~TNodeFactory();
        int initialize();


		//! adds a scene node to the scene graph based on its type id
		/** \param type: Type of the scene node to add.
		\param parent: Parent scene node of the new node, can be null to add the scene node to the root.
		\return Returns pointer to the new scene node or null if not successful. */
		virtual ISceneNode* addSceneNode(ESCENE_NODE_TYPE type, ISceneNode* parent=0);

		//! adds a scene node to the scene graph based on its type name
		/** \param typeName: Type name of the scene node to add.
		\param parent: Parent scene node of the new node, can be null to add the scene node to the root.
		\return Returns pointer to the new scene node or null if not successful. */
		virtual ISceneNode* addSceneNode(const c8* typeName, ISceneNode* parent=0);

		//! returns amount of scene node types this factory is able to create
		virtual u32 getCreatableSceneNodeTypeCount() const;

		//! returns type name of a createable scene node type by index
		/** \param idx: Index of scene node type in this factory. Must be a value between 0 and
		uetCreatableSceneNodeTypeCount() */
		virtual const c8* getCreateableSceneNodeTypeName(u32 idx) const;

		//! returns type of a createable scene node type
		/** \param idx: Index of scene node type in this factory. Must be a value between 0 and
		getCreatableSceneNodeTypeCount() */
		virtual ESCENE_NODE_TYPE getCreateableSceneNodeType(u32 idx) const;

		//! returns type name of a createable scene node type 
		/** \param idx: Type of scene node. 
		\return: Returns name of scene node type if this factory can create the type, otherwise 0. */
		virtual const c8* getCreateableSceneNodeTypeName(ESCENE_NODE_TYPE type) const;

        static const NodeInfo types[];
        static const u32 count;

    };
} 
#endif
