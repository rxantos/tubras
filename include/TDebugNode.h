//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TDEBUGNODE_H_
#define _TDEBUGNODE_H_

namespace Tubras
{
    class TDebugNode : public TSceneNode
    {
    private:
        S3DVertex*      m_vertices;
        u32             m_vcount;
        u32             m_vmax;

        u32*            m_indices;
        u32             m_icount;

        video::IVideoDriver* m_driver;
        TAABBox         m_aabb;
        SMaterial       m_material;

    public:

        TDebugNode(ISceneNode* parent);
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
