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
    class TEvent : public IReferenceCounted
    {
    protected:
        typedef array<TEventParameter*> TParameterList;
        TParameterList      m_parameters;

        TString             m_name;
        u32                 m_id;
        void*               m_userData;
    public:

        TEvent() : m_name(""), m_id(0), m_userData(0) {}
        TEvent(TString name);
        inline virtual ~TEvent();

        void setName(const TString &name);
        inline const TString getName() const;
        inline u32 getID() {return m_id;};
        inline void setID(u32 id) {m_id = id;};

        inline void setUserData(void* userData);
        inline void* getUserData();
        inline void resetUserData();

        inline void addParameter(TEventParameter* param);
        inline void addIntParameter(int value);
        inline void addDoubleParameter(double value);
        inline void addStringParameter(TString value);
        inline void addWStringParameter(TStringW value);
        inline void addPointerParameter(void* value);

        int getNumParameters() const {return (int)m_parameters.size();};
        TEventParameter* getParameter(int n);

    };

    inline TEvent::~TEvent()
    {
        for(u32 i=0;i<m_parameters.size();i++)
            m_parameters[i]->drop();
        m_parameters.clear();
    }

    inline const TString TEvent::getName() const
    {
        return m_name;
    }

    inline void TEvent::addParameter(TEventParameter* param)
    {
        m_parameters.push_back(param);
    }

    inline void TEvent::addIntParameter(int value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addDoubleParameter(double value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addStringParameter(TString value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addWStringParameter(TStringW value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addPointerParameter(void* value)
    {
        m_parameters.push_back(new TEventParameter(value));
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


#define EVENT_DELEGATE(member) new Tubras::TEventDelegate(this,(Tubras::TEventDelegateFunction)&member)

}

#endif