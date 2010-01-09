//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _ILISTENER_H_
#define _ILISTENER_H_

namespace Tubras
{
    class IListener : public virtual IReferenceCounted
    {
    public:
        virtual void update(TEvent& event)=0;
    };
}

#endif
