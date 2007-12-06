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

namespace Tubras
{
    const NodeInfo TNodeFactory::types[]= {
        {"TPlaneNode",MAKE_IRR_ID('t','p','l','n')}
    };

    const u32 TNodeFactory::count=1;

    //-----------------------------------------------------------------------
    //                         T N o d e F a c t o r y
    //-----------------------------------------------------------------------
    TNodeFactory::TNodeFactory() : ISceneNodeFactory()
    {
    }

    //-----------------------------------------------------------------------
    //                        ~ T N o d e F a c t o r y
    //-----------------------------------------------------------------------
    TNodeFactory::~TNodeFactory()
    {
    }

    //-----------------------------------------------------------------------
    //                           i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TNodeFactory::initialize()
    {

        return 0;
    }


		//! adds a scene node to the scene graph based on its type id
		/** \param type: Type of the scene node to add.
		\param parent: Parent scene node of the new node, can be null to add the scene node to the root.
		\return Returns pointer to the new scene node or null if not successful. */
    ISceneNode* TNodeFactory::addSceneNode(ESCENE_NODE_TYPE type, ISceneNode* parent)
    {
        ISceneNode* node=0;

        return node;
    }


		//! adds a scene node to the scene graph based on its type name
		/** \param typeName: Type name of the scene node to add.
		\param parent: Parent scene node of the new node, can be null to add the scene node to the root.
		\return Returns pointer to the new scene node or null if not successful. */
    ISceneNode* TNodeFactory::addSceneNode(const c8* typeName, ISceneNode* parent)
    {
        ISceneNode* node=0;

        return node;
    }

		//! returns amount of scene node types this factory is able to create
    u32 TNodeFactory::getCreatableSceneNodeTypeCount() const
    {
        return count;
    }

		//! returns type name of a createable scene node type by index
		/** \param idx: Index of scene node type in this factory. Must be a value between 0 and
		uetCreatableSceneNodeTypeCount() */
    const c8* TNodeFactory::getCreateableSceneNodeTypeName(u32 idx) const
    {
        return types[idx].name.c_str();
    }

		//! returns type of a createable scene node type
		/** \param idx: Index of scene node type in this factory. Must be a value between 0 and
		getCreatableSceneNodeTypeCount() */
    ESCENE_NODE_TYPE TNodeFactory::getCreateableSceneNodeType(u32 idx) const
    {
        return (ESCENE_NODE_TYPE)types[idx].type;
    }

		//! returns type name of a createable scene node type 
		/** \param idx: Type of scene node. 
		\return: Returns name of scene node type if this factory can create the type, otherwise 0. */
    const c8* TNodeFactory::getCreateableSceneNodeTypeName(ESCENE_NODE_TYPE type) const
    {
        return "x";
    }


} 
