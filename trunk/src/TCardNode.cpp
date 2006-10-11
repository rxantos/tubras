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
            TVector3 pos, TVector3 size, TRenderPosition rp,
            bool fullScreen) : TSceneNode(name,parent)
    {
        m_fullScreen = fullScreen;
        m_renderPos = rp;
        m_tus = NULL;
        m_mat = NULL;
        m_pos = pos;
        m_size = size;

        m_rect = new Ogre::Rectangle2D(true);
        m_rect->setCastShadows(false);
        if(m_renderPos == rpBack)
        {
            m_rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
        }
        else
        {
            m_rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
        }
        m_pass = m_rect->getTechnique()->getPass(0);
        m_pass->setDepthCheckEnabled(false);
        m_pass->setDepthWriteEnabled(false);

        if(m_fullScreen)
        {
            m_rect->setCorners(-1.0, 1.0, 1.0, -1.0);
            m_aab.setInfinite();
        }
        else
        {
            m_rect->setCorners(pos.x,pos.y,pos.x+size.x,pos.y+size.y);
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

    }

    //-----------------------------------------------------------------------
    //                         ~ T C a r d N o d e
    //-----------------------------------------------------------------------
    TCardNode::~TCardNode()
    {

    }

    //-----------------------------------------------------------------------
    //                            s e t I m a g e
    //-----------------------------------------------------------------------
    int TCardNode::setImage(string groupName, string imageName)
    {
        int result = 0;
        m_mat = loadTexture(getName() + "Mat",groupName,imageName);
        m_rect->setMaterial(getName() + "Mat");
        m_tus = m_mat->getMat()->getTechnique(0)->getPass(0)->getTextureUnitState(0);

        return result;
    }

    //-----------------------------------------------------------------------
    //                             s e t P o s 
    //-----------------------------------------------------------------------
    void TCardNode::setPos(const TVector3& pos)
    {
    }

    //-----------------------------------------------------------------------
    //                             s e t P o s 
    //-----------------------------------------------------------------------
    void TCardNode::setPos(TReal x, TReal y, TReal z)
    {
    }

    //-----------------------------------------------------------------------
    //                            s e t S i z e
    //-----------------------------------------------------------------------
    void TCardNode::setSize(const TVector3& size)
    {

    }

    //-----------------------------------------------------------------------
    //                            s e t S i z e
    //-----------------------------------------------------------------------
    void TCardNode::setSize(TReal x, TReal y, TReal z)
    {

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
        
    }
}