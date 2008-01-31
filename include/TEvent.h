//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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
        TEvent(const TString& name);
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
        inline void addStringParameter(const TString& value);
        inline void addWStringParameter(const TStringW& value);
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

    inline void TEvent::addStringParameter(const TString& value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addWStringParameter(const TStringW& value)
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

