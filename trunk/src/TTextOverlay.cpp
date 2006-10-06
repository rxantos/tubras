//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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
    TTextOverlay::TTextOverlay(string name, TFloatRect dims, 
        string fontName, TColor fontColor, float fontSize,
        TColor overlayColor, float overlayAlpha, 
        string overlayMaterialName) : TOverlay(name,dims,overlayColor, overlayAlpha,
        overlayMaterialName,true)
    {

        m_fontName = fontName;
        m_fontColor = fontColor;
        m_fontSize = fontSize;

    }

    //-----------------------------------------------------------------------
    //                         ~ T T e x t O v e r l a y
    //-----------------------------------------------------------------------
    TTextOverlay::~TTextOverlay()
    {
    }

    //-----------------------------------------------------------------------
    //                              a d d L i n e
    //-----------------------------------------------------------------------
    void TTextOverlay::addItem(string text,TFloatRect dims,TTextAlignment a)
    {
        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

        

        TTextElement* textArea = static_cast<TTextElement*>(
            overlayManager.createOverlayElement("TextArea", "TextAreaName"));
        m_panel->addChild(textArea);
        textArea->setMetricsMode(Ogre::GMM_RELATIVE);
        textArea->setFontName(m_fontName);
        textArea->setAlignment(a);
        textArea->setPosition(0.25,0);
        textArea->setDimensions(1.0,1.0);
        textArea->setCaption(text);
        //textArea->setCharHeight(m_panel->getHeight());
        textArea->setColourBottom(m_fontColor);
        textArea->setColourTop(m_fontColor);




    }


}
