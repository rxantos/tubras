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
#include "mokena.h"

#include <stdlib.h>
#include <shellapi.h>

using namespace Tubras;

class TMokena : public TApplication
{
private:
    int         screenNumber;

public:
    TMokena(int argc,char **argv) : TApplication(argc,argv,"Mokena") 
    {
        getApplication()->setThemeDirectory("themes");
    }

    virtual ~TMokena()
    {
    }

    //
    // show/hide the console
    //
    int TMokena::showConsole(Tubras::TSEvent event)
    {
        toggleConsole();
        return 1;
    }

    //
    // take a screen shot of our window.
    //
    int TMokena::saveScreen(Tubras::TSEvent event)
    {

        TStrStream fileName;
        string ext;

        ext = getConfigFile()->getSetting("ScreenCapExt","Options");

        fileName << "cap" << screenNumber++ << "." << ext;

        captureScreen(fileName.str().c_str());
        return 0;
    }

    int TMokena::showHelp(Tubras::TSEvent event)
    {
        toggleHelpOverlay();
        return 0;
    }

    //
    // toggle the wireframe view
    //
    int TMokena::toggleWire(Tubras::TSEvent event)
    {
        toggleWireFrame();
        return 0;
    }

    //
    // toggle the debug overlay
    //
    int TMokena::toggleDebug(Tubras::TSEvent event)
    {
        toggleDebugOverlay();
        return 0;
    }

    //
    // toggle bounding boxes
    //
    int TMokena::toggleBBox(Tubras::TSEvent event)
    {
        getRenderEngine()->toggleBoundingBoxes();
        return 0;
    }

    //
    // initialize the event handlers and set up the text
    // that will appear on the help overlay
    //
    int initialize()
    {
        //
        // invoke TApplication initialize which initializes all of the
        // sub-systems (render, sound, input etc.)
        //
        if(TApplication::initialize())
            return 1;

        screenNumber = 1;

        //
        // key event handlers (delegates)
        //
        acceptEvent("key.down.sysrq",EVENT_DELEGATE(TMokena::saveScreen));
        acceptEvent("key.down.f12",EVENT_DELEGATE(TMokena::showConsole));
        acceptEvent("key.down.f1",EVENT_DELEGATE(TMokena::showHelp));
        acceptEvent("key.down.f2",EVENT_DELEGATE(TMokena::toggleWire));
        acceptEvent("key.down.f3",EVENT_DELEGATE(TMokena::toggleDebug));
        acceptEvent("key.down.f4",EVENT_DELEGATE(TMokena::toggleBBox));

        //
        // add help text to the help overlay
        //
        addHelpText("wasd - Camera movement");
        addHelpText("ec   - Elevate camera");
        addHelpText("m    - Toggle mouse control");
        addHelpText("i    - Invert mouse");
        addHelpText("F1   - Toggle help");
        addHelpText("F2   - Toggle wire");
        addHelpText("F3   - Toggle debug");
        addHelpText("F4   - Toggle bbox");
        addHelpText("F12  - Toggle console");
        toggleHelpOverlay();

        //
        // modify the GUI base theme colors
        //

        TGUI::TGTheme theme = getGUIManager()->getSystem()->getTheme();
        theme.getBase()->setColour(TGColour(0,0,0));
        theme.getBaseOpaque()->setColour(TGColour(0,0,0));
        theme.getTextBrush()->setColour(TGColour(1,1,1));
        theme.getFrameBrush()->setColour(TGColour(0.7f,0.7f,0));

        return 0;

    }

    //
    // override the applications createStates() to create our 
    // own individual states. If we chose not to override this, our 
    // application class derivative would be the only active state.
    //
    int createStates()
    {
        new TSplashState();
        new TMenuState();
        new TPlayState();
        new TOptionsState();
        new TPauseState();

        string istate = m_configFile->getSetting("InitialState","Options");
        if(istate.empty())
            istate = "splashState";
        setInitialState(istate);
        return 0;
    }

    //
    // override the applications createThemeClass() to return 
    // an instance of our theme subclass.
    //
    Tubras::TTheme* createThemeClass(string baseDir)
    {
        return new TTestTheme(baseDir);
    }

};

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

        TMokena app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;

    }

