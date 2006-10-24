//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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
#include "sandbox.h"
#include <stdlib.h>

TSandbox::TSandbox(int argc,char **argv) : TApplication(argc,argv,"Tubras Sandbox") 
{
    getApplication()->setGUIScheme("TaharezLookSkin.scheme","TaharezLook");
    getApplication()->setThemeDirectory("themes");
}

TSandbox::~TSandbox()
{
}

//
// exit the sandbox application
//
int TSandbox::quitApp(TSEvent event)
{
    stopRunning();
    return 1;
}

//
// show/hide the console
//
int TSandbox::showConsole(Tubras::TSEvent event)
{
    toggleConsole();
    return 1;
}

//
// take a screen shot of our window.
//
int TSandbox::saveScreen(Tubras::TSEvent event)
{

    TStrStream fileName;
    string ext;

    ext = getConfigFile()->getSetting("ScreenCapExt","Options");

    fileName << "cap" << screenNumber++ << "." << ext;

    captureScreen(fileName.str().c_str());
    return 0;
}

int TSandbox::showHelp(Tubras::TSEvent event)
{
    toggleHelp();
    return 0;
}

//
// toggle the wireframe view
//
int TSandbox::toggleWire(Tubras::TSEvent event)
{
    getRenderEngine()->toggleWireframe();
    return 0;
}

//
// toggle the debug overlay
//
int TSandbox::toggleDebug(Tubras::TSEvent event)
{
    toggleDebugOverlay();
    return 0;
}

//
// toggle bounding boxes
//
int TSandbox::toggleBBox(Tubras::TSEvent event)
{
    getRenderEngine()->toggleBoundingBoxes();
    return 0;
}

//
// initialize the event handlers and set up the text
// that will appear on the help overlay
//
int TSandbox::initialize()
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
    acceptEvent("key.down.sysrq",EVENT_DELEGATE(TSandbox::saveScreen));
    acceptEvent("key.down.f12",EVENT_DELEGATE(TSandbox::showConsole));
    acceptEvent("key.down.f1",EVENT_DELEGATE(TSandbox::showHelp));
    acceptEvent("key.down.f2",EVENT_DELEGATE(TSandbox::toggleWire));
    acceptEvent("key.down.f3",EVENT_DELEGATE(TSandbox::toggleDebug));
    acceptEvent("key.down.f4",EVENT_DELEGATE(TSandbox::toggleBBox));
    acceptEvent("key.down.esc",EVENT_DELEGATE(TSandbox::quitApp));


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
    toggleHelp();

    //
    // load a cube
    //
    m_cube = loadModel("Cube", "General", "Cube.mesh", NULL);
    m_cube->setPos(Ogre::Vector3(0,0,0));

    //
    // decomposer test
    //
    TNodeDecomposer* nd = new TNodeDecomposer();
    nd->decompose(m_cube);
    delete nd;


    //
    // create plane grid
    //
    size_t gridSize=200;

    Tubras::TMaterial* mat = new TMaterial("planeMat","General");

    mat->setColor(TColor(1,0,0,1));
    mat->loadImage("grid.tga");
    mat->getMat()->setTextureFiltering(Ogre::TFO_TRILINEAR);

    TPlaneNode* pn = new TPlaneNode("Viewer_ZXPlane",NULL,200,TVector3::UNIT_Y);
    pn->setMaterialName("planeMat");

    pn->setPos(0,-5,0);

    //
    // position the camera and enable movement
    //
    getRenderEngine()->getCamera("Camera::Default")->setPos(TVector3(0,25,50));
    getRenderEngine()->getCamera("Camera::Default")->lookAt(TVector3(0,0,-100));
    getRenderEngine()->getCamera("Camera::Default")->enableMovement(true);
    setControllerEnabled("DefaultInputController",true);

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

        TSandbox app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;

    }
