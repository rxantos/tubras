//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TLINENODE_H_
#define _TLINENODE_H_

namespace Tubras
{
    class TLineNode : public TSceneNode
    {
        friend class TNodeFactory;
    private:
        TVector3        m_start;
        TVector3        m_end;
        TColour         m_colour;
        TAABBox         m_aabb;

        SMaterial       m_material;

    private:
        TLineNode(ISceneNode* parent);

    public:
        ~TLineNode();

        int initialize(const TVector3& start, const TVector3& end, 
            const TColour& colour=TColour(255,255,255));

        void set(const TVector3& start, const TVector3& end, 
            const TColour& colour=TColour(255,255,255));

        TVector3 start() {return m_start;}
        TVector3 end() {return m_end;}

        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;
        SMaterial& getMaterial(u32 i);

    };
} 
#endif
