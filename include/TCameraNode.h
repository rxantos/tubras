//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#ifndef _TCAMERANODE_H_
#define _TCAMERANODE_H_

namespace Tubras
{
    class TCameraNode : public ICameraSceneNode
    {
        friend class TNodeFactory;

    private:
        void recalculateProjectionMatrix();
        void recalculateViewArea();

        TVector3            m_target;
        TVector3            m_upVector;

        f32                 m_fovy;	        // Field of view, in radians. 
        f32                 m_aspect;	    // Aspect ratio. 
        f32                 m_nearPlane;	// value of the near view-plane. 
        f32                 m_farPlane;	    // Z-value of the far view-plane.

        SViewFrustum        m_viewArea;

    protected:
        TCameraNode(ISceneNode* parent, ISceneManager* mgr);

    public:

        virtual ~TCameraNode();

        int initialize();
        //! Sets the projection matrix of the camera. The core::matrix4 class has some methods
        //! to build a projection matrix. e.g: core::matrix4::buildProjectionMatrixPerspectiveFovLH
        //! \param projection: The new projection matrix of the camera. 
        virtual void setProjectionMatrix(const core::matrix4& projection);

        //! Gets the current projection matrix of the camera
        //! \return Returns the current projection matrix of the camera.
        virtual const core::matrix4& getProjectionMatrix() const;

        //! Gets the current view matrix of the camera
        //! \return Returns the current view matrix of the camera.
        virtual const core::matrix4& getViewMatrix() const;

        //! It is possible to send mouse and key events to the camera. Most cameras
        //! may ignore this input, but camera scene nodes which are created for 
        //! example with scene::ISceneManager::addMayaCameraSceneNode or
        //! scene::ISceneManager::addMeshViewerCameraSceneNode, may want to get this input
        //! for changing their position, look at target or whatever. 
        virtual bool OnEvent(const SEvent& event);

        //! sets the look at target of the camera
        //! \param pos: Look at target of the camera.
        virtual void setTarget(const core::vector3df& pos);

        //! Gets the current look at target of the camera
        //! \return Returns the current look at target of the camera
        virtual core::vector3df getTarget() const;

        //! Sets the up vector of the camera.
        //! \param pos: New upvector of the camera.
        virtual void setUpVector(const core::vector3df& pos);

        //! Gets the up vector of the camera.
        //! \return Returns the up vector of the camera.
        virtual core::vector3df getUpVector() const;

        //! Gets distance from the camera to the near plane.
        //! \return Value of the near plane of the camera.
        virtual f32 getNearValue() const;

        //! Gets the distance from the camera to the far plane.
        //! \return Value of the far plane of the camera.
        virtual f32 getFarValue() const;

        //! Get the aspect ratio of the camera.
        //! \return The aspect ratio of the camera.
        virtual f32 getAspectRatio() const;

        //! Gets the field of view of the camera.
        //! \return Field of view of the camera
        virtual f32 getFOV() const;

        //! Sets the value of the near clipping plane. (default: 1.0f)
        virtual void setNearValue(f32 zn);

        //! Sets the value of the far clipping plane (default: 2000.0f)
        virtual void setFarValue(f32 zf);

        //! Sets the aspect ratio (default: 4.0f / 3.0f)
        virtual void setAspectRatio(f32 aspect);

        //! Sets the field of view (Default: PI / 3.5f)
        virtual void setFOV(f32 fovy);

        //! PreRender event
        virtual void OnRegisterSceneNode();

        //! Render
        virtual void render();

        //! Returns the axis aligned bounding box of this node
        virtual const core::aabbox3d<f32>& getBoundingBox() const;

        //! Returns the view area. Sometimes needed by bsp or lod render nodes.
        virtual const SViewFrustum* getViewFrustum() const;

        //! Disables or enables the camera to get key or mouse inputs.
        //! If this is set to true, the camera will respond to key inputs
        //! otherwise not.
        virtual void setInputReceiverEnabled(bool enabled);

        //! Returns if the input receiver of the camera is currently enabled.
        virtual bool isInputReceiverEnabled() const;

        //! Writes attributes of the scene node.
        virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

        //! Reads attributes of the scene node.
        virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

        //! Returns type of the scene node
        virtual ESCENE_NODE_TYPE getType() const { return ESNT_CAMERA; }

        virtual core::vector3df getAbsolutePosition() const;


    };
} 
#endif
