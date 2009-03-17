//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TTASKDELEGATE_H_
#define _TTASKDELEGATE_H_

namespace Tubras
{
    class TTask;
    class TDObject;


    typedef int (TDObject::*TTaskDelegateFunction)(TTask* Param);

    class TTaskDelegate : public TDelegate
    {
    protected:
        TTaskDelegateFunction  pFunction;

    public:
        TTaskDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TTaskDelegate(TDObject* instance,
            TTaskDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual int Execute(TTask* Param) const;

        void SetCallback (TDObject  *instance,
            TTaskDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}
#endif

