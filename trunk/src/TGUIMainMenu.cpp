//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    enum
    {
        GUI_ID_DIALOG_ROOT_WINDOW  = 0x10000,

        GUI_ID_X_SCALE,
        GUI_ID_Y_SCALE,
        GUI_ID_Z_SCALE,

        GUI_ID_OPEN_MODEL,
        GUI_ID_SET_MODEL_ARCHIVE,
        GUI_ID_LOAD_AS_OCTREE,

        GUI_ID_SKY_BOX_VISIBLE,
        GUI_ID_TOGGLE_DEBUG_INFO,

        GUI_ID_DEBUG_OFF,
        GUI_ID_DEBUG_BOUNDING_BOX,
        GUI_ID_DEBUG_NORMALS,
        GUI_ID_DEBUG_SKELETON,
        GUI_ID_DEBUG_WIRE_OVERLAY,
        GUI_ID_DEBUG_HALF_TRANSPARENT,
        GUI_ID_DEBUG_BUFFERS_BOUNDING_BOXES,
        GUI_ID_DEBUG_ALL,

        GUI_ID_MODEL_MATERIAL_SOLID,
        GUI_ID_MODEL_MATERIAL_TRANSPARENT,
        GUI_ID_MODEL_MATERIAL_REFLECTION,

        GUI_ID_CAMERA_MAYA,
        GUI_ID_CAMERA_FIRST_PERSON,

        GUI_ID_POSITION_TEXT,

        GUI_ID_ABOUT,
        GUI_ID_QUIT,

        GUI_ID_TEXTUREFILTER,
        GUI_ID_SKIN_TRANSPARENCY,
        GUI_ID_SKIN_ANIMATION_FPS,

        GUI_ID_BUTTON_SET_SCALE,
        GUI_ID_BUTTON_SCALE_MUL10,
        GUI_ID_BUTTON_SCALE_DIV10,
        GUI_ID_BUTTON_OPEN_MODEL,
        GUI_ID_BUTTON_SHOW_ABOUT,
        GUI_ID_BUTTON_SHOW_TOOLBOX,
        GUI_ID_BUTTON_SELECT_ARCHIVE,

        GUI_ID_ANIMATION_INFO,

        // And some magic numbers
        MAX_FRAMERATE = 80,
        DEFAULT_FRAMERATE = 30
    };

    //-----------------------------------------------------------------------
    //                       T G U I M a i n M e n u
    //-----------------------------------------------------------------------
    TGUIMainMenu::TGUIMainMenu(IGUIEnvironment* environment, IGUIElement* parent)
    {
        m_mainMenu = environment->addMenu();
        m_mainMenu->addItem(L"File", -1, true, true);
        m_mainMenu->addItem(L"View", -1, true, true);
        m_mainMenu->addItem(L"Camera", -1, true, true);
        m_mainMenu->addItem(L"Help", -1, true, true);


        gui::IGUIContextMenu* submenu;
        submenu = m_mainMenu->getSubMenu(0);
        submenu->addItem(L"Open Model File & Texture...", GUI_ID_OPEN_MODEL);
        submenu->addItem(L"Set Model Archive...", GUI_ID_SET_MODEL_ARCHIVE);
        submenu->addItem(L"Load as Octree", GUI_ID_LOAD_AS_OCTREE);
        submenu->addSeparator();
        submenu->addItem(L"Quit", GUI_ID_QUIT);


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
