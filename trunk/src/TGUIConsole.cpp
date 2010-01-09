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

    TGUIConsole::TGUIConsole(IGUIEnvironment* environment, IGUIElement* parent,
            s32 id, core::rect<s32> rectangle, bool modal, bool centered, 
            bool draggable) : TGUIWindow(environment, parent, id, 
            rectangle, modal, centered, draggable)
    {
    }

    TGUIConsole::~TGUIConsole()
    {
    }

}
