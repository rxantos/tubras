//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TPLANENODE_H_
#define _TPLANENODE_H_

namespace Tubras
{
    class TPlaneNode : public TSceneNode
    {
        friend class TNodeFactory;
    private:
        f32             m_size;
        TVector3        m_normal;
        TAABBox         m_aabb;

        TVertex         m_vertices[4];
        SMaterial       m_material;

    private:
        TPlaneNode(ISceneNode* parent);

    public:
        ~TPlaneNode();

        int initialize(f32 size, TVector3 normal=TVector3::UNIT_Y, TColor color=TColor(255,255,255));

        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;
        SMaterial& getMaterial(u32 i);

    };
} 
#endif
