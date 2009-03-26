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

    //! constructor
    TGUIImage::TGUIImage(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle)
        : IGUIImage(environment, parent, id, rectangle), Texture(0), Color(255,255,255,255),
        UseAlphaChannel(false), ScaleImage(false)
    {
#ifdef _DEBUG
        setDebugName("TGUIImage");
#endif
    }


    //! destructor
    TGUIImage::~TGUIImage()
    {
        if (Texture)
            Texture->drop();
    }


    //! sets an image
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


    //! sets the color of the image
    void TGUIImage::setColor(video::SColor color)
    {
        Color = color;
    }

    void TGUIImage::setAlpha(f32 alpha)
    {
        Color.setAlpha((u32)(alpha*255.f));
    }

    //! draws the element and its children
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


    //! sets if the image should use its alpha channel to draw itself
    void TGUIImage::setUseAlphaChannel(bool use)
    {
        UseAlphaChannel = use;
    }


    //! sets if the image should use its alpha channel to draw itself
    void TGUIImage::setScaleImage(bool scale)
    {
        ScaleImage = scale;
    }


    //! Returns true if the image is scaled to fit, false if not
    bool TGUIImage::isImageScaled() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return ScaleImage;
    }

    //! Returns true if the image is using the alpha channel, false if not
    bool TGUIImage::isAlphaChannelUsed() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return UseAlphaChannel;
    }


    //! Writes attributes of the element.
    void TGUIImage::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
    {
        IGUIImage::serializeAttributes(out,options);

        out->addTexture	("Texture", Texture);
        out->addBool	("UseAlphaChannel", UseAlphaChannel);
        out->addColor	("Color", Color);
        out->addBool	("ScaleImage", ScaleImage);

    }


    //! Reads attributes of the element
    void TGUIImage::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
    {
        IGUIImage::deserializeAttributes(in,options);

        setImage(in->getAttributeAsTexture("Texture"));
        setUseAlphaChannel(in->getAttributeAsBool("UseAlphaChannel"));
        setColor(in->getAttributeAsColor("Color"));
        setScaleImage(in->getAttributeAsBool("ScaleImage"));
    }
}
