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
    typedef TArray<TEntity*> TOwnerList;
    class IBehavior : public virtual IReferenceCounted, public virtual IListener
    {
        friend class TBehaviorFactory;
    protected:

    public:
        virtual int initialize(TEntity* owner, TProperties& properties) = 0;
        virtual bool addOwner(TEntity* owner) = 0;

        virtual void setEnabled(bool value) = 0;
        virtual bool getEnabled() = 0;
        virtual TString getName() = 0;
        virtual TString getType() = 0;
        virtual TOwnerList& getOwners() = 0;
        virtual TProperties& properties()  = 0;
        virtual TProperty& operator[](TString name) = 0;
        virtual TProperty& operator[](const char name[])  = 0;
        virtual void update(TEvent& event) = 0;
    };
}

#endif
