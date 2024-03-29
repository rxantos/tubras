//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T T a s k M a n a g e r
    //-----------------------------------------------------------------------
    TTaskManager::TTaskManager() : TDelegate()
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
            task->m_startTime = m_clock->getMilliSeconds();
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
            getApplication()->logMessage(LOG_WARNING, 
                "Duplicate Task Registration: %s", task->getName().c_str());
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
            getApplication()->logMessage(LOG_WARNING, 
                "Attempt to remove non-existent task: %s", taskName.c_str());
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
            getApplication()->logMessage(LOG_WARNING, 
                "Attempt to remove non-existent task: %s", task->getName().c_str());
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
        task->m_startTime = m_clock->getMilliSeconds();
        task->m_delay = delay;
        m_doLaterTasks[task->getName()] = task;
        return 0;
    }

    //-----------------------------------------------------------------------
    //                               u p d a t e
    //-----------------------------------------------------------------------
    void TTaskManager::update()
    {
        //
        // check for waiting tasks to be released
        //
        if(m_doLaterTasks.size())
        {
            for(TTaskMapItr it = m_doLaterTasks.getIterator(); !it.atEnd(); it++)
            {
                TTask*  task = it->getValue();
                u32 curTime = m_clock->getMilliSeconds();
                task->m_elapsedTime = curTime - task->m_startTime;
                if(task->m_elapsedTime >= task->m_delay)
                {
                    task->start();
                    m_doLaterTasks.delink(it->getKey());
                    break;
                }
            }
        }

        //
        // run tasks
        //
        if(m_runningTasks.size())
        {
            TList<TTaskMapItr> finishedTasks;
            TList<TTaskMapItr>::Iterator fit;

            for ( TTaskMapItr it = m_runningTasks.getIterator(); !it.atEnd(); it++)
            {
                TTask*  task = it->getValue();
                //
                // set up task specific timing
                //
                u32 curTime = m_clock->getMilliSeconds();
                task->m_elapsedTime = curTime - task->m_startTime;
                task->m_deltaTime = curTime - task->m_lastTime;

                //
                // invoke the task delegate
                //
                int rc = task->m_delegate->Execute(task);
                task->m_lastTime = m_clock->getMilliSeconds();

                //
                // if finished, put it on the finished list.  it will
                // be removed later so the current processing isn't 
                // interrupted.
                //
                if(rc == TTask::done)
                {                
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
            if(finishedTasks.size())
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
}
