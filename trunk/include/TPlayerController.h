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
    public:
        enum Actions {
            A_FRWD=0,           // move forward
            A_BACK=1,           // move backward
            A_LEFT=2,           // move left
            A_RGHT=3,           // move right
            A_ROTR=4,           // rotate right
            A_ROTL=5,           // rotate left
            A_MVUP=6,           // move up
            A_MVDN=7,           // move down
            A_ROTF=8,           // rotate forward
            A_ROTB=9,           // rotate backward
            A_AVEL=10,          // adjust velocity
            A_LAST
        };
    private:
        TCameraNode*            m_camera;
        TEventDelegate*         m_cmdDelegate;
        TEventDelegate*         m_mouseDelegate;
        TVector3                m_targetVector;
        TVector3                m_translate;
        f32					    m_pitch;
        f32					    m_rotate;
        f32                     m_velocity;
        f32                     m_orgVelocity;
        f32                     m_shift;
        f32					    m_angularVelocity;
        f32                     m_mouseX;
        f32                     m_mouseY;
        f32                     m_inverted;
        f32                     m_maxVertAngle;
        bool					m_translating;
        bool					m_pitching;
        bool					m_rotating;
        bool                    m_mouseMoved;
        bool                    m_zoomed;
        bool                    m_actions[A_LAST];

        size_t                  m_frwdID,m_backID;
        size_t                  m_leftID, m_rghtID;
        size_t                  m_mvupID, m_mvdnID;
        size_t                  m_rotfID, m_rotbID;
        size_t                  m_rotrID, m_rotlID;
        size_t                  m_zoomID;
        size_t                  m_avelID;
        size_t                  m_invertMouseID,m_toggleMouseID;
        size_t                  m_zoomedInID, m_zoomedOutID;

    private:
        int procCmd(TEvent* event);
        int procMouseMove(TEvent* event);
        void procZoom(double T, void* userData);

    public:

        TPlayerController(TString controllerName,TCameraNode* camera, ISceneNode* playerNode=0);
        virtual ~TPlayerController();

        virtual void setEnabled(bool value);

        virtual void enableMovement(bool value);
        virtual void enableMouseMovement(bool enable);

        void setVelocity(f32 value) {m_velocity = value;};
        f32 getVelocity() {return m_velocity;};

        void setAngularVelocity(f32 value) {m_angularVelocity = value;};
        f32 getAngularVelocity() {return m_angularVelocity;};

        void update(f32 deltaFrameTime);
    };

}

#endif
