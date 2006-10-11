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
#include "meshdlg.h"


TMeshDlg::TMeshDlg(TWindow* parent, std::vector<std::string> meshfiles) : TFrameWindow(parent,"MeshDlg","Open a Mesh")
{
    setSize(0.5,0.5);
    setPosition(0.1,0.1);
    setVisible(false);

    m_listBox = new TListBox(this,"meshLB");
    m_listBox->setSize(0.5,0.8);
    m_listBox->setPosition(0.05,0.12);
    for(int i=0;i<(int)meshfiles.size();i++)
    {
        m_listBox->addTextItem(meshfiles[i]);
    }

    subscribeEvent(esKeyDown);
    CEGUI::MouseCursor::getSingleton().hide();

    TButton* b = new TButton(this,"openButton","Open");
    b->setPosition(0.58,0.83);
    b->setSize(0.17,0.09);

    b = new TButton(this,"cancelButton","Cancel");
    b->setPosition(0.8,0.83);
    b->setSize(0.17,0.09);

    acceptEvent("gui.cancelButton.clicked",EVENT_DELEGATE(TMeshDlg::cancelClicked));
    acceptEvent("gui.openButton.clicked",EVENT_DELEGATE(TMeshDlg::openClicked));

}

int TMeshDlg::cancelClicked(TSEvent event)
{
    TSEvent e;
    e.bind(new TEvent("meshdlg.canceled"));
    getApplication()->queueEvent(e);

    return 1;
}

int TMeshDlg::openClicked(TSEvent event)
{
    TSEvent e;
    e.bind(new TEvent("meshdlg.open"));
    CEGUI::ListboxItem* item = m_listBox->getFirstSelectedItem();
    if(!item)
        return 1;

    e->addStringParameter(item->getText().c_str());
    getApplication()->queueEvent(e);

    return 1;
}

TMeshDlg::~TMeshDlg()
{
}

void TMeshDlg::show()
{
    setAlwaysOnTop(true);
    setVisible(true);
    activate();
    moveToFront();
    
    getApplication()->setGUIEnabled(true);
    getApplication()->setGUIExclusive(true);
    getApplication()->getGUISystem()->setMouseMoveScaling(1.2);
    getApplication()->getGUISystem()->injectMouseMove(0,0);
    int cx = getRenderEngine()->getRenderWindow()->getWidth() / 2;
    int cy = getRenderEngine()->getRenderWindow()->getHeight() / 2;
    CEGUI::MouseCursor::getSingleton().setPosition(CEGUI::Point(cx,cy));
    CEGUI::MouseCursor::getSingleton().show();
}

void TMeshDlg::hide()
{
    getApplication()->setGUIExclusive(false);
    CEGUI::MouseCursor::getSingleton().hide();
    setVisible(false);

}

bool TMeshDlg::handleKeyDown(const CEGUI::EventArgs& event)
{
    CEGUI::KeyEventArgs& key = (CEGUI::KeyEventArgs&) event;
    if(key.scancode == CEGUI::Key::Escape)
    {
        TSEvent e;
        e.bind(new TEvent("meshdlg.canceled"));
        getApplication()->queueEvent(e);

        return true;
    }
    return false;
}

