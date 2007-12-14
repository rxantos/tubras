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

#ifdef USE_IRR_SOUND

namespace Tubras
{
    int TIrrSoundManager::m_activeManagers = 0;

    //-----------------------------------------------------------------------
    //                     T I r r S o u n d M a n a g e r
    //-----------------------------------------------------------------------
    TIrrSoundManager::TIrrSoundManager() : TSoundManager()
    {
    }

    //-----------------------------------------------------------------------
    //                    ~ T I r r S o u n d M a n a g e r
    //-----------------------------------------------------------------------
    TIrrSoundManager::~TIrrSoundManager() 
    {

        m_system->stopAllSounds();
        //
        // clean up sound objects
        //
        AudioSet::Iterator itr = _soundsOnLoan.begin();

        while(itr != _soundsOnLoan.end())
        {
            TIrrSound* sound = *itr;
            delete sound;
            itr++;
        }


        // Be sure to delete associated sounds before deleting the manager!
        _soundsOnLoan.empty();
        clearCache();
        --m_activeManagers;
        if (m_activeManagers == 0) 
        {
            m_system->drop();
        }
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TIrrSoundManager::initialize()
    {

        TStrStream msg;

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

        // Fill list of supported types
        // Order of this list (first is most important) determines
        // the search order for sound files without an extension.
        m_supportedTypes.push_back("ogg");
        m_supportedTypes.push_back("wav");
        m_supportedTypes.push_back("mp3");
        m_supportedTypes.push_back("mod");
        m_supportedTypes.push_back("it");
        m_supportedTypes.push_back("s3d");
        m_supportedTypes.push_back("xm");

        // Initialize FMOD, if this is the first manager created.
        m_isValid = true;
        if (m_activeManagers == 0) 
        {
            m_system = irrklang::createIrrKlangDevice();

            getApplication()->logMessage("Initializing IrrKlang Sound System.");

            if (!m_system)
            {

                msg << "Error Creating IrrKlang Device";
                getApplication()->logMessage(msg.str().c_str());
                m_isValid = false;
                return 1;
            }
            m_system->grab();

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

    int TIrrSoundManager::step()
    {
        TSoundManager::step();

        m_system->update();
        return 0;
    }


    //-----------------------------------------------------------------------
    //                             i s V a l i d
    //-----------------------------------------------------------------------
    bool TIrrSoundManager::isValid() 
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

    //-----------------------------------------------------------------------
    //                          g e t S o u n d
    //-----------------------------------------------------------------------
    TSound* TIrrSoundManager::getSound(const TString &file_name, bool positional) 
    {

        TString fullPath="";
        TString mangledName="";
        IFileSystem* fileSystem=getApplication()->getFileSystem();

        if(!isValid()) 
        {
            return getnullSound();
        }

        
        TFile path = file_name.c_str();

        // RobCode
        // test for an invalid suffix type
        TStdString suffix = downcase(path.get_extension());
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
                msg << "TIrrSoundManager::getSound: \""<<path<<"\" is not a supported sound file format.";
                getApplication()->logMessage(msg.str().c_str());
                getApplication()->logMessage("Supported formats are: OGG, WAV, MP3, WMA, MID, MIDI, AIFF, FLAC, RMI");
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
            msg << "TIrrSoundManager::getSound: \""<<path<<"\" has no extension. Searching for supported files with the same name.";
            getApplication()->logMessage(msg.str().c_str());
            // look for each type of file 
            u32 i;
            for (i=0;i<m_supportedTypes.size();i++)
            { 

                path.set_extension(m_supportedTypes[i].c_str()); // set extension as supported type

                fullPath = file_name;
                if(fileSystem->existFile(fullPath.c_str()))
                    break;
            } // end for loop
            // if no valid file found
            if (i >= m_supportedTypes.size() ) 
            {
                TStrStream msg;

                // just print a warning for now
                msg << "TIrrSoundManager::getSound: \"" << file_name.c_str() 
                    << "\" does not exist, even with default sound extensions.";
                // reset path to no extension
                path.set_extension("");
            } 
            else 
            {
                TStrStream msg;
                msg << "TIrrSoundManager::getSound: \""<<path.c_str()<<"\" found using default sound extensions.";
                suffix = downcase(path.get_extension()); // update suffix (used below when loading file)
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
            getApplication()->logMessage(msg.str().c_str());
        } 
        else 
        {
            // The sound was not found in the cache.  Load it from disk.
            SoundCacheEntry* new_entry = new SoundCacheEntry;
            new_entry->data = load(path, new_entry->size);
            if (!new_entry->data) 
            {
                getApplication()->logMessage("TIrrSoundManager::load failed");
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
                    getApplication()->logMessage(msg.str().c_str());
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

        ISoundSource* soundSource = m_system->addSoundSource((void*)entry->data,(s32)entry->size,file_name.c_str(),false);

        if (soundSource == NULL) 
        {
            TStrStream msg;
            msg << "TIrrSoundManager::getSound(" << file_name.c_str() << ", " << positional
                << ") failed.";
            getApplication()->logMessage(msg.str().c_str());
            return getnullSound();
        }
        inc_refcount(mangledName);
        mostRecentlyUsed(mangledName);

        // determine length of sound
        unsigned int ulength;

        ulength = soundSource->getPlayLength();

        float length = (float)ulength * 0.001f;

        // Build a new AudioSound from the audio data.
        TSound* audioSound = 0;
        TIrrSound* irrAudioSound = new TIrrSound(this, soundSource, mangledName,
            length);
        irrAudioSound->setActive(m_active);
        irrAudioSound->setPositional(positional);
        _soundsOnLoan.push_back(irrAudioSound);
        audioSound = irrAudioSound;

        return audioSound;
    }

    //-----------------------------------------------------------------------
    //                       u n c a c h e S o u n d
    //-----------------------------------------------------------------------
    void TIrrSoundManager::uncacheSound(const TString& file_name) 
    {
        TFile path = file_name.c_str();

        SoundMap::Node* itor = m_sounds.find(path.c_str());
        if (!itor)
        {
            TStrStream msg;
            msg << "TIrrSoundManager::uncacheSound: no such entry "<<file_name.c_str();
            getApplication()->logMessage(msg.str().c_str());
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

            msg << "TIrrSoundManager::uncacheSound: purging "<<path
                << " from the cache.";
            getApplication()->logMessage(msg.str().c_str());

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

    //-----------------------------------------------------------------------
    //                       u n c a c h e S o u n d
    //-----------------------------------------------------------------------
    bool TIrrSoundManager::uncacheSound() 
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

    //-----------------------------------------------------------------------
    //                  m o s t R e c e n t l y U s e d
    //-----------------------------------------------------------------------
    void TIrrSoundManager::mostRecentlyUsed(const TString& path) 
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

    //-----------------------------------------------------------------------
    //                       c l e a r C a c h e
    //-----------------------------------------------------------------------
    void TIrrSoundManager::clearCache() 
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

    //-----------------------------------------------------------------------
    //                       s e t C a c h e L i m i t
    //-----------------------------------------------------------------------
    void TIrrSoundManager::setCacheLimit(unsigned int count) 
    {
        while (m_lru.size() > count) 
        {
            uncacheSound();
        }
        m_cacheLimit = count;
    }

    //-----------------------------------------------------------------------
    //                       s e t C a c h e L i m i t
    //-----------------------------------------------------------------------
    unsigned int TIrrSoundManager::getCacheLimit() const 
    {
        return m_cacheLimit;
    }

    //-----------------------------------------------------------------------
    //                       r e l e a s e S o u n d
    //-----------------------------------------------------------------------
    void TIrrSoundManager::releaseSound(TIrrSound* audioSound) 
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

    //-----------------------------------------------------------------------
    //                          s e t V o l u m e
    //-----------------------------------------------------------------------
    void TIrrSoundManager::setVolume(float volume) 
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

    //-----------------------------------------------------------------------
    //                          g e t V o l u m e
    //-----------------------------------------------------------------------
    float TIrrSoundManager::getVolume() const 
    {
        return m_volume;
    }

    //-----------------------------------------------------------------------
    //                           s e t A c t i v e
    //-----------------------------------------------------------------------
    void TIrrSoundManager::setActive(bool active) 
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

    //-----------------------------------------------------------------------
    //                           g e t A c t i v e
    //-----------------------------------------------------------------------
    bool TIrrSoundManager::getActive() const 
    {
        return m_active;
    }

    //-----------------------------------------------------------------------
    //               s e t C o n c u r r e n t S o u n d L i m i t
    //-----------------------------------------------------------------------
    void TIrrSoundManager::setConcurrentSoundLimit(unsigned int limit) 
    {
        m_concurrentSoundLimit = limit;
        reduceSoundsPlayingTo(m_concurrentSoundLimit);
    }

    //-----------------------------------------------------------------------
    //               g e t C o n c u r r e n t S o u n d L i m i t
    //-----------------------------------------------------------------------
    unsigned int TIrrSoundManager::getConcurrentSoundLimit() const 
    {
        return m_concurrentSoundLimit;
    }

    //-----------------------------------------------------------------------
    //               r e d u c e S o u n d s P l a y i n g T o
    //-----------------------------------------------------------------------
    void TIrrSoundManager::reduceSoundsPlayingTo(unsigned int count) 
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

    //-----------------------------------------------------------------------
    //                       s t o p A l l S o u n d s
    //-----------------------------------------------------------------------
    void TIrrSoundManager::stopAllSounds() 
    {
        reduceSoundsPlayingTo(0);
    }

    //-----------------------------------------------------------------------
    //                       a u d i o 3 D U p d a t e
    //-----------------------------------------------------------------------
    void TIrrSoundManager::audio3DUpdate() 
    {
        m_system->update();
    }

    //-----------------------------------------------------------------------
    //          s e t A u d i o 3 D L i s t e n e r A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TIrrSoundManager::setAudio3DListenerAttributes(float px, float py, float pz, 
        float vx, float vy, float vz, float fx, float fy, float fz, 
        float ux, float uy, float uz) 
    {

        irrklang::vec3df irr_pos,irr_vel,irr_forward,irr_up;
        irr_pos.X = px;
        irr_pos.Y = py;
        irr_pos.Z = pz;

        irr_vel.X = vx;
        irr_vel.Y = vy;
        irr_vel.Z = vz;

        irr_forward.X = fx;
        irr_forward.Y = fy; 
        irr_forward.Z = fz;

        irr_up.X = ux;
        irr_up.Y = uy;
        irr_up.Z = uz;

        m_system->setListenerPosition(irr_pos,irr_forward,irr_vel,irr_up);

    }

    //-----------------------------------------------------------------------
    //          s e t A u d i o 3 D L i s t e n e r A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TIrrSoundManager::getAudio3DListenerAttributes(float *px, float *py, float *pz, 
        float *vx, float *vy, float *vz, 
        float *fx, float *fy, float *fz, 
        float *ux, float *uy, float *uz) 
    {
        // not supported by irrklang
    }


    //-----------------------------------------------------------------------
    //            s e t A u d i o 3 D D i s t a n c e F a c t o r
    //-----------------------------------------------------------------------
    void TIrrSoundManager::setAudio3DDistanceFactor(float factor) 
    {

        if (factor<0.0) 
        {
            factor = 0.0;
        }
        if (m_distanceFactor != factor)
        {
            m_distanceFactor = factor;
            m_system->setDopplerEffectParameters(m_dopplerFactor,m_distanceFactor);
        }

    }

    //-----------------------------------------------------------------------
    //            g e t A u d i o 3 D D i s t a n c e F a c t o r
    //-----------------------------------------------------------------------
    float TIrrSoundManager::getAudio3DDistanceFactor() const 
    {
        return m_distanceFactor;
    }

    //-----------------------------------------------------------------------
    //              s e t A u d i o 3 D D o p p l e r F a c t o r
    //-----------------------------------------------------------------------
    void TIrrSoundManager::setAudio3DDopplerFactor(float factor) 
    {
        if (factor<0.0) 
        {
            factor = 0.0;
        }
        if (m_dopplerFactor != factor) 
        {
            m_dopplerFactor = factor;
            m_system->setDopplerEffectParameters(m_dopplerFactor,m_distanceFactor);
        }
    }

    //-----------------------------------------------------------------------
    //              g e t A u d i o 3 D D o p p l e r F a c t o r
    //-----------------------------------------------------------------------
    float TIrrSoundManager::getAudio3DDopplerFactor() const 
    {
        return m_dopplerFactor;
    }

    //-----------------------------------------------------------------------
    //              s e t A u d i o 3 D D r o p O f f F a c t o r
    //-----------------------------------------------------------------------
    void TIrrSoundManager::setAudio3DDropOffFactor(float factor) 
    {
        if (factor<0.0) 
        {
            factor = 0.0;
        }
        if (m_dropOffFactor != factor) 
        {
            m_dropOffFactor = factor;
        }
    }

    //-----------------------------------------------------------------------
    //              g e t A u d i o 3 D D r o p O f f F a c t o r
    //-----------------------------------------------------------------------
    float TIrrSoundManager::getAudio3DDropOffFactor() const 
    {
        return m_dropOffFactor;

    }

    //-----------------------------------------------------------------------
    //                       i n c _ r e f c o u n t
    //-----------------------------------------------------------------------
    void TIrrSoundManager::inc_refcount(const TString& file_name) 
    {
        TFile path = file_name.c_str();
        SoundMap::Node* itor = m_sounds.find(file_name);
        if (!itor)
        {
            return;
        }

        SoundCacheEntry *entry = itor->getValue();
        entry->refcount++;
        entry->stale = false; // definitely not stale!
    }

    //-----------------------------------------------------------------------
    //                       d e c _ r e f c o u n t
    //-----------------------------------------------------------------------
    void TIrrSoundManager::dec_refcount(const TString& file_name) 
    {
        TFile path = file_name.c_str();
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

    //-----------------------------------------------------------------------
    //                             l o a d
    //-----------------------------------------------------------------------
    char* TIrrSoundManager::load(TFile& filename, size_t &size) const 
    {
        // Check file type (based on filename suffix
        TString suffix = downcase(filename.get_extension()).c_str();
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
            msg << "TIrrSoundManager::load \""<<filename<<"\" is not a supported sound file format.";
            getApplication()->logMessage(msg.str().c_str());
            getApplication()->logMessage("Supported formats are: OGG, WAV, MP3, WMA, MID, MIDI, AIFF, FLAC, RMI");

            return NULL;
        }

        // open the file.
        std::istream *audioFile = NULL;

        TFile binary_filename = TFile::binary_filename(filename);

        TString fname = filename.c_str();

        IFileSystem* fileSystem=getApplication()->getFileSystem();
        IReadFile* archive = fileSystem->createAndOpenFile(fname.c_str());




        if(!archive)
        {
            TStrStream msg;
            msg << "File " << filename << " does not exist.";
            getApplication()->logMessage(msg.str().c_str());
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
void TIrrSoundManagerSuppressLinkerWarning() {}
#endif
