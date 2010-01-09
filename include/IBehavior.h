//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
