//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TGUISKIN_H_
#define _TGUISKIN_H_

namespace Tubras
{
    class TGUISkin : public IGUISkin
    {
    private:
        IGUISkin*           m_defSkin;
        TString             m_skinName;
        TString             m_skinName2;
        ITexture*           m_guiTexture;
        ITexture*           m_guiTexture2;
        IVideoDriver*       m_driver;

    public:
        TGUISkin(TString skinName,TString skinName2);
        virtual ~TGUISkin();

        int initialize();

        //! returns default color
        video::SColor getColor(gui::EGUI_DEFAULT_COLOR color) const;

        //! sets a default color
        virtual void setColor(EGUI_DEFAULT_COLOR which, video::SColor newColor);

        //! returns size for the given size type
        virtual s32 getSize(EGUI_DEFAULT_SIZE size) const;

        //! Returns a default text. 
        /** For example for Message box button captions:
        "OK", "Cancel", "Yes", "No" and so on. */
        virtual const wchar_t* getDefaultText(EGUI_DEFAULT_TEXT text) const;

        //! Sets a default text.
        /** For example for Message box button captions:
        "OK", "Cancel", "Yes", "No" and so on. */
        virtual void setDefaultText(EGUI_DEFAULT_TEXT which, const wchar_t* newText);

        //! sets a default size
        virtual void setSize(EGUI_DEFAULT_SIZE which, s32 size);

        //! returns the default font
        virtual IGUIFont* getFont(EGUI_DEFAULT_FONT which=EGDF_DEFAULT) const;

        //! sets a default font
        virtual void setFont(IGUIFont* font, EGUI_DEFAULT_FONT which=EGDF_DEFAULT);

        //! returns the sprite bank
        virtual IGUISpriteBank* getSpriteBank() const;

        //! sets the sprite bank
        virtual void setSpriteBank(IGUISpriteBank* bank);

        //! Returns a default icon
        /** Returns the sprite index within the sprite bank */
        virtual u32 getIcon(EGUI_DEFAULT_ICON icon) const;

        //! Sets a default icon
        /** Sets the sprite index used for drawing icons like arrows, 
        close buttons and ticks in checkboxes 
        \param icon: Enum specifying which icon to change
        \param index: The sprite index used to draw this icon */
        virtual void setIcon(EGUI_DEFAULT_ICON icon, u32 index);

        //! draws a standard 3d button pane
        /**	Used for drawing for example buttons in normal state. 
        It uses the colors EGDC_3D_DARK_SHADOW, EGDC_3D_HIGH_LIGHT, EGDC_3D_SHADOW and
        EGDC_3D_FACE for this. See EGUI_DEFAULT_COLOR for details. 
        \param element: Pointer to the element which wishes to draw this. This parameter
        is usually not used by IGUISkin, but can be used for example by more complex 
        implementations to find out how to draw the part exactly. 
        \param rect: Defining area where to draw.
        \param clip: Clip area.	*/
        virtual void draw3DButtonPaneStandard(IGUIElement* element,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        virtual void draw3DButtonPaneHighlight(IGUIElement* element,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        //! draws a pressed 3d button pane
        /**	Used for drawing for example buttons in pressed state. 
        It uses the colors EGDC_3D_DARK_SHADOW, EGDC_3D_HIGH_LIGHT, EGDC_3D_SHADOW and
        EGDC_3D_FACE for this. See EGUI_DEFAULT_COLOR for details. 
        \param element: Pointer to the element which wishes to draw this. This parameter
        is usually not used by IGUISkin, but can be used for example by more complex 
        implementations to find out how to draw the part exactly. 
        \param rect: Defining area where to draw.
        \param clip: Clip area.	*/
        virtual void draw3DButtonPanePressed(IGUIElement* element, 
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        //! draws a sunken 3d pane
        /** Used for drawing the background of edit, combo or check boxes.
        \param element: Pointer to the element which wishes to draw this. This parameter
        is usually not used by IGUISkin, but can be used for example by more complex 
        implementations to find out how to draw the part exactly. 
        \param bgcolor: Background color.
        \param flat: Specifies if the sunken pane should be flat or displayed as sunken 
        deep into the ground.
        \param fillBackGround: Specifies if the background should be filled with the background
        color or not be drawn at all.
        \param rect: Defining area where to draw.
        \param clip: Clip area.	*/
        virtual void draw3DSunkenPane(IGUIElement* element,
            video::SColor bgcolor, bool flat, bool fillBackGround,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        //! draws a window background
        /** Used for drawing the background of dialogs and windows.
        \param element: Pointer to the element which wishes to draw this. This parameter
        is usually not used by IGUISkin, but can be used for example by more complex 
        implementations to find out how to draw the part exactly. 
        \param titleBarColor: Title color.
        \param drawTitleBar: True to enable title drawing.
        \param rect: Defining area where to draw.
        \param clip: Clip area.	
        \return Returns rect where it would be good to draw title bar text. */
        virtual core::rect<s32> draw3DWindowBackground(IGUIElement* element,
            bool drawTitleBar, video::SColor titleBarColor,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        //! draws a standard 3d menu pane
        /**	Used for drawing for menus and context menus. 
        It uses the colors EGDC_3D_DARK_SHADOW, EGDC_3D_HIGH_LIGHT, EGDC_3D_SHADOW and
        EGDC_3D_FACE for this. See EGUI_DEFAULT_COLOR for details. 
        \param element: Pointer to the element which wishes to draw this. This parameter
        is usually not used by IGUISkin, but can be used for example by more complex 
        implementations to find out how to draw the part exactly. 
        \param rect: Defining area where to draw.
        \param clip: Clip area.	*/
        virtual void draw3DMenuPane(IGUIElement* element,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        //! draws a standard 3d tool bar
        /**	Used for drawing for toolbars and menus.
        \param element: Pointer to the element which wishes to draw this. This parameter
        is usually not used by IGUISkin, but can be used for example by more complex 
        implementations to find out how to draw the part exactly. 
        \param rect: Defining area where to draw.
        \param clip: Clip area.	*/
        virtual void draw3DToolBar(IGUIElement* element,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        //! draws a tab button
        /**	Used for drawing for tab buttons on top of tabs.
        \param element: Pointer to the element which wishes to draw this. This parameter
        is usually not used by IGUISkin, but can be used for example by more complex 
        implementations to find out how to draw the part exactly. 
        \param active: Specifies if the tab is currently active.
        \param rect: Defining area where to draw.
        \param clip: Clip area.	*/
        virtual void draw3DTabButton(IGUIElement* element, bool active,
            const core::rect<s32>& rect, const core::rect<s32>* clip=0, gui::EGUI_ALIGNMENT alignment=EGUIA_UPPERLEFT);

        //! draws a tab control body
        /**	\param element: Pointer to the element which wishes to draw this. This parameter
        is usually not used by IGUISkin, but can be used for example by more complex 
        implementations to find out how to draw the part exactly. 
        \param border: Specifies if the border should be drawn.
        \param background: Specifies if the background should be drawn.
        \param rect: Defining area where to draw.
        \param clip: Clip area.	*/
        virtual void draw3DTabBody(IGUIElement* element, bool border, bool background,
            const core::rect<s32>& rect, const core::rect<s32>* clip=0, s32 tabHeight=-1, gui::EGUI_ALIGNMENT alignment=EGUIA_UPPERLEFT );

        //! draws an icon, usually from the skin's sprite bank
        /** \param element: Pointer to the element which wishes to draw this icon. 
        This parameter is usually not used by IGUISkin, but can be used for example 
        by more complex implementations to find out how to draw the part exactly. 
        \param icon: Specifies the icon to be drawn.
        \param position: The position to draw the icon
        \param starttime: The time at the start of the animation
        \param currenttime: The present time, used to calculate the frame number
        \param loop: Whether the animation should loop or not
        \param clip: Clip area.	*/
        virtual void drawIcon(IGUIElement* element, EGUI_DEFAULT_ICON icon,
            const core::position2di position, u32 starttime=0, u32 currenttime=0, 
            bool loop=false, const core::rect<s32>* clip=0);

        //! draws a 2d rectangle.
        /** \param element: Pointer to the element which wishes to draw this icon. 
        This parameter is usually not used by IGUISkin, but can be used for example 
        by more complex implementations to find out how to draw the part exactly. 
        \param color: Color of the rectangle to draw. The alpha component specifies how 
        transparent the rectangle will be.
        \param pos: Position of the rectangle.
        \param clip: Pointer to rectangle against which the rectangle will be clipped.
        If the pointer is null, no clipping will be performed. */
        virtual void draw2DRectangle(IGUIElement* element, const video::SColor &color, 
            const core::rect<s32>& pos, const core::rect<s32>* clip = 0);

    };
}
#endif
