//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
// A modified version of Klasker's CImageGUISkin implemenation. 
//-----------------------------------------------------------------------------
#ifndef _TGUISKIN2_H_
#define _TGUISKIN2_H_

namespace Tubras
{

    struct TImageGUIElementStyle
    {
        TRectd          outer,inner;
        TRectd          ulc,urc,llc,lrc;
        u32             ulcw,urcw,llcw,lrcw;
        u32             ulch,urch,llch,lrch;
        u32             leftw,rightw,toph,bottomh;
        s32             minWidth,minHeight;
        TRectd          top,left,right,bottom;
        TRectd          client;
        bool            useOuter;
        bool            hasHilight;
        video::SColor   Color;

        TImageGUIElementStyle() : Color(255,255,255,255) {}
    };

    struct TGUISkinConfig
    {
        TImageGUIElementStyle SunkenPane, Window, Button, 
            ButtonPressed, ProgressBar, ProgressBarFilled, MenuBar;
    };

    class TGUISkin2 : public IGUISkin
    {
    private:
        IVideoDriver*       m_videoDriver;
        IGUISkin*           m_defSkin;
        TString             m_skinName;
        TGUISkinConfig      m_skinConfig;
        ITexture*           m_baseTex;
        ITexture*           m_baseTex2;
        ITexture*           m_hilightTex;
        ITexture*           m_hilightTex2;
        SColor              m_windowColor;
        SColor              m_dialogColor;

        void drawElementStyle( IGUIElement* element, const TImageGUIElementStyle& style, 
            const core::rect<s32>& rect, const core::rect<s32>* clip, const ITexture* texture=0, 
            video::SColor* color=0 );

    public:
        TGUISkin2(TString skinName);
        virtual ~TGUISkin2();

        int initialize();

        void loadConfig( const TGUISkinConfig& config );

        //! returns default color
        virtual video::SColor getColor(EGUI_DEFAULT_COLOR color) const;

        //! sets a default color
        virtual void setColor(EGUI_DEFAULT_COLOR which, video::SColor newColor);

        //! returns default color
        virtual s32 getSize(EGUI_DEFAULT_SIZE size) const;

        //! Returns a default text. 
        virtual const wchar_t* getDefaultText(EGUI_DEFAULT_TEXT text) const;

        //! Sets a default text.
        virtual void setDefaultText(EGUI_DEFAULT_TEXT which, const wchar_t* newText);

        //! sets a default size
        virtual void setSize(EGUI_DEFAULT_SIZE which, s32 size);

        //! returns the default font
        virtual IGUIFont* getFont(EGUI_DEFAULT_FONT defaultFont) const;

        //! sets a default font
        virtual void setFont(IGUIFont* font, EGUI_DEFAULT_FONT defaultFont);

        //! returns the sprite bank
        virtual IGUISpriteBank* getSpriteBank() const;

        //! sets the sprite bank
        virtual void setSpriteBank(IGUISpriteBank* bank);

        virtual u32 getIcon(EGUI_DEFAULT_ICON icon) const;

        virtual void setIcon(EGUI_DEFAULT_ICON icon, u32 index);

        virtual void draw3DButtonPaneStandard(IGUIElement* element,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        virtual void draw3DButtonPanePressed(IGUIElement* element, 
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        virtual void draw3DSunkenPane(IGUIElement* element,
            video::SColor bgcolor, bool flat, bool fillBackGround,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        virtual core::rect<s32> draw3DWindowBackground(IGUIElement* element,
            bool drawTitleBar, video::SColor titleBarColor,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        virtual void draw3DMenuPane(IGUIElement* element,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        virtual void draw3DToolBar(IGUIElement* element,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip=0);

        virtual void draw3DTabButton(IGUIElement* element, bool active,
            const core::rect<s32>& rect, const core::rect<s32>* clip=0, 
            gui::EGUI_ALIGNMENT alignment=EGUIA_UPPERLEFT);

        virtual void draw3DTabBody(IGUIElement* element, bool border, bool background,
            const core::rect<s32>& rect, const core::rect<s32>* clip=0, s32 tabHeight=-1, 
            gui::EGUI_ALIGNMENT alignment=EGUIA_UPPERLEFT );

        virtual void drawIcon(IGUIElement* element, EGUI_DEFAULT_ICON icon,
            const core::position2di position, u32 starttime=0, u32 currenttime=0, 
            bool loop=false, const core::rect<s32>* clip=0);



        virtual void drawHorizontalProgressBar( IGUIElement* element, const core::rect<s32>& rectangle, const core::rect<s32>* clip,
            f32 filledRatio, video::SColor fillColor );



        virtual void draw2DRectangle(IGUIElement* element, const video::SColor &color, 

            const core::rect<s32>& pos, const core::rect<s32>* clip = 0);

    };
}
#endif

