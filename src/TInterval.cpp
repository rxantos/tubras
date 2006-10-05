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


    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::Constructor
    //       Access: Public
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    TInterval::TInterval(const string &name, double duration, bool open_ended) : _state(S_initial),
        _curr_t(0.0),
        _name(name),_duration(max(duration, 0.0)),
        _open_ended(open_ended),_dirty(false)
    {
        _auto_pause = false;
        _auto_finish = false;
        _wants_t_callback = false;
        _last_t_callback = -1.0;
        _manager = getApplication()->getIntervalManager();
        _clock_start = 0.0;
        _start_t = 0.0;
        _end_t = _duration;
        _start_t_at_start = true;
        _end_t_at_end = true;
        _play_rate = 1.0;
        _do_loop = false;
        _loop_count = 0;

    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::Destructor
    //       Access: Public, Virtual
    //  Description: 
    ////////////////////////////////////////////////////////////////////
    TInterval::~TInterval() 
    {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::setT
    //       Access: Published
    //  Description: Explicitly sets the time within the interval.
    //               Normally, you would use start() .. finish() to let
    //               the time play normally, but this may be used to set
    //               the time to some particular value.
    ////////////////////////////////////////////////////////////////////
    void TInterval::setT(double t) 
    {
        // There doesn't seem to be any reason to clamp this, and it
        // breaks looping intervals.  The interval code should properly
        // handle t values outside the proper range.
        //t = min(max(t, 0.0), get_duration());

        switch (getState()) 
        {
        case S_initial:
            priv_initialize(t);
            if (isPlaying()) {
                setupResume();
            } else {
                priv_interrupt();
            }
            break;

        case S_started:
            // Support modifying t while the interval is playing.  We assume
            // isPlaying() will be true in this state.
            priv_interrupt();
            priv_step(t);
            setupResume();
            break;

        case S_paused:
            // Support modifying t while the interval is paused.  In this
            // case, we simply step to the new value of t; but this will
            // change the state to S_started, so we must then change it back
            // to S_paused by hand (because we're still paused).
            priv_step(t);
            priv_interrupt();
            break;

        case S_final:
            priv_reverse_initialize(t);
            if (isPlaying()) {
                setupResume();
            } else {
                priv_interrupt();
            }
            break;
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::start
    //       Access: Published
    //  Description: Starts the interval playing by registering it with
    //               the current TIntervalManager.  The interval will
    //               play to the end and stop.
    //
    //               If end_t is less than zero, it indicates the end of
    //               the interval.
    ////////////////////////////////////////////////////////////////////
    void TInterval::start(double start_t, double end_t, double play_rate) 
    {
        setupPlay(start_t, end_t, play_rate, false);
        _manager->add_c_interval(this, false);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::loop
    //       Access: Published
    //  Description: Starts the interval playing by registering it with
    //               the current TIntervalManager.  The interval will
    //               play until it is interrupted with finish() or
    //               pause(), looping back to start_t when it reaches
    //               end_t.
    //
    //               If end_t is less than zero, it indicates the end of
    //               the interval.
    ////////////////////////////////////////////////////////////////////
    void TInterval::loop(double start_t, double end_t, double play_rate) 
    {
        setupPlay(start_t, end_t, play_rate, true);
        _manager->add_c_interval(this, false);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::pause
    //       Access: Published
    //  Description: Stops the interval from playing but leaves it in its
    //               current state.  It may later be resumed from this
    //               point by calling resume().
    ////////////////////////////////////////////////////////////////////
    double TInterval::pause() 
    {
        if (getState() == S_started) 
        {
            priv_interrupt();
        }
        int index = _manager->find_c_interval(this->get_name());
        if (index >= 0) 
        {
            _manager->remove_c_interval(index);
        }
        return getT();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::resume
    //       Access: Published
    //  Description: Restarts the interval from its current point after a
    //               previous call to pause().
    ////////////////////////////////////////////////////////////////////
    void TInterval::resume() 
    {
        setupResume();
        _manager->add_c_interval(this, false);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::resume
    //       Access: Published
    //  Description: Restarts the interval from the indicated point after a
    //               previous call to pause().
    ////////////////////////////////////////////////////////////////////
    void TInterval::resume(double start_t) 
    {
        setT(start_t);
        setupResume();
        _manager->add_c_interval(this, false);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::resumeUntil
    //       Access: Published
    //  Description: Restarts the interval from the current point after a
    //               previous call to pause() (or a previous
    //               play-to-point-and-stop), to play until the indicated
    //               point and then stop.
    ////////////////////////////////////////////////////////////////////
    void TInterval::resumeUntil(double end_t) 
    {
        setupResumeUntil(end_t);
        _manager->add_c_interval(this, false);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::finish
    //       Access: Published
    //  Description: Stops the interval from playing and sets it to its
    //               final state.
    ////////////////////////////////////////////////////////////////////
    void TInterval::finish() 
    {
        switch (getState()) 
        {
        case S_initial:
            priv_instant();
            break;

        case S_final:
            break;

        default:
            priv_finalize();
        }

        int index = _manager->find_c_interval(this->get_name());
        if (index >= 0) 
        {
            _manager->remove_c_interval(index);
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::clearToInitial
    //       Access: Published
    //  Description: Pauses the interval, if it is playing, and resets its
    //               state to its initial state, abandoning any state
    //               changes already in progress in the middle of the
    //               interval.  Calling this is like pausing the interval
    //               and discarding it, creating a new one in its place.
    ////////////////////////////////////////////////////////////////////
    void TInterval::clearToInitial() 
    {
        pause();

        _state = S_initial;
        _curr_t = 0.0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::isPlaying
    //       Access: Published
    //  Description: Returns true if the interval is currently playing,
    //               false otherwise.
    ////////////////////////////////////////////////////////////////////
    bool TInterval::isPlaying() const 
    {
        int index = _manager->find_c_interval(this->get_name());
        return (index >= 0);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::priv_do_event
    //       Access: Published
    //  Description: Calls the appropriate event function indicated by the
    //               EventType.
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_do_event(double t, EventType event) 
    {
        switch (event) 
        {
        case ET_initialize:
            priv_initialize(t);
            return;

        case ET_instant:
            priv_instant();
            return;

        case ET_step:
            priv_step(t);
            return;

        case ET_finalize:
            priv_finalize();
            return;

        case ET_reverse_initialize:
            priv_reverse_initialize(t);
            return;

        case ET_reverse_instant:
            priv_reverse_instant();
            return;

        case ET_reverse_finalize:
            priv_reverse_finalize();
            return;

        case ET_interrupt:
            priv_interrupt();
            return;
        }

    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::priv_initialize
    //       Access: Published, Virtual
    //  Description: This replaces the first call to priv_step(), and indicates
    //               that the interval has just begun.  This may be
    //               overridden by derived classes that need to do some
    //               explicit initialization on the first call.
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_initialize(double t) 
    {
        recompute();
        _state = S_started;
        priv_step(t);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::priv_instant
    //       Access: Published, Virtual
    //  Description: This is called in lieu of priv_initialize() .. priv_step()
    //               .. priv_finalize(), when everything is to happen within
    //               one frame.  The interval should initialize itself,
    //               then leave itself in the final state.
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_instant() 
    {
        recompute();
        _state = S_started;
        priv_step(get_duration());
        _state = S_final;
        intervalDone();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::priv_step
    //       Access: Published, Virtual
    //  Description: Advances the time on the interval.  The time may
    //               either increase (the normal case) or decrease
    //               (e.g. if the interval is being played by a slider).
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_step(double t) 
    {
        _state = S_started;
        _curr_t = t;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::priv_finalize
    //       Access: Published, Virtual
    //  Description: This is called to stop an interval, forcing it to
    //               whatever state it would be after it played all the
    //               way through.  It's generally invoked by
    //               set_final_t().
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_finalize() 
    {
        double duration = get_duration();
        priv_step(duration);
        _state = S_final;
        intervalDone();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::reverse_initialize
    //       Access: Published, Virtual
    //  Description: Similar to priv_initialize(), but this is called when the
    //               interval is being played backwards; it indicates that
    //               the interval should start at the finishing state and
    //               undo any intervening intervals.
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_reverse_initialize(double t) 
    {
        recompute();
        _state = S_started;
        priv_step(t);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::reverse_instant
    //       Access: Published, Virtual
    //  Description: This is called in lieu of priv_reverse_initialize()
    //               .. priv_step() .. priv_reverse_finalize(), when everything is
    //               to happen within one frame.  The interval should
    //               initialize itself, then leave itself in the initial
    //               state.
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_reverse_instant() 
    {
        recompute();
        _state = S_started;
        priv_step(0.0);
        _state = S_initial;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::reverse_finalize
    //       Access: Published, Virtual
    //  Description: Called generally following a priv_reverse_initialize(),
    //               this indicates the interval should set itself to the
    //               initial state.
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_reverse_finalize() 
    {
        priv_step(0.0);
        _state = S_initial;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::priv_interrupt
    //       Access: Published, Virtual
    //  Description: This is called while the interval is playing to
    //               indicate that it is about to be interrupted; that is,
    //               priv_step() will not be called for a length of time.  But
    //               the interval should remain in its current state in
    //               anticipation of being eventually restarted when the
    //               calls to priv_step() eventually resume.
    //
    //               The purpose of this function is to allow self-running
    //               intervals like sound intervals to stop the actual
    //               sound playback during the pause.
    ////////////////////////////////////////////////////////////////////
    void TInterval::priv_interrupt() 
    {
        _state = S_paused;
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::setupPlay
    //       Access: Published
    //  Description: Called to prepare the interval for automatic timed
    //               playback, e.g. via a Python task.  The interval will
    //               be played from start_t to end_t, at a time factor
    //               specified by play_rate.  start_t must always be less
    //               than end_t (except for the exception for end_t == -1,
    //               below), but if play_rate is negative the interval
    //               will be played backwards.
    //
    //               Specify end_t of -1 to play the entire interval from
    //               start_t.
    //
    //               Call stepPlay() repeatedly to execute the interval.
    ////////////////////////////////////////////////////////////////////
    void TInterval::setupPlay(double start_t, double end_t, double play_rate, bool do_loop) 
    {

        double duration = get_duration();

        if (start_t <= 0.0) 
        {
            _start_t = 0.0;
            _start_t_at_start = true;
        } 
        else if (start_t > duration) 
        {
            _start_t = duration;
            _start_t_at_start = false;
        } 
        else 
        {
            _start_t = start_t;
            _start_t_at_start = false;
        }

        if (end_t < 0.0 || end_t >= duration) 
        {
            _end_t = duration;
            _end_t_at_end = true;
        } 
        else 
        {
            _end_t = end_t;
            _end_t_at_end = false;
        }

        _clock_start = getApplication()->getGlobalClock()->getMilliseconds()  / 1000.0f;
        _play_rate = play_rate;
        _do_loop = do_loop;
        _loop_count = 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::setupResume
    //       Access: Published
    //  Description: Called to prepare the interval for restarting at the
    //               current point within the interval after an
    //               interruption.
    ////////////////////////////////////////////////////////////////////
    void TInterval::setupResume() 
    {
        double now = getApplication()->getGlobalClock()->getMilliseconds()   / 1000.0f;
        if (_play_rate > 0.0) 
        {
            _clock_start = now - ((getT() - _start_t) / _play_rate);

        }
        else if (_play_rate < 0.0) 
        {
            _clock_start = now - ((getT() - _end_t) / _play_rate);
        }
        _loop_count = 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::setupResumeUntil
    //       Access: Published
    //  Description: Called to prepare the interval for restarting from
    //               the current point after a previous call to pause()
    //               (or a previous play-to-point-and-stop), to play until
    //               the indicated point and then stop.
    ////////////////////////////////////////////////////////////////////
    void TInterval::setupResumeUntil(double end_t) 
    {
        double duration = get_duration();

        if (end_t < 0.0 || end_t >= duration) 
        {
            _end_t = duration;
            _end_t_at_end = true;
        } 
        else 
        {
            _end_t = end_t;
            _end_t_at_end = false;
        }

        setupResume();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::stepPlay
    //       Access: Published
    //  Description: Should be called once per frame to execute the
    //               automatic timed playback begun with setupPlay().
    //
    //               Returns true if the interval should continue, false
    //               if it is done and should stop.
    ////////////////////////////////////////////////////////////////////
    bool TInterval::stepPlay() 
    {
        double now = getApplication()->getGlobalClock()->getMilliseconds() / 1000.0f;

        if (_play_rate >= 0.0) 
        {
            double t = (now - _clock_start) * _play_rate + _start_t;

            if (_end_t_at_end) 
            {
                _end_t = get_duration();
            }

            if (t < _end_t) 
            {
                // In the middle of the interval, not a problem.
                if (isStopped()) 
                {
                    priv_initialize(t);
                } 
                else 
                {
                    priv_step(t);
                }

            } 
            else 
            {
                // Past the ending point; time to finalize.
                if (_end_t_at_end) 
                {
                    // Only finalize if the playback cycle includes the whole
                    // interval.
                    if (isStopped()) 
                    {
                        if (get_open_ended() || _loop_count != 0) 
                        {
                            priv_instant();
                        }
                    } 
                    else 
                    {
                        priv_finalize();
                    }
                } 
                else 
                {
                    if (isStopped()) 
                    {
                        priv_initialize(_end_t);
                    } 
                    else 
                    {
                        priv_step(_end_t);
                    }
                }

                // Advance the clock for the next loop cycle.  We might have to
                // advance multiple times if we skipped several cycles in the past
                // frame.

                if (_end_t == _start_t) 
                {
                    // If the interval has no length, we loop exactly once each
                    // time.
                    _loop_count++;

                } 
                else 
                {
                    // Otherwise, figure out how many loops we need to skip.
                    double time_per_loop = (_end_t - _start_t) / _play_rate;
                    double num_loops = floor((now - _clock_start) / time_per_loop);
                    _loop_count += (int)num_loops;
                    _clock_start += num_loops * time_per_loop;
                }
            }

        } else {
            // Playing backwards.
            double t = (now - _clock_start) * _play_rate + _end_t;

            if (t >= _start_t) 
            {
                // In the middle of the interval, not a problem.
                if (isStopped()) 
                {
                    priv_reverse_initialize(t);
                } 
                else 
                {
                    priv_step(t);
                }

            } 
            else 
            {
                // Past the ending point; time to finalize.
                if (_start_t_at_start) 
                {
                    // Only finalize if the playback cycle includes the whole
                    // interval.
                    if (isStopped()) 
                    {
                        if (get_open_ended() || _loop_count != 0) 
                        {
                            priv_reverse_instant();
                        }
                    } 
                    else 
                    {
                        priv_reverse_finalize();
                    }
                } 
                else 
                {
                    if (isStopped()) 
                    {
                        priv_reverse_initialize(_start_t);
                    } 
                    else 
                    {
                        priv_step(_start_t);
                    }
                }

                // Advance the clock for the next loop cycle.  We might have to
                // advance multiple times if we skipped several cycles in the past
                // frame.

                if (_end_t == _start_t) 
                {
                    // If the interval has no length, we loop exactly once each
                    // time.
                    _loop_count++;

                } 
                else 
                {
                    // Otherwise, figure out how many loops we need to skip.
                    double time_per_loop = (_end_t - _start_t) / -_play_rate;
                    double num_loops = floor((now - _clock_start) / time_per_loop);
                    _loop_count += (int)num_loops;
                    _clock_start += num_loops * time_per_loop;
                }
            }
        }

        bool should_continue = (_loop_count == 0 || _do_loop);

        if (!should_continue && _state == S_started) 
        {
            priv_interrupt();
        }

        return should_continue;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::markDirty
    //       Access: Public
    //  Description: Called by a derived class to indicate the interval has
    //               been changed internally and must be recomputed before
    //               its duration may be returned.
    ////////////////////////////////////////////////////////////////////
    void TInterval::markDirty() 
    {
        if (!_dirty) 
        {
            _dirty = true;
            Parents::iterator pi;
            for (pi = _parents.begin(); pi != _parents.end(); ++pi) 
            {
                (*pi)->markDirty();
            }
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::intervalDone
    //       Access: Protected
    //  Description: Called internally whenever the interval reaches its
    //               final state.
    ////////////////////////////////////////////////////////////////////
    void TInterval::intervalDone() 
    {
        if (!_done_event.empty()) 
        {
            TSEvent event;
            event.bind(new TEvent(_done_event));
            getApplication()->sendEvent(event);
        }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::doRecompute
    //       Access: Protected, Virtual
    //  Description: Does whatever processing is necessary to recompute
    //               the interval after a call to markDirty() has
    //               indicated a recomputation is necessary.
    ////////////////////////////////////////////////////////////////////
    void TInterval::doRecompute() 
    {
        _dirty = false;
    }

}