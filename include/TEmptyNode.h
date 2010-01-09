//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TEMPTYNODE_H_
#define _TEMPTYNODE_H_

namespace Tubras
{
    class TEmptyNode : public TSceneNode
    {
        friend class TSoundNode;
    protected:
        const TAABBox         m_aabb;

    public:
        TEmptyNode(ISceneNode* parent);
        virtual ~TEmptyNode();

        //! Renders the node.
        virtual void render() {}
        virtual const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 

    };
} 
#endif
