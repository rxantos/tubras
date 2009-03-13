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
    //                        T M o t i o n S t a t e
    //-----------------------------------------------------------------------
    TMotionState::TMotionState(const btTransform& startTrans,
        bool allowDeactivation) : btDefaultMotionState(startTrans)
    {
        m_allowDeactivation = allowDeactivation;
    }

    //-----------------------------------------------------------------------
    //                       ~ T M o t i o n S t a t e
    //-----------------------------------------------------------------------
    TMotionState::~TMotionState() 
    {
    }

    //-----------------------------------------------------------------------
    //                 d e a c t i v a t i o n C a l l b a c k
    //-----------------------------------------------------------------------
    bool TMotionState::deactivationCallback(void*	userPointer)
    {

        return m_allowDeactivation;
    }


}



