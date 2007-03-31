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
    getApplication()->setThemeDirectory("themes");
    m_deactivation = true;
    m_fireCount = 0;
    m_velocity = 65.0f;
    m_debugRay = 0;
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

void TSandbox::setUserDebugInfo(TStringVector& debugStrings)
{
    debugStrings.push_back("Debug Data 1");
    debugStrings.push_back("Debug Data 2");
}

//
// object picking
//
int TSandbox::mousePick(Tubras::TSEvent event)
{

    size_t x,y;
    //
    // shoot from the center of the screen (cross-hair)
    //
    getRenderEngine()->getDisplaySize(x,y);
    x /= 2;
    y /= 2;
    y += 7;         // offset for cross-hair center
    TStrStream str;
    str << "LButton Down: x(" << x << ") y(" << y << ")";
    logMessage(str.str().c_str());

    TCameraNode* pCam = getCamera("Camera::Default");
    TRay ray = pCam->getRay((int)x,(int)y, 1000.f);

    if(m_debugRay)
        delete m_debugRay;
   
    TColor  yellow(1.f,1.f,0.f,1.f);
    m_debugRay = new TLineNode("debugRay",0,ray.getOrigin(),ray.getEndPoint(),yellow);

    TRayResult res = getDynamicWorld()->rayTest(ray);
    if(res.hasHit())
    {
        TDynamicNode* pdn=res.getCollisionNode();
        if(getDebug())
        {
            TString name = pdn->getName();
            TStrStream msg;
            msg << "rayTest Hit: " << name;
            logMessage(msg.str().c_str());
        }

        pdn->setActivationState(ACTIVE_TAG);
        TVector3 impulse = ray.getEndPoint();
        impulse.normalise();
        float impulseStrength = 12.f;
        impulse *= impulseStrength;
        TVector3 relPos = res.getHitPointWorld() - pdn->getCenterOfMassPosition();
        pdn->applyImpulse(impulse,relPos);        
    }

    m_shot->play();
    return 0;
}

int TSandbox::mousePickUp(Tubras::TSEvent event)
{

    if(m_debugRay)
    {
        delete m_debugRay;
        m_debugRay = 0;
    }

    return 0;
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
        TColliderSphere* shape = new TColliderSphere(m_object->getEntity()->getBoundingBox());
        cshape = shape;
    }
    else
    {
        m_object = loadModel("Cube.mesh");
        TColliderBox* shape = new TColliderBox(m_object->getEntity()->getBoundingBox());
        cshape = shape;
    }

    pos = getCamera("Camera::Default")->getPos();
    TVector3 direction = getCamera("Camera::Default")->getDerivedOrientation().zAxis();
    direction.normalise();

    //
    // start the object in front of the camera so it doesn't collide with the camera collider
    //
    pos -= (direction * 2.0);
    m_object->setPos(pos);
    m_object->setOrientation(getCamera("Camera::Default")->getOrientation());

    TDynamicNode* pnode = new TDynamicNode(m_object->getName() + "::pnode",m_object,cshape,1.0);
    TVector3 vel = direction * -1.0f;
    pnode->setLinearVelocity(vel*m_velocity);

    pnode->setRestitution(0.0);
    pnode->setFriction(1.0);
    pnode->setDamping(0.2,0.2);
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
    acceptEvent("key.down.f12",EVENT_DELEGATE(TSandbox::showConsole));
    acceptEvent("input.mouse.down.0",EVENT_DELEGATE(TSandbox::mousePick));
    acceptEvent("input.mouse.up.0",EVENT_DELEGATE(TSandbox::mousePickUp));
    acceptEvent("input.mouse.down.1",EVENT_DELEGATE(TSandbox::fire));
    acceptEvent("key.down.esc",EVENT_DELEGATE(TSandbox::quitApp));

    TEventDelegate* edp = EVENT_DELEGATE(TSandbox::adjustFireVelocity);
    acceptEvent("key.down.subtract",edp,(void *)-1);
    acceptEvent("key.down.add",edp,(void *)1);

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
    toggleHelp();

    //
    // turn gravity on
    //
    getDynamicWorld()->setGravity(TVector3(0,-9.68f,0));


    //
    // create a kinematic node and attach controllers
    //
    m_cube = loadModel("Cube.mesh");
    m_cube->setPos(TVector3(0,8,0));
    TColliderShape* shape = new TColliderBox(m_cube);
    TDynamicNode* pnode = new TDynamicNode("cube1::pnode",m_cube,shape,0.0,btKinematic);
    pnode->allowDeactivation(false);

    TSound* sound = loadSound("whirl_mono.ogg","General",true);
    TSoundNode* snode = new TSoundNode("Cube::snode",m_cube,sound);

    sound->set3DMinDistance(2.0);
    sound->setLoop(true);
    sound->play();
    setSoundListener(getCamera("Camera::Default"));

    new Tubras::TRotateController("cube3::rotatorx",m_cube,200.0,TVector3::UNIT_X);
    new Tubras::TRotateController("cube3::rotatorz",m_cube,250.0,TVector3::UNIT_Z);
    new Tubras::TOscillateController("cube3::oscillator",m_cube,0.45,3.5);

    m_cube = loadModel("Cube.mesh");
    m_cube->setPos(TVector3(10,8,0));
    TQuaternion q(TDegree(-360),TVector3::UNIT_Y);
    m_cube->setOrientation(q);

    //
    // load dynamic nodes
    //

    m_cube = loadModel("Cube.mesh");
    m_cube->setPos(TVector3(0,20,0));
    shape = new TColliderBox(m_cube);
    pnode = new TDynamicNode("cube2::pnode",m_cube,shape,5.0);

    m_cube = loadModel("Cube.mesh");
    m_cube->setPos(TVector3(1,22,0));
    shape = new TColliderBox(m_cube);
    pnode = new TDynamicNode("curb3::pnode",m_cube,shape,3.0);
    pnode->setRestitution(1.0);

    m_ball = loadModel("Ball.mesh");
    m_ball->setPos(TVector3(0,5,0));
    shape = new TColliderSphere(m_ball);
    pnode = new TDynamicNode("ball::pnode",m_ball,shape,1.0);
    pnode->setRestitution(0.0);
    pnode->setDamping(0.2,0.2);

    
    m_ball = loadModel("martina.mesh");
    m_ball->setPos(TVector3(-5,35,0));
    shape = new TColliderBox(m_ball);
    pnode = new TDynamicNode("Martina::pnode",m_ball,shape,1.0,btKinematic,TVector3(0,1.9f,0));
    pnode->allowDeactivation(false);
    m_lmc = new TLinMovController(m_ball,pnode);
    
    m_lmc->setVelocity(TVector3(0,0,6.f));
    m_lmc->setAngularVelocity(8.f);
    m_lmc->enableHugging(true);

    
    m_ball = loadModel("martina.mesh");
    m_ball->setPos(TVector3(5,0,-10));
    shape = new TColliderBox(m_ball);
    pnode = new TDynamicNode("Martina2::pnode",m_ball,shape,1.0,btKinematic,TVector3(0,1.95f,0));
    pnode->allowDeactivation(false);

    sound = loadSound("cocktail.ogg","General",true);
    new TSoundNode("Martina2::snode",m_ball,sound);
    sound->set3DMinDistance(1.0);
    sound->setLoop(true);
    sound->play();

    m_lmc = new TLinMovController(m_ball,pnode);
    m_lmc->setVelocity(TVector3(0,0,2.f));
    m_lmc->setAngularVelocity(-4.f);
    

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
    pnode->setFriction(1);
    pnode->setRestitution(0.0);

    //
    // position the camera and enable movement
    //
    getCamera("Camera::Default")->setPos(TVector3(0,25,50));
    getCamera("Camera::Default")->lookAt(TVector3(0,0,-100));
    getCamera("Camera::Default")->enableMovement(true);
    setControllerEnabled("DefaultPlayerController",true);

    shape = new TColliderCylinder(TVector3(1,2.5,1));
    pnode = new TDynamicNode("Camera::pnode",getCamera("Camera::Default"),shape,1.0,btKinematic);
    pnode->setRestitution(1.0);
    pnode->getRigidBody()->getBulletRigidBody()->setHitFraction(0.0);
    pnode->allowDeactivation(false);



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
    m_shot = loadSound("singleshot.ogg");

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
