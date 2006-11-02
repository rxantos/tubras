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
#include "sandbox.h"
#include <stdlib.h>

TSandbox::TSandbox(int argc,char **argv) : TApplication(argc,argv,"Tubras Sandbox") 
{
    getApplication()->setGUIScheme("TaharezLookSkin.scheme","TaharezLook");
    getApplication()->setThemeDirectory("themes");
    m_deactivation = true;
    m_fireCount = 0;
    m_velocity = 65.0f;
}

TSandbox::~TSandbox()
{
	if(m_crosshair)
		delete m_crosshair;
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
    return 1;
}

int TSandbox::showHelp(Tubras::TSEvent event)
{
    toggleHelp();
    return 1;
}

//
// toggle the wireframe view
//
int TSandbox::toggleWire(Tubras::TSEvent event)
{
    getRenderEngine()->toggleWireframe();
    return 1;
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
    return 1;
}

//
// toggle physics debug
//
int TSandbox::togglePhysicsDebug(Tubras::TSEvent event)
{
    getDynamicWorld()->toggleDebug();
    return 1;
}

//
// toggle gravity
//
int TSandbox::toggleGravity(Tubras::TSEvent event)
{
    if(getDynamicWorld()->getGravity().y)
        getDynamicWorld()->setGravity(TVector3::ZERO);
    else getDynamicWorld()->setGravity(TVector3(0,-9.68f,0));
    return 1;
}

//
// toggle deactivation state
//
int TSandbox::toggleDeactivation(Tubras::TSEvent event)
{
    if(m_deactivation)
        getDynamicWorld()->allowDeactivation(false);
    else getDynamicWorld()->allowDeactivation(true);
    m_deactivation = m_deactivation ? false : true;
    return 1;
}

int TSandbox::adjustFireVelocity(Tubras::TSEvent event)
{
    char buf[128];
    int dir = (int)event->getUserData();
    m_velocity += ((float)dir * 5.0f);

    sprintf(buf,"Fire Velocity: %.1f m/s",m_velocity);
    getPhysicsManager()->setUserDebugString(buf);
    return 1;
}


//
// fire a physics node
//
int TSandbox::fire(Tubras::TSEvent event)
{
    TStrStream str;
    TModelNode* m_object;
    TVector3 pos;
    TColliderShape* cshape;

    if(isKeyDown(OIS::KC_LCONTROL))
    {
        m_object = loadModel("Ball.mesh");
        pos = getCamera("Camera::Default")->getPos();
        TColliderSphere* shape = new TColliderSphere(m_object->getEntity()->getBoundingBox());
        cshape = shape;
    }
    else
    {
        m_object = loadModel("Cube.mesh");
        pos = getCamera("Camera::Default")->getPos();
        TColliderBox* shape = new TColliderBox(m_object->getEntity()->getBoundingBox());
        cshape = shape;
    }

    TVector3 direction = getCamera("Camera::Default")->getDerivedOrientation().zAxis();
    direction.normalise();

	//
	// start the object in front of the camera so it doesn't collide with the camera collider
	//
	pos -= (direction * 2.0);
    m_object->setPos(pos);

    TDynamicNode* pnode = new TDynamicNode(m_object->getName() + "::pnode",m_object,cshape,1.0);
    TVector3 vel = direction * -1.0f;
    pnode->getRigidBody()->setLinearVelocity(vel*m_velocity);
    pnode->getRigidBody()->setRestitution(1.0);
    pnode->getRigidBody()->setFriction(5.0);
    m_fire->play();

    ++m_fireCount;

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
    acceptEvent("key.down.f5",EVENT_DELEGATE(TSandbox::togglePhysicsDebug));
    acceptEvent("key.down.f6",EVENT_DELEGATE(TSandbox::toggleGravity));
    acceptEvent("key.down.f7",EVENT_DELEGATE(TSandbox::toggleDeactivation));
    acceptEvent("input.mouse.down.1",EVENT_DELEGATE(TSandbox::fire));
    acceptEvent("key.down.esc",EVENT_DELEGATE(TSandbox::quitApp));

    TEventDelegate* edp = EVENT_DELEGATE(TSandbox::adjustFireVelocity);
    acceptEvent("key.down.subtract",edp,(void *)-1);
    acceptEvent("key.down.add",edp,(void *)1);



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
    toggleHelp();

    //
    // turn gravity on
    //
    getDynamicWorld()->setGravity(TVector3(0,-9.68f,0));


    //
    // load a static node (no mass)
    //
    m_cube = loadModel("Cube.mesh");
    m_cube->setPos(Ogre::Vector3(0,8,0));
    TColliderBox* boxShape = new TColliderBox(m_cube->getEntity()->getBoundingBox());
    TDynamicNode* pnode = new TDynamicNode(m_cube->getName() + "::pnode",m_cube,boxShape,0.0);

    //
    // load dynamic nodes
    //
    m_cube = loadModel("Cube.mesh");
    m_cube->setPos(Ogre::Vector3(0,20,0));
    boxShape = new TColliderBox(m_cube->getEntity()->getBoundingBox());
    pnode = new TDynamicNode(m_cube->getName() + "::pnode",m_cube,boxShape,5.0);

    m_cube = loadModel("Cube.mesh");
    m_cube->setPos(Ogre::Vector3(1,22,0));
    boxShape = new TColliderBox(m_cube->getEntity()->getBoundingBox());
    pnode = new TDynamicNode(m_cube->getName() + "::pnode",m_cube,boxShape,3.0);

    m_ball = loadModel("Ball.mesh");
    m_ball->setPos(TVector3(0,5,0));
    TColliderSphere* sphereShape = new TColliderSphere(m_ball->getEntity()->getBoundingBox());
    pnode = new TDynamicNode(m_ball->getName() + "::pnode",m_ball,sphereShape,1.0);
    pnode->getRigidBody()->setRestitution(1.0);

    //
    // create plane grid
    //
    size_t gridSize=200;

    Tubras::TMaterial* mat = new TMaterial("planeMat","General");

    mat->setColor(TColor(1,0,0,1));
    mat->loadImage("grid.tga");
    mat->getMat()->setTextureFiltering(Ogre::TFO_TRILINEAR);
	mat->getMat()->setLightingEnabled(false);

    TPlaneNode* pn = new TPlaneNode("Viewer_ZXPlane",NULL,gridSize,TVector3::UNIT_Y);
    pn->setMaterialName("planeMat");
    pn->setPos(0,0,0);

    TColliderMesh* meshShape = new TColliderMesh(pn);
    pnode = new TDynamicNode("Viewer_ZXPlane::pnode",pn,meshShape,0.0f);
    pnode->getRigidBody()->setFriction(25.0);

    //
    // position the camera and enable movement
    //
    getCamera("Camera::Default")->setPos(TVector3(0,25,50));
    getCamera("Camera::Default")->lookAt(TVector3(0,0,-100));
    getCamera("Camera::Default")->enableMovement(true);
    setControllerEnabled("DefaultInputController",true);
    //boxShape = new TColliderBox(TAABox(TVector3(-1,-1,-1),TVector3(1,1,1)));
    //pnode = new TDynamicNode("Camera::pnode",getCamera("Camera::Default"),boxShape,5.0,true);


    //
    // create crosshair overlay
    //

    mat = new TMaterial("matCrossHair","General");
    mat->loadImage("crosshair1.png");
    mat->setDepthCheckEnabled(false);
    mat->setDepthWriteEnabled(false);

    m_crosshair = new TOverlay("crosshair",TDim(0.46,0.46,0.08,0.1),TColor::White,1.0,"matCrossHair");
    m_crosshair->setVisible(true);

    //
    // load the "fire" sound
    //
    m_fire = loadSound("cannon.ogg");

    char buf[128];
    sprintf(buf,"Fire Velocity: %.1f m/s",m_velocity);
    getPhysicsManager()->setUserDebugString(buf);


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
