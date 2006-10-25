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
    //                       T C o l l i d e r S h a p e
    //-----------------------------------------------------------------------
    TColliderShape::TColliderShape()
    {
        m_shape = NULL;
        m_body = NULL;
    }

    //-----------------------------------------------------------------------
    //                      ~ T C o l l i d e r S h a p e
    //-----------------------------------------------------------------------
    TColliderShape::~TColliderShape()
    {
    }

    //-----------------------------------------------------------------------
    //                      c r e a t e R i g i d B o d y
    //-----------------------------------------------------------------------
    btRigidBody* TColliderShape::createRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape)
    {
        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (isDynamic)
            shape->calculateLocalInertia(mass,localInertia);

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody* body = new btRigidBody(mass,myMotionState,shape,localInertia);

        TPhysicsManager::getSingleton().getWorld()->addRigidBody(body);

        return body;
    }

}