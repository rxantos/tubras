//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                     T P l a y e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    TPlayerController::TPlayerController(const TString& controllerName,ICameraSceneNode* camera,
        ISceneNode* playerNode) : TController(controllerName,playerNode)
    {

        m_camera = camera;
        m_rotating = false;
        m_pitching = false;
        m_translating = false;
        m_mouseMoved = false;
        m_zoomed = false;
        m_translate = TVector3::ZERO;
        m_pitch = 0.0f;
        m_rotate = 0.0f;
        m_shift = 1.0f;
        m_inverted = -1.0f;
        memset(m_actions,0,sizeof(m_actions));

        m_orgVelocity =
        m_velocity = getAppConfig()->getFloat("velocity","options",3.0);
        m_angularVelocity = getAppConfig()->getFloat("angularvelocity","options",3.0);
        m_maxVertAngle = getAppConfig()->getFloat("maxvertangle","options",88.0);

        m_mouseDelegate = EVENT_DELEGATE(TPlayerController::procMouseMove);
        acceptEvent("input.mouse.move",m_mouseDelegate);

        m_cmdDelegate = EVENT_DELEGATE(TPlayerController::procCmd);

        m_frwdID = acceptEvent("frwd",m_cmdDelegate);
        m_backID = acceptEvent("back",m_cmdDelegate);
        m_leftID = acceptEvent("left",m_cmdDelegate);
        m_rghtID = acceptEvent("rght",m_cmdDelegate);
        m_rotlID = acceptEvent("rotl",m_cmdDelegate);
        m_rotrID = acceptEvent("rotr",m_cmdDelegate);
        m_mvupID = acceptEvent("mvup",m_cmdDelegate);
        m_mvdnID = acceptEvent("mvdn",m_cmdDelegate);
        m_rotfID = acceptEvent("rotf",m_cmdDelegate);
        m_rotbID = acceptEvent("rotb",m_cmdDelegate);
        m_avelID = acceptEvent("avel",m_cmdDelegate);

        m_invertMouseID = acceptEvent("invert-mouse",m_cmdDelegate);
        m_toggleMouseID = acceptEvent("toggle-mouse",m_cmdDelegate);
        m_zoomedInID = acceptEvent("zoomed.in",m_cmdDelegate);
        m_zoomedOutID = acceptEvent("zoomed.out",m_cmdDelegate);

        m_cmdDelegate->setEnabled(false);
        m_mouseDelegate->setEnabled(false);
    }

    //-----------------------------------------------------------------------
    //                    ~ T P l a y e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    TPlayerController::~TPlayerController()
    {

    }

    //-----------------------------------------------------------------------
    //                         s e t E n a b l e d
    //-----------------------------------------------------------------------
    void TPlayerController::setEnabled(bool value)
    {
        TController::setEnabled(value);
        enableMovement(value);
        enableMouseMovement(value);            
    }

    //-----------------------------------------------------------------------
    //                       e n a b l e M o v e m e n t
    //-----------------------------------------------------------------------
    void TPlayerController::enableMovement(bool value)
    {
        m_cmdDelegate->setEnabled(value);
    }

    //-----------------------------------------------------------------------
    //                   e n a b l e M o u s e M o v e m e n t
    //-----------------------------------------------------------------------
    void TPlayerController::enableMouseMovement(bool enable)
    {
        m_mouseDelegate->setEnabled(enable);
    }

    //-----------------------------------------------------------------------
    //                         p r o c M o u s e M o v e
    //-----------------------------------------------------------------------
    int TPlayerController::procMouseMove(TEvent* event)
    {
        
        OIS::MouseEvent* pme;
        float zcoeff=1.0f;
        if(m_zoomed)
            zcoeff = 0.1f;

        pme = (OIS::MouseEvent*) event->getParameter(0)->getPointerValue();
        m_mouseX = (f32)(-pme->state.X.rel * 0.13 * zcoeff);
        m_mouseY = (f32) (m_inverted * pme->state.Y.rel * 0.13 * zcoeff);
        m_mouseMoved = true;
        
        return 1;
    }

    //-----------------------------------------------------------------------
    //                            p r o c C m d
    //-----------------------------------------------------------------------
    int TPlayerController::procCmd(TEvent* event)
    {
        int result = 1;
        bool start = false;
        float famount = 0.0f;

        if(event->getNumParameters() > 0)
        {
            if(event->getParameter(0)->isInt())
                start = event->getParameter(0)->getIntValue() ? true : false;
            else if (event->getParameter(0)->isDouble())
                famount = (float) event->getParameter(0)->getDoubleValue();
        }
        int adjust = start ? 1 : -1;
        size_t eid = event->getID();

        m_rotating = m_pitching = m_translating = false;

        if(eid == m_frwdID)
        {
            m_actions[A_FRWD] = start;
        }
        else if(eid == m_backID)
        {
            m_actions[A_BACK] = start;
        }
        else if(eid == m_leftID)
        {
            m_actions[A_LEFT] = start;
        }
        else if(eid == m_rghtID)
        {
            m_actions[A_RGHT] = start;
        }
        else if(eid == m_rotlID)
        {
            m_actions[A_ROTL] = start;
        }
        else if(eid == m_rotrID)
        {
            m_actions[A_ROTR] = start;
        }
        else if(eid == m_mvupID)
        {
            m_actions[A_MVUP] = start;
        }
        else if(eid == m_mvdnID)
        {
            m_actions[A_MVDN] = start;
        }
        else if(eid == m_rotfID)
        {
            m_actions[A_ROTF] = start;
        }
        else if(eid == m_rotbID)
        {
            m_actions[A_ROTB] = start;
        }
        else if(eid == m_avelID)
        {
            m_velocity = m_orgVelocity * famount;
        }
        else if(eid == m_invertMouseID)
        {
            if(m_inverted < 0)
                m_inverted = 1.0f;
            else m_inverted = -1.0f;
        }
        else if(eid == m_toggleMouseID)
        {
            if(m_mouseDelegate->getEnabled())
                m_mouseDelegate->setEnabled(false);
            else m_mouseDelegate->setEnabled(true);
        }
        else if(eid == m_zoomedInID)
        {
            m_zoomed = true;
        }
        else if(eid == m_zoomedOutID)
        {
            m_zoomed = false;
        }

        return 1;
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TPlayerController::update(float deltaFrameTime)
    {
        TVector3 target(0,0,1);
        TVector3 pos = m_camera->getPosition();
        TVector3 rotation = m_camera->getRotation();
        TVector3 upVector = m_camera->getUpVector();

        m_camera->setTarget(target);
        rotation.X *= -1.0f;
        rotation.Y *= -1.0f;

        if(m_mouseMoved)
        {
            rotation.Y += m_mouseX;

            rotation.X += m_mouseY;
            rotation.X = clamp(rotation.X,
                -m_maxVertAngle, +m_maxVertAngle);
            m_mouseX = 0;
            m_mouseY = 0;
            m_mouseMoved = false;
        }

        if(m_actions[A_ROTR])
        {
            rotation.Y -= (deltaFrameTime * m_angularVelocity);
        }

        if(m_actions[A_ROTL])
        {
            rotation.Y += (deltaFrameTime * m_angularVelocity);
        }

        if(m_actions[A_ROTF])
        {
            rotation.X -= (deltaFrameTime * m_angularVelocity);
            rotation.X = clamp(rotation.X,
                -m_maxVertAngle, +m_maxVertAngle);
        }

        if(m_actions[A_ROTB])
        {
            rotation.X += (deltaFrameTime * m_angularVelocity);
            rotation.X = clamp(rotation.X,
                -m_maxVertAngle, +m_maxVertAngle);
        }

        rotation.X *= -1.0f;
        rotation.Y *= -1.0f;

        m_camera->setRotation(rotation);

		matrix4 mat;
		mat.setRotationDegrees(core::vector3df( rotation.X, rotation.Y, 0));
		mat.transformVect(target);

        vector3df movedir = target.normalize();

        if(m_actions[A_FRWD])
        {
	        pos += movedir * deltaFrameTime * m_velocity;
        }
        if(m_actions[A_BACK])
        {
	        pos -= movedir * deltaFrameTime * m_velocity;
        }

        TVector3 strafeVector = target;
        strafeVector = strafeVector.crossProduct(upVector).normalize();
        if(m_actions[A_LEFT])
        {
            pos += strafeVector * deltaFrameTime * m_velocity;
        }

        if(m_actions[A_RGHT])
        {
            pos -= strafeVector * deltaFrameTime * m_velocity;
        }

        if(m_actions[A_MVUP])
        {
            pos += TVector3::UNIT_Y * deltaFrameTime * m_velocity;
        }

        if(m_actions[A_MVDN])
        {
            pos -= TVector3::UNIT_Y * deltaFrameTime * m_velocity;
        }

        m_camera->setPosition(pos);
	    m_targetVector = target;
	    target += pos;
        m_camera->setTarget(target);
	    m_camera->updateAbsolutePosition();
    }
}

