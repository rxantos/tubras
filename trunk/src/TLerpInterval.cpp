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
    TLerpInterval::TLerpInterval(const string &name, double duration, BlendType blendType) : TInterval(
        name,duration,true)
    {
    }

    TLerpInterval::~TLerpInterval()
    {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: CLerpInterval::compute_delta
    //       Access: Protected
    //  Description: Given a t value in the range [0, get_duration()],
    //               returns the corresponding delta value clamped to the
    //               range [0, 1], after scaling by duration and applying
    //               the blend type.
    ////////////////////////////////////////////////////////////////////
    double TLerpInterval::computeDelta(double t) const {
        double duration = get_duration();
        if (duration == 0.0) {
            // If duration is 0, the lerp works as a set.  Thus, the delta is
            // always 1.0, the terminating value.
            return 1.0;
        }
        t /= duration;
        t = min(max(t, 0.0), 1.0);

        switch (m_blendType) 
        {
        case BT_ease_in:
            {
                double t2 = t * t;
                return ((3.0 * t2) - (t2 * t)) * 0.5;
            }

        case BT_ease_out:
            {
                double t2 = t * t;
                return ((3.0 * t) - (t2 * t)) * 0.5;
            }

        case BT_ease_in_out:
            {
                double t2 = t * t;
                return (3.0 * t2) - (2.0 * t * t2);
            }

        default:
            return t;
        }


    }
}