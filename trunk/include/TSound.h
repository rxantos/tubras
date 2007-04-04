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

#ifndef _TSOUND_H__
#define _TSOUND_H__

namespace Tubras
{
    class TSound 
    {
    protected: 
        TSoundNode*             m_node;

    public:

        TSound();
        virtual ~TSound();

        virtual void setNode(TSoundNode* node) {m_node = node;}
        virtual TSoundNode* getNode() {return m_node;}

        // For best compatability, set the loop_count,
        // volume, and balance, prior to calling play().  You may
        // set them while they're playing, but it's implementation
        // specific whether you get the results.
        // - Calling play() a second time on the same sound before it is
        //   finished will start the sound again (creating a skipping or
        //   stuttering effect).
        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;

        // loop: false = play once; true = play forever.
        // inits to false.
        virtual void setLoop(bool loop=true) = 0;
        virtual bool getLoop() const = 0;

        // loop_count: 0 = forever; 1 = play once; n = play n times.
        // inits to 1.
        virtual void setLoopCount(unsigned long loop_count=1) = 0;
        virtual unsigned long getLoopCount() const = 0;

        // Control time position within the sound.
        // This is similar (in concept) to the seek position within
        // a file.
        // time in seconds: 0 = beginning; length() = end.
        // inits to 0.0.
        // - Unlike the other get_* and set_* calls for a sound, the
        //   current time position will change while the sound is playing.
        //   To play the same sound from a time offset a second time,
        //   explicitly set the time position again.  When looping, the
        //   second and later loops will start from the beginning of the
        //   sound.
        // - If a sound is playing, calling get_time() repeatedly will
        //   return different results over time.  e.g.:
        //   float percent_complete = s.get_time() / s.length();
        virtual void setTime(float start_time=0.0) = 0;
        virtual float getTime() const = 0;

        // 0 = minimum; 1.0 = maximum.
        // inits to 1.0.
        virtual void setVolume(float volume=1.0) = 0;
        virtual float getVolume() const = 0;

        // -1.0 is hard left
        // 0.0 is centered
        // 1.0 is hard right
        // inits to 0.0.
        virtual void setBalance(float balance_right=0.0) = 0;
        virtual float getBalance() const = 0;

        // play_rate is any positive float value.
        // inits to 1.0.
        virtual void setPlayRate(float play_rate=1.0f) = 0;
        virtual float getPlayRate() const = 0;

        // inits to manager's state.
        virtual void setActive(bool flag=true) = 0;
        virtual bool getActive() const = 0;

        // set 3d state
        virtual bool setPositional(bool value) = 0;
        virtual bool getPositional() = 0;

        // Set (or clear) the event that will be thrown when the sound
        // finishes playing.  To clear the event, pass an empty TString.
        virtual void setFinishedEvent(const TString& event) = 0;
        virtual const TString& getFinishedEvent() const = 0;

        // There is no set_name(), this is intentional.
        virtual const TString& getName() const = 0;

        // return: playing time in seconds.
        virtual float length() const = 0;

        // Controls the position of this sound's emitter.
        // px, py and pz are the emitter's position.
        // vx, vy and vz are the emitter's velocity in UNITS PER SECOND (default: meters).
        virtual void set3DAttributes(float px, float py, float pz,
            float vx, float vy, float vz);
        virtual void get3DAttributes(float *px, float *py, float *pz,
            float *vx, float *vy, float *vz);


        // Controls the distance (in units) that this sound begins to fall off.
        // Also affects the rate it falls off.
        // Default is 1.0
        // Closer/Faster, <1.0
        // Farther/Slower, >1.0
        virtual void set3DMinDistance(float dist);
        virtual float get3DMinDistance() const;

        // Controls the maximum distance (in units) that this sound stops falling off.
        // The sound does not stop at that point, it just doesn't get any quieter.
        // You should rarely need to adjust this.
        // Default is 1000000000.0
        virtual void set3DMaxDistance(float dist);
        virtual float get3DMaxDistance() const;

        enum SoundStatus { BAD, READY, PLAYING, PAUSED };
        virtual SoundStatus status() const = 0;

        friend class TSoundManager;

    };

}

#endif