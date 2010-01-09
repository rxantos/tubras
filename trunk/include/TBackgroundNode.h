//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
