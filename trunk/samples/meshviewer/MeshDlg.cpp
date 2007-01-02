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


TMeshDlg::TMeshDlg(TGUI::TGScreen* parent, std::vector<std::string> meshfiles) : TGUI::TGWindow(parent,"MeshDlg","Open a Mesh")
{
    setSize(0.6f,0.5f);
    setPos(0.25f,0.25f);
    setVisible(false);

    m_listBox = new TGUI::TGListBox(this,"meshLB");
    m_listBox->setSize(0.5f,0.8f);
    m_listBox->setPos(0.05f,0.12f);
    for(int i=0;i<(int)meshfiles.size();i++)
    {
        m_listBox->addItem(meshfiles[i]);
    }


    TGUI::TGButton* b = new TGUI::TGButton(this,"openButton","Open");
    b->setPos(0.58f,0.83f);
    b->setSize(0.17f,0.09f);
    TGUI::TGEventHandler* eh = new TGUI::TGEventHandler(&TMeshDlg::openClicked,this);
    b->addEventHandler("mouseClicked",TGEVENT_HANDLER(TMeshDlg::openClicked));

    b = new TGUI::TGButton(this,"cancelButton","Cancel");
    b->setPos(0.8f,0.83f);
    b->setSize(0.17f,0.09f);
    b->addEventHandler("mouseClicked",TGEVENT_HANDLER(TMeshDlg::cancelClicked));


    TGUI::TGLabel* t = new TGUI::TGLabel(this,"textScale","Initial Scale: ");
    t->setPos(0.58f,0.25f);
    t->setSize(0.2f,0.1f);

    m_scale = new TGUI::TGSpinEdit(this,"scaleSpinner");
    m_scale->setPos(0.8f,0.25f);
    m_scale->setSize(0.14f,0.1f);
    m_scale->setMinimumValue(0.001);
    m_scale->setMaximumValue(100.0);
    m_scale->setIncrementValue(0.05);
    m_scale->setCurrentValue(1.0);

}

bool TMeshDlg::cancelClicked(const TGUI::TGEventArgs& event)
{
    TSEvent e;
    e.bind(new TEvent("meshdlg.canceled"));
    getApplication()->queueEvent(e);

    return 1;
}

bool TMeshDlg::openClicked(const TGUI::TGEventArgs& event)
{
    TSEvent e;
    e.bind(new TEvent("meshdlg.open"));
    TGUI::TGListBoxItem* item = m_listBox->getSelectedItem();

    if(!item)
        return 1;

    e->addStringParameter(item->getText().c_str());
    e->addDoubleParameter(m_scale->getCurrentValue());
    getApplication()->queueEvent(e);

    return 1;
}

TMeshDlg::~TMeshDlg()
{
}

void TMeshDlg::show()
{
    TGWindow::show();
    makeExclusive();
    TGUI::TGSystem::getSingleton().setKeyboardFocusControl(this);

    m_scale->setCurrentValue(1.0);
    getApplication()->setGUIEnabled(true);
    getApplication()->setGUIExclusive(true);
    TGUI::TGSystem::getSingleton().getMouseCursor()->center();
    TGUI::TGSystem::getSingleton().getMouseCursor()->show();

}

void TMeshDlg::hide()
{
    TGWindow::hide();
    makeExclusive(false);
    TGUI::TGSystem::getSingleton().setKeyboardFocusControl(NULL);

    getApplication()->setGUIExclusive(false);
    TGUI::TGSystem::getSingleton().getMouseCursor()->hide();
}

void TMeshDlg::onKeyUp(int key, unsigned char ascii)
{
    if(key == 27)
    {
        TSEvent e;
        e.bind(new TEvent("meshdlg.canceled"));
        getApplication()->queueEvent(e);

    }
    return;
}

