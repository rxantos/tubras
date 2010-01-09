//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    int TTaskDelegate::Execute(TTask* Param) const
    {
        {
            if (pFunction) 
            {
                return (m_instance->*pFunction)(Param);
            }
            else 
            {
                return 0;
            }
        }
    }
}

