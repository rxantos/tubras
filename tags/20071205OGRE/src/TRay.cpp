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
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay() : Ogre::Ray()
    {
        m_magnitude = 1.f;
        m_endPoint = mOrigin + (mDirection * m_magnitude);
    }

    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay(const TVector3& origin, const TVector3& direction, const TReal magnitude)
        : Ogre::Ray(origin,direction)
    {
        m_magnitude = magnitude;
        m_endPoint = origin + (direction * magnitude);
    }

    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay(const Ogre::Ray& oRay,const TReal magnitude)
        : Ogre::Ray(oRay.getOrigin(),oRay.getDirection())
    {
        m_magnitude = magnitude;
        m_endPoint = mOrigin + (mDirection * m_magnitude);
    }

    //-----------------------------------------------------------------------
    //                            ~ T R a y 
    //-----------------------------------------------------------------------
    TRay::~TRay()
    {
    }
}