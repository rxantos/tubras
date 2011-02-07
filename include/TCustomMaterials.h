//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TCUSTOMMATERIALS_H_
#define _TCUSTOMMATERIALS_H_

namespace Tubras
{
#ifdef _IRR_COMPILE_WITH_OPENGL_

    class TOGL_LightMapAlpha : public IMaterialRenderer
    {
        video::COpenGLDriver* Driver;
    public:

        TOGL_LightMapAlpha(video::COpenGLDriver* d)
            : Driver(d) {}

        virtual void OnSetMaterial(const SMaterial& material, const SMaterial& lastMaterial,
            bool resetAllRenderstates, IMaterialRendererServices* services);

        virtual void OnUnsetMaterial();
    };

#endif

#ifdef _IRR_COMPILE_WITH_DIRECT3D_9_
    class TDX9_LightMapAlpha : public IMaterialRenderer
    {
        video::CD3D9Driver* Driver;
    public:

        TDX9_LightMapAlpha(video::CD3D9Driver* d)
            : Driver(d) {}

        virtual void OnSetMaterial(const SMaterial& material, const SMaterial& lastMaterial,
            bool resetAllRenderstates, IMaterialRendererServices* services);

        virtual void OnUnsetMaterial();
    };
#endif

}
#endif
