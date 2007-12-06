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
        {"TEmptyNode",MAKE_IRR_ID('t','e','m','p')},
        {"TPlaneNode",MAKE_IRR_ID('t','p','l','n')}
    };

    const u32 TNodeFactory::typeCount=2;

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
        TObject::initialize();
        getApplication()->getSceneManager()->registerSceneNodeFactory(this);

        return 0;
    }


    //-----------------------------------------------------------------------
    //                         a d d S c e n e N o d e
    //-----------------------------------------------------------------------
    ISceneNode* TNodeFactory::addSceneNode(ESCENE_NODE_TYPE type, ISceneNode* parent)
    {
        for(u32 i=0;i<TNodeFactory::typeCount;i++)
        {
            if(type == types[i].type)
                return addSceneNode(types[i].name.c_str(),parent);
        }
        return 0;
    }


    //-----------------------------------------------------------------------
    //                         a d d S c e n e N o d e
    //-----------------------------------------------------------------------
    ISceneNode* TNodeFactory::addSceneNode(const c8* typeName, ISceneNode* parent)
    {
        TString tname=typeName;
        ISceneNode* node=0;

        if(tname == "TEmptyNode")
        {
            node = new TEmptyNode(parent);
        }
        else if(tname == "TPlaneNode")
        {
            node = new TPlaneNode(parent);
        }
        

        return node;
    }

    //-----------------------------------------------------------------------
    //       g e t C r e a t a b l e S c e n e N o d e T y p e C o u n t
    //-----------------------------------------------------------------------
    u32 TNodeFactory::getCreatableSceneNodeTypeCount() const
    {
        return TNodeFactory::typeCount;
    }

    //-----------------------------------------------------------------------
    //       g e t C r e a t a b l e S c e n e N o d e T y p e N a m e
    //-----------------------------------------------------------------------
    const c8* TNodeFactory::getCreateableSceneNodeTypeName(u32 idx) const
    {
        return types[idx].name.c_str();
    }

    //-----------------------------------------------------------------------
    //          g e t C r e a t a b l e S c e n e N o d e T y p e 
    //-----------------------------------------------------------------------
    ESCENE_NODE_TYPE TNodeFactory::getCreateableSceneNodeType(u32 idx) const
    {
        return (ESCENE_NODE_TYPE)types[idx].type;
    }

    //-----------------------------------------------------------------------
    //       g e t C r e a t a b l e S c e n e N o d e T y p e N a m e
    //-----------------------------------------------------------------------
    const c8* TNodeFactory::getCreateableSceneNodeTypeName(ESCENE_NODE_TYPE type) const
    {
        for(u32 i=0;i<TNodeFactory::typeCount;i++)
        {
            if(type == types[i].type)
                return types[i].name.c_str();
        }

        return 0;
    }


} 
