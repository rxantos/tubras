//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
