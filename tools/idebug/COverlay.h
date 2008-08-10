//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _COVERLAY_H_
#define _COVERLAY_H_

    class COverlay 
    {
    protected:
        stringc                     m_name;
        rectf                       m_dims;
        SColor                      m_colour;
        IGUIStaticText*             m_panel;

    public:
        COverlay(stringc name,rectf dims, SColor colour=SColor(128,255,255,255));
        void setVisible(bool value);
        bool getVisible();
        void setColour(SColor colour);
        void setAlpha(float alpha);
        void setRelativePosition(rectf dims);
    };


#endif

