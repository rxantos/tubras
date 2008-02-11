//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TGUISCREEN_H_
#define _TGUISCREEN_H_

namespace Tubras
{
    class TGUIScreen : public TObject, public IGUIElement
    {
    public:
        TGUIScreen(s32 id=-1);
        virtual ~TGUIScreen();
    };
} 
#endif
