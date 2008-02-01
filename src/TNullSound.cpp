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

namespace {
    static const Tubras::TString blank="";
    //  static float no_attributes [] = {0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f};
}

namespace Tubras
{
    ////////////////////////////////////////////////////////////////////
    //     Function: 
    //       Access: 
    //  Description: All of these functions are just stubs.
    ////////////////////////////////////////////////////////////////////
    TNullSound::TNullSound() 
    {
        // Intentionally blank.
    }

    TNullSound::~TNullSound() 
    {
        // Intentionally blank.
    }

    void TNullSound::play() 
    {
        // Intentionally blank.
    }

    void TNullSound::stop() 
    {
        // Intentionally blank.
    }

    void TNullSound::pause() 
    {
        // Intentionally blank.
    }

    void TNullSound::resume() 
    {
        // Intentionally blank.
    }

    void TNullSound::setLoop(bool) 
    {
        // Intentionally blank.
    }

    bool TNullSound::getLoop() const {
        return false; 
    }

    void TNullSound::setLoopCount(unsigned long) 
    {
        // Intentionally blank.
    }

    unsigned long TNullSound::getLoopCount() const 
    {
        return 0; 
    }

    void TNullSound::setTime(float) 
    {
        // Intentionally blank.
    }

    float TNullSound::getTime() const 
    {
        return 0; 
    }

    void TNullSound::setVolume(float) 
    {
        // Intentionally blank.
    }

    float TNullSound::getVolume() const 
    {
        return 0; 
    }

    void TNullSound::setBalance(float) {
        // Intentionally blank.
    }

    float TNullSound::getBalance() const 
    {
        return 0; 
    }

    void TNullSound::setPlayRate(float) 
    {
        // Intentionally blank.
    }

    float TNullSound::getPlayRate() const 
    {
        return 0; 
    }

    void TNullSound::setActive(bool) 
    {
        // Intentionally blank.
    }

    bool TNullSound::getActive() const 
    {
        return false; 
    }

    void TNullSound::setFinishedEvent(const TString& event) 
    {
        // Intentionally blank.
    }

    const TString& TNullSound::getFinishedEvent() const 
    {
        return blank;
    }

    const TString& TNullSound::getName() const 
    {
        return blank;
    }

    float TNullSound::length() const 
    {
        return 0;
    }

    void TNullSound::set3DAttributes(float px, float py, float pz, float vx, float vy, float vz) 
    {
        // Intentionally blank.
    }

    void TNullSound::get3DAttributes(float *px, float *py, float *pz, float *vx, float *vy, float *vz) 
    {
        // Intentionally blank.
    }

    void TNullSound::set3DMinDistance(float dist) 
    {
        // Intentionally blank.
    }

    float TNullSound::get3DMinDistance() const 
    {
        // Intentionally blank.
        return 0.0f;
    }

    void TNullSound::set3DMaxDistance(float dist) 
    {
        // Intentionally blank.
    }

    float TNullSound::get3DMaxDistance() const 
    {
        // Intentionally blank.
        return 0.0f;
    }

    TSound::SoundStatus TNullSound::status() const 
    {
        return TSound::READY; 
    }
}

