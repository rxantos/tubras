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
#include "config.h"
#include "Evas.h"

#include <evas_common.h>
#include <evas_private.h>

#include "evas_test_main.h"

#include "Evas_Engine_Buffer.h"
#include "Evas_Engine.h"

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


    ptex = Ogre::TextureManager::getSingleton().createManual(
        "DynaTex","General", Ogre::TEX_TYPE_2D, win_w, win_h, 0, Ogre::PF_A8B8G8R8, 
        Ogre::TU_DYNAMIC_WRITE_ONLY);
	buffer = ptex->getBuffer(0, 0);

    // Create a material using the texture
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
        "DynamicTextureMaterial", // name
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    material->getTechnique(0)->getPass(0)->createTextureUnitState("DynaTex");
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureAddressingMode(Ogre::TextureUnitState::TAM_MIRROR);
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureRotate(Ogre::Radian(Ogre::Degree(90)));


    optex = Ogre::TextureManager::getSingleton().createManual(
        "DynaTex2","General", Ogre::TEX_TYPE_2D, win_w, win_h, 0, Ogre::PF_A8B8G8R8, 
        Ogre::TU_DYNAMIC_WRITE_ONLY);
	obuffer = optex->getBuffer(0, 0);

    // Create a material using the texture
    Ogre::MaterialPtr omaterial = Ogre::MaterialManager::getSingleton().create(
        "DynamicTextureMaterial2", // name
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    omaterial->getTechnique(0)->getPass(0)->createTextureUnitState("DynaTex2");
    omaterial->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    omaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureAddressingMode(Ogre::TextureUnitState::TAM_MIRROR);



    Tubras::TMaterial* mat = new TMaterial("planeMat","General");

    mat->setColor(TColour(1,0,0,1));
    mat->loadImage("grid.tga");
    mat->getMat()->setTextureFiltering(Ogre::TFO_TRILINEAR);
    mat->getMat()->setLightingEnabled(false);

    TPlaneNode* pn = new TPlaneNode("Viewer_ZXPlane",NULL,gridSize,TVector3::UNIT_Y);
    pn->setMaterialName("planeMat");
    pn->setPos(0,0,0);

    pn = new TPlaneNode("Viewer_YXPlane",NULL,20,TVector3::UNIT_Z);
    pn->setMaterialName("planeMat");
    pn->setPos(0,10,0);

    pn = new TPlaneNode("Viewer_YXPlane2",NULL,10,TVector3::UNIT_Z);
    pn->setMaterialName("DynamicTextureMaterial");
    pn->setPos(13,5,-8);

    pn = new TPlaneNode("Viewer_YXPlane3",NULL,40,TVector3::UNIT_Z);
    pn->setMaterialName("DynamicTextureMaterial");
    pn->setPos(-20,20,-25);

    Tubras::TDim dims(0.005,0.5,0.32,0.495);
    Tubras::TOverlay* o = new Tubras::TOverlay("Evas Overlay",dims,TColour::White,1.f,"DynamicTextureMaterial2",false);
    o->setVisible(true);
    o->setAlpha(0.95f);


    //
    // position the camera and enable movement
    //
    getCamera("Camera::Default")->setPos(TVector3(0,25,50));
    getCamera("Camera::Default")->lookAt(TVector3(0,0,-100));
    getCamera("Camera::Default")->enableMovement(true);
    setControllerEnabled("DefaultPlayerController",true);

    //
    // setup the evas buffer canvas
    //


    evas_init();
    evas = evas_new();
    evas_output_method_set(evas, evas_render_method_lookup("buffer"));

    Evas_Engine_Info_Buffer  *einfo;
    einfo = (Evas_Engine_Info_Buffer *) evas_engine_info_get(evas);
    einfo->info.depth_type = EVAS_ENGINE_BUFFER_DEPTH_RGB32;

    canvas_bufSize = win_w * win_h * 4;
    canvas_buf = (unsigned char *)malloc(canvas_bufSize);
    
    einfo->info.dest_buffer = canvas_buf;
    einfo->info.dest_buffer_row_bytes = win_w * 4;
    einfo->info.use_color_key = 0;
    evas_engine_info_set(evas, (Evas_Engine_Info *)einfo);
    evas_output_size_set(evas, win_w, win_h);
    evas_output_viewport_set(evas, 0, 0, win_w, win_h);

    setup();
    orig_start_time = start_time = get_time();



    return 0;
}

//
// invoked before "renderFrame" - evas buffer -> dynamic texture
//
void TEvasTest::preRender()
{
    loop();
    if(!evas->changed)
        return;

    evas_damage_rectangle_add(evas,0,0,win_w,win_h);
    
    evas_render(evas);

    buffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    Ogre::PixelBox &pb = (Ogre::PixelBox &)buffer->getCurrentLock();
    memcpy(pb.data,canvas_buf,canvas_bufSize);
    buffer->unlock();

    obuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    pb = (Ogre::PixelBox &)obuffer->getCurrentLock();
    memcpy(pb.data,canvas_buf,canvas_bufSize);
    obuffer->unlock();


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
