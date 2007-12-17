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
    static ULONG gTaskNumber=1;

    //-----------------------------------------------------------------------
    //                             T T a s k 
    //-----------------------------------------------------------------------
    TTask::TTask(TString taskName, TTaskDelegate* delegate, int priority, long delayTime, 
        void* userData, TString doneEvent)

    {
        m_taskNumber = gTaskNumber++;
        if(!taskName.size())
            m_name = taskName;
        else
        {
            TStrStream name;
            name << "_Task_" << m_taskNumber;
            m_name = name.str().c_str();
        }
        m_isRunning = false;
        m_delegate = delegate;
        m_priority = priority;
        m_delayTime = delayTime;
        m_userData = userData;
        m_doneEvent = doneEvent;
        TTaskManager::getSingleton().registerTask(this);
    }

    //-----------------------------------------------------------------------
    //                            ~T T a s k 
    //-----------------------------------------------------------------------
    TTask::~TTask()
    {
        if(m_delegate)
            delete m_delegate;
    }

    //-----------------------------------------------------------------------
    //                          s e t D e l e g a t e
    //-----------------------------------------------------------------------
    void TTask::setDelegate(TTaskDelegate* delegate)
    {
        m_delegate = delegate;
    }

    //-----------------------------------------------------------------------
    //                          g e t D e l e g a t e
    //-----------------------------------------------------------------------
    TTaskDelegate* TTask::getDelegate()
    {
        return m_delegate;
    }

    //-----------------------------------------------------------------------
    //                          s e t T a s k N a m e
    //-----------------------------------------------------------------------
    void TTask::setName(TString name)
    {
        m_name = name;
    }

    //-----------------------------------------------------------------------
    //                          g e t T a s k N a m e
    //-----------------------------------------------------------------------
    TString TTask::getName()
    {
        return m_name;
    }

    //-----------------------------------------------------------------------
    //                          s e t U s e r D a t a
    //-----------------------------------------------------------------------
    void TTask::setUserData(void* userData) 
    {
        m_userData = userData;
    }

    //-----------------------------------------------------------------------
    //                          g e t U s e r D a t a
    //-----------------------------------------------------------------------
    void* TTask::getUserData()
    {
        return m_userData;
    }

    //-----------------------------------------------------------------------
    //                          s e t P r i o r i t y 
    //-----------------------------------------------------------------------
    void TTask::setPriority(int priority)
    {
        m_priority = priority;
    }

    //-----------------------------------------------------------------------
    //                          g e t P r i o r i t y 
    //-----------------------------------------------------------------------
    int TTask::getPriority()
    {
        return m_priority;
    }

    //-----------------------------------------------------------------------
    //                          s e t D o n e E v e n t
    //-----------------------------------------------------------------------
    void TTask::setDoneEvent(TString doneEvent)
    {
        m_doneEvent = doneEvent;
    }

    //-----------------------------------------------------------------------
    //                          g e t D o n e E v e n t
    //-----------------------------------------------------------------------
    TString TTask::getDoneEvent()
    {
        return m_doneEvent;
    }

    //-----------------------------------------------------------------------
    //                              s t a r t
    //-----------------------------------------------------------------------
    void TTask::start()
    {
        if(m_isRunning)
            return;

        m_isRunning = true;
        m_delegate->setEnabled(true);
        TTaskManager::getSingleton().start(this);

    }

    //-----------------------------------------------------------------------
    //                               s t o p
    //-----------------------------------------------------------------------
    void TTask::stop()
    {
        if(!m_isRunning)
            return;

        m_isRunning = false;
        m_delegate->setEnabled(false);
        TTaskManager::getSingleton().stop(this);
    }

}