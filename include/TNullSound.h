//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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