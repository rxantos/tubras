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
    //                           i n i t i a l i z e
    //-----------------------------------------------------------------------
    int  TGUISkin2::initialize()
    {
        int result=0;

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
        if ( !Config.Button.Texture )
        {
            m_defSkin->draw3DButtonPaneStandard( element, rect, clip );
            return;
        }

        drawElementStyle( element, Config.Button, rect, clip );
    }

    //-----------------------------------------------------------------------
    //              d r a w 3 D B u t t o n P a n e P r e s s e d 
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DButtonPanePressed( IGUIElement* element, 
        const core::rect<s32>& rect, const core::rect<s32>* clip )
    {
        if ( !Config.Button.Texture )
        {
            m_defSkin->draw3DButtonPanePressed( element, rect, clip );
            return;
        }

        drawElementStyle( element, Config.ButtonPressed, rect, clip );
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D S u n k e n P a n e
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DSunkenPane(IGUIElement* element,
        video::SColor bgcolor, bool flat, bool fillBackGround,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        if ( !Config.SunkenPane.Texture )
        {
            m_defSkin->draw3DSunkenPane(element, bgcolor, flat, 
                fillBackGround, rect, clip);
            return;
        }
        drawElementStyle( element, Config.SunkenPane, rect, clip );
    }

    //-----------------------------------------------------------------------
    //               d r a w 3 D W i n d o w B a c k g r o u n d
    //-----------------------------------------------------------------------
    core::rect<s32> TGUISkin2::draw3DWindowBackground(IGUIElement* element,
        bool drawTitleBar, video::SColor titleBarColor,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        if ( !Config.Window.Texture )
        {
            return m_defSkin->draw3DWindowBackground(element, drawTitleBar, 
                titleBarColor, rect, clip );
        }
        drawElementStyle( element, Config.Window, rect, clip );

        return core::rect<s32>( rect.UpperLeftCorner.X+Config.Window.DstBorder.Left, 
            rect.UpperLeftCorner.Y, 
            rect.LowerRightCorner.X-Config.Window.DstBorder.Right, 
            rect.UpperLeftCorner.Y+Config.Window.DstBorder.Top );
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
        const core::rect<s32>& rect, const core::rect<s32>* clip)
    {
        m_defSkin->draw3DTabButton(element, active, rect, clip);
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D T a b B o d y
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DTabBody(IGUIElement* element, bool border, bool background,
        const core::rect<s32>& rect, const core::rect<s32>* clip)
    {
        m_defSkin->draw3DTabBody(element, border, background, rect, clip);
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
        if ( !Config.ProgressBar.Texture || !Config.ProgressBarFilled.Texture )
        {
            return;
        }

        // Draw empty progress bar
        drawElementStyle( element, Config.ProgressBar, rectangle, clip );

        // Draw filled progress bar on top
        if ( filledRatio < 0.0f )
            filledRatio = 0.0f;
        else
            if ( filledRatio > 1.0f )
                filledRatio = 1.0f;

        if ( filledRatio > 0.0f )
        {
            s32 filledPixels = (s32)( filledRatio * rectangle.getSize().Width );
            s32 height = rectangle.getSize().Height;

            core::rect<s32> clipRect = clip? *clip:rectangle;
            if ( filledPixels < height )
            {
                if ( clipRect.LowerRightCorner.X > rectangle.UpperLeftCorner.X + filledPixels )
                    clipRect.LowerRightCorner.X = rectangle.UpperLeftCorner.X + filledPixels;

                filledPixels = height;
            }

            core::rect<s32> filledRect = core::rect<s32>( 
                rectangle.UpperLeftCorner.X, 
                rectangle.UpperLeftCorner.Y, 
                rectangle.UpperLeftCorner.X + filledPixels, 
                rectangle.LowerRightCorner.Y );

            drawElementStyle( element, Config.ProgressBarFilled, filledRect, &clipRect, &fillColor );
        }
    }

    //-----------------------------------------------------------------------
    //                    d r a w E l e m e n t S t y l e
    //-----------------------------------------------------------------------
    void TGUISkin2::drawElementStyle( IGUIElement* element,
        const TImageGUIElementStyle& style, 
        const core::rect<s32>& rect, 
        const core::rect<s32>* clip, 
        video::SColor* pcolor  )
    {
        core::rect<s32> srcRect;
        core::rect<s32> dstRect;
        core::dimension2di tsize = style.Texture->getSize();
        video::ITexture* texture = style.Texture;

        video::SColor color = style.Color;
        if ( pcolor )
            color = *pcolor;

        video::SColor faceColor = getColor(EGDC_3D_FACE);
        color.setRed( (u8)(color.getRed() * faceColor.getRed() / 255) );
        color.setGreen( (u8)(color.getGreen() * faceColor.getGreen() / 255) );
        color.setBlue( (u8)(color.getBlue() * faceColor.getBlue() / 255) );
        color.setAlpha( (u8)(color.getAlpha() * faceColor.getAlpha() / 255 ) );

        video::SColor colors [4] = { color, color, color, color };

        core::dimension2di dstSize = rect.getSize();

        // Scale the border if there is insufficient room
        TImageGUIElementStyle::SBorder dst = style.DstBorder;
        f32 scale = 1.0f;
        if ( dstSize.Width < dst.Left + dst.Right )
        {
            scale = dstSize.Width / (f32)( dst.Left + dst.Right );
        }
        if ( dstSize.Height < dst.Top + dst.Bottom )
        {
            f32 x = dstSize.Height / (f32)( dst.Top + dst.Bottom );
            if ( x < scale )
            {
                scale = x;
            }
        }

        if ( scale < 1.0f )
        {
            dst.Left = (s32)( dst.Left * scale );
            dst.Right = (s32)( dst.Right * scale );
            dst.Top = (s32)( dst.Top * scale );
            dst.Bottom = (s32)( dst.Bottom * scale );
        }

        const TImageGUIElementStyle::SBorder& src = style.SrcBorder;

        // Draw the top left corner
        srcRect = core::rect<s32>( 0, 0, src.Left, src.Top );
        dstRect = core::rect<s32>( rect.UpperLeftCorner.X, rect.UpperLeftCorner.Y, 
            rect.UpperLeftCorner.X+dst.Left, rect.UpperLeftCorner.Y+dst.Top );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

        // Draw the top right corner
        srcRect = core::rect<s32>( tsize.Width-src.Right, 0, tsize.Width, src.Top );
        dstRect = core::rect<s32>( rect.LowerRightCorner.X-dst.Right, rect.UpperLeftCorner.Y, 
            rect.LowerRightCorner.X, rect.UpperLeftCorner.Y+dst.Top );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

        // Draw the top border
        srcRect = core::rect<s32>( src.Left, 0, tsize.Width-src.Right, src.Top );
        dstRect = core::rect<s32>( rect.UpperLeftCorner.X+dst.Left, rect.UpperLeftCorner.Y, 
            rect.LowerRightCorner.X-dst.Right, rect.UpperLeftCorner.Y+dst.Top );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

        // Draw the left border
        srcRect = core::rect<s32>( 0, src.Top, src.Left, tsize.Height-src.Bottom );
        dstRect = core::rect<s32>( rect.UpperLeftCorner.X, rect.UpperLeftCorner.Y+dst.Top, 
            rect.UpperLeftCorner.X+dst.Left, rect.LowerRightCorner.Y-dst.Bottom );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

        // Draw the right border
        srcRect = core::rect<s32>( tsize.Width-src.Right, src.Top, tsize.Width, tsize.Height-src.Bottom );
        dstRect = core::rect<s32>( rect.LowerRightCorner.X-dst.Right, 
            rect.UpperLeftCorner.Y+dst.Top, rect.LowerRightCorner.X, rect.LowerRightCorner.Y-dst.Bottom );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

        // Draw the middle section
        srcRect = core::rect<s32>( src.Left, src.Top, tsize.Width-src.Right, tsize.Height-src.Bottom );
        dstRect = core::rect<s32>( rect.UpperLeftCorner.X+dst.Left, rect.UpperLeftCorner.Y+dst.Top, 
            rect.LowerRightCorner.X-dst.Right, rect.LowerRightCorner.Y-dst.Bottom );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

        // Draw the bottom left corner
        srcRect = core::rect<s32>( 0, tsize.Height-src.Bottom, src.Left, tsize.Height );
        dstRect = core::rect<s32>( rect.UpperLeftCorner.X, rect.LowerRightCorner.Y-dst.Bottom, 
            rect.UpperLeftCorner.X+dst.Left, rect.LowerRightCorner.Y );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

        // Draw the bottom right corner
        srcRect = core::rect<s32>( tsize.Width-src.Right, tsize.Height-src.Bottom, tsize.Width, tsize.Height );
        dstRect = core::rect<s32>( rect.LowerRightCorner.X-dst.Right, rect.LowerRightCorner.Y-dst.Bottom, 
            rect.LowerRightCorner.X, rect.LowerRightCorner.Y );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

        // Draw the bottom border
        srcRect = core::rect<s32>( src.Left, tsize.Height-src.Bottom, tsize.Width-src.Right, tsize.Height );
        dstRect = core::rect<s32>( rect.UpperLeftCorner.X+dst.Left, rect.LowerRightCorner.Y-dst.Bottom, 
            rect.LowerRightCorner.X-dst.Right, rect.LowerRightCorner.Y );
        if ( !clip || clipRects( dstRect, srcRect, *clip ) )
            m_videoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );
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

