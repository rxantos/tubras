//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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
    TPlayerController::TPlayerController(string controllerName,TSceneNode* node) : TController(controllerName,node)
    {
        m_rotating = false;
        m_pitching = false;
        m_translating = false;
        m_mouseMoved = false;
        m_translate = TVector3::ZERO;
        m_pitch = 0.0f;
        m_rotate = 0.0f;
        m_shift = 1.0f;
        m_inverted = -1.0f;

        string temp = getApplication()->getConfigFile()->getSetting("Velocity","Options");
        if(temp.empty())
            m_velocity = 3.0;
        else
            m_velocity = atof(temp.c_str());

        temp = getApplication()->getConfigFile()->getSetting("AngularVelocity","Options");
        if(temp.empty())
            m_angularVelocity = 3.0;
        else
            m_angularVelocity = atof(temp.c_str());

        m_orgAngularVelocity = m_angularVelocity;

        m_mouseDelegate = EVENT_DELEGATE(TPlayerController::procMouseMove);
        acceptEvent("input.mouse.move",m_mouseDelegate);

        m_cmdDelegate = EVENT_DELEGATE(TPlayerController::procCmd);

        m_forwardID = acceptEvent("forward",m_cmdDelegate);
        m_backwardID = acceptEvent("backward",m_cmdDelegate);
        m_strafeLeftID = acceptEvent("strafe-left",m_cmdDelegate);
        m_strafeRightID = acceptEvent("strafe-right",m_cmdDelegate);
        m_strafeUpID = acceptEvent("strafe-up",m_cmdDelegate);
        m_strafeDownID = acceptEvent("strafe-down",m_cmdDelegate);
        m_pitchForwardID = acceptEvent("pitch-forward",m_cmdDelegate);
        m_pitchBackwardID = acceptEvent("pitch-backward",m_cmdDelegate);
        m_yawLeftID = acceptEvent("yaw-left",m_cmdDelegate);
        m_yawRightID = acceptEvent("yaw-right",m_cmdDelegate);
        m_invertMouseID = acceptEvent("invert-mouse",m_cmdDelegate);
        m_increaseVelocityID = acceptEvent("increase-velocity",m_cmdDelegate);
        m_toggleMouseID = acceptEvent("toggle-mouse",m_cmdDelegate);

        setEventDelegateEnabled(m_cmdDelegate,false);
        setEventDelegateEnabled(m_mouseDelegate,false);
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
        m_node->enableMovement(value);
        setEventDelegateEnabled(m_cmdDelegate,value);
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
    int TPlayerController::procMouseMove(Tubras::TSEvent event)
    {
        OIS::MouseEvent* pme;

        pme = (OIS::MouseEvent*) event->getParameter(0)->getPointerValue();
        m_mouseX = -pme->state.relX * 0.13;
        m_mouseY = m_inverted * pme->state.relY * 0.13;
        m_mouseMoved = true;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                            p r o c C m d
    //-----------------------------------------------------------------------
    int TPlayerController::procCmd(Tubras::TSEvent event)
    {
        int result = 1;
        int start = 0;
        float famount = 0.0f;

        if(event->getNumParameters() > 0)
        {
            if(event->getParameter(0)->isInt())
                start = event->getParameter(0)->getIntValue();
            else if (event->getParameter(0)->isDouble())
                famount = event->getParameter(0)->getDoubleValue();
        }
        int adjust = start ? 1 : -1;
        size_t eid = event->getID();

        m_rotating = m_pitching = m_translating = false;

        if(eid == m_forwardID)
        {
            m_translate.z -= ((float) adjust *  m_velocity);
        }
        else if(eid == m_backwardID)
        {
            m_translate.z += ((float) adjust *  m_velocity);
        }
        else if(eid == m_strafeLeftID)
        {
            m_translate.x -= ((float) adjust *  m_velocity);
        }
        else if(eid == m_strafeRightID)
        {
            m_translate.x += ((float) adjust *  m_velocity);
        }
        else if(eid == m_strafeUpID)
        {
            m_translate.y += ((float) adjust *  m_velocity);
        }
        else if(eid == m_strafeDownID)
        {
            m_translate.y -= ((float) adjust *  m_velocity);
        }
        else if(eid == m_pitchForwardID)
        {
            m_pitch -= ((float) adjust * m_angularVelocity);
        }
        else if(eid == m_pitchBackwardID)
        {
            m_pitch += ((float) adjust * m_angularVelocity);
        }
        else if(eid == m_yawLeftID)
        {
            m_rotate += ((float) adjust * m_angularVelocity);
        }
        else if(eid == m_yawRightID)
        {
            m_rotate -= ((float) adjust * m_angularVelocity);
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

        return 1;
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TPlayerController::update(float deltaFrameTime)
    {
        if(m_pitch != 0.0f)
        {
            float famount = m_shift * m_pitch * deltaFrameTime;
            Ogre::Degree d(famount);

            m_node->pitch(Ogre::Radian(d));
        }

        if(m_rotate != 0.0f)
        {
            float famount = m_shift * m_rotate * deltaFrameTime;
            Ogre::Degree d(famount);
            m_node->yaw(Ogre::Radian(d),Ogre::Node::TS_PARENT);
        }

        if(m_mouseMoved)
        {
            if(m_mouseX)
            {
                float famount = m_angularVelocity * m_mouseX * deltaFrameTime;
                Ogre::Degree d(famount);
                m_node->yaw(Ogre::Radian(d),Ogre::Node::TS_PARENT);
            }

            if(m_mouseY)
            {
                float famount = m_angularVelocity * m_mouseY * deltaFrameTime;
                Ogre::Degree d(famount);
                m_node->pitch(Ogre::Radian(d));
            }
            m_mouseX = 0;
            m_mouseY = 0;
            m_mouseMoved = false;
        }

        if(m_translate != TVector3::ZERO)
        {
            string name = m_node->getName();
            float famount = m_shift * deltaFrameTime;
            m_node->moveRelative(m_translate * famount);
        }

    }
}