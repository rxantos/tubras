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
    //                  T I n t e r v a l C o n t r o l l e r
    //-----------------------------------------------------------------------
    TIntervalController::TIntervalController(TString name, float start, float stop, float duration, 
        TIntervalDelegate* delegate, void* userData, TBlendType blendType, TString finishedEvent) : TController(name, 0),
        m_start(start), 
        m_stop(stop), 
        m_duration(duration),
        m_elapsed(0.f),
        m_length(m_stop-m_start),
        m_delegate(delegate),
        m_userData(userData),
        m_finished(false),
        m_current(m_start),
        m_blendType(blendType),
        m_finishedEvent(finishedEvent)
    {
    }

    //-----------------------------------------------------------------------
    //                 ~ T I n t e r v a l C o n t r o l l e r
    //-----------------------------------------------------------------------
    TIntervalController::~TIntervalController()
    {
    }

    //-----------------------------------------------------------------------
    //                      c o m p u t e D e l t a 
    //-----------------------------------------------------------------------
    float TIntervalController::computeDelta(float t)
    {
        float duration = m_duration;
        if (duration == 0.0) {
            // If duration is 0, the lerp works as a set.  Thus, the delta is
            // always 1.0, the terminating value.
            return 1.0;
        }
        t /= duration;
        t = min_<float>(max_<float>(t, 0.0), 1.0);

        switch (m_blendType) 
        {
        case btEaseIn:
            {
                double t2 = t * t;
                return (float)(((3.0 * t2) - (t2 * t)) * 0.5);
            }
        case btEaseOut:
            {
                double t2 = t * t;
                return (float)(((3.0 * t) - (t2 * t)) * 0.5);
            }
        case btEaseInOut:
            {
                double t2 = t * t;
                return (float)((3.0 * t2) - (2.0 * t * t2));
            }
        default:
            return t;
        }
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TIntervalController::update(float value)
    {
        if(m_finished)
            return;

        m_elapsed += value;

        float d = computeDelta(m_elapsed);

        m_current = m_start + d * (m_stop - m_start);

        m_delegate->Execute(m_current,m_userData);

        if(m_current >= m_stop)
        {
            m_finished = true;
            m_manager->stop(this);
        }
    }
}