//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {

    //-----------------------------------------------------------------------
    //                           T C a m e r a N o d e
    //-----------------------------------------------------------------------
    TCameraNode::TCameraNode(ISceneNode* parent, s32 id) : ICameraSceneNode(parent, getApplication()->getSceneManager(), id),
        m_targetAndRotationAreBound(0)
    {
        // set default view

        m_upVector.set(0.0f, 1.0f, 0.0f);
        m_target.set(0,0,100);

        // set default projection

        m_fovy = core::PI / 2.5f;	// Field of view, in radians. 
        m_aspect = 4.0f / 3.0f;	    // m_aspect ratio. 
        m_nearPlane = 0.1f;	    	// value of the near view-plane. 
        m_farPlane = 3000.0f;		// Z-value of the far view-plane. 

        video::IVideoDriver* d = getApplication()->getSceneManager()->getVideoDriver();
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
    void TCameraNode::setProjectionMatrix(const core::matrix4& projection, bool isOrthogonal)
    {
	    IsOrthogonal = isOrthogonal;
        m_viewArea.getTransform ( video::ETS_PROJECTION ) = projection;
    }

    //-----------------------------------------------------------------------
    //                 g e t P r o j e c t i o n M a t r i x
    //-----------------------------------------------------------------------
    const core::matrix4& TCameraNode::getProjectionMatrix() const
    {
        return m_viewArea.getTransform( video::ETS_PROJECTION );
    }

    //-----------------------------------------------------------------------
    //                     g e t V i e w M a t r i x
    //-----------------------------------------------------------------------
    const core::matrix4& TCameraNode::getViewMatrix() const
    {
        return m_viewArea.getTransform ( video::ETS_VIEW );
    }

    //-----------------------------------------------------------------------
    //               s e t V i e w M a t r i x A f f e c t o r
    //-----------------------------------------------------------------------
    void TCameraNode::setViewMatrixAffector(const core::matrix4& affector)
    {
        m_affector = affector;
    }

    //-----------------------------------------------------------------------
    //               g e t V i e w M a t r i x A f f e c t o r
    //-----------------------------------------------------------------------
    const core::matrix4& TCameraNode::getViewMatrixAffector() const
    {
        return m_affector;
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
    const core::vector3df& TCameraNode::getTarget() const
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
    const core::vector3df& TCameraNode::getUpVector() const
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
    //                        s e t R o t a t i o n
    //-----------------------------------------------------------------------
    void TCameraNode::setRotation(const core::vector3df& rotation)
    {
        if(m_targetAndRotationAreBound)
            m_target = getAbsolutePosition() + rotation.rotationToDirection();

        ISceneNode::setRotation(rotation);
    }

    //-----------------------------------------------------------------------
    //                b i n d T a r g e t A n d R o t a t i o n
    //-----------------------------------------------------------------------
    void TCameraNode::bindTargetAndRotation(bool bound)
    {
	    m_targetAndRotationAreBound = bound;
    }

    //-----------------------------------------------------------------------
    //          g e t T a r g e t A n d R o t a t i o n B i n d i n g
    //-----------------------------------------------------------------------
    bool TCameraNode::getTargetAndRotationBinding(void) const
    {
        return m_targetAndRotationAreBound;
    }

    //-----------------------------------------------------------------------
    //           r e c a l c u l a t e P r o j e c t i o n M a t r i x
    //-----------------------------------------------------------------------
    void TCameraNode::recalculateProjectionMatrix()
    {
        m_viewArea.getTransform ( video::ETS_PROJECTION ).buildProjectionMatrixPerspectiveFovLH(m_fovy, m_aspect, m_nearPlane, m_farPlane);
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

        if ( core::equals (fabsf ( dp ), (f32)1.f ) )
        {
            up.X += 0.5f;
        }

        m_viewArea.getTransform(video::ETS_VIEW).buildCameraLookAtMatrixLH(pos, m_target, up);
        m_viewArea.getTransform(video::ETS_VIEW) *= m_affector;
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
            driver->setTransform(video::ETS_PROJECTION, m_viewArea.getTransform ( video::ETS_PROJECTION ) );
            driver->setTransform(video::ETS_VIEW, m_viewArea.getTransform ( video::ETS_VIEW ) );
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

        core::matrix4 m ( core::matrix4::EM4CONST_NOTHING );
        m.setbyproduct_nocheck (	m_viewArea.getTransform (video::ETS_PROJECTION),
            m_viewArea.getTransform (video::ETS_VIEW)
            );
        m_viewArea.setFrom(m);
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

    //-----------------------------------------------------------------------
    //                            g e t T y p e
    //-----------------------------------------------------------------------
    ESCENE_NODE_TYPE TCameraNode::getType() const
    {
        return (ESCENE_NODE_TYPE) MAKE_IRR_ID('t','c','a','m');
    }

}

