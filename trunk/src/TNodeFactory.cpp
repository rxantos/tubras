//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    const NodeInfo TNodeFactory::types[]= {
        {"TEmptyNode",MAKE_IRR_ID('t','e','m','p')},
        {"TPlaneNode",MAKE_IRR_ID('t','p','l','n')},
        {"TCameraNode",MAKE_IRR_ID('t','c','a','m')}
    };

    const u32 TNodeFactory::typeCount=3;

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
        else if(tname == "TCameraNode")
        {
            if(!parent)
                parent = getSceneManager()->getRootSceneNode();
            node = new TCameraNode(parent,getSceneManager());
            getSceneManager()->setActiveCamera((ICameraSceneNode*)node);            
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
