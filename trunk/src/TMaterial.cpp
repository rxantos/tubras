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
    //                           T M a t e r i a l
    //-----------------------------------------------------------------------
    TMaterial::TMaterial(string name,string resourceGroup)
    {
        m_material = Ogre::MaterialManager::getSingleton().create(name,resourceGroup);
        getApplication()->getRenderEngine()->addMaterial(name,this);

    }

    //-----------------------------------------------------------------------
    //                           T M a t e r i a l
    //-----------------------------------------------------------------------
    TMaterial::TMaterial(Ogre::MaterialPtr mat)
    {
        m_material = mat;
    }

    //-----------------------------------------------------------------------
    //                          ! T M a t e r i a l
    //-----------------------------------------------------------------------
    TMaterial::~TMaterial()
    {
        getApplication()->getRenderEngine()->removeMaterial(m_material->getName());
    }

    //-----------------------------------------------------------------------
    //                           l o a d I m a g e
    //-----------------------------------------------------------------------
    void TMaterial::loadImage(string imageName, int unitIndex)
    {
        m_material->getTechnique(0)->getPass(0)->createTextureUnitState(imageName);
        m_material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        m_material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        m_material->getTechnique(0)->getPass(0)->setLightingEnabled(false);        
    }
}