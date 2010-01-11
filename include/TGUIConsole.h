//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TGUICONSOLE_H_
#define _TGUICONSOLE_H_

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                          T G U I C o n s o l e
    //-----------------------------------------------------------------------
    class TGUIConsole : public TGUIWindow
    {
    private:
        IGUIListBox*        m_listBox;
        TGUICmdEdit*        m_editBox;

    public:
        TGUIConsole(IGUIEnvironment* environment, IGUIElement* parent,
            s32 id, core::rect<s32> rectangle,
            bool modal=false, bool centered=true, bool draggable=true);
        virtual ~TGUIConsole();

        //! called if an event happened.
        virtual bool OnEvent(const SEvent& event);

        s32 addText(core::stringw text);

        void setVisible(bool visible);
    };

}

#endif
