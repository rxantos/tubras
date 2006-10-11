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

#ifndef _TWINDOW_H_
#define _TWINDOW_H_

namespace Tubras
{

    enum TEventSubscription
    {
        esMouseDown,
        esMouseUp,
        esMouseEnter,
        esMouseClick,
        esAllMouse,
        esAllKeyboard,
        esTextAccepted,
        esKeyDown,
        esAll
    };

    class TWindow : public TObject
    {
    public:
        enum THorzAlignment
        {
            horzLeft,
            horzRight,
            horzCenter
        };

    private:
        CEGUI::Window*          m_widget;
        TWindow*                m_parent;
        string                  m_widgetName;
        string                  m_widgetType;

    protected:
        virtual bool handleMouseEnter(const CEGUI::EventArgs& event);
        virtual bool handleMouseDown(const CEGUI::EventArgs& event);
        virtual bool handleMouseClick(const CEGUI::EventArgs& event);
        virtual bool handleTextAccepted(const CEGUI::EventArgs& event);
        virtual bool handleKeyDown(const CEGUI::EventArgs& event) {return false;};

    public:
        TWindow(TWindow* parent, string widgetName, string widgetType="DefaultWindow", 
            string text="", string font="");

        virtual ~TWindow();

        string getWidgetName() {return m_widgetName;};
        CEGUI::Window* getWidget() {return m_widget;};
        TWindow* getParent() {return m_parent;};

        bool subscribeEvent(TEventSubscription whichEvent);

        bool isVisible() {return m_widget->isVisible();};

        void setPosition(float x,float y);
        void setSize(float w, float h);
        void setBackgroundImage(string imageFileName);
        void setFrameEnabled(bool value);
        void setBackgroundEnabled(bool value);
        void setText(string text);
        void setFont(string font);
        void setHorzAlignment(THorzAlignment align);
        void setVisible(bool value);
        void setAlwaysOnTop(bool value);
        void activate();
        void moveToFront();


    };

}

#endif