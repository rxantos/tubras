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
    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TBStaticMesh::initialize(TEntity* owner, TProperties& properties)
    {
        IBehavior::initialize(owner, properties);

        TString meshName = properties["mesh"].asString();

        m_node = getApplication()->loadModel(meshName);
        if(m_node)
        {
            TVector3* pos = (TVector3 *)properties["position"].asPointer();
            if(pos)
                m_node->setPosition(*pos);
        }

        m_properties["node"] = (void *)m_node;

        return 0;
    }

}
