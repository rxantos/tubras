//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TEVENTMANAGER_H_
#define _TEVENTMANAGER_H_

namespace Tubras
{
    class TApplication;

    typedef TMap<TEventDelegate *,void *>    TEventDelegateMap;
    typedef TMap<u32, TEventDelegateMap*>    TEventListenerMap;
    typedef TMap<TString,u32>                TEventRegistryMap;


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
        friend class TApplication;
    protected:
        //
        // m_listeners is a map of: (eventString,DelegateMap(Delegate,extraData))
        //
        TEventQueue*            m_eventQueue1;
        TEventQueue*            m_eventQueue2;
        TEventQueue*            m_currentQueue;
        TEventListenerMap       m_listeners;
        TEventRegistryMap       m_registry;
        TString                 m_prefix;
        TApplication*           m_application;
        int                     m_debug;
        int                     m_activeQueue;

    protected:
        void removeCallBack(TEventDelegateMap* map,TEventDelegate* delegate);
        TEventManager();
        virtual ~TEventManager();
    public:

        static TEventManager& getSingleton(void);
        static TEventManager* getSingletonPtr(void);
        int initialize();

        /** Step the event manager to process queued events.
        */
        int step();

        /** Set up a new delegate to be called for a specific event.
        @remarks
        Delegate member functions must be of the type:
        int class::func(TString eventMessage,void *extraData)
        In order for a class member function to be a delegate candidate,
        the class must inherit from "TEventHandler".

        A TEventDelegate may be created using:
        EVENT_DELEGATE(ClassName::member_function)
        */
        u32 accept(const TString& eventMsg,TEventDelegate* callback,
            const void *extraData=NULL,int priority=0, bool enabled=true);

        u32 getEventID(const TString& eventName);
        u32 registerEvent(const TString& eventName);

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
        int send(TEvent* event);

        /** Queues an event for processing
        */
        int queue(TEvent* event);

        /** Set a temporary prefix that is prepended to all events.
        @remarks
        In order to reset, call again with a value of ("").
        */
        TString setEventPrefix(const TString& value);

    };

    TEventManager *getEventManager();
}

#endif

