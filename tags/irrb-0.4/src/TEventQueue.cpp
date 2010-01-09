//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                         T E v e n t Q u e u e
    //-----------------------------------------------------------------------
    TEventQueue::TEventQueue()
    {
    }

    //-----------------------------------------------------------------------
    //                        ~ T E v e n t Q u e u e
    //-----------------------------------------------------------------------
    TEventQueue::~TEventQueue()
    {
    }

    //-----------------------------------------------------------------------
    //                          q u e u e E v e n t
    //-----------------------------------------------------------------------
    void TEventQueue::queueEvent(TEvent* event)
    {
        m_queue.push_back(event);

    }

    //-----------------------------------------------------------------------
    //                              c l e a r
    //-----------------------------------------------------------------------
    void TEventQueue::clear()
    {
        m_queue.clear();
    }

    //-----------------------------------------------------------------------
    //                         i s Q u e u e E m p t y
    //-----------------------------------------------------------------------
    bool TEventQueue::isQueueEmpty() const
    {
        return m_queue.empty();
    }

    //-----------------------------------------------------------------------
    //                         d e q u e E v e n t
    //-----------------------------------------------------------------------
    TEvent* TEventQueue::dequeueEvent()
    {
        TEvent*  event;
        TEvents::Iterator itr = m_queue.begin();
        event = *itr;
        m_queue.erase(itr);
        return event;
    }
}
