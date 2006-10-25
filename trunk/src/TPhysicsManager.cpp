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
    //                    T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::TPhysicsManager() : TObject()
    {
        m_mode = pmNone;
        m_world = NULL;
    }

    //-----------------------------------------------------------------------
    //                   ~ T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::~TPhysicsManager()
    {

        //
        // bug in the bullet library that causes hang, leak for now.
        //

        if(m_world)
            delete m_world;
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TPhysicsManager* TSingleton<TPhysicsManager>::ms_Singleton = 0;

    TPhysicsManager* TPhysicsManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TPhysicsManager& TPhysicsManager::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TPhysicsManager::initialize()
    {
        m_world = new TDynamicWorld();

        return 0;
    }



}