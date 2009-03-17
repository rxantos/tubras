//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _IBEHAVIOR_H_
#define _IBEHAVIOR_H_

namespace Tubras
{
    typedef TMap<TString, IBehavior*> TBehaviorMap;
    typedef TBehaviorMap::Iterator TBehaviorMapItr;

    class IBehavior : public virtual IReferenceCounted
    {
        friend class IBehaviorFactory;
    protected:
        TEntity*        m_owner;
        bool            m_enabled;
        TString         m_name;
        TProperties     m_properties;

    protected:
        IBehavior() : m_owner(0), m_enabled(true), m_name("") {};

    public:
        virtual int initialize(TEntity* owner, TProperties& properties)
        {
            m_owner = owner;
            m_name = properties["name"].getString();
            m_enabled = properties["enabled"].getBool();
            m_properties = properties;
            return 0;
        }
        virtual void setEnabled(bool value) {m_enabled=value;}
        virtual bool getEnabled() {return m_enabled;}
        virtual TString getName() {return m_name;}
        virtual TEntity* getOwner() {return m_owner;}
    };

}

#endif
