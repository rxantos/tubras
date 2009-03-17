//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TEVENTDELEGATE_H_
#define _TEVENTDELEGATE_H_

namespace Tubras
{
    class TEvent;

    typedef int (TDObject::*TEventDelegateFunction)(const TEvent* event);

    class TEventDelegate : public TDelegate
    {
    protected:
        TEventDelegateFunction  pFunction;

    public:
        TEventDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TEventDelegate(TDObject* instance,
            TEventDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual int Execute(const TEvent* event) const;

        void SetCallback (TDObject  *instance,
            TEventDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}
#endif

