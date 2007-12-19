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

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T T a s k M a n a g e r
    //-----------------------------------------------------------------------
    TTaskManager::TTaskManager() : TObject()
    {

    }

    //-----------------------------------------------------------------------
    //                       T T a s k M a n a g e r
    //-----------------------------------------------------------------------
    TTaskManager::~TTaskManager()
    {

        for ( TTaskMapItr it = m_tasks.getIterator(); !it.atEnd(); it++)
        {
            TTask*  task = it->getValue();
            if(task->isRunning())
                task->stop();

            delete task;
        }
        m_tasks.clear();
        m_runningTasks.clear();
        m_doLaterTasks.clear();

    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TTaskManager* TSingleton<TTaskManager>::ms_Singleton = 0;

    TTaskManager* TTaskManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TTaskManager& TTaskManager::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TTaskManager::initialize()
    {
        m_clock = getApplication()->getGlobalClock();
        return 0;
    }

    //-----------------------------------------------------------------------
    //                     s e t G l o b a l C l o c k
    //-----------------------------------------------------------------------
    void TTaskManager::setGlobalClock(TTimer* clock)
    {
        m_clock = clock;
    }

    //-----------------------------------------------------------------------
    //                             s t a r t 
    //-----------------------------------------------------------------------
    int TTaskManager::start(TTask* task)
    {

        TTaskMap::Node* node = m_runningTasks.find(task->getName());
        if(node)
            return 1;

        if(m_clock)
        {
            task->m_startTime = m_clock->getMilliseconds();
            task->m_lastTime = task->m_startTime;
        }
        m_runningTasks[task->getName()] = task;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                              s t o p
    //-----------------------------------------------------------------------
    int TTaskManager::stop(TTask* task)
    {
        //
        // remove from running list
        //

        TTaskMapItr itr;

        TTaskMap::Node* node = m_runningTasks.find(task->getName());
        if(node)
        {
            
            m_runningTasks.delink(node->getKey());
        }


        return 0;
    }

    //-----------------------------------------------------------------------
    //                       r e g i s t e r T a s k
    //-----------------------------------------------------------------------
    int TTaskManager::registerTask(TTask* task)
    {
        TTaskMap::Node* node = m_tasks.find(task->getName());
        if(node)
        {
            TStrStream msg;
            msg << "Duplicate Task Registration: " << task->getName().c_str();
            logMessage(msg.str().c_str());
            return 1;
        }

        m_tasks[task->getName()] = task;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e
    //-----------------------------------------------------------------------
    int TTaskManager::remove(const TString& taskName)
    {
        TTaskMap::Node* node = m_tasks.find(taskName);
        if(!node)
        {
            TStrStream msg;
            msg << "Attempt to remove non-existent task: " << taskName.c_str();
            logMessage(msg.str().c_str());
            return 1;
        }
        remove(node->getValue());
        return 0;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e
    //-----------------------------------------------------------------------
    int TTaskManager::remove(TTask* task)
    {
        TTaskMapItr itr;

        TTaskMap::Node* node = m_tasks.find(task->getName());
        if(!node)
        {
            TStrStream msg;
            msg << "Attempt to remove non-existent task: " << task->getName().c_str();
            logMessage(msg.str().c_str());
            return 1;
        }

        if(task->isRunning())
            task->stop();

        m_tasks.delink(node->getKey());

        node = m_doLaterTasks.find(task->getName());
        if(node)
            m_doLaterTasks.delink(node->getKey());

        return 0;
    }

    //-----------------------------------------------------------------------
    //                        d o M e t h o d L a t e r
    //-----------------------------------------------------------------------
    int TTaskManager::doMethodLater(Tubras::TTaskDelegate* delegate,ULONG delay)
    {
        TTask* task = new TTask("",delegate);
        task->m_startTime = m_clock->getMilliseconds();
        task->m_delay = delay;
        m_doLaterTasks[task->getName()] = task;
        return 0;
    }

    //-----------------------------------------------------------------------
    //                               s t e p
    //-----------------------------------------------------------------------
    void TTaskManager::step()
    {
        ULONG current_time = m_clock->getMilliseconds();
        bool removeSome=false;
        TList<TTaskMapItr> finishedTasks;
        TList<TTaskMapItr>::Iterator fit;

        //
        // check for waiting tasks to be released
        //
        for(TTaskMapItr it = m_doLaterTasks.getIterator(); !it.atEnd(); it++)
        {
            TTask*  task = it->getValue();
            ULONG curTime = m_clock->getMilliseconds();
            task->m_elapsedTime = curTime - task->m_startTime;
            if(task->m_elapsedTime >= task->m_delay)
            {
                task->start();
                m_doLaterTasks.delink(it->getKey());
                break;
            }

        }

        //
        // run tasks
        //
        for ( TTaskMapItr it = m_runningTasks.getIterator(); !it.atEnd(); it++)
        {
            TTask*  task = it->getValue();
            if(task->m_delegate->getEnabled())
            {
                //
                // set up task specific timing
                //
                ULONG curTime = m_clock->getMilliseconds();
                task->m_elapsedTime = curTime - task->m_startTime;
                task->m_deltaTime = curTime - task->m_lastTime;

                //
                // invoke the task delegate
                //
                int rc = task->m_delegate->Execute(task);
                task->m_lastTime = m_clock->getMilliseconds();

                //
                // if finished, put it on the finished list.  it will
                // be removed later so the current processing isn't 
                // interrupted.
                //
                if(rc == TTask::done)
                {                
                    removeSome = true;
                    if(task->m_doneEvent != "")
                    {
                        TEvent* event = new TEvent(task->m_doneEvent);
                        event->addPointerParameter((void *) task);
                        getApplication()->sendEvent(event);
                        event->drop();
                    }
                    finishedTasks.push_back(it);
                }
            }
        }

        //
        // remove finished tasks from the running list
        //
        if(removeSome)
        {
            for(fit=finishedTasks.begin();fit != finishedTasks.end(); ++fit)
            {
                TTaskMapItr it = *fit;
                it->getValue()->stop();
            }
            finishedTasks.clear();
        }


    }


}