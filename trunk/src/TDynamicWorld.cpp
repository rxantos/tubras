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
    //                       T D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld::TDynamicWorld()
    {
        m_maxProxies = 32766;
        m_maxOverlap = 65535;

        m_dispatcher = new	btCollisionDispatcher();

        btVector3 worldAabbMin(-10000,-10000,-10000);
        btVector3 worldAabbMax(10000,10000,10000);

        m_broadPhase = new btAxisSweep3(worldAabbMin,worldAabbMax,m_maxProxies);
        m_solver = new btSequentialImpulseConstraintSolver;

        m_world = new btDiscreteDynamicsWorld(m_dispatcher,m_broadPhase,m_solver);
        m_world->setGravity(btVector3(0,-10,0));

        //m_world->setDebugDrawer(&debugDrawer);
    }

    //-----------------------------------------------------------------------
    //                      ~ T D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld::~TDynamicWorld()
    {
    }

    //-----------------------------------------------------------------------
    //                        a d d R i g i d B o d y
    //-----------------------------------------------------------------------
    void TDynamicWorld::addRigidBody(TRigidBody* body)
    {
    }

    //-----------------------------------------------------------------------
    //                              s t e p
    //-----------------------------------------------------------------------
    void TDynamicWorld::step(float delta)
    {
        m_world->updateAabbs();
        m_world->stepSimulation(delta);

    }

}