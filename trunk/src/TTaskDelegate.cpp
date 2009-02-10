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

