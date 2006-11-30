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

#ifndef _TCAMERANODE_H_
#define _TCAMERANODE_H_

namespace Tubras
{
    enum TCameraMode
    {
        CM_FPS=0,
        CM_3RDPERSON=1,
        CM_3RDPERSON_CHASE=2
    };

    class TCameraNode : public TSceneNode
    {
    protected:
        string				m_name;
        bool                m_movementEnabled;
        Ogre::Camera*       m_camera;

    public:
        TCameraNode(string name, TSceneNode* parent,Ogre::Camera* camera=NULL);
        virtual ~TCameraNode();
        string getName() {return m_name;};
        Ogre::Camera* getCamera() {return m_camera;};

        void setPolygonMode(Ogre::PolygonMode sd);
        Ogre::PolygonMode getPolygonMode(void) const;

        virtual void setNearClipDistance(float nearDist);
        virtual float getNearClipDistance(void) const;
        virtual void setAspectRatio(float ratio);
        virtual float getAspectRatio(void) const;
        void setAutoAspectRatio(bool autoratio);
        bool getAutoAspectRatio(void) const;
        virtual void setFOVy(const TRadian& fovy);
        virtual const TRadian& getFOVy(void) const;

    };
}

#endif
