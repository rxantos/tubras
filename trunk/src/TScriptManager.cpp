//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"
#ifdef SCRIPTING_ENABLED

static Tubras::TScriptManager* theScriptManager;
static FILE* logFile=0; // temporary startup log file
static lua_State* m_lua; // in order to avoid lua also having a "TString" definition... 

namespace Tubras
{
    template<> TScriptManager* TSingleton<TScriptManager>::ms_Singleton = 0;

    //-----------------------------------------------------------------------
    //                       T S c r i p t M a n a g e r
    //-----------------------------------------------------------------------
    TScriptManager::TScriptManager() : TObject(),
        m_eventDelegate(0),
        m_scriptLang(slUnknown),
        m_funcIntervalDelegate(0)
    {
        theScriptManager = this;
    }

    //-----------------------------------------------------------------------
    //                      ~ T S c r i p t M a n a g e r
    //-----------------------------------------------------------------------
    TScriptManager::~TScriptManager()
    {
        if(m_funcIntervalDelegate)
            delete m_funcIntervalDelegate;
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
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

        Tubras::TString msg;
        msg = "Python: ";
        msg += line;

        if(getApplication())
        {
            if(logFile)
            {
                fclose(logFile);
                logFile = 0;
            }
            getApplication()->logMessage(msg.c_str());
        }
        else // application net yet available
        {
            if(logFile)
                fprintf(logFile,"%s\n",msg.c_str());
            else
                printf("%s\n",msg.c_str());
        }
        return 0;
    }

    //-----------------------------------------------------------------------
    //                         s t d R e d i r e c t
    //-----------------------------------------------------------------------
    /*
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
    */

    //-----------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TScriptManager::initialize(TString modPath, TString appEXE, TString lang,
        int argc,const char **argv)
    {
        TString path;
        int rc=0;
        m_modPath = modPath;

        if(lang.equals_ignore_case("lua"))
            m_scriptLang = slLUA;
        else
            m_scriptLang = slLUA;
        
        //
        // setup script delegates
        //
        m_eventDelegate = EVENT_DELEGATE(TScriptManager::handleEvent);
        m_funcIntervalDelegate = INTERVAL_DELEGATE(TScriptManager::functionInterval);

        return rc;
    }

    //-----------------------------------------------------------------------
    //                    f u n c t i o n I n t e r v a l
    //-----------------------------------------------------------------------
    void TScriptManager::functionInterval(double T,void* userData)
    {
        /*
        PyObject* function = (PyObject*)userData;
        PyObject* elapsedTime = PyFloat_FromDouble(T);

        PyTuple_SetItem(m_funcIntervalArgs, 0, elapsedTime);

        //
        // Call the function
        //
        PyObject* pResult = PyObject_CallObject(function, m_funcIntervalArgs);

        if(pResult)
        {
            Py_DECREF(pResult);
            pResult = NULL;
        }
        */
    }

    //-----------------------------------------------------------------------
    //                         h a n d l e E v e n t
    //-----------------------------------------------------------------------
    int TScriptManager::handleEvent(const TEvent* event)
    {
        int rc = 0;

        
        /*
        PyObject* handler = (PyObject*)((TEvent*)event)->getUserData();

        //
        // prep the TEvent class to be passed as an argument to the
        // event handler.
        //
        sipWrapperType *wt=sipFindClass("TEvent");
        PyObject* pevent = sipConvertFromInstance((void *)event,wt,0);
        Py_INCREF(pevent);

        PyObject* pargs = PyTuple_New(1);
        PyTuple_SetItem(pargs, 0, pevent);


        //
        // Call the event handler.
        //
        PyObject* pResult = PyObject_CallObject(handler, pargs);

        //
        // clean up args (and implicitly the contained values)
        //
        Py_DECREF(pargs);


        if(!pResult)
        {
            PyErr_Print();
            return 0;
        }

        //
        // decref None and return NULL
        //
        if(pResult == Py_None)
        {
            Py_DECREF(pResult);
            pResult = NULL;
        }
        else 
        {
            rc = PyInt_AsLong(pResult);
            Py_DECREF(pResult);
        }

        //
        // non NULL return values must be Py_DECREF'd by the caller when
        // the caller is finished with result.
        //
        */

        return rc;
    }

    //-----------------------------------------------------------------------
    //                         l o a d S c r i p t
    //-----------------------------------------------------------------------
    IScript* TScriptManager::loadScript(TString scriptName)
    {
        IScript* script = 0;
        switch(m_scriptLang)
        {
        case slLUA:
            script = new TLUAScript();
            break;
        };

        if(!script)
            return 0;

        if(script->initialize(m_modPath, scriptName))
        {
            script->drop();
            return 0;
        }

        m_scripts[scriptName] = script;
        return script;
    }

    //-----------------------------------------------------------------------
    //                        u n l o a d S c r i p t
    //-----------------------------------------------------------------------
    int TScriptManager::unloadScript(IScript* script)
    {
        return unloadScript(script->getModuleName());
    }

    //-----------------------------------------------------------------------
    //                        u n l o a d S c r i p t
    //-----------------------------------------------------------------------
    int TScriptManager::unloadScript(TString scriptName)
    {
        IScript* script;
        MAP_SCRIPTS_ITR itr = m_scripts.find(scriptName);
        if(itr.atEnd())
            return 1;

        script = itr->getValue();
        m_scripts.delink(itr->getKey());

        script->drop();


        return 0;
    }

}
#endif
