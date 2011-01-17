//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

#ifdef USE_SOUND_FMOD

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
            getApplication()->logMessage(LOG_INFO, "Initializing FMOD Sound System.");

            unsigned int fmod_version;
            result = m_system->getVersion(&fmod_version);
            if (fmod_version < FMOD_VERSION) 
            {

                msg << "Wrong FMOD Version.  You have " << fmod_version
                    << ". You need " << FMOD_VERSION;
                getApplication()->logMessage(LOG_INFO, msg.str().c_str());
                m_isValid = false;
                return 1;
            }

            FMOD_SPEAKERMODE speakermode;

            result = m_system->getDriverCaps(0, 0, 0, 0, &speakermode);
            result = m_system->setSpeakerMode(speakermode);

            result = m_system->init(32,FMOD_INIT_NORMAL,0);
            if (result != FMOD_OK)
            {

                getApplication()->logMessage(LOG_ERROR, "FMOD initialization failure.");
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

    void TFMSoundManager::update()
    {
        TSoundManager::update();
        m_system->update();
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFMSoundManager::isValid
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    bool TFMSoundManager::isValid() 
    {
        bool check=true;
        if (m_sounds.size() != m_lru.size()) 
        {
            check=false;
        } 
        else 
        {
            

            for (u32 i=0; i != m_lru.size(); ++i) 
            {
                SoundMap::Iterator smi=m_sounds.find(m_lru[i]);
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

        TString fullPath="";
        TString mangledName="";
        IFileSystem* fileSystem=getApplication()->getFileSystem();

        if(!isValid()) 
        {
            return getnullSound();
        }

        
        io::path path = file_name.c_str();

        // test for an invalid suffix type
        io::path ext;
        irr::core::getFileNameExtension(ext, path);        
        TStdString suffix = ext.make_lower().c_str();
        if (suffix.size()) 
        {
            u32 i;
            for(i=0;i<m_supportedTypes.size();i++)
                if(m_supportedTypes[i] == suffix.c_str())
                    break;
            // if suffix not found in list of supported types
            if (i >= m_supportedTypes.size())
            {
                // print error and return
                TStrStream msg;
                msg << "TFMSoundManager::getSound: \"" << path.c_str()
                    << "\" is not a supported sound file format.";
                getApplication()->logMessage(LOG_ERROR, msg.str().c_str());
                getApplication()->logMessage(LOG_ERROR, "Supported formats are: OGG, WAV, MP3, WMA, MID, MIDI, AIFF, FLAC, RMI");
                return getnullSound();
            } 
            else 
            { // the suffix is of a supported type
                // resolve the path normally
                fullPath = file_name;
            }
        } 
        else 
        { // no suffix given. Search for supported file types of the same name.
            TStrStream msg;
            msg << "TFMSoundManager::getSound: \"" << path.c_str()
                << "\" has no extension. Searching for supported files with the same name.";
            getApplication()->logMessage(LOG_WARNING, msg.str().c_str());
            // look for each type of file 
            u32 i;
            for (i=0;i<m_supportedTypes.size();i++)
            { 
                fullPath = path + "." + m_supportedTypes[i];
                if(fileSystem->existFile(fullPath.c_str()))
                {
                    path = fullPath;
                    break;
                }
            } // end for loop
            // if no valid file found
            if (i >= m_supportedTypes.size() ) 
            {
                TStrStream msg;

                // just print a warning for now
                msg << "TFMSoundManager::getSound: \"" << file_name.c_str() 
                    << "\" does not exist, even with default sound extensions.";
                getApplication()->logMessage(LOG_WARNING, msg.str().c_str());
                // reset path to no extension
            } 
            else 
            {
                TStrStream msg;
                msg << "TFMSoundManager::getSound: \""<<path.c_str()<<"\" found using default sound extensions.";
                getApplication()->logMessage(LOG_WARNING, msg.str().c_str());
                irr::core::getFileNameExtension(ext, path);        
                suffix = ext.make_lower().c_str();
            }
        }

        // Get the sound, either from the cache or from disk.

        mangledName = "$";
        mangledName .append("::");
        mangledName.append(path.c_str());


        SoundMap::Node* si = m_sounds.find(mangledName);
        SoundCacheEntry *entry = NULL;
        if (si)
        {
            // The sound was found in the cache.
            entry = si->getValue();
            TStrStream msg;
            msg << "Sound file '"<< mangledName.c_str() <<"' found in cache.";
            getApplication()->logMessage(LOG_INFO, msg.str().c_str());
        } 
        else 
        {
            // The sound was not found in the cache.  Load it from disk.
            SoundCacheEntry* new_entry = new SoundCacheEntry;
            new_entry->data = load(path, new_entry->size);
            if (!new_entry->data) 
            {
                getApplication()->logMessage(LOG_ERROR, "TFMSoundManager::load failed");
                return getnullSound();
            }
            new_entry->refcount = 0;
            new_entry->stale = true;

            // Add to the cache
            while (m_sounds.size() >= (unsigned int)m_cacheLimit) 
            {
                if (!uncacheSound()) 
                {
                    TStrStream msg;
                    msg << (m_sounds.size()+1) << "sounds cached. Limit is " << m_cacheLimit;
                    getApplication()->logMessage(LOG_INFO, msg.str().c_str());
                    break;
                }
            }

            m_sounds.insert(mangledName,new_entry);
            si = m_sounds.find(mangledName);


            // It's important that we assign entry to the address of the entry
            // we just added to the map, and not to the address of the
            // temporary variable new_entry, which we just defined locally and
            // is about to go out of scope.
            entry = si->getValue();
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

        TString os_path = getApplication()->getFileSystem()->getAbsolutePath(path);


        FMOD_CREATESOUNDEXINFO exinfo;
        memset(&exinfo,0,sizeof(exinfo));
        exinfo.cbsize = sizeof(exinfo);
        exinfo.length = (unsigned int) entry->size;

        m_system->createStream(entry->data,flags,&exinfo,&stream);

        if (stream == NULL) 
        {
            TStrStream msg;
            msg << "TFMSoundManager::getSound(" << file_name.c_str() << ", " << positional
                << ") failed.";
            getApplication()->logMessage(LOG_ERROR, msg.str().c_str());
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
        io::path path = file_name;

        SoundMap::Node* itor = m_sounds.find(path.c_str());
        if (!itor)
        {
            TStrStream msg;
            msg << "TFMSoundManager::uncacheSound: no such entry "<<file_name.c_str();
            getApplication()->logMessage(LOG_ERROR, msg.str().c_str());
            return;
        }

        // Mark the entry as stale -- when its refcount reaches zero, it will
        // be removed from the cache.
        SoundCacheEntry *entry =itor->getValue();
        if (entry->refcount == 0) 
        {
            // If the refcount is already zero, it can be
            // purged right now!
            TStrStream msg;

            msg << "TFMSoundManager::uncacheSound: purging " << path.c_str()
                << " from the cache.";
            getApplication()->logMessage(LOG_INFO, msg.str().c_str());

            delete [] entry->data;

            // Erase the sound from the LRU list as well.
            for(u32 i=0;i<m_lru.size();i++)
            {
                if(m_lru[i] == itor->getKey())
                {
                    m_lru.erase(i);
                    break;
                }

            }

            m_sounds.delink(itor->getKey());
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

        for (u32 i=0;i<m_lru.size();i++)
        {
            TString path=m_lru[i];
            SoundMap::Node* it = m_sounds.find(path);
            if (!it)
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

        for(u32 i=0;i<m_lru.size();i++)
        {
            if(m_lru[i] == path)
            {
                m_lru.erase(i);
                break;
            }
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

        SoundMap::Iterator itor = m_sounds.getIterator();

        // Have to use a while loop, not a for loop, since we don't want to
        // increment itor in the case in which we delete an entry.
        while (!itor.atEnd())
        {
            SoundCacheEntry *entry = itor->getValue();
            if (entry->refcount == 0) 
            {
                delete [] entry->data;

                delete entry;

                // Erase the sound from the LRU list as well.
                for(u32 i=0;i<m_lru.size();i++)
                {
                    if(m_lru[i] == itor->getKey())
                    {
                        m_lru.erase(i);
                        break;
                    }
                }

                itor++;
            } 
            else 
            {
                entry->stale = true;
                itor++;
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

        AudioSet::Iterator itr = _soundsOnLoan.begin();
        while(itr != _soundsOnLoan.end())
        {
            if(*itr == audioSound)
            {
                _soundsOnLoan.erase(itr);
                break;
            }
            itr++;
        }
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
            AudioSet::Iterator i=_soundsOnLoan.begin();
            for (; i!=_soundsOnLoan.end(); i++) 
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
            AudioSet::Iterator i=_soundsOnLoan.begin();
            for (; i!=_soundsOnLoan.end(); i++) 
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
        int limit = (int) m_soundsPlaying.getSize() - count;
        while (limit-- > 0) 
        {
            SoundsPlaying::Iterator sound = m_soundsPlaying.begin();
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
            getApplication()->logMessage(LOG_ERROR, "Erroring setting sound listener attributes");
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
        io::path path = file_name.c_str();
        SoundMap::Node* itor = m_sounds.find(file_name);
        if (!itor)
        {
            return;
        }

        SoundCacheEntry *entry = itor->getValue();
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
        io::path path = file_name.c_str();
        SoundMap::Node* itor = m_sounds.find(file_name);
        if (itor)
        {
            SoundCacheEntry *entry = itor->getValue();
            entry->refcount--;
            if (entry->refcount == 0 && entry->stale) 
            {
                delete [] entry->data;

                // Erase the sound from the LRU list as well.
                if(m_lru.size() == 0)
                    return;

                for(u32 i=0;i<m_lru.size();i++)
                {
                    if(m_lru[i] == itor->getKey())
                    {
                        m_lru.erase(i);
                        m_sounds.delink(itor->getKey());
                        return;
                    }
                }
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
    char* TFMSoundManager::load(io::path& filename, size_t &size) const 
    {
        // Check file type (based on filename suffix
        io::path ext;
        irr::core::getFileNameExtension(ext, filename);
        TString suffix = ext.make_lower();
#ifdef HAVE_ZLIB
        if (suffix == "pz") {
            suffix = Filename(filename.get_basename_wo_extension()).get_extension();
        }
#endif  // HAVE_ZLIB
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
            msg << "TFMSoundManager::load \"" << filename.c_str()
                << "\" is not a supported sound file format.";
            getApplication()->logMessage(LOG_ERROR, msg.str().c_str());
            getApplication()->logMessage(LOG_ERROR, "Supported formats are: OGG, WAV, MP3, WMA, MID, MIDI, AIFF, FLAC, RMI");

            return NULL;
        }

        // open the file.
        std::istream *audioFile = NULL;

        io::path binary_filename = getApplication()->getFileSystem()->getAbsolutePath(filename);

        TString fname = filename;

        IFileSystem* fileSystem=getApplication()->getFileSystem();
        IReadFile* archive = fileSystem->createAndOpenFile(fname.c_str());

        if(!archive)
        {
            TStrStream msg;
            msg << "File " << filename.c_str() << " does not exist.";
            getApplication()->logMessage(LOG_ERROR, msg.str().c_str());
            return NULL;
        }

        // Determine the file size.
        size = archive->getSize();

        // Read the entire file into memory.
        char *buffer = new char[size];
        if (buffer == NULL) 
        {
            archive->drop();
            return NULL;
        }
        if ((size_t)(archive->read(buffer,(u32)size)) != size) 
        {
            archive->drop();
            delete [] buffer;
            return NULL;
        }

        archive->drop();
        return buffer;
    }

}
#else
void TFMSoundManagerSuppressLinkerWarning() {}
#endif
