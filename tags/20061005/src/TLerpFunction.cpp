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

    TLerpFunction::TLerpFunction(const string &name, double start, double end,
        double duration, TFuncIntDelegate* func,
        void* userData, BlendType blendType) : TLerpInterval(name,duration,blendType)
    {
        m_func = func;
        m_userData = userData;
        m_start = start;
        m_end = end;
    }

    TLerpFunction::~TLerpFunction()
    {
        if(m_func)
            delete m_func;
    }

    void TLerpFunction::start(double start, double end)
    {
        if((start != 0.0f) || (end != 0.0f))
        {
            m_start = start;
            m_end = end;
        }
        TLerpInterval::start();
    }

    void TLerpFunction::priv_step(double t)
    {
        double value = 0;
        double delta = t / _duration;
        if(m_end > m_start)
        {
            double diff = m_end - m_start;
            value = m_start + (diff * delta);
        }
        else
        {
            double diff = m_start - m_end;
            value = m_start - (diff * delta);
        }

        (*m_func)(value,m_userData);
    }


}