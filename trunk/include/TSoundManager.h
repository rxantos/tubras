//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TSOUNDMANAGER_H__
#define _TSOUNDMANAGER_H__

namespace Tubras
{
    class TSoundManager;

    typedef TSoundManager* (Create_AudioManager_proc)();
    typedef TList<TSoundNode*> TSoundNodeList;

    class TSoundManager
    {
        friend class TApplication;
    protected:
        TSoundManager();
        virtual ~TSoundManager();
        virtual int initialize();

    public:

        virtual int step();

        static TSoundManager* createAudioManager();

        virtual void shutdown();

        virtual bool isValid() = 0;

        virtual TSound* getSound(const TString& file_name, bool positional = false) = 0;
        TSound* getnullSound();

        virtual void setListenerNode(ISceneNode* node);
        virtual ISceneNode* getListenerNode() {return m_listenerNode;}

        void addSoundNode(TSoundNode* node);
        void removeSoundNode(TSoundNode* node);

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
        ISceneNode*         m_listenerNode;
        TVector3            m_listenerPos;
        TVector3            m_listenerDir;


        // Avoid adding data members (instance variables) to this mostly abstract
        // base class.  This allows implementors of various sound systems the
        // best flexibility.

        static Create_AudioManager_proc* _create_AudioManager;
        int audio_cache_limit;
        double audio_doppler_factor;
        double audio_distance_factor;
        double audio_drop_off_factor;

        TSound* _null_sound;

    };
}
#endif 

