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
    //                             T E v e n t
    //-----------------------------------------------------------------------
    TEvent::TEvent(const TString& name)
    {
        m_name = name;
        m_userData = NULL;
        m_id = getEventManager()->registerEvent(name);
    }

    //-----------------------------------------------------------------------
    //                             s e t N a m e
    //-----------------------------------------------------------------------
    void TEvent::setName(const TString &name)
    {
        m_name = name;
        m_id = getEventManager()->registerEvent(name);
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
