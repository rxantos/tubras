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
        TSoundNodeList::iterator itr;

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
        TSoundNodeList::iterator itr;

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
            TVector3 pos = m_listenerNode->getDerivedPosition();
            TVector3 dir = m_listenerNode->getDerivedOrientation().zAxis();
            dir.normalise();

            setAudio3DListenerAttributes(pos.x,pos.y,pos.z,
                0.f,0.f,0.f,
                dir.x,dir.y,dir.z,
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
            TVector3 pos = m_listenerNode->getDerivedPosition();
            TVector3 dir = m_listenerNode->getDerivedOrientation().zAxis();
            dir.normalise();

            if( (pos != m_listenerPos) || (dir != m_listenerDir))
            {
                setAudio3DListenerAttributes(pos.x,pos.y,pos.z,
                    0.f,0.f,0.f,
                    dir.x,dir.y,dir.z,
                    0.f,1.f,0.f);
                m_listenerPos = pos;
                m_listenerDir = dir;
            }
        }

        TSoundNode* node;
        TSoundNodeList::iterator itr;

        for(itr = m_3dSounds.begin();itr != m_3dSounds.end();itr++)
        {
            node = *itr;
            TVector3 pos = node->getDerivedPosition();

            node->getSound()->set3DAttributes(pos.x,pos.y,pos.z,0.f,0.f,0.f);
        }


        return 0;
    }

}