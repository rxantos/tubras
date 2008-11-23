//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "sandbox.h"
#define GID_QUIT 101

//-----------------------------------------------------------------------
//                           T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::TSandbox() : TApplication("sandbox"),
m_screen(0), m_fireCount(0), m_velocity(50.f), m_irrInfo(0),
m_bulletInfo(0)
{
}

//-----------------------------------------------------------------------
//                          ~ T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::~TSandbox()
{
    if(m_screen)
        m_screen->drop();
    if(m_irrInfo)
        delete m_irrInfo;
    if(m_bulletInfo)
        delete m_bulletInfo;
#ifdef _DEBUG
    m_dumpMemoryReport();
#endif
}

//-----------------------------------------------------------------------
//                        t o g g l e H e l p
//-----------------------------------------------------------------------
int TSandbox::toggleHelp(const TEvent* event)
{
    toggleHelpOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e D e b u g
//-----------------------------------------------------------------------
int TSandbox::toggleDebug(const TEvent* event)
{
    toggleDebugOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                        c y c l e D e b u g
//-----------------------------------------------------------------------
int TSandbox::cycleDebug(const TEvent* event)
{
    cycleDebugData();
    return 1;
}

//-----------------------------------------------------------------------
//                 t o g g l e P h y s i c s D e b u g
//-----------------------------------------------------------------------
int TSandbox::togglePhysicsDebug(const TEvent* event)
{
    TApplication::togglePhysicsDebug();
    return 1;
}

//-----------------------------------------------------------------------
//                      c a p t u r e S c r e e n
//-----------------------------------------------------------------------
int TSandbox::captureScreen(const TEvent* event)
{
    getRenderer()->captureScreen();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e T r a n s f o r m
//-----------------------------------------------------------------------
int TSandbox::toggleTransform(const TEvent* event)
{
    if(m_irrInfo->getVisible())
    {
        m_infoTask->stop();
        m_irrInfo->setVisible(false);
        m_bulletInfo->setVisible(false);
    }
    else
    {
        m_infoTask->start();
        m_irrInfo->setVisible(true);
        m_bulletInfo->setVisible(true);
    }
    return 0;
}


//-----------------------------------------------------------------------
//                        t o g g l e W i r e
//-----------------------------------------------------------------------
int TSandbox::toggleWire(const TEvent* event)
{
    TRenderMode mode = getRenderMode();

    if(mode == rmNormal)
        setRenderMode(rmWire);
    else if(mode == rmWire)
        setRenderMode(rmPointCloud);
    else if(mode == rmPointCloud)
        setRenderMode(rmNormal);

    return 1;
}


//-----------------------------------------------------------------------
//                             o n C l i c k
//-----------------------------------------------------------------------
int TSandbox::onClick(const TEvent* event)
{
    int result = 0;


    int id = ((TEvent*)event)->getParameter(0)->getIntValue();

    if(id == GID_QUIT)
    {
        stopRunning();
        result = 1;
    }

    return result;
}


//-----------------------------------------------------------------------
//                             q u i t
//-----------------------------------------------------------------------
int TSandbox::quit(const TEvent* event)
{
    TApplication::stopRunning();
    return 1;
}

//-----------------------------------------------------------------------
//                       t e s t I n t e r v a l
//-----------------------------------------------------------------------
void TSandbox::testInterval(double T, void* userData)
{
    char buf[100];
    sprintf(buf,"testInterval T: %.3f",T);
    logMessage(buf);
}

//-----------------------------------------------------------------------
//                      O n R e a d U s e r D a t a
//-----------------------------------------------------------------------
void TSandbox::OnReadUserData(ISceneNode* forSceneNode, 
                              io::IAttributes* userData)
{
    bool value=false;

    if(userData->existsAttribute("collider"))
        value = userData->getAttributeAsBool("collider");

    if(value)
    {
        ESCENE_NODE_TYPE type = forSceneNode->getType();
        if(type == ESNT_MESH)
        {
            IMeshSceneNode* mnode = 
                reinterpret_cast<IMeshSceneNode*>(forSceneNode);
            TColliderMesh* cm = new TColliderMesh(mnode->getMesh());
            new TDynamicNode("testCollider",forSceneNode,cm);
            //
            // do mnode->remove() later...
            //
            mnode->setVisible(false);                       
        }
    }
}

//-----------------------------------------------------------------------
//                           s h o o t R a y
//-----------------------------------------------------------------------
int TSandbox::shootRay(const TEvent* event)
{
    if(((TEvent*)event)->getID() == m_upID)
    {
        m_shooterLine->setVisible(false);
        return 0;
    }
    //
    // shoot from the center of the screen
    //
    TDimension screenSize = getRenderer()->getVideoDriver()->
        getScreenSize();
    position2d<s32> pos;
    pos.X = screenSize.Width/2;
    pos.Y = screenSize.Height/2;
    
    TRay ray(pos,getActiveCamera());
    m_shooterLine->set(ray.start,ray.end,TColour(255,255,0));
    m_shooterLine->setVisible(true);

    TRayResult res = getPhysicsManager()->getWorld()->rayTest(ray);
    if(res.hasHit())
    {
        TDynamicNode* pdn=res.getCollisionNode();
        if(getDebug())
        {
            TStrStream msg;
            msg << "rayTest Hit: " << pdn->getName().c_str();
            logMessage(msg.str().c_str());
        }

        pdn->setActivationState(ACTIVE_TAG);
        TVector3 impulse = ray.getEndPoint();
        impulse.normalize();
        float impulseStrength = 12.f;
        impulse *= impulseStrength;
        TVector3 cmPos;
        pdn->getCenterOfMassPosition(cmPos);
        TVector3 relPos = res.getHitPointWorld() - cmPos;
        pdn->applyImpulse(impulse,relPos);        
    }
    m_shot->play();


    return 0;
}

//-----------------------------------------------------------------------
//                          s h o o t N o d e
//-----------------------------------------------------------------------
int TSandbox::shootNode(const TEvent* event)
{
    
    TStrStream str;
    ISceneNode* m_object;
    TVector3 pos,direction;
    TColliderShape* cshape;

    if(getInputManager()->isKeyDown(OIS::KC_LCONTROL))
    {
        m_object = loadModel("mdl/Ball.irrmesh");
        TColliderSphere* shape = new TColliderSphere(m_object);
        cshape = shape;
    }
    else
    {
        m_object = loadModel("mdl/Cube.irrmesh");
        TColliderBox* shape = new TColliderBox(m_object);
        cshape = shape;
    }

    TRenderMode renderMode = getRenderer()->getRenderMode();
    if(m_object->getMaterialCount())
    {
        for(u32 idx=0;idx<m_object->getMaterialCount();idx++)
        {
            SMaterial& mat = m_object->getMaterial(idx);

            switch(renderMode)
            {
            case rmNormal:
                mat.setFlag(EMF_WIREFRAME,false);
                mat.setFlag(EMF_POINTCLOUD,false);
                break;
            case rmWire:
                mat.setFlag(EMF_WIREFRAME,true);
                mat.setFlag(EMF_POINTCLOUD,false);
                break;
            case rmPointCloud:
                mat.setFlag(EMF_WIREFRAME,false);
                mat.setFlag(EMF_POINTCLOUD,true);
                break;
            }
        }
    }

    ICameraSceneNode* cam = getActiveCamera();
    pos = cam->getPosition();
    direction = cam->getTarget() - pos;
    direction.normalize();

    //
    // start the object in front of the camera so it doesn't
    // collide with the camera collider
    //
    pos += (direction * 2.0);
    m_object->setPosition(pos);
    TMatrix4 mat4 = cam->getAbsoluteTransformation();
    TVector3 rot = mat4.getRotationDegrees();
    if(rot.Z > 0.f)
        rot = -rot;    

    m_object->setRotation(rot);
    

    TDynamicNode* pnode = new TDynamicNode("default",
        m_object,cshape,1.0);
    pnode->setLinearVelocity(direction*m_velocity);

    pnode->setRestitution(0.f);
    pnode->setFriction(1.0);
    pnode->setDamping(0.2f,0.2f);
    ++m_fireCount;

    m_fire->play();

    return 0;
}

//-----------------------------------------------------------------------
//                       s e t u p M a t r i x I n f o
//-----------------------------------------------------------------------
void TSandbox::setupMatrixInfo()
{
    IGUIFont* font = getGUIManager()->getFont("monospace.xml");

    m_irrInfo = new TTextOverlay("IrrlichtInfo",
        TRect(0.005f,0.70f,0.295f,0.505f));
    m_irrInfo->setVisible(true);
    if(font)
        m_irrInfo->setFont(font);
    m_irrInfo->addItem("Irrlicht Transform Info", taCenter); 
    m_irrInfo->addItem(" ");
    m_irrInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_irrInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_irrInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_irrInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_irrInfo->addItem(" ");
    m_irrInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_irrInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_irrInfo->addItem(" 000.00 000.00 000.00 000.00");

    m_bulletInfo = new TTextOverlay("IrrlichtInfo",
        TRect(0.305f,0.70f,0.595f,0.505f));
    m_bulletInfo->setVisible(true);
    if(font)
        m_bulletInfo->setFont(font);
    m_bulletInfo->addItem("Bullet Transform Info", taCenter); 
    m_bulletInfo->addItem(" ");
    m_bulletInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_bulletInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_bulletInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_bulletInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_bulletInfo->addItem(" ");
    m_bulletInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_bulletInfo->addItem(" 000.00 000.00 000.00 000.00");
    m_bulletInfo->addItem(" 000.00 000.00 000.00 000.00");

    m_infoTask = new TTask("updateMatInfo",
        TASK_DELEGATE(TSandbox::updateMatInfo));
    m_irrInfo->setVisible(false);
    m_bulletInfo->setVisible(false);
}

//-----------------------------------------------------------------------
//                      u p d a t e M a t I n f o
//-----------------------------------------------------------------------
int TSandbox::updateMatInfo(TTask* task)
{
    if(task->m_elapsedTime >= 500)
    {
        ICameraSceneNode* cam = getActiveCamera();

        TMatrix4 mat = cam->getAbsoluteTransformation();

        f32* m = mat.pointer();

        char buf[100];
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",m[0],m[1],m[2],m[3]);
        m_irrInfo->updateItem(2,buf);

        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",m[4],m[5],m[6],m[7]);
        m_irrInfo->updateItem(3,buf);

        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",m[8],m[9],m[10],m[11]);
        m_irrInfo->updateItem(4,buf);

        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",m[12],m[13],m[14],m[15]);
        m_irrInfo->updateItem(5,buf);

        TQuaternion q(mat);

        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",q.X, q.Y, q.Z, q.W);
        m_irrInfo->updateItem(7,buf);

        TVector3 e;
        q.toEuler(e);
        // hpr : heading(yaw), pitch, roll
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",e.Y, e.X, e.Z, 0.f);
        m_irrInfo->updateItem(8,buf);

        q.toEulerDegrees(e);
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",e.Y, e.X, e.Z, 0.f);
        m_irrInfo->updateItem(9,buf);


        btTransform trans;
        TIBConvert::IrrToBullet(mat,trans);
        btMatrix3x3 mat3 = trans.getBasis();
        btVector3 v = mat3.getRow(0);
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",v.getX(), v.getY(), 
            v.getZ(), 0.f);
        m_bulletInfo->updateItem(2,buf);

        v = mat3.getRow(1);
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",v.getX(), v.getY(), 
            v.getZ(), 0.f);
        m_bulletInfo->updateItem(3,buf);

        v = mat3.getRow(2);
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",v.getX(), v.getY(), 
            v.getZ(), 0.f);
        m_bulletInfo->updateItem(4,buf);

        v = trans.getOrigin();
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",v.getX(), v.getY(), 
            v.getZ(), 1.f);
        m_bulletInfo->updateItem(5,buf);

        btQuaternion bq = trans.getRotation();
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",bq.getX(),bq.getY(),
            bq.getZ(),bq.getW());
        m_bulletInfo->updateItem(7,buf);

        btScalar yaw,pitch,roll;
        trans.getBasis().getEulerYPR(yaw,pitch,roll);
        sprintf(buf," %6.2f %6.2f %6.2f %6.2f",yaw,pitch,roll,0.f);
        m_bulletInfo->updateItem(8,buf);

        task->m_elapsedTime = 0;
    }

    return TTask::cont;
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TSandbox::initialize()
{
    if(TApplication::initialize())
        return 1;
    
    //
    // add text to the help panel
    //
    addHelpText("wasd - Camera movement");
    addHelpText("   i - Invert mouse");
    addHelpText(" prt - Screen capture");
    addHelpText("  F1 - Toggle help");
    addHelpText("  F2 - Toggle debug");
    addHelpText("  F3 - Cycle wire/pts");
    addHelpText("  F4 - Toggle Phys dbg");
    addHelpText("  F5 - Cycle dbg data");
    addHelpText("  F6 - Toggle Xform");

    setupMatrixInfo();

    //
    // specify the events we want notifications for
    //
    acceptEvent("help",EVENT_DELEGATE(TSandbox::toggleHelp));
    acceptEvent("idbg",EVENT_DELEGATE(TSandbox::toggleDebug));      
    acceptEvent("wire",EVENT_DELEGATE(TSandbox::toggleWire));  
    acceptEvent("pdbg",EVENT_DELEGATE(TSandbox::togglePhysicsDebug));      
    acceptEvent("cdbg",EVENT_DELEGATE(TSandbox::cycleDebug));
    acceptEvent("xfrm",EVENT_DELEGATE(TSandbox::toggleTransform));
    acceptEvent("sprt",EVENT_DELEGATE(TSandbox::captureScreen));
    acceptEvent("quit",EVENT_DELEGATE(TSandbox::quit));  
    acceptEvent("gui.clicked",EVENT_DELEGATE(TSandbox::onClick));
    acceptEvent("input.mouse.down.right",EVENT_DELEGATE(TSandbox::shootNode));
    acceptEvent("input.mouse.down.left",EVENT_DELEGATE(TSandbox::shootRay));
    m_upID = acceptEvent("input.mouse.up.left",EVENT_DELEGATE(TSandbox::shootRay));

    //
    // create background node
    //
    TBackgroundNode* bgNode = (TBackgroundNode*)getSceneManager()->addSceneNode("TBackgroundNode");
    bgNode->initialize();
    getRenderer()->setBackgroundNode(bgNode);

    //
    // setup the "floor" mesh & material, collider
    //
    TDynamicNode* dnode;

    SMaterial mat;
    ITexture* tex = getTexture("tex/grid.tga");
    mat.setTexture(0,tex);
    mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    mat.setFlag(EMF_LIGHTING,false);
    mat.getTextureMatrix(0).setTextureScale(50.0,50.0);

    TDimensionf tileSize(50,50);
    TDimensionu tileCount(6,6);
    IAnimatedMesh* pmesh = getSceneManager()->addHillPlaneMesh("testHillPlane"
        ,tileSize,tileCount,&mat);
   
    IAnimatedMeshSceneNode* pnode;
    pnode = getSceneManager()->addAnimatedMeshSceneNode(pmesh);

    TColliderMesh* planeShape = new TColliderMesh(pnode->getMesh());
    dnode = new TDynamicNode("Viewer_ZXPlane::pnode",pnode,
        planeShape,0.0f,btStatic);
    //dnode->allowDeactivation(false);

    dnode->setFriction(1.2f);
    dnode->setRestitution(0.0);    

    //
    // turn gravity on
    //
    getPhysicsManager()->getWorld()->setGravity(TVector3(0.f,-10.f,0.f));

    //
    // create a kinematic cube node and attach controllers
    //
    ISceneNode* m_cube;
    TColliderShape* shape;
    m_cube = loadModel("mdl/Cube.irrmesh");
    if(!m_cube)
    {
        m_cube = getSceneManager()->addCubeSceneNode(3.0f);
    }

    m_cube->setPosition(TVector3(0,8,0));
    m_cube->setMaterialFlag(EMF_LIGHTING,false);
    
    shape = new TColliderBox(m_cube);
    dnode = new TDynamicNode("cube1::pnode",m_cube,shape,0.0,btKinematic);
    dnode->allowDeactivation(false);
    
    new Tubras::TRotateController("cube::rotatorx",m_cube,
        200.0,TVector3::UNIT_X);
    new Tubras::TRotateController("cube::rotatory",m_cube,
        100.0,TVector3::UNIT_Y);
    new Tubras::TRotateController("cube::rotatorz",m_cube,
        250.0,TVector3::UNIT_Z);
    new Tubras::TOscillateController("cube::oscillator",m_cube,
        1.0f,4.0f,TVector3::UNIT_Y);
    
    //
    // create a positional sound that is attached to the cube created above.
    //
    TSound* sound = loadSound("snd/whirl_mono.ogg",true);
    if(sound)
    {
        TSoundNode* snode = new TSoundNode(sound,m_cube);

        sound->setVolume(1.0f);
        sound->set3DMinDistance(2.0);
        sound->setLoop(true);
        sound->play();
    }
    
    //
    // setup shere & cube dynamic nodes
    //
    m_cube = loadModel("mdl/Cube.irrmesh");
    if(!m_cube)
    {
        m_cube = getSceneManager()->addCubeSceneNode(3.0f);
    }
    m_cube->setPosition(TVector3(0,20,0));
    m_cube->setMaterialFlag(EMF_LIGHTING,false);
    m_cube->setName("test cube");
    shape = new TColliderBox(m_cube);
    new TDynamicNode("cube2::pnode",m_cube,shape,1.0);

    ISceneNode* m_ball = loadModel("mdl/Ball.irrmesh");
    if(!m_ball)
    {
        m_ball = getSceneManager()->addCubeSceneNode(3.0f);
    }
    m_ball->setPosition(TVector3(-5,10,0));
    m_ball->setMaterialFlag(EMF_LIGHTING,false);
    m_ball->setName("test cube");
    shape = new TColliderSphere(m_ball);
    dnode = new TDynamicNode("ball::pnode",m_ball,shape,1.0);
    dnode->setRestitution(0.0);
    dnode->setFriction(1.0);
    dnode->setDamping(0.2f,0.2f);


    //
    // add kinematic sphere collider around our camera
    //
    ICameraSceneNode* cam = getActiveCamera();
    cam->setPosition(TVector3(0.f,25.f,-50.f));
    
    shape = new TColliderCylinder(TVector3(1,2.5,1));
    dnode = new TDynamicNode("Camera::pnode",cam,shape,1.0,btKinematic);
    dnode->setRestitution(1.0);
    dnode->getRigidBody()->getBulletRigidBody()->setHitFraction(0.0);
    dnode->allowDeactivation(false);    

    //
    // set the sound listener node to our camera node
    //
    getSoundManager()->setListenerNode(cam);

    //
    // pre-load sounds we'll need later on
    //
    m_fire = loadSound("snd/cannon.ogg"); 
    m_shot = loadSound("snd/singleshot.ogg");

    //
    // todo: create & use TImageOverlay
    //
    tex = getTexture("tex/crosshair.png");
    s32 x,y;
    TDimension size;
    size = getRenderer()->getVideoDriver()->getCurrentRenderTargetSize();
    x = (size.Width/2) - 64;
    y = (size.Height/2) - 64;
    getGUIManager()->addImage(tex,position2d<s32>(x,y));


    m_shooterLine = (TLineNode*)getSceneManager()->addSceneNode("TLineNode");
    m_shooterLine->initialize(TVector3(0,5,0),TVector3(25,5,0),
        TColour(255,255,0));
    m_shooterLine->setVisible(false);


    TAxisNode* anode;
    anode = (TAxisNode*)getSceneManager()->addSceneNode("TAxisNode",m_cube);
    anode->initialize(3.f);
    anode->setPosition(TVector3(0.f,0.f,0.f));

    TQuaternion quat;

    return 0;
}

//-----------------------------------------------------------------------
//                          t e s t T a s k
//-----------------------------------------------------------------------
int TSandbox::testTask(TTask* task)
{
    return TTask::cont;
}

//-----------------------------------------------------------------------
//                              m a i n
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
        TSandbox app;

        app.setArgs(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }
#ifndef TUBRAS_PLATFORM_WIN32
} // extern "C"
#endif

