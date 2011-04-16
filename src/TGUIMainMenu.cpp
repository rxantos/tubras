//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T G U I M a i n M e n u
    //-----------------------------------------------------------------------
    TGUIMainMenu::TGUIMainMenu(IGUIEnvironment* environment, IGUIElement* parent)
    {
        m_mainMenu = environment->addMenu();

        parent->addChild(m_mainMenu);

        setVisible(false);
    }

    //-----------------------------------------------------------------------
    //                      ~ T G U I M a i n M e n u
    //-----------------------------------------------------------------------
    TGUIMainMenu::~TGUIMainMenu()
    {
    }

    //-----------------------------------------------------------------------
    //                          s e t V i s i b l e
    //-----------------------------------------------------------------------
    void TGUIMainMenu::setVisible(bool visible)
    {
        m_mainMenu->setVisible(visible);
    }

    //-----------------------------------------------------------------------
    //                             O n E v e n t
    //-----------------------------------------------------------------------
    bool TGUIMainMenu::OnEvent(const SEvent& event)
    {        

        return false;
    }

    //-----------------------------------------------------------------------
    //                              c l e a r
    //-----------------------------------------------------------------------
    void TGUIMainMenu::clear()
    {
    }
}
