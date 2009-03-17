//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TPROPERTIES_H_
#define _TPROPERTIES_H_

namespace Tubras
{
    class TProperty : public IReferenceCounted
    {
        friend class TProperties;
    protected:
        TPropertyType   m_type;
        bool            m_bool;
        double          m_number;
        TString         m_string;
        TStringW        m_wstring;
        void*           m_pointer;
        TEntity*        m_entity;

        inline TProperty() {
            m_type = ptEmpty;
        }

        inline TProperty(TProperty& other) {
            *this = other;
        }

        inline TProperty(bool value) {
            m_type = ptBool;
            m_bool = value;
        }

        inline TProperty(double value) {
            m_type = ptNumber;
            m_number = value;
        }

        inline TProperty(const TString value) {
            m_type = ptString;
            m_string = value;
        }

        inline TProperty(const TStringW value) {
            m_type = ptWideString;
            m_wstring = value;
        }

        inline TProperty(const void* value) {
            m_type = ptPointer;
            m_pointer = (void *)value;
        }

        inline TProperty(const TEntity* value) {
            m_type = ptEntity;
            m_entity = (TEntity *)value;
        }

    public:
        inline TProperty& operator=(const TProperty& other) {
            if(this == &other)
                return *this;
            this->m_type = other.m_type;
            switch(this->m_type)
            {
            case ptNumber: this->m_number = other.m_number; break;
            case ptString: this->m_string = other.m_string; break;
            case ptWideString: this->m_wstring = other.m_wstring; break;
            case ptPointer: this->m_pointer = other.m_pointer; break;
            case ptEntity: this->m_entity = other.m_entity; break;
            }
            return *this;
        }

        inline void operator=(const bool value) {
            m_type = ptBool;
            m_bool = value;
        }
        inline void operator=(const int value) {
            m_type = ptNumber;
            m_number = (double) value;
        }
        inline void operator=(const double value) {
            m_type = ptNumber;
            m_number = value;
        }
        inline void operator=(const TString value) {
            m_type = ptString;
            m_string = value;
        }
        inline void operator=(const TStringW value) {
            m_type = ptWideString;
            m_wstring = value;
        }
        inline void operator=(const char value[]) {
            m_type = ptString;
            m_string = value;
        }
        inline void operator=(const void* value) {
            m_type = ptPointer;
            m_pointer = (void *) value;
        }
        inline void operator=(const TEntity* value) {
            m_type = ptEntity;
            m_entity = (TEntity*) value;
        }

        inline TPropertyType getType() {return m_type;}
        inline bool getBool() {return m_bool;}
        inline int getInteger() {return (int) m_number;}
        inline double getDouble() {return m_number;}
        inline float getFloat() {return (float) m_number;}
        inline TString getString() {return m_string;}
        inline TStringW getWideString() {return m_wstring;}
        inline TEntity* getEntity() {return m_entity;}
    };

    typedef TMap<TString, TProperty*>   TPropertyMap;
    typedef TPropertyMap::Iterator      TPropertyMapItr; 

    class TProperties : public IReferenceCounted
    {
        TPropertyMap            m_properties;
        static TProperty        m_empty;
    public:
        TProperties() {}
        ~TProperties() {}

        TProperties& operator=(TProperties& other)
        {
            if(this == &other)
                return *this;

            TPropertyMapItr itr = other.getMap().getIterator();
            while(!itr.atEnd())
            {
                TString name = itr->getKey();
                TProperty* prop = itr->getValue();

                m_properties[name] = new TProperty(&prop);

                itr++;
            }


            return *this;
        }

        TProperty& operator[](TString name) {
            TPropertyMap::Node* node = m_properties.find(name);
            if(node)
                return *(node->getValue());
            return m_empty;
        }

        TProperty& operator[](const char name[]) {
            TPropertyMap::Node* node = m_properties.find(name);
            if(node)
                return *(node->getValue());
            else
            {
                TProperty* property = new TProperty();
                m_properties[name] = property;
                return *property;
            }
        }

        TProperty& operator[](u32 index) {
            if((index < 0) || (index >= m_properties.size()))
                return m_empty;
            TPropertyMapItr it = m_properties.getIterator();

            while(index--)
                it++;

            return *(it->getValue());
        }

        inline void addInteger(const TString name, const int value) {
            m_properties[name] = new TProperty((double)value);
        }
        inline void addDouble(const TString name, const double value) {
            m_properties[name] = new TProperty(value);            
        }
        inline void addString(const TString name, const TString value) {
            m_properties[name] = new TProperty(value);            
        }
        inline void addWideString(const TString name, const TString value) {
            m_properties[name] = new TProperty(value);            
        }
        inline void addPointer(const TString name, const void* value) {
            m_properties[name] = new TProperty(value);            
        }
        inline void addEntity(const TString name, const TEntity* value) {
            m_properties[name] = new TProperty(value);            
        }

        inline void clear() {
            m_properties.clear();
        }

        TPropertyMap& getMap() {
            return m_properties;
        }

        inline u32 size() {
            return m_properties.size();
        }
    };
}

#endif
