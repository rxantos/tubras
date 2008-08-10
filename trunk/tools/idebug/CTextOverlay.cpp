//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "idebug.h"


//-----------------------------------------------------------------------
//                          T T e x t O v e r l a y
//-----------------------------------------------------------------------
CTextOverlay::CTextOverlay(const stringc& name, rectf dims, SColor overlayColor)
: COverlay(name,dims,overlayColor)
{

    m_margins.Width = 5;
    m_margins.Height = 5;

}

//-----------------------------------------------------------------------
//                              a d d I t e m
//-----------------------------------------------------------------------
void CTextOverlay::addItem(const stringc& text,EGUI_ALIGNMENT a)
{

    s32 offset = 0;
    int idx;
    IGUIFont* font=m_panel->getOverrideFont();
    if(!font)
        font = getGUI()->getSkin()->getFont();

    rectd apos = m_panel->getAbsolutePosition();

    idx = (int)m_textItems.size();
    StrStream name;		
    name << m_name.c_str() << "-item" << idx+1;

    stringw wstr = text.c_str();

    s32 cheight = font->getDimension(L"Ay").Height;
    cheight += font->getKerningHeight();

    rectd tdim(0,0,apos.getWidth(),cheight);

    IGUIStaticText* textArea = getGUI()->addStaticText(wstr.c_str(),tdim,false,false,0);
    textArea->move(position2di(0,cheight*idx));
    //textArea->setOverrideFont(font);
    textArea->setOverrideColor(SColor(255,255,255,255));


    offset = idx * (cheight);
    s32 theight = ((idx+1) * cheight) + (m_margins.Height * 2);

    textArea->setTextAlignment(a,EGUIA_UPPERLEFT);

    m_panel->addChild(textArea);
    m_textItems.push_back(textArea);

    if(apos.getHeight() < theight)     
    {
        m_panel->setMinSize(dimension2di(0,theight));
    }
}

//-----------------------------------------------------------------------
//                          u p d a t e I t e m
//-----------------------------------------------------------------------
void CTextOverlay::updateItem(s32 index, const stringc& text)
{
    if( (index < 0) || ((u32)index >= m_textItems.size()))
        return;

    stringw wstr = text.c_str();
    m_textItems[index]->setText(wstr.c_str());
}

//-----------------------------------------------------------------------
//                            s e t F o n t
//-----------------------------------------------------------------------
void CTextOverlay::setFont(IGUIFont* value)
{
    m_panel->setOverrideFont(value);
}
