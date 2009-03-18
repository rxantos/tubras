//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TBEHAVIOR_H_
#define _IBEHAVIOR_H_

namespace Tubras
{

    class TBehavior : public virtual IBehavior
    {
        friend class TBehaviorFactory;
    protected:
        TString         m_type;
        TEntity*        m_owner;
        bool            m_enabled;
        TString         m_name;
        TProperties     m_properties;

    protected:
        TBehavior(TString type) : IBehavior(), m_type(type), m_owner(0), m_enabled(true) {}
        virtual ~TBehavior() {}

    public:
        virtual int initialize(TEntity* owner, TProperties& properties)
        {
            m_owner = owner;
            m_name = properties["name"].asString();
            m_enabled = properties["enabled"].asBool();
            m_properties = properties;
            return 0;
        }
        virtual void setEnabled(bool value) {m_enabled=value;}
        virtual bool getEnabled() {return m_enabled;}
        virtual TString getName() {return m_name;}
        virtual TString getType() {return m_type;}
        virtual TEntity* getOwner() {return m_owner;}
        virtual TProperties& properties() {return m_properties;}
        virtual TProperty& operator[](TString name) {
            return m_properties[name];
        }

        virtual TProperty& operator[](const char name[]) {
            return m_properties[name];
        }
    };

}

#endif
