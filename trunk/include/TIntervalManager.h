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

#ifndef _TINTERVALMANAGER_H_
#define _TINTERVALMANAGER_H_

namespace Tubras
{
    class TIntervalManager : public TSingleton<Tubras::TIntervalManager>
    {
    public:
        TIntervalManager();
        virtual ~TIntervalManager();

        static TIntervalManager& getSingleton(void);
        static TIntervalManager* getSingletonPtr(void);

        void step();
        int initialize();

        int add_c_interval(TInterval *interval, bool external);
        int find_c_interval(const TString &name) const;

        TInterval *get_c_interval(int index) const;
        void remove_c_interval(int index);

        int interrupt();
        int get_num_intervals() const;
        int get_max_index() const;

        int get_next_event();
        int get_next_removal();

    private:
        void finish_interval(TInterval *interval);
        void remove_index(int index);
        void registerInterval(TInterval* interval);
        void _removeInterval(TInterval* interval);

        enum Flags {
            F_external      = 0x0001,
            F_meta_interval = 0x0002,
        };
        class IntervalDef {
        public:
            TInterval*      _interval;
            int _flags;
            int _next_slot;
        };
        typedef std::vector<IntervalDef> Intervals;
        Intervals _intervals;
        typedef std::map<TString, int> NameIndex;
        NameIndex _name_index;
        typedef std::vector<int> Removed;
        Removed _removed;

        std::vector<TInterval*> m_intervals;

        int _first_slot;
        int _next_event_index;

        friend class TInterval;
    };

}

#endif