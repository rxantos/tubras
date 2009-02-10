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

        TTaskMapItr itr;
        while(m_tasks.size() > 0)
        {
            itr = m_tasks.getIterator();
            TTask* task = itr->getValue();
            remove(task);
            delete task;
        }

        m_tasks.clear();
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
            
            TTaskMap::Node* p = m_runningTasks.delink(node->getKey());
            delete p;
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

        TTaskMap::Node* p = m_tasks.delink(node->getKey());
        delete p;

        node = m_doLaterTasks.find(task->getName());
        if(node)
        {
            TTaskMap::Node* p = m_doLaterTasks.delink(node->getKey());
            delete p;
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                        d o M e t h o d L a t e r
    //-----------------------------------------------------------------------
    int TTaskManager::doMethodLater(Tubras::TTaskDelegate* delegate,u32 delay)
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
        bool removeSome=false;
        TList<TTaskMapItr> finishedTasks;
        TList<TTaskMapItr>::Iterator fit;

        //
        // check for waiting tasks to be released
        //
        for(TTaskMapItr it = m_doLaterTasks.getIterator(); !it.atEnd(); it++)
        {
            TTask*  task = it->getValue();
            u32 curTime = m_clock->getMilliseconds();
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
                u32 curTime = m_clock->getMilliseconds();
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
