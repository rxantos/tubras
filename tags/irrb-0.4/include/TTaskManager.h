//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TTASKMANAGER_H_
#define _TTASKMANAGER_H_

namespace Tubras
{
    typedef TMap<TString, TTask*> TTaskMap;
    typedef TMap<TString, TTask*>::Iterator TTaskMapItr;
    /**
    TTaskManager Class.
    @remarks
    Task Manager class.
    */
    class TTaskManager : public TDelegate
    {
        friend class TApplication;
    private:
        TTaskMap			m_tasks;
        TTaskMap			m_doLaterTasks;
        TTaskMap            m_runningTasks;
        TTimer*             m_clock;
    protected:
        TTaskManager();
        virtual ~TTaskManager();
        int initialize();
    public:
        void update();
        void setGlobalClock(TTimer* clock);

        int registerTask(TTask* task);

        int start(TTask* task);
        int stop(TTask* task);

        int doMethodLater(Tubras::TTaskDelegate* delegate,u32 delay);

        int remove(const TString& taskName);
        int remove(TTask* task);
        TTask* get(const TString& taskName) {return m_tasks[taskName];};
    };
}

#endif

