// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_SCENE_NODE_ANIMATOR_MATERIAL_LAYER_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_MATERIAL_LAYER_H_INCLUDED__

#include "irrMap.h"
#include "ISceneNode.h"

namespace irr
{
namespace scene
{

    typedef struct _AMLParms_ {
        irr::video::SMaterialLayer*     layer;
        irr::core::vector2df            scroll;
        irr::core::vector2df            scale;
        irr::f32                        rotation;
        bool                            active;

        _AMLParms_() : layer(0), 
            scroll(0,0),
            scale(0),
            rotation(0),
            active(true)
        {}
        
    } AMLParms;

	class CSceneNodeAnimatorMaterialLayer : public ISceneNodeAnimator
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
		virtual void animateNode(ISceneNode* node, u32 timeMs);

		//! Writes attributes of the scene node animator.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

		//! Reads attributes of the scene node animator.
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

		//! Returns type of the scene node animator
		virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_TEXTURE; }
		
		//! Creates a clone of this animator.
		/** Please note that you will have to drop
		(IReferenceCounted::drop()) the returned pointer after calling
		this. */
		virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager=0);

	private:

        irr::u32               lastTime;

		MLMAP                  Materials;
	};


} // end namespace scene
} // end namespace irr

#endif

