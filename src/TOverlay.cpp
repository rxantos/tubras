//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                          T O v e r l a y
    //-----------------------------------------------------------------------
    TOverlay::TOverlay(TString name, TRectf dims, TColor color) : TDelegate()
    {


        m_name = name;
        m_dims = dims;
        m_panel = getApplication()->getGUIManager()->addStaticText(L"",rect<s32>(0,0,0,0));
        setColor(color);

        m_panel->setRelativePositionProportional(dims);

    }

    //-----------------------------------------------------------------------
    //                         ~ T O v e r l a y 
    //-----------------------------------------------------------------------
    TOverlay::~TOverlay()
    {

    }

    //-----------------------------------------------------------------------
    //                         s e t V i s i b l e
    //-----------------------------------------------------------------------
    void TOverlay::setVisible(bool value)
    {
        m_panel->setVisible(value);
    }

    //-----------------------------------------------------------------------
    //                         g e t V i s i b l e
    //-----------------------------------------------------------------------
    bool TOverlay::getVisible()
    {
        return m_panel->isVisible();
    }

    //-----------------------------------------------------------------------
    //                           s e t C o l o r
    //-----------------------------------------------------------------------
    void TOverlay::setColor(TColor color)
    {
        m_color = color;
        m_panel->setBackgroundColor(color);
    }

    //-----------------------------------------------------------------------
    //                          s e t A l p h a 
    //-----------------------------------------------------------------------
    void TOverlay::setAlpha(float alpha)
    {
        TColor c = m_color;
        c.setAlpha((u32)(255.f * alpha));
        setColor(c);
    }

    //-----------------------------------------------------------------------
    //                   s e t R e l a t i v e P o s i t i o n 
    //-----------------------------------------------------------------------
    void TOverlay::setRelativePosition(TRectf dims)
    {
        m_panel->setRelativePositionProportional(dims);

    }
}

