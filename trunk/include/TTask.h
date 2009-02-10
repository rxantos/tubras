//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
        TString                 m_name;
        void*                   m_userData;
        u32                     m_delayTime;
        u32                     m_startTime;
        int                     m_priority;
        TString                 m_doneEvent;
        bool                    m_isRunning;
        u32                     m_delay;
        u32                     m_taskNumber;
    public:
        u32                     m_elapsedTime;
        u32                     m_deltaTime;
        u32                     m_lastTime;

    public:
        TTask(const TString& taskName, TTaskDelegate* delegate, int priority=0, long delayTime=0, 
            void* userData=NULL, TString doneEvent="");
        virtual ~TTask();

        enum TaskStatus { cont, done, suspend };

        void setDelegate(TTaskDelegate* delegate);
        TTaskDelegate* getDelegate();

        void setName(const TString& name);
        TString getName();

        void setUserData(void* userData) ;
        void* getUserData();

        void setPriority(int priority);
        int getPriority();

        TString getDoneEvent();
        void setDoneEvent(const TString& doneEvent);

        inline bool isRunning() {return m_isRunning;};
        void start();
        void stop();


    };

#define TASK_DELEGATE(member) new Tubras::TTaskDelegate(this,(Tubras::TTaskDelegateFunction)&member)

}

#endif

