//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------

#ifndef _ISCRIPT_H_
#define _ISCRIPT_H_

namespace Tubras
{
    enum SReturnType {stInt, stFloat, stDouble, stString, stStringW, stObject};
    class SReturnValue : public IReferenceCounted
    {
        int         iValue;
        float       fValue;
        double      dValue;
        stringc     sValue;
        stringw     swValue;
        long        lValue;
        void*       oValue;
    public:
        SReturnType type;
        int getInt() {return iValue;}
        float getFloat() {return fValue;}
        double getDouble() {return dValue;}
        stringc getString() {return sValue;}
        stringw getStringW() {return swValue;}
        long getLong() {return lValue;}
        void* getObject() {return oValue;}
    };

    class IScript : public virtual IReferenceCounted
    {
    public:
        virtual SReturnValue* callFunction(const stringc function,const char *fmt, ...)=0;
        virtual int initialize(const stringc modPath, const stringc moduleName)=0;
        virtual stringc getModuleName()=0;
        virtual bool inheritsFrom(const stringc className)=0;
        virtual int createStates()=0;
    };
}

#endif
