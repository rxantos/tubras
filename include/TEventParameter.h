//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
    class TEventParameter : public IReferenceCounted
    {
    public:
    protected:
        TParamType    m_type;
        int           m_intValue;
        double        m_doubleValue;
        TString       m_stringValue;
        TStringW      m_wstringValue;
        void*         m_pointerValue;


    public:


        inline TEventParameter();
        inline virtual ~TEventParameter();

        inline TEventParameter(int value);
        inline TEventParameter(double value);
        inline TEventParameter(const TString value);
        inline TEventParameter(const TStringW value);
        inline TEventParameter(const void *ptr);

        inline bool isEmpty() const;

        inline bool isInt() const;
        inline int getIntValue() const;

        inline bool isDouble() const;
        inline double getDoubleValue() const;

        inline bool isString() const;
        inline TString getStringValue() const;

        inline bool isWString() const;
        inline TStringW getWStringValue() const;

        inline bool isPointer() const;
        inline void* getPointerValue() const;

        inline void setIntValue(int value);
        inline void setPointerValue(void* value);

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

    inline TEventParameter::TEventParameter(const TString value)
    {
        m_type = PT_string;
        m_stringValue = value;
    }

    inline TEventParameter::TEventParameter(const TStringW value)
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

    inline void TEventParameter::setIntValue(int value)
    {
        m_type = PT_int;
        m_intValue = value;
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

    inline TString TEventParameter::getStringValue() const 
    {
        return m_stringValue;
    }

    inline bool TEventParameter::isWString() const 
    {
        return (m_type == PT_wstring);
    }

    inline TStringW TEventParameter::getWStringValue() const 
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

    inline void TEventParameter::setPointerValue(void* value)
    {
        m_pointerValue = value;
    }
}
#endif

