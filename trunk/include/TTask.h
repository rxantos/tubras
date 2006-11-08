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

#ifndef _TTASK_H_
#define _TTASK_H_

namespace Tubras
{

    /**
    TTask Class.
    @remarks
    Task Manager class.

    Creating a task automatically registers it with the Task Manager.  The task manager 
    automatically deletes registered tasks when the manager itself is destroyed.

    If you would like to remove a task that is no longer needed:
    1. Invoke TaskManager::remove()
    2. Delete the task manually

    */
    class TTask 
    {
        friend class TTaskManager;
    private:
        TTaskDelegate*          m_delegate;
        string                  m_name;
        void*                   m_userData;
        ULONG                   m_delayTime;
        ULONG                   m_startTime;
        int                     m_priority;
        string                  m_doneEvent;
        bool                    m_isRunning;
    public:
        ULONG                   m_elapsedTime;
        ULONG                   m_deltaTime;
        ULONG                   m_lastTime;

    public:
        TTask(string taskName, TTaskDelegate* delegate, int priority=0, long delayTime=0, 
            void* userData=NULL, string doneEvent="");
        virtual ~TTask();

        enum TaskStatus { cont, done, suspend };

        void setDelegate(TTaskDelegate* delegate);
        TTaskDelegate* getDelegate();

        void setName(string name);
        string getName();

        void setUserData(void* userData) ;
        void* getUserData();

        void setPriority(int priority);
        int getPriority();

        string getDoneEvent();
        void setDoneEvent(string doneEvent);

        inline bool isRunning() {return m_isRunning;};
        void start();
        void stop();


    };

#define TASK_DELEGATE(member) new Tubras::TTaskDelegate(this,(Tubras::TTaskDelegateFunction)&member)

}

#endif