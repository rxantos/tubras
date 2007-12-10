//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T C a m e r a N o d e
    //-----------------------------------------------------------------------
    TCameraNode::TCameraNode(ISceneNode* parent, ISceneManager* mgr) : ICameraSceneNode(parent, mgr, -1)
    {
        // set default view

        // set default view

        UpVector.set(0.0f, 1.0f, 0.0f);
        Target.set(0,0,100);

        // set default projection

        Fovy = core::PI / 2.5f;	// Field of view, in radians. 
        Aspect = 4.0f / 3.0f;	// Aspect ratio. 
        ZNear = 1.0f;		// value of the near view-plane. 
        ZFar = 3000.0f;		// Z-value of the far view-plane. 

        video::IVideoDriver* d = mgr->getVideoDriver();
        if (d)
            Aspect = (f32)d->getCurrentRenderTargetSize().Width /
            (f32)d->getCurrentRenderTargetSize().Height;

        recalculateProjectionMatrix();
        recalculateViewArea();
    }

    //-----------------------------------------------------------------------
    //                          ~ T C a m e r a N o d e
    //-----------------------------------------------------------------------
    TCameraNode::~TCameraNode()
    {
    }

    //-----------------------------------------------------------------------
    //                           i n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TCameraNode::initialize()
    {
        return 0;
    }

    //! Disables or enables the camera to get key or mouse inputs.
    void TCameraNode::setInputReceiverEnabled(bool enabled)
    {
        InputReceiverEnabled = enabled;
    }


    //! Returns if the input receiver of the camera is currently enabled.
    bool TCameraNode::isInputReceiverEnabled() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return InputReceiverEnabled;
    }


    //! Sets the projection matrix of the camera. The core::matrix4 class has some methods
    //! to build a projection matrix. e.g: core::matrix4::buildProjectionMatrixPerspectiveFovLH
    //! \param projection: The new projection matrix of the camera. 
    void TCameraNode::setProjectionMatrix(const core::matrix4& projection)
    {
        ViewArea.Matrices [ video::ETS_PROJECTION ] = projection;
        ViewArea.setTransformState ( video::ETS_PROJECTION );
    }



    //! Gets the current projection matrix of the camera
    //! \return Returns the current projection matrix of the camera.
    const core::matrix4& TCameraNode::getProjectionMatrix() const
    {
        return ViewArea.Matrices [ video::ETS_PROJECTION ];
    }



    //! Gets the current view matrix of the camera
    //! \return Returns the current view matrix of the camera.
    const core::matrix4& TCameraNode::getViewMatrix() const
    {
        return ViewArea.Matrices [ video::ETS_VIEW ];
    }



    //! It is possible to send mouse and key events to the camera. Most cameras
    //! may ignore this input, but camera scene nodes which are created for 
    //! example with scene::ISceneManager::addMayaCameraSceneNode or
    //! scene::ISceneManager::addFPSCameraSceneNode, may want to get this input
    //! for changing their position, look at target or whatever. 
    bool TCameraNode::OnEvent(const SEvent& event)
    {
        return false;
    }



    //! sets the look at target of the camera
    //! \param pos: Look at target of the camera.
    void TCameraNode::setTarget(const core::vector3df& pos)
    {
        Target = pos;
    }



    //! Gets the current look at target of the camera
    //! \return Returns the current look at target of the camera
    core::vector3df TCameraNode::getTarget() const
    {
        return Target;
    }



    //! sets the up vector of the camera
    //! \param pos: New upvector of the camera.
    void TCameraNode::setUpVector(const core::vector3df& pos)
    {
        UpVector = pos;
    }



    //! Gets the up vector of the camera.
    //! \return Returns the up vector of the camera.
    core::vector3df TCameraNode::getUpVector() const
    {
        return UpVector;
    }


    f32 TCameraNode::getNearValue() const 
    {
        return ZNear;
    }

    f32 TCameraNode::getFarValue() const 
    {
        return ZFar;
    }

    f32 TCameraNode::getAspectRatio() const 
    {
        return Aspect;
    }

    f32 TCameraNode::getFOV() const 
    {
        return Fovy;
    }

    void TCameraNode::setNearValue(f32 f)
    {
        ZNear = f;
        recalculateProjectionMatrix();
    }

    void TCameraNode::setFarValue(f32 f)
    {
        ZFar = f;
        recalculateProjectionMatrix();
    }

    void TCameraNode::setAspectRatio(f32 f)
    {
        Aspect = f;
        recalculateProjectionMatrix();
    }

    void TCameraNode::setFOV(f32 f)
    {
        Fovy = f;
        recalculateProjectionMatrix();
    }

    void TCameraNode::recalculateProjectionMatrix()
    {
        ViewArea.Matrices [ video::ETS_PROJECTION ].buildProjectionMatrixPerspectiveFovLH(Fovy, Aspect, ZNear, ZFar);
        ViewArea.setTransformState ( video::ETS_PROJECTION );
    }


    //! prerender
    void TCameraNode::OnRegisterSceneNode()
    {
        // if upvector and vector to the target are the same, we have a
        // problem. so solve this problem:

        core::vector3df pos = getAbsolutePosition();
        core::vector3df tgtv = Target - pos;
        tgtv.normalize();

        core::vector3df up = UpVector;
        up.normalize();

        f32 dp = tgtv.dotProduct(up);

        if ( core::equals ( fabs ( dp ), 1.f ) )
        {
            up.X += 0.5f;
        }

        ViewArea.Matrices [ video::ETS_VIEW ].buildCameraLookAtMatrixLH(pos, Target, up);
        ViewArea.setTransformState ( video::ETS_VIEW );
        recalculateViewArea();

        if ( SceneManager->getActiveCamera () == this )
            SceneManager->registerNodeForRendering(this, ESNRP_CAMERA);

        ISceneNode::OnRegisterSceneNode();
    }



    //! render
    void TCameraNode::render()
    {	
        video::IVideoDriver* driver = SceneManager->getVideoDriver();
        if ( driver)
        {
            driver->setTransform(video::ETS_PROJECTION, ViewArea.Matrices [ video::ETS_PROJECTION ] );
            driver->setTransform(video::ETS_VIEW, ViewArea.Matrices [ video::ETS_VIEW ] );
        }
    }


    //! returns the axis aligned bounding box of this node
    const core::aabbox3d<f32>& TCameraNode::getBoundingBox() const
    {
        return ViewArea.getBoundingBox();
    }



    //! returns the view frustum. needed sometimes by bsp or lod render nodes.
    const SViewFrustum* TCameraNode::getViewFrustum() const
    {
        return &ViewArea;
    }

    core::vector3df TCameraNode::getAbsolutePosition() const
    {
        return AbsoluteTransformation.getTranslation();
    }

    void TCameraNode::recalculateViewArea()
    {
        ViewArea.cameraPosition = getAbsolutePosition();
        ViewArea.setFrom ( ViewArea.Matrices [ SViewFrustum::ETS_VIEW_PROJECTION_3 ] );
        /*
        video::IVideoDriver* driver = SceneManager->getVideoDriver();
        if ( driver)
        {
        driver->setTransform(video::ETS_PROJECTION, ViewArea.Matrices [ video::ETS_PROJECTION ] );
        driver->setTransform(video::ETS_VIEW, ViewArea.Matrices [ video::ETS_VIEW ] );
        }
        */
    }


    //! Writes attributes of the scene node.
    void TCameraNode::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
    {
        ISceneNode::serializeAttributes(out, options);

        out->addVector3d("Target", Target);
        out->addVector3d("UpVector", UpVector);
        out->addFloat("Fovy", Fovy);
        out->addFloat("Aspect", Aspect);
        out->addFloat("ZNear", ZNear);
        out->addFloat("ZFar", ZFar);
    }


    //! Reads attributes of the scene node.
    void TCameraNode::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
    {
        ISceneNode::deserializeAttributes(in, options);

        Target = in->getAttributeAsVector3d("Target");
        UpVector = in->getAttributeAsVector3d("UpVector");
        Fovy = in->getAttributeAsFloat("Fovy");
        Aspect = in->getAttributeAsFloat("Aspect");
        ZNear = in->getAttributeAsFloat("ZNear");
        ZFar = in->getAttributeAsFloat("ZFar");

        recalculateProjectionMatrix();
        recalculateViewArea();	
    }
}