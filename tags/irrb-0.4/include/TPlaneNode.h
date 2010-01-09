//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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
    private:
        TVector2        m_size;
        TAABBox         m_aabb;

        TVertex         m_vertices[4];
        SMaterial       m_material;

    private:

    public:
        // orientation - (0,0,1).  rotation in degrees.
        TPlaneNode(ISceneNode* parent, s32 id, TVector2 size=TVector2(1,1), 
            TVector3 rotation=TVector3(), TColor color=TColor::White);
        ~TPlaneNode();

        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;
        SMaterial& getMaterial(u32 i);

    };
} 
#endif
