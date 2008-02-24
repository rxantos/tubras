//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T S o u n d N o d e
    //-----------------------------------------------------------------------
    TSoundNode::TSoundNode(TSound* sound, ISceneNode *parent) : TEmptyNode(parent)
    {

        m_sound = sound;
        m_sound->setPositional(true);
        m_sound->setNode(this);
        getApplication()->getSoundManager()->addSoundNode(this);

    }

    //-----------------------------------------------------------------------
    //                       ~ T S o u n d N o d e
    //-----------------------------------------------------------------------
    TSoundNode::~TSoundNode()
    {

    }
}

