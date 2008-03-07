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
#include "tubras.h"

namespace Tubras
{
    //! Workaround for a bug in IVideoDriver::draw2DImage( ITexture* tex, rect<s32> dstRect, 
    //! rect<s32> srcRect, rect<s32>* clip, SColor* colors, bool alpha )
    //! It modifies dstRect and srcRect so the resulting dstRect is entirely inside the clipping rect.
    //! srcRect is scaled so the same part of the image is displayed.
    //! Returns false if dstRect is entirely outside clip, or true if at least some of it is inside.
    inline bool clipRects( core::rect<s32>& dstRect, core::rect<s32>& srcRect, 
        const core::rect<s32>& clip )
    {
        // Clip left side
        if ( dstRect.UpperLeftCorner.X < clip.UpperLeftCorner.X )
        {
            s32 w = clip.UpperLeftCorner.X - dstRect.UpperLeftCorner.X;

            f32 percentRemoved = (f32)w / (f32)dstRect.getWidth();

            dstRect.UpperLeftCorner.X = clip.UpperLeftCorner.X;

            srcRect.UpperLeftCorner.X += (s32)(percentRemoved * srcRect.getWidth());
        }

        // Clip top side
        if ( dstRect.UpperLeftCorner.Y < clip.UpperLeftCorner.Y )
        {
            s32 w = clip.UpperLeftCorner.Y - dstRect.UpperLeftCorner.Y;

            f32 percentRemoved = (f32)w / (f32)dstRect.getHeight();

            dstRect.UpperLeftCorner.Y = clip.UpperLeftCorner.Y;

            srcRect.UpperLeftCorner.Y += (s32)(percentRemoved * srcRect.getHeight());
        }

        // Clip right side
        if ( dstRect.LowerRightCorner.X > clip.LowerRightCorner.X )
        {
            s32 w = dstRect.LowerRightCorner.X - clip.LowerRightCorner.X;

            f32 percentRemoved = (f32)w / (f32)dstRect.getWidth();

            dstRect.LowerRightCorner.X = clip.LowerRightCorner.X;

            srcRect.LowerRightCorner.X -= (s32)(percentRemoved * srcRect.getWidth());
        }

        // Clip bottom side
        if ( dstRect.LowerRightCorner.Y > clip.LowerRightCorner.Y )
        {
            s32 w = dstRect.LowerRightCorner.Y - clip.LowerRightCorner.Y;

            f32 percentRemoved = (f32)w / (f32)dstRect.getHeight();

            dstRect.LowerRightCorner.Y = clip.LowerRightCorner.Y;

            srcRect.LowerRightCorner.Y -= (s32)(percentRemoved * srcRect.getHeight());
        }

        return ( dstRect.getWidth() > 0 && dstRect.getHeight() > 0 );
    }


    //-----------------------------------------------------------------------
    //                            T G U I S k i n
    //-----------------------------------------------------------------------
    TGUISkin2::TGUISkin2( TString skinName ) : m_skinName(skinName)
    {
    }

    //-----------------------------------------------------------------------
    //                           ~ T G U I S k i n
    //-----------------------------------------------------------------------
    TGUISkin2::~TGUISkin2()
    {
        m_defSkin->drop();
    }

    //-----------------------------------------------------------------------
    //                           c a l c E l e m e n t
    //-----------------------------------------------------------------------
    static void calcElement(TImageGUIElementStyle& el)
    {
        el.ulcw = el.ulc.getWidth();
        el.ulch = el.ulc.getHeight();
        el.urcw = el.urc.getWidth();
        el.urch = el.urc.getHeight();
        el.llcw = el.llc.getWidth();
        el.llch = el.llc.getHeight();
        el.lrcw = el.lrc.getWidth();
        el.lrch = el.lrc.getHeight();
        el.leftw = el.left.getWidth();
        el.rightw = el.right.getWidth();
        el.toph = el.top.getHeight();
        el.bottomh = el.bottom.getHeight();

        el.client.UpperLeftCorner.X = el.left.UpperLeftCorner.X + el.leftw + 1;
        el.client.UpperLeftCorner.Y = el.top.UpperLeftCorner.Y + el.toph + 1;
        el.client.LowerRightCorner.X = el.right.UpperLeftCorner.X - 1;
        el.client.LowerRightCorner.Y = el.right.LowerRightCorner.Y - 1;       
    }

    //-----------------------------------------------------------------------
    //                           i n i t i a l i z e
    //-----------------------------------------------------------------------
    int  TGUISkin2::initialize()
    {
        TString cfgName;

        int result=0;

        //
        // load skin config
        //

        if(!m_skinName.size())
        {
            getApplication()->logMessage("Error: Missing GUI Skin Configuration");
            return 1;
        }

        TXMLConfig* config = new TXMLConfig();
        if(!config->load(m_skinName))
            return 1;

        TString baseName = config->getString("base512","textures");
        TString baseName2 = config->getString("base256","textures");
        TString hilightName = config->getString("hilight512","textures");
        TString hilightName2 = config->getString("hilight256","textures");

        m_skinConfig.Window.ulc = config->getRectd("window.ulc","layout");
        m_skinConfig.Window.urc = config->getRectd("window.urc","layout");
        m_skinConfig.Window.top = config->getRectd("window.top","layout");
        m_skinConfig.Window.llc = config->getRectd("window.llc","layout");
        m_skinConfig.Window.lrc = config->getRectd("window.lrc","layout");
        m_skinConfig.Window.bottom = config->getRectd("window.bottom","layout");
        m_skinConfig.Window.left = config->getRectd("window.left","layout");
        m_skinConfig.Window.right = config->getRectd("window.right","layout");
        m_skinConfig.Window.client = config->getRectd("window.client","layout");
        m_skinConfig.Window.hasHilight = config->getBool("window.hashilight","layout",false);
        calcElement(m_skinConfig.Window);

        m_skinConfig.Button.ulc = config->getRectd("button.ulc","layout");
        m_skinConfig.Button.urc = config->getRectd("button.urc","layout");
        m_skinConfig.Button.top = config->getRectd("button.top","layout");
        m_skinConfig.Button.llc = config->getRectd("button.llc","layout");
        m_skinConfig.Button.lrc = config->getRectd("button.lrc","layout");
        m_skinConfig.Button.bottom = config->getRectd("button.bottom","layout");
        m_skinConfig.Button.left = config->getRectd("button.left","layout");
        m_skinConfig.Button.right = config->getRectd("button.right","layout");
        m_skinConfig.Button.client = config->getRectd("button.client","layout");
        m_skinConfig.Button.hasHilight = config->getBool("button.hashilight","layout",false);
        calcElement(m_skinConfig.Button);

        IrrlichtDevice* dev = getApplication()->getRenderer()->getDevice();
        m_videoDriver = dev->getVideoDriver();
        m_baseTex = m_videoDriver->getTexture(baseName.c_str());
        if(!m_baseTex)
        {
            config->drop();
            return 1;
        }

        m_baseTex2 = m_videoDriver->getTexture(baseName2.c_str());
        if(!m_baseTex2)
        {
            config->drop();
            return 1;
        }

        m_hilightTex = m_videoDriver->getTexture(hilightName.c_str());
        if(!m_hilightTex)
        {
            config->drop();
            return 1;
        }

        m_hilightTex2 = m_videoDriver->getTexture(hilightName2.c_str());
        if(!m_hilightTex2)
        {
            config->drop();
            return 1;
        }

        m_defSkin = getApplication()->getRenderer()->getGUIManager()->getSkin();
        m_defSkin->grab();


        //
        // load default colours
        //

        config->drop();

        return result;
    }

    //-----------------------------------------------------------------------
    //                            g e t C o l o r
    //-----------------------------------------------------------------------
    video::SColor TGUISkin2::getColor(EGUI_DEFAULT_COLOR color) const
    {
        if ( color == EGDC_ACTIVE_CAPTION || color == EGDC_INACTIVE_CAPTION || 
            color == EGDC_TOOLTIP )
        {
            return video::SColor(255,0,0,0);
        }
        return m_defSkin->getColor(color);
    }

    //-----------------------------------------------------------------------
    //                            s e t C o l o r
    //-----------------------------------------------------------------------
    void TGUISkin2::setColor( EGUI_DEFAULT_COLOR which, video::SColor newColor )
    {
        m_defSkin->setColor(which, newColor);
    }

    //-----------------------------------------------------------------------
    //                            g e t S i z e
    //-----------------------------------------------------------------------
    s32 TGUISkin2::getSize(EGUI_DEFAULT_SIZE size) const
    {
        return m_defSkin->getSize(size);
    }

    //-----------------------------------------------------------------------
    //                            s e t S i z e
    //-----------------------------------------------------------------------
    void TGUISkin2::setSize(EGUI_DEFAULT_SIZE which, s32 size)
    {
        m_defSkin->setSize(which, size);
    }

    //-----------------------------------------------------------------------
    //                      g e t D e f a u l t T e x t
    //-----------------------------------------------------------------------
    const wchar_t* TGUISkin2::getDefaultText(EGUI_DEFAULT_TEXT text) const
    {
        return m_defSkin->getDefaultText(text);
    }

    //-----------------------------------------------------------------------
    //                      s e t D e f a u l t T e x t
    //-----------------------------------------------------------------------
    void TGUISkin2::setDefaultText(EGUI_DEFAULT_TEXT which, const wchar_t* newText)
    {
        m_defSkin->setDefaultText(which, newText);
    }


    //-----------------------------------------------------------------------
    //                            g e t F o n t
    //-----------------------------------------------------------------------
    IGUIFont* TGUISkin2::getFont(EGUI_DEFAULT_FONT defaultFont) const
    {
        return m_defSkin->getFont(defaultFont);
    }

    //-----------------------------------------------------------------------
    //                            s e t F o n t
    //-----------------------------------------------------------------------
    void TGUISkin2::setFont(IGUIFont* font, EGUI_DEFAULT_FONT defaultFont)
    {
        m_defSkin->setFont(font, defaultFont);
    }

    //-----------------------------------------------------------------------
    //                      g e t S p r i t e B a n k
    //-----------------------------------------------------------------------
    IGUISpriteBank* TGUISkin2::getSpriteBank() const
    {
        return m_defSkin->getSpriteBank();
    }

    //-----------------------------------------------------------------------
    //                      s e t S p r i t e B a n k
    //-----------------------------------------------------------------------
    void TGUISkin2::setSpriteBank( IGUISpriteBank* bank )
    {
        m_defSkin->setSpriteBank(bank);
    }

    //-----------------------------------------------------------------------
    //                            g e t I c o n
    //-----------------------------------------------------------------------
    u32 TGUISkin2::getIcon( EGUI_DEFAULT_ICON icon ) const
    {
        return m_defSkin->getIcon(icon);
    }

    //-----------------------------------------------------------------------
    //                            s e t I c o n
    //-----------------------------------------------------------------------
    void TGUISkin2::setIcon( EGUI_DEFAULT_ICON icon, u32 index )
    {
        m_defSkin->setIcon(icon, index);
    }

    //-----------------------------------------------------------------------
    //              d r a w 3 D B u t t o n P a n e S t a n d a r d 
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DButtonPaneStandard( IGUIElement* element, 
        const core::rect<s32>& rect, const core::rect<s32>* clip )
    {

        drawElementStyle( element, m_skinConfig.Button, rect, clip );
    }

    //-----------------------------------------------------------------------
    //              d r a w 3 D B u t t o n P a n e P r e s s e d 
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DButtonPanePressed( IGUIElement* element, 
        const core::rect<s32>& rect, const core::rect<s32>* clip )
    {
        m_defSkin->draw3DButtonPanePressed( element, rect, clip );
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D S u n k e n P a n e
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DSunkenPane(IGUIElement* element,
        video::SColor bgcolor, bool flat, bool fillBackGround,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        m_defSkin->draw3DSunkenPane(element, bgcolor, flat, 
            fillBackGround, rect, clip);
    }

    //-----------------------------------------------------------------------
    //               d r a w 3 D W i n d o w B a c k g r o u n d
    //-----------------------------------------------------------------------
    core::rect<s32> TGUISkin2::draw3DWindowBackground(IGUIElement* element,
        bool drawTitleBar, video::SColor titleBarColor,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        drawElementStyle( element, m_skinConfig.Window, rect, clip );
        return core::rect<s32>( rect.UpperLeftCorner.X + m_skinConfig.Window.leftw,rect.UpperLeftCorner.Y+4,
            rect.LowerRightCorner.X, rect.UpperLeftCorner.Y + m_skinConfig.Window.toph );
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D M e n u P a n e
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DMenuPane(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        m_defSkin->draw3DMenuPane(element,rect,clip);
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D T o o l B a r
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DToolBar(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        m_defSkin->draw3DToolBar(element,rect,clip);
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D T a b B u t t o n
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DTabButton(IGUIElement* element, bool active,
            const core::rect<s32>& rect, const core::rect<s32>* clip, 
            gui::EGUI_ALIGNMENT alignment)
    {
        m_defSkin->draw3DTabButton(element, active, rect, clip, alignment);
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D T a b B o d y
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DTabBody(IGUIElement* element, bool border, bool background,
            const core::rect<s32>& rect, const core::rect<s32>* clip, s32 tabHeight, 
            gui::EGUI_ALIGNMENT alignment)
    {
        m_defSkin->draw3DTabBody(element, border, background, rect, clip, tabHeight, alignment);
    }

    //-----------------------------------------------------------------------
    //                          d r a w I c o n
    //-----------------------------------------------------------------------
    void TGUISkin2::drawIcon(IGUIElement* element, EGUI_DEFAULT_ICON icon,
        const core::position2di position, u32 starttime, u32 currenttime, 
        bool loop, const core::rect<s32>* clip)
    {
        m_defSkin->drawIcon(element,icon,position,starttime,currenttime,loop,clip);
    }

    //-----------------------------------------------------------------------
    //              d r a w H o r i z o n t a l P r o g r e s s B a r
    //-----------------------------------------------------------------------
    void TGUISkin2::drawHorizontalProgressBar( IGUIElement* element, 
        const core::rect<s32>& rectangle, const core::rect<s32>* clip,
        f32 filledRatio, video::SColor fillColor )
    {
    }

    //-----------------------------------------------------------------------
    //                    d r a w E l e m e n t S t y l e
    //-----------------------------------------------------------------------
    void TGUISkin2::drawElementStyle( IGUIElement* element,
        const TImageGUIElementStyle& style, 
        const core::rect<s32>& rect, 
        const core::rect<s32>* clip, 
        const ITexture* texture,
        video::SColor* pcolor  )
    {
        core::rect<s32> r=rect;
        TRectd dstRect,srcRect,capRect;
        const ITexture* tex = texture;
        if(!tex)
            tex = m_baseTex;

        SColor col=SColor(255,155,155,155);
        if(pcolor)
            col = *pcolor;
        SColor vcol[4]={col,col,col,col};

        //
        // upper left corner
        //
        srcRect = style.ulc;
        dstRect = rect;
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + style.ulcw;
        dstRect.LowerRightCorner.Y = dstRect.UpperLeftCorner.Y + style.ulch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // upper middle
        //
        srcRect = style.top;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.UpperLeftCorner.X + style.ulcw;
        dstRect.LowerRightCorner.X = rect.LowerRightCorner.X - style.urcw;
        dstRect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + style.ulch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // upper right corner
        //
        srcRect = style.urc;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.LowerRightCorner.X - style.urcw;
        dstRect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + style.urch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // lower left
        //
        srcRect = style.llc;
        dstRect = rect;
        dstRect.UpperLeftCorner.Y = rect.LowerRightCorner.Y - style.llch;
        dstRect.LowerRightCorner.X = rect.UpperLeftCorner.X + style.llcw;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);
        return;

        //
        // lower right
        //
        srcRect = style.lrc;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.LowerRightCorner.X - style.lrcw;
        dstRect.UpperLeftCorner.Y = rect.LowerRightCorner.Y - style.lrch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // lower middle
        //
        srcRect = style.bottom;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.UpperLeftCorner.X + style.llcw;
        dstRect.LowerRightCorner.X = rect.LowerRightCorner.X - style.lrcw;
        dstRect.UpperLeftCorner.Y = rect.LowerRightCorner.Y - style.llch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);


        //
        // left side
        //
        srcRect = style.left;
        dstRect = rect;
        dstRect.UpperLeftCorner.Y  = dstRect.UpperLeftCorner.Y + style.ulch;
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + style.leftw;
        dstRect.LowerRightCorner.Y = dstRect.LowerRightCorner.Y - style.llch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // right side
        //
        srcRect = style.right;
        dstRect = rect;
        dstRect.UpperLeftCorner.X  = dstRect.LowerRightCorner.X - style.rightw;
        dstRect.UpperLeftCorner.Y = dstRect.UpperLeftCorner.Y + style.urch;
        dstRect.LowerRightCorner.Y = dstRect.LowerRightCorner.Y - style.llch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);


        //
        // client/middle area
        //
        srcRect = style.client;
        dstRect = rect;
        dstRect.UpperLeftCorner.X  = dstRect.UpperLeftCorner.X + style.leftw;
        dstRect.UpperLeftCorner.Y = dstRect.UpperLeftCorner.Y + style.toph;
        dstRect.LowerRightCorner.X = dstRect.LowerRightCorner.X - style.rightw;
        dstRect.LowerRightCorner.Y = dstRect.LowerRightCorner.Y - style.bottomh;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        if(!texture && style.hasHilight)
            drawElementStyle(element,style,rect,clip,m_hilightTex,pcolor);
        
    }

    //-----------------------------------------------------------------------
    //                     d r a w 2 D R e c t a n g l e
    //-----------------------------------------------------------------------
    void TGUISkin2::draw2DRectangle(IGUIElement* element, const video::SColor &color, 
        const core::rect<s32>& pos, const core::rect<s32>* clip)
    {
        m_defSkin->draw2DRectangle(element, color, pos, clip);
    }

}

