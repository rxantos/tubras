//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TINTERVALDELEGATE_H_
#define _TINTERVALDELEGATE_H_

namespace Tubras
{
    class TObject;


    typedef void (TObject::*TIntervalDelegateFunction)(double T, void* userData);

    class TIntervalDelegate : public TDelegate
    {
    protected:
        TIntervalDelegateFunction  pFunction;

    public:
        TIntervalDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TIntervalDelegate(TObject* instance,
            TIntervalDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual void Execute(double T, void* userData) const;

        void SetCallback (TObject  *instance,
            TIntervalDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}
#endif

