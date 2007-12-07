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
    //                  T O s c i l l a t e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TOscillateController::TOscillateController(TString name, ISceneNode* node, float velocity,
        float amplitude, TVector3 axis) : TController(name, node, 
        new TWaveControllerFunction(WFT_SINE,0,velocity,1,amplitude,0.5))
    {
        m_axis = axis;
        m_velocity = velocity;
        m_amplitude = amplitude;
        m_currentPos = m_node->getPosition();
    }

    //-----------------------------------------------------------------------
    //                 ~ T O s c i l l a t e C o n t r o l l e r
    //-----------------------------------------------------------------------
    TOscillateController::~TOscillateController()
    {
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TOscillateController::update(float value)
    {
        TVector3 adjust = m_axis * value;

        m_node->setPosition(m_currentPos + adjust);
    }


}