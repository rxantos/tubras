// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CSceneNodeAnimatorMaterialLayer.h"
#include "ITexture.h"


namespace lsl
{


//! constructor
    CSceneNodeAnimatorMaterialLayer::CSceneNodeAnimatorMaterialLayer() : lastTime(0)
{
	#ifdef _DEBUG
	setDebugName("CSceneNodeAnimatorMaterialLayer");
	#endif

}



//! destructor
CSceneNodeAnimatorMaterialLayer::~CSceneNodeAnimatorMaterialLayer()
{
}

//! animates a scene node
void CSceneNodeAnimatorMaterialLayer::animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs)
{
    irr::u32   t = timeMs - lastTime;

    if(t)
    {
        irr::f32 delta = t / 1000.f;
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
            
            mat.buildTextureTransform(0.0f, parms->center, parms->cscroll, parms->cscale);
            
            if(rotateRad != 0.f)
            {
                irr::core::matrix4  rot;
                irr::f32  M[16];
                memset(M, 0, 16*sizeof(irr::f32));

                const irr::f32 c = cosf(rotateRad);
                const irr::f32 s = sinf(rotateRad);

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
        lastTime = timeMs;
    }
}


//! Writes attributes of the scene node animator.
void CSceneNodeAnimatorMaterialLayer::serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options) const
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
void CSceneNodeAnimatorMaterialLayer::deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options)
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

irr::scene::ISceneNodeAnimator* CSceneNodeAnimatorMaterialLayer::createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager)
{
	CSceneNodeAnimatorMaterialLayer * newAnimator = 
		new CSceneNodeAnimatorMaterialLayer();

	return newAnimator;
}

void CSceneNodeAnimatorMaterialLayer::addMaterialRef(irr::core::stringc name, irr::video::SMaterialLayer& ref, AMLParms* parms)
{
    parms->layer = &ref;
    Materials[name] = parms;
}

AMLParms* CSceneNodeAnimatorMaterialLayer::getMaterialParms(irr::core::stringc name)
{
    return Materials[name];
}



} // end namespace isl

