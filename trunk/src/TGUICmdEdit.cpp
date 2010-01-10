//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T G U I C m d E d i t
    //-----------------------------------------------------------------------
    TGUICmdEdit::TGUICmdEdit(const wchar_t* text, bool border, 
        IGUIEnvironment* environment, IGUIElement* parent, s32 id, 
        const core::rect<s32>& rectangle) : CGUIEditBox(text, 
        border, environment, parent, id, rectangle)
    {
    }

    //-----------------------------------------------------------------------
    //                      ~ T G U I C m d E d i t
    //-----------------------------------------------------------------------
    TGUICmdEdit::~TGUICmdEdit()
    {
    }

    //-----------------------------------------------------------------------
    //                         p a r s e E v e n t
    //-----------------------------------------------------------------------
    void TGUICmdEdit::parseEvent(core::stringw cmd, TEvent& event)
    {
        core::stringc ccmd = cmd;
        const irr::c8* p=ccmd.c_str();
        core::stringc parm="";

        while(*p)
        {
            if( (*p == ' ') || (*p == ','))
            {
                event.addStringParameter(parm);
                parm = "";
            }
            else parm += *p;

            ++p;
        }
        if(parm.size())
            event.addStringParameter(parm);
    }

    //-----------------------------------------------------------------------
    //                           O n E v e n t
    //-----------------------------------------------------------------------
    bool TGUICmdEdit::OnEvent(const SEvent& event)
    {
        TEvent tevent("console.cmd");

        if (IsEnabled && event.EventType == EET_KEY_INPUT_EVENT)
        {
            if((event.KeyInput.Key == KEY_RETURN) && event.KeyInput.PressedDown)
            {
                core::stringw text = this->getText();
                if(text.size())
                {
                    parseEvent(text, tevent);
                    getApplication()->getEventManager()->send(&tevent);
                    this->setText(L"");
                    return true;
                }
            }
        }


        bool result = CGUIEditBox::OnEvent(event);

        return result;
    }


}
