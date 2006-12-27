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
    //                          T O v e r l a y
    //-----------------------------------------------------------------------
    TOverlay::TOverlay(string name, TDim dims, TColor color,float alpha, string materialName, bool dynamic) : TObject()
    {
        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
        m_name = name;
        m_materialName = materialName;
        m_dims = dims;
        m_dynamic = dynamic;
        m_color = color;
        m_alpha = alpha;
        m_textureUnit = NULL;

        m_panel = static_cast<Ogre::OverlayContainer*>(
            overlayManager.createOverlayElement("Panel",m_name+"Panel"));
        m_panel->setMetricsMode(Ogre::GMM_RELATIVE);
        m_panel->setPosition(m_dims.x, m_dims.y);
        m_panel->setDimensions(m_dims.w,m_dims.h);

        if(m_materialName.empty())
        {
            // Create background material
            m_materialName = m_name + "-OverlayMat";
            m_material = Ogre::MaterialManager::getSingleton().create(m_materialName, "General");
            m_material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            m_material->getTechnique(0)->getPass(0)->createTextureUnitState();
            m_material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(Ogre::LBX_SOURCE1,Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, m_color);
            m_material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, m_alpha); 
        }
		else 
		{
			m_material = Ogre::MaterialManager::getSingleton().getByName(m_materialName);
            m_material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            m_material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_TEXTURE, Ogre::LBS_CURRENT, m_alpha); 
		}
        m_panel->setMaterialName(m_materialName);
        m_textureUnit = m_material->getTechnique(0)->getPass(0)->getTextureUnitState(0);

        m_overlay = overlayManager.create(m_name + "-Overlay");
        m_overlay->add2D(m_panel);
    }

    //-----------------------------------------------------------------------
    //                         ~ T O v e r l a y 
    //-----------------------------------------------------------------------
    TOverlay::~TOverlay()
    {

    }

    //-----------------------------------------------------------------------
    //                         s e t V i s i b l e
    //-----------------------------------------------------------------------
    void TOverlay::setVisible(bool value)
    {
        if(value)
            m_overlay->show();
        else
            m_overlay->hide();
    }

    //-----------------------------------------------------------------------
    //                         g e t V i s i b l e
    //-----------------------------------------------------------------------
    bool TOverlay::getVisible()
    {
        return m_overlay->isVisible();
    }

    //-----------------------------------------------------------------------
    //                          s e t C o l o r
    //-----------------------------------------------------------------------
    void TOverlay::setColor(Ogre::ColourValue color)
    {
        m_color = color;
        m_textureUnit->setColourOperationEx(Ogre::LBX_SOURCE1,Ogre::LBS_MANUAL, 
            Ogre::LBS_CURRENT, color);

    }

    //-----------------------------------------------------------------------
    //                          s e t A l p h a 
    //-----------------------------------------------------------------------
    void TOverlay::setAlpha(float alpha)
    {
        m_alpha = alpha;
        m_textureUnit->setAlphaOperation(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, 
            Ogre::LBS_CURRENT, m_alpha); 
    }

    //-----------------------------------------------------------------------
    //                            s e t P o s 
    //-----------------------------------------------------------------------
    void TOverlay::setPos(float left, float top)
    {

        m_dims.x = left;
        m_dims.y = top;
        m_panel->setPosition(left, top);

    }

    //-----------------------------------------------------------------------
    //                           s e t S i z e
    //-----------------------------------------------------------------------
    void TOverlay::setSize(float width, float height)
    {
        m_dims.w = width;
        m_dims.h = height;
        m_panel->setDimensions(width,height);
    }



}