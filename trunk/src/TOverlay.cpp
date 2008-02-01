//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                          T O v e r l a y
    //-----------------------------------------------------------------------
    TOverlay::TOverlay(TString name, TRect dims, TColour colour) : TObject()
    {


        m_name = name;
        m_dims = dims;
        m_panel = getGUIManager()->addStaticText(L"",rect<s32>(0,0,0,0));
        setColour(colour);

        m_panel->setRelativePosition(dims);

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
    //                          s e t C o l o u r
    //-----------------------------------------------------------------------
    void TOverlay::setColour(TColour colour)
    {
        m_colour = colour;
        m_panel->setBackgroundColor(colour);
    }

    //-----------------------------------------------------------------------
    //                          s e t A l p h a 
    //-----------------------------------------------------------------------
    void TOverlay::setAlpha(float alpha)
    {
        TColour c = m_colour;
        c.setAlpha((u32)(255.f * alpha));
        setColour(c);
    }

    //-----------------------------------------------------------------------
    //                   s e t R e l a t i v e P o s i t i o n 
    //-----------------------------------------------------------------------
    void TOverlay::setRelativePosition(TRect dims)
    {
        m_panel->setRelativePosition(dims);

    }
}

