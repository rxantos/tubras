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
    TWindow::TWindow(TWindow* parent, string widgetName, string widgetType, 
        string text, string font) : TObject()
    {
        m_parent = parent;
        m_widgetName = widgetName;
        m_widgetType = widgetType;
        if(widgetType.compare("DefaultWindow"))
            m_widgetType = getApplication()->getGUIManager()->getLookName() + "/" + widgetType;

        TStrStream windowName;
        windowName << m_widgetName << "_window";

        CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
        m_widget = wmgr.createWindow(m_widgetType,windowName.str());
        if(m_parent)
            m_parent->getWidget()->addChildWindow(m_widget);

        if(!text.empty())
            setText(text);

        if(!font.empty())
            setFont(font);

        getApplication()->getGUIManager()->addWidget(this);
    }

    TWindow::~TWindow()
    {
        CEGUI::WindowManager::getSingleton().destroyWindow(m_widget);
    }


    void TWindow::setPosition(float x, float y)
    {
        m_widget->setPosition(CEGUI::UVector2(CEGUI::UDim(x,0), CEGUI::UDim(y,0)));
    }

    void TWindow::setSize(float w, float h)
    {
        m_widget->setSize( CEGUI::UVector2(CEGUI::UDim(w,0), CEGUI::UDim(h,0)));
    }

    void TWindow::setFrameEnabled(bool value)
    {
        string svalue;
        if(value)
            svalue = "true";
        else svalue = "false";
        m_widget->setProperty("FrameEnabled", svalue);
    }

    void TWindow::setBackgroundEnabled(bool value)
    {
        string svalue;
        if(value)
            svalue = "true";
        else svalue = "false";
        m_widget->setProperty("BackgroundEnabled", svalue);
    }

    void TWindow::setBackgroundImage(string imageFileName)
    {
        TStrStream imagesetName;
        imagesetName << m_widgetName << "_bg_imageset";

        CEGUI::Imageset* imageset = CEGUI::ImagesetManager::getSingleton().createImagesetFromImageFile
            (imagesetName.str(), imageFileName);

        TStrStream pvalue;

        pvalue << "set:" << imagesetName.str() << " image:full_image";
        m_widget->setProperty("Image", pvalue.str());
    }

    void TWindow::setText(string text)
    {
        m_widget->setText(text);
    }

    void TWindow::setFont(string font)
    {
        m_widget->setFont(font);
    }

    void TWindow::setHorzAlignment(THorzAlignment align)
    {
        string value;

        switch(align)
        {
        case horzCenter:
            value = "Centred";
            break;

        case horzRight:
            value = "RightAligned";
            break;
        default:
            value = "LeftAligned";
            break;
        }
        m_widget->setProperty("HorzFormatting",value);
    }

    void TWindow::setVisible(bool value)
    {
        m_widget->setVisible(value);
    }



    bool TWindow::handleMouseEnter(const CEGUI::EventArgs& event)
    {
        TStrStream msg;
        msg << "gui." << m_widgetName << "_enter";
        TSEvent tevent;
        tevent.bind(new TEvent(msg.str()));
        sendEvent(tevent);
        return true;
    }

    bool TWindow::handleMouseDown(const CEGUI::EventArgs& event)
    {
        TStrStream msg;
        msg << "gui." << m_widgetName << "_down";
        TSEvent tevent;
        tevent.bind(new TEvent(msg.str()));
        sendEvent(tevent);
        return true;
    }

    bool TWindow::handleTextAccepted(const CEGUI::EventArgs& event)
    {
        TStrStream msg;
        msg << "gui." << m_widgetName << "_textaccepted";
        TSEvent tevent;
        tevent.bind(new TEvent(msg.str()));
        sendEvent(tevent);
        return true;
    }

    bool TWindow::handleMouseClick(const CEGUI::EventArgs& event)
    {
        TStrStream msg;
        msg << "gui." << m_widgetName << "_clicked";
        TSEvent tevent;
        tevent.bind(new TEvent(msg.str()));
        sendEvent(tevent);
        return true;
    }

    bool TWindow::subscribeEvent(TEventSubscription whichEvent)
    {
        bool result = true;

        if(whichEvent == esAllMouse)
        {
            m_widget->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&TWindow::handleMouseEnter, this));
            m_widget->subscribeEvent(CEGUI::Window::EventMouseButtonDown, CEGUI::Event::Subscriber(&TWindow::handleMouseDown, this));
            m_widget->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&TWindow::handleMouseClick, this));       
            m_widget->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&TWindow::handleTextAccepted, this)); 
            m_widget->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&TWindow::handleKeyDown, this)); 
        }
        else if (whichEvent == esKeyDown)
        {
            m_widget->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&TWindow::handleKeyDown, this)); 
        }
        else if (whichEvent == esTextAccepted)
        {
            m_widget->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&TWindow::handleTextAccepted, this)); 
        }
        else if (whichEvent == esMouseDown)
        {
            m_widget->subscribeEvent(CEGUI::Window::EventMouseButtonDown, CEGUI::Event::Subscriber(&TWindow::handleMouseDown, this));
        }
        else if (whichEvent == esMouseEnter)
        {
            m_widget->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&TWindow::handleMouseEnter, this));
        }
        else if (whichEvent == esMouseClick)
        {
            m_widget->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&TWindow::handleMouseClick, this));       
        }

        return result;
    }

}