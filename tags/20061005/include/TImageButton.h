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

#ifndef _TIMAGEBUTTON_H_
#define _TIMAGEBUTTON_H_

namespace Tubras
{

    class TImageButton : public TWindow
    {
    private:
        string                  m_imageFileName;
        CEGUI::Imageset*        m_imageset;
        TSound*                 m_rolloverSound;
        TSound*                 m_clickSound;

    protected:
        virtual bool handleMouseEnter(const CEGUI::EventArgs& event);
        virtual bool handleMouseDown(const CEGUI::EventArgs& event);
        virtual bool handleMouseClick(const CEGUI::EventArgs& event);

    public:
        TImageButton(TWindow* parent, string widgetName,string imageFileName);

        virtual ~TImageButton();
        virtual bool initialize(CEGUI::Window* parent, string widgetType, string widgetName);


    };

}

#endif