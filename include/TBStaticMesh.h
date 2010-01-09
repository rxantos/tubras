//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TBSTATICMESH_H_
#define _TBSTATICMESH_H_

namespace Tubras
{
    class TBStaticMesh : public TBehavior
    {
        friend class TBehaviorFactory;
    protected:
        IAnimatedMeshSceneNode*     m_node;
    protected:
        TBStaticMesh() : TBehavior("staticmesh") {}

    public:
        int initialize(TEntity* owner, TProperties& properties);
    };
}

#endif
