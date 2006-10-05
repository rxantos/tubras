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

#ifndef _TEVENTPARAMETER_H_
#define _TEVENTPARAMETER_H_

namespace Tubras
{


    /** TEventParameter class. 
    @remarks
    This class should be used as a base class for user defined
    classes that want to receive event notifications.
    */
    enum TParamType 
    {
        PT_empty,
        PT_int,
        PT_double,
        PT_string,
        PT_wstring,
        PT_pointer
    };
    class TEventParameter
    {
    public:
    protected:
        TParamType    m_type;
        int           m_intValue;
        double        m_doubleValue;
        string        m_stringValue;
        wstring       m_wstringValue;
        void*         m_pointerValue;


    public:


        inline TEventParameter();
        inline virtual ~TEventParameter();

        inline TEventParameter(int value);
        inline TEventParameter(double value);
        inline TEventParameter(const string value);
        inline TEventParameter(const wstring value);
        inline TEventParameter(const void *ptr);

        inline bool isEmpty() const;

        inline bool isInt() const;
        inline int getIntValue() const;

        inline bool isDouble() const;
        inline double getDoubleValue() const;

        inline bool isString() const;
        inline string getStringValue() const;

        inline bool isWString() const;
        inline wstring getWStringValue() const;

        inline bool isPointer() const;
        inline void* getPointerValue() const;



    };

    inline TEventParameter::TEventParameter() 
    {
        m_type = PT_empty;
    }

    inline TEventParameter::~TEventParameter() 
    {
    }

    inline TEventParameter::TEventParameter(int value)
    {
        m_type = PT_int;
        m_intValue = value;
    }

    inline TEventParameter::TEventParameter(double value)
    {
        m_type = PT_double;
        m_doubleValue = value;
    }

    inline TEventParameter::TEventParameter(const string value)
    {
        m_type = PT_string;
        m_stringValue = value;
    }

    inline TEventParameter::TEventParameter(const wstring value)
    {
        m_type = PT_wstring;
        m_wstringValue = value;
    }

    inline TEventParameter::TEventParameter(const void* value)
    {
        m_type = PT_pointer;
        m_pointerValue = (void *)value;
    }


    inline bool TEventParameter::isEmpty() const 
    {
        return (m_type == PT_empty);
    }

    inline bool TEventParameter::isInt() const 
    {
        return (m_type == PT_int);
    }

    inline int TEventParameter::getIntValue() const 
    {
        return m_intValue;
    }
    inline bool TEventParameter::isDouble() const 
    {
        return (m_type == PT_double);
    }

    inline double TEventParameter::getDoubleValue() const 
    {
        return m_doubleValue;
    }

    inline bool TEventParameter::isString() const 
    {
        return (m_type == PT_string);
    }

    inline string TEventParameter::getStringValue() const 
    {
        return m_stringValue;
    }

    inline bool TEventParameter::isWString() const 
    {
        return (m_type == PT_wstring);
    }

    inline wstring TEventParameter::getWStringValue() const 
    {
        return m_wstringValue;
    }

    inline bool TEventParameter::isPointer() const 
    {
        return (m_type == PT_pointer);
    }

    inline void* TEventParameter::getPointerValue() const 
    {
        return m_pointerValue;
    }



    typedef Ogre::SharedPtr<TEventParameter> TSEventParameter;

}
#endif