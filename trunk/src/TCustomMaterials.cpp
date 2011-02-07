//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"
#ifdef _IRR_COMPILE_WITH_DIRECT3D_9_
#include <d3d9.h>
#endif

namespace Tubras
{
#ifdef _IRR_COMPILE_WITH_OPENGL_
    void TOGL_TRANSPARENT_LIGHTMAP::OnSetMaterial(const SMaterial& material, const SMaterial& lastMaterial,
        bool resetAllRenderstates, IMaterialRendererServices* services)
    {
        Driver->disableTextures(2);
        Driver->setBasicRenderStates(material, lastMaterial, resetAllRenderstates);

        if (material.MaterialType != lastMaterial.MaterialType || resetAllRenderstates)
        {
            // diffuse map
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            // lightmap
            Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_PREVIOUS_ARB);
            glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB, GL_MODULATE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB, GL_PREVIOUS_ARB);
            glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_ARB, GL_PREVIOUS_ARB);
            glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 1.0f);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glEnable(GL_ALPHA_TEST);

            glAlphaFunc(GL_GREATER, material.MaterialTypeParam);

            Driver->extGlActiveTexture(GL_TEXTURE0_ARB);
        }
    }

    void TOGL_TRANSPARENT_LIGHTMAP::OnUnsetMaterial()
    {
        Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
        glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 1.f );
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        Driver->extGlActiveTexture(GL_TEXTURE0_ARB);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
#endif // _IRR_COMPILE_WITH_OPENGL_

#ifdef _IRR_COMPILE_WITH_DIRECT3D_9_
    void TDX9_TRANSPARENT_LIGHTMAP::OnSetMaterial(const SMaterial& material, const SMaterial& lastMaterial,
        bool resetAllRenderstates, IMaterialRendererServices* services)
    {
        if (material.MaterialType != lastMaterial.MaterialType || resetAllRenderstates)
        {
            pID3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
            pID3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
            pID3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,  D3DTOP_SELECTARG1);
            pID3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );

            pID3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
            pID3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
            pID3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
            pID3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
            pID3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP,  D3DTOP_DISABLE);

            pID3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
            pID3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pID3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

            pID3DDevice->SetRenderState(D3DRS_ALPHAREF, core::floor32(material.MaterialTypeParam * 255.f));
            pID3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
            pID3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
        }

        services->setBasicRenderStates(material, lastMaterial, resetAllRenderstates);
    }
#endif // _IRR_COMPILE_WITH_DIRECT3D_9_

}
