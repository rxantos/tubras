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
    //                          T C a r d N o d e
    //-----------------------------------------------------------------------
    TCardNode::TCardNode (string name, TSceneNode *parent,
        TVector3 ulCorner, TVector3 lrCorner, TRenderPosition rp,
        bool fullScreen) : TSceneNode(name,parent)
    {
        m_fullScreen = fullScreen;
        m_renderPos = rp;
        m_tus = NULL;
        m_mat = NULL;
        m_ulCorner = ulCorner;
        m_lrCorner = lrCorner;

        m_rect = new Ogre::Rectangle2D(true);
        m_rect->setCastShadows(false);
        m_pass = m_rect->getTechnique()->getPass(0);
        if(m_renderPos == rpBack)
        {
            m_rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
        }
        else
        {
            m_rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
        }
        m_pass->setDepthCheckEnabled(false);
        m_pass->setDepthWriteEnabled(false);

        if(m_fullScreen)
        {
            m_rect->setCorners(-1.0, 1.0, 1.0, -1.0);
            m_aab.setInfinite();
        }
        else
        {
            setCorners(m_ulCorner,m_lrCorner);
            m_aab.setExtents(m_ulCorner,m_lrCorner);
        }


        m_rect->setBoundingBox(m_aab);
        if(m_parent)
        {
            m_parent->getNode()->attachObject(m_rect);
        }
        else
        {
            string msg = "(Error) Null parent passed to TCardNode: " + name;
            logMessage(msg.c_str());
        }

        m_pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

    }

    //-----------------------------------------------------------------------
    //                         ~ T C a r d N o d e
    //-----------------------------------------------------------------------
    TCardNode::~TCardNode()
    {
        if(m_rect)
            delete m_rect;
        if(m_mat)
            delete m_mat;

    }

    //-----------------------------------------------------------------------
    //                            s e t I m a g e
    //-----------------------------------------------------------------------
    int TCardNode::setImage(string groupName, string imageName)
    {
        int result = 0;
        m_mat = loadTexture(getName() + "Mat",groupName,imageName);
        m_rect->setMaterial(getName() + "Mat");

        if(m_renderPos == rpBack)
        {
            m_mat->setDepthCheckEnabled(false);
            m_mat->setDepthWriteEnabled(false);
        }

        m_tus = m_mat->getMat()->getTechnique(0)->getPass(0)->getTextureUnitState(0);

        return result;
    }

    //-----------------------------------------------------------------------
    //                          s e t C o r n e r s
    //-----------------------------------------------------------------------
    void TCardNode::setCorners(TVector3 ulCorner, TVector3 lrCorner)
    {
        m_rect->setCorners(ulCorner.x,ulCorner.y,lrCorner.x,lrCorner.y);
    }

    //-----------------------------------------------------------------------
    //                          s e t C o r n e r s
    //-----------------------------------------------------------------------
    void TCardNode::setCorners(float left, float top, float right, float bottom)
    {
        m_rect->setCorners(left,top,right,bottom);
    }

    //-----------------------------------------------------------------------
    //                    s e t S c r o l l A n i m a t i o n
    //-----------------------------------------------------------------------
    void TCardNode::setScrollAnimation(float uSpeed, float vSpeed)
    {
        if(m_tus)
            m_tus->setScrollAnimation(uSpeed,vSpeed);
    }

    //-----------------------------------------------------------------------
    //                    s e t R o t a t e A n i m a t i o n
    //-----------------------------------------------------------------------
    void TCardNode::setRotateAnimation(float speed)
    {
        if(m_tus)
            m_tus->setRotateAnimation(speed);
    }

    //-----------------------------------------------------------------------
    //                           s e t A l p h a
    //-----------------------------------------------------------------------
    void TCardNode::setAlpha(float value)
    {
        if(m_tus)
            m_tus->setAlphaOperation(Ogre::LBX_BLEND_MANUAL, Ogre::LBS_TEXTURE, Ogre::LBS_MANUAL, 1, value , 1);

    }
}