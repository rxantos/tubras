//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TGUICMDEDIT_H_
#define _TGUICMDEDIT_H_

namespace Tubras
{
    class TGUICmdEdit : public gui::CGUIEditBox
    {
    private:
        core::array<stringw>    m_history;
        s32                     m_historyIdx;
    protected:
        void parseEvent(core::stringw cmd, TEvent& event);

    public:
        //! constructor
        TGUICmdEdit(const wchar_t* text, bool border, 
            IGUIEnvironment* environment, IGUIElement* parent, s32 id, 
            const core::rect<s32>& rectangle);

        //! destructor
        virtual ~TGUICmdEdit();

        //! called if an event happened.
       virtual bool OnEvent(const SEvent& event);
       void showHistory(const s32 direction);

    };

}
#endif

