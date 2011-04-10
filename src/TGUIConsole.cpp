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
        rectangle, modal, centered, draggable),
        m_display(0),
        m_cmdEdit(0)
    {
        TRecti rect(16, 30, rectangle.getWidth()-20, rectangle.getHeight()-52);
        TRecti erect(20, rectangle.getHeight()-50, rectangle.getWidth()-20, rectangle.getHeight()-25);

        m_display = environment->addListBox(rect, this);
        m_display->setAutoScrollEnabled(true);
        m_display->setTabStop(false);

        m_cmdEdit = new TGUICmdEdit(L"", true, environment, this, -1, erect);
        m_cmdEdit->setOverrideColor(SColor(0xFFFFFFFF));
        addText("Console v0.1 - Enter \"help\" for a list of available commands.");

        setVisible(false);
    }

    //-----------------------------------------------------------------------
    //                         ~ T G U I C o n s o l e
    //-----------------------------------------------------------------------
    TGUIConsole::~TGUIConsole()
    {
        if(m_cmdEdit)
            m_cmdEdit->drop();
    }

    //-----------------------------------------------------------------------
    //                           s e t V i s i b l e
    //-----------------------------------------------------------------------
    void TGUIConsole::setVisible(bool visible)
    {
        TGUIWindow::setVisible(visible);   
        if(visible)
            getApplication()->getGUIManager()->setFocus(m_cmdEdit);
    }

    //-----------------------------------------------------------------------
    //                           c a n C l o s e
    //-----------------------------------------------------------------------
    bool TGUIConsole::canClose()
    {
        TEvent* event = new TEvent("tcon");
        getApplication()->queueEvent(event);
        return false;
    }

    //-----------------------------------------------------------------------
    //                             O n E v e n t
    //-----------------------------------------------------------------------
    bool TGUIConsole::OnEvent(const SEvent& event)
    {        
        if(TGUIWindow::OnEvent(event))
            return true;


        if(event.EventType == EET_KEY_INPUT_EVENT)
        {
            switch(event.KeyInput.Key)
            {
                case irr::KEY_UP:    
                    if(event.KeyInput.PressedDown)
                        m_cmdEdit->showHistory(-1);
                    return true;
                    break;
                case irr::KEY_DOWN:
                    if(event.KeyInput.PressedDown)
                        m_cmdEdit->showHistory(1);
                    return true;
                    break;
            };
        }

        return false;
    }

    //-----------------------------------------------------------------------
    //                              c l e a r
    //-----------------------------------------------------------------------
    void TGUIConsole::clear()
    {
        m_display->clear();
    }

    //-----------------------------------------------------------------------
    //                            a d d T e x t
    //-----------------------------------------------------------------------
    s32 TGUIConsole::addText(core::stringw text)
    {
        s32 result = m_display->addItem(text.c_str());
        m_display->setItemOverrideColor(m_display->getItemCount()-1, SColor(0xFFFFFFFF));
        m_display->setSelected(m_display->getItemCount()-1);
        return result;
    }

}
