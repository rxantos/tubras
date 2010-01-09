//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TBVIEW_H_
#define _TBVIEW_H_

namespace Tubras
{
    class TBView : public TBehavior
    {
        friend class TBehaviorFactory;
    protected:
        TBView() : TBehavior("view") {}
    public:
        int initialize(TEntity* owner, TProperties& properties);
    };
}

#endif
