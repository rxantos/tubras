//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                             T E v e n t
    //-----------------------------------------------------------------------
    TEvent::TEvent(const TString& name)
    {
        m_name = name;
        m_userData = NULL;
        m_id = getApplication()->getEventManager()->registerEvent(name);
    }

    //-----------------------------------------------------------------------
    //                             s e t N a m e
    //-----------------------------------------------------------------------
    u32 TEvent::setName(const TString &name)
    {
        m_name = name;
        m_id = getApplication()->getEventManager()->registerEvent(name);
        return m_id;
    }

    //-----------------------------------------------------------------------
    //                        g e t P a r a m e t e r
    //-----------------------------------------------------------------------
    TEventParameter* TEvent::getParameter(int n)
    {
        if((n < 0) || (n > (int)m_parameters.size()))
        {
            return 0;
        }

        return m_parameters[n];
    }


}
