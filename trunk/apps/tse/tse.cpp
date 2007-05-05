//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software Ltd
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
    TConfigFile conf;

    conf.load("tse.cfg");

    m_modPath = conf.getSetting("modpath","Script");

    m_modName = conf.getSetting("module","Script");

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
    if(m_scriptManager->initialize(m_modPath,argv[0]))
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
    m_application = m_script->callFunction("createTubrasApp","iv",argc,argv);
    if(!m_application)
    {
        //logMessage("Error Invoking Script \"createApplication()\" function ");
        return 1;
    }
    Py_INCREF(m_application);

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
    m_script->callFunction(m_application,"initialize","");



    return rc;
}

//-----------------------------------------------------------------------
//                           r u n S c r i p t
//-----------------------------------------------------------------------
int runScript()
{
    m_script->callFunction(m_application,"run","");
    return 0;
}

//-----------------------------------------------------------------------
//                               m a i n
//-----------------------------------------------------------------------
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
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

        if(m_application)
            Py_DECREF(m_application);

        return 0;

    }
