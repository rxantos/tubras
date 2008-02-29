//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TAXISNODE_H_
#define _TAXISNODE_H_

namespace Tubras
{
    class TAxisNode : public TSceneNode
    {
        friend class TNodeFactory;
    private:
        TAABBox         m_aabb;
        u32             m_size;
        TLineNode*      m_xLine;
        TLineNode*      m_yLine;
        TLineNode*      m_zLine;
        bool            m_full;

        SMaterial       m_material;

    private:
        TAxisNode(ISceneNode* parent);

    public:
        ~TAxisNode();

        int initialize(f32 size,bool full=true, bool labels=true);

        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;
        SMaterial& getMaterial(u32 i);

    };
} 
#endif
