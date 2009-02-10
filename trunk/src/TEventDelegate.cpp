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

