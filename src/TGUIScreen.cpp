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
    TGUIScreen::TGUIScreen(s32 id): TDelegate(), IGUIElement(EGUIET_MODAL_SCREEN,
        getApplication()->getGUIManager(),
        getApplication()->getGUIManager()->getRootGUIElement(),id,
        getApplication()->getRenderer()->getScreenRect())
    {
        setVisible(false);
    }

    TGUIScreen::~TGUIScreen()
    {
    }
} 
