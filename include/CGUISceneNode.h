// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_GUI_SCENE_NODE_H_INCLUDED__
#define __C_GUI_SCENE_NODE_H_INCLUDED__

#include "IGUISceneNode.h"
#include "IGUIElement.h"
#include "IGUIImage.h"
#include "IEventReceiver.h"
#include "S3DVertex.h"

namespace irr
{
namespace scene
{
    enum EGUI_NODE_EVENT_TYPE
    {
        EGNET_ACTIVATED = 0,
        EGNET_MAX
    };

    struct SGUISceneNodeEvent
    {
        EGUI_NODE_EVENT_TYPE EventType;
        s32     UserData;
    };

   
    class CGUISceneNode : public IGUISceneNode, gui::IGUIElement
	{
	public:

		//! constructor
		CGUISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
            const core::stringc& cursorImageFileName,
            IEventReceiver* eventReceiver=0,
            f32 activationDistance=5.f,
            const video::SColor& backgroundColor = video::SColor(255,128,128,128),
            const core::dimension2du& textureSize = core::dimension2du(256, 256),
            const core::vector2df& size = core::vector2df(1, 1),
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));

		//! destructor
		virtual ~CGUISceneNode();

        //! application must feed events...
        virtual bool postEventFromUser(const SEvent& event);

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

		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
        virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

        void updateHoveredElement(core::position2d<s32> mousePos);
        bool setFocus(gui::IGUIElement* element);
        gui::IGUIElement* getNextElement(bool reverse, bool group);

    public:
        core::vector3df debug;
	//private:
        ISceneManager*  SceneManager;
		core::aabbox3d<f32> Box;
        video::ITexture*   RenderTarget;
        video::SMaterial Material;
        video::S3DVertex Vertices[4];
        video::SColor   BColor;
        core::plane3df Plane;
        core::triangle3df Triangle,Triangle2;
        f32 ActivationDistance;
        gui::IGUIImage* Cursor;
        core::position2di CursorPos;
        bool Activated, Draw;
        core::vector3df UpperLeftCorner;
        core::vector2df GeometrySize;
        IEventReceiver* EventReceiver;   

        core::position2d<s32> LastHoveredMousePos;
        gui::IGUIElement* Hovered;
        gui::IGUIElement* Focus;
	};

} // end namespace scene
} // end namespace irr

#endif

