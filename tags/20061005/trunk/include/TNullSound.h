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

#ifndef _TNULLSOUND_H_
#define _TNULLSOUND_H_

namespace Tubras
{

    // This class intentionally does next to nothing.
    // It's used as a placeholder when you don't want a sound
    // system.
    class TNullSound : public TSound {
        // All of these methods are stubbed out to some degree.
        // If you're looking for a starting place for a new AudioManager,
        // please consider looking at the milesAudioManager.

    public:
        TNullSound();

        virtual ~TNullSound();

        void play();
        void stop();

        void setLoop(bool);
        bool getLoop() const;

        void setLoopCount(unsigned long);
        unsigned long getLoopCount() const;

        void setTime(float);
        float getTime() const;

        void setVolume(float);
        float getVolume() const;

        void setBalance(float);
        float getBalance() const;

        void setPlayRate(float);
        float getPlayRate() const;

        void setActive(bool);
        bool getActive() const;

        void setFinishedEvent(const string& event);
        const string& getFinishedEvent() const;

        const string& getName() const;

        float length() const;

        void set3DAttributes(float px, float py, float pz,
            float vx, float vy, float vz);
        void get3DAttributes(float *px, float *py, float *pz,
            float *vx, float *vy, float *vz);

        void set3DMinDistance(float dist);
        float get3DMinDistance() const;

        void set3DMaxDistance(float dist);
        float get3DMaxDistance() const;

        TSound::SoundStatus status() const;

        friend class NullAudioManager;
    };

}

#endif