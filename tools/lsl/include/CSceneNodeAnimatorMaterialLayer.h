// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_SCENE_NODE_ANIMATOR_MATERIAL_LAYER_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_MATERIAL_LAYER_H_INCLUDED__

#include "irrMap.h"
#include "ISceneNode.h"

namespace lsl
{

    typedef struct _AMLParms_ {
        irr::video::SMaterialLayer*     layer;
        irr::core::vector2df            cscroll;
        irr::core::vector2df            scroll;
        irr::core::vector2df            cscale;
        irr::core::vector2df            scale;
        irr::core::vector2df            center;     // texture center
        irr::core::vector2df            rcenter;    // animated rotation center
        irr::f32                        crotation;
        irr::f32                        rotation;
        irr::f32                        orotation;
        bool                            active;

        _AMLParms_() : layer(0), 
            cscroll(0,0),
            scroll(0,0),
            cscale(1,1),
            scale(0),
            center(0,0),
            rcenter(0.5f, 0.5f),
            crotation(0),
            rotation(0),
            orotation(0),
            active(true)
        {}
        
    } AMLParms;

    class CSceneNodeAnimatorMaterialLayer : public irr::scene::ISceneNodeAnimator
	{
	public:

        typedef irr::core::map<irr::core::stringc, AMLParms*> MLMAP;

		//! constructor
		CSceneNodeAnimatorMaterialLayer();

		//! destructor
		virtual ~CSceneNodeAnimatorMaterialLayer();

        //! adds a material layer to animate
        virtual void addMaterialRef(irr::core::stringc name, irr::video::SMaterialLayer& ref, AMLParms* parms);

        virtual AMLParms* getMaterialParms(irr::core::stringc name);

		//! animates a scene node
        virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);

		//! Writes attributes of the scene node animator.
        virtual void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const;

		//! Reads attributes of the scene node animator.
        virtual void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0);

		//! Returns type of the scene node animator
        virtual irr::scene::ESCENE_NODE_ANIMATOR_TYPE getType() const { return irr::scene::ESNAT_TEXTURE; }
		
		//! Creates a clone of this animator.
		/** Please note that you will have to drop
		(IReferenceCounted::drop()) the returned pointer after calling
		this. */
        virtual irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager=0);

	private:

        irr::u32               lastTime;

		MLMAP                  Materials;
	};


} // end namespace isl

#endif

