//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //! constructor
    TSceneNodeAnimatorMaterialLayer::TSceneNodeAnimatorMaterialLayer() : lastTime(0)
    {
#ifdef _DEBUG
        setDebugName("TSceneNodeAnimatorMaterialLayer");
#endif

    }

    //! destructor
    TSceneNodeAnimatorMaterialLayer::~TSceneNodeAnimatorMaterialLayer()
    {

        for ( MLMAP::Iterator itr = Materials.getIterator(); !itr.atEnd(); itr++)
        {
            AMLParms*   pdata = itr->getValue();
            pdata->drop();
        }
    }

    //! animates a scene node
    void TSceneNodeAnimatorMaterialLayer::animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs)
    {
        irr::u32   t = timeMs - lastTime;

        if(t)
        {
            irr::f32 delta = t * 0.001f;
            for ( MLMAP::Iterator itr = Materials.getIterator(); !itr.atEnd(); itr++)
            {
                AMLParms*  parms = itr->getValue();
                irr::core::matrix4& mat = parms->layer->getTextureMatrix();

                irr::f32 rotateRad=0.0;
                irr::core::vector2df scale(1, 1);


                if(parms->rotation != 0.0f)
                {
                    parms->crotation += parms->rotation * delta;
                    rotateRad = parms->crotation * irr::core::DEGTORAD;
                }

                if((parms->scroll.X != 0.0f) ||
                    (parms->scroll.Y != 0.0f))
                {
                    parms->cscroll.X += parms->scroll.X * delta;
                    parms->cscroll.Y += parms->scroll.Y * delta;
                }

                if((parms->scale.X != 0.0f) ||
                    (parms->scale.Y != 0.0f))
                {
                    parms->cscale.X += parms->scale.X * delta;
                    parms->cscale.Y += parms->scale.Y * delta;
                }

                mat.buildTextureTransform(parms->orotation, parms->center, parms->cscroll, parms->cscale);
                if(rotateRad != 0.f)
                {
                    const irr::f32 c = cosf(rotateRad);
                    const irr::f32 s = sinf(rotateRad);

                    if(mat.isIdentity())
                    {
                        irr::f32* M = mat.pointer();
                        M[0] = c;
                        M[1] = s;
                        M[4] = -s;
                        M[5] = c;
                        M[8] = (irr::f32)(parms->rcenter.X * ( s - c) + parms->rcenter.Y);
                        M[9] = (irr::f32)(-parms->rcenter.Y * ( s + c) + parms->rcenter.X);
                        M[10] = 1;
                        M[15] = 1;
                    }
                    else
                    {
                        irr::core::matrix4  rot;
                        irr::f32  M[16];
                        memset(M, 0, 16*sizeof(irr::f32));

                        M[0] = c;
                        M[1] = s;
                        M[4] = -s;
                        M[5] = c;
                        M[8] = (irr::f32)(parms->rcenter.X * ( s - c) + parms->rcenter.Y);
                        M[9] = (irr::f32)(-parms->rcenter.Y * ( s + c) + parms->rcenter.X);
                        M[10] = 1;
                        M[15] = 1;
                        rot.setM(M);

                        mat *= rot;
                    }
                }
            }   
            lastTime = timeMs;
        }
    }


    //! Writes attributes of the scene node animator.
    void TSceneNodeAnimatorMaterialLayer::serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options) const
    {
        /*
        out->addInt("TimePerFrame", TimePerFrame);
        out->addBool("Loop", Loop);

        // add one texture in addition when serializing for editors
        // to make it easier to add textures quickly

        u32 count = Textures.size();
        if ( options && (options->Flags & io::EARWF_FOR_EDITOR))
        count += 1;

        for (u32 i=0; i<count; ++i)
        {
        core::stringc tname = "Texture";
        tname += (int)(i+1);

        out->addTexture(tname.c_str(), i<Textures.size() ? Textures[i] : 0);
        }
        */
    }

    //! Reads attributes of the scene node animator.
    void TSceneNodeAnimatorMaterialLayer::deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options)
    { 
        /*
        TimePerFrame = in->getAttributeAsInt("TimePerFrame");
        Loop = in->getAttributeAsBool("Loop");

        clearTextures();

        for(u32 i=1; true; ++i)
        {
        core::stringc tname = "Texture";
        tname += (int)i;

        if (in->existsAttribute(tname.c_str()))
        {
        video::ITexture* tex = in->getAttributeAsTexture(tname.c_str());
        if (tex)
        {
        tex->grab();
        Textures.push_back(tex);
        }
        }
        else
        break;
        }
        */
    }

    irr::scene::ISceneNodeAnimator* TSceneNodeAnimatorMaterialLayer::createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager)
    {
        TSceneNodeAnimatorMaterialLayer * newAnimator = 
            new TSceneNodeAnimatorMaterialLayer();

        return newAnimator;
    }

    void TSceneNodeAnimatorMaterialLayer::addMaterialRef(irr::core::stringc name, irr::video::SMaterialLayer& ref, AMLParms* parms)
    {
        parms->grab();
        parms->layer = &ref;
        Materials[name] = parms;
    }

    AMLParms* TSceneNodeAnimatorMaterialLayer::getMaterialParms(irr::core::stringc name)
    {
        return Materials[name];
    }



} // end namespace isl

