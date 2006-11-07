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

#ifndef _TPLAYERCONTROLLER_H_
#define _TPLAYERCONTROLLER_H_

namespace Tubras
{
    /**
    TPlayerController Class.
    @remarks
    Controller class - a variation of Ogre::Controller.

    Creating a controller automatically registers it with the Controller Manager.  The manager 
    automatically deletes registered controllers when the manager itself is destroyed.

    If you would like to remove a controller that is no longer needed:
    1. Invoke TControllerManager::remove()
    2. Delete the controller manually

    */

    class TPlayerController : public TController
    {
    private:
        TEventDelegate*         m_cmdDelegate;
        TEventDelegate*         m_mouseDelegate;
        TVector3                m_translate;
        float					m_pitch;
        float					m_rotate;
        float                   m_velocity;
        float                   m_shift;
        float					m_angularVelocity;
        float					m_orgAngularVelocity;
        float                   m_mouseX;
        float                   m_mouseY;
        float                   m_inverted;
        bool					m_translating;
        bool					m_pitching;
        bool					m_rotating;
        bool                    m_mouseMoved;

        size_t                  m_forwardID,m_backwardID;
        size_t                  m_strafeLeftID, m_strafeRightID;
        size_t                  m_strafeUpID, m_strafeDownID;
        size_t                  m_pitchForwardID, m_pitchBackwardID;
        size_t                  m_yawLeftID, m_yawRightID;
        size_t                  m_zoomID;
        size_t                  m_invertMouseID,m_toggleMouseID;
        size_t                  m_increaseVelocityID;

    private:
        int procCmd(Tubras::TSEvent event);
        int procMouseMove(Tubras::TSEvent event);
        int updateTask(Tubras::TTask* task);
        void procZoom(double T, void* userData);

    public:

        TPlayerController(string controllerName,TSceneNode* node);
        virtual ~TPlayerController();

        virtual void setEnabled(bool value);

        virtual void enableMovement(bool value);
        virtual void enableMouseMovement(bool enable);

        void setVelocity(float value) {m_velocity = value;};
        float getVelocity() {return m_velocity;};

        void setAngularVelocity(float value) {m_angularVelocity = value;};
        float getAngularVelocity() {return m_angularVelocity;};

        void update(float deltaFrameTime);
    };

}

#endif
