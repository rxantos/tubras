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
        ULONG                   m_delayTime;
        ULONG                   m_startTime;
        int                     m_priority;
        TString                 m_doneEvent;
        bool                    m_isRunning;
        ULONG                   m_delay;
        ULONG                   m_taskNumber;
    public:
        ULONG                   m_elapsedTime;
        ULONG                   m_deltaTime;
        ULONG                   m_lastTime;

    public:
        TTask(TString taskName, TTaskDelegate* delegate, int priority=0, long delayTime=0, 
            void* userData=NULL, TString doneEvent="");
        virtual ~TTask();

        enum TaskStatus { cont, done, suspend };

        void setDelegate(TTaskDelegate* delegate);
        TTaskDelegate* getDelegate();

        void setName(TString name);
        TString getName();

        void setUserData(void* userData) ;
        void* getUserData();

        void setPriority(int priority);
        int getPriority();

        TString getDoneEvent();
        void setDoneEvent(TString doneEvent);

        inline bool isRunning() {return m_isRunning;};
        void start();
        void stop();


    };

#define TASK_DELEGATE(member) new Tubras::TTaskDelegate(this,(Tubras::TTaskDelegateFunction)&member)

}

#endif