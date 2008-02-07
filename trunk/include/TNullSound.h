//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
        void pause();
        void resume();

        bool isPlaying() {return false;}

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

        void setFinishedEvent(const TString& event);
        const TString& getFinishedEvent() const;

        const TString& getName() const;

        float length() const;

        void set3DAttributes(float px, float py, float pz,
            float vx, float vy, float vz);
        void get3DAttributes(float *px, float *py, float *pz,
            float *vx, float *vy, float *vz);

        void set3DMinDistance(float dist);
        float get3DMinDistance() const;

        void set3DMaxDistance(float dist);
        float get3DMaxDistance() const;

        bool setPositional(bool value) {return false;}
        bool getPositional() {return false;}

        TSound::SoundStatus status() const;

        friend class NullAudioManager;
    };

}

#endif

