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
    //                     T P a r t i c l e M a n a g e r
    //-----------------------------------------------------------------------
    TParticleManager::TParticleManager() : TObject()
    {
    }

    //-----------------------------------------------------------------------
    //                    ~ T P a r t i c l e M a n a g e r
    //-----------------------------------------------------------------------
    TParticleManager::~TParticleManager()
    {
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r 
    //-----------------------------------------------------------------------
    template<> TParticleManager* TSingleton<TParticleManager>::ms_Singleton = 0;

    TParticleManager* TParticleManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n 
    //-----------------------------------------------------------------------
    TParticleManager& TParticleManager::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }

    //-----------------------------------------------------------------------
    //                          I n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TParticleManager::initialize()
    {
        int result=0;
        return result;
    }

    //-----------------------------------------------------------------------
    //                   c r e a t e P a r t i c l e G r o u p
    //-----------------------------------------------------------------------
    TParticleGroup* TParticleManager::createParticleGroup(TString name,const size_t maxParticles)
    {
        TParticleGroup* pg;
        pg = new TParticleGroup(maxParticles);
        m_groups[name] = pg;

        return pg;
    }

    //-----------------------------------------------------------------------
    //                           f i n d G r o u p
    //-----------------------------------------------------------------------
    TParticleGroup* TParticleManager::findGroup(TString name)
    {
        TParticleGroup* pg=0;

        return pg;
    }

    //-----------------------------------------------------------------------
    //                  r e m o v e P a r t i c l e G r o u p
    //-----------------------------------------------------------------------
    TParticleGroup* TParticleManager::removeParticleGroup(TString name)
    {
        TParticleGroup* pg=0;

        return pg;
    }

    //-----------------------------------------------------------------------
    //                 d e s t r o y P a r t i c l e G r o u p
    //-----------------------------------------------------------------------
    void TParticleManager::destroyParticleGroup(TString name)
    {

    }

    //-----------------------------------------------------------------------
    //                               s t e p
    //-----------------------------------------------------------------------
    void TParticleManager::step()
    {

        MAP_PGROUPS_ITR  itr;
        itr = m_groups.begin();
        while(itr != m_groups.end())
        {
            if(itr->second->m_enabled)
                (itr->second)->step();            
            ++itr;
        }

    }


}