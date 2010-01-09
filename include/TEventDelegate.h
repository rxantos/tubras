//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TEVENTDELEGATE_H_
#define _TEVENTDELEGATE_H_

namespace Tubras
{
    class TEvent;

    typedef int (TDelegate::*TEventDelegateFunction)(const TEvent* event);

    class TEventDelegate : public TDelegate
    {
    protected:
        TEventDelegateFunction  pFunction;

    public:
        TEventDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TEventDelegate(TDelegate* instance,
            TEventDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual int Execute(const TEvent* event) const;

        void SetCallback (TDelegate  *instance,
            TEventDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}
#endif

