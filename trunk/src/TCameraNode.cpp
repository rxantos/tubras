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
    //                            T C a m e r a
    //-----------------------------------------------------------------------
    TCameraNode::TCameraNode(string name, TSceneNode* parent, Ogre::Camera* camera) : TSceneNode(name,parent)
    {
        m_name = name;
        m_ownCamera = false;
        m_camera = camera;

        if(!m_camera)
        {
            m_camera = new Ogre::Camera(name,getRenderEngine()->getSceneManager());
            m_ownCamera = true;
        }

        setAutoAspectRatio(true);
        getApplication()->getRenderEngine()->addCamera(this);
        getNode()->attachObject(m_camera);

    }

    //-----------------------------------------------------------------------
    //                           ~ T C a m e r a
    //-----------------------------------------------------------------------
    TCameraNode::~TCameraNode()
    {
        if(m_ownCamera && m_camera)
            delete m_camera;
    }

    //-----------------------------------------------------------------------
    //                             s e t P o s
    //-----------------------------------------------------------------------
    void TCameraNode::setPos(float x, float y, float z) 
    {
        //setPosition(x,y,z);
        TSceneNode::setPos(x,y,z);
    }

    //-----------------------------------------------------------------------
    //                             s e t P o s
    //-----------------------------------------------------------------------
    void TCameraNode::setPos(TVector3 vec) 
    {
        //setPosition(vec);
        TSceneNode::setPos(vec);
    }

    //-----------------------------------------------------------------------
    //                       s e t P o l y g o n M o d e
    //-----------------------------------------------------------------------
    void TCameraNode::setPolygonMode(Ogre::PolygonMode sd)
    {
        m_camera->setPolygonMode(sd);
    }

    //-----------------------------------------------------------------------
    //                       g e t P o l y g o n M o d e
    //-----------------------------------------------------------------------
    Ogre::PolygonMode TCameraNode::getPolygonMode(void) const
    {
        return m_camera->getPolygonMode();
    }

    //-----------------------------------------------------------------------
    //                g e t D e r i v e d O r i e n t a t i o n
    //-----------------------------------------------------------------------
    const Ogre::Quaternion& TCameraNode::getDerivedOrientation(void) const
    {
        return m_camera->getDerivedOrientation();
    }

    //-----------------------------------------------------------------------
    //                   g e t D e r i v e d P o s i t i o n 
    //-----------------------------------------------------------------------
    const TVector3& TCameraNode::getDerivedPosition(void) const
    {
        return m_camera->getDerivedPosition();
    }

    //-----------------------------------------------------------------------
    //                         s e t P o s i t i o n
    //-----------------------------------------------------------------------
    void TCameraNode::setPosition(float x, float y, float z)
    {
        m_camera->setPosition(x,y,z);
    }

    //-----------------------------------------------------------------------
    //                         s e t P o s i t i o n
    //-----------------------------------------------------------------------
    void TCameraNode::setPosition(const TVector3& vec)
    {
        m_node->setPosition(vec);
        m_camera->setPosition(vec);
    }

    //-----------------------------------------------------------------------
    //                         g e t P o s i t i o n
    //-----------------------------------------------------------------------
    const TVector3& TCameraNode::getPosition(void) const
    {
        return m_camera->getPosition();
    }

    //-----------------------------------------------------------------------
    //                              m o v e
    //-----------------------------------------------------------------------
    void TCameraNode::move(const TVector3& vec)
    {
        m_camera->move(vec);
    }

    //-----------------------------------------------------------------------
    //                         m o v e R e l a t i v e
    //-----------------------------------------------------------------------
    void TCameraNode::moveRelative(const TVector3& vec)
    {
        m_camera->moveRelative(vec);
    }

    //-----------------------------------------------------------------------
    //                             l o o k A t
    //-----------------------------------------------------------------------
    void TCameraNode::lookAt( const TVector3& targetPoint )
    {
        m_camera->lookAt(targetPoint);
    }

    //-----------------------------------------------------------------------
    //                             l o o k A t
    //-----------------------------------------------------------------------
    void TCameraNode::lookAt(float x, float y, float z)
    {
        m_camera->lookAt(x,y,z);
    }

    //-----------------------------------------------------------------------
    //                   s e t N e ar C l i p D i s t a n c e
    //-----------------------------------------------------------------------
    void TCameraNode::setNearClipDistance(float nearDist)
    {
        m_camera->setNearClipDistance(nearDist);
    }

    //-----------------------------------------------------------------------
    //                   g e t N e ar C l i p D i s t a n c e
    //-----------------------------------------------------------------------
    float TCameraNode::getNearClipDistance(void) const
    {
        return m_camera->getNearClipDistance();
    }

    //-----------------------------------------------------------------------
    //                      s e t A s p e c t R a t i o
    //-----------------------------------------------------------------------
    void TCameraNode::setAspectRatio(float ratio)
    {
        m_camera->setAspectRatio(ratio);
    }

    //-----------------------------------------------------------------------
    //                      g e t A s p e c t R a t i o
    //-----------------------------------------------------------------------
    float TCameraNode::getAspectRatio(void) const
    {
        return m_camera->getAspectRatio();
    }

    //-----------------------------------------------------------------------
    //                   s e t A u t o A s p e c t R a t i o
    //-----------------------------------------------------------------------
    void TCameraNode::setAutoAspectRatio(bool autoratio)
    {
        m_camera->setAutoAspectRatio(autoratio);
    }

    //-----------------------------------------------------------------------
    //                   g e t A u t o A s p e c t R a t i o
    //-----------------------------------------------------------------------
    bool TCameraNode::getAutoAspectRatio(void) const
    {
        return m_camera->getAutoAspectRatio();
    }

    //-----------------------------------------------------------------------
    //                          s e t F O V y
    //-----------------------------------------------------------------------
    void TCameraNode::setFOVy(const TRadian& fovy)
    {
        m_camera->setFOVy(fovy);
    }

    //-----------------------------------------------------------------------
    //                          g e t F O V y
    //-----------------------------------------------------------------------
    const TRadian& TCameraNode::getFOVy(void) const
    {
        return m_camera->getFOVy();
    }

    //-----------------------------------------------------------------------
    //                    s e t F i x e d Y a w A x i s
    //-----------------------------------------------------------------------
    void TCameraNode::setFixedYawAxis( bool useFixed, const TVector3& fixedAxis )
    {
        m_camera->setFixedYawAxis(useFixed,fixedAxis);
    }

    //-----------------------------------------------------------------------
    //                             r o l l
    //-----------------------------------------------------------------------
    void TCameraNode::roll(const TRadian& angle)
    {
        m_camera->roll(angle);
    }

    //-----------------------------------------------------------------------
    //                              y a w
    //-----------------------------------------------------------------------
    void TCameraNode::yaw(const TRadian& angle)
    {
        m_camera->yaw(angle);
    }

    //-----------------------------------------------------------------------
    //                            p i t c h 
    //-----------------------------------------------------------------------
    void TCameraNode::pitch(const TRadian& angle)
    {
        m_camera->pitch(angle);
    }

    //-----------------------------------------------------------------------
    //                           r o t a t e 
    //-----------------------------------------------------------------------
    void TCameraNode::rotate(const TVector3& axis, const TRadian& angle)
    {
        m_camera->rotate(axis,angle);
    }

    //-----------------------------------------------------------------------
    //                           r o t a t e 
    //-----------------------------------------------------------------------
    void TCameraNode::rotate(const TQuaternion& q)
    {
        m_camera->rotate(q);
    }



}
