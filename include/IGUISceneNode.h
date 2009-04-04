// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_GUI_SCENE_NODE_H_INCLUDED__
#define __I_GUI_SCENE_NODE_H_INCLUDED__

#include "ISceneNode.h"
#include "IMeshSceneNode.h"
#include "IGUIElement.h"

namespace irr
{
namespace scene
{

//! A scene node for displaying 2d text at a position in three dimensional space
class IGUISceneNode : public ISceneNode
{
public:

	//! constructor
	IGUISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
            const core::vector2df& size = core::vector2df(1, 1),
            const core::vector3df& normal = core::vector3df(0, 0, 1),
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
            const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)) :
    ISceneNode(parent, mgr, id, position, rotation, scale) {}

    virtual void addGUIElement(irr::gui::IGUIElement* element) = 0;
};

} // end namespace scene
} // end namespace irr


#endif

