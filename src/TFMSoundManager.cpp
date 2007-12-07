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

#ifdef USE_FMOD_SOUND

namespace Tubras
{
    int TFMSoundManager::m_activeManagers = 0;

    TFMSoundManager::TFMSoundManager() : TSoundManager()
    {
    }

    TFMSoundManager::~TFMSoundManager() 
    {

        //
        // clean up sound objects
        //
        while(_soundsOnLoan.getSize() > 0)
        {
            TFMSound* sound = *(_soundsOnLoan.begin());			
            delete sound;

        }

        // Be sure to delete associated sounds before deleting the manager!
        _soundsOnLoan.empty();
        clearCache();
        --m_activeManagers;
        if (m_activeManagers == 0) 
        {
            m_system->close();
        }
    }

    int TFMSoundManager::initialize()
    {

        TStrStream msg;
        FMOD_RESULT result;

        //
        // these are "config" options - todo
        //
        m_active = true;
        m_volume = 1.0;

        //positional audio data
        m_distanceFactor     = .3048f;
        m_dopplerFactor      = 1.0f;
        m_dropOffFactor     = 1.0f;

        m_cacheLimit = audio_cache_limit;
        m_concurrentSoundLimit = 0;

        // RobCode
        // Fill list of supported types
        // Order of this list (first is most important) determines
        // the search order for sound files without an extension.
        m_supportedTypes.push_back("ogg");
        m_supportedTypes.push_back("wav");
        m_supportedTypes.push_back("mp3");
        m_supportedTypes.push_back("wma");
        m_supportedTypes.push_back("mid");
        m_supportedTypes.push_back("midi");
        m_supportedTypes.push_back("aiff");
        m_supportedTypes.push_back("flac");
        m_supportedTypes.push_back("rmi");

        // Initialize FMOD, if this is the first manager created.
        m_isValid = true;
        if (m_activeManagers == 0) 
        {
            result = FMOD::System_Create(&m_system);
            getApplication()->logMessage("Initializing FMOD Sound System.");

            unsigned int fmod_version;
            result = m_system->getVersion(&fmod_version);
            if (fmod_version < FMOD_VERSION) 
            {

                msg << "Wrong FMOD Version.  You have " << fmod_version
                    << ". You need " << FMOD_VERSION;
                getApplication()->logMessage(msg.str().c_str());
                m_isValid = false;
                return 1;
            }

            FMOD_SPEAKERMODE speakermode;

            result = m_system->getDriverCaps(0, 0, 0, 0, &speakermode);
            result = m_system->setSpeakerMode(speakermode);

            result = m_system->init(32,FMOD_INIT_NORMAL,0);
            if (result != FMOD_OK)
            {

                getApplication()->logMessage("FMOD initialization failure.");
                m_isValid = false;
                return 1;
            }

            result = m_system->set3DSettings(1.0, 1.0f, 1.0f);

        }

        // set 3D sound characteristics as they are given in the configrc
        setAudio3DDopplerFactor((float)audio_doppler_factor);
        setAudio3DDistanceFactor((float)audio_distance_factor);
        setAudio3DDropOffFactor((float)audio_drop_off_factor);
        // increment regardless of whether an error has occured -- the
        // destructor will do the right thing.
        ++m_activeManagers;
        return 0;
    }

    int TFMSoundManager::step()
    {
        TSoundManager::step();

        if(m_system->update() != FMOD_OK)
            return 1;
        return 0;
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::isValid
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    bool TFMSoundManager::isValid() 
    {
        bool check=true;
        if (m_sounds.size() != m_lru.getSize()) 
        {
            check=false;
        } 
        else 
        {
            LRU::Iterator i=m_lru.begin();

            for (; i != m_lru.end(); ++i) 
            {
                SoundMap::Iterator smi=m_sounds.find(*i);
                if (smi.atEnd())
                {
                    check=false;
                    break;
                }
            }
        }
        return m_isValid && check;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getSound
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    TSound* TFMSoundManager::getSound(const TString &file_name, bool positional) 
    {

        IFileSystem* archive=NULL;
        TString fullPath="";
        TString mangledName="";

        if(!isValid()) 
        {
            return getnullSound();
        }

        
        TFile path = file_name;

        // RobCode
        // test for an invalid suffix type
        TString suffix = downcase(path.get_extension());
        if (!suffix.empty()) 
        {
            SupportedTypes::iterator type_i=find(m_supportedTypes.begin(), m_supportedTypes.end(), suffix);
            // if suffix not found in list of supported types
            if (type_i == m_supportedTypes.end()) 
            {
                // print error and return
                TStrStream msg;
                msg << "TFMSoundManager::getSound: \""<<path<<"\" is not a supported sound file format.";
                getApplication()->logMessage(msg.str().c_str());
                getApplication()->logMessage("Supported formats are: OGG, WAV, MP3, WMA, MID, MIDI, AIFF, FLAC, RMI");
                return getnullSound();
            } 
            else 
            { // the suffix is of a supported type
                // resolve the path normally
                fullPath = file_name;
                archive = TFile::findArchive(resourceGroup,fullPath);
            }
        } 
        else 
        { // no suffix given. Search for supported file types of the same name.
            TStrStream msg;
            msg << "TFMSoundManager::getSound: \""<<path<<"\" has no extension. Searching for supported files with the same name.";
            getApplication()->logMessage(msg.str().c_str());
            // look for each type of file 
            SupportedTypes::const_iterator type_i; 
            for (type_i = m_supportedTypes.begin(); type_i != m_supportedTypes.end(); ++type_i) 
            { 

                path.set_extension(*type_i); // set extension as supported type

                fullPath = file_name;
                archive = TFile::findArchive(resourceGroup,fullPath);
                if(archive)
                    break;

            } // end for loop
            // if no valid file found
            if (type_i == m_supportedTypes.end() ) 
            {
                TStrStream msg;

                // just print a warning for now
                msg << "TFMSoundManager::getSound: \""<<file_name<<"\" does not exist, even with default sound extensions.";
                // reset path to no extension
                path.set_extension("");
            } 
            else 
            {
                TStrStream msg;
                msg << "TFMSoundManager::getSound: \""<<path<<"\" found using default sound extensions.";
                suffix = downcase(path.get_extension()); // update suffix (used below when loading file)
            }
        }

        // Get the sound, either from the cache or from disk.

        mangledName = resourceGroup;
        mangledName .append("::");
        mangledName.append(path);


        SoundMap::iterator si = m_sounds.find(mangledName);
        SoundCacheEntry *entry = NULL;
        if (si != m_sounds.end()) 
        {
            // The sound was found in the cache.
            entry = &(*si).second;
            TStrStream msg;
            msg << "Sound file '"<< mangledName <<"' found in cache.";
            getApplication()->logMessage(msg.str().c_str());
        } 
        else 
        {
            // The sound was not found in the cache.  Load it from disk.
            SoundCacheEntry new_entry;
            new_entry.data = load(resourceGroup, path, new_entry.size);
            if (!new_entry.data) 
            {
                getApplication()->logMessage("TFMSoundManager::load failed");
                return getnullSound();
            }
            new_entry.refcount = 0;
            new_entry.stale = true;

            // Add to the cache
            while (m_sounds.size() >= (unsigned int)m_cacheLimit) 
            {
                if (!uncacheSound()) 
                {
                    TStrStream msg;
                    msg << (m_sounds.size()+1) << "sounds cached. Limit is " << m_cacheLimit;
                    getApplication()->logMessage(msg.str().c_str());
                    break;
                }
            }

            si = m_sounds.insert(SoundMap::value_type(mangledName, new_entry)).first;

            // It's important that we assign entry to the address of the entry
            // we just added to the map, and not to the address of the
            // temporary variable new_entry, which we just defined locally and
            // is about to go out of scope.
            entry = &(*si).second;
        }

        // Create an FMOD object from the memory-mapped file.  Here remains
        // one last vestige of special-case MIDI code: apparently, FMOD
        // doesn't like creating streams from memory-mapped MIDI files.
        // They must therefore be streamed from disk every time.  This
        // causes strange things to happen when the same MIDI file is loaded
        // twice, and played simultaneously...so, *don't do that then*.  all
        // I can say is that MIDI support will be significantly improved in
        // FMOD v4.0!
        FMOD::Sound *stream = NULL;
        FMOD_MODE flags = FMOD_OPENMEMORY | FMOD_MPEGSEARCH | FMOD_SOFTWARE;

        // 3D sounds have to be mono. Forcing stereo streams
        // to be mono will create a speed hit.
        if (positional) 
        {
            flags |= FMOD_3D;
        } 
        else 
        {
            flags |= FMOD_2D;
        }

        TString os_path = path.to_os_specific();


        FMOD_CREATESOUNDEXINFO exinfo;
        memset(&exinfo,0,sizeof(exinfo));
        exinfo.cbsize = sizeof(exinfo);
        exinfo.length = (unsigned int) entry->size;

        m_system->createStream(entry->data,flags,&exinfo,&stream);

        if (stream == NULL) 
        {
            TStrStream msg;
            msg << "TFMSoundManager::getSound(" << file_name << ", " << positional
                << ") failed.";
            getApplication()->logMessage(msg.str().c_str());
            return getnullSound();
        }
        inc_refcount(mangledName);
        mostRecentlyUsed(mangledName);

        // determine length of sound
        unsigned int ulength;
        stream->getLength(&ulength,FMOD_TIMEUNIT_MS);

        float length = (float)ulength * 0.001f;

        // Build a new AudioSound from the audio data.
        TSound* audioSound = 0;
        TFMSound* fmodAudioSound = new TFMSound(this, stream, mangledName,
            length);
        fmodAudioSound->setActive(m_active);
        fmodAudioSound->setPositional(positional);
        _soundsOnLoan.push_back(fmodAudioSound);
        audioSound = fmodAudioSound;

        return audioSound;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::uncacheSound
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::uncacheSound(const TString& file_name) 
    {
        TFile path = file_name;

        SoundMap::iterator itor = m_sounds.find(path);
        if (itor == m_sounds.end()) 
        {
            TStrStream msg;
            msg << "TFMSoundManager::uncacheSound: no such entry "<<file_name;
            getApplication()->logMessage(msg.str().c_str());
            return;
        }

        // Mark the entry as stale -- when its refcount reaches zero, it will
        // be removed from the cache.
        SoundCacheEntry *entry = &(*itor).second;
        if (entry->refcount == 0) 
        {
            // If the refcount is already zero, it can be
            // purged right now!
            TStrStream msg;

            msg << "TFMSoundManager::uncacheSound: purging "<<path
                << " from the cache.";
            getApplication()->logMessage(msg.str().c_str());

            delete [] entry->data;

            // Erase the sound from the LRU list as well.
            LRU::iterator lru_i=find(m_lru.begin(), m_lru.end(), itor->first);
            m_lru.erase(lru_i);
            m_sounds.erase(itor);
        } 
        else 
        {
            entry->stale = true;
        }

    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::uncacheSound
    //       Access: Public
    //  Description: Uncaches the least recently used sound.
    ////////////////////////////////////////////////////////////////////
    bool TFMSoundManager::uncacheSound() 
    {
        // uncache least recently used:
        unsigned int orig_size = (unsigned int) m_lru.size();

        for (LRU::iterator it = m_lru.begin(); it != m_lru.end(); it++) 
        {
            LRU::reference path=m_lru.front();
            SoundMap::iterator i = m_sounds.find(path);
            if (i == m_sounds.end()) 
                continue;
            uncacheSound(path);
            if (m_lru.size() < orig_size) 
                return true;
        }
        return false;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::mostRecentlyUsed
    //       Access: Public
    //  Description: Indicates that the given sound was the most recently used.
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::mostRecentlyUsed(const TString& path) 
    {
        LRU::iterator i=find(m_lru.begin(), m_lru.end(), path);
        if (i != m_lru.end()) 
        {
            m_lru.erase(i);
        }
        // At this point, path should not exist in the m_lru:
        m_lru.push_back(path);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::clearCache
    //       Access: Public
    //  Description: Clear out the sound cache.
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::clearCache() 
    {
        // Mark all cache entries as stale.  Delete those which already have 
        // refcounts of zero.

        SoundMap::iterator itor = m_sounds.begin();

        // Have to use a while loop, not a for loop, since we don't want to
        // increment itor in the case in which we delete an entry.
        while (itor != m_sounds.end()) 
        {
            SoundCacheEntry *entry = &(*itor).second;
            if (entry->refcount == 0) 
            {
                delete [] entry->data;

                // Erase the sound from the LRU list as well.
                LRU::iterator lru_i=find(m_lru.begin(), m_lru.end(), itor->first);
                m_lru.erase(lru_i);
                m_sounds.erase(itor);

                itor = m_sounds.begin();
            } 
            else 
            {
                entry->stale = true;
                ++itor;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::setCacheLimit
    //       Access: Public
    //  Description: Set the number of sounds that the cache can hold.
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::setCacheLimit(unsigned int count) 
    {
        while (m_lru.size() > count) 
        {
            uncacheSound();
        }
        m_cacheLimit = count;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getCacheLimit
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    unsigned int TFMSoundManager::getCacheLimit() const 
    {
        return m_cacheLimit;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::releaseSound
    //       Access: Private
    //  Description:
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::releaseSound(TFMSound* audioSound) 
    {
        dec_refcount(audioSound->getName());

        _soundsOnLoan.remove(audioSound);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::setVolume
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::setVolume(float volume) 
    {
        if (m_volume!=volume) 
        {
            m_volume = volume;
            // Tell our AudioSounds to adjust:
            AudioSet::iterator i=_soundsOnLoan.begin();
            for (; i!=_soundsOnLoan.end(); ++i) 
            {
                (**i).setVolume((**i).getVolume());
            }
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getVolume
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    float TFMSoundManager::getVolume() const 
    {
        return m_volume;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::setActive
    //       Access: Public
    //  Description: turn on/off
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::setActive(bool active) 
    {
        if (m_active!=active) 
        {
            m_active=active;
            // Tell our AudioSounds to adjust:
            AudioSet::iterator i=_soundsOnLoan.begin();
            for (; i!=_soundsOnLoan.end(); ++i) 
            {
                (**i).setActive(m_active);
            }
        }
        m_active = active;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getActive
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    bool TFMSoundManager::getActive() const 
    {
        return m_active;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::setConcurrentSoundLimit
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::setConcurrentSoundLimit(unsigned int limit) 
    {
        m_concurrentSoundLimit = limit;
        reduceSoundsPlayingTo(m_concurrentSoundLimit);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getConcurrentSoundLimit
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    unsigned int TFMSoundManager::getConcurrentSoundLimit() const 
    {
        return m_concurrentSoundLimit;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::reduceSoundsPlayingTo
    //       Access: Private
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::reduceSoundsPlayingTo(unsigned int count) 
    {
        int limit = (int) m_soundsPlaying.size() - count;
        while (limit-- > 0) 
        {
            SoundsPlaying::iterator sound = m_soundsPlaying.begin();
            if(sound == m_soundsPlaying.end())
                break;
            (**sound).stop();
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::stop_a_sound
    //       Access: Public
    //  Description: Stop playback on one sound managed by this manager.
    ////////////////////////////////////////////////////////////////////
    //void TFMSoundManager::
    //stop_a_sound() {
    //  audio_debug("TFMSoundManager::stop_a_sound()");
    //  AudioSet::size_type s=_soundsOnLoan.size() - 1;
    //  reduceSoundsPlayingTo(s);
    //if (s == _soundsOnLoan.size()) return true;
    //return false;
    //}

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::stopAllSounds
    //       Access: Public
    //  Description: Stop playback on all sounds managed by this manager.
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::stopAllSounds() 
    {
        reduceSoundsPlayingTo(0);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::audio3DUpdate
    //       Access: Public
    //  Description: Commit position changes to listener and all
    //               positioned sounds. Normally, you'd want to call this
    //               once per iteration of your main loop.
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::audio3DUpdate() 
    {
        m_system->update();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::setAudio3DListenerAttributes
    //       Access: Public
    //  Description: Set position of the "ear" that picks up 3d sounds
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::setAudio3DListenerAttributes(float px, float py, float pz, 
        float vx, float vy, float vz, float fx, float fy, float fz, 
        float ux, float uy, float uz) 
    {
        FMOD_RESULT res;

        FMOD_VECTOR fmod_pos,fmod_vel,fmod_forward,fmod_up;
        fmod_pos.x = px;
        fmod_pos.y = py;
        fmod_pos.z = pz;

        fmod_vel.x = vx;
        fmod_vel.y = vy;
        fmod_vel.z = vz;

        fmod_forward.x = fx;
        fmod_forward.y = fy; 
        fmod_forward.z = fz;

        fmod_up.x = ux;
        fmod_up.y = uy;
        fmod_up.z = uz;

        res = m_system->set3DListenerAttributes(0,&fmod_pos, &fmod_vel,&fmod_forward, &fmod_up);

        if(res != FMOD_OK)
        {
            getApplication()->logMessage("Erroring setting sound listener attributes");
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getAudio3DListenerAttributes
    //       Access: Public
    //  Description: Get position of the "ear" that picks up 3d sounds
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::getAudio3DListenerAttributes(float *px, float *py, float *pz, 
        float *vx, float *vy, float *vz, 
        float *fx, float *fy, float *fz, 
        float *ux, float *uy, float *uz) 
    {
        FMOD_VECTOR pos,vel,forward,up;

        m_system->get3DListenerAttributes(0,&pos,&vel,&forward,&up);
        *px = pos.x;
        *py = pos.y;
        *pz = pos.z;

        *vx = vel.x;
        *vy = vel.y;
        *vz = vel.z;

        *fx = forward.x;
        *fy = forward.y;
        *fz = forward.z;

        *ux = up.x;
        *uy = up.y;
        *uz = up.z;
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::setAudio3DDistanceFactor
    //       Access: Public
    //  Description: Set units per meter (Fmod uses meters internally for
    //               its sound-spacialization calculations)
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::setAudio3DDistanceFactor(float factor) 
    {
        if (factor<0.0) 
        {
            factor = 0.0;
        }
        if (m_distanceFactor != factor)
        {
            float doppler,rolloffscale,distance;
            m_distanceFactor = factor;
            m_system->get3DSettings(&doppler,&distance,&rolloffscale);
            m_system->set3DSettings(doppler,factor,rolloffscale);
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getAudio3DDistanceFactor
    //       Access: Public
    //  Description: Gets units per meter (Fmod uses meters internally for
    //               its sound-spacialization calculations)
    ////////////////////////////////////////////////////////////////////
    float TFMSoundManager::getAudio3DDistanceFactor() const 
    {
        return m_distanceFactor;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::setAudio3DDopplerFactor
    //       Access: Public
    //  Description: Exaggerates or diminishes the Doppler effect. 
    //               Defaults to 1.0
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::setAudio3DDopplerFactor(float factor) 
    {
        if (factor<0.0) 
        {
            factor = 0.0;
        }
        if (m_dopplerFactor != factor) 
        {
            m_dopplerFactor = factor;
            float doppler,rolloffscale,distance;
            m_system->get3DSettings(&doppler,&distance,&rolloffscale);
            m_system->set3DSettings(factor,factor,rolloffscale);
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getAudio3DDopplerFactor
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    float TFMSoundManager::getAudio3DDopplerFactor() const 
    {
        return m_dopplerFactor;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::setAudio3DDropOffFactor
    //       Access: Public
    //  Description: Control the effect distance has on audability.
    //               Defaults to 1.0
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::setAudio3DDropOffFactor(float factor) 
    {
        if (factor<0.0) 
        {
            factor = 0.0;
        }
        if (m_dropOffFactor != factor) 
        {
            m_dropOffFactor = factor;
            float doppler,rolloffscale,distance;
            m_system->get3DSettings(&doppler,&distance,&rolloffscale);
            m_system->set3DSettings(factor,factor,factor);
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::getAudio3DDropOffFactor
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    float TFMSoundManager::getAudio3DDropOffFactor() const 
    {
        return m_dropOffFactor;

    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::inc_refcount
    //       Access: Protected
    //  Description: Increments the refcount of a file's cache entry.
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::inc_refcount(const TString& file_name) 
    {
        TFile path = file_name;
        SoundMap::iterator itor = m_sounds.find(path);
        if (itor == m_sounds.end()) 
        {
            return;
        }

        SoundCacheEntry *entry = &(*itor).second;
        entry->refcount++;
        entry->stale = false; // definitely not stale!
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::dec_refcount
    //       Access: Protected
    //  Description: Decrements the refcount of a file's cache entry. If
    //               the refcount reaches zero and the entry is stale, it
    //               will be removed from the cache.
    ////////////////////////////////////////////////////////////////////
    void TFMSoundManager::dec_refcount(const TString& file_name) 
    {
        TFile path = file_name;
        SoundMap::iterator itor = m_sounds.find(path);
        if (itor != m_sounds.end()) 
        {
            SoundCacheEntry *entry = &(*itor).second;
            entry->refcount--;
            if (entry->refcount == 0 && entry->stale) 
            {
                delete [] entry->data;

                // Erase the sound from the LRU list as well.
                if(m_lru.size() == 0)
                    return;
                LRU::iterator lru_i=find(m_lru.begin(), m_lru.end(), itor->first);
                if(lru_i == m_lru.end())
                    return;
                m_lru.erase(lru_i);
                m_sounds.erase(itor);
            }
        } 
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::load
    //       Access: Private
    //  Description: Loads the specified file into memory.  Returns a
    //               newly-allocated buffer, and stores the size of the
    //               buffer in size.  Returns NULL if an error occurs.
    ////////////////////////////////////////////////////////////////////
    char* TFMSoundManager::load(TString resourceGroup, TFile& filename, size_t &size) const 
    {
        // Check file type (based on filename suffix
        TString suffix = filename.get_extension();
#ifdef HAVE_ZLIB
        if (suffix == "pz") {
            suffix = Filename(filename.get_basename_wo_extension()).get_extension();
        }
#endif  // HAVE_ZLIB
        suffix = downcase(suffix);
        bool bSupported = false;
        if (suffix == "wav" || suffix == "mp3" || suffix == "mid"
            || suffix == "rmi" || suffix == "midi" || suffix == "flac"
            || suffix == "mod" || suffix == "s3m" || suffix == "it"
            || suffix == "ogg" || suffix == "aiff" || suffix == "wma") 
        {
            bSupported = true;
        }
        if (!bSupported) 
        {
            TStrStream msg;
            msg << "TFMSoundManager::load \""<<filename<<"\" is not a supported sound file format.";
            getApplication()->logMessage(msg.str().c_str());
            getApplication()->logMessage("Supported formats are: OGG, WAV, MP3, WMA, MID, MIDI, AIFF, FLAC, RMI");

            return NULL;
        }

        // open the file.
        std::istream *audioFile = NULL;

        TFile binary_filename = TFile::binary_filename(filename);

        TString fname = filename;

        Ogre::Archive* archive = TFile::findArchive(resourceGroup, fname);
        if(!archive)
        {
            TStrStream msg;
            msg << "File " << filename << " does not exist.";
            getApplication()->logMessage(msg.str().c_str());
            return NULL;
        }

        Ogre::DataStreamPtr pstream = archive->open(filename);

        if (pstream.getPointer() == NULL) 
        {
            // Unable to open.
            TStrStream msg;
            msg << "Unable to read " << fname << ".";
            getApplication()->logMessage(msg.str().c_str());
            return NULL;
        }

        // Determine the file size.
        size = pstream->size();

        // Read the entire file into memory.
        char *buffer = new char[size];
        if (buffer == NULL) 
        {
            pstream->close();
            return NULL;
        }
        if (pstream->read(buffer,size) != size) 
        {
            pstream->close();
            delete [] buffer;
            return NULL;
        }

        pstream->close();
        return buffer;
    }

}
#endif
