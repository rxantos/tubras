//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TBEHAVIORFACTORY_H_
#define _TBEHAVIORFACTORY_H_

namespace Tubras
{
    class TBehaviorFactory : public virtual IBehaviorFactory
    {
    public:
        IBehavior* createBehavior(const TString type, TProperties& properties,
            TEntity* owner);
    };
}

#endif
