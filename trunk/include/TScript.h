//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------

#ifndef _TSCRIPT_H_
#define _TSCRIPT_H_

namespace Tubras
{
    typedef TMap< TString, void *> MAP_SCRIPTFUNCS;
    typedef void*           TModule;

    typedef MAP_SCRIPTFUNCS::Iterator MAP_SCRIPTFUNCS_ITR;

    class TScript 
    {
        friend class TScriptManager;
    private:
        TString             m_modName;
        void*			    m_module;
        void*			    m_application;
        MAP_SCRIPTFUNCS	    m_functions;

    protected:
        void printLUAErr();
        int checkError();
        void* classToScriptObject(void *klass, TString type);
        int	unRef(void *pobj);
        void* getFunction(void*pObj, TString funcname);
        TScript(TString modName);
        virtual ~TScript();
        int initialize();

    public:
        void logMessage(TString msg) {}
        void* callFunction(TString function,const char *fmt, ...);
        void* callModFunction(TModule baseptr, TString function,const char *fmt, ...);
        bool inheritedFrom(void* obj, TString cname);
        TModule getModule() {return m_module;}
        TString getModName() {return m_modName;}
    };
}

#endif
