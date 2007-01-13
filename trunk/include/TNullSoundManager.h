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

#ifndef _TNULLSOUNDMANAGER_H_
#define _TNULLSOUNDMANAGER_H_

namespace Tubras
{
    class TNullSoundManager : public TSoundManager {
        // All of these methods are stubbed out to some degree.
        // If you're looking for a starting place for a new AudioManager,
        // please consider looking at the milesAudioManager.

    public:
        TNullSoundManager();
        virtual ~TNullSoundManager();

        virtual bool isValid();

        virtual TSound* getSound(const TString resourceGroup, const TString&, bool positional = false);
        virtual void uncacheSound(const TString&);
        virtual void clearCache();
        virtual void setCacheLimit(unsigned int);
        virtual unsigned int getCacheLimit() const;

        virtual void setVolume(float);
        virtual float getVolume() const;

        virtual void setplayRate(float);
        virtual float getplayRate() const;

        virtual void setActive(bool);
        virtual bool getActive() const;

        virtual void setConcurrentSoundLimit(unsigned int limit);
        virtual unsigned int getConcurrentSoundLimit() const;

        virtual void reduceSoundsPlayingTo(unsigned int count);

        virtual void stopAllSounds();

    };
}

#endif