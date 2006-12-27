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

#ifndef _TEVENT_H_
#define _TEVENT_H_

namespace Tubras
{


    /** TEvent class. 
    @remarks
    This class should be used as a base class for user defined
    classes that want to receive event notifications.
    */
    class TEvent
    {
    protected:
        typedef std::vector<TSEventParameter> TParameterList;
        TParameterList      m_parameters;

        string              m_name;
        size_t              m_id;
        void*               m_userData;
    public:

        TEvent(string name);
        inline virtual ~TEvent();

        inline void setName(const string &name);
        inline const string getName() const;
        inline size_t getID() {return m_id;};
        inline void setID(size_t id) {m_id = id;};

        inline void setUserData(void* userData);
        inline void* getUserData();
        inline void resetUserData();

        inline void addParameter(const TSEventParameter &param);
        inline void addIntParameter(int value);
        inline void addDoubleParameter(double value);
        inline void addStringParameter(string value);
        inline void addWStringParameter(string value);
        inline void addPointerParameter(void* value);

        int getNumParameters() const {return (int)m_parameters.size();};
        TSEventParameter getParameter(int n) const;

    };

    inline TEvent::~TEvent()
    {
        m_parameters.clear();
    }

    inline void TEvent::setName(const string &name)
    {
        m_name = name;
    }

    inline const string TEvent::getName() const
    {
        return m_name;
    }

    inline void TEvent::addParameter(const TSEventParameter &param)
    {
        m_parameters.push_back(param);
    }

    inline void TEvent::addIntParameter(int value)
    {
        TSEventParameter  param;
        param.bind(new TEventParameter(value));
        m_parameters.push_back(param);
    }

    inline void TEvent::addDoubleParameter(double value)
    {
        TSEventParameter  param;
        param.bind(new TEventParameter(value));
        m_parameters.push_back(param);
    }

    inline void TEvent::addStringParameter(string value)
    {
        TSEventParameter  param;
        param.bind(new TEventParameter(value));
        m_parameters.push_back(param);
    }

    inline void TEvent::addWStringParameter(string value)
    {
        TSEventParameter  param;
        param.bind(new TEventParameter(value));
        m_parameters.push_back(param);
    }

    inline void TEvent::addPointerParameter(void* value)
    {
        TSEventParameter  param;
        param.bind(new TEventParameter(value));
        m_parameters.push_back(param);
    }

    inline void TEvent::setUserData(void* userData)
    {
        m_userData = userData;
    }

    inline void* TEvent::getUserData()
    {
        return m_userData;
    }

    inline void TEvent::resetUserData()
    {
        m_userData = NULL;
    }



    typedef Ogre::SharedPtr<TEvent> TSEvent;

#define EVENT_DELEGATE(member) new Tubras::TEventDelegate(this,(Tubras::TEventDelegateFunction)&member)

}

#endif