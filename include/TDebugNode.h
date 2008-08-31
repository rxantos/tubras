//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TDEBUGNODE_H_
#define _TDEBUGNODE_H_

namespace Tubras
{
    class TDebugNode : public TSceneNode
    {
        friend class TNodeFactory;
    private:
        S3DVertex*      m_vertices;
        u16             m_vcount;
        u16             m_vmax;

        u32*            m_indices;
        u16             m_icount;

        video::IVideoDriver* m_driver;
        TAABBox         m_aabb;
        SMaterial       m_material;

    private:
        TDebugNode(ISceneNode* parent);

    public:
        ~TDebugNode();

        void addLine(const TVertex& v1, const TVertex& v2);
        void reset();

        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;
        SMaterial& getMaterial(u32 i);

    };
} 
#endif
