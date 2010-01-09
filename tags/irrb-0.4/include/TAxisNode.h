//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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
    private:
        TAABBox         m_aabb;
        u32             m_size;
        TLineNode*      m_xLine;
        TLineNode*      m_yLine;
        TLineNode*      m_zLine;
        bool            m_full;

        SMaterial       m_material;

    public:
        TAxisNode(ISceneNode* parent, s32 id, f32 size,bool full=true, bool labels=true);
        ~TAxisNode();
        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;
        SMaterial& getMaterial(u32 i);

    };
} 
#endif
