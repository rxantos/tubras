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

#ifndef __FMSOUNDMANAGER_H_
#define __FMSOUNDMANAGER_H_

#ifdef USE_FMOD_SOUND

#include "fmod.hpp"
#include "fmod_errors.h"

namespace Tubras
{
    class TFMSoundManager : public TSoundManager {
    public:
        TFMSoundManager();
        virtual ~TFMSoundManager();

        virtual int initialize();

        virtual int step();

        virtual bool isValid();

        virtual TSound* getSound(const TString resourceGroup, const TString&, bool positional = false);
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
        typedef std::map<TString, SoundCacheEntry> SoundMap;
        SoundMap            m_sounds;

        typedef std::list<TFMSound *> AudioSet;
        // The offspring of this manager:
        AudioSet _soundsOnLoan;
        unsigned int        m_concurrentSoundLimit;

        typedef std::list<TFMSound*> SoundsPlaying;
        // The sounds from this manager that are currently playing
        SoundsPlaying       m_soundsPlaying;

        // The Least Recently Used mechanism:
        typedef std::deque<TString> LRU;
        LRU                 m_lru;

        // RobCode
        // List of supported sound formats
        typedef std::vector<TString> SupportedTypes;
        SupportedTypes      m_supportedTypes;

        void releaseSound(TFMSound *audioSound);

        int                 m_cacheLimit;
        static int          m_activeManagers;
        bool                m_isValid;
        bool                m_active;
        float               m_volume;
        float               m_listenerPos [3];
        float               m_listenerVel [3];
        float               m_listenerForward [3];
        float               m_listenerUp [3];
        float               m_distanceFactor;
        float               m_dopplerFactor;
        float               m_dropOffFactor;

        char* load(TString resourceGroup, TFile& filename, size_t &size) const;

        friend class TFMSound;
    };

}
#endif
#endif 
