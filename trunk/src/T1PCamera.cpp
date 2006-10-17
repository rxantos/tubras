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
    //                           T 1 P C a m e r a
    //-----------------------------------------------------------------------
    T1PCamera::T1PCamera(string name, TSceneNode* parent) : TCameraNode(name,parent)
    {
        m_rotating = false;
        m_pitching = false;
        m_translating = false;
        m_mouseMoved = false;
        m_zoomInSound = NULL;
        m_zoomOutSound = NULL;

        m_translate = Ogre::Vector3::ZERO;
        m_pitch = 0.0f;
        m_rotate = 0.0f;
        m_shift = 1.0f;
        m_inverted = -1.0f;
        m_normalFOV = getFOVy();
        m_zoomedFOV = m_normalFOV / 3;

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

        m_mouseDelegate = EVENT_DELEGATE(T1PCamera::procMouseMove);
        acceptEvent("input.mouse.move",m_mouseDelegate);

        m_keyDelegate = EVENT_DELEGATE(T1PCamera::procKey);

        m_cmdDelegate = EVENT_DELEGATE(T1PCamera::procCmd);

        m_zoomDelegate = FUNCINT_DELEGATE(T1PCamera::procZoom);
        string lerpName = m_name + "ZoomLerp";
        m_zoomLerp = new TLerpFunction(lerpName,m_normalFOV.valueRadians(),
            m_zoomedFOV.valueRadians(),0.53,m_zoomDelegate);

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
        m_zoomID = acceptEvent("zoom",m_cmdDelegate);
        m_invertMouseID = acceptEvent("invert-mouse",m_cmdDelegate);
        m_increaseVelocityID = acceptEvent("increase-velocity",m_cmdDelegate);

        acceptEvent("key.down.m",m_keyDelegate);	    // toggle mouse movement

        setEventDelegateEnabled(m_keyDelegate,false);
        setEventDelegateEnabled(m_mouseDelegate,false);

        m_updateTask = new TTask("Camera::name::updateTask",TASK_DELEGATE(T1PCamera::updateTask),
            0,0,NULL,"Camera::name::updateDone");

        setAutoAspectRatio(true);
        setFixedYawAxis(true);
    }

    //-----------------------------------------------------------------------
    //                           ~ T 1 P C a m e r a
    //-----------------------------------------------------------------------
    T1PCamera::~T1PCamera()
    {
        delete m_zoomLerp;
    }

    //-----------------------------------------------------------------------
    //                       e n a b l e M o v e m e n t
    //-----------------------------------------------------------------------
    void T1PCamera::enableMovement(bool value)
    {
        TCameraNode::enableMovement(value);
        setEventDelegateEnabled(m_keyDelegate,value);
    }

    //-----------------------------------------------------------------------
    //                        s e t Z o o m S o u n d s
    //-----------------------------------------------------------------------
    void T1PCamera::setZoomSounds(TSound* in, TSound* out)
    {
        m_zoomInSound = in;
        m_zoomOutSound = out;
    }


    //-----------------------------------------------------------------------
    //                           p r o c Z o o m
    //-----------------------------------------------------------------------
    void T1PCamera::procZoom(double T, void* userData)
    {
        printf("procZoom T=%f\n",T);
        setFOVy(Ogre::Radian(T));
    }

    //-----------------------------------------------------------------------
    //                   e n a b l e M o u s e M o v e m e n t
    //-----------------------------------------------------------------------
    void T1PCamera::enableMouseMovement(bool enable)
    {
        m_mouseDelegate->setEnabled(enable);
    }

    //-----------------------------------------------------------------------
    //                         p r o c M o u s e M o v e
    //-----------------------------------------------------------------------
    int T1PCamera::procMouseMove(Tubras::TSEvent event)
    {
        OIS::MouseEvent* pme;

        pme = (OIS::MouseEvent*) event->getParameter(0)->getPointerValue();
        m_mouseX = -pme->state.relX * 0.13;
        m_mouseY = m_inverted * pme->state.relY * 0.13;
        m_mouseMoved = true;
        if(!m_updateTask->isRunning())
            m_updateTask->start();

        return 0;
    }


    //-----------------------------------------------------------------------
    //                            p r o c C m d
    //-----------------------------------------------------------------------
    int T1PCamera::procCmd(Tubras::TSEvent event)
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
            m_translate.z -= (float) adjust;
        }
        else if(eid == m_backwardID)
        {
            m_translate.z += (float) adjust;
        }
        else if(eid == m_strafeLeftID)
        {
            m_translate.x -= (float) adjust;
        }
        else if(eid == m_strafeRightID)
        {
            m_translate.x += (float) adjust;
        }
        else if(eid == m_strafeUpID)
        {
            m_translate.y += (float) adjust;
        }
        else if(eid == m_strafeDownID)
        {
            m_translate.y -= (float) adjust;
        }
        else if(eid == m_pitchForwardID)
        {
            m_pitch -= (float) adjust;
        }
        else if(eid == m_pitchBackwardID)
        {
            m_pitch += (float) adjust;
        }
        else if(eid == m_yawLeftID)
        {
            m_rotate += (float) adjust;
        }
        else if(eid == m_yawRightID)
        {
            m_rotate -= (float) adjust;
        }
        else if(eid == m_zoomID)
        {
            if(start)
            {
                m_zoomLerp->start(m_normalFOV.valueRadians(),m_zoomedFOV.valueRadians());
                if(m_zoomInSound)
                    m_zoomInSound->play();
                m_angularVelocity /= 5.0;
            }
            else 
            {
                m_zoomLerp->start(getFOVy().valueRadians(),m_normalFOV.valueRadians());
                if(m_zoomOutSound)
                    m_zoomOutSound->play();
                m_angularVelocity = m_orgAngularVelocity;
            }
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


        if(m_translate != Ogre::Vector3::ZERO)
        {
            m_translating = true;
        }
        if(m_pitch != 0.0f)
        {
            m_pitching = true;
        }
        if(m_rotate != 0.0f)
        {
            m_rotating = true;
        }

        if(!m_translating && !m_pitching && !m_rotating &&
            m_updateTask->isRunning())
        {
            m_updateTask->stop();
        }

        if((m_translating || m_pitching || m_rotating) &&
            !m_updateTask->isRunning())
        {
            m_updateTask->start();
        }

        return 1;

    }

    //-----------------------------------------------------------------------
    //                            p r o c K e y
    //-----------------------------------------------------------------------
    int T1PCamera::procKey(Tubras::TSEvent event)
    {
        int result = 1;
        int key = event->getParameter(0)->getIntValue();
        int down = event->getParameter(1)->getIntValue();
        int adjust = down ? 1 : -1;

        m_rotating = m_pitching = m_translating = false;
        switch(key)
        {
        case OIS::KC_M:
            if(m_mouseDelegate->getEnabled())
                m_mouseDelegate->setEnabled(false);
            else m_mouseDelegate->setEnabled(true);
            break;
        default:
            result = 0;
        }

        if(m_translate != Ogre::Vector3::ZERO)
        {
            m_translating = true;
        }
        if(m_pitch != 0.0f)
        {
            m_pitching = true;
        }
        if(m_rotate != 0.0f)
        {
            m_rotating = true;
        }

        if(!m_translating && !m_pitching && !m_rotating &&
            m_updateTask->isRunning())
        {
            m_updateTask->stop();
        }

        if((m_translating || m_pitching || m_rotating) &&
            !m_updateTask->isRunning())
        {
            m_updateTask->start();
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                         u p d a t e T a s k
    //-----------------------------------------------------------------------
    int T1PCamera::updateTask(Tubras::TTask* task)
    {
        float delta = (float)task->m_deltaTime / 1000.0f;

        if(m_translating)
        {
            float famount = m_shift * m_velocity * delta;
            moveRelative(m_translate * famount);
        }

        if(m_pitching)
        {
            float famount = m_shift * m_angularVelocity * m_pitch * delta;
            Ogre::Degree d(famount);

            pitch(Ogre::Radian(d));
        }

        if(m_rotating)
        {
            float famount = m_shift * m_angularVelocity * m_rotate * delta;
            Ogre::Degree d(famount);
            yaw(Ogre::Radian(d));
        }

        if(m_mouseMoved)
        {
            if(m_mouseX)
            {
                float famount = m_angularVelocity * m_mouseX * delta;
                Ogre::Degree d(famount);
                yaw(Ogre::Radian(d));
            }

            if(m_mouseY)
            {
                float famount = m_angularVelocity * m_mouseY * delta;
                Ogre::Degree d(famount);
                pitch(Ogre::Radian(d));
            }
            m_mouseX = 0;
            m_mouseY = 0;
            m_mouseMoved = false;
        }

        return TTask::cont;
    }

}
