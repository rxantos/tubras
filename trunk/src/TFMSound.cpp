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

#ifdef USE_FMOD_SOUND

namespace Tubras
{

    ////////////////////////////////////////////////////////////////////
    //     Function: pandaFmodFinishedCallback_Stream
    //       Access: file scope
    //  Description: What happens when a sound ends (not reaches the end
    //               of a loop, but really ends).
    ////////////////////////////////////////////////////////////////////
    FMOD_RESULT F_CALLBACK 
        FMODFinishedCallback( FMOD_CHANNEL *m_channel, FMOD_CHANNEL_CALLBACKTYPE type, 
        int command, unsigned int commanddata1, unsigned int commanddata2)

    {
        FMOD_RESULT result;
        TFMSound* sound;
        FMOD::Channel *channel = (FMOD::Channel *)m_channel;

        result = channel->getUserData((void **)&sound);

        assert(sound); //sanity test
        sound->finished();
        return FMOD_OK;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::TFMSound
    //       Access: 
    //  Description: constructor
    ////////////////////////////////////////////////////////////////////

    TFMSound::TFMSound(TFMSoundManager* manager, FMOD::Sound *audio_data,
        TString file_name, float length)
        : m_manager(manager), m_sound(audio_data), m_fileName(file_name),
        m_volume(1.0f), m_balance(0), m_loopCount(1), m_length(length), m_positional(false),
        m_active(true), m_paused(false), m_bExclusive(false),m_channel(NULL) 
    {
        m_minDist = 1.0f; m_maxDist = 1000000000.0f;

    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::~TFMSound
    //       Access: public
    //  Description: destructor
    ////////////////////////////////////////////////////////////////////
    TFMSound::~TFMSound() 
    {
        this->stop();
        m_manager->releaseSound(this);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound:: play
    //       Access: public
    //  Description: Play a sound
    ////////////////////////////////////////////////////////////////////
    void TFMSound::play() 
    {
        TStrStream msg;
        FMOD_RESULT result;

        if (!m_active) 
        {
            return;
        }
        // If the sound is already playing, stop it.
        if (this->status() == TSound::PLAYING) 
        {
            this->stop();
        }

        if (m_bExclusive) 
        {
            // stop another sound that parent mgr is playing
            m_manager->stopAllSounds();
        }

        // Play the stream, but start it paused so we can set the volume and
        // panning first.
        m_manager->m_system->playSound(FMOD_CHANNEL_FREE,m_sound,true,&m_channel);

        if (!m_channel) 
        {
            getApplication()->logMessage("play() failed");
            return;
        }

        m_channel->getFrequency(&m_speed);

        m_channel->setUserData(this);
        m_channel->setCallback(FMOD_CHANNEL_CALLBACKTYPE_END,FMODFinishedCallback,0);

        // Set volume.
        m_channel->setVolume(m_volume);

        // Set panning.
        m_channel->setPan(m_balance);

        FMOD_MODE mode;
        result = m_channel->getMode(&mode);

        // Set 3d attributes, if needed
        if ((result == FMOD_OK) && (mode & FMOD_3D)) 
        {
            TVector3 pos;
            if(m_node)
                pos = m_node->getDerivedPosition();

            FMOD_VECTOR fmod_pos;
            fmod_pos.x = pos.x;
            fmod_pos.y = pos.y;
            fmod_pos.z = pos.z;
            FMOD_VECTOR fmod_vel;
            fmod_vel.x = fmod_vel.y = fmod_vel.z = 0.f;
            if(m_channel->set3DAttributes(&fmod_pos, &fmod_vel) != FMOD_OK) 
            {
                msg << "Unable to set 3d attributes for "<<m_fileName<<"!";
                getApplication()->logMessage(msg.str().c_str());
            }

            if(m_channel->set3DMinMaxDistance(m_minDist, m_maxDist) != FMOD_OK) 
            {
                msg << "Unable to set 3d min/max distance for "<<m_fileName<<"!";
                getApplication()->logMessage(msg.str().c_str());
            }
        }
        // Set looping -- unimplemented

        // Unpause and set status to playing

        m_channel->setPaused(false);

    }


    void TFMSound::pause()
    {
        if (!m_active) 
        {
            return;
        }
        // If the sound is already playing, stop it.
        if ((this->status() == TSound::PLAYING) && m_channel)
        {
            m_channel->setPaused(true);
        }

    }

    void TFMSound::resume()
    {
        if((this->status() == TSound::PAUSED) && m_channel)
        {
            m_channel->setPaused(false);
        }

    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::stop
    //       Access: public
    //  Description: Stop a sound
    ////////////////////////////////////////////////////////////////////
    void TFMSound::stop() 
    {
        if(!m_channel)
            return;

        if(m_channel->stop() != FMOD_OK)
        {
            getApplication()->logMessage("Sound Stop failed!");
        }
        m_channel = NULL;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::finished
    //       Access: public
    //  Description: called by finishedCallback function when a sound
    //               terminates (but doesn't loop).
    ////////////////////////////////////////////////////////////////////
    void TFMSound::finished() 
    {
        stop();
        if(!m_finishedEvent.empty())
        {
            TSEvent event;
            event.bind(new TEvent(m_finishedEvent));
            getApplication()->queueEvent(event);
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::setLoop
    //       Access: public
    //  Description: Turns looping on and off
    ////////////////////////////////////////////////////////////////////
    void TFMSound::setLoop(bool loop) 
    {
        FMOD_MODE mode;
        m_sound->getMode(&mode);
        if (loop) 
        {
            // turn looping on
            mode ^= FMOD_LOOP_OFF;
            m_sound->setMode(mode | FMOD_LOOP_NORMAL);
        } 
        else 
        {
            // turn looping off if and only if it is on
            m_sound->setMode(mode & FMOD_LOOP_OFF);
        }
        // default to loop infinitely
        m_loopCount = loop ? 0 : 1;
        m_sound->setLoopCount(m_loopCount - 1);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getLoop
    //       Access: public
    //  Description: Returns whether looping is on or off
    ////////////////////////////////////////////////////////////////////
    bool TFMSound::getLoop() const 
    {
        // 0 means loop forever,
        // >1 means loop that many times
        // So m_loopCount != 1 means we're looping
        return (m_loopCount != 1);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::setLoop_count
    //       Access: public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TFMSound::setLoopCount(unsigned long loop_count) 
    {
        // Panda uses 0 to mean loop forever.
        // Fmod uses negative numbers to mean loop forever.
        // (0 means don't loop, 1 means play twice, etc.)
        // We must convert!

        if (loop_count < 0) 
        {
            loop_count = 0;
        }
        m_loopCount = loop_count;
        loop_count -= 1; 
        m_sound->setLoopCount(loop_count);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getLoop_count
    //       Access: public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    unsigned long TFMSound::getLoopCount() const 
    {
        return m_loopCount;
    }

    //-----------------------------------------------------------------------
    //                       s e t P o s i t i o n a l
    //-----------------------------------------------------------------------
    bool TFMSound::setPositional(bool value)
    {

        bool rc=false;

        if(m_positional == value)
            return true;

        FMOD_MODE mode;
        FMOD_RESULT result = m_sound->getMode(&mode);

        if (result != FMOD_OK)
        {
            return false;
        }

        m_positional = value;
        if(m_positional)
        {
            if(mode & FMOD_3D)
                return true;
            mode ^= FMOD_2D;
            mode |= FMOD_3D;
            result = m_sound->setMode(mode);
            rc = (result == FMOD_OK);
        }
        else
        {
            if(!(mode & FMOD_3D))
                return false;

            mode ^= FMOD_3D;
            mode |= FMOD_2D;
            result = m_sound->setMode(mode);
            rc = (result == FMOD_OK);

        }

        return rc;

    }

    //-----------------------------------------------------------------------
    //                       g e t P o s i t i o n a l
    //-----------------------------------------------------------------------
    bool TFMSound::getPositional()
    {
        return m_positional;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::setTime
    //       Access: public
    //  Description: Sets the play position within the sound
    ////////////////////////////////////////////////////////////////////
    void TFMSound::setTime(float start_time) 
    {
        if (start_time < 0.0f) 
        {
            start_time = 0.0f;
        } 
        else if (start_time > m_length) 
        {
            start_time = m_length - 0.01;
        }
        // FMOD measures time in milliseconds, so scale up by 1000.
        m_channel->setPosition((int)(start_time * 1000.0f),FMOD_TIMEUNIT_MS);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getTime
    //       Access: public
    //  Description: Gets the play position within the sound
    ////////////////////////////////////////////////////////////////////
    float TFMSound::getTime() const 
    {
        // A bug in stream WAV files causes FSOUND_Stream_GetTime() to
        // divide-by-zero somewhere if the stream isn't currently playing.
        // In this case, we should just return zero.
        bool is_playing;
        m_channel->isPlaying(&is_playing);

        if (!is_playing)
        {
            return 0.0f;
        }

        // FMOD measures time in milliseconds, so scale down by 1000.
        unsigned int position;
        m_channel->getPosition(&position,FMOD_TIMEUNIT_MS);
        float current_time = float(position) * 0.001f;
        //fmod_audio_debug("getTime() returning "<<current_time);
        return current_time;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::set_volume
    //       Access: public
    //  Description: 0.0 to 1.0 scale of volume converted to Fmod's
    //               internal 0.0 to 255.0 scale.
    ////////////////////////////////////////////////////////////////////
    void TFMSound::setVolume(float vol) 
    {
        if (vol < 0.0f) 
        {
            vol = 0.0f;
        } 
        else if (vol > 1.0f) 
        {
            vol = 1.0f;
        }
        m_volume = vol;
        m_channel->setVolume(m_volume);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getVolume
    //       Access: public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    float TFMSound::getVolume() const 
    {
        return m_volume;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::setBalance
    //       Access: public
    //  Description: -1.0 to 1.0 scale
    ////////////////////////////////////////////////////////////////////
    void TFMSound::setBalance(float bal) 
    {
        if (bal < -1.0f) {
            bal = -1.0f;
        } 
        else if (bal > 1.0f) {
            bal = 1.0f;
        }
        m_balance = bal;
        m_channel->setPan(m_balance);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getBalance
    //       Access: public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    float TFMSound::getBalance() const 
    {
        return m_balance;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::setPlayRate
    //       Access: public
    //  Description: NOT IMPLEMENTED! DO NOT USE!
    ////////////////////////////////////////////////////////////////////
    void TFMSound::setPlayRate(float rate) 
    {
        m_channel->setFrequency(m_speed * rate);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getPlayRate
    //       Access: public
    //  Description: NOT IMPLEMENTED! DO NOT USE!
    ////////////////////////////////////////////////////////////////////
    float TFMSound::getPlayRate() const 
    {
        float rate;
        m_channel->getFrequency(&rate);
        return rate;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::setActive
    //       Access: public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TFMSound::setActive(bool active) 
    {
        if (!active) {
            // Once looping works, a looping sound should be paused, not
            // stopped.  When the sound is activated again, it is unpaused.
            m_channel->setPaused(true);
        }
        else m_channel->setPaused(false);
        m_active = active;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getActive
    //       Access: public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    bool TFMSound::getActive() const 
    {
        return m_active;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::setFinishedEvent
    //       Access: public
    //  Description: Assign a TString for the finished event to be referenced 
    //               by in python by an accept method
    ////////////////////////////////////////////////////////////////////
    void TFMSound::setFinishedEvent(const TString& event) 
    {
        m_finishedEvent = event;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getFinishedEvent
    //       Access: public
    //  Description: Return the TString the finished event is referenced by
    ////////////////////////////////////////////////////////////////////
    const TString& TFMSound::getFinishedEvent() const 
    {
        return m_finishedEvent;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::getName
    //       Access: public
    //  Description: Get name of sound file
    ////////////////////////////////////////////////////////////////////
    const TString& TFMSound::getName() const 
    {
        return m_fileName;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::length
    //       Access: public
    //  Description: Get length
    ////////////////////////////////////////////////////////////////////
    float TFMSound::length() const 
    {
        return m_length;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::set_3d_attributes
    //       Access: public
    //  Description: Set position and velocity of this sound
    ////////////////////////////////////////////////////////////////////
    void TFMSound::set3DAttributes(float px, float py, float pz, float vx, float vy, float vz) 
    {
        FMOD_MODE mode;
        FMOD_RESULT result = m_channel->getMode(&mode);

        // Set 3d attributes, if needed
        if ((result == FMOD_OK) && (mode & FMOD_3D)) 
        {

            // Convert from Panda coordinates to Fmod coordinates
            FMOD_VECTOR fmod_pos;
            fmod_pos.x = px;
            fmod_pos.y = py;
            fmod_pos.z = pz;
            FMOD_VECTOR fmod_vel;
            fmod_vel.x = vx;
            fmod_vel.y = vy;
            fmod_vel.z = vz;
            if(m_channel->set3DAttributes(&fmod_pos, &fmod_vel) != FMOD_OK) 
            {
                TStrStream msg;
                msg << "Unable to set 3d attributes for "<<m_fileName<<"!";
                getApplication()->logMessage(msg.str().c_str());
            }
        }

    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::get_3d_attributes
    //       Access: public
    //  Description: Get position and velocity of this sound
    ////////////////////////////////////////////////////////////////////
    void TFMSound::get3DAttributes(float *px, float *py, float *pz, float *vx, float *vy, float *vz) 
    {
        FMOD_VECTOR pos;
        FMOD_VECTOR vel;
        FMOD_RESULT result = m_channel->get3DAttributes(&pos,&vel);
        if(result != FMOD_OK)
        {
            getApplication()->logMessage("Error retrieving 3d sound attributes.");
            return;
        }
        *px = pos.x;
        *py = pos.y;
        *pz = pos.z;
        *vx = vel.x;
        *vy = vel.y;
        *vz = vel.z;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::set_3d_min_distance
    //       Access: public
    //  Description: Set the distance that this sound begins to fall off. Also
    //               affects the rate it falls off.
    ////////////////////////////////////////////////////////////////////
    void TFMSound::set3DMinDistance(float dist) 
    {
        m_minDist = dist;

        FMOD_MODE mode;
        FMOD_RESULT result = m_sound->getMode(&mode);

        // Set 3d attributes, if needed
        if ((result == FMOD_OK) && (mode & FMOD_3D)) 
        {
            m_sound->set3DMinMaxDistance(m_minDist,m_maxDist);

        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::get_3d_min_distance
    //       Access: public
    //  Description: Get the distance that this sound begins to fall off
    ////////////////////////////////////////////////////////////////////
    float TFMSound::get3DMinDistance() const 
    {
        return m_minDist;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::set_3d_max_distance
    //       Access: public
    //  Description: Set the distance that this sound stops falling off
    ////////////////////////////////////////////////////////////////////
    void TFMSound::set3DMaxDistance(float dist) 
    {
        m_maxDist = dist;

        FMOD_MODE mode;
        FMOD_RESULT result = m_channel->getMode(&mode);

        // Set 3d attributes, if needed
        if ((result == FMOD_OK) && (mode & FMOD_3D)) 
        {
            m_channel->set3DMinMaxDistance(m_minDist,m_maxDist);

        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::get_3d_max_distance
    //       Access: public
    //  Description: Get the distance that this sound stops falling off
    ////////////////////////////////////////////////////////////////////
    float TFMSound::get3DMaxDistance() const 
    {
        return m_maxDist;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSound::status
    //       Access: public
    //  Description: Get status of the sound.
    ////////////////////////////////////////////////////////////////////
    TFMSound::SoundStatus TFMSound::status() const 
    {
        // If the stream's channel isn't playing anything, then the stream
        // definitely isn't playing.
        if(!m_channel)
            return TFMSound::READY;

        bool is_playing;
        if (m_channel->isPlaying(&is_playing) == FMOD_OK) 
        {
            if(!is_playing)
                return TFMSound::READY;
        }

        bool is_paused;
        if (m_channel->getPaused(&is_paused) == FMOD_OK)
        {
            if(is_paused)
                return TFMSound::PAUSED;
        }

        // If the channel is playing, see whether the current time is at the
        // end of the file.  If not, the stream is playing.
        float current_time = this->getTime();
        if (current_time >= m_length - 0.01f) 
        {
            // FMOD MIDI files don't stop automatically when they hit the end of the
            // file.  Their channel isn't released unless the stream is stopped
            // explicitly.
            m_channel->stop();
            return TFMSound::READY;
        } 
        else 
        {
            return TFMSound::PLAYING;
        }
    }

}

#endif