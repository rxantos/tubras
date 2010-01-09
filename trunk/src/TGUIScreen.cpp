//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"
namespace Tubras
{
    TGUIScreen::TGUIScreen(s32 id): TDelegate(), IGUIElement(EGUIET_MODAL_SCREEN,
        getApplication()->getGUIManager(),
        getApplication()->getGUIManager()->getRootGUIElement(),id,
        getApplication()->getRenderer()->getScreenRect())
    {
        setVisible(false);
    }

    TGUIScreen::~TGUIScreen()
    {
    }
} 
