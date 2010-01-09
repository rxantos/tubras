//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TBACKGROUNDNODE_H_
#define _TBACKGROUNDNODE_H_

namespace Tubras
{
    class TBackgroundNode : public TSceneNode
    {
    private:
        f32             m_size;
        TAABBox         m_aabb;

        S3DVertex2TCoords m_vertices[4];
        SMaterial       m_material;

    public:
        TBackgroundNode(TString imageFileName="");

        virtual ~TBackgroundNode();

        void setImage(TString fileName);
        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;

        SMaterial& getMaterial(u32 i);

    };
} 
#endif
