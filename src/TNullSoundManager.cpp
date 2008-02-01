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

