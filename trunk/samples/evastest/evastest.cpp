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
#include "evastest.h"
#include <stdlib.h>

TEvasTest::TEvasTest(int argc,char **argv) : TApplication(argc,argv,"Tubras Sandbox") 
{
    getApplication()->setThemeDirectory("themes");
    m_deactivation = true;
    m_velocity = 65.0f;
}

TEvasTest::~TEvasTest()
{
}

//
// exit the sandbox application
//
int TEvasTest::quitApp(TSEvent event)
{
    stopRunning();
    return 1;
}

//
// show/hide the console
//
int TEvasTest::showConsole(Tubras::TSEvent event)
{
    toggleConsole();
    return 1;
}

//
// take a screen shot of our window.
//
int TEvasTest::saveScreen(Tubras::TSEvent event)
{

    TStrStream fileName;
    string ext;

    ext = getConfigFile()->getSetting("ScreenCapExt","Options");

    fileName << "cap" << screenNumber++ << "." << ext;

    captureScreen(fileName.str().c_str());
    return 1;
}

int TEvasTest::showHelp(Tubras::TSEvent event)
{
    toggleHelpOverlay();
    return 1;
}

//
// toggle the wireframe view
//
int TEvasTest::toggleWire(Tubras::TSEvent event)
{
    toggleWireFrame();
    return 1;
}

//
// toggle the debug overlay
//
int TEvasTest::toggleDebug(Tubras::TSEvent event)
{
    toggleDebugOverlay();
    return 0;
}

//
// toggle bounding boxes
//
int TEvasTest::toggleBBox(Tubras::TSEvent event)
{
    getRenderEngine()->toggleBoundingBoxes();
    return 1;
}


void TEvasTest::setUserDebugInfo(TStringVector& debugStrings)
{
    debugStrings.push_back("Debug Data 1");
    debugStrings.push_back("Debug Data 2");
}

//
// initialize the event handlers and set up the text
// that will appear on the help overlay
//
int TEvasTest::initialize()
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
    acceptEvent("key.down.sysrq",EVENT_DELEGATE(TEvasTest::saveScreen));
    acceptEvent("key.down.f12",EVENT_DELEGATE(TEvasTest::showConsole));
    acceptEvent("key.down.f1",EVENT_DELEGATE(TEvasTest::showHelp));
    acceptEvent("key.down.f2",EVENT_DELEGATE(TEvasTest::toggleWire));
    acceptEvent("key.down.f3",EVENT_DELEGATE(TEvasTest::toggleDebug));
    acceptEvent("key.down.f4",EVENT_DELEGATE(TEvasTest::toggleBBox));
    acceptEvent("key.down.f12",EVENT_DELEGATE(TEvasTest::showConsole));
    acceptEvent("key.down.esc",EVENT_DELEGATE(TEvasTest::quitApp));

    setGUIEnabled(false);
    setGUICursorVisible(false);


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
    addHelpText("F5   - Toggle physics debug");
    addHelpText("F6   - Toggle gravity");
    addHelpText("F7   - Toggle Deactivation");
    addHelpText("F12  - Toggle console");
    toggleHelpOverlay();

    //
    // turn gravity on
    //
    getDynamicWorld()->setGravity(TVector3(0,-9.68f,0));

    //
    // create plane grid
    //
    size_t gridSize=200;

    Tubras::TMaterial* mat = new TMaterial("planeMat","General");

    mat->setColor(TColour(1,0,0,1));
    mat->loadImage("grid.tga");
    mat->getMat()->setTextureFiltering(Ogre::TFO_TRILINEAR);
    mat->getMat()->setLightingEnabled(false);

    TPlaneNode* pn = new TPlaneNode("Viewer_ZXPlane",NULL,gridSize,TVector3::UNIT_Y);
    pn->setMaterialName("planeMat");
    pn->setPos(0,0,0);

    //
    // position the camera and enable movement
    //
    getCamera("Camera::Default")->setPos(TVector3(0,25,50));
    getCamera("Camera::Default")->lookAt(TVector3(0,0,-100));
    getCamera("Camera::Default")->enableMovement(true);
    setControllerEnabled("DefaultPlayerController",true);

    return 0;
}

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

        TEvasTest app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;

    }
