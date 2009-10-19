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
    //                          T T e x t O v e r l a y
    //-----------------------------------------------------------------------
    TTextOverlay::TTextOverlay(const TString& name, TRectf dims, TColor overlayColor)
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
    u32 TTextOverlay::addItem(const TString& text,TTextAlignment a, TColor color,
        TColor bgColor)
    {

        s32 offset = 0;
        int idx;
        IGUIEnvironment* gmgr = getApplication()->getGUIManager();
        IGUIFont* font=m_panel->getOverrideFont();
        if(!font)
            font = gmgr->getSkin()->getFont();

        TRecti apos = m_panel->getAbsolutePosition();

        idx = (int)m_textItems.size();
        TStrStream name;		
        name << m_name.c_str() << "-item" << idx+1;

        TStringW wstr = text.c_str();

        s32 cheight = font->getDimension(L"Ay").Height;
        cheight += font->getKerningHeight();

        TRecti tdim(0,0,apos.getWidth(),cheight);
        
        TTextElement* textArea = gmgr->addStaticText(wstr.c_str(),tdim,false,false,m_panel);
        textArea->move(position2di(0,cheight*idx));
        textArea->setOverrideFont(font);
        textArea->setOverrideColor(color);
        textArea->setBackgroundColor(bgColor);

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
            m_panel->setMinSize(TDimensionu(0,theight));
        }

        return m_textItems.size()-1;
    }

    //-----------------------------------------------------------------------
    //                          u p d a t e I t e m
    //-----------------------------------------------------------------------
    void TTextOverlay::updateItem(s32 index, const TString& text, TColor color,
        TColor bgColor)
    {
        if( (index < 0) || ((u32)index >= m_textItems.size()))
            return;

        TStringW wstr = text.c_str();
        m_textItems[index]->setText(wstr.c_str());
        m_textItems[index]->setOverrideColor(color);
        m_textItems[index]->setBackgroundColor(bgColor);
    }

    //-----------------------------------------------------------------------
    //                            s e t F o n t
    //-----------------------------------------------------------------------
    void TTextOverlay::setFont(IGUIFont* value)
    {
        m_panel->setOverrideFont(value);
    }

}
