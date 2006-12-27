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
    //                            T C a m e r a
    //-----------------------------------------------------------------------
    TCameraNode::TCameraNode(string name, TSceneNode* parent, Ogre::Camera* camera) : TSceneNode(name,parent)
    {
        m_name = name;
        m_camera = camera;

        if(!m_camera)
        {
            m_camera = getRenderEngine()->getSceneManager()->createCamera(name);
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

}
