//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T G U I B u t t o n
    //-----------------------------------------------------------------------
    TGUIButton::TGUIButton(IGUIEnvironment* environment, IGUIElement* parent,
        s32 id, core::rect<s32> rectangle, bool noclip) : IGUIButton(environment,
        parent,id,rectangle),
        Pressed(false),
        IsPushButton(false), UseAlphaChannel(false), IsDefault(false), 
        Border(true), MouseOverTime(0), FocusTime(0), ClickTime(0), 
        SpriteBank(0), OverrideFont(0), Image(0), PressedImage(0), ScaleImage(false)
    {
#ifdef _DEBUG
        setDebugName("TGUIButton");
#endif
        Type = (EGUI_ELEMENT_TYPE)TGUI_BUTTON;
        setNotClipped(noclip);
        Timer = getApplication()->getGlobalClock();

        // Initialize the sprites.
        for (u32 i=0; i<EGBS_COUNT; ++i)
            ButtonSprites[i].Index = -1;

        // This element can be tabbed.
        setTabStop(true);
        setTabOrder(-1);
    }    

    //-----------------------------------------------------------------------
    //                       ~ T G U I B u t t o n
    //-----------------------------------------------------------------------
    TGUIButton::~TGUIButton()
    {
        if (OverrideFont)
            OverrideFont->drop();

        if (Image)
            Image->drop();

        if (PressedImage)
            PressedImage->drop();

        if (SpriteBank)
            SpriteBank->drop();
    }

    //-----------------------------------------------------------------------
    //                          i s D e f a u l t
    //-----------------------------------------------------------------------
    bool TGUIButton::isDefault() const
    {
        return IsDefault;
    }

    //-----------------------------------------------------------------------
    //                          s e t I s D e f a u l t
    //-----------------------------------------------------------------------
    void TGUIButton::setIsDefault(bool value)
    {
        IsDefault = value;
    }


    //-----------------------------------------------------------------------
    //                        s e t D r a w B o r d e r
    //-----------------------------------------------------------------------
    void TGUIButton::setDrawBorder(bool border)
    {
        Border = border;
    }

    //-----------------------------------------------------------------------
    //                      s e t S p r i t e B a n k
    //-----------------------------------------------------------------------
    void TGUIButton::setSpriteBank(IGUISpriteBank* sprites)
    {
        if (sprites)
            sprites->grab();

        if (SpriteBank)
            SpriteBank->drop();

        SpriteBank = sprites;
    }

    //-----------------------------------------------------------------------
    //                           s e t S p r i t e
    //-----------------------------------------------------------------------
    void TGUIButton::setSprite(EGUI_BUTTON_STATE state, s32 index, video::SColor color, bool loop)
    {
        if (SpriteBank)
        {
            ButtonSprites[(u32)state].Index	= index;
            ButtonSprites[(u32)state].Color	= color;
            ButtonSprites[(u32)state].Loop	= loop;
        }
        else
        {
            ButtonSprites[(u32)state].Index = -1;
        }
    }

    //-----------------------------------------------------------------------
    //                            O n E v e n t
    //-----------------------------------------------------------------------
    bool TGUIButton::OnEvent(const SEvent& event)
    {
        if (!IsEnabled)
            return Parent ? Parent->OnEvent(event) : false;

        switch(event.EventType)
        {
        case EET_KEY_INPUT_EVENT:
            if (event.KeyInput.PressedDown &&
                (event.KeyInput.Key == KEY_RETURN || 
                event.KeyInput.Key == KEY_SPACE))
            {
                if (!IsPushButton)
                    setPressed(true);
                else
                    setPressed(!Pressed);

                return true;
            }
            if (Pressed && !IsPushButton && event.KeyInput.PressedDown && event.KeyInput.Key == KEY_ESCAPE)
            {
                setPressed(false);
                return true;
            }
            else
                if (!event.KeyInput.PressedDown && Pressed &&
                    (event.KeyInput.Key == KEY_RETURN || 
                    event.KeyInput.Key == KEY_SPACE))
                {
                    //Environment->removeFocus(this);

                    if (!IsPushButton)
                        setPressed(false);

                    if (Parent)
                    {
                        SEvent newEvent;
                        newEvent.EventType = EET_GUI_EVENT;
                        newEvent.GUIEvent.Caller = this;
                        newEvent.GUIEvent.Element = 0;
                        newEvent.GUIEvent.EventType = EGET_BUTTON_CLICKED;
                        Parent->OnEvent(newEvent);
                    }
                    return true;
                }
                break;
        case EET_GUI_EVENT:
            if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUS_LOST)
            {
                if (event.GUIEvent.Caller == this && !IsPushButton)
                    setPressed(false);
            }
            break;
        case EET_MOUSE_INPUT_EVENT:
            if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
            {
                if (Environment->hasFocus(this) &&
                    !AbsoluteClippingRect.isPointInside(core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y)))
                {
                    Environment->removeFocus(this);
                    return false;
                }

                if (!IsPushButton)
                    setPressed(true);

                Environment->setFocus(this);
                return true;
            }
            else
                if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
                {
                    bool wasPressed = Pressed;
                    //Environment->removeFocus(this);

                    if ( !AbsoluteClippingRect.isPointInside( core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y ) ) )
                    {
                        if (!IsPushButton)
                            setPressed(false);
                        return true;
                    }

                    if (!IsPushButton)
                        setPressed(false);
                    else
                    {
                        setPressed(!Pressed);
                    }

                    if ((!IsPushButton && wasPressed && Parent) ||
                        (IsPushButton && wasPressed != Pressed))
                    {
                        SEvent newEvent;
                        newEvent.EventType = EET_GUI_EVENT;
                        newEvent.GUIEvent.Caller = this;
                        newEvent.GUIEvent.Element = 0;
                        newEvent.GUIEvent.EventType = EGET_BUTTON_CLICKED;
                        Parent->OnEvent(newEvent);
                    }

                    return true;
                }
                break;
        default:
            break;
        }

        return Parent ? Parent->OnEvent(event) : false;
    }



    //-----------------------------------------------------------------------
    //                              d r a w
    //-----------------------------------------------------------------------
    void TGUIButton::draw()
    {
        if (!IsVisible)
            return;

        IGUISkin* skin = Environment->getSkin();
        video::IVideoDriver* driver = Environment->getVideoDriver();

        IGUIFont* font = OverrideFont;
        if (!OverrideFont)
            font = skin->getFont(EGDF_BUTTON);

        core::rect<s32> rect = AbsoluteRect;

        // todo:	move sprite up and text down if the pressed state has a sprite
        //			draw sprites for focused and mouse-over 
        core::position2di spritePos = AbsoluteRect.getCenter();

        if (!Pressed)
        {
            if (Border)
                skin->draw3DButtonPaneStandard(this, rect, &AbsoluteClippingRect);

            if (Image)
            {
                core::position2d<s32> pos = AbsoluteRect.getCenter();
                pos.X -= ImageRect.getWidth() / 2;
                pos.Y -= ImageRect.getHeight() / 2;

                driver->draw2DImage(Image,
                    ScaleImage? AbsoluteRect :
                    core::recti(pos, ImageRect.getSize()),
                    ImageRect, &AbsoluteClippingRect,
                    0, UseAlphaChannel);
            }
            if (SpriteBank && ButtonSprites[EGBS_BUTTON_UP].Index != -1)
            {
                // draw pressed sprite
                SpriteBank->draw2DSprite(ButtonSprites[EGBS_BUTTON_UP].Index, spritePos, 
                    &AbsoluteClippingRect, ButtonSprites[EGBS_BUTTON_UP].Color, ClickTime, Timer->getMilliSeconds(), 
                    ButtonSprites[EGBS_BUTTON_UP].Loop, true);
            }
        }
        else
        {
            if (Border)
                skin->draw3DButtonPanePressed(this, rect, &AbsoluteClippingRect);

            if (PressedImage)
            {
                core::position2d<s32> pos = AbsoluteRect.getCenter();
                pos.X -= PressedImageRect.getWidth() / 2;
                pos.Y -= PressedImageRect.getHeight() / 2;
                // patch by Alan Tyndall/Jonas Petersen
                if (Image == PressedImage && PressedImageRect == ImageRect)
                {
                    pos.X += 1;
                    pos.Y += 1;
                }
                driver->draw2DImage(PressedImage,
                    ScaleImage? AbsoluteRect :
                    core::recti(pos, PressedImageRect.getSize()),
                    PressedImageRect, &AbsoluteClippingRect,
                    0, UseAlphaChannel);
            }

            if (SpriteBank && ButtonSprites[EGBS_BUTTON_DOWN].Index != -1)
            {
                // draw sprite
                SpriteBank->draw2DSprite(ButtonSprites[EGBS_BUTTON_DOWN].Index, spritePos, 
                    &AbsoluteClippingRect, ButtonSprites[EGBS_BUTTON_DOWN].Color, ClickTime, Timer->getMilliSeconds(), 
                    ButtonSprites[EGBS_BUTTON_DOWN].Loop, true);
            }

        }

        if (Text.size())
        {
            rect = AbsoluteRect;
            if (Pressed)
                rect.UpperLeftCorner.Y += 2;

            if (font)
                font->draw(Text.c_str(), rect,
                skin->getColor(IsEnabled ? EGDC_BUTTON_TEXT : EGDC_GRAY_TEXT), true, true, 
                &AbsoluteClippingRect);
        }

        IGUIElement::draw();
    }

    //-----------------------------------------------------------------------
    //                      s e t O v e r r i d e F o n t
    //-----------------------------------------------------------------------
    void TGUIButton::setOverrideFont(IGUIFont* font)
    {
        if (OverrideFont)
            OverrideFont->drop();

        OverrideFont = font;

        if (OverrideFont)
            OverrideFont->grab();
    }

    //-----------------------------------------------------------------------
    //                     g e t O v e r r i d e F o n t
    //-----------------------------------------------------------------------
    IGUIFont * TGUIButton::getOverrideFont() const
    {
        return OverrideFont;
    }

    //-----------------------------------------------------------------------
    //                      g e t A c t i v e F o n t
    //-----------------------------------------------------------------------
    IGUIFont* TGUIButton::getActiveFont() const
    {
        if ( OverrideFont )
            return OverrideFont;
        IGUISkin* skin = Environment->getSkin();
        if (skin)
            return skin->getFont();
        return 0;
    }

    //-----------------------------------------------------------------------
    //                          s e t I m a g e
    //-----------------------------------------------------------------------
    void TGUIButton::setImage(video::ITexture* image)
    {
        if (Image)
            Image->drop();

        Image = image;
        if (image)
        {
            dimension2du size = image->getOriginalSize();
            ImageRect = core::recti(core::vector2di(0,0), core::position2di(size.Width, size.Height));
        }

        if (Image)
            Image->grab();

        if (!PressedImage)
            setPressedImage(Image);
    }

    //-----------------------------------------------------------------------
    //                          s e t I m a g e
    //-----------------------------------------------------------------------
    void TGUIButton::setImage(video::ITexture* image, const core::rect<s32>& pos)
    {
        if (Image)
            Image->drop();

        Image = image;
        ImageRect = pos;

        if (Image)
            Image->grab();

        if (!PressedImage)
            setPressedImage(Image, pos);
    }

    //-----------------------------------------------------------------------
    //                    s e t P r e s s e d I m a g e
    //-----------------------------------------------------------------------
    void TGUIButton::setPressedImage(video::ITexture* image)
    {
        if (PressedImage)
            PressedImage->drop();

        PressedImage = image;
        if (image)
        {
            dimension2du size = image->getOriginalSize();
            PressedImageRect  = core::recti(core::vector2di(0,0), core::position2di(size.Width, size.Height));
        }

        if (PressedImage)
            PressedImage->grab();
    }

    //-----------------------------------------------------------------------
    //                    s e t P r e s s e d I m a g e
    //-----------------------------------------------------------------------
    void TGUIButton::setPressedImage(video::ITexture* image, const core::rect<s32>& pos)
    {
        if (PressedImage)
            PressedImage->drop();

        PressedImage = image;
        PressedImageRect = pos;

        if (PressedImage)
            PressedImage->grab();
    }


    //-----------------------------------------------------------------------
    //                     s e t I s P u s h B u t t o n
    //-----------------------------------------------------------------------
    void TGUIButton::setIsPushButton(bool isPushButton)
    {
        IsPushButton = isPushButton;
    }


    //-----------------------------------------------------------------------
    //                          i s P r e s s e d
    //-----------------------------------------------------------------------
    bool TGUIButton::isPressed() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return Pressed;
    }

    //-----------------------------------------------------------------------
    //                          s e t P r e s s e d
    //-----------------------------------------------------------------------
    void TGUIButton::setPressed(bool pressed)
    {
        if (Pressed != pressed)
        {
            ClickTime = Timer->getMilliSeconds();
            Pressed = pressed;
        }
    }

    //-----------------------------------------------------------------------
    //                         i s P u s h B u t t o n
    //-----------------------------------------------------------------------
    bool TGUIButton::isPushButton() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return IsPushButton;
    }

    //-----------------------------------------------------------------------
    //                   s e t U s e A l p h a C h a n n e l
    //-----------------------------------------------------------------------
    void TGUIButton::setUseAlphaChannel(bool useAlphaChannel)
    {
        UseAlphaChannel = useAlphaChannel;
    }

    //-----------------------------------------------------------------------
    //                   i s A l p h a C h a n n e l U s e d
    //-----------------------------------------------------------------------
    bool TGUIButton::isAlphaChannelUsed() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return UseAlphaChannel;
    }

    //-----------------------------------------------------------------------
    //                      s e t S c a l e I  m a g e
    //-----------------------------------------------------------------------
    void TGUIButton::setScaleImage(bool scaleImage)
    {
        ScaleImage = scaleImage;
    }

    //-----------------------------------------------------------------------
    //                     i s S c a l i n g I m a g e
    //-----------------------------------------------------------------------
    bool TGUIButton::isScalingImage() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return ScaleImage;
    }

    //-----------------------------------------------------------------------
    //                     i s D r a w i n g B o r d e r
    //-----------------------------------------------------------------------
    bool TGUIButton::isDrawingBorder() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return Border;
    }

    //-----------------------------------------------------------------------
    //                   s e r i a l i z e A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TGUIButton::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
    {

        IGUIButton::serializeAttributes(out,options);

        out->addBool	("PushButton",		IsPushButton );
        if (IsPushButton)
            out->addBool("Pressed",		Pressed);

        out->addTexture ("Image",		Image);
        out->addRect	("ImageRect",		ImageRect);
        out->addTexture	("PressedImage",	PressedImage);
        out->addRect	("PressedImageRect",	PressedImageRect);

        out->addBool	("Border",		Border);
        out->addBool	("UseAlphaChannel",	UseAlphaChannel);
        out->addBool	("ScaleImage",		isScalingImage());

        //   out->addString  ("OverrideFont",	OverrideFont);
    }

    //-----------------------------------------------------------------------
    //                  d e s e r i a l i z e A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TGUIButton::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
    {
        IGUIButton::deserializeAttributes(in,options);

        IsPushButton	= in->getAttributeAsBool("PushButton");
        Pressed		= IsPushButton ? in->getAttributeAsBool("Pressed") : false;

        core::rect<s32> rec = in->getAttributeAsRect("ImageRect");
        if (rec.isValid())
            setImage( in->getAttributeAsTexture("Image"), rec);
        else
            setImage( in->getAttributeAsTexture("Image") );

        rec = in->getAttributeAsRect("PressedImageRect");
        if (rec.isValid())
            setPressedImage( in->getAttributeAsTexture("PressedImage"), rec);
        else
            setPressedImage( in->getAttributeAsTexture("PressedImage") );

        setDrawBorder(in->getAttributeAsBool("Border"));
        UseAlphaChannel = in->getAttributeAsBool("UseAlphaChannel");

        setScaleImage(in->getAttributeAsBool("ScaleImage"));

        //   setOverrideFont(in->getAttributeAsString("OverrideFont"));

        updateAbsolutePosition();
    }

}
