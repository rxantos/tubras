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
    //                          T T e x t O v e r l a y
    //-----------------------------------------------------------------------
    TTextOverlay::TTextOverlay(const TString& name, TRect dims, TColour overlayColor)
        : TOverlay(name,dims,overlayColor)
    {

        m_margins.Width = 5;
        m_margins.Height = 5;

    }

    //-----------------------------------------------------------------------
    //                         ~ T T e x t O v e r l a y
    //-----------------------------------------------------------------------
    TTextOverlay::~TTextOverlay()
    {
    }

    //-----------------------------------------------------------------------
    //                              a d d I t e m
    //-----------------------------------------------------------------------
    void TTextOverlay::addItem(const TString& text,TTextAlignment a)
    {
        
        s32 offset = 0;
        int idx;
        IGUIFont* font=m_panel->getOverrideFont();
        if(!font)
            font = getGUIManager()->getSkin()->getFont();

        TRectd apos = m_panel->getAbsolutePosition();

        idx = (int)m_textItems.size();
        TStrStream name;		
        name << m_name.c_str() << "-item" << idx+1;

        TStringW wstr = text.c_str();

        s32 cheight = font->getDimension(L"Ay").Height;
        cheight += font->getKerningHeight();

        TRectd tdim(0,0,apos.getWidth(),cheight);
        
        TTextElement* textArea = getGUIManager()->addStaticText(wstr.c_str(),tdim,false,false,m_panel);
        textArea->move(position2di(0,cheight*idx));
        textArea->setOverrideFont(font);


        offset = idx * (cheight);
        s32 theight = ((idx+1) * cheight) + (m_margins.Height * 2);

        EGUI_ALIGNMENT oa;

        switch(a)
        {
        case taLeft:
            oa = EGUIA_UPPERLEFT;
            break;
        case taCenter:
            oa = EGUIA_CENTER;
            break;
        case taRight:
            oa = EGUIA_LOWERRIGHT;
            break;
        };

        textArea->setTextAlignment(oa,EGUIA_UPPERLEFT);

        m_panel->addChild(textArea);
        m_textItems.push_back(textArea);

        if(apos.getHeight() < theight)     
        {
            m_panel->setMinSize(TDimensioni(0,theight));
        }
            

    }

    //-----------------------------------------------------------------------
    //                          u p d a t e I t e m
    //-----------------------------------------------------------------------
    void TTextOverlay::updateItem(s32 index, const TString& text)
    {
        if( (index < 0) || ((u32)index >= m_textItems.size()))
            return;

        TStringW wstr = text.c_str();
        m_textItems[index]->setText(wstr.c_str());
    }

    //-----------------------------------------------------------------------
    //                            s e t F o n t
    //-----------------------------------------------------------------------
    void TTextOverlay::setFont(IGUIFont* value)
    {
        m_panel->setOverrideFont(value);
    }

}
