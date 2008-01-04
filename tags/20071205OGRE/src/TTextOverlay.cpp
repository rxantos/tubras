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
    TTextOverlay::TTextOverlay(TString name, TDim dims, 
        TString fontName, TColour fontColor, float fontSize,
        TColour overlayColor, float overlayAlpha, 
        TString overlayMaterialName) : TOverlay(name,dims,overlayColor, overlayAlpha,
        overlayMaterialName,true)
    {

        m_fontName = fontName;
        m_fontColor = fontColor;
        m_fontSize = fontSize;
        m_margins.w = 0.005;
        m_margins.h = 0.005;

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
        Ogre::TextAreaOverlayElement::Alignment oa;
        TDim pdim;
        float offset = 0.0;
        int idx;

        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

        pdim.x = m_panel->getLeft();
        pdim.y = m_panel->getTop();
        pdim.w = m_panel->getWidth();
        pdim.h = m_panel->getHeight();

        idx = (int)m_textItems.size();
        TStrStream name;		
        name << m_name << "-item" << idx+1;

        TTextElement* textArea = static_cast<TTextElement*>(
            overlayManager.createOverlayElement("TextArea", name.str()));
        textArea->setMetricsMode(Ogre::GMM_RELATIVE);
        textArea->setFontName(m_fontName);

        float cheight = textArea->getCharHeight();
        offset = idx * (cheight);
        float theight = ((idx+1) * cheight) + (m_margins.h * 2);


        switch(a)
        {
        case taLeft:
            oa = Ogre::TextAreaOverlayElement::Left;
            break;
        case taCenter:
            oa = Ogre::TextAreaOverlayElement::Center;
            break;
        case taRight:
            oa = Ogre::TextAreaOverlayElement::Right;
            break;
        };

        textArea->setAlignment(oa);

        if(a == taRight)
        {
            textArea->setPosition(pdim.w-m_margins.w, m_margins.h + offset );	
        }
        else if(a == taCenter)
        {
            textArea->setPosition((pdim.w / 2), m_margins.h + offset );	
        }
        else 
        {
            textArea->setPosition(m_margins.w, m_margins.h + offset );
        }

        textArea->setCaption(text);
        //textArea->setCharHeight(m_fontSize);
        textArea->setColourBottom(m_fontColor);
        textArea->setColourTop(m_fontColor);

        m_panel->addChild(textArea);
        m_textItems.push_back(textArea);

        if(m_panel->getHeight() < theight)
            m_panel->setHeight(theight);

    }

    //-----------------------------------------------------------------------
    //                          u p d a t e I t e m
    //-----------------------------------------------------------------------
    void TTextOverlay::updateItem(size_t index,TString text)
    {
        std::list<TTextElement*>::iterator itr = m_textItems.begin();
        size_t i = 0;

        while(i < index)
        {
            ++i;
            ++itr;
        }

        (*itr)->setCaption(text);

    }

}
