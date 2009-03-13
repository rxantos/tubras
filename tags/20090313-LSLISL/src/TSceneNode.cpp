//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode::TSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
				const TVector3& position,
				const TVector3& rotation,
                const TVector3& scale): TObject(),
                ISceneNode(parent,mgr ? mgr : TObject::getSceneManager(),id,position,rotation,scale)

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

