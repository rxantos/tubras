// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGUISceneNode.h"
#include "ISceneManager.h"
#include "IVideoDriver.h"
#include "ICameraSceneNode.h"
#include "os.h"


namespace irr
{
namespace scene
{


//! constructor
CGUISceneNode::CGUISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
            const core::vector2df& size,
            const core::vector3df& normal,
			const core::vector3df& position,
			const core::vector3df& rotation,
			const core::vector3df& scale)
	: IGUISceneNode(parent, mgr, id, size, position, rotation, scale),
    SceneManager(mgr), Normal(normal)
{
	#ifdef _DEBUG
	setDebugName("CGUISceneNode");
	#endif

    video::IVideoDriver* driver = mgr->getVideoDriver();

	if (driver->queryFeature(video::EVDF_RENDER_TO_TARGET))
	{
		RenderTarget = driver->addRenderTargetTexture(core::dimension2d<u32>(256,256), "GUISceneNodeRTT");
	}

        Material.Wireframe = false;
        Material.Lighting = false;

        f32 m_halfSize = size/2.f;

        
        Normal.normalize();

        /*
        core::vector3df p1(-m_halfSize,m_halfSize,0),p2(m_halfSize,m_halfSize,0),p3(m_halfSize,-m_halfSize,0),p4(-m_halfSize,-m_halfSize,0);
        if(m_normal.equals(TVector3::UNIT_Y))
        {
            p1 = core::vector3df(-m_halfSize,0,m_halfSize);
            p2 = core::vector3df(m_halfSize,0,m_halfSize);
            p3 = core::vector3df(m_halfSize,0,-m_halfSize);
            p4 = core::vector3df(-m_halfSize,0,-m_halfSize);
        } else if(m_normal.equals(TVector3::UNIT_X))
        {
            p1 = core::vector3df(0,m_halfSize,-m_halfSize);
            p2 = core::vector3df(0,m_halfSize,m_halfSize);
            p3 = core::vector3df(0,-m_halfSize,m_halfSize);
            p4 = core::vector3df(0,-m_halfSize,-m_halfSize);
        }
        */


        Vertices[0] = S3DVertex(p1, Normal ,color,TVector2f(0,1));
        Vertices[1] = S3DVertex(p2, Normal ,color,TVector2f(1,1));
        Vertices[2] = S3DVertex(p3, Normal ,color,TVector2f(1,0));
        Vertices[3] = S3DVertex(p4, Normal,color,TVector2f(0,0));

        Box.reset(m_vertices[0].Pos);
        for (s32 i=1; i<4; ++i)
            Box.addInternalPoint(Vertices[i].Pos);
}

//! destructor
CGUISceneNode::~CGUISceneNode()
{
}

void CGUISceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this, ESNRP_TRANSPARENT);

	ISceneNode::OnRegisterSceneNode();
}

//! renders the node.
void CGUISceneNode::render()
{
    video::IVideoDriver* driver = SceneManager->getVideoDriver();
    gui::IGUIEnvironment* env = SceneManager->getGUIEnvironment();

    // set render target texture
    driver->setRenderTarget(RenderTarget, true, true, video::SColor(0,0,0,255));

    // draw the gui elements
    for(u32 i=0; i< Elements.size(); i++)
    {
        gui::IGUIElement* element = Elements[i];
        element->draw();
    }

    // set back old render target
    // The buffer might have been distorted, so clear it
    driver->setRenderTarget(0, true, true, 0);

}


//! returns the axis aligned bounding box of this node
const core::aabbox3d<f32>& CGUISceneNode::getBoundingBox() const
{
	return Box;
}


} // end namespace scene
} // end namespace irr

