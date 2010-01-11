//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                          T G U I C o n s o l e
    //-----------------------------------------------------------------------

    TGUIConsole::TGUIConsole(IGUIEnvironment* environment, 
        IGUIElement* parent, s32 id, core::rect<s32> rectangle, bool modal, 
        bool centered,  bool draggable) : TGUIWindow(environment, parent, id, 
        rectangle, modal, centered, draggable)
    {
        TRecti rect(16, 30, rectangle.getWidth()-20, rectangle.getHeight()-52);
        TRecti erect(20, rectangle.getHeight()-50, rectangle.getWidth()-20, rectangle.getHeight()-25);

        m_listBox = environment->addListBox(rect, this);
        m_listBox->setAutoScrollEnabled(true);
        m_listBox->setTabStop(false);

        m_editBox = new TGUICmdEdit(L"", true, environment, this, -1, erect);
        m_editBox->setOverrideColor(SColor(0xFFFFFFFF));
        addText("Console v0.1 - Enter \"help\" for a list of available commands.");

        setVisible(false);
    }

    //-----------------------------------------------------------------------
    //                         ~ T G U I C o n s o l e
    //-----------------------------------------------------------------------
    TGUIConsole::~TGUIConsole()
    {
    }

    //-----------------------------------------------------------------------
    //                           s e t V i s i b l e
    //-----------------------------------------------------------------------
    void TGUIConsole::setVisible(bool visible)
    {
        TGUIWindow::setVisible(visible);   
        if(visible)
            getApplication()->getGUIManager()->setFocus(m_editBox);
    }

    //-----------------------------------------------------------------------
    //                             O n E v e n t
    //-----------------------------------------------------------------------
    bool TGUIConsole::OnEvent(const SEvent& event)
    {        
        bool result = TGUIWindow::OnEvent(event);

        return result;
    }

    //-----------------------------------------------------------------------
    //                            a d d T e x t
    //-----------------------------------------------------------------------
    s32 TGUIConsole::addText(core::stringw text)
    {
        s32 result = m_listBox->addItem(text.c_str());
        m_listBox->setItemOverrideColor(m_listBox->getItemCount()-1, SColor(0xFFFFFFFF));
        m_listBox->setSelected(m_listBox->getItemCount()-1);
        return result;
    }

}
