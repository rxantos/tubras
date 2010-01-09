//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TGUIIMAGE_H_
#define _TGUIIMAGE_H_

namespace Tubras
{
    class TGUIImage : public IGUIImage
    {
    public:
        //! constructor
        TGUIImage(IGUIEnvironment* environment, IGUIElement* parent=0, s32 id=-1, 
            core::rect<s32> rectangle=core::rect<s32>());

        //! destructor
        virtual ~TGUIImage();

        //! sets an image
        virtual void setImage(video::ITexture* image);

        //! sets the color of the image
        virtual void setColor(video::SColor color);

        virtual void setAlpha(f32 alpha);

        //! sets if the image should scale to fit the element
        virtual void setScaleImage(bool scale);

        //! draws the element and its children
        virtual void draw();

        //! sets if the image should use its alpha channel to draw itself
        virtual void setUseAlphaChannel(bool use);

        //! Returns true if the image is scaled to fit, false if not
        virtual bool isImageScaled() const;

        //! Returns true if the image is using the alpha channel, false if not
        virtual bool isAlphaChannelUsed() const;

        //! Writes attributes of the element.
        virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

        //! Reads attributes of the element
        virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

    private:
        video::ITexture* Texture;
        video::SColor Color;
        bool UseAlphaChannel;
        bool ScaleImage;
    };
}
#endif

