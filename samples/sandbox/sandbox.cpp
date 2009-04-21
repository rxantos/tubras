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
#define GID_GUISCENENODE 200
#define GID_GRAVITY 201

//-----------------------------------------------------------------------
//                           T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::TSandbox() : TApplication("sandbox"),
m_screen(0), m_fire(0), m_shot(0), m_velocity(50.f), m_fireCount(0), 
m_shooterLine(0), m_irrInfo(0), m_bulletInfo(0), m_infoTask(0),
m_guiNodeActivated(false), m_guiNode(0), m_guiNode2(0)
{
}

//-----------------------------------------------------------------------
//                          ~ T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::~TSandbox()
{
    if(m_guiNode)
        m_guiNode->drop();
    if(m_screen)
        m_screen->drop();
    if(m_irrInfo)
        delete m_irrInfo;
    if(m_bulletInfo)
        delete m_bulletInfo;
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
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e C u r s o r
//-----------------------------------------------------------------------
int TSandbox::toggleCursor(const TEvent* event)
{
    getInputManager()->setCursorVisible(!getInputManager()->getCursorVisible());
    return 1;
}

//-----------------------------------------------------------------------
//                      t o g g l e G o d M o d e
//-----------------------------------------------------------------------
int TSandbox::toggleGodMode(const TEvent* event)
{
    TPlayerController* pc = getPlayerController();
    if(pc->getMode() == pcmGod)
    {
        pc->setMode(pcmFirstPerson);
    }
    else
    {
        pc->setMode(pcmGod);
    }
    return 1;
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
//                            O n E v e n t
//-----------------------------------------------------------------------
bool TSandbox::OnEvent(const SEvent &  event)
{
    if(m_guiNode)
        m_guiNode->postEventFromUser(event);

    if(m_guiNode2)
        m_guiNode2->postEventFromUser(event);
        
    if(event.EventType == EET_USER_EVENT)
    {
        if(event.UserEvent.UserData1 == GID_GUISCENENODE)
        {
            SGUISceneNodeEvent* nevent = (SGUISceneNodeEvent*)event.UserEvent.UserData2;
            if(nevent->EventType == EGNET_ACTIVATED)
            {
                m_guiNodeActivated = nevent->UserData == 0 ? false : true;
                if(m_guiNodeActivated)
                    m_guiEnterSound->play();
                else m_guiExitSound->play();
                m_crossHair->setVisible(!m_guiNodeActivated);
            }
            return true;
        }
    }
    else if(event.EventType == EET_GUI_EVENT)
    {
        if(event.GUIEvent.Caller->getID() == GID_GRAVITY)
        {
            if(event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
            {
                if(((IGUICheckBox*)event.GUIEvent.Caller)->isChecked())
                    getPhysicsManager()->getWorld()->setGravity(TVector3(0.f,-10.f,0.f));
                else
                    getPhysicsManager()->getWorld()->setGravity(TVector3(0.f,0.f,0.f));
                return true;
            }
        }
    }

    return TApplication::OnEvent(event);
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
            new TPhysicsObject("testCollider",forSceneNode,cm);
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
    if(m_guiNodeActivated)
        return 0;

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

    pos.X = pos.Y = 100;

    TRay ray(pos,getActiveCamera());
    m_shooterLine->set(ray.start,ray.end,TColor(255,255,0));
    m_shooterLine->setVisible(true);

    TRayResult res = getPhysicsManager()->getWorld()->rayTest(ray);
    if(res.hasHit())
    {
        TPhysicsObject* pdn=res.getCollisionObject();
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

    if(m_guiNodeActivated)
        return 0;

    if(getInputManager()->isKeyDown(KEY_CONTROL))
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
            default:
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
    

    TPhysicsObject* pnode = new TPhysicsObject("default",
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
        TRectf(0.005f,0.70f,0.295f,0.505f));
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
        TRectf(0.305f,0.70f,0.595f,0.505f));
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
        TIBConvert::IrrToBullet(mat.getTranslation(), mat.getRotationDegrees(),trans);
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
    addHelpText("  F7 - Toggle God Mode");
    addHelpText("  F8 - Toggle Cursor");

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
    acceptEvent("key.down.f7", EVENT_DELEGATE(TSandbox::toggleGodMode));
    acceptEvent("key.down.f8", EVENT_DELEGATE(TSandbox::toggleCursor));
    acceptEvent("input.mouse.down.right",EVENT_DELEGATE(TSandbox::shootNode));
    acceptEvent("input.mouse.down.left",EVENT_DELEGATE(TSandbox::shootRay));
    m_upID = acceptEvent("input.mouse.up.left",EVENT_DELEGATE(TSandbox::shootRay));

    //
    // create background node if configured.
    //
    if(getConfig()->getBool("useBackground"))
    {
        TBackgroundNode* bgNode = new TBackgroundNode();
        if(getConfig()->getMaterial(getRenderer()->getDevice(),"Background",bgNode->getMaterial(0)) &&
            getConfig()->isAnimatedMaterial("Background"))
        {
            // add a ref to the universal material layer animator (scroll, scale, rotation).
            getConfig()->addAnimationRef("Background", bgNode->getMaterial(0));
        }
        getRenderer()->setBackgroundNode(bgNode);
        bgNode->setVisible(true);
    }
    
    //
    // setup the "floor" mesh & material, collider
    //
    TPhysicsObject* dnode;

    SMaterial mat;
    ITexture* tex = getTexture("tex/floor.png");
    mat.setTexture(0,tex);
    mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    mat.setFlag(EMF_LIGHTING,false);
    mat.setFlag(EMF_BACK_FACE_CULLING, false);
    mat.getTextureMatrix(0).setTextureScale(50.0,50.0);

    TDimensionf tileSize(50,50);
    TDimensionu tileCount(6,6);
    IAnimatedMesh* pmesh = getSceneManager()->addHillPlaneMesh("testHillPlane"
        ,tileSize,tileCount,&mat);
   
    IAnimatedMeshSceneNode* pnode;
    pnode = getSceneManager()->addAnimatedMeshSceneNode(pmesh);

    TColliderMesh* planeShape = new TColliderMesh(pnode->getMesh());
    dnode = new TPhysicsObject("Viewer_ZXPlane::pnode",pnode,
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
    dnode = new TPhysicsObject("cube1::pnode",m_cube,shape,0.0,btKinematic);
    dnode->allowDeactivation(false);
    
    (new Tubras::TRotateController("cube::rotatorx",m_cube,
        200.0,TVector3::UNIT_X))->start();
    (new Tubras::TRotateController("cube::rotatory",m_cube,
        100.0,TVector3::UNIT_Y))->start();
    (new Tubras::TRotateController("cube::rotatorz",m_cube,
        250.0,TVector3::UNIT_Z))->start();
    (new Tubras::TOscillateController("cube::oscillator",m_cube,
        1.0f,4.0f,TVector3::UNIT_Y))->start();
    
    m_guiEnterSound = loadSound("snd/sandbox/guienter.ogg");
    m_guiExitSound = loadSound("snd/sandbox/guiexit.ogg");
    //
    // create a positional sound that is attached to the cube created above.
    //
    TSound* sound = loadSound("snd/sandbox/whirl_mono.ogg",true);
    if(sound)
    {
        new TSoundNode(sound,m_cube);

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
    new TPhysicsObject("cube2::pnode",m_cube,shape,1.0);

    ISceneNode* m_ball = loadModel("mdl/Ball.irrmesh");
    if(!m_ball)
    {
        m_ball = getSceneManager()->addCubeSceneNode(3.0f);
    }
    m_ball->setPosition(TVector3(-5,10,0));
    m_ball->setMaterialFlag(EMF_LIGHTING,false);
    m_ball->setName("test cube");
    shape = new TColliderSphere(m_ball);
    dnode = new TPhysicsObject("ball::pnode",m_ball,shape,1.0);
    dnode->setRestitution(0.0);
    dnode->setFriction(1.0);
    dnode->setDamping(0.2f,0.2f);

    //
    // update the player position
    //
    getPlayerController()->setPosition(TVector3(0.f,25.f,-50.f));
    
    /*
    shape = new TColliderCylinder(TVector3(1,2.5,1));
    dnode = new TPhysicsObject("Camera::pnode",cam,shape,1.0,btKinematic);
    dnode->setRestitution(1.0);
    dnode->getRigidBody()->getBulletRigidBody()->setHitFraction(0.0);
    dnode->allowDeactivation(false);    
    */

    //
    // set the sound listener node to our camera node
    //
    getSoundManager()->setListenerNode(this->getActiveCamera());

    //
    // pre-load sounds we'll need later on
    //
    m_fire = loadSound("snd/sandbox/cannon.ogg"); 
    m_shot = loadSound("snd/sandbox/singleshot.ogg");

    //
    // todo: create & use TImageOverlay
    //
    tex = getTexture("tex/sandbox/crosshair.png");
    s32 x,y;
    TDimension size;
    size = getRenderer()->getVideoDriver()->getCurrentRenderTargetSize();
    x = (size.Width/2) - 64;
    y = (size.Height/2) - 64;
    m_crossHair = getGUIManager()->addImage(tex,position2d<s32>(x,y));

    m_shooterLine = new TLineNode(getRootSceneNode(), -1, TVector3(0,5,0),TVector3(25,5,0),
        TColor(255,255,0));
    m_shooterLine->setVisible(false);

    TAxisNode* anode;
    anode = new TAxisNode(m_cube,-1,3.f);
    anode->setPosition(TVector3(0.f,0.f,0.f));

    //
    // particle2 tests
    //
    m_particleNode = this->getParticleManager()->createParticleNode("testParticle", 500, PP_POINT);
    m_particleNode->setSpeed(1);
    m_particleNode->setPointSize(1);

    TCylinderDomain* cdom = new TCylinderDomain(TVector3(0.f, 0.25f, -0.01f), TVector3(0.0f, 0.27f, -0.01f), 0.021f, 0.019f);
    m_particleNode->setVelocity(cdom);
    cdom->drop();
    m_particleNode->setColor(TColor(255, 255, 255, 255));
    //pnode2->setColor(TLineDomain(TVector3(0.8, 0.9,1.0),TVector3(0.0, 0.0, 1.0)));

    TLineDomain* ldom = new TLineDomain(TVector3(0,0,0), TVector3(0,0.4f,0));
    TParticleAction* action = new TSourceAction(5.f, ldom);
    ldom->drop();
    m_particleNode->addAction(action);

    action = new TGravityAction(TVector3(0,-0.01f,0));
    m_particleNode->addAction(action);

    TDiscDomain* ddom = new TDiscDomain(TVector3(0,0,0), TVector3(0,1.f,0), 5.f);
    action = new TBounceAction(-0.05f, 0.35f, 0, ddom);
    m_particleNode->addAction(action);
    ddom->drop();

    TPlaneDomain* pdom = new TPlaneDomain(TVector3(0,-3.f,0), TVector3(0,1.f,0));
    action = new TSinkAction(false,pdom);
    m_particleNode->addAction(action);
    pdom->drop();

    //
    TPlaneNode* plane = new TPlaneNode(0, 0, TVector2(16,4), TVector3(), TColor(128,0,0));
    plane->setPosition(TVector3(0,2,20));

    m_guiNode = new CGUISceneNode(getSceneManager()->getRootSceneNode(), getSceneManager(), 
        GID_GUISCENENODE, 
        "tex/altcursor.png",
        GSNAM_3D,           // activation mode (3d - camera pos/target)
        this,
        10.f,               // activation distance
        SColor(240,200,200,200),
        TDimensionu(512,512),
        TVector2(6,6),      // size
        TVector3(0,0,0), // position
        TVector3(0,0,0)); // rotation

    //m_guiNode->setScale(TVector3(3,1,1));
    m_guiNode->setRotation(TVector3(0,-35,0));
    m_guiNode->setPosition(TVector3(-0,3,0));
    m_guiNode->addStaticText(L"Transparent Control:", rect<s32>(5,20,200,40), true);

    m_guiNodeRot = new Tubras::TRotateController("guinode::rotatory",m_guiNode,
        45.f,TVector3::UNIT_Y);


    IGUIScrollBar* bar = m_guiNode->addScrollBar(true, rect<s32>(210, 20, 410, 40));
    bar->setMin(0);
    bar->setMax(255);

    m_guiNode->addButton(rect<s32>(5, 50, 98, 70),0,777,L"Test Button");
    m_guiNode->addButton(rect<s32>(102, 50, 200, 70),0,-1,L"Test Button 2");
    m_guiNode->addCheckBox(true,rect<s32>(5,80,200,100),0,GID_GRAVITY,L"Gravity Enabled");

    IGUIComboBox* combo = m_guiNode->addComboBox(rect<s32>(5,120,200,140));
    combo->addItem(L"Test Item 1");
    combo->addItem(L"Test Item 2");
    combo->addItem(L"Test Item 3");
    combo->setSelected(1);

    IGUIListBox* lb = m_guiNode->addListBox(rect<s32>(5,160,200,300),0,-1,true);
    lb->addItem(L"lb item 1");
    lb->addItem(L"lb item 2");
    lb->addItem(L"lb item 3");
    lb->addItem(L"lb item 4");
    lb->addItem(L"lb item 5");
    lb->addItem(L"lb item 6");
    lb->addItem(L"lb item 7");
    lb->addItem(L"lb item 8");
    lb->addItem(L"lb item 9");

    IImage* image = getRenderer()->getVideoDriver()->createImageFromFile("tex/t351sml.jpg");
    ITexture* texture = getRenderer()->getVideoDriver()->addTexture("tex/t351sml.jpg", image);    
    image->drop();
    m_guiNode->addImage(texture, vector2d<s32>(210, 60));
    m_guiNode->addImage(texture, vector2d<s32>(210+135, 60));

    m_guiNode2 = new CGUISceneNode(getActiveCamera(), getSceneManager(), 
    //m_guiNode2 = new CGUISceneNode(getSceneManager()->getRootSceneNode(), getSceneManager(), 
        GID_GUISCENENODE, 
        "tex/altcursor.png",
        GSNAM_2D,           // activation mode (3d - camera pos/target)
        this,
        10.f,               // activation distance
        SColor(64,200,200,200),
        TDimensionu(512,512),
        TVector2(2,2),    // size
        TVector3(-1.24,0,4),  // position
        TVector3(0,-65,0)); // rotation

    m_guiNode2->getMaterial(0).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    m_guiNode2->addButton(rect<s32>(5, 50, 98, 70),0,777,L"Test Button");
    m_guiNode2->addButton(rect<s32>(102, 50, 200, 70),0,-1,L"Test Button 2");
    m_guiNode2->addCheckBox(true,rect<s32>(5,80,200,100),0,GID_GRAVITY,L"Gravity Enabled");

    return 0;
}

//-----------------------------------------------------------------------
//                    s e t U s e r D e b u g I n f o         
//-----------------------------------------------------------------------
void TSandbox::setUserDebugInfo(TStringVector& debugStrings)
{
    char buf[256];
    sprintf(buf,"intersection(%.4f,%.4f,%.4f), cpos(%d,%d)", m_guiNode->debug.X, m_guiNode->debug.Y, 
        m_guiNode->debug.Z, m_guiNode->RTTCursorPos.X, m_guiNode->RTTCursorPos.Y);
    stringc s = buf;
    debugStrings.push_back(s);
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
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
int main(int argc, const char* argv[])
{
	//m_breakOnAlloc(154374);
	TSandbox app;

	app.setArgs(argc,argv);

	if(!app.initialize())
		app.run();

	return 0;
} 

