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
#include <stdlib.h>

using namespace Tubras;

IScript* m_script;
TScriptManager* m_scriptManager=0;
TModule m_application=0;

static TString  m_modPath;
static TString  m_modName;
static TString  m_lang;

//-----------------------------------------------------------------------
//                           l o a d O p t i o n s
//-----------------------------------------------------------------------
int loadOptions(int argc, const char** argv)
{

    lsl::CLSL* conf = new lsl::CLSL();
    if(conf->loadScript("../data/cfg/tse.lsl") == E_OK)
    {
        m_modPath = conf->getString("script.modpath");
        m_modName = conf->getString("script.modname");
        m_lang = conf->getString("script.lang","lua");
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
int initScript(int argc, const char** argv)
{
    int rc = 0;

    m_scriptManager = new TScriptManager();
    if(m_scriptManager->initialize(m_modPath,argv[0],m_lang,argc,argv))
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
    if(!m_script->inheritsFrom("TApplication"))
    {
        //logMessage("createApplication() Return Argument Not Inherited From Tubras.TApplication");
        return 1;
    }

    //
    // invoke the scripts initialize() method
    //
    m_script->callFunction("initialize","");

    return rc;
}

//-----------------------------------------------------------------------
//                           r u n S c r i p t
//-----------------------------------------------------------------------
int runScript()
{
    m_script->callFunction("run","");
    return 0;
}

//-----------------------------------------------------------------------
//                               m a i n
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    const char  **argv=(const char**)__argv;
    int         argc=__argc;
#else
extern "C" {
    int main(int argc, const char **argv)
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
        }

        return 0;

    }
#ifndef TUBRAS_PLATFORM_WIN32
}
#endif

