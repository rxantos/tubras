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

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::TNullSoundManager
    //       Access: 
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    TNullSoundManager::TNullSoundManager() 
    {
            
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::~TNullSoundManager
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    TNullSoundManager::~TNullSoundManager() 
    {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::is_valid
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    bool TNullSoundManager::isValid() 
    {
            return false;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::get_sound
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    TSound* TNullSoundManager::getSound(const string resourceGroup, const string&, bool positional) 
    {
            return getnullSound();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::uncache_sound
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::uncacheSound(const string&) 
    {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::uncache_all_sounds
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::clearCache() 
    {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::set_cache_limit
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::setCacheLimit(unsigned int) 
    {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::get_cache_limit
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    unsigned int TNullSoundManager::getCacheLimit() const 
    {
            // intentionally blank.
            return 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::set_volume
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::setVolume(float) {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::get_volume
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    float TNullSoundManager::getVolume() const 
    {
            return 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::set_play_rate
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::setplayRate(float) 
    {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::get_play_rate
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    float TNullSoundManager::getplayRate() const 
    {
            return 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::set_active
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::setActive(bool) 
    {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::get_active
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    bool TNullSoundManager::getActive() const 
    {
            return 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::set_concurrent_sound_limit
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::setConcurrentSoundLimit(unsigned int) 
    {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::get_concurrent_sound_limit
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    unsigned int TNullSoundManager::getConcurrentSoundLimit() const {
            return 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::reduce_sounds_playing_to
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::reduceSoundsPlayingTo(unsigned int) {
            // intentionally blank.
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TNullSoundManager::stop_all_sounds
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TNullSoundManager::
        stopAllSounds() {
            // intentionally blank.
    }

}