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
    T1PCamera::T1PCamera(string name) : TCamera(name)
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

        m_mouseDelegate = EVENT_DELEGATE(T1PCamera::procMouseMove);
        acceptEvent("input.mouse.move",m_mouseDelegate);

        m_keyDelegate = EVENT_DELEGATE(T1PCamera::procKey);

        m_zoomDelegate = FUNCINT_DELEGATE(T1PCamera::procZoom);
        string lerpName = m_name + "ZoomLerp";
        m_zoomLerp = new TLerpFunction(lerpName,m_normalFOV.valueRadians(),
            m_zoomedFOV.valueRadians(),0.53,m_zoomDelegate);

        acceptEvent("key.down.w",m_keyDelegate);
        acceptEvent("key.down.a",m_keyDelegate);
        acceptEvent("key.down.s",m_keyDelegate);
        acceptEvent("key.down.d",m_keyDelegate);
        acceptEvent("key.down.c",m_keyDelegate);		    
        acceptEvent("key.down.e",m_keyDelegate);		    
        acceptEvent("key.down.m",m_keyDelegate);	    // toggle mouse movement
        acceptEvent("key.down.i",m_keyDelegate);
        acceptEvent("key.down.z",m_keyDelegate);
        acceptEvent("key.down.up",m_keyDelegate);		// up arrow
        acceptEvent("key.down.down",m_keyDelegate);		// down arrow
        acceptEvent("key.down.left",m_keyDelegate);		// left arrow
        acceptEvent("key.down.right",m_keyDelegate);	// right arrow
        acceptEvent("key.down.lshift",m_keyDelegate);		

        acceptEvent("key.up.w",m_keyDelegate);
        acceptEvent("key.up.a",m_keyDelegate);
        acceptEvent("key.up.s",m_keyDelegate);
        acceptEvent("key.up.d",m_keyDelegate);
        acceptEvent("key.up.c",m_keyDelegate);		    
        acceptEvent("key.up.e",m_keyDelegate);		    
        acceptEvent("key.up.z",m_keyDelegate);
        acceptEvent("key.up.up",m_keyDelegate);			// up arrow
        acceptEvent("key.up.down",m_keyDelegate);		// down arrow
        acceptEvent("key.up.left",m_keyDelegate);		// left arrow
        acceptEvent("key.up.right",m_keyDelegate);		// right arrow
        acceptEvent("key.up.lshift",m_keyDelegate);		

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
        TCamera::enableMovement(value);
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
        case OIS::KC_I:
            if(m_inverted < 0)
                m_inverted = 1.0f;
            else m_inverted = -1.0f;
            break;
        case OIS::KC_W:
            m_translate.z -= (float) adjust;
            break;
        case OIS::KC_A:
            m_translate.x -= (float) adjust;
            break;
        case OIS::KC_S:
            m_translate.z += (float) adjust;
            break;
        case OIS::KC_D:
            m_translate.x += (float) adjust;
            break;
        case OIS::KC_E:
            m_translate.y += (float) adjust;
            break;
        case OIS::KC_C:
            m_translate.y -= (float) adjust;
            break;
        case OIS::KC_Z:
            if(down)
            {
                m_zoomLerp->start(m_normalFOV.valueRadians(),m_zoomedFOV.valueRadians());
                if(m_zoomInSound)
                    m_zoomInSound->play();
            }
            else 
            {
                m_zoomLerp->start(getFOVy().valueRadians(),m_normalFOV.valueRadians());
                if(m_zoomOutSound)
                    m_zoomOutSound->play();
            }
            break;
        case OIS::KC_UP:
            m_pitch -= (float) adjust;
            break;
        case OIS::KC_DOWN:
            m_pitch += (float) adjust;
            break;
        case OIS::KC_LEFT:
            m_rotate += (float) adjust;
            break;
        case OIS::KC_RIGHT:
            m_rotate -= (float) adjust;
            break;
        case OIS::KC_LSHIFT:
            if(down)
                m_shift = 2.0;
            else m_shift = 1.0;
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
                float famount = m_shift * m_angularVelocity * m_mouseX * delta;
                Ogre::Degree d(famount);
                yaw(Ogre::Radian(d));
            }

            if(m_mouseY)
            {
                float famount = m_shift * m_angularVelocity * m_mouseY * delta;
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
