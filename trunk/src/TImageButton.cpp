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
    TImageButton::TImageButton(TWindow* parent, string widgetName,
        string imageFileName) : m_imageFileName(imageFileName), 
        TWindow(parent,widgetName,"ImageButton")
    {
        Ogre::Image image;
        image.load(m_imageFileName,"General");
        size_t width = image.getWidth();
        size_t height = image.getHeight() / 4;

        m_rolloverSound = loadSound("General", "GUI_rollover.ogg");
        m_clickSound = loadSound("General", "GUI_click.ogg");

        //
        // imageset setup
        //
        TStrStream imagesetName;
        imagesetName << getWidgetName() << "_imageset";

        m_imageset = CEGUI::ImagesetManager::getSingleton().createImagesetFromImageFile(imagesetName.str(), 
                            m_imageFileName);
        m_imageset->defineImage("ButtonUp",
            CEGUI::Point(1,1),
            CEGUI::Size( width, height ),
            CEGUI::Point(0.0f,0.0f)); 
        m_imageset->defineImage("ButtonHover",
            CEGUI::Point(1,height),
            CEGUI::Size( width, height ),
            CEGUI::Point(0.0f,0.0f));
        m_imageset->defineImage("ButtonDown",
            CEGUI::Point(1,height*2),
            CEGUI::Size( width, height ),
            CEGUI::Point(0.0f,0.0f));
        m_imageset->defineImage("ButtonDisabled",
            CEGUI::Point(1,height*3),
            CEGUI::Size( width, height ),
            CEGUI::Point(0.0f,0.0f));

        TStrStream pv1,pv2,pv3,pv4;
        pv1 << "set:" << imagesetName.str() << " image:ButtonUp";
        getWidget()->setProperty("NormalImage", pv1.str()); 

        pv2 << "set:" << imagesetName.str() << " image:ButtonHover";
        getWidget()->setProperty("HoverImage", pv2.str());

        pv3 << "set:" << imagesetName.str() << " image:ButtonDown";
        getWidget()->setProperty("PushedImage", pv3.str());

        pv4 << "set:" << imagesetName.str() << " image:ButtonDisabled";
        getWidget()->setProperty("DisabledImage", pv4.str());

        subscribeEvent(esAllMouse);

    }

    TImageButton::~TImageButton()
    {
        if(m_clickSound)
            delete m_clickSound;
        if(m_rolloverSound)
            delete m_rolloverSound;
    }

    bool TImageButton::initialize(CEGUI::Window* parent, string widgetType, string widgetName)
    {

        return true;
    }

    bool TImageButton::handleMouseEnter(const CEGUI::EventArgs& event)
    {
        TWindow::handleMouseEnter(event);
        m_rolloverSound->play();
        return true;
    }

    bool TImageButton::handleMouseDown(const CEGUI::EventArgs& event)
    {
        TWindow::handleMouseDown(event);
        m_clickSound->play();
        return true;
    }

    bool TImageButton::handleMouseClick(const CEGUI::EventArgs& event)
    {
        TWindow::handleMouseClick(event);
        return true;
    }
}