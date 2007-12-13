//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software Ltd
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