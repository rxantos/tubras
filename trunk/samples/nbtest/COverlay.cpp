//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "main.h"

//-----------------------------------------------------------------------
//                          C O v e r l a y
//-----------------------------------------------------------------------
COverlay::COverlay(stringc name, rectf dims, SColor colour)
{
    m_name = name;
    m_dims = dims;
    m_panel = getGUI()->addStaticText(L"",rect<s32>(0,0,0,0));
    setColour(colour);

    m_panel->setRelativePosition(dims);
}

//-----------------------------------------------------------------------
//                         s e t V i s i b l e
//-----------------------------------------------------------------------
void COverlay::setVisible(bool value)
{
    m_panel->setVisible(value);
}

//-----------------------------------------------------------------------
//                         g e t V i s i b l e
//-----------------------------------------------------------------------
bool COverlay::getVisible()
{
    return m_panel->isVisible();
}

//-----------------------------------------------------------------------
//                          s e t C o l o u r
//-----------------------------------------------------------------------
void COverlay::setColour(SColor colour)
{
    m_colour = colour;
    m_panel->setBackgroundColor(colour);
}

//-----------------------------------------------------------------------
//                          s e t A l p h a 
//-----------------------------------------------------------------------
void COverlay::setAlpha(float alpha)
{
    SColor c = m_colour;
    c.setAlpha((u32)(255.f * alpha));
    setColour(c);
}

//-----------------------------------------------------------------------
//                   s e t R e l a t i v e P o s i t i o n 
//-----------------------------------------------------------------------
void COverlay::setRelativePosition(rectf dims)
{
    m_panel->setRelativePosition(dims);
}

