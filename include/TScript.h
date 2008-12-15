//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------

#ifndef _TSCRIPT_H_
#define _TSCRIPT_H_

namespace Tubras
{
    typedef TMap< TString, PyObject *> MAP_SCRIPTFUNCS;
    typedef PyObject    TModule;

    typedef MAP_SCRIPTFUNCS::Iterator MAP_SCRIPTFUNCS_ITR;

    class TScript 
    {
        friend class TScriptManager;
    private:
        TString             m_modName;
        PyObject*			m_module;
        PyObject*			m_application;
        MAP_SCRIPTFUNCS	    m_functions;

    protected:
        void printPyErr();
        int checkError();
        PyObject* classToPyObject(void *klass, TString type);
        int	unRef(PyObject *pobj);
        PyObject *getFunction(PyObject *pObj, TString funcname);
        TScript(TString modName);
        virtual ~TScript();
        int initialize();

    public:
        void logMessage(TString msg) {}
        PyObject* callFunction(TString function,const char *fmt, ...);
        PyObject* callModFunction(TModule* baseptr, TString function,const char *fmt, ...);
        bool inheritedFrom(PyObject* obj, TString cname);
        TModule* getModule() {return m_module;}
        TString getModName() {return m_modName;}
    };
}

#endif
