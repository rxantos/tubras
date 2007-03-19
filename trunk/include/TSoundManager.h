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

#ifndef _TSOUNDMANAGER_H__
#define _TSOUNDMANAGER_H__

namespace Tubras
{
    class TSoundManager;

    typedef TSoundManager* (Create_AudioManager_proc)();
    typedef std::vector<TSoundNode*> TSoundNodeList;

    class TSoundManager : public TSingleton<TSoundManager>
    {
    public:
        TSoundManager();
        virtual ~TSoundManager();

        virtual int initialize();
        virtual int step();

        TSoundManager* getSingletonPtr(void);
        TSoundManager& getSingleton(void);

        // Create an AudioManager for each category of sounds you have.
        // E.g.
        //   MySoundEffects = create_AudioManager::AudioManager();
        //   MyMusicManager = create_AudioManager::AudioManager();
        //   ...
        //   my_sound = MySoundEffects.get_sound("neatSfx.mp3");
        //   my_music = MyMusicManager.get_sound("introTheme.mid");

        static TSoundManager* createAudioManager();

        virtual void shutdown();

        // If you're interested in knowing whether this audio manager
        // is valid, here's the call to do it.  It is not necessary
        // to check whether the audio manager is valid before making other
        // calls.  You are free to use an invalid sound manager, you
        // may get silent sounds from it though.  The sound manager and
        // the sounds it creates should not crash the application even
        // when the objects are not valid.
        virtual bool isValid() = 0;

        // Get a sound:
        virtual TSound* getSound(const TString& file_name, const TString resourceGroup, bool positional = false) = 0;
        TSound* getnullSound();

        virtual void setListenerNode(TSceneNode* node) {m_listenerNode = node;}
        virtual TSceneNode* getListenerNode() {return m_listenerNode;}

        void addSoundNode(TSoundNode* node);
        void removeSoundNode(TSoundNode* node);

        // Tell the AudioManager there is no need to keep this one cached.
        // This doesn't break any connection between AudioSounds that have
        // already given by get_sound() from this manager.  It's
        // only affecting whether the AudioManager keeps a copy of the sound
        // in its pool/cache.
        virtual void uncacheSound(const TString& file_name) = 0;
        virtual void clearCache() = 0;
        virtual void setCacheLimit(unsigned int count) = 0;
        virtual unsigned int getCacheLimit() const = 0;

        // Control volume:
        // FYI:
        //   If you start a sound with the volume off and turn the volume 
        //   up later, you'll hear the sound playing at that late point.
        // 0 = minimum; 1.0 = maximum.
        // inits to 1.0.
        virtual void setVolume(float volume) = 0;
        virtual float getVolume() const = 0;

        // Turn the manager on or off.
        // If you play a sound while the manager is inactive, it won't start.
        // If you deactivate the manager while sounds are playing, they'll
        // stop.
        // If you activate the manager while looping sounds are playing
        // (those that have a loop_count of zero),
        // they will start playing from the begining of their loop.
        // inits to true.
        virtual void setActive(bool flag) = 0;
        virtual bool getActive() const = 0;

        // This controls the number of sounds that you allow at once.  This
        // is more of a user choice -- it avoids talk over and the creation
        // of a cacophony.
        // It can also be used to help performance.
        // 0 == unlimited.
        // 1 == mutually exclusive (one sound at a time).  Which is an example of:
        // n == allow n sounds to be playing at the same time.
        virtual void setConcurrentSoundLimit(unsigned int limit = 0) = 0;
        virtual unsigned int getConcurrentSoundLimit() const = 0;

        // This is likely to be a utility function for the concurrent_sound_limit
        // options.  It is exposed as an API, because it's reasonable that it
        // may be useful to be here.  It reduces the number of concurrently
        // playing sounds to count by some implementation specific means.
        // If the number of sounds currently playing is at or below count then
        // there is no effect.
        virtual void reduceSoundsPlayingTo(unsigned int count) = 0;

        // Stop playback on all sounds managed by this manager.
        // This is effectively the same as reduce_sounds_playing_to(0), but
        // this call may be for efficient on some implementations.
        virtual void stopAllSounds() = 0;


        // Changes to the positions of 3D spacialized sounds and the listener
        // are all made at once when this method is called. It should be put
        // in the main program loop.
        virtual void audio3DUpdate() {step();};

        // This controls the "set of ears" that listens to 3D spacialized sound
        // px, py, pz are position coordinates. Can be 0.0f to ignore.
        // vx, vy, vz are a velocity vector in UNITS PER SECOND (default: meters).
        // fx, fy and fz are the respective components of a unit forward-vector
        // ux, uy and uz are the respective components of a unit up-vector
        // These changes will NOT be invoked until audio_3d_update() is called.
        virtual void setAudio3DListenerAttributes(float px, float py, float pz,
            float vx, float xy, float xz, 
            float fx, float fy, float fz,
            float ux, float uy, float uz) {};
        virtual void getAudio3DListenerAttributes(float *px, float *py, float *pz,
            float *vx, float *vy, float *vz,
            float *fx, float *fy, float *fz,
            float *ux, float *uy, float *uz) {};

        // Control the "relative distance factor" for 3D spacialized audio. Default is 1.0
        // Fmod uses meters internally, so give a float in Units-per meter
        // Don't know what Miles uses.
        virtual void setAudio3DDistanceFactor(float factor) {};
        virtual float getAudio3DDistanceFactor() const {return 0.0f;};

        // Control the presence of the Doppler effect. Default is 1.0
        // Exaggerated Doppler, use >1.0
        // Diminshed Doppler, use <1.0
        virtual void setAudio3DDopplerFactor(float factor) {};
        virtual float getAudio3DDopplerFactor() const {return 0.0f;};

        // Exaggerate or diminish the effect of distance on sound. Default is 1.0
        // Faster drop off, use >1.0
        // Slower drop off, use <1.0
        virtual void setAudio3DDropOffFactor(float factor) {};
        virtual float getAudio3DDropOffFactor() const {return 0.0f;};


    public:
        static void register_SoundManager_creator(Create_AudioManager_proc* proc);

    protected:
        friend class TSound;

        TSoundNodeList      m_3dSounds;
        TSceneNode*         m_listenerNode;


        // Avoid adding data members (instance variables) to this mostly abstract
        // base class.  This allows implementors of various sound systems the
        // best flexibility.

        static Create_AudioManager_proc* _create_AudioManager;
        int audio_cache_limit;
        double audio_doppler_factor;
        double audio_distance_factor;
        double audio_drop_off_factor;

        TSound* _null_sound;

        /*
        public:
        static TypeHandle get_class_type() {
        return _type_handle;
        }
        static void init_type() {
        TypedReferenceCount::init_type();
        register_type(_type_handle, "AudioManager",
        TypedReferenceCount::get_class_type());
        }
        virtual TypeHandle get_type() const {
        return get_class_type();
        }
        virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

        private:
        static TypeHandle _type_handle;
        */

    };
}
#endif // __SOUNDMANAGER_H__