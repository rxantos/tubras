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
        friend class TBehaviorFactory;
    protected:
        TString         m_type;
        TEntity*        m_owner;
        bool            m_enabled;
        TString         m_name;
        TProperties     m_properties;

    public:
        virtual int initialize(TEntity* owner, TProperties& properties) = 0;
        virtual void setEnabled(bool value) = 0;
        virtual bool getEnabled() = 0;
        virtual TString getName() = 0;
        virtual TString getType() = 0;
        virtual TEntity* getOwner() = 0;
        virtual TProperties& properties()  = 0;
        virtual TProperty& operator[](TString name) = 0;
        virtual TProperty& operator[](const char name[])  = 0;
    };
}

#endif
