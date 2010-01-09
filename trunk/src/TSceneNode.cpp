//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode::TSceneNode(ISceneNode* parent, s32 id,
				const TVector3& position,
				const TVector3& rotation,
                const TVector3& scale): TDelegate(),
                ISceneNode(parent,getApplication()->getSceneManager(),id,position,rotation,scale)

    {
        if(!parent)
            setParent(getApplication()->getRootSceneNode());

        drop();
    }

    //-----------------------------------------------------------------------
    //                          ~ T S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode::~TSceneNode()
    {
    }
}

