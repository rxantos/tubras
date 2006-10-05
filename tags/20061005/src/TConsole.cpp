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
    //                           T C o n s o l e
    //-----------------------------------------------------------------------
    TConsole::TConsole(TWindow* parent, string widgetName, string caption) : TFrameWindow(parent,
        widgetName,caption)
    {
        setSize(0.5,0.4);
        setPosition(0,0);
        getWidget()->setAlwaysOnTop(true);
        getWidget()->setText("Command Console");

        ((CEGUI::FrameWindow*)getWidget())->setCloseButtonEnabled(false);
        ((CEGUI::FrameWindow*)getWidget())->setFrameEnabled(false);
        //((CEGUI::FrameWindow*)getWidget())->setAlpha(0.65);

        m_list = new TListBox(this,"console-list");
        m_list->setSize(1,0.8);
        m_list->setPosition(0,0.1);
        //m_list->getWidget()->setAlpha(0.5);

        m_edit = new TEditBox(this,"console-edit");
        m_edit->setSize(1,0.1);
        m_edit->setPosition(0.0,0.9);
        m_edit->subscribeEvent(esTextAccepted);
        subscribeEvent(esKeyDown);

        acceptEvent("gui.console-edit_textaccepted", EVENT_DELEGATE(TConsole::textAccepted));
        acceptEvent("console.hide",EVENT_DELEGATE(TConsole::hideConsole));

    }

    //-----------------------------------------------------------------------
    //                           ~T C o n s o l e
    //-----------------------------------------------------------------------
    TConsole::~TConsole()
    {
    }

    //-----------------------------------------------------------------------
    //                           h i d e C o n s o l e
    //-----------------------------------------------------------------------
    int TConsole::hideConsole(TSEvent event)
    {
        if(getWidget()->isVisible())
            toggle();

        return 1;
    }

    //-----------------------------------------------------------------------
    //                        t e x t A c c e p t e d
    //-----------------------------------------------------------------------
    int TConsole::textAccepted(TSEvent event)
    {
        string text = m_edit->getWidget()->getText().c_str();
        if(text.empty())
            return 1;

        m_list->addTextItem(text);

        TSEvent cevent;
        cevent.bind(new TEvent("console.command"));
        cevent->addStringParameter(text);
        sendEvent(cevent);

        m_edit->getWidget()->setText("");

        return 1;
    }

    //-----------------------------------------------------------------------
    //                             a d d T e x t
    //-----------------------------------------------------------------------
    void TConsole::addText(string text)
    {
        m_list->addTextItem(text);
    }

    //-----------------------------------------------------------------------
    //                        h a n d l e K e y D o w n
    //-----------------------------------------------------------------------
    bool TConsole::handleKeyDown(const CEGUI::EventArgs& event)
    {
        CEGUI::KeyEventArgs& key = (CEGUI::KeyEventArgs&) event;
        if(key.scancode == CEGUI::Key::Escape)
        {
            TSEvent event;
            event.bind(new TEvent("console.hide"));
            queueEvent(event);
            return true;

        }

        return false;
    }



    //-----------------------------------------------------------------------
    //                            t o g g l e
    //-----------------------------------------------------------------------
    void TConsole::toggle()
    {
        if(getWidget()->isVisible())
        {
            setVisible(false);
            getWidget()->deactivate();
            getApplication()->getInputManager()->setGUIExclusive(false);
            m_edit->getWidget()->setEnabled(false);
        }
        else 
        {
            setVisible(true);
            m_edit->getWidget()->setEnabled(true);
            getWidget()->moveToFront();
            getWidget()->activate();
            getApplication()->getInputManager()->setGUIExclusive(true);
            m_edit->getWidget()->activate();
        }

    }
}
