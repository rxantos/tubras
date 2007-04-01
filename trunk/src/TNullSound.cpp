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

namespace {
    static const TString blank="";
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