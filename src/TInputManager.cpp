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
#ifndef TUBRAS_PLATFORM_WIN32
#ifdef _IRR_COMPILE_WITH_X11_
#include <X11/Xlib.h>
#endif
#endif

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T I n p u t M a n a g e r
    //-----------------------------------------------------------------------
    TInputManager::TInputManager() : m_inputHandler(0)
    {
    }

    //-----------------------------------------------------------------------
    //                      ~T I n p u t M a n a g e r
    //-----------------------------------------------------------------------
    TInputManager::~TInputManager()
    {
        if(m_inputHandler)
        {
            delete m_inputHandler;
            m_inputHandler = 0;
        }
    }

    //-----------------------------------------------------------------------
    //                          I n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TInputManager::initialize()
    {
        int result=0;

        m_inputHandler = new TInputHandler();
        if(m_inputHandler->Initialize())
            return 1;       

        return result;
    }

    //-----------------------------------------------------------------------
    //                              u p d a t e
    //-----------------------------------------------------------------------
    void TInputManager::update(const u32 deltaTime)
    {
    }

    //-----------------------------------------------------------------------
    //                         i s K e y D o w n 
    //-----------------------------------------------------------------------
    bool TInputManager::isKeyDown(EKEY_CODE key)
    {
        return m_inputHandler->isKeyDown(key);
    }
}
