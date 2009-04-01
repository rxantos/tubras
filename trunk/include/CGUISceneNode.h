// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_GUI_SCENE_NODE_H_INCLUDED__
#define __C_GUI_SCENE_NODE_H_INCLUDED__

#include "IGUISceneNode.h"
#include "IGUIElement.h"
#include "S3DVertex.h"

namespace irr
{
namespace scene
{
	class CGUISceneNode : public IGUISceneNode
	{
	public:

		//! constructor
		CGUISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
            const core::vector2df& size = core::vector2df(1, 1),
            const core::vector3df& normal = core::vector3df(0, 0, 1),
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));

		//! destructor
		virtual ~CGUISceneNode();

		virtual void OnRegisterSceneNode();

		//! renders the node.
		virtual void render();

		//! returns the axis aligned bounding box of this node
		virtual const core::aabbox3d<f32>& getBoundingBox() const;

		//! adds a gui element to render
        virtual void addGUIElement(gui::IGUIElement* element);

		//! Returns type of the scene node
		virtual ESCENE_NODE_TYPE getType() const { return ESNT_TEXT; }

		virtual video::SMaterial& getMaterial(u32 num)
		{
			return Material;
		}


		//! Get amount of materials used by this scene node.
		/** \return Current amount of materials of this scene node. */
		virtual u32 getMaterialCount() const
		{
			return 1;
		}


	private:
        ISceneManager*  SceneManager;
		core::aabbox3d<f32> Box;
        core::array<irr::gui::IGUIElement*>   Elements;
        video::ITexture*   RenderTarget;
        video::SMaterial Material;
        core::vector3df Normal;
        video::S3DVertex Vertices[4];

	};

} // end namespace scene
} // end namespace irr

#endif

