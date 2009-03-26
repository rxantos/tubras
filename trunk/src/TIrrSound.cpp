//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
        : m_manager(manager), m_soundSource(soundSource), m_sound(0), 
        m_fileName(file_name), m_finishedEvent(""), m_volume(1.0f), m_balance(0), 
        m_minDist(1.0f), m_maxDist(1000000000.0f), m_loopCount(1), m_length(length), 
        m_active(true), m_paused(false), m_positional(false), m_bExclusive(false)
    {
        
    }

    //-----------------------------------------------------------------------
    //                          ~ T I r r S o u n d
    //-----------------------------------------------------------------------
    TIrrSound::~TIrrSound() 
    {
        this->stop();
        if(m_sound)
            m_sound->drop();
        if(m_soundSource)
            m_soundSource->drop();
        m_manager->releaseSound(this);
    }

    //-----------------------------------------------------------------------
    //                      O n S o u n d S t o p p e d
    //-----------------------------------------------------------------------
    void TIrrSound::OnSoundStopped(ISound* sound, E_STOP_EVENT_CAUSE reason, void* userData)
    {
        ((TIrrSound*)userData)->finished();
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
        
        if(m_positional)
        {
            TVector3 pos;
            if(m_node)
                pos = m_node->getAbsolutePosition();
            m_sound = m_manager->m_system->play3D(m_soundSource,pos,(m_loopCount==0),true);
        }
        else
        {
            m_sound = m_manager->m_system->play2D(m_soundSource,false,true);
        }

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
        // Set looping -- loop_count(0) - loop
        //                loop_count(>0) - loop x times

        if(m_loopCount == 0)
            m_sound->setIsLooped(true);

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
        if(m_finishedEvent.size())
        {
            TEvent* event;
            event = new TEvent(m_finishedEvent);
            getApplication()->queueEvent(event);
            event->drop();
        }
    }

    //-----------------------------------------------------------------------
    //                           s e t L o o p
    //-----------------------------------------------------------------------
    void TIrrSound::setLoop(bool loop) 
    {
        m_loopCount = loop ? 0 : 1;
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
        m_active = active;
        if(!m_sound)
            return;

        if (!active) {
            // Once looping works, a looping sound should be paused, not
            // stopped.  When the sound is activated again, it is unpaused.
            m_sound->setIsPaused(true);
        }
        else m_sound->setIsPaused(false);
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
#else
void TIrrSoundSuppressLinkerWarning() {}
#endif

