//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    void TIntervalDelegate::Execute(double T, void* userData) const
    {
        {
            if (pFunction) 
            {
                (m_instance->*pFunction)(T,userData);
            }
        }
    }
}
