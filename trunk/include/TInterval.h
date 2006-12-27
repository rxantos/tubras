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

#ifndef _TINTERVAL_H_
#define _TINTERVAL_H_

namespace Tubras
{
    class TIntervalManager;

    class TInterval
    {

    public:
        TInterval(const string &name, double duration, bool open_ended);
        virtual ~TInterval();

    public:
        inline const string &get_name() const;
        inline double get_duration() const;
        inline bool get_open_ended() const;

        enum EventType {
            ET_initialize,
            ET_instant,
            ET_step,
            ET_finalize,
            ET_reverse_initialize,
            ET_reverse_instant,
            ET_reverse_finalize,
            ET_interrupt
        };

        enum State {
            S_initial,
            S_started,
            S_paused,
            S_final
        };

        inline State getState() const;
        inline bool isStopped() const;

        inline void setDoneEvent(const string &event);
        inline const string &getDoneEvent() const;

        void setT(double t);
        inline double getT() const;

        inline void setAutoPause(bool auto_pause);
        inline bool getAutoPause() const;
        inline void setAutoFinish(bool auto_finish);
        inline bool getAutoFinish() const;

        inline void setWantsTCallback(bool wants_t_callback);
        inline bool getWantsTCallback() const;

        inline void setManager(TIntervalManager *manager);
        inline TIntervalManager *getManager() const;

        void start(double start_t = 0.0, double end_t = -1.0, double play_rate = 1.0);
        void loop(double start_t = 0.0, double end_t = -1.0, double play_rate = 1.0);
        double pause();
        void resume();
        void resume(double start_t);
        void resumeUntil(double end_t);
        void finish();
        void clearToInitial();
        bool isPlaying() const;

        // These functions control the actual playback of the interval.
        // Don't call them directly; they're intended to be called from a
        // supervising object, e.g. the Python start() .. finish()
        // interface.

        // These cannot be declared private because they must be accessible
        // to Python, but the method names are prefixed with priv_ to remind
        // you that you probably don't want to be using them directly.
        void priv_do_event(double t, EventType event);
        virtual void priv_initialize(double t);
        virtual void priv_instant();
        virtual void priv_step(double t);
        virtual void priv_finalize();
        virtual void priv_reverse_initialize(double t);
        virtual void priv_reverse_instant();
        virtual void priv_reverse_finalize();
        virtual void priv_interrupt();

        void setupPlay(double start_time, double end_time, double play_rate,
            bool do_loop);
        void setupResume();
        void setupResumeUntil(double end_t);
        bool stepPlay();

    public:
        void markDirty();
        inline bool checkTCallback();

    protected:
        void intervalDone();

        inline void recompute() const;
        virtual void doRecompute();

        State _state;
        double _curr_t;
        string _name;
        string _done_event;
        double _duration;

        bool _auto_pause;
        bool _auto_finish;
        bool _wants_t_callback;
        double _last_t_callback;
        TIntervalManager *_manager;

        // For setupPlay() and stepPlay().
        double _clock_start;
        double _start_t;
        double _end_t;
        bool _end_t_at_end;
        bool _start_t_at_start;
        double _play_rate;
        bool _do_loop;
        int _loop_count;

    private:
        bool _open_ended;
        bool _dirty;

        // We keep a record of the "parent" intervals (that is, any
        // CMetaInterval objects that keep a pointer to this one) strictly
        // so we can mark all of our parents dirty when this interval gets
        // dirty. NOTE - MetaInterval not implemented in tubras for now.
        typedef std::vector<TInterval *> Parents;
        Parents _parents;
    };

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::get_name
    //       Access: Published
    //  Description: Returns the interval's name.
    ////////////////////////////////////////////////////////////////////
    inline const string &TInterval::get_name() const 
    {
        return _name;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::get_duration
    //       Access: Published
    //  Description: Returns the duration of the interval in seconds.
    ////////////////////////////////////////////////////////////////////
    inline double TInterval::get_duration() const 
    {
        recompute();
        return _duration;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::get_open_ended
    //       Access: Published
    //  Description: Returns the state of the "open_ended" flag.  This is
    //               primarily intended for instantaneous intervals like
    //               FunctionIntervals; it indicates true if the interval
    //               has some lasting effect that should be applied even
    //               if the interval doesn't get started until after its
    //               finish time, or false if the interval is a transitive
    //               thing that doesn't need to be called late.
    ////////////////////////////////////////////////////////////////////
    inline bool TInterval::get_open_ended() const 
    {
        return _open_ended;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::get_state
    //       Access: Published
    //  Description: Indicates the state the interval believes it is in:
    //               whether it has been started, is currently in the
    //               middle, or has been finalized.
    ////////////////////////////////////////////////////////////////////
    inline TInterval::State TInterval::getState() const 
    {
        return _state;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::is_stopped
    //       Access: Published
    //  Description: Returns true if the interval is in either its initial
    //               or final states (but not in a running or paused
    //               state).
    ////////////////////////////////////////////////////////////////////
    inline bool TInterval::isStopped() const 
    {
        return (_state == S_initial || _state == S_final);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::set_done_event
    //       Access: Published
    //  Description: Sets the event that is generated whenever the
    //               interval reaches its final state, whether it is
    //               explicitly finished or whether it gets there on its
    //               own.
    ////////////////////////////////////////////////////////////////////
    inline void TInterval::setDoneEvent(const string &event) 
    {
        _done_event = event;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::get_done_event
    //       Access: Published
    //  Description: Returns the event that is generated whenever the
    //               interval reaches its final state, whether it is
    //               explicitly finished or whether it gets there on its
    //               own.
    ////////////////////////////////////////////////////////////////////
    inline const string &TInterval::getDoneEvent() const 
    {
        return _done_event;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::getT
    //       Access: Published
    //  Description: Returns the current time of the interval: the last
    //               value of t passed to priv_initialize(), priv_step(), or
    //               priv_finalize().
    ////////////////////////////////////////////////////////////////////
    inline double TInterval::getT() const 
    {
        return _curr_t;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::set_AutoPause
    //       Access: Published
    //  Description: Changes the state of the 'auto_pause' flag.  If
    //               this is true, the interval may be arbitrarily
    //               interrupted when the system needs to reset due to
    //               some external event by calling
    //               TIntervalManager::interrupt().  If this
    //               is false (the default), the interval must always be
    //               explicitly finished or paused.
    ////////////////////////////////////////////////////////////////////
    inline void TInterval::setAutoPause(bool auto_pause) 
    {
        _auto_pause = auto_pause;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::getAutoPause
    //       Access: Published
    //  Description: Returns the state of the 'auto_pause' flag.  See
    //               set_AutoPause().
    ////////////////////////////////////////////////////////////////////
    inline bool TInterval::getAutoPause() const 
    {
        return _auto_pause;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::setAutoFinish
    //       Access: Published
    //  Description: Changes the state of the 'auto_finish' flag.  If
    //               this is true, the interval may be arbitrarily
    //               finished when the system needs to reset due to
    //               some external event by calling
    //               TIntervalManager::interrupt().  If this
    //               is false (the default), the interval must always be
    //               explicitly finished or paused.
    ////////////////////////////////////////////////////////////////////
    inline void TInterval::setAutoFinish(bool auto_finish) 
    {
        _auto_finish = auto_finish;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::getAutoFinish
    //       Access: Published
    //  Description: Returns the state of the 'auto_finish' flag.  See
    //               setAutoFinish().
    ////////////////////////////////////////////////////////////////////
    inline bool TInterval::getAutoFinish() const 
    {
        return _auto_finish;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::setWantsTCallback
    //       Access: Published
    //  Description: Changes the state of the 'wants_t_callback' flag.  If
    //               this is true, the interval will be returned by
    //               TIntervalManager::get_event() each time the
    //               interval's time value has been changed, regardless of
    //               whether it has any external events.
    ////////////////////////////////////////////////////////////////////
    inline void TInterval::setWantsTCallback(bool wants_t_callback) 
    {
        _wants_t_callback = wants_t_callback;
        _last_t_callback = -1.0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::getWantsTCallback
    //       Access: Published
    //  Description: Returns the state of the 'wants_t_callback' flag.
    //               See setWantsTCallback().
    ////////////////////////////////////////////////////////////////////
    inline bool TInterval::getWantsTCallback() const 
    {
        return _wants_t_callback;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::setManager
    //       Access: Published
    //  Description: Indicates the TIntervalManager object which will be
    //               responsible for playing this interval.  This defaults
    //               to the global TIntervalManager; you should need to
    //               change this only if you have special requirements for
    //               playing this interval.
    ////////////////////////////////////////////////////////////////////
    inline void TInterval::setManager(TIntervalManager *manager) 
    {
        _manager = manager;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::getManager
    //       Access: Published
    //  Description: Returns the TIntervalManager object which will be
    //               responsible for playing this interval.  Note that
    //               this can only return a C++ object; if the particular
    //               TIntervalManager object has been extended in the
    //               scripting language, this will return the encapsulated
    //               C++ object, not the full extended object.
    ////////////////////////////////////////////////////////////////////
    inline TIntervalManager *TInterval::getManager() const 
    {
        return _manager;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::checkTCallback
    //       Access: Public
    //  Description: Returns true if the wants_t_callback() flag is true
    //               and the interval's t value has changed since the last
    //               call to checkTCallback(), false otherwise.
    ////////////////////////////////////////////////////////////////////
    inline bool TInterval::checkTCallback() 
    {
        if (getWantsTCallback() && getT() != _last_t_callback) {
            _last_t_callback = getT();
            return true;
        }
        return false;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TInterval::recompute
    //       Access: Protected
    //  Description: Calls doRecompute() if the dirty flag has been set.
    ////////////////////////////////////////////////////////////////////
    inline void TInterval::recompute() const 
    {
        if (_dirty) {
            ((TInterval *)this)->doRecompute();
        }
    }


}
#endif