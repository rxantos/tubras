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
	//                     T L i n M o v C o n t r o l l e r
	//-----------------------------------------------------------------------
	TLinMovController::TLinMovController(TSceneNode* node,
		TColliderShape* shape) : TController(node->getName()+"::LinMovController",node)
	{
	}

	//-----------------------------------------------------------------------
	//                    ~ T L i n M o v C o n t r o l l e r
	//-----------------------------------------------------------------------
	TLinMovController::~TLinMovController()
	{
	}

	//-----------------------------------------------------------------------
	//                         s e t V e l o c i t y
	//-----------------------------------------------------------------------
	void TLinMovController::setVelocity(TVector3 value)
	{
		m_velocity = value;
	}


	//-----------------------------------------------------------------------
	//                         s e t O r i e n t a t i o n
	//-----------------------------------------------------------------------
	void TLinMovController::setOrientation(TQuaternion value)
	{
		m_orientation = value;
	}

	//-----------------------------------------------------------------------
	//                           e n a b l e C D
	//-----------------------------------------------------------------------
	void TLinMovController::enableCD(bool value)
	{
		m_useCD = value;
	}


	//-----------------------------------------------------------------------
	//                        e n a b l e H u g g i n g
	//-----------------------------------------------------------------------
	void TLinMovController::enableHugging(bool value)
	{
		m_hugGround = value;
	}


	//-----------------------------------------------------------------------
	//                          s e t G r a v i t y
	//-----------------------------------------------------------------------
	void TLinMovController::setGravity(float value)
	{
		m_gravity = value;
	}

	//-----------------------------------------------------------------------
	//                     s e t C o l l i d e r S h a p e
	//-----------------------------------------------------------------------
	void TLinMovController::setColliderShape(TColliderShape* value)
	{
		m_collider = value;
	}


	//-----------------------------------------------------------------------
	//                             u p d a t e
	//-----------------------------------------------------------------------
	void TLinMovController::update(float deltaFrameTime)
	{
	}


}