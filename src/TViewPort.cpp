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
    //                          T V i e w P o r t
    //-----------------------------------------------------------------------
    TViewPort::TViewPort(TString name, TCameraNode* camera,
        Ogre::RenderTarget* target,
        Ogre::Real left, Ogre::Real top,
        Ogre::Real width, Ogre::Real height,
        int ZOrder)
    {
        m_name = name;


        if(target)
            m_viewPort = target->addViewport(camera->getCamera(),ZOrder,left,top,width,height);

        getApplication()->getRenderEngine()->addViewPort(this);

    }

    //-----------------------------------------------------------------------
    //                          ~ T V i e w P o r t
    //-----------------------------------------------------------------------
    TViewPort::~TViewPort()
    {

    }

    //-----------------------------------------------------------------------
    //                  s e t B a c k g r o u n d C o l o u r
    //-----------------------------------------------------------------------
    void TViewPort::setBackgroundColour(const TColour& colour)
    {
        m_viewPort->setBackgroundColour(colour);
    }

    //-----------------------------------------------------------------------
    //                      g e t A c t u a l W i d t h 
    //-----------------------------------------------------------------------
    int TViewPort::getActualWidth(void) const
    {
        return m_viewPort->getActualWidth();
    }

    //-----------------------------------------------------------------------
    //                     g e t A c t u a l H e i g h t
    //-----------------------------------------------------------------------
    int TViewPort::getActualHeight(void) const
    {
        return m_viewPort->getActualHeight();
    }

}
