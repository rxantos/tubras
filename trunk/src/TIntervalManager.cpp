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
    TIntervalManager::TIntervalManager()
    {
        _first_slot = 0;
        _next_event_index = 0;
    }

    TIntervalManager::~TIntervalManager()
    {
        size_t size = _name_index.size();

        if(_name_index.size() > 0)
            _name_index.empty();
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TIntervalManager* TSingleton<TIntervalManager>::ms_Singleton = 0;

    TIntervalManager* TIntervalManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TIntervalManager& TIntervalManager::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TIntervalManager::initialize()
    {
        return 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::add_c_interval
    //       Access: Published
    //  Description: Adds the interval to the manager, and returns a
    //               unique index for the interval.  This index will be
    //               unique among all the currently added intervals, but
    //               not unique across all intervals ever added to the
    //               manager.  The maximum index value will never exceed
    //               the maximum number of intervals added at any given
    //               time.
    //
    //               If the external flag is true, the interval is
    //               understood to also be stored in the scripting
    //               language data structures.  In this case, it will be
    //               available for information returned by
    //               get_next_event() and get_next_removal().  If external
    //               is false, the interval's index will never be returned
    //               by these two functions.
    ////////////////////////////////////////////////////////////////////
    int TIntervalManager::
        add_c_interval(TInterval *interval, bool external) {

            external = true;
            // First, check the name index.  If we already have an interval by
            // this name, it gets finished and removed.
            NameIndex::iterator ni = _name_index.find(interval->get_name());
            if (ni != _name_index.end()) {
                int old_index = (*ni).second;
                TInterval *old_interval = _intervals[old_index]._interval;
                if (old_interval == interval) {
                    // No, it's the same interval that was already here.  In this
                    // case, don't finish the interval; just return it.
                    return old_index;
                }
                finish_interval(old_interval);
                remove_index(old_index);
                _name_index.erase(ni);
            }

            int slot;

            if (_first_slot >= (int)_intervals.size()) {
                // All the slots are filled; make a new slot.
                slot = (int)_intervals.size();
                _intervals.push_back(IntervalDef());
                _first_slot = (int)_intervals.size();

            } else {
                // Some slot is available; use it.
                slot = _first_slot;
                _first_slot = _intervals[slot]._next_slot;
            }

            IntervalDef &def = _intervals[slot];
            def._interval = interval;
            def._flags = 0;
            if (external) {
                def._flags |= F_external;
            }
            def._next_slot = -1;

            _name_index[interval->get_name()] = slot;
            return slot;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::find_c_interval
    //       Access: Published
    //  Description: Returns the index associated with the named interval,
    //               if there is such an interval, or -1 if there is not.
    ////////////////////////////////////////////////////////////////////
    int TIntervalManager::
        find_c_interval(const string &name) const {

            NameIndex::const_iterator ni = _name_index.find(name);
            if (ni != _name_index.end()) {
                return (*ni).second;
            }
            return -1;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::get_c_interval
    //       Access: Published
    //  Description: Returns the interval associated with the given index.
    ////////////////////////////////////////////////////////////////////
    TInterval *TIntervalManager::
        get_c_interval(int index) const {

            return _intervals[index]._interval;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::remove_c_interval
    //       Access: Published
    //  Description: Removes the indicated interval from the queue
    //               immediately.  It will not be returned from
    //               get_next_removal(), and none of its pending events,
    //               if any, will be returned by get_next_event().
    ////////////////////////////////////////////////////////////////////
    void TIntervalManager::
        remove_c_interval(int index) {

            IntervalDef &def = _intervals[index];

            NameIndex::iterator ni = _name_index.find(def._interval->get_name());
            _name_index.erase(ni);

            def._interval = (TInterval *)NULL;
            def._next_slot = _first_slot;
            _first_slot = index;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::interrupt
    //       Access: Published
    //  Description: Pauses or finishes (removes from the active queue)
    //               all intervals tagged with auto_pause or auto_finish
    //               set to true.  These are intervals that someone fired
    //               up but won't necessarily expect to clean up; they can
    //               be interrupted at will when necessary.
    //
    //               Returns the number of intervals affected.
    ////////////////////////////////////////////////////////////////////
    int TIntervalManager::
        interrupt() {

            int num_paused = 0;

            NameIndex::iterator ni;
            ni = _name_index.begin();
            while (ni != _name_index.end()) {
                int index = (*ni).second;
                const IntervalDef &def = _intervals[index];
                if (def._interval->getAutoPause() || def._interval->getAutoFinish()) {
                    // This interval may be interrupted.
                    if (def._interval->getAutoPause()) {
                        // It may be interrupted simply by pausing it.
                        if (def._interval->getState() == TInterval::S_started) {
                            def._interval->priv_interrupt();
                        }

                    } else {
                        // It should be interrupted by finishing it.
                        switch (def._interval->getState()) 
                        {
                        case TInterval::S_initial:
                            def._interval->priv_instant();
                            break;

                        case TInterval::S_final:
                            break;

                        default:
                            def._interval->priv_finalize();
                        }
                    }

                    // Now carefully remove it from the active list.
                    NameIndex::iterator prev;
                    prev = ni;
                    ++ni;
                    _name_index.erase(prev);
                    remove_index(index);
                    num_paused++;

                } else {
                    // The interval should remain on the active list.
                    ++ni;
                }
            }

            return num_paused;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::get_num_intervals
    //       Access: Published
    //  Description: Returns the number of currently active intervals.
    ////////////////////////////////////////////////////////////////////
    int TIntervalManager::
        get_num_intervals() const {

            return (int) _name_index.size();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::get_max_index
    //       Access: Published
    //  Description: Returns one more than the largest interval index
    //               number in the manager.  If you walk through all the
    //               values between (0, get_max_index()] and call
    //               get_c_interval() on each number, you will retrieve
    //               all of the managed intervals (and possibly a number
    //               of NULL pointers as well).
    ////////////////////////////////////////////////////////////////////
    int TIntervalManager::
        get_max_index() const {

            return (int) _intervals.size();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::step
    //       Access: Published
    //  Description: This should be called every frame to do the
    //               processing for all the active intervals.  It will
    //               call step_play() for each interval that has been
    //               added and that has not yet been removed.
    //
    //               After each call to step(), the scripting language
    //               should call get_next_event() and get_next_removal()
    //               repeatedly to process all the high-level
    //               (e.g. Python-interval-based) events and to manage the
    //               high-level list of intervals.
    ////////////////////////////////////////////////////////////////////
    void TIntervalManager::
        step() {

            NameIndex::iterator ni;
            ni = _name_index.begin();
            while (ni != _name_index.end()) {
                int index = (*ni).second;
                const IntervalDef &def = _intervals[index];
                if (!def._interval->stepPlay()) {
                    // This interval is finished and wants to be removed from the
                    // active list.
                    NameIndex::iterator prev;
                    prev = ni;
                    ++ni;
                    _name_index.erase(prev);
                    remove_index(index);
                    break;

                } else {
                    // The interval can remain on the active list.
                    ++ni;
                }
            }
            while(get_next_removal() >= 0);

            _next_event_index = 0;
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::get_next_removal
    //       Access: Published
    //  Description: This should be called by the scripting language after
    //               each call to step().  It returns the index number of
    //               an interval that was recently removed, or -1 if no
    //               intervals were removed.
    //
    //               If this returns something other than -1, the
    //               scripting language should clean up its own data
    //               structures accordingly, and then call
    //               get_next_removal() again.
    ////////////////////////////////////////////////////////////////////
    int TIntervalManager::
        get_next_removal() {

            if (!_removed.empty()) {
                int index = _removed.back();
                _removed.pop_back();

                IntervalDef &def = _intervals[index];
                def._interval = (TInterval *)NULL;
                def._next_slot = _first_slot;
                _first_slot = index;
                return index;
            }

            return -1;
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::finish_interval
    //       Access: Private
    //  Description: Explicitly finishes the indicated interval in
    //               preparation for moving it to the removed queue.
    ////////////////////////////////////////////////////////////////////
    void TIntervalManager::
        finish_interval(TInterval *interval) {
            switch (interval->getState()) 
            {
            case TInterval::S_initial:
                interval->priv_instant();
                break;

            case TInterval::S_final:
                break;

            default:
                interval->priv_finalize();
            }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TIntervalManager::remove_index
    //       Access: Private
    //  Description: Removes the indicated index number from the active
    //               list, either by moving it to the removed queue if it
    //               is flagged external, or by simply making the slot
    //               available again if it is not.  Assumes the lock is
    //               already held.
    ////////////////////////////////////////////////////////////////////
    void TIntervalManager::
        remove_index(int index) {
            IntervalDef &def = _intervals[index];
            if ((def._flags & F_external) != 0) {
                _removed.push_back(index);
            } else {
                def._interval = (TInterval *)NULL;
                def._next_slot = _first_slot;
                _first_slot = index;
            }    
    }

}