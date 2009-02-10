//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TEMPTYNODE_H_
#define _TEMPTYNODE_H_

namespace Tubras
{
    class TEmptyNode : public TSceneNode
    {
        friend class TNodeFactory;
        friend class TSoundNode;
    protected:
        const TAABBox         m_aabb;

    private:
        //
        // used by TNodeFactory
        //
        TEmptyNode(ISceneNode* parent);

    public:

        virtual ~TEmptyNode();

        //! Renders the node.
        virtual void render() {}
        virtual const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 

    };
} 
#endif
