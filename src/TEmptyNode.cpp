//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T E m p t y N o d e
    //-----------------------------------------------------------------------
    TEmptyNode::TEmptyNode(ISceneNode* parent) : TSceneNode(parent)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T E m p t y N o d e
    //-----------------------------------------------------------------------
    TEmptyNode::~TEmptyNode()
    {
    }
}

