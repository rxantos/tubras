//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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

