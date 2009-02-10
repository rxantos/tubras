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
