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
#ifndef _TLINMOVCONTROLLER_H_
#define _TLINMOVCONTROLLER_H_

namespace Tubras
{
    class TLinMovController : public TController
    {
    protected:
        TDynamicWorld*			m_world;
        TSceneNode*				m_node;
        TDynamicNode*			m_dnode;
        TColliderShape*			m_collider;
        TVector3				m_velocity;
        float					m_angularVelocity;
        TVector3				m_pos;
        TQuaternion				m_orientation;
        bool					m_useCD;
        bool					m_hugGround;
        bool					m_onGround;
        bool					m_isJumping;
        float					m_gravity;
        float					m_lastDist;

    public:
        TLinMovController(TSceneNode* node, TDynamicNode* dnode );
        virtual ~TLinMovController();

        void setVelocity(TVector3 value);
        TVector3 getVelocity() {return m_velocity;};

        void setAngularVelocity(float value);
        float getAngularVelocity() {return m_angularVelocity;};

        void setOrientation(TQuaternion value);
        TQuaternion getOrientation() {return m_orientation;};

        void enableCD(bool value);
        bool isCDEnabled() {return m_useCD;};

        void enableHugging(bool value);			// ;)
        bool isHuggingEnabled() {return m_hugGround;};

        void setGravity(float value);
        float getGravity() {return m_gravity;};

        void setColliderShape(TColliderShape* value);
        TColliderShape* getColliderShape() {return m_collider;};

        TVector3 getPos() {return m_pos;};

        virtual void update(float deltaFrameTime);
    };
}
#endif