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

#ifndef _TEVENTMANAGER_H_
#define _TEVENTMANAGER_H_

namespace Tubras
{
    class TApplication;

    typedef std::map<TEventDelegate *,void *>   TEventDelegateMap;
    typedef std::map<string, TEventDelegateMap> TEventListenerMap;
    typedef std::map<string,size_t>             TEventRegistryMap;


    /** Global Event Manager.
    @remarks
    All events (keyboard, mouse, joystick, and user defined events) are
    sent and handled through this class.

    A single event delegate may be used to handle multiple events.

    All delegates are automatically cleaned up when the event manager is
    destroyed.  In order to delete/destroy a delegate outside of the
    event manager, use TEventManager::destroy().
    */
    class TEventManager : public TSingleton<Tubras::TEventManager>
    {
    protected:
        //
        // m_listeners is a map of: (eventString,DelegateMap(Delegate,extraData))
        //
        TEventQueue*            m_eventQueue1;
        TEventQueue*            m_eventQueue2;
        TEventQueue*            m_currentQueue;
        TEventListenerMap       m_listeners;
        TEventRegistryMap       m_registry;
        string                  m_prefix;
        TApplication*           m_application;
        bool                    m_debug;
        int                     m_activeQueue;
    public:
        TEventManager();
        virtual ~TEventManager();

        static TEventManager& getSingleton(void);
        static TEventManager* getSingletonPtr(void);
        int initialize();

        /** Step the event manager to process queued events.
        */
        int step();

        /** Set up a new delegate to be called for a specific event.
        @remarks
        Delegate member functions must be of the type:
        int class::func(string eventMessage,void *extraData)
        In order for a class member function to be a delegate candidate,
        the class must inherit from "TEventHandler".

        A TEventDelegate may be created using:
        EVENT_DELEGATE(ClassName::member_function)
        */
        size_t accept(string eventMsg,TEventDelegate* callback,void *extraData=NULL,
            int priority=0, bool enabled=true);

        size_t getEventID(string eventName);

        /** disables all events belonging to a class isntance
        */
        int disable(void *classInstance);

        /** enables all events belonging to a class isntance
        */
        int enable(void *classInstance);

        /** remove a delegate.
        */
        int remove(TEventDelegate* callback);

        /** remove and destroy a delegate.
        */
        int destroy(TEventDelegate* callback);

        /** Sends an event immediately to be processed by listening delegates.
        */
        int send(TSEvent& event);

        /** Queues an event for processing
        */
        int queue(TSEvent& event);

        /** Set a temporary prefix that is prepended to all events.
        @remarks
        In order to reset, call again with a value of ("").
        */
        string setEventPrefix(string value);

    };

    typedef Ogre::SharedPtr<TEventManager> TSEventManager;

    TEventManager *getEventManager();


}

#endif