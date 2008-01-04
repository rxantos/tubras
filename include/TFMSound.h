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

#ifndef _TFMSOUND_H_
#define _TFMSOUND_H_

#ifdef USE_FMOD_SOUND

#include "fmod.hpp"
#include "fmod_errors.h"

namespace Tubras
{
    class TFMSoundManager;


    class TFMSound : public TSound {
    public:
        virtual ~TFMSound();

        // For best compatability, set the loop_count, start_time,
        // volume, and balance, prior to calling play().  You may
        // set them while they're playing, but it's implementation
        // specific whether you get the results.
        void play();
        void stop();
        void pause();
        void resume();

        bool isPlaying();

        // loop: false = play once; true = play forever.
        // inits to false.
        void setLoop(bool loop=true);
        bool getLoop() const;

        // loop_count: 0 = forever; 1 = play once; n = play n times.
        // inits to 1.
        void setLoopCount(unsigned long loop_count=1);
        unsigned long getLoopCount() const;

        // 0 = begining; length() = end.
        // inits to 0.0.
        void setTime(float start_time=0.0);
        float getTime() const;

        // 0 = minimum; 1.0 = maximum.
        // inits to 1.0.
        void setVolume(float volume=1.0);
        float getVolume() const;

        // -1.0 is hard left
        // 0.0 is centered
        // 1.0 is hard right
        // inits to 0.0.
        void setBalance(float balance_right=0.0);
        float getBalance() const;

        // play_rate is any positive float value.
        // inits to 1.0.
        void setPlayRate(float play_rate=1.0f);
        float getPlayRate() const;

        // inits to manager's state.
        void setActive(bool active=true);
        bool getActive() const;

        void setFinishedEvent(const TString& event);
        const TString& getFinishedEvent() const;

        const TString& getName() const;

        // return: playing time in seconds.
        float length() const;

        // set 3d state
        bool setPositional(bool value);
        bool getPositional();

        // Controls the position of this sound's emitter.
        // pos is a pointer to an xyz triplet of the emitter's position.
        // vel is a pointer to an xyz triplet of the emitter's velocity.
        void set3DAttributes(float px, float py, float pz,
            float vx, float vy, float vz);
        void get3DAttributes(float *px, float *py, float *pz,
            float *vx, float *vy, float *vz);

        void set3DMinDistance(float dist);
        float get3DMinDistance() const;

        void set3DMaxDistance(float dist);
        float get3DMaxDistance() const;

        TSound::SoundStatus status() const;

        void finished();

    protected:

    private:
        TFMSoundManager*    m_manager;
        FMOD::Sound*        m_sound;
        FMOD::Channel*      m_channel;
        TString             m_fileName;
        TString             m_finishedEvent;
        float               m_volume; // 0..1.0
        float               m_balance; // -1..1
        float               m_minDist;
        float               m_maxDist;
        float               m_speed;
        unsigned long       m_loopCount;
        mutable float       m_length; // in seconds.
        bool                m_active;
        bool                m_paused;
        bool                m_positional;
        bool                m_bExclusive; //stops all other sounds before playing when true

        TFMSound(TFMSoundManager* manager, FMOD::Sound *audio_data,
            TString file_name, float length=0.0f);


        friend class TFMSoundManager;
    };

}
#endif
#endif

