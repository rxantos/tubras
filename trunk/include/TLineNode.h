//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TLINENODE_H_
#define _TLINENODE_H_

namespace Tubras
{
    class TLineNode : public TSceneNode
    {
    private:
        TVector3        m_start;
        TVector3        m_end;
        TColor          m_color;
        TAABBox         m_aabb;

        SMaterial       m_material;

    public:
        TLineNode(ISceneNode* parent, s32 id,
            const TVector3& start, const TVector3& end, 
            const TColor& color=TColor(255,255,255));
        ~TLineNode();
        void set(const TVector3& start, const TVector3& end, 
            const TColor& color=TColor(255,255,255));

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
