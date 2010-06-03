//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "sandbox.h"
#define GID_QUIT            101
#define GID_GUISCENENODE    200
#define GID_GUISCENENODE2   201
#define GID_GRAVITY         202
#define GID_FIREVELOCITY    203
#define GID_ROTATEGUINODE   204
#define GID_BACKFACECULL    205
#define GID_BGCOLOR         206
#define GID_XFORCE          207
#define GID_YFORCE          208
#define GID_ZFORCE          209
#define GID_TRANSPARENT     210
#define GID_RESETGRAVITY    211
#define GID_WALLVISIBLE     212
#define GID_DOORACTION      213

#define FLOOR_RESTITUTION   1.f
#define FLOOR_FRICTION      1.f
#define OBJECT_RESTITUTION  0.2f
#define OBJECT_FRICTION     1.f

//-----------------------------------------------------------------------
//                           T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::TSandbox() : TApplication("sandbox"),
m_screen(0), m_fire(0), m_shot(0), m_velocity(50.f), m_fireCount(0), 
m_shooterLine(0), m_irrInfo(0), m_bulletInfo(0), m_infoTask(0),
m_guiNode(0), m_guiNode2(0), m_guiNodeActivated(false), m_doorState(1),
m_opMode(1)
{
}

//-----------------------------------------------------------------------
//                          ~ T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::~TSandbox()
{
    if(m_guiNode)
        m_guiNode->drop();
    if(m_guiNode2)
        m_guiNode2->drop();
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
    this->toggleHelpGUI();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e D e b u g
//-----------------------------------------------------------------------
int TSandbox::toggleDebug(const TEvent* event)
{
    toggleDebugGUI();
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
    TCharacterController* pc = getCharacterController();
    if(pc->getMode() == ccmGod)
    {
        pc->setMode(ccmFirstPerson);
    }
    else
    {
        pc->setMode(ccmGod);
    }
    return 1;
}

//-----------------------------------------------------------------------
//                      t o g g l e O p M o d e
//-----------------------------------------------------------------------
int TSandbox::toggleOpMode(const TEvent* event)
{
    m_opMode = m_opMode ? 0 : 1;

    if(m_opMode)
    {
        m_guiNode2->setEnabled(false);
        m_crossHair->setVisible(true);
        setGUICursorEnabled(false);
        setInputMode(imAll);
    }
    else {
        if(m_guiNode2)
        {
            m_guiNode2->setEnabled(true);
            m_crossHair->setVisible(false);
            setGUICursorEnabled(true);
            setInputMode(imGUI);
        }
    }
    return 1;
}

//-----------------------------------------------------------------------
//                          p r e R e n d e r
//-----------------------------------------------------------------------
void TSandbox::preRender(f32 deltaTime)
{
    if(!m_opMode && m_guiNode2)
    {
        m_guiNode2->CursorPos2D = this->getRenderer()->getGUICursor()->getPosition();
    }
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
    logMessage(LOG_INFO, "testInterval T: %.3f",T );
}

//-----------------------------------------------------------------------
//                      O n R e a d U s e r D a t a
//-----------------------------------------------------------------------
void TSandbox::OnReadUserData(ISceneNode* forSceneNode, 
                              io::IAttributes* userData)
{
    bool value=false;


    ESCENE_NODE_TYPE type = forSceneNode->getType();
    if(type == ESNT_MESH)
    {
        // look for a collier
        if(userData->existsAttribute("collider"))
            value = userData->getAttributeAsBool("collider");
        if(value)
        {
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

    TRayResult res = getPhysicsManager()->rayTest(ray);
    if(res.hasHit())
    {
        TPhysicsObject* pdn=res.getCollisionObject();
        if(getDebug())
        {
            logMessage(LOG_INFO, "rayTest Hit: %s", pdn->getName().c_str());
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
//                       d o o r A c t i o n D o n e
//-----------------------------------------------------------------------
int TSandbox::doorActionDone(const TEvent* event)
{
    m_doorBell->setEnabled(true);
    if(m_doorState == 2)  // opening?
    {
        m_doorState = 0;  // set open
        m_doorBell->setText(L"Close Door");
    }
    else
    {
        m_doorState = 1;  // set closed
        m_doorBell->setText(L"Open Door");
    }

    // force gui node update
    m_guiNode2->updateGUITexture();

    // reverse the position interval
    m_openDoor->reverse();

    return 1;
}

//-----------------------------------------------------------------------
//                          s h o o t N o d e
//-----------------------------------------------------------------------
int TSandbox::shootNode(const TEvent* event)
{
    
    TStrStream str;
    ISceneNode* node;
    TVector3 pos,direction;
    TPhysicsBodyShape bodyShape;

    if(m_guiNodeActivated)
        return 0;

    if(getInputManager()->isKeyDown(KEY_CONTROL) |
            getInputManager()->isKeyDown(KEY_LCONTROL))
    {
        node = loadModel("mdl/TBall.irrmesh");
        bodyShape = stSphere;
    }
    else
    {
        node = loadModel("mdl/TCube.irrmesh");
        bodyShape = stBox;
    }

    TRenderMode renderMode = getRenderer()->getRenderMode();
    if(node->getMaterialCount())
    {
        for(u32 idx=0;idx<node->getMaterialCount();idx++)
        {
            SMaterial& mat = node->getMaterial(idx);

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
    pos += (direction * 4.5);
    node->setPosition(pos);
    TMatrix4 mat4 = cam->getAbsoluteTransformation();
    TVector3 rot = mat4.getRotationDegrees();
    if(rot.Z > 0.f)
        rot = -rot;    

    node->setRotation(rot);
    
    static int snodeNum=1;

    stringc poName = "snode::";
    poName += snodeNum;
    ++snodeNum;

    TPhysicsObject* pobject = getPhysicsManager()->createObject(node, btDynamic, bodyShape, 1.f);

    pobject->setLinearVelocity(direction*m_velocity);

    pobject->setRestitution(OBJECT_RESTITUTION);
    pobject->setFriction(OBJECT_FRICTION);
    pobject->setDamping(0.2f,0.2f);
    pobject->allowDeactivation(true);
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
        if(event.UserEvent.UserData1 == GID_GUISCENENODE ||
           event.UserEvent.UserData1 == GID_GUISCENENODE2)
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
        if(event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
        {
            m_guiClickSound2->play();
            if(event.GUIEvent.Caller->getID() == GID_GRAVITY)
            {
                if(((IGUICheckBox*)event.GUIEvent.Caller)->isChecked())
                {
                    f32 xforce = (f32)m_gxForce->getPos() / 10.f;
                    f32 yforce = (f32)m_gyForce->getPos() / 10.f;
                    f32 zforce = (f32)m_gzForce->getPos() / 10.f;
                    getPhysicsManager()->setGravity(TVector3(xforce,yforce,zforce));
                }
                else
                {
                    m_gxForce->setPos(0);
                    m_gyForce->setPos(0);
                    m_gzForce->setPos(0);
                    m_sxForce->setText(L"X Force (0)");
                    m_syForce->setText(L"Y Force (0)");
                    m_szForce->setText(L"Z Force (0)");
                    getPhysicsManager()->setGravity(TVector3(0.f,0.f,0.f));
                }
                getPhysicsManager()->activateAllObjects();
                return true;
            }
            else if(event.GUIEvent.Caller->getID() == GID_BACKFACECULL)
            {
                m_guiNode->getMaterial(0).BackfaceCulling = 
                    ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
                return true;
            }
            else if(event.GUIEvent.Caller->getID() == GID_TRANSPARENT)
            {
                if(((IGUICheckBox*)event.GUIEvent.Caller)->isChecked())
                    m_guiNode->getMaterial(0).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
                else
                    m_guiNode->getMaterial(0).MaterialType = EMT_SOLID;
                return true;
            }
            else if(event.GUIEvent.Caller->getID() == GID_ROTATEGUINODE)
            {
                if(((IGUICheckBox*)event.GUIEvent.Caller)->isChecked())
                    m_guiNodeRot->start();
                else
                    m_guiNodeRot->stop();
                return true;
            }
            else if(event.GUIEvent.Caller->getID() == GID_WALLVISIBLE)
            {
                bool visible = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
                m_wall->setVisible(visible);
                m_door->setVisible(visible);
                if(visible)
                {
                    m_poWall->enable();
                    m_poDoor->enable();
                }
                else
                {
                    m_poWall->disable();
                    m_poDoor->disable();
                }
                m_doorBell->setEnabled(visible);
                return true;
            }
        }
        else if(event.GUIEvent.EventType == EGET_SPINBOX_CHANGED)
        {
            m_guiClickSound2->play();

        }
        else if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
        {
            if(event.GUIEvent.Caller->getID() == GID_BGCOLOR)
            {
                m_guiNode->addColorSelectDialog(L"Color Select Dialog", true, 0, -1);
            }
            else if(event.GUIEvent.Caller->getID() == GID_RESETGRAVITY)
            {
                m_gxForce->setPos(0);
                m_gzForce->setPos(0);
                m_sxForce->setText(L"X Force (0)");
                m_szForce->setText(L"Z Force (0)");
                if(m_gravityEnabled->isChecked())
                {
                    m_gyForce->setPos(-98);
                    m_syForce->setText(L"Y Force (-9.8)");
                }
                else
                {
                    m_gyForce->setPos(0);
                    m_syForce->setText(L"Y Force (0)");
                }
                f32 yforce = (f32)m_gyForce->getPos() / 10.f;
                getPhysicsManager()->setGravity(TVector3(0.f,yforce,0.f));
                getPhysicsManager()->activateAllObjects();
            }
            else if(event.GUIEvent.Caller->getID() == GID_DOORACTION)
            {
                m_doorBell->setEnabled(false);
                if(m_doorState == 1) // closed?
                    m_doorState = 2;  // opening
                else
                    m_doorState = -2; // closing
                m_openDoor->start(); 
                m_slide->play();
            }
            m_guiClickSound->play();
        }
        else if(event.GUIEvent.EventType == EGET_SCROLL_BAR_CHANGED)
        {
            s32 id = event.GUIEvent.Caller->getID();
            bool updateGravity = false;
            if(id == GID_FIREVELOCITY)
            {
                m_velocity = (f32)m_fireVelocity->getPos();
                stringw tmp = L"(";
                tmp += m_fireVelocity->getPos();
                tmp += L")";

                m_stVelocity->setText(tmp.c_str());
            }
            else if (id == GID_XFORCE)
            {
                char buf[64];
                f32 force = (f32)m_gxForce->getPos() / 10.f;
#if defined(WIN32) && !defined(__GNUWIN32__)
                sprintf(buf,"X Force (%.1f)", force);
#else
                snprintf(buf,sizeof(buf),"X Force (%.1f)", force);
#endif
                stringw msg = buf;
                m_sxForce->setText(msg.c_str());
                updateGravity = true;
            }
            else if (id == GID_YFORCE)
            {
                char buf[64];
                f32 force = (f32)m_gyForce->getPos() / 10.f;
#if defined(WIN32) && !defined(__GNUWIN32__)
                sprintf(buf,"Y Force (%.1f)", force);
#else
                snprintf(buf,sizeof(buf),"Y Force (%.1f)", force);
#endif
                stringw msg = buf;
                m_syForce->setText(msg.c_str());
                updateGravity = true;
            }
            else if (id == GID_ZFORCE)
            {
                char buf[64];
                f32 force = (f32)m_gzForce->getPos() / 10.f;
#if defined(WIN32) && !defined(__GNUWIN32__)
                sprintf(buf,"Z Force (%.1f)", force);
#else
                snprintf(buf,sizeof(buf),"Z Force (%.1f)", force);
#endif
                stringw msg = buf;
                m_szForce->setText(msg.c_str());
                updateGravity = true;
            }
            if(updateGravity)
            {
                f32 xforce = (f32)m_gxForce->getPos() / 10.f;
                f32 yforce = (f32)m_gyForce->getPos() / 10.f;
                f32 zforce = (f32)m_gzForce->getPos() / 10.f;
                getPhysicsManager()->setGravity(TVector3(xforce,yforce,zforce));
                getPhysicsManager()->activateAllObjects();
            }
        }
    }
    else if(event.EventType == EET_KEY_INPUT_EVENT)
    {
        if(event.KeyInput.Key == KEY_F9 && event.KeyInput.PressedDown && !m_opMode)  // reset gui op mode
        {
            this->toggleOpMode(0);
            return 1;
        }
    }

    return TApplication::OnEvent(event);
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
    addHelpText("wasd -","Camera movement");
    addHelpText("ec -","Camera elevation");
    addHelpText("arrow -","Camera rotation");
    addHelpText("shift -","Camera velocity+");
    addHelpText("space -","Camera jump");
    addHelpText("I -","Invert mouse");
    addHelpText("L -","Toggle debug lights");
    addHelpText("M -","Toggle light maps");
    addHelpText("tab -","Toggle console");
    addHelpText("prt -","Screen capture");
    addHelpText("F1 -","Toggle help");
    addHelpText("F2 -","Toggle debug info");
    addHelpText("F3 -","Cycle wire/pts");
    addHelpText("F4 -","Toggle Phys dbg");
    addHelpText("F5 -","Cycle dbg data");
    addHelpText("F6 -","Toggle Xform");
    addHelpText("F7 -","Toggle God mode");
    addHelpText("F8 -","Toggle Cursor");
    addHelpText("F9 -","Toggle Op Mode");
    addHelpText("Esc -","Quit");

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
    acceptEvent("input.key.down.f7", EVENT_DELEGATE(TSandbox::toggleGodMode));
    acceptEvent("input.key.down.f8", EVENT_DELEGATE(TSandbox::toggleCursor));
    acceptEvent("input.key.down.f9", EVENT_DELEGATE(TSandbox::toggleOpMode));
    acceptEvent("input.mouse.down.right",EVENT_DELEGATE(TSandbox::shootNode));
    acceptEvent("input.mouse.down.left",EVENT_DELEGATE(TSandbox::shootRay));
    acceptEvent("door.action.done", EVENT_DELEGATE(TSandbox::doorActionDone));
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
    TPhysicsObject* pobject;

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

    pobject = getPhysicsManager()->createObject(pnode, btStatic, stConvexMesh);
    pobject->setRestitution(FLOOR_RESTITUTION);
    pobject->setFriction(FLOOR_FRICTION);

    // ceiling mesh
    pnode = getSceneManager()->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(TVector3(0,60,0));
    pobject = getPhysicsManager()->createObject(pnode, btStatic, stConvexMesh);
    pobject->setRestitution(FLOOR_RESTITUTION);
    pobject->setFriction(FLOOR_FRICTION);

    //
    // turn gravity on
    //
    getPhysicsManager()->setGravity(TVector3(0.f,-10.f,0.f));

    //
    // create a kinematic cube node and attach controllers
    //
    ISceneNode* m_cube;
    m_cube = loadModel("mdl/TCube.irrmesh");
    if(!m_cube)
    {
        m_cube = getSceneManager()->addCubeSceneNode(3.0f);
    }

    m_cube->setPosition(TVector3(0,8,0));
    m_cube->setMaterialFlag(EMF_LIGHTING,false);
    
    pobject = getPhysicsManager()->createObject(m_cube, btKinematic, stBox);
    pobject->allowDeactivation(false);
    
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
    m_guiClickSound = loadSound("snd/sandbox/click1.ogg");
    m_guiClickSound2 = loadSound("snd/sandbox/click2.ogg");
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
    m_cube = loadModel("mdl/TCube.irrmesh");
    if(!m_cube)
    {
        m_cube = getSceneManager()->addCubeSceneNode(3.0f);
    }
    m_cube->setPosition(TVector3(0,20,0));
    m_cube->setMaterialFlag(EMF_LIGHTING,false);
    m_cube->setName("test cube");
    pobject = getPhysicsManager()->createObject(m_cube, btDynamic, stBox, 1.f);

    ISceneNode* m_ball = loadModel("mdl/TBall.irrmesh");
    if(!m_ball)
    {
        m_ball = getSceneManager()->addCubeSceneNode(3.0f);
    }
    m_ball->setPosition(TVector3(-5,10,0));
    m_ball->setMaterialFlag(EMF_LIGHTING,false);
    m_ball->setName("test ball");
    pobject = getPhysicsManager()->createObject(m_cube, btDynamic, stBox, 1.f);
    pobject->setRestitution(0.0);
    pobject->setFriction(1.0);
    pobject->setDamping(0.2f,0.2f);

    //
    // update the player position
    //
    getCharacterController()->setPosition(TVector3(0.f,25.f,-50.f));
    
    //
    // set the sound listener node to our camera node
    //
    getSoundManager()->setListenerNode(this->getActiveCamera());

    //
    // pre-load sounds we'll need later on
    //
    m_fire = loadSound("snd/sandbox/cannon.ogg"); 
    m_shot = loadSound("snd/sandbox/singleshot.ogg");
    m_slide = loadSound("snd/sandbox/slide.ogg",true);

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

    // test plane node
    /*
    TPlaneNode* plane = new TPlaneNode(0, 0, TVector2(16,4), TVector3(), TColor(128,0,0));
    plane->setPosition(TVector3(0,2,20));
    */

    m_guiNode = new CGUISceneNode(getSceneManager()->getRootSceneNode(), getSceneManager(), 
        GID_GUISCENENODE, 
        "tex/altcursor.png",
        GSNAM_3D,           // activation mode (3d - camera pos/target)
        this,
        10.f,               // activation distance
        SColor(128,200,200,200),
        TDimensionu(512,512),
        TVector2(6,6),      // size
        TVector3(0,0,0), // position
        TVector3(0,0,0)); // rotation

    //m_guiNode->setScale(TVector3(3,1,1));
    //m_guiNode->setRotation(TVector3(0,0,0));
    m_guiNode->setPosition(TVector3(0,3, -10));
    (m_guiNode->addStaticText(L"Fire Velocity: ", rect<s32>(5,20,200,40), true))->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_CENTER);

    m_guiNodeRot = new Tubras::TRotateController("guinode::rotatory",m_guiNode,
        45.f,TVector3::UNIT_Y);

    //m_guiNodeRot->start();

    m_fireVelocity = m_guiNode->addScrollBar(true, rect<s32>(210, 20, 440, 40),0,GID_FIREVELOCITY);
    m_fireVelocity->setMin(1);
    m_fireVelocity->setMax(100);
    m_fireVelocity->setPos(50);

    m_stVelocity = m_guiNode->addStaticText(L"(50)", rect<s32>(443,20,473,40), true);
    m_stVelocity->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);

    m_guiNode->addButton(rect<s32>(5, 50, 98, 70),0,GID_BGCOLOR,L"Color Select");
    m_guiNode->addButton(rect<s32>(102, 50, 200, 70),0,-1,L"Test Button 2");

    m_guiNode->addCheckBox(true,rect<s32>(5,80,200,100),0,GID_BACKFACECULL,L"Backface Culling");
    (m_guiNode->addCheckBox(true,rect<s32>(5,100,200,120),0,GID_TRANSPARENT,L"Transparent"))->setChecked(false);
    (m_guiNode->addCheckBox(true,rect<s32>(5,120,200,140),0,GID_ROTATEGUINODE,L"Rotate GUI Node"))->setChecked(false);

    IGUIStaticText * st = m_guiNode->addStaticText(L"--Gravity--",rect<s32>(5,150,200,360),true,true,0,-1,false);

    m_gravityEnabled  = m_guiNode->addCheckBox(true,rect<s32>(5,20,80,40),st,GID_GRAVITY,L"Enabled");
    m_guiNode->addButton(rect<s32>(100, 20, 160, 40),st,GID_RESETGRAVITY,L"Reset");

    m_sxForce = m_guiNode->addStaticText(L"X Force (0)", rect<s32>(5,45,200,65), false, false, st, -1, false);
    m_gxForce = m_guiNode->addScrollBar(true, rect<s32>(5,65,190,85),st,GID_XFORCE);
    m_gxForce->setMin(-98);
    m_gxForce->setMax(98);
    m_gxForce->setPos(0);

    m_syForce = m_guiNode->addStaticText(L"Y Force (-9.8)", rect<s32>(5,100,200,120), false, false, st, -1, false);
    m_gyForce = m_guiNode->addScrollBar(true, rect<s32>(5, 120, 190, 140),st,GID_YFORCE);
    m_gyForce->setMin(-98);
    m_gyForce->setMax(98);
    m_gyForce->setPos(-98);

    m_szForce = m_guiNode->addStaticText(L"Z Force (0)", rect<s32>(5,155,200,175), false, false, st, -1, false);
    m_gzForce = m_guiNode->addScrollBar(true, rect<s32>(5,175,190,195),st,GID_ZFORCE);
    m_gzForce->setMin(-98);
    m_gzForce->setMax(98);
    m_gzForce->setPos(0);

    /*
    IGUIComboBox* combo = m_guiNode->addComboBox(rect<s32>(5,120,200,140));
    combo->addItem(L"Test Item 1");
    combo->addItem(L"Test Item 2");
    combo->addItem(L"Test Item 3");
    combo->setSelected(1);
    */

    IGUIListBox* lb = m_guiNode->addListBox(rect<s32>(210,200,473,340),0,-1,true);
    for(int i=1;i<=50;i++)
    {
        stringw tmp = "lb item ";
        tmp += i;
        lb->addItem(tmp.c_str());
    }

    IImage* image = getRenderer()->getVideoDriver()->createImageFromFile("tex/t351sml.jpg");
    ITexture* texture = getRenderer()->getVideoDriver()->addTexture("tex/t351sml.jpg", image);    
    image->drop();
    m_guiNode->addImage(texture, vector2d<s32>(210, 60));
    m_guiNode->addImage(texture, vector2d<s32>(210+135, 60));

    //m_guiNode->setEnabled(false);
  
    // wall/door meshes

    IMeshSceneNode* node = loadStaticModel("mdl/TWall.irrmesh");
    m_wall = node;
    node->setPosition(TVector3(0,0,30));
    m_poWall = getPhysicsManager()->createObject(node, btStatic, stConvexMesh);

    m_door = 
    node = loadStaticModel("mdl/TDoor.irrmesh");
    node->setPosition(TVector3(0,0,30));
    m_poDoor = getPhysicsManager()->createObject(node, btKinematic, stConvexMesh);
    m_poDoor->allowDeactivation(false);

    TVector3 doorPos = m_door->getAbsolutePosition();
    m_openDoor = new TNodePosInterval(m_door,doorPos, doorPos-TVector3(3.95f, 0, 0),
        "openDoor",0,2.8f,2.8f,btNoBlend,"","door.action.done");

    new TSoundNode(m_slide,m_door);
    m_slide->setVolume(1.0f);
    m_slide->set3DMinDistance(10.0);

    node = loadStaticModel("mdl/TKiosk.irrmesh");
    node->setPosition(TVector3(4,0,30));
    pobject = getPhysicsManager()->createObject(node, btStatic, stConvexMesh);

    // replace guipanel texture with GUISceneNode
    m_guiNode2 = new CGUISceneNode(node, getSceneManager(), 
        GID_GUISCENENODE2, 
        "tex/altcursor.png",
        getTexture("tex/guipanel.png")->getName(),
        this,
        5.f,               // activation distance
        SColor(64,100,101,140),
        TDimensionu(256,256));

    image = getRenderer()->getVideoDriver()->createImageFromFile("tex/sandbox/mat.tga");
    texture = getRenderer()->getVideoDriver()->addTexture("tex/sandbox/mat.tga", image);
    image->drop();
    IGUIImage* guiImage = m_guiNode2->addImage(rect<s32>(0,0,256,256));
    //guiImage->setScaleImage(true);
    guiImage->setImage(texture);


    m_doorBell = m_guiNode2->addButton(rect<s32>(25, 25, 230, 100),0,GID_DOORACTION,L"Open Door");
    
    IGUISpinBox* sb = m_guiNode2->addSpinBox(L"",rect<s32>(70,120,100,150),true,0,-1);
    sb->setRange(0,9);
    sb->setValue(1);
    sb->setDecimalPlaces(0);

    sb = m_guiNode2->addSpinBox(L"",rect<s32>(105,120,135,150),true,0,-1);
    sb->setRange(0,9);
    sb->setValue(9);
    sb->setDecimalPlaces(0);

    sb = m_guiNode2->addSpinBox(L"",rect<s32>(140,120,170,150),true,0,-1);
    sb->setRange(0,9);
    sb->setValue(3);
    sb->setDecimalPlaces(0);
        
    m_guiNode2->addCheckBox(true,rect<s32>(70, 200, 170, 230),0,GID_WALLVISIBLE,L"Wall Visible");

    // timing framework tests
    irr::timing::CEvaluatorSColor eColor;
    SColor c1(0,0,0,0), c2(255, 255, 255, 255), c3;
    eColor.evaluate(c1, c2, c3, 0.5f);

    f32 f1=0.f, f2=10.f, f3;
    irr::timing::CEvaluatorF32 ef32;
    ef32.evaluate(f1, f2, f3, 0.75);

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
	//m_breakOnAlloc(149473);
	TSandbox app;

	app.setArgs(argc,argv);

	if(!app.initialize())
		app.run();

	return 0;
} 

