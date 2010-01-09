//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TINTERVALDELEGATE_H_
#define _TINTERVALDELEGATE_H_

namespace Tubras
{
    typedef void (TDelegate::*TIntervalDelegateFunction)(double T, void* userData);

    class TIntervalDelegate : public TDelegate
    {
    protected:
        TIntervalDelegateFunction  pFunction;

    public:
        TIntervalDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TIntervalDelegate(TDelegate* instance,
            TIntervalDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual void Execute(double T, void* userData) const;

        void SetCallback (TDelegate  *instance,
            TIntervalDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}
#endif

