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
    //                          T O v e r l a y
    //-----------------------------------------------------------------------
    TOverlay::TOverlay(TString name, TRect dims, TColor color) : TObject()
    {


        m_name = name;
        m_dims = dims;
        m_panel = getGUIManager()->addStaticText(L"",rect<s32>(0,0,0,0));
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
    void TOverlay::setRelativePosition(TRect dims)
    {
        m_panel->setRelativePositionProportional(dims);

    }
}

