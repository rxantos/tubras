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
#ifndef _TINTERVALCONTROLLER_H_
#define _TINTERVALCONTROLLER_H_

namespace Tubras
{

    class TIntervalController : public TController
    {
    protected:
        TIntervalDelegate*      m_delegate;
        void*                   m_userData;
        float                   m_duration;
        float                   m_start;
        float                   m_stop;
        float                   m_length;
        float                   m_elapsed;
        float                   m_current;
        bool                    m_finished;
        TString                 m_finishedEvent;

    public:
        TIntervalController(TString name, float start, float stop, float duration, 
            TIntervalDelegate* delegate,void* userData=0, TString finishedEvent="");

        virtual ~TIntervalController();

        void setFinishedEvent(TString value) {m_finishedEvent = value;}
        TString getFinishedEvent() {return m_finishedEvent;}

        virtual void update(float deltaTime);
    };

    typedef TIntervalController TInterval;

    #define INTERVAL_DELEGATE(member) new Tubras::TIntervalDelegate(this,(Tubras::TIntervalDelegateFunction)&member)
}

#endif