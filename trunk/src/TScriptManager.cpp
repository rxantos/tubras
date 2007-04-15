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
#include "sip/sipAPITubras.h"
#include "sip.h"

static Tubras::TScriptManager* theScriptManager;
extern "C" void initTubras();

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                       T S c r i p t M a n a g e r
    //-----------------------------------------------------------------------
    TScriptManager::TScriptManager() : TObject()
    {
        theScriptManager = this;
    }

    //-----------------------------------------------------------------------
    //                      ~ T S c r i p t M a n a g e r
    //-----------------------------------------------------------------------
    TScriptManager::~TScriptManager()
    {
        Py_Finalize();
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TScriptManager* TSingleton<TScriptManager>::ms_Singleton = 0;

    TScriptManager* TScriptManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TScriptManager& TScriptManager::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                             l o g W r i t e
    //-----------------------------------------------------------------------
    int logWrite(char *line)
    {
        int newline=line[strlen(line)-1]=='\n';
        if(newline)
            line[strlen(line)-1]='\0';
        
        // printf("logwrite(\"%s%s\")\n", line, newline?"\\n":"");

        TString msg;
        msg = "Python: ";
        msg += line;

        if(getApplication())
            getApplication()->logMessage(msg.c_str());
        else printf(msg.c_str());
        return 0;
    }

    //-----------------------------------------------------------------------
    //                         s t d R e d i r e c t
    //-----------------------------------------------------------------------
    static PyObject *stdRedirect(PyObject *self, PyObject *args)
    {
        char *s_line;
        if (!PyArg_ParseTuple(args, "s:stdRedirect", &s_line))
            return NULL;

        Py_BEGIN_ALLOW_THREADS
            logWrite(s_line);
        Py_END_ALLOW_THREADS

        Py_INCREF(Py_None);
        return Py_None;
    }

    //-----------------------------------------------------------------------
    //                      r e d i r e c t M e t h o d s
    //-----------------------------------------------------------------------
    static PyMethodDef redirectMethods[] = {
        {"stdRedirect", (PyCFunction)stdRedirect, METH_VARARGS,
        "stdRedirect(line) writes a log message"},
        {NULL, NULL, 0, NULL}
    };

    //-----------------------------------------------------------------------
    //                         s e t u p R e d i r e c t
    //-----------------------------------------------------------------------
    void TScriptManager::setupRedirect()
    {
        Py_InitModule("stdRedirect", redirectMethods);
        if(PyErr_Occurred())
        {
            PyErr_Print();
            return;
        }
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
        if(PyErr_Occurred())
        {
            PyErr_Print();
            return;
        }
    }

    //-----------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TScriptManager::initialize(TString modPath)
    {
        TString path;
        int rc=0;
        m_modPath = modPath;

        //
        // Initialize the Python interpreter
        //

        Py_Initialize();

        path = Py_GetPath();

        path = m_modPath;

        PySys_SetPath((char *)path.c_str());

        path = Py_GetPath();

        //
        // redirect Python's stdout/stderr 
        //
        setupRedirect();

        //
        // initialize the SIP generated tubras module
        //
        initTubras();

        //
        // setup script delegates
        //
        m_eventDelegate = EVENT_DELEGATE(TScriptManager::handleEvent);

        return rc;
    }

    //-----------------------------------------------------------------------
    //                         h a n d l e E v e n t
    //-----------------------------------------------------------------------
    int TScriptManager::handleEvent(TSEvent event)
    {
        PyObject* handler = (PyObject*)event->getUserData();
        sipWrapperType *wt=sipFindClass("TEvent");
        PyObject* pevent = sipConvertFromInstance((void *)event.getPointer(),wt,0);

        call handler(pevent) here

        return 0;
    }

    //-----------------------------------------------------------------------
    //                         l o a d S c r i p t
    //-----------------------------------------------------------------------
    TScript* TScriptManager::loadScript(TString scriptName)
    {
        TScript* script = new TScript(scriptName);
        if(script->initialize())
        {
            delete script;
            return 0;
        }

        m_scripts[scriptName] = script;
        return script;
    }
}
