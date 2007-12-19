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
    class TTaskManager : public TSingleton<Tubras::TTaskManager>, public TObject
    {
    private:
        TTaskMap			m_tasks;
        TTaskMap			m_doLaterTasks;
        TTaskMap            m_runningTasks;
        TTimer*             m_clock;
    public:
        TTaskManager();
        virtual ~TTaskManager();

        static TTaskManager& getSingleton(void);
        static TTaskManager* getSingletonPtr(void);
        int initialize();
        void step();
        void setGlobalClock(TTimer* clock);

        int registerTask(TTask* task);

        int start(TTask* task);
        int stop(TTask* task);

        int doMethodLater(Tubras::TTaskDelegate* delegate,ULONG delay);

        int remove(const TString& taskName);
        int remove(TTask* task);
        TTask* get(const TString& taskName) {return m_tasks[taskName];};
    };
}

#endif