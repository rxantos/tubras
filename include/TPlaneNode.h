//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
