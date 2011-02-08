//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TCUSTOMMATERIALS_H_
#define _TCUSTOMMATERIALS_H_

namespace Tubras
{
    // used for all materials added to the null device
    class TNULL_GENERIC_MATERIAL : public IMaterialRenderer
    {
    public:
        TNULL_GENERIC_MATERIAL(IVideoDriver* driver) : IMaterialRenderer() {}

        virtual void OnSetMaterial(const SMaterial& material, const SMaterial& lastMaterial,
            bool resetAllRenderstates, IMaterialRendererServices* services) {}

        virtual void OnUnsetMaterial() {}

        virtual bool isTransparent() const { return true; }
    };

#ifdef _IRR_COMPILE_WITH_OPENGL_

    class TOGL_TRANSPARENT_LIGHTMAP : public COpenGLMaterialRenderer
    {
    public:
        TOGL_TRANSPARENT_LIGHTMAP(video::COpenGLDriver* driver) : COpenGLMaterialRenderer(driver) {}

        virtual void OnSetMaterial(const SMaterial& material, const SMaterial& lastMaterial,
            bool resetAllRenderstates, IMaterialRendererServices* services);

        virtual void OnUnsetMaterial();

        virtual bool isTransparent() const { return true; }
    };

#endif

#ifdef _IRR_COMPILE_WITH_DIRECT3D_9_
    class TDX9_TRANSPARENT_LIGHTMAP: public IMaterialRenderer
    {
    protected:

        IDirect3DDevice9* pID3DDevice;
        video::IVideoDriver* Driver;

    public:
        TDX9_TRANSPARENT_LIGHTMAP(video::IVideoDriver* driver)
            : IMaterialRenderer(), Driver(driver), 
            pID3DDevice(driver->getExposedVideoData().D3D9.D3DDev9) {}

        virtual void OnSetMaterial(const SMaterial& material, const SMaterial& lastMaterial,
            bool resetAllRenderstates, IMaterialRendererServices* services);

        virtual bool isTransparent() const { return true; }
    };
#endif

}
#endif
