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
#include "tubras.h"

namespace Tubras {

    //-----------------------------------------------------------------------
    //                           T C a m e r a N o d e
    //-----------------------------------------------------------------------
    TCameraNode::TCameraNode(ISceneNode* parent, ISceneManager* mgr) : ICameraSceneNode(parent, mgr, -1)
    {
        // set default view

        // set default view

        m_upVector.set(0.0f, 1.0f, 0.0f);
        m_target.set(0,0,100);

        // set default projection

        m_fovy = core::PI / 2.5f;	// Field of view, in radians. 
        m_aspect = 4.0f / 3.0f;	// m_aspect ratio. 
        m_nearPlane = 1.0f;		// value of the near view-plane. 
        m_farPlane = 3000.0f;		// Z-value of the far view-plane. 

        video::IVideoDriver* d = mgr->getVideoDriver();
        if (d)
            m_aspect = (f32)d->getCurrentRenderTargetSize().Width /
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

    //-----------------------------------------------------------------------
    //               s e t I n p u t R e c e i v e r E n a b l e d
    //-----------------------------------------------------------------------
    void TCameraNode::setInputReceiverEnabled(bool enabled)
    {
    }

    //-----------------------------------------------------------------------
    //                i s I n p u t R e c e i v e r E n a b l e d
    //-----------------------------------------------------------------------
    bool TCameraNode::isInputReceiverEnabled() const
    {
        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
        return false;
    }

    //-----------------------------------------------------------------------
    //                 s e t P r o j e c t i o n M a t r i x
    //-----------------------------------------------------------------------
    void TCameraNode::setProjectionMatrix(const core::matrix4& projection)
    {
        m_viewArea.Matrices [ video::ETS_PROJECTION ] = projection;
        m_viewArea.setTransformState ( video::ETS_PROJECTION );
    }

    //-----------------------------------------------------------------------
    //                 g e t P r o j e c t i o n M a t r i x
    //-----------------------------------------------------------------------
    const core::matrix4& TCameraNode::getProjectionMatrix() const
    {
        return m_viewArea.Matrices [ video::ETS_PROJECTION ];
    }

    //-----------------------------------------------------------------------
    //                     g e t V i e w M a t r i x
    //-----------------------------------------------------------------------
    const core::matrix4& TCameraNode::getViewMatrix() const
    {
        return m_viewArea.Matrices [ video::ETS_VIEW ];
    }

    //-----------------------------------------------------------------------
    //                         O n E v e n t
    //-----------------------------------------------------------------------
    bool TCameraNode::OnEvent(const SEvent& event)
    {
        return false;
    }

    //-----------------------------------------------------------------------
    //                         s e t T a r g e t
    //-----------------------------------------------------------------------
    void TCameraNode::setTarget(const core::vector3df& pos)
    {
        m_target = pos;
    }

    //-----------------------------------------------------------------------
    //                         g e t T a r g e t
    //-----------------------------------------------------------------------
    core::vector3df TCameraNode::getTarget() const
    {
        return m_target;
    }

    //-----------------------------------------------------------------------
    //                       s e t U p V e c t o r
    //-----------------------------------------------------------------------
    void TCameraNode::setUpVector(const core::vector3df& pos)
    {
        m_upVector = pos;
    }

    //-----------------------------------------------------------------------
    //                       g e t U p V e c t o r
    //-----------------------------------------------------------------------
    core::vector3df TCameraNode::getUpVector() const
    {
        return m_upVector;
    }

    //-----------------------------------------------------------------------
    //                      g e t N e a r V a l u e
    //-----------------------------------------------------------------------
    f32 TCameraNode::getNearValue() const 
    {
        return m_nearPlane;
    }

    //-----------------------------------------------------------------------
    //                        g e t F a r V a l u e
    //-----------------------------------------------------------------------
    f32 TCameraNode::getFarValue() const 
    {
        return m_farPlane;
    }

    //-----------------------------------------------------------------------
    //                      g e t A s p e c t R a t i o 
    //-----------------------------------------------------------------------
    f32 TCameraNode::getAspectRatio() const 
    {
        return m_aspect;
    }

    //-----------------------------------------------------------------------
    //                           g e t F O V 
    //-----------------------------------------------------------------------
    f32 TCameraNode::getFOV() const 
    {
        return m_fovy;
    }

    //-----------------------------------------------------------------------
    //                       s e t N e a r V a l u e
    //-----------------------------------------------------------------------
    void TCameraNode::setNearValue(f32 f)
    {
        m_nearPlane = f;
        recalculateProjectionMatrix();
    }

    //-----------------------------------------------------------------------
    //                       s e t F a r V a l u e
    //-----------------------------------------------------------------------
    void TCameraNode::setFarValue(f32 f)
    {
        m_farPlane = f;
        recalculateProjectionMatrix();
    }

    //-----------------------------------------------------------------------
    //                       s e t A s p e c t R a t i o 
    //-----------------------------------------------------------------------
    void TCameraNode::setAspectRatio(f32 f)
    {
        m_aspect = f;
        recalculateProjectionMatrix();
    }

    //-----------------------------------------------------------------------
    //                            s e t F O V
    //-----------------------------------------------------------------------
    void TCameraNode::setFOV(f32 f)
    {
        m_fovy = f;
        recalculateProjectionMatrix();
    }

    //-----------------------------------------------------------------------
    //           r e c a l c u l a t e P r o j e c t i o n M a t r i x
    //-----------------------------------------------------------------------
    void TCameraNode::recalculateProjectionMatrix()
    {
        m_viewArea.Matrices [ video::ETS_PROJECTION ].buildProjectionMatrixPerspectiveFovLH(m_fovy, m_aspect, m_nearPlane, m_farPlane);
        m_viewArea.setTransformState ( video::ETS_PROJECTION );
    }

    //-----------------------------------------------------------------------
    //                  O n R e g i s t r S c e n e N o d e
    //-----------------------------------------------------------------------
    void TCameraNode::OnRegisterSceneNode()
    {
        // if upvector and vector to the target are the same, we have a
        // problem. so solve this problem:

        TVector3 pos = getAbsolutePosition();
        TVector3 tgtv = m_target - pos;
        tgtv.normalize();

        TVector3 up = m_upVector;
        up.normalize();

        f32 dp = tgtv.dotProduct(up);

        if ( core::equals ( fabs ( dp ), 1.f ) )
        {
            up.X += 0.5f;
        }

        m_viewArea.Matrices [ video::ETS_VIEW ].buildCameraLookAtMatrixLH(pos, m_target, up);
        m_viewArea.setTransformState ( video::ETS_VIEW );
        recalculateViewArea();

        if ( SceneManager->getActiveCamera () == this )
            SceneManager->registerNodeForRendering(this, ESNRP_CAMERA);

        ISceneNode::OnRegisterSceneNode();
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TCameraNode::render()
    {	
        video::IVideoDriver* driver = SceneManager->getVideoDriver();
        if ( driver)
        {
            driver->setTransform(video::ETS_PROJECTION, m_viewArea.Matrices [ video::ETS_PROJECTION ] );
            driver->setTransform(video::ETS_VIEW, m_viewArea.Matrices [ video::ETS_VIEW ] );
        }
    }

    //-----------------------------------------------------------------------
    //                      g e t B o u n d i n g B o x
    //-----------------------------------------------------------------------
    const core::aabbox3d<f32>& TCameraNode::getBoundingBox() const
    {
        return m_viewArea.getBoundingBox();
    }

    //-----------------------------------------------------------------------
    //                       g e t V i e w F r u s t u m
    //-----------------------------------------------------------------------
    const SViewFrustum* TCameraNode::getViewFrustum() const
    {
        return &m_viewArea;
    }

    //-----------------------------------------------------------------------
    //                  g e t A b s o l u t e P o s i t i o n
    //-----------------------------------------------------------------------
    core::vector3df TCameraNode::getAbsolutePosition() const
    {
        return AbsoluteTransformation.getTranslation();
    }

    //-----------------------------------------------------------------------
    //                 r e c a l c u l a t e V i e w A r e a 
    //-----------------------------------------------------------------------
    void TCameraNode::recalculateViewArea()
    {
        m_viewArea.cameraPosition = getAbsolutePosition();
        m_viewArea.setFrom ( m_viewArea.Matrices [ SViewFrustum::ETS_VIEW_PROJECTION_3 ] );
    }

    //-----------------------------------------------------------------------
    //                 s e r i a l i z e A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TCameraNode::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
    {
        ISceneNode::serializeAttributes(out, options);

        out->addVector3d("m_target", m_target);
        out->addVector3d("m_upVector", m_upVector);
        out->addFloat("m_fovy", m_fovy);
        out->addFloat("m_aspect", m_aspect);
        out->addFloat("m_nearPlane", m_nearPlane);
        out->addFloat("m_farPlane", m_farPlane);
    }

    //-----------------------------------------------------------------------
    //                 d e s e r i a l i z e A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TCameraNode::deserializeAttributes(io::IAttributes* in, 
        io::SAttributeReadWriteOptions* options)
    {
        ISceneNode::deserializeAttributes(in, options);

        m_target = in->getAttributeAsVector3d("m_target");
        m_upVector = in->getAttributeAsVector3d("m_upVector");
        m_fovy = in->getAttributeAsFloat("m_fovy");
        m_aspect = in->getAttributeAsFloat("m_aspect");
        m_nearPlane = in->getAttributeAsFloat("m_nearPlane");
        m_farPlane = in->getAttributeAsFloat("m_farPlane");

        recalculateProjectionMatrix();
        recalculateViewArea();	
    }
}