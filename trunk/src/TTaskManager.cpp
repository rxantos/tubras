//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
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

        for ( TTaskMapItr it = m_tasks.begin(); it != m_tasks.end(); it++)
        {
            TTask*  task = it->second;
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
        m_clock = NULL;
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
        if(m_runningTasks.find(task->getName()) != m_runningTasks.end())
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

        itr = m_runningTasks.find(task->getName());
        if(itr != m_runningTasks.end())
        {
            m_runningTasks.erase(itr);
        }


        return 0;
    }

    //-----------------------------------------------------------------------
    //                       r e g i s t e r T a s k
    //-----------------------------------------------------------------------
    int TTaskManager::registerTask(TTask* task)
    {
        if(m_tasks.find(task->getName()) != m_tasks.end())
        {
            TStrStream msg;
            msg << "Duplicate Task Registration: " << task->getName();
            logMessage(msg.str().c_str());
            return 1;
        }

        m_tasks[task->getName()] = task;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e
    //-----------------------------------------------------------------------
    int TTaskManager::remove(string taskName)
    {
        TTaskMapItr itr;

        itr = m_tasks.find(taskName);
        if(itr == m_tasks.end())
        {
            TStrStream msg;
            msg << "Attempt to remove non-existent task: " << taskName;
            logMessage(msg.str().c_str());
            return 1;
        }
        itr->second;
        remove(itr->second);


        return 0;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e
    //-----------------------------------------------------------------------
    int TTaskManager::remove(TTask* task)
    {
        TTaskMapItr itr;

        itr = m_tasks.find(task->getName());
        if(itr == m_tasks.end())
        {
            TStrStream msg;
            msg << "Attempt to remove non-existent task: " << task->getName();
            logMessage(msg.str().c_str());
            return 1;
        }

        if(task->isRunning())
            task->stop();

        m_tasks.erase(itr);

        itr = m_doLaterTasks.find(task->getName());
        if(itr != m_doLaterTasks.end())
            m_doLaterTasks.erase(itr);

        return 0;
    }

    //-----------------------------------------------------------------------
    //                            d o L a t e r
    //-----------------------------------------------------------------------
    int TTaskManager::doLater(TTask* task)
    {
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
        std::list<TTaskMapItr> finishedTasks;
        std::list<TTaskMapItr>::iterator fit;

        //
        // run tasks
        //
        for ( TTaskMapItr it = m_runningTasks.begin(); it != m_runningTasks.end(); it++)
        {
            TTask*  task = it->second;
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
                        TSEvent event;
                        event.bind(new TEvent(task->m_doneEvent));
                        event->addPointerParameter((void *) task);
                        getApplication()->sendEvent(event);
                    }
                    delete task;
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
                m_runningTasks.erase(it);
            }
        }


    }


}