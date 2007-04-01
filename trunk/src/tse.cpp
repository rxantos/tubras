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
#include "tpyscript.h"
#include <stdlib.h>

using namespace Tubras;

static TScript* theScript;
static TString  m_path;
static TString  m_script;

//-----------------------------------------------------------------------
//                           l o a d O p t i o n s
//-----------------------------------------------------------------------
int loadOptions()
{
    TConfigFile conf;

    conf.load("tse.cfg");
    m_path = conf.getSetting("path","Script");
    m_script = conf.getSetting("script","Script");

    return 0;
}

//-----------------------------------------------------------------------
//                           i n i t S c r i p t
//-----------------------------------------------------------------------
int initScript(int argc, char** argv)
{
    theScript = new TPyScript(m_path,m_script);
    return theScript->initialize(argc, argv);
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

    if(loadOptions())
        return 1;

    if(initScript(argc,argv))
        return 1;

        //TSandbox app(argc,argv);

        //if(!app.initialize())
        //    app.run();

        return 0;

    }
