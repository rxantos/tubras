//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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

