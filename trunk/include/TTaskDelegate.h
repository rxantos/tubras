//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TTASKDELEGATE_H_
#define _TTASKDELEGATE_H_

namespace Tubras
{
    class TTask;
    class TDelegate;


    typedef int (TDelegate::*TTaskDelegateFunction)(TTask* Param);

    class TTaskDelegate : public TDelegate
    {
    protected:
        TTaskDelegateFunction  pFunction;

    public:
        TTaskDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TTaskDelegate(TDelegate* instance,
            TTaskDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual int Execute(TTask* Param) const;

        void SetCallback (TDelegate  *instance,
            TTaskDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}
#endif

