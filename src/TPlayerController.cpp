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

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                     T P l a y e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    TPlayerController::TPlayerController(TString controllerName,TCameraNode* camera,
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

        m_velocity = getAppConfig()->getFloat("velocity","options",3.0);
        m_angularVelocity = getAppConfig()->getFloat("angularvelocity","options",3.0);

        m_orgAngularVelocity = m_angularVelocity;

        m_mouseDelegate = EVENT_DELEGATE(TPlayerController::procMouseMove);
        acceptEvent("input.mouse.move",m_mouseDelegate);

        m_cmdDelegate = EVENT_DELEGATE(TPlayerController::procCmd);

        m_frwdID = acceptEvent("frwd",m_cmdDelegate);
        m_backID = acceptEvent("back",m_cmdDelegate);
        m_leftID = acceptEvent("left",m_cmdDelegate);
        m_rghtID = acceptEvent("rght",m_cmdDelegate);
        m_rotlID = acceptEvent("rotl",m_cmdDelegate);
        m_rotrID = acceptEvent("rotr",m_cmdDelegate);

        m_strafeUpID = acceptEvent("strafe-up",m_cmdDelegate);
        m_strafeDownID = acceptEvent("strafe-down",m_cmdDelegate);
        m_pitchForwardID = acceptEvent("pitch-forward",m_cmdDelegate);
        m_pitchBackwardID = acceptEvent("pitch-backward",m_cmdDelegate);
        m_invertMouseID = acceptEvent("invert-mouse",m_cmdDelegate);
        m_increaseVelocityID = acceptEvent("increase-velocity",m_cmdDelegate);
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
        /*
        OIS::MouseEvent* pme;
        float zcoeff=1.0f;
        if(m_zoomed)
            zcoeff = 0.1;

        pme = (OIS::MouseEvent*) event->getParameter(0)->getPointerValue();
        m_mouseX = -pme->state.X.rel * 0.13 * zcoeff;
        m_mouseY = m_inverted * pme->state.Y.rel * 0.13 * zcoeff;
        m_mouseMoved = true;
        */

        return 0;
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
        else if(eid == m_strafeUpID)
        {
            m_translate.Y += ((float) adjust *  m_velocity);
        }
        else if(eid == m_strafeDownID)
        {
            m_translate.Y -= ((float) adjust *  m_velocity);
        }
        else if(eid == m_pitchForwardID)
        {
            m_pitch -= ((float) adjust * m_angularVelocity);
        }
        else if(eid == m_pitchBackwardID)
        {
            m_pitch += ((float) adjust * m_angularVelocity);
        }
        else if(eid == m_invertMouseID)
        {
            if(m_inverted < 0)
                m_inverted = 1.0f;
            else m_inverted = -1.0f;
        }
        else if(eid == m_increaseVelocityID)
        {
            m_shift = famount;
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

		core::matrix4 mat;
		mat.setRotationDegrees(core::vector3df( rotation.X, rotation.Y, 0));
		mat.transformVect(target);

        core::vector3df movedir = target.normalize();

		//if (NoVerticalMovement)
		//	movedir.Y = 0.f;

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


        m_camera->setPosition(pos);
	    m_targetVector = target;
	    target += pos;
	    m_camera->updateAbsolutePosition();
        m_camera->setTarget(m_camera->getPosition() + m_targetVector);

    }
}