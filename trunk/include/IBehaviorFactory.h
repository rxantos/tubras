//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _IBEHAVIORFACTORY_H_
#define _IBEHAVIORFACTORY_H_

namespace Tubras
{
    class IBehaviorFactory : public virtual IReferenceCounted
    {

    public:
        virtual ~IBehaviorFactory() {}
        virtual IBehavior* createBehavior(const TString type, TProperties& properties,
            TEntity* owner) = 0;

    };
}

#endif
