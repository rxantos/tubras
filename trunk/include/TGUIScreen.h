//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TGUISCREEN_H_
#define _TGUISCREEN_H_

namespace Tubras
{
    class TGUIScreen : public TDelegate, public IGUIElement
    {
    public:
        TGUIScreen(s32 id=-1);
        virtual ~TGUIScreen();
    };
} 
#endif
