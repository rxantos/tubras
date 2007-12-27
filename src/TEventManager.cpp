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

        TEventListenerMap::Iterator cur;

        while(m_listeners.size() > 0)
        {
            cur=m_listeners.getIterator();
            TEventDelegateMap* map = cur->getValue();
            while(map->size() > 0)
            {
                TEventDelegateMap::Iterator itr = map->getIterator();
                TEventDelegate*d = itr->getKey();
                remove(d);
                delete d;

            }
            m_listeners.delink(cur->getKey());
            delete map;
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
    //                          g e t E v e n t I D
    //-----------------------------------------------------------------------
    u32 TEventManager::getEventID(const TString& eventName)
    {

        const char* pIdentStr = eventName.c_str();
        // ripped from GCC code. Relatively simple hash of arbitrary  
        // text TString into a 32-bit identifier Output value is
        // input-valid-deterministic, but no guarantees are made
        // about the uniqueness of the output per-input
        //
        // Input value is treated as lower-case to cut down on false
        // separations cause by human mistypes. Sure, it could be
        // construed as a programming error to mix up your cases, and
        // it cuts down on permutations, but in Real World Usage
        // making this text case-sensitive will likely just lead to
        // Pain and Suffering.
        //
        // This code lossely based upon the adler32 checksum by Mark
        // Adler and published as part of the zlib compression
        // library sources.

        // largest prime smaller than 65536
        unsigned long BASE = 65521L;

        // NMAX is the largest n such that 255n(n+1)/2 +
        // (n+1)(BASE-1) <= 2^32-1
        unsigned long NMAX = 5552;

#define DO1(buf,i)  {s1 += tolower(buf[i]); s2 += s1;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);

        if (pIdentStr == NULL)
            return NULL;

        unsigned long s1 = 0;
        unsigned long s2 = 0;

        for ( size_t len = strlen( pIdentStr ); len > 0 ; )
        {
            size_t k = len < NMAX ? len : NMAX;

            len -= k;

            while (k >= 16)
            {
                DO16(pIdentStr);
                pIdentStr += 16;
                k -= 16;
            }

            if (k != 0) do
            {
                s1 += *pIdentStr++;
                s2 += s1;
            } while (--k);

            s1 %= BASE;
            s2 %= BASE;
        }

#pragma warning(push)
#pragma warning(disable : 4312)

        return (s2 << 16) | s1;

#pragma warning(pop)
#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16
    }

    //-----------------------------------------------------------------------
    //                        r e g i s t e r E v e n t
    //-----------------------------------------------------------------------
    u32 TEventManager::registerEvent(const TString& eventName)
    {
        u32 id;

        TEventRegistryMap::Node* node;
        node = m_registry.find(eventName);
        if(node)
        {
            id = node->getValue();
        }
        else
        {
            id = getEventID(eventName);
            m_registry[eventName] = id;
        }

        return id;

    }

    //-----------------------------------------------------------------------
    //                            a c c e p t
    //-----------------------------------------------------------------------
    u32 TEventManager::accept(const TString& eventMsg,TEventDelegate* callback,void *extraData,
        int priority, bool enabled)
    {
        u32 id;

        TEventRegistryMap::Node* node;
        

        node = m_registry.find(eventMsg);
        if(node)
        {
            id = node->getValue();
        }
        else
        {
            id = getEventID(eventMsg);
            m_registry[eventMsg] = id;
        }



        callback->setPriority(priority);
        callback->setEnabled(enabled);

        //
        // if not found, then create a new delegate map and entry
        //
        TEventDelegateMap* edm;
        TEventListenerMap::Node* mnode;
        mnode = m_listeners.find(id);
        if(!mnode)
        {
            edm = new TEventDelegateMap();
            m_listeners[id] = edm;
        }
        else edm = mnode->getValue();

        TEventDelegateMap::Node* dnode;
        dnode = edm->find(callback);
        if(!dnode)
        {
            (*edm)[callback] = extraData;
        }

        return id;
    }

    //-----------------------------------------------------------------------
    //                            d i s a b l e
    //-----------------------------------------------------------------------
    int TEventManager::disable(void *classInstance)
    {
        int result=0;

        TEventListenerMap::Iterator cur;

        for(cur=m_listeners.getIterator();!cur.atEnd();cur++)
        {
            TEventDelegateMap* edm = cur->getValue();
            TEventDelegateMap::Iterator dcur;
            for(dcur=edm->getIterator();!dcur.atEnd();dcur++)
            {
                TEventDelegate* d = dcur->getKey();
                if(d->getInstance() == classInstance)
                {
                    ++result;
                    d->setEnabled(false);
                }
            }
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                             e n a b l e
    //-----------------------------------------------------------------------
    int TEventManager::enable(void *classInstance)
    {
        int result=0;

        TEventListenerMap::Iterator cur;

        for(cur=m_listeners.getIterator();!cur.atEnd();cur++)
        {
            TEventDelegateMap* edm = cur->getValue();
            TEventDelegateMap::Iterator dcur;
            for(dcur=edm->getIterator();!dcur.atEnd();dcur++)
            {
                TEventDelegate* d = dcur->getKey();
                if(d->getInstance() == classInstance)
                {
                    ++result;
                    d->setEnabled(true);
                }
            }
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                            r e m o v e
    //-----------------------------------------------------------------------
    int TEventManager::remove(TEventDelegate* callback)
    {
        TEventListenerMap::Iterator cur;
        TEventDelegateMap* dmap;

        cur = m_listeners.getIterator();
        while(!cur.atEnd())
        {
            dmap = cur->getValue();
            removeCallBack(dmap,callback);
            cur++;
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                     r e m o v e C a l l B a c k
    //-----------------------------------------------------------------------
    void TEventManager::removeCallBack(TEventDelegateMap* map,TEventDelegate* delegate)
    {
        TEventDelegateMap::Iterator itr;
        itr = map->getIterator();

        while(!itr.atEnd())
        {
            TEventDelegate* del = itr->getKey();
            if(del == delegate)
            {
                map->delink(delegate);
                itr = map->getIterator();
            }
            else itr++;
        }
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
    TString TEventManager::setEventPrefix(const TString& value)
    {
        TString oldPrefix = m_prefix;
        m_prefix = value + oldPrefix;
        return oldPrefix;
    }

    //-----------------------------------------------------------------------
    //                              s e n d
    //-----------------------------------------------------------------------
    int TEventManager::send(TEvent* event)
    {
        if(m_debug >= DBG_EVENTS)
        {
            TString msg = "Send Event: ";
            msg += event->getName();
            m_application->logMessage(msg.c_str(),DBG_EVENTS);
        }
        TEventListenerMap::Node* node;

        //
        // anyone listening?
        //
        node = m_listeners.find(event->getID());
        if(!node)
            return 0;

        TEventDelegateMap::Iterator dcur;
        dcur = node->getValue()->getIterator();
		int rc=0;
        while(!rc && !dcur.atEnd())
        {
            if(dcur->getKey()->getEnabled())
            {
                void *userData = dcur->getValue();

                if(userData)
                    event->setUserData(userData);

                rc = dcur->getKey()->Execute(event);

                if(userData)
                    event->resetUserData();
            }
            dcur++;
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                             q u e u e
    //-----------------------------------------------------------------------
    int TEventManager::queue(TEvent* event)
    {

        if(m_debug >= DBG_EVENTS)
        {
            TString msg = "Queue Event: ";
            msg += event->getName();
            m_application->logMessage(msg.c_str(),DBG_EVENTS);

        }
        TEventListenerMap::Node* node;

        //
        // anyone listening?
        //
        node = m_listeners.find(event->getID());
        if(!node)
            return 0;

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
            TEvent* event = m_procQueue->dequeueEvent();
            send(event);
            ++count;
        }
        return count;
    }
}