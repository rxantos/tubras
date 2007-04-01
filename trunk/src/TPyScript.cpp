//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#include "tubras.h"
#include "tpyscript.h"
#include "swigpyrun.h"

extern "C" void init_Tubras(void);
extern PyObject* toCharPP(char** v);

namespace Tubras
{
    int logwrite(char *line)
    {
        int newline=line[strlen(line)-1]=='\n';
        if(newline)
            line[strlen(line)-1]='\0';
        printf("logwrite(\"%s%s\")\n", line, newline?"\\n":"");
        return 0;
    }

    static PyObject *stdRedirect(PyObject *self, PyObject *args)
    {
        char *s_line;
        if (!PyArg_ParseTuple(args, "s:stdRedirect", &s_line))
            return NULL;

        Py_BEGIN_ALLOW_THREADS
            logwrite(s_line);
        Py_END_ALLOW_THREADS

        Py_INCREF(Py_None);
        return Py_None;
    }

    static PyMethodDef andreMethods[] = {
        {"stdRedirect", (PyCFunction)stdRedirect, METH_VARARGS,
        "stdRedirect(line) writes a log message"},
        {NULL, NULL, 0, NULL}
    };

    //-----------------------------------------------------------------------
    //                             T S c r i p t
    //-----------------------------------------------------------------------
    TPyScript::TPyScript(TString scriptPath, TString scriptName) : TScript(scriptPath,scriptName)
    {
    }

    //-----------------------------------------------------------------------
    //                            ~ T S c r i p t
    //-----------------------------------------------------------------------
    TPyScript::~TPyScript()
    {
        Py_Finalize();
    }

    //-------------------------------------------------------------------
    //                       p r i n t P y E r r
    //-------------------------------------------------------------------
    void TPyScript::printPyErr()
    {
        PyErr_Print();
        return;
    }

    //-------------------------------------------------------------------
    //                        c h e c k E r r o r
    //-------------------------------------------------------------------
    int TPyScript::checkError()
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
    //                  c l a s s T o P y O b j e c t
    //-------------------------------------------------------------------
    PyObject* TPyScript::classToPyObject(void *klass, string type)
    {
        swig_type_info *pti = SWIG_TypeQuery(type.c_str());
        return SWIG_NewPointerObj(klass, pti, 0);
    }

    //-------------------------------------------------------------------
    //                            u n R e f
    //-------------------------------------------------------------------
    int	TPyScript::unRef(PyObject *pobj)
    {

        if(!pobj)
            return 0;


        Py_DECREF(pobj);


        return 0;
    }

    //-------------------------------------------------------------------
    //                     i n h e r i t e d F r o m
    //-------------------------------------------------------------------
    int TPyScript::inheritedFrom(PyObject* obj,string cname)
    {
        string s;
        struct _typeobject *tp_base;

        tp_base = obj->ob_type;
        while(tp_base->tp_base)
        {
            if(!strcmp(tp_base->tp_name,cname.c_str()))
                return 1;
            tp_base = tp_base->tp_base;
        }

        return 0;
    }

    //-------------------------------------------------------------------
    //                       g e t F u n c t i o n
    //-------------------------------------------------------------------
    PyObject *TPyScript::getFunction(PyObject *pObj,string funcname)
    {

        char	buf[10];
        string  Namespace;
        PyObject* pFunc;

        if(!pObj)
            pObj = m_module;

        _ui64toa((unsigned __int64)pObj,buf,16);

        Namespace = buf;
        Namespace += ':';
        Namespace += funcname;

        if(pFunc = m_functions[Namespace])
            return pFunc;

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
    PyObject* TPyScript::callFunction(string function, char *fmt, ...)
    {
        PyObject	*result=NULL;
        va_list arglist;

        va_start (arglist, fmt);
        result = callFunction(m_module,function, fmt, arglist);
        va_end (arglist);
        return result;
    }

    //-------------------------------------------------------------------
    //                       c a l l F u n c t i o n
    //-------------------------------------------------------------------
    PyObject* TPyScript::callFunction(PyObject* baseptr, string function,char *fmt, ...)
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
            case 'p':
                char ** arg;
                arg = va_arg(ap,char**);
                pValue = toCharPP(arg);
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
    int TPyScript::initialize(int argc,char** argv)
    {
        PyObject *pName;
        string err,trace;

        TString path;

        //
        // Initialize the Python interpreter
        //

        Py_Initialize();

        path = Py_GetPath();

        path = ";c:\\gdev\\tubras\\scripts;C:\\gdev\\tubras\\deps\\python\\Lib;c:\\gdev\\tubras\\src\\swig;";

        PySys_SetPath((char *)path.c_str());

        path = Py_GetPath();

        //
        // setup stdout/stderr redirection
        //
        Py_InitModule("stdRedirect", andreMethods);
        checkError();
        PyRun_SimpleString(""
			"import stdRedirect     # a module interface created by C application\n"
			"class Logger:\n"
			"    def __init__(self):\n"
			"        self.buf = []\n"
			"    def write(self, data):\n"
			"        self.buf.append(data)\n"
			"        if data.endswith('\\n'):\n"
			"            stdRedirect.stdRedirect(''.join(self.buf))\n"
			"            self.buf = []\n"
			"\n"
			"import sys\n"
			"sys.stdout = Logger()\n"
			"sys.stderr = Logger()\n"
			"");
        checkError();

        init_Tubras();
        checkError();

        //
        // import the script module
        //
        pName = PyString_FromString(m_scriptName.c_str());
        if(!pName)
        {
            checkError();
            return 1;
        }

        m_module = PyImport_Import(pName);
        if(!m_module)
        {
            checkError();
            return 1;
        }

        Py_DECREF(pName);

        Py_INCREF(m_module);

        //
        // Call module script function "createApplication" - returns
        // a TApplication derivative.
        //
        m_application = callFunction(m_module,"createApplication","ip",argc,argv);
        if(!m_application)
        {
            checkError();
            logMessage("Error Invoking Script \"createApplication()\" function ");
            return 1;
        }
        if(checkError())
            return 1;
        Py_INCREF(m_application);

        //
        // validate class inheritence
        //
        if(!inheritedFrom(m_application,"TApplication"))
        {
            logMessage("createApplication() Return Argument Not Inherited From Tubras.TApplication");
            return 1;
        }

        callFunction(m_application,"initialize","");
        callFunction(m_application,"run","");



        //
        // redirect the standard output back into the application object
        //
        string sscript = "import Tubras\n"
            "import sys\n"
            "app = Tubras.getApplication()\n"
            "sys.stdout = app\n"
            "sys.stderr = app\n";

        PyRun_SimpleString(sscript.c_str());

        return 0;

    }

}