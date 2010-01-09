//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TBStaticMesh::initialize(TEntity* owner, TProperties& properties)
    {
        TBehavior::initialize(owner, properties);

        TString meshName = properties["mesh"].asString();

        m_node = getApplication()->loadModel(meshName);
        if(m_node)
        {
            TVector3* pos = (TVector3 *)properties["position"].asPointer();
            if(pos)
                m_node->setPosition(*pos);

            if(!properties["visible"].asBool())
                m_node->setVisible(false);
        }

        m_properties["node"] = (void *)m_node;

        return 0;
    }

}
