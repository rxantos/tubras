//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                          T T e x t O v e r l a y
    //-----------------------------------------------------------------------
    TTextOverlay::TTextOverlay(TString name, TRect dims, TColour overlayColor)
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
    void TTextOverlay::addItem(TString text,TTextAlignment a)
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
    void TTextOverlay::updateItem(s32 index,TString text)
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
