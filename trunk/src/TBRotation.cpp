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

namespace Tubras
{
    TBRotation::~TBRotation()
    {

    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TBRotation::initialize(TEntity* owner, TProperties& properties)
    {
        IBehavior::initialize(owner, properties);

        m_node = (ISceneNode*) properties["node"].asPointer();
        if(m_node)
        {
            char name[64];
            sprintf(name,"e%d:rotation:%p",owner->getID(),this);
            m_controller = new TRotateController(name, m_node, 
                properties["velocity"].asFloat(),
                *((TVector3 *)properties["axis"].asPointer()));
        }

        return 0;
    }

}
