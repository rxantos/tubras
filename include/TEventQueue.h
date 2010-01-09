//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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

