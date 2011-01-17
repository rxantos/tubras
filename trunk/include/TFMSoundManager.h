//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TFMSOUNDMANAGER_H_
#define _TFMSOUNDMANAGER_H_

#ifdef USE_SOUND_FMOD

#include "fmod.hpp"
#include "fmod_errors.h"

#pragma comment( lib, "fmodex_vc.lib" )

namespace Tubras
{
    class TFMSoundManager : public TSoundManager {
    public:
        TFMSoundManager();
        virtual ~TFMSoundManager();

        virtual int initialize();

        virtual void update();

        virtual bool isValid();

        virtual TSound* getSound(const TString& file_name, bool positional = false);
        virtual void uncacheSound(const TString&);
        virtual void clearCache();
        virtual void setCacheLimit(unsigned int count);
        virtual unsigned int getCacheLimit() const;

        // Indicates that the given sound was the most recently used.
        void mostRecentlyUsed(const TString& path);

        // Uncaches the least recently used sound.
        bool uncacheSound();

        virtual void setVolume(float);
        virtual float getVolume() const;

        virtual void setActive(bool);
        virtual bool getActive() const;

        virtual void setConcurrentSoundLimit(unsigned int limit = 0);
        virtual unsigned int getConcurrentSoundLimit() const;

        virtual void reduceSoundsPlayingTo(unsigned int count);

        //virtual void stop_a_sound();
        virtual void stopAllSounds();

        // Changes to the positions of 3D spacialized sounds and the listener
        // are all made at once when this method is called. It should be put
        // in the main program loop.
        virtual void audio3DUpdate();

        // This controls the "set of ears" that listens to 3D spacialized sound
        // px, py, pz are position coordinates. Can be 0.0f to ignore.
        // vx, vy, vz are a velocity vector in UNITS PER SECOND (default: meters).
        // fx, fy and fz are the respective components of a unit forward-vector
        // ux, uy and uz are the respective components of a unit up-vector
        // These changes will NOT be invoked until audio_3d_update() is called.
        virtual void setAudio3DListenerAttributes(float px, float py, float pz,
            float vx, float xy, float xz, 
            float fx, float fy, float fz,
            float ux, float uy, float uz);
        virtual void getAudio3DListenerAttributes(float *px, float *py, float *pz,
            float *vx, float *vy, float *vz,
            float *fx, float *fy, float *fz,
            float *ux, float *uy, float *uz);

        // Control the "relative distance factor" for 3D spacialized audio. Default is 1.0
        // Fmod uses meters internally, so give a float in Units-per meter
        // Don't know what Miles uses.
        virtual void setAudio3DDistanceFactor(float factor);
        virtual float getAudio3DDistanceFactor() const;

        // Control the presence of the Doppler effect. Default is 1.0
        // Exaggerated Doppler, use >1.0
        // Diminshed Doppler, use <1.0
        virtual void setAudio3DDopplerFactor(float factor);
        virtual float getAudio3DDopplerFactor() const;

        // Exaggerate or diminish the effect of distance on sound. Default is 1.0
        // Faster drop off, use >1.0
        // Slower drop off, use <1.0
        virtual void setAudio3DDropOffFactor(float factor);
        virtual float getAudio3DDropOffFactor() const;

    protected:
        // increment or decrement the refcount of the given file's cache entry.
        // sounds can only be uncached when their refcounts are zero.
        void inc_refcount(const TString& file_name);
        void dec_refcount(const TString& file_name);
    private:
        FMOD::System        *m_system;

        typedef struct {
            size_t size; // size of the data field, in bytes
            unsigned int refcount; // how many AudioSound objects are referencing me?
            bool stale; // can this entry be  purged from the cache?
            char *data; // the memory-mapped audio file.
        } SoundCacheEntry;
        typedef TMap<TString, SoundCacheEntry*> SoundMap;
        SoundMap            m_sounds;

        typedef TList<TFMSound *> AudioSet;
        // The offspring of this manager:
        AudioSet _soundsOnLoan;
        unsigned int        m_concurrentSoundLimit;

        typedef TList<TFMSound*> SoundsPlaying;
        // The sounds from this manager that are currently playing
        SoundsPlaying       m_soundsPlaying;

        // The Least Recently Used mechanism:
        typedef TArray<TString> LRU;
        LRU                 m_lru;

        // RobCode
        // List of supported sound formats
        typedef TArray<TString> SupportedTypes;
        SupportedTypes      m_supportedTypes;

        void releaseSound(TFMSound *audioSound);

        int                 m_cacheLimit;
        static int          m_activeManagers;
        bool                m_isValid;
        bool                m_active;
        float               m_volume;
        float               m_distanceFactor;
        float               m_dopplerFactor;
        float               m_dropOffFactor;

        char* load(io::path& filename, size_t &size) const;

        friend class TFMSound;
    };

}
#endif
#endif 
