//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TIRRSOUND_H_
#define _TIRRSOUND_H_

#ifdef USE_IRR_SOUND

#include "irrKlang.h"
using namespace irrklang;

namespace Tubras
{
    class TIrrSoundManager;


    class TIrrSound : public TSound, public ISoundStopEventReceiver {
    public:
        virtual ~TIrrSound();

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

	    void OnSoundStopped(ISound* sound, E_STOP_EVENT_CAUSE reason, void* userData);


        void finished();

    protected:

    private:
        TIrrSoundManager*   m_manager;
        ISoundSource*       m_soundSource;
        ISound*             m_sound;
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

        TIrrSound(TIrrSoundManager* manager, ISoundSource* soundSource,
            TString file_name, float length=0.0f);


        friend class TIrrSoundManager;
    };

}
#endif
#endif

