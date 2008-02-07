//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TEVENTQUEUE_H_
#define _TEVENTQUEUE_H_

namespace Tubras
{


    /** TEventQueue class. 
    @remarks
    This class should be used as a base class for user defined
    classes that want to receive event notifications.
    */
    class TEventQueue
    {
    protected:
        typedef list<TEvent *> TEvents;
        TEvents           m_queue;

    public:

        TEventQueue();
        virtual ~TEventQueue();

        void queueEvent(TEvent* event);
        void clear();

        bool isQueueEmpty() const;
        TEvent* dequeueEvent();


    };

}

#endif

