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
#include <stdlib.h>

using namespace Tubras;

TScript* m_script;
TScriptManager* m_scriptManager=0;
TModule* m_application=0;

static TString  m_modPath;
static TString  m_modName;

//-----------------------------------------------------------------------
//                           l o a d O p t i o n s
//-----------------------------------------------------------------------
int loadOptions(int argc, char** argv)
{

#ifdef USE_ISL_SCRIPT
    isl::CISL* conf = new isl::CISL();
#else
    lsl::CLSL* conf = new lsl::CLSL();
#endif
    if(conf->loadScript("../data/cfg/tse.cfg") == E_OK)
    {
        m_modPath = conf->getString("script.modpath");
        m_modName = conf->getString("script.module");
    }

    conf->drop();

    //
    // command line overrides settings in config file.
    //
    int c;
    optind = 0;		
    while ((c = getopt(argc, argv, "m:p:")) != EOF)
    {
        switch (c)
        {
        case 'm':
            m_modName = optarg;
            break;
        case 'p':
            m_modPath += optarg;
            break;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------
//                           i n i t S c r i p t
//-----------------------------------------------------------------------
int initScript(int argc, char** argv)
{
    int rc = 0;

    m_scriptManager = new TScriptManager();
    if(m_scriptManager->initialize(m_modPath,argv[0],argc,argv))
        return 1;

    m_script = m_scriptManager->loadScript(m_modName);
    if(!m_script)
    {
        // error loading script
        return 1;
    }

    //
    // Call module script function "createTubrasApp" - returns
    // a TApplication derivative.
    //
    m_application = m_script->callFunction("createTubrasApp","");
    if(!m_application)
    {
        //logMessage("Error Invoking Script \"createApplication()\" function ");
        return 1;
    }
    TApplication* theApp = getApplication();
    if(theApp)
        theApp->setArgs(argc,argv);
    //Py_INCREF(m_application);

    //
    // validate class inheritence
    //
    if(!m_script->inheritedFrom(m_application,"TApplication"))
    {
        //logMessage("createApplication() Return Argument Not Inherited From Tubras.TApplication");
        return 1;
    }

    //
    // invoke the scripts initialize() method
    //
    m_script->callModFunction(m_application,"initialize","");

    return rc;
}

//-----------------------------------------------------------------------
//                           r u n S c r i p t
//-----------------------------------------------------------------------
int runScript()
{
    m_script->callModFunction(m_application,"run","");
    return 0;
}

//-----------------------------------------------------------------------
//                               m a i n
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    char    **argv=__argv;
    int     argc=__argc;
#else
extern "C" {
    int main(int argc, char **argv)
    {
#endif

        if(loadOptions(argc,argv))
            return 1;

        if(initScript(argc,argv))
            return 1;

        runScript();

        if(m_script)
            m_scriptManager->unloadScript(m_script);

        if(m_application)
        {
            //
            // decref down to zero so app object is gc'd and
            // destructor is called.
            //
            Py_ssize_t refcnt = m_application->ob_refcnt;
            while(refcnt > 0)
            {
                Py_DECREF(m_application);
                --refcnt;
            }
        }

        return 0;

    }
#ifndef TUBRAS_PLATFORM_WIN32
}
#endif

