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

#ifdef USE_IRR_SOUND

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                           T I r r S o u n d
    //-----------------------------------------------------------------------
    TIrrSound::TIrrSound(TIrrSoundManager* manager, ISoundSource* soundSource,
        TString file_name, float length)
        : m_manager(manager), m_soundSource(soundSource), m_sound(0), m_fileName(file_name),
        m_volume(1.0f), m_balance(0), m_loopCount(1), m_length(length), m_positional(false),
        m_active(true), m_paused(false), m_bExclusive(false),m_finishedEvent("")
    {
        m_minDist = 1.0f; m_maxDist = 1000000000.0f;

    }

    //-----------------------------------------------------------------------
    //                          ~ T I r r S o u n d
    //-----------------------------------------------------------------------
    TIrrSound::~TIrrSound() 
    {
        this->stop();
        m_manager->releaseSound(this);
    }

    //-----------------------------------------------------------------------
    //                               p l a y
    //-----------------------------------------------------------------------
    void TIrrSound::play() 
    {
        TStrStream msg;

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
        
        m_sound = m_manager->m_system->play2D(m_soundSource,false,true);

        if (!m_sound) 
        {
            getApplication()->logMessage("play() failed");
            return;
        }

        m_speed = m_sound->getPlaybackSpeed();
        m_sound->setSoundStopEventReceiver(this,this);

        // Set volume.
        m_sound->setVolume(m_volume);

        // Set panning.
        m_sound->setPan(m_balance);

        // Set 3d attributes, if needed
        if (m_positional) 
        {
            TVector3 pos;
            if(m_node)
                pos = m_node->getAbsolutePosition();

            irrklang::vec3df irr_pos;
            irr_pos.X = pos.X;
            irr_pos.Y = pos.Y;
            irr_pos.Z = pos.Z;
            irrklang::vec3df irr_vel;
            irr_vel.X = irr_vel.Y = irr_vel.Z = 0.f;

            m_sound->setPosition(irr_pos);
            m_sound->setVelocity(irr_vel);

            m_sound->setMinDistance(m_minDist);
            m_sound->setMaxDistance(m_maxDist);

        }
        // Set looping -- unimplemented

        // Unpause and set status to playing

        m_sound->setIsPaused(false);

    }


    //-----------------------------------------------------------------------
    //                              p a u s e
    //-----------------------------------------------------------------------
    void TIrrSound::pause()
    {
        if (!m_active) 
        {
            return;
        }
        // If the sound is already playing, stop it.
        if ((this->status() == TSound::PLAYING) && m_sound)
        {
            m_sound->setIsPaused(true);
        }

    }

    //-----------------------------------------------------------------------
    //                              r e s u m e
    //-----------------------------------------------------------------------
    void TIrrSound::resume()
    {
        if((this->status() == TSound::PAUSED) && m_sound)
        {
            m_sound->setIsPaused(true);
        }

    }

    //-----------------------------------------------------------------------
    //                               s t o p
    //-----------------------------------------------------------------------
    void TIrrSound::stop() 
    {
        if(!m_sound)
            return;

        m_sound->stop();
    }

    //-----------------------------------------------------------------------
    //                           i s P l a y i n g
    //-----------------------------------------------------------------------
    bool TIrrSound::isPlaying()
    {
        return  this->status() == TSound::PLAYING;
    }

    //-----------------------------------------------------------------------
    //                           f i n i s h e d
    //-----------------------------------------------------------------------
    void TIrrSound::finished() 
    {
        stop();
        if(m_finishedEvent.size())
        {
            TEvent* event;
            event = new TEvent(m_finishedEvent);
            getApplication()->queueEvent(event);
        }
    }

    //-----------------------------------------------------------------------
    //                           s e t L o o p
    //-----------------------------------------------------------------------
    void TIrrSound::setLoop(bool loop) 
    {
        m_sound->setIsLooped(loop);

        // default to loop infinitely
        m_loopCount = loop ? 0 : 1;
        //m_sound->setLoopCount(m_loopCount - 1);
    }

    //-----------------------------------------------------------------------
    //                           g e t L o o p
    //-----------------------------------------------------------------------
    bool TIrrSound::getLoop() const 
    {
        // 0 means loop forever,
        // >1 means loop that many times
        // So m_loopCount != 1 means we're looping
        
        return (m_loopCount != 1);
    }

    //-----------------------------------------------------------------------
    //                       s e t L o o p C o u n t
    //-----------------------------------------------------------------------
    void TIrrSound::setLoopCount(unsigned long loop_count) 
    {
        // not supported in irrklang

        if (loop_count < 0) 
        {
            loop_count = 0;
        }
        m_loopCount = loop_count;
        loop_count -= 1; 
        //m_sound->setLoopCount(loop_count);
    }

    //-----------------------------------------------------------------------
    //                           g e t L o o p C o u n t
    //-----------------------------------------------------------------------
    unsigned long TIrrSound::getLoopCount() const 
    {
        return m_loopCount;
    }

    //-----------------------------------------------------------------------
    //                       s e t P o s i t i o n a l
    //-----------------------------------------------------------------------
    bool TIrrSound::setPositional(bool value)
    {

        bool rc=false;

        if(m_positional == value)
            return true;


        m_positional = value;
        return rc;

    }

    //-----------------------------------------------------------------------
    //                       g e t P o s i t i o n a l
    //-----------------------------------------------------------------------
    bool TIrrSound::getPositional()
    {
        return m_positional;
    }

    //-----------------------------------------------------------------------
    //                             s e t T i m e
    //-----------------------------------------------------------------------
    void TIrrSound::setTime(float start_time) 
    {
        if (start_time < 0.0f) 
        {
            start_time = 0.0f;
        } 
        else if (start_time > m_length) 
        {
            start_time = m_length - 0.01f;
        }
        m_sound->setPlayPosition((u32)(start_time * 1000.0f));
    }

    //-----------------------------------------------------------------------
    //                             g e t T i m e
    //-----------------------------------------------------------------------
    float TIrrSound::getTime() const 
    {
        if (status() != TSound::PLAYING)
        {
            return 0.0f;
        }

        u32 position;
        position = m_sound->getPlayPosition();
        float current_time = float(position) * 0.001f;
        return current_time;
    }

    //-----------------------------------------------------------------------
    //                           s e t V o l u m e
    //-----------------------------------------------------------------------
    void TIrrSound::setVolume(float vol) 
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
        m_sound->setVolume(m_volume);
    }

    //-----------------------------------------------------------------------
    //                           g e t V o l u m e
    //-----------------------------------------------------------------------
    float TIrrSound::getVolume() const 
    {
        return m_volume;
    }

    //-----------------------------------------------------------------------
    //                           s e t B a l a n c e
    //-----------------------------------------------------------------------
    void TIrrSound::setBalance(float bal) 
    {
        if (bal < -1.0f) {
            bal = -1.0f;
        } 
        else if (bal > 1.0f) {
            bal = 1.0f;
        }
        m_balance = bal;
        m_sound->setPan(m_balance);
    }

    //-----------------------------------------------------------------------
    //                           g e t B a l a n c e
    //-----------------------------------------------------------------------
    float TIrrSound::getBalance() const 
    {
        return m_balance;
    }

    //-----------------------------------------------------------------------
    //                       s e t P l a y R a t e
    //-----------------------------------------------------------------------
    void TIrrSound::setPlayRate(float rate) 
    {
        m_sound->setPlaybackSpeed(rate);
    }

    //-----------------------------------------------------------------------
    //                       g e t P l a y R a t e
    //-----------------------------------------------------------------------
    float TIrrSound::getPlayRate() const 
    {
        return m_sound->getPlaybackSpeed();
    }

    //-----------------------------------------------------------------------
    //                         s e t A c t i v e
    //-----------------------------------------------------------------------
    void TIrrSound::setActive(bool active) 
    {
        if (!active) {
            // Once looping works, a looping sound should be paused, not
            // stopped.  When the sound is activated again, it is unpaused.
            m_sound->setIsPaused(true);
        }
        else m_sound->setIsPaused(false);
        m_active = active;
    }

    //-----------------------------------------------------------------------
    //                         g e t A c t i v e
    //-----------------------------------------------------------------------
    bool TIrrSound::getActive() const 
    {
        return m_active;
    }

    //-----------------------------------------------------------------------
    //                   s e t F i n i s h e d E v e n t
    //-----------------------------------------------------------------------
    void TIrrSound::setFinishedEvent(const TString& event) 
    {
        m_finishedEvent = event;
    }

    //-----------------------------------------------------------------------
    //                   g e t F i n i s h e d E v e n t
    //-----------------------------------------------------------------------
    const TString& TIrrSound::getFinishedEvent() const 
    {
        return m_finishedEvent;
    }

    //-----------------------------------------------------------------------
    //                           g e t N a m e
    //-----------------------------------------------------------------------
    const TString& TIrrSound::getName() const 
    {
        return m_fileName;
    }

    //-----------------------------------------------------------------------
    //                            l e n g t h
    //-----------------------------------------------------------------------
    float TIrrSound::length() const 
    {
        return m_length;
    }

    //-----------------------------------------------------------------------
    //                       s e t 3 D A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TIrrSound::set3DAttributes(float px, float py, float pz, float vx, float vy, float vz) 
    {

        // Set 3d attributes, if needed
        if (m_positional) 
        {

            // Convert from Panda coordinates to Fmod coordinates
            irrklang::vec3df irr_pos, irr_vel;
            irr_pos.X = px;
            irr_pos.Y = py;
            irr_pos.Z = pz;
            irr_vel.X = vx;
            irr_vel.Y = vy;
            irr_vel.Z = vz;
            m_sound->setPosition(irr_pos);
            m_sound->setVelocity(irr_vel);
        }
    }

    //-----------------------------------------------------------------------
    //                       g e t 3 D A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TIrrSound::get3DAttributes(float *px, float *py, float *pz, float *vx, float *vy, float *vz) 
    {
        irrklang::vec3df val;
        val = m_sound->getPosition();
        *px = val.X;
        *py = val.Y;
        *pz = val.Z;
        val = m_sound->getVelocity();
        *vx = val.X;
        *vy = val.Y;
        *vz = val.Z;
    }

    //-----------------------------------------------------------------------
    //                     s e t 3 D M i n D i s t a n c e
    //-----------------------------------------------------------------------
    void TIrrSound::set3DMinDistance(float dist) 
    {
        m_minDist = dist;

        // Set 3d attributes, if needed
        if (m_positional) 
        {
            m_sound->setMaxDistance(m_minDist);
        }
    }

    //-----------------------------------------------------------------------
    //                     g e t 3 D M i n D i s t a n c e
    //-----------------------------------------------------------------------
    float TIrrSound::get3DMinDistance() const 
    {
        return m_minDist;
    }

    //-----------------------------------------------------------------------
    //                     s e t 3 D M a x D i s t a n c e
    //-----------------------------------------------------------------------
    void TIrrSound::set3DMaxDistance(float dist) 
    {
        m_maxDist = dist;

        // Set 3d attributes, if needed
        if (m_positional)
        {
            m_sound->setMaxDistance(m_maxDist);
        }
    }

    //-----------------------------------------------------------------------
    //                     g e t 3 D M a x D i s t a n c e
    //-----------------------------------------------------------------------
    float TIrrSound::get3DMaxDistance() const 
    {
        return m_maxDist;
    }

    //-----------------------------------------------------------------------
    //                            s t a t u s
    //-----------------------------------------------------------------------
    TSound::SoundStatus TIrrSound::status() const 
    {
        // If the stream's channel isn't playing anything, then the stream
        // definitely isn't playing.
        if(!m_sound)
            return TSound::READY;

        if (m_manager->m_system->isCurrentlyPlaying(m_sound->getSoundSource()))
            return TSound::PLAYING;

        if (m_sound->getIsPaused())
        {
            return TSound::PAUSED;
        }

        return TSound::READY;
    }

}

#endif