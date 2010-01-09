//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                           E x e c u t e
    //-----------------------------------------------------------------------
    int TEventDelegate::Execute(const TEvent* event) const
    {
        {
            if (pFunction) 
            {
                return (m_instance->*pFunction)(event);
            }
            else 
            {
                return 0;
            }
        }
    }
}

