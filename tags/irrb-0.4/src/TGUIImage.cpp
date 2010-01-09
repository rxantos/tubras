//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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

    //-----------------------------------------------------------------------
    //                            T G U I I m a g e
    //-----------------------------------------------------------------------
    TGUIImage::TGUIImage(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle)
        : IGUIImage(environment, parent, id, rectangle), Texture(0), Color(255,255,255,255),
        UseAlphaChannel(false), ScaleImage(false)
    {
#ifdef _DEBUG
        setDebugName("TGUIImage");
#endif
    }

    //-----------------------------------------------------------------------
    //                           ~ T G U I I m a g e
    //-----------------------------------------------------------------------
    TGUIImage::~TGUIImage()
    {
        if (Texture)
            Texture->drop();
    }

    //-----------------------------------------------------------------------
    //                           s e t I m a g e
    //-----------------------------------------------------------------------
    void TGUIImage::setImage(video::ITexture* image)
    {
        if (image == Texture)
            return;

        if (Texture)
            Texture->drop();

        Texture = image;

        if (Texture)
            Texture->grab();
    }

    //-----------------------------------------------------------------------
    //                           s e t C o l o r
    //-----------------------------------------------------------------------
    void TGUIImage::setColor(video::SColor color)
    {
        Color = color;
    }

    //-----------------------------------------------------------------------
    //                           s e t A l p h a 
    //-----------------------------------------------------------------------
    void TGUIImage::setAlpha(f32 alpha)
    {
        Color.setAlpha((u32)(alpha*255.f));
    }

    //-----------------------------------------------------------------------
    //                              d r a w
    //-----------------------------------------------------------------------
    void TGUIImage::draw()
    {
        if (!IsVisible)
            return;

        IGUISkin* skin = Environment->getSkin();
        video::IVideoDriver* driver = Environment->getVideoDriver();

        core::rect<s32> rect = AbsoluteRect;

        if (Texture)
        {
            if (ScaleImage)
            {
                const video::SColor Colors[] = {Color,Color,Color,Color};

                driver->draw2DImage(Texture, AbsoluteRect,
                    core::rect<s32>(core::position2d<s32>(0,0), core::dimension2di(Texture->getOriginalSize())),
                    &AbsoluteClippingRect, Colors, UseAlphaChannel);
            }
            else
            {
                driver->draw2DImage(Texture, AbsoluteRect.UpperLeftCorner,
                    core::rect<s32>(core::position2d<s32>(0,0), core::dimension2di(Texture->getOriginalSize())),
                    &AbsoluteClippingRect, Color, UseAlphaChannel);
            }
        }
        else
        {
            skin->draw2DRectangle(this, skin->getColor(EGDC_3D_DARK_SHADOW), AbsoluteRect, &AbsoluteClippingRect);
        }

        IGUIElement::draw();
    }

    //-----------------------------------------------------------------------
    //                     s e t U s e A l p h a C h a n n e l
    //-----------------------------------------------------------------------
    void TGUIImage::setUseAlphaChannel(bool use)
    {
        UseAlphaChannel = use;
    }

    //-----------------------------------------------------------------------
    //                     s e t S c a l e I m a g e
    //-----------------------------------------------------------------------
    void TGUIImage::setScaleImage(bool scale)
    {
        ScaleImage = scale;
    }

    //-----------------------------------------------------------------------
    //                     i s I m a g e S c a l e d
    //-----------------------------------------------------------------------
    bool TGUIImage::isImageScaled() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return ScaleImage;
    }

    //-----------------------------------------------------------------------
    //                  i s A l p h a C h a n n e l U s e d
    //-----------------------------------------------------------------------
    bool TGUIImage::isAlphaChannelUsed() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return UseAlphaChannel;
    }

    //-----------------------------------------------------------------------
    //                  s e r i a l i z e A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TGUIImage::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
    {
        IGUIImage::serializeAttributes(out,options);

        out->addTexture	("Texture", Texture);
        out->addBool	("UseAlphaChannel", UseAlphaChannel);
        out->addColor	("Color", Color);
        out->addBool	("ScaleImage", ScaleImage);

    }

    //-----------------------------------------------------------------------
    //                 d e s e r i a l i z e A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TGUIImage::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
    {
        IGUIImage::deserializeAttributes(in,options);

        setImage(in->getAttributeAsTexture("Texture"));
        setUseAlphaChannel(in->getAttributeAsBool("UseAlphaChannel"));
        setColor(in->getAttributeAsColor("Color"));
        setScaleImage(in->getAttributeAsBool("ScaleImage"));
    }
}
