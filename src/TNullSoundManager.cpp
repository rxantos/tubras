//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                    T N u l l S o u n d M a n a g e r
    //-----------------------------------------------------------------------
    TNullSoundManager::TNullSoundManager() 
    {

    }

    //-----------------------------------------------------------------------
    //                   ~ T N u l l S o u n d M a n a g e r
    //-----------------------------------------------------------------------
    TNullSoundManager::~TNullSoundManager() 
    {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                            i s V a l i d
    //-----------------------------------------------------------------------
    bool TNullSoundManager::isValid() 
    {
        return false;
    }

    //-----------------------------------------------------------------------
    //                          g e t S o u n d
    //-----------------------------------------------------------------------
    TSound* TNullSoundManager::getSound(const TString& file_name,   bool positional) 
    {
        return getnullSound();
    }

    //-----------------------------------------------------------------------
    //                       u n c a c h e S o u n d
    //-----------------------------------------------------------------------
    void TNullSoundManager::uncacheSound(const TString&) 
    {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                            c l e a r C a c h e
    //-----------------------------------------------------------------------
    void TNullSoundManager::clearCache() 
    {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                        s e t C a c h e L i m i t
    //-----------------------------------------------------------------------
    void TNullSoundManager::setCacheLimit(unsigned int) 
    {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                        g e t C a c h e L i m i t
    //-----------------------------------------------------------------------
    unsigned int TNullSoundManager::getCacheLimit() const 
    {
        // intentionally blank.
        return 0;
    }

    //-----------------------------------------------------------------------
    //                           s e t V o l u m e
    //-----------------------------------------------------------------------
    void TNullSoundManager::setVolume(float) {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                           g e t V o l u m e
    //-----------------------------------------------------------------------
    float TNullSoundManager::getVolume() const 
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                           s e t p l a y R a t e
    //-----------------------------------------------------------------------
    void TNullSoundManager::setplayRate(float) 
    {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                           g e t p l a y R a t e
    //-----------------------------------------------------------------------
    float TNullSoundManager::getplayRate() const 
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                           s e t A c t i v e
    //-----------------------------------------------------------------------
    void TNullSoundManager::setActive(bool) 
    {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                           g e t A c t i v e
    //-----------------------------------------------------------------------
    bool TNullSoundManager::getActive() const 
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //               s e t C o n c u r r e n t S o u n d L i m i t
    //-----------------------------------------------------------------------
    void TNullSoundManager::setConcurrentSoundLimit(unsigned int) 
    {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //               g e t C o n c u r r e n t S o u n d L i m i t
    //-----------------------------------------------------------------------
    unsigned int TNullSoundManager::getConcurrentSoundLimit() const {
        return 0;
    }

    //-----------------------------------------------------------------------
    //               r e d u c e S o u n d s P l a y i n g T o
    //-----------------------------------------------------------------------
    void TNullSoundManager::reduceSoundsPlayingTo(unsigned int) {
        // intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                     s t o p A l l S o u n d s
    //-----------------------------------------------------------------------
    void TNullSoundManager::
        stopAllSounds() {
            // intentionally blank.
    }
}

