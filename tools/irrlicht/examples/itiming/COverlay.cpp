//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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

    m_panel->setRelativePositionProportional(dims);
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
    m_panel->setRelativePositionProportional(dims);
}

