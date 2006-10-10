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

#ifndef _T1PCAMERA_H_
#define _T1PCAMERA_H_

namespace Tubras
{
    class T1PCamera : public TCamera, public TObject
    {
    private:
        TEventDelegate*         m_keyDelegate;
        TEventDelegate*         m_mouseDelegate;
        TFuncIntDelegate*       m_zoomDelegate;
        TLerpFunction*          m_zoomLerp;
        TTask*                  m_updateTask;
        TVector3                m_translate;
        float					m_pitch;
        float					m_rotate;
        float                   m_velocity;
        float                   m_shift;
        float					m_angularVelocity;
        float                   m_mouseX;
        float                   m_mouseY;
        float                   m_inverted;
        bool					m_translating;
        bool					m_pitching;
        bool					m_rotating;
        bool                    m_mouseMoved;
        Ogre::Radian            m_normalFOV;
        Ogre::Radian            m_zoomedFOV;
        TSound*                 m_zoomInSound;
        TSound*                 m_zoomOutSound;

    private:
        int procKey(Tubras::TSEvent event);
        int procMouseMove(Tubras::TSEvent event);
        int updateTask(Tubras::TTask* task);
        void procZoom(double T, void* userData);

    public:
        T1PCamera(string name);
        virtual ~T1PCamera();
        virtual void enableMovement(bool value);
        virtual void enableMouseMovement(bool enable);

        void setZoomSounds(TSound* in, TSound* out);
    };
}

#endif
