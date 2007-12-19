//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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
            return NULL;
        }

        return m_parameters[n];
    }


}
