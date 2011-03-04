//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TGUIMAINMENU_H_
#define _TGUIMAINMENU_H_

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                      T G U I M a i n M e n u
    //-----------------------------------------------------------------------
    class TGUIMainMenu : public IReferenceCounted
    {
    private:
        gui::IGUIContextMenu*       m_mainMenu;

    public:
        TGUIMainMenu(IGUIEnvironment* environment, IGUIElement* parent);
        virtual ~TGUIMainMenu();

        //! called if an event happened.
        virtual bool OnEvent(const SEvent& event);

        void setVisible(bool visible);

        void clear();
    };

}

#endif
