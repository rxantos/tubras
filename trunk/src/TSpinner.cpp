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
    //                           T S p i n n e r
    //-----------------------------------------------------------------------
    TSpinner::TSpinner(TWindow* parent, string widgetName, string text, string font) :  TWindow(parent,
        widgetName,"Spinner",text,font)
    {

    }

    //-----------------------------------------------------------------------
    //                          ~ T S p i n n e r
    //-----------------------------------------------------------------------
    TSpinner::~TSpinner()
    {
    }

    //-----------------------------------------------------------------------
    //                        s e t M a x i m u m V a l u e
    //-----------------------------------------------------------------------
    void TSpinner::setMaximumValue(float value)
    {
        ((CEGUI::Spinner*)getWidget())->setMaximumValue(value);
    }

    //-----------------------------------------------------------------------
    //                       s e t M i n i m u m V a l u e
    //-----------------------------------------------------------------------
    void TSpinner::setMinimumValue(float value)
    {
        ((CEGUI::Spinner*)getWidget())->setMinimumValue(value);
    }

    //-----------------------------------------------------------------------
    //                       s e t C u r r e n t V a l u e
    //-----------------------------------------------------------------------
    void TSpinner::setCurrentValue(float value)
    {
        ((CEGUI::Spinner*)getWidget())->setCurrentValue(value);
    }

    //-----------------------------------------------------------------------
    //                       g e t C u r r e n t V a l u e
    //-----------------------------------------------------------------------
    float TSpinner::getCurrentValue(void)
    {
        return ((CEGUI::Spinner*)getWidget())->getCurrentValue();
    }

    //-----------------------------------------------------------------------
    //                         s e t S t e p S i z e
    //-----------------------------------------------------------------------
    void TSpinner::setStepSize(float value)
    {
        ((CEGUI::Spinner*)getWidget())->setStepSize(value);
    }

    //-----------------------------------------------------------------------
    //                         g e t S t e p S i z e
    //-----------------------------------------------------------------------
    float TSpinner::getStepSize()
    {
        return ((CEGUI::Spinner*)getWidget())->getStepSize();
    }

    //-----------------------------------------------------------------------
    //                     s e t T e x t I n p u t M o d e
    //-----------------------------------------------------------------------
    void TSpinner::setTextInputMode(TextInputMode mode)
    {
        CEGUI::Spinner::TextInputMode ceMode;

        switch(mode)
        {
        case timFloatingPoint:
            ceMode = CEGUI::Spinner::FloatingPoint;
            break;
        case timInteger:
            ceMode = CEGUI::Spinner::Integer;
            break;
        case timHexadecimal:
            ceMode = CEGUI::Spinner::Hexadecimal;
            break;
        case timOctal:
            ceMode = CEGUI::Spinner::Octal;
            break;
        default:
            ceMode = CEGUI::Spinner::Integer;
            break;
        };
        ((CEGUI::Spinner*)getWidget())->setTextInputMode(ceMode);
    }





}
