//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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

