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

#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                             T T a s k 
    //-----------------------------------------------------------------------
    TTask::TTask(string taskName, TTaskDelegate* delegate, int priority, long delayTime, 
        void* userData, string doneEvent)

    {
        m_name = taskName;
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
    void TTask::setName(string name)
    {
        m_name = name;
    }

    //-----------------------------------------------------------------------
    //                          g e t T a s k N a m e
    //-----------------------------------------------------------------------
    string TTask::getName()
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
    void TTask::setDoneEvent(string doneEvent)
    {
        m_doneEvent = doneEvent;
    }

    //-----------------------------------------------------------------------
    //                          g e t D o n e E v e n t
    //-----------------------------------------------------------------------
    string TTask::getDoneEvent()
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