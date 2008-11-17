//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"
#ifdef USE_PYTHON_SCRIPTING

namespace Tubras
{
    using namespace std;
    static TApplication* m_app=0;

    //-----------------------------------------------------------------------
    //                             T S c r i p t
    //-----------------------------------------------------------------------
    TScript::TScript(TString modName)
    {
        m_modName = modName;
    }

    //-----------------------------------------------------------------------
    //                            ~ T S c r i p t
    //-----------------------------------------------------------------------
    TScript::~TScript()
    {

        for(MAP_SCRIPTFUNCS_ITR it=m_functions.getIterator();!it.atEnd();it++)
        {
            PyObject* obj = it->getValue();
            Py_DECREF(obj);
        }

        if(m_module)
        {
            Py_DECREF(m_module);
            m_module = 0;
        }
    }

    //-------------------------------------------------------------------
    //                           p r i n t P y E r r
    //-------------------------------------------------------------------
    void TScript::printPyErr()
    {
        PyErr_Print();
        return;
    }

    //-------------------------------------------------------------------
    //                        c h e c k E r r o r
    //-------------------------------------------------------------------
    int TScript::checkError()
    {
        int result=0;

        if(PyErr_Occurred())
        {
            printPyErr();
            result = 1;
        }

        return result;
    }

    //-------------------------------------------------------------------
    //                            u n R e f
    //-------------------------------------------------------------------
    int	TScript::unRef(PyObject *pobj)
    {

        if(!pobj)
            return 0;


        Py_DECREF(pobj);


        return 0;
    }

    //-------------------------------------------------------------------
    //                     i n h e r i t e d F r o m
    //-------------------------------------------------------------------
    bool TScript::inheritedFrom(PyObject* obj,TString cname)
    {
        std::string s;
        struct _typeobject *tp_base;

        tp_base = obj->ob_type;
        while(tp_base->tp_base)
        {
            if(!strcmp(tp_base->tp_name,cname.c_str()))
                return true;
            tp_base = tp_base->tp_base;
        }

        return false;
    }

    //-------------------------------------------------------------------
    //                       g e t F u n c t i o n
    //-------------------------------------------------------------------
    PyObject *TScript::getFunction(PyObject *pObj, TString funcname)
    {

        char	buf[10];
        TString  Namespace;
        PyObject* pFunc;

        if(!pObj)
            pObj = m_module;

        sprintf(buf,"%p",pObj);

        Namespace = buf;
        Namespace += ':';
        Namespace += funcname;

        if(m_functions.size())
        {
            MAP_SCRIPTFUNCS::Node* node;
            node = m_functions.find(Namespace);
            if(node)
                return node->getValue();
        }

        //
        // Get function attribute. Ownership is automatically transferred therefore
        // Py_DECREF(pFunc) must be called to release it.
        //
        pFunc = PyObject_GetAttrString(pObj, (char *)funcname.c_str());

        if(!pFunc)
        {
            return NULL;
        }

        //
        // Check attribute (function) is callable
        //
        if(!PyCallable_Check(pFunc))
        {
            return NULL;
        }

        m_functions[Namespace] = pFunc;

        return pFunc;

    }

    //-------------------------------------------------------------------
    //                       c a l l F u n c t i o n
    //-------------------------------------------------------------------
    PyObject* TScript::callFunction(TString function, char *fmt, ...)
    {
        PyObject            *pArgs, *pFunc, *pValue, *pResult;
        va_list             ap;
        const char          *p=fmt;
        int                 args;

        pFunc = getFunction(m_module,function);
        if(!pFunc)
        {
            checkError();
            return NULL;
        }

        //
        // Build parameter list
        //
        va_start(ap,fmt);
        args = (int) strlen(p);

        pArgs = PyTuple_New(args);        

        for(int i=0;*p;i++)
        {
            pValue = NULL;
            switch(*p)
            {
            case 's':
                pValue = PyString_FromString(va_arg(ap,const char *));
                break;
            case 'i':
                pValue = PyInt_FromLong(va_arg(ap,long));
                break;
            case 'f':
                pValue = PyFloat_FromDouble(va_arg(ap,double));
                break;
            case 'p':
                pValue = PyCObject_FromVoidPtr(va_arg(ap,void *),0);
                break;
            case 'v':
                pValue = PyLong_FromVoidPtr(va_arg(ap,void*));
                break;
            case 'o':
                pValue = va_arg(ap,PyObject *);
                //
                // increment ref because callee assumes ownership and decref's it
                //
                Py_INCREF(pValue);
                break;
            }

            //
            // The tuple now owns the value, DECREF'ing the tuple will
            // automatically DECREF the value.
            //
            // This is a bit tricky so worth noting - the above Pyxxx_Fromxxx
            // transfers ownership to us.  PyTuple_SetItem assumes ownership
            // with incrementing the Reference count. If we need to keep a
            // reference around, we would need to Py_INCREF it.
            //
            PyTuple_SetItem(pArgs, i, pValue);
            ++p;
        }

        //
        // Call the function.
        //
        pResult = PyObject_CallObject(pFunc, pArgs);
        if(!pResult)
            PyErr_Print();

        //
        // clean up args (and implicitly the contained values)
        //
        Py_DECREF(pArgs);

        //
        // decref None and return NULL
        //
        if(pResult == Py_None)
        {
            Py_DECREF(pResult);
            pResult = NULL;
        }

        //
        // non NULL return values must be Py_DECREF'd by the caller when
        // the caller is finished with result.
        //
        return pResult;
    }

    //-------------------------------------------------------------------
    //                     c a l l M o d F u n c t i o n
    //-------------------------------------------------------------------
    PyObject* TScript::callModFunction(PyObject* baseptr, TString function,char *fmt, ...)
    {
        PyObject            *pArgs, *pFunc, *pValue, *pResult;
        va_list             ap;
        const char          *p=fmt;
        int                 args;

        pFunc = getFunction(baseptr,function);
        if(!pFunc)
        {
            checkError();
            return NULL;
        }

        //
        // Build parameter list
        //
        va_start(ap,fmt);
        args = (int) strlen(p);

        pArgs = PyTuple_New(args);        

        for(int i=0;*p;i++)
        {
            pValue = NULL;
            switch(*p)
            {
            case 's':
                pValue = PyString_FromString(va_arg(ap,const char *));
                break;
            case 'i':
                pValue = PyInt_FromLong(va_arg(ap,long));
                break;
            case 'f':
                pValue = PyFloat_FromDouble(va_arg(ap,double));
                break;
            case 'o':
                pValue = va_arg(ap,PyObject *);
                //
                // increment ref because callee assumes ownership and decref's it
                //
                Py_INCREF(pValue);
                break;
            }

            //
            // The tuple now owns the value, DECREF'ing the tuple will
            // automatically DECREF the value.
            //
            // This is a bit tricky so worth noting - the above Pyxxx_Fromxxx
            // transfers ownership to us.  PyTuple_SetItem assumes ownership
            // with incrementing the Reference count. If we need to keep a
            // reference around, we would need to Py_INCREF it.
            //
            PyTuple_SetItem(pArgs, i, pValue);
            ++p;
        }

        //
        // Call the function.
        //
        pResult = PyObject_CallObject(pFunc, pArgs);
        if(!pResult)
            PyErr_Print();

        //
        // clean up args (and implicitly the contained values)
        //
        Py_DECREF(pArgs);

        //
        // decref None and return NULL
        //
        if(pResult == Py_None)
        {
            Py_DECREF(pResult);
            pResult = NULL;
        }

        //
        // non NULL return values must be Py_DECREF'd by the caller when
        // the caller is finished with result.
        //
        return pResult;
    }

    //-------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-------------------------------------------------------------------
    int TScript::initialize()
    {
        PyObject *pName;
        TString err,trace;

        TString path;

        //
        // import the script module
        //
        pName = PyString_FromString(m_modName.c_str());
        if(!pName)
        {
            checkError();
            return 1;
        }

        //
        // reference already incremented for us. will be decref'd
        // when our object is destroyed.
        //
        m_module = PyImport_Import(pName);
        if(!m_module)
        {
            checkError();
            return 1;
        }

        Py_DECREF(pName);

        return 0;

    }
}
#endif
