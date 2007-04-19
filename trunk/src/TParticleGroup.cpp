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
    using namespace PAPI;

    Ogre::String TParticleGroup::m_movableType = "TParticleGroup";

    //-----------------------------------------------------------------------
    //                       T P a r t i c l e G r o u p 
    //-----------------------------------------------------------------------
    TParticleGroup::TParticleGroup(size_t maxParticles)
    {
        m_handle = m_pc.GenParticleGroups(1, maxParticles);
        m_pc.CurrentGroup(m_handle);
    }

    //-----------------------------------------------------------------------
    //                       T P a r t i c l e G r o u p 
    //-----------------------------------------------------------------------
    TParticleGroup::~TParticleGroup()
    {
    }

    //-----------------------------------------------------------------------
    //                       g e t M o v a b l e T y p e
    //-----------------------------------------------------------------------
    const Ogre::String& TParticleGroup::getMovableType(void) const
    {
        return m_movableType;
    }

    //-----------------------------------------------------------------------
    //                       g e t B o u n d i n g B o x
    //-----------------------------------------------------------------------
    const Ogre::AxisAlignedBox& TParticleGroup::getBoundingBox(void) const
    {
        return m_bb;
    }

    //-----------------------------------------------------------------------
    //                    g e t B o u n d i n g R a d i u s
    //-----------------------------------------------------------------------
    Ogre::Real TParticleGroup::getBoundingRadius(void) const
    {
        return 0.f;
    }

    //-----------------------------------------------------------------------
    //                              s t e p
    //-----------------------------------------------------------------------
    void TParticleGroup::step()
    {
        //
        // hardcoded for render testing - incorporate actions as affectors later.
        //

        // Set up the state.
        m_pc.Velocity(PDCylinder(pVec(0.0f, -0.01f, 0.25f), pVec(0.0f, -0.01f, 0.27f), 0.021f, 0.019f));
        m_pc.Color(PDLine(pVec(0.8f, 0.9f, 1.0f), pVec(1.0f, 1.0f, 1.0f)));

        // Generate particles along a very small line in the nozzle.
        m_pc.Source(100, PDLine(pVec(0, 0, 0), pVec(0, 0, 0.4f)));

        // Gravity.
        m_pc.Gravity(pVec(0, 0, -0.01f));

        // Bounce particles off a disc of radius 5.
        m_pc.Bounce(-0.05f, 0.35f, 0, PDDisc(pVec(0, 0, 0), pVec(0, 0, 1), 5));

        // Kill particles below Z=-3.
        m_pc.Sink(false, PDPlane(pVec(0,0,-3), pVec(0,0,1)));

        // Move particles to their new positions.
        m_pc.Move(true, false);
    }


    //-----------------------------------------------------------------------
    //                   _ u p d a t e R e n d e r Q u e u e
    //-----------------------------------------------------------------------
    void TParticleGroup::_updateRenderQueue(Ogre::RenderQueue* queue)
    {
    }

}