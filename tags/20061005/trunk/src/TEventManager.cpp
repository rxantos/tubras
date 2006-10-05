//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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

static Tubras::TEventManager* theEventManager;

namespace Tubras
{

    TEventManager *getEventManager() {
        return theEventManager;
    }

    //-----------------------------------------------------------------------
    //                       T E v e n t M a n a g e r
    //-----------------------------------------------------------------------
    TEventManager::TEventManager()
    {
        theEventManager = this;
        m_prefix = "";
        m_application = getApplication();
        m_debug = m_application->getDebug();
        m_activeQueue = 1;
    }

    //-----------------------------------------------------------------------
    //                       ~ T E v e n t M a n a g e r
    //-----------------------------------------------------------------------
    TEventManager::~TEventManager()
    {

        TEventListenerMap::iterator cur;

        for(cur=m_listeners.begin();cur != m_listeners.end();cur++)
        {
            TEventDelegateMap::iterator dcur;
            while(cur->second.size() > 0)
            {
                dcur = cur->second.begin();
                TEventDelegate* d = dcur->first;
                remove(d);
                delete d;
            }
        }
        m_listeners.clear();

        if(m_eventQueue1)
            delete m_eventQueue1;

        if(m_eventQueue2)
            delete m_eventQueue2;

    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TEventManager* TSingleton<TEventManager>::ms_Singleton = 0;

    TEventManager* TEventManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TEventManager& TEventManager::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TEventManager::initialize()
    {
        //
        // using a double queue - event posted while events are being
        // processed will be processed the next step().
        //
        m_eventQueue1 = new TEventQueue();
        m_eventQueue2 = new TEventQueue();
        m_currentQueue = m_eventQueue1;
        return 0;
    }

    //-----------------------------------------------------------------------
    //                            a c c e p t
    //-----------------------------------------------------------------------
    int TEventManager::accept(string eventMsg,TEventDelegate* callback,void *extraData,
        int priority, bool enabled)
    {
        TEventListenerMap::iterator cur;
        cur = m_listeners.find(eventMsg);

        callback->setPriority(priority);
        callback->setEnabled(enabled);

        //
        // if not found, then create a new delegate map and entry
        //
        if(cur == m_listeners.end())
        {
            m_listeners[eventMsg] = TEventDelegateMap();
            cur = m_listeners.find(eventMsg);
        }

        TEventDelegateMap::iterator dcur;
        dcur = cur->second.find(callback);
        if(dcur == cur->second.end())
        {
            cur->second[callback] = extraData;
        }

        return 1;
    }

    //-----------------------------------------------------------------------
    //                            r e m o v e
    //-----------------------------------------------------------------------
    int TEventManager::remove(TEventDelegate* callback)
    {
        TEventListenerMap::iterator cur;
        TEventDelegateMap::iterator dcur;

        cur = m_listeners.begin();
        while(cur != m_listeners.end())
        {
            dcur = cur->second.find(callback);
            while(dcur != cur->second.end())
            {
                cur->second.erase(dcur);
                dcur = cur->second.find(callback);
            }
            ++cur;
        }

        //cur->second.erase(callback);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                            d e s t r o y
    //-----------------------------------------------------------------------
    int TEventManager::destroy(TEventDelegate* callback)
    {
        remove(callback);
        delete callback;
        return 0;
    }

    //-----------------------------------------------------------------------
    //                      s e t E v e n t P r e f i x 
    //-----------------------------------------------------------------------
    string TEventManager::setEventPrefix(string value)
    {
        string oldPrefix = m_prefix;
        m_prefix = value + oldPrefix;
        return oldPrefix;
    }

    //-----------------------------------------------------------------------
    //                              s e n d
    //-----------------------------------------------------------------------
    int TEventManager::send(TSEvent& event)
    {
#ifdef _DEBUG
        if(m_debug)
        {
            string msg = "Send Event: " + event->getName();
            m_application->logMessage(msg.c_str());
        }
#endif
        TEventListenerMap::iterator cur;

        cur = m_listeners.find(event->getName());
        if(cur == m_listeners.end())
            return 0;

        TEventDelegateMap::iterator dcur;
        dcur = cur->second.begin();
        while(dcur != cur->second.end())
        {
            if(dcur->first->m_enabled)
            {
                void *userData = dcur->second;

                if(userData)
                    event->setUserData(userData);

                int rc = (*dcur->first)(event);

                if(userData)
                    event->resetUserData();
            }
            ++dcur;
        }


        return 0;
    }

    //-----------------------------------------------------------------------
    //                             q u e u e
    //-----------------------------------------------------------------------
    int TEventManager::queue(TSEvent& event)
    {

#ifdef _DEBUG
        if(m_debug)
        {
            string msg = "Queue Event: " + event->getName();
            m_application->logMessage(msg.c_str());

        }
#endif
        m_currentQueue->queueEvent(event);

        return 0;
    }

    //-----------------------------------------------------------------------
    //                              s t e p
    //-----------------------------------------------------------------------
    int TEventManager::step()
    {
        int count=0;
        TEventQueue* m_procQueue = m_currentQueue;
        if(m_activeQueue == 1)
        {
            m_currentQueue = m_eventQueue2;
            m_activeQueue = 2;
        }
        else 
        {
            m_currentQueue = m_eventQueue1;
            m_activeQueue = 1;
        }

        while(!m_procQueue->isQueueEmpty())
        {
            TSEvent event = m_procQueue->dequeueEvent();
            send(event);
            ++count;
        }

        return count;
    }



}