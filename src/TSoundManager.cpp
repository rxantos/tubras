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

#define INITIAL_VECTOR_SIZE   100
#define INCREASE_VECTOR_SIZE  20

#define DOPPLER_SCALE         1.0
#define DISTANCE_FACTOR       1.0
#define ROLLOFF_SCALE         0.5

namespace Tubras
{

    template<> TSoundManager* TSingleton<TSoundManager>::ms_Singleton = 0;

    TSoundManager::TSoundManager()
    {
        //
        // todo: make these configurable
        //
        audio_cache_limit = 15;
        audio_doppler_factor = 1.0;
        audio_distance_factor = 1.0;
        audio_drop_off_factor = 1.0;
        m_listenerNode = 0;
    }

    TSoundManager::~TSoundManager()
    {

    }

    int TSoundManager::initialize()
    {
        return 0;
    }


    TSoundManager* TSoundManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }


    TSoundManager& TSoundManager::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSoundManager::shutdown
    //       Access: Published, Virtual
    //  Description: Call this at exit time to shut down the audio system.
    //               This will invalidate all currently-active
    //               AudioManagers and AudioSounds in the system.  If you
    //               change your mind and want to play sounds again, you
    //               will have to recreate all of these objects.
    ////////////////////////////////////////////////////////////////////
    void TSoundManager::shutdown() 
    {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSoundManager::get_null_sound
    //       Access: Public
    //  Description: Returns a special NullAudioSound object that has all
    //               the interface of a normal sound object, but plays no
    //               sound.  This same object may also be returned by
    //               get_sound() if it fails.
    ////////////////////////////////////////////////////////////////////
    TSound* TSoundManager::getnullSound() 
    {
        return new TNullSound();
    }

    //-----------------------------------------------------------------------
    //                       a d d S o u n d N o d e
    //-----------------------------------------------------------------------
    void TSoundManager::addSoundNode(TSoundNode* node)
    {
        TSoundNodeList::Iterator itr;

        for(itr = m_3dSounds.begin();itr != m_3dSounds.end();itr++)
        {
            if(node == *itr)
            {
                return;
            }
        }

        m_3dSounds.push_back(node);
    }

    //-----------------------------------------------------------------------
    //                    r e m o v e S o u n d N o d e
    //-----------------------------------------------------------------------
    void TSoundManager::removeSoundNode(TSoundNode* node)
    {
        TSoundNodeList::Iterator itr;

        for(itr = m_3dSounds.begin();itr != m_3dSounds.end();itr++)
        {
            if(node == *itr)
            {
                m_3dSounds.erase(itr);
                return;
            }
        }
    }

    //-----------------------------------------------------------------------
    //                     s e t L i s t e n e r N o d e
    //-----------------------------------------------------------------------
    void TSoundManager::setListenerNode(TSceneNode* node) 
    {
        m_listenerNode = node;
        if(m_listenerNode)
        {
            TVector3 pos = m_listenerNode->getAbsolutePosition();
            TVector3 dir = m_listenerNode->getRotation();
            dir.normalize();

            setAudio3DListenerAttributes(pos.X,pos.Y,pos.Z,
                0.f,0.f,0.f,
                dir.X,dir.Y,dir.Z,
                0.f,1.f,0.f);
            m_listenerPos = pos;
            m_listenerDir = dir;
        }
    }

    //-----------------------------------------------------------------------
    //                           s t e p
    //-----------------------------------------------------------------------
    int TSoundManager::step()
    {
        if(m_listenerNode)
        {
            TVector3 pos = m_listenerNode->getAbsolutePosition();
            TVector3 dir = m_listenerNode->getRotation();
            dir.normalize();

            if( (pos != m_listenerPos) || (dir != m_listenerDir))
            {
                setAudio3DListenerAttributes(pos.X,pos.Y,pos.Z,
                    0.f,0.f,0.f,
                    dir.X,dir.Y,dir.Z,
                    0.f,1.f,0.f);
                m_listenerPos = pos;
                m_listenerDir = dir;
            }
        }

        TSoundNode* node;
        TSoundNodeList::Iterator itr;

        for(itr = m_3dSounds.begin();itr != m_3dSounds.end();itr++)
        {
            node = *itr;
            TVector3 pos = node->getPosition();

            node->getSound()->set3DAttributes(pos.X,pos.Y,pos.Z,0.f,0.f,0.f);
        }


        return 0;
    }

}