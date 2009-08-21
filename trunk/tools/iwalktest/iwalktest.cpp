//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "iwalktest.h"

//-----------------------------------------------------------------------
//                           T W a l k t e s t
//-----------------------------------------------------------------------
TWalktest::TWalktest() : TApplication("iwalktest"), m_lightsVisible(false),
    m_sceneAttributes(0)
{
}

//-----------------------------------------------------------------------
//                          ~ T W a l k t e s t
//-----------------------------------------------------------------------
TWalktest::~TWalktest()
{
#ifdef _DEBUG
    m_dumpMemoryReport();
#endif
}

//-----------------------------------------------------------------------
//                        t o g g l e H e l p
//-----------------------------------------------------------------------
int TWalktest::toggleHelp(const TEvent* event)
{
    toggleHelpOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e D e b u g
//-----------------------------------------------------------------------
int TWalktest::toggleDebug(const TEvent* event)
{
    toggleDebugOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                    t o g g l e D e b u g L i g h t s 
//-----------------------------------------------------------------------
int TWalktest::toggleDebugLights(const TEvent* event)
{
    m_lightsVisible = m_lightsVisible ? false : true;
    for(u32 i=0; i<m_lights.size(); i++)
    {
        m_lights[i]->setVisible(m_lightsVisible);
    }
    return 1;
}

//-----------------------------------------------------------------------
//                         c y c l e D e b u g
//-----------------------------------------------------------------------
int TWalktest::cycleDebug(const TEvent* event)
{
    cycleDebugData();
    return 1;
}

//-----------------------------------------------------------------------
//                         t o g g l e G o d
//-----------------------------------------------------------------------
int TWalktest::toggleGod(const TEvent* event)
{
    if(getPlayerController()->getMode() == pcmFirstPerson)
        getPlayerController()->setMode(pcmGod);
    else
        getPlayerController()->setMode(pcmFirstPerson);
    return 1;
}

//-----------------------------------------------------------------------
//                         c y c l e C a m e r a
//-----------------------------------------------------------------------
int TWalktest::cycleCamera(const TEvent* event)
{
    u32  tcams = m_cameras.size();
    void *ccam=getActiveCamera();
    for(u32 i=0;i<tcams;i++)
    {
        if(ccam == (void*)m_cameras[i])
        {
            if( (i+1) >= tcams)
                i = 0;
            else ++i;
            ICameraSceneNode* cam = (ICameraSceneNode*)m_cameras[i];
            getSceneManager()->setActiveCamera(cam);
            getPlayerController()->setCamera(cam);
            return 1;
        }
    }

    return 1;
}

//-----------------------------------------------------------------------
//                 t o g g l e P h y s i c s D e b u g
//-----------------------------------------------------------------------
int TWalktest::togglePhysicsDebug(const TEvent* event)
{
    TApplication::togglePhysicsDebug();
    return 1;
}

//-----------------------------------------------------------------------
//                      c a p t u r e S c r e e n
//-----------------------------------------------------------------------
int TWalktest::captureScreen(const TEvent* event)
{
    getRenderer()->captureScreen();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e W i r e
//-----------------------------------------------------------------------
int TWalktest::toggleWire(const TEvent* event)
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
//                             q u i t
//-----------------------------------------------------------------------
int TWalktest::quit(const TEvent* event)
{
    TApplication::stopRunning();
    return 1;
}

//-----------------------------------------------------------------------
//                     b u i l d C a m e r a L i s t
//-----------------------------------------------------------------------
void TWalktest::buildCameraList(ISceneNode* node)
{
    ESCENE_NODE_TYPE type = node->getType();
    ESCENE_NODE_TYPE tcamtype =  (ESCENE_NODE_TYPE)MAKE_IRR_ID('t','c','a','m');

    if( (type==ESNT_CAMERA) || (type==ESNT_CAMERA_MAYA) ||
        (type==ESNT_CAMERA_FPS) || (type==tcamtype))
    {
        m_cameras.push_back(node);
    }

    list<ISceneNode*> children = node->getChildren();
    list<ISceneNode*>::Iterator itr = children.begin();
    while(itr != children.end())
    {
        ISceneNode* child = *itr;
        buildCameraList(child);
        itr++;
    }
}

//-----------------------------------------------------------------------
//                     b u i l d L i g h t L i s t
//-----------------------------------------------------------------------
void TWalktest::buildLightList(ISceneNode* node)
{
    ESCENE_NODE_TYPE type = node->getType();

    if( (type==ESNT_LIGHT) )
    {
        ILightSceneNode* lnode = (ILightSceneNode*) node;
        
        SLight& ldata = lnode->getLightData();

        IBillboardSceneNode* bnode = getSceneManager()->addBillboardSceneNode(lnode->getParent());
        bnode->setColor(ldata.DiffuseColor.toSColor());
        bnode->setSize(core::dimension2d<f32>(1, 1));
        bnode->setPosition(lnode->getPosition());
        bnode->setVisible(false);
        SMaterial& mat = bnode->getMaterial(0);
        ITexture* tex = getTexture("tex/lamp.tga");
        mat.setTexture(0,tex);
        mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
        mat.setFlag(EMF_LIGHTING,false);
        m_lights.push_back(bnode);

        // doLightRecalc() is called in the light scene node constructor
        // but the light attributes (light type, direction, etc.) aren't set 
        // until after the light is initially created. invoking 
        // OnRegisterSceneNode here forces a direction recalc.
        lnode->OnRegisterSceneNode();

        TLineNode* dline;
        if(ldata.Type != ELT_POINT)
        {
            // direction is already normalized.
            TVector3 dir = ldata.Direction * ldata.Radius;
            TColor dcolor = ldata.DiffuseColor.toSColor();
            // create direction line
            TLineNode* dline =  new TLineNode(bnode,-1,TVector3::ZERO,dir,dcolor);
            dline->setVisible(true);
        }
        // pole - vertical line to the ground (y=0)
        TVector3 pos = bnode->getPosition();
        dline = new TLineNode(bnode,-1, TVector3(), TVector3(pos.X, 0, pos.Z) - pos, TColor(128, 128, 128));
        dline->setVisible(true);
    }

    list<ISceneNode*> children = node->getChildren();
    list<ISceneNode*>::Iterator itr = children.begin();
    while(itr != children.end())
    {
        ISceneNode* child = *itr;
        buildLightList(child);
        itr++;
    }
}

//-----------------------------------------------------------------------
//                      O n R e a d U s e r D a t a
//-----------------------------------------------------------------------
void TWalktest::OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
{
    stringc sname = forSceneNode->getName();
    static bool checkPhysicsAttributes = false;
    static bool physicsEnabled = false;

    // save the root (scene) attributes.
    if(sname == "root")
    {
        m_sceneAttributes = userData;
        m_sceneAttributes->grab();
        stringc exporter = m_sceneAttributes->getAttributeAsString("Exporter");
        stringc exporterVersion = m_sceneAttributes->getAttributeAsString("ExporterVersion");
        if(exporter == "irrb")
        {
            checkPhysicsAttributes = true;
        }

        physicsEnabled = m_sceneAttributes->getAttributeAsBool("PhysicsEnabled");
        //
        // turn gravity on
        //
        if(physicsEnabled)
        {
            f32 gravity=-9.8f;
            if(m_sceneAttributes->existsAttribute("Gravity"))
                gravity = m_sceneAttributes->getAttributeAsFloat("Gravity");
            getPhysicsManager()->getWorld()->setGravity(TVector3(0.f,gravity,0.f));
        }

        return;
    }

    ESCENE_NODE_TYPE type = forSceneNode->getType();
    if(type == ESNT_MESH)
    {
        IMeshSceneNode* mnode = reinterpret_cast<IMeshSceneNode*>(forSceneNode);
        if(physicsEnabled)
        {
            TColliderShape* colliderShape;
            TPhysicsObject* pobj=0;
            stringc bodyType = userData->getAttributeAsString("PhysicsBodyType");
            stringc dNodeName = mnode->getName();
            dNodeName += "::physics";
            bool convex=false;
            stringc bodyShape = userData->getAttributeAsString("PhysicsBodyShape");


            // make sure we have a valid mesh
            IMesh* mesh = mnode->getMesh();
            if(!mesh)
            {
                this->logMessage(LOG_ERROR, "Mesh is NULL for %s", mnode->getName());
                return;
            }

            if(bodyShape.equals_ignore_case("box"))
            {
                colliderShape = new TColliderBox(mnode);                 
            }
            else if(bodyShape.equals_ignore_case("sphere"))
            {
                colliderShape = new TColliderSphere(mnode);      
            }
            else if(bodyShape.equals_ignore_case("cylinder"))
            {
                colliderShape = new TColliderCylinder(mnode);
            }
            else if(bodyShape.equals_ignore_case("cone"))
            {
                colliderShape = new TColliderCone(mnode);
            }
            else // mesh shape
            {
                if(!bodyShape.size())
                    bodyShape = "trimesh";

                if(bodyShape == "convexhull")
                    convex = true;

                // dynamic bodies must be convex
                if(((bodyType == "rigid") || (bodyType == "dynamic")) && (bodyShape == "trimesh"))
                {
                    logMessage(LOG_WARNING, "Dynamic concave mesh not supported - using convex shape.");
                    logMessage(LOG_WARNING, "    mesh: %s", mnode->getName());
                    convex = true;
                }

                colliderShape = new TColliderMesh(mnode->getMesh(),
                    mnode->getRelativeTransformation(),convex,false);
            }

            if(bodyType == "static")
            {

                pobj = new TPhysicsObject(dNodeName,mnode,colliderShape,0.0f,btStatic);
                //dnode->allowDeactivation(false);
            }
            else if(bodyType == "dynamic")
            {
                f32 mass=1.f;
                bool allowDeactivation=true;

                if(userData->existsAttribute("PhysicsMass"))
                    mass = userData->getAttributeAsFloat("PhysicsMass");
                // dynamic nodes only support convex shapes
                pobj = new TPhysicsObject(dNodeName,mnode,colliderShape,mass,btDynamic);
                pobj->setDamping(0.2f,0.2f);
                pobj->allowDeactivation(allowDeactivation);

            }
            else if(bodyType == "rigid")
            {
                f32 mass=1.f;
                if(userData->existsAttribute("PhysicsMass"))
                    mass = userData->getAttributeAsFloat("PhysicsMass");
                pobj = new TPhysicsObject(dNodeName,mnode,colliderShape,mass,btKinematic);
                pobj->allowDeactivation(false);  // no deactivation for rigid body type
            }
            else if(bodyType == "soft")
            {
                // net yet supported
            }

            if(pobj)
            {
                if(userData->existsAttribute("PhysicsFriction"))
                    pobj->setFriction(userData->getAttributeAsFloat("PhysicsFriction"));

                if(userData->existsAttribute("PhysicsRestitution"))
                    pobj->setRestitution(userData->getAttributeAsFloat("PhysicsRestitution"));
            }


            // check if ghost object (physics only)
            if(userData->getAttributeAsBool("PhysicsGhost"))
            {
                if(pobj)
                    pobj->setSceneNode(0);
                mnode->setVisible(false);
                getSceneManager()->addToDeletionQueue(mnode);
                mnode = 0;
            }
        }

        if(mnode && userData->existsAttribute("HWMappingHint"))
        {
            E_HARDWARE_MAPPING  mapping=EHM_NEVER;
            E_BUFFER_TYPE buffertype=EBT_NONE;

            IMesh* mesh = mnode->getMesh();

            stringc smapping = userData->getAttributeAsString("HWMappingHint");
            if(smapping == "static")
                mapping = EHM_STATIC;
            else if(smapping == "dynamic")
                mapping = EHM_DYNAMIC;
            else if(smapping == "stream")
                mapping = EHM_STREAM;

            stringc sbuffertype = userData->getAttributeAsString("HWMappingBufferType");
            if(sbuffertype == "vertex")
                buffertype = EBT_VERTEX;
            else if(sbuffertype == "index")
                buffertype = EBT_INDEX;
            else if(sbuffertype == "vertexindex")
                buffertype = EBT_VERTEX_AND_INDEX;

            mesh->setHardwareMappingHint(mapping, buffertype);
        }
    }
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TWalktest::initialize()
{
    TArray<stringc> folderArchives;

    //
    // must call inherited initialize to create and initialize
    // all sub-systems.
    //
    if(TApplication::initialize())
        return 1;

    //
    // check for scene file name passed as an argument
    //
    int c;
    while ((c = getopt(m_argc,m_argv, "i:a:")) != EOF)
    {
        switch (c)
        {
        case 'i':
            m_sceneFileName = optarg;
            break;
        case 'a':
            folderArchives.push_back(optarg);
            break;
        }        
    }

    if(!m_sceneFileName.size())
    {
        if(optind < m_argc)
        {
            m_sceneFileName = m_argv[optind++];
        }
    }

    stringc caption = "iwalktest - ";
    caption += m_sceneFileName;
    setWindowCaption(caption);

    addHelpText(" wasd - Camera movement");
    addHelpText("   ec - Camera elevation");
    addHelpText("arrow - Camera rotation");
    addHelpText("shift - Camera velocity+");
    addHelpText("    I - Invert mouse");
    addHelpText("    L - Toggle debug lights");
    addHelpText("  prt - Screen capture");
    addHelpText("   F1 - Toggle help");
    addHelpText("   F2 - Toggle debug info");
    addHelpText("   F3 - Cycle wire/pts");
    addHelpText("   F4 - Toggle Phys dbg");
    addHelpText("   F5 - Cycle dbg data");
    addHelpText("   F7 - Toggle God mode");

    acceptEvent("help",EVENT_DELEGATE(TWalktest::toggleHelp));
    acceptEvent("idbg",EVENT_DELEGATE(TWalktest::toggleDebug));      
    acceptEvent("ldbg",EVENT_DELEGATE(TWalktest::toggleDebugLights));      
    acceptEvent("wire",EVENT_DELEGATE(TWalktest::toggleWire));  
    acceptEvent("pdbg",EVENT_DELEGATE(TWalktest::togglePhysicsDebug));      
    acceptEvent("cdbg",EVENT_DELEGATE(TWalktest::cycleDebug));
    acceptEvent("sprt",EVENT_DELEGATE(TWalktest::captureScreen));
    acceptEvent("tgod",EVENT_DELEGATE(TWalktest::toggleGod)); 
    acceptEvent("quit",EVENT_DELEGATE(TWalktest::quit));   

    //
    // save tubras default camera
    //
    ICameraSceneNode* cam;
    cam = getActiveCamera();
    TVector3 cpos = getConfig()->getVector3df("options.defcampos",cam->getPosition());
    TVector3 ctarget = getConfig()->getVector3df("options.defcamtarget",cam->getTarget());
    cam->setPosition(cpos);
    cam->setTarget(ctarget);


    //
    // if scene file name not passed as a parameter then look in iwalktest.lsl
    //
    if(!m_sceneFileName.size())
        m_sceneFileName = getConfig()->getString("options.loadscene");

    if(m_sceneFileName.size())
    {
        // add folder archives specified on the command line
        for(u32 i=0;i<folderArchives.size();i++)
        {
            stringc folder = folderArchives[i];
            TFile   file(folder.c_str());
            if(file.exists())
                getFileSystem()->addFileArchive(folder.c_str(), false, false, EFAT_FOLDER);
        }

        getSceneManager()->loadScene(m_sceneFileName.c_str(), this);
    }

    //
    // setup light debugging billboards
    //
    buildLightList(getSceneManager()->getRootSceneNode());

    //
    // if multiple cameras, then setup cycling
    //
    buildCameraList(getSceneManager()->getRootSceneNode());
    if(m_cameras.size() > 1)
    {
        char buf[100];
        sprintf(buf,"   F9 - Cycle cameras[%d]",m_cameras.size());
        addHelpText(buf);
        acceptEvent("input.key.down.f9",EVENT_DELEGATE(TWalktest::cycleCamera));
    }

    getPlayerController()->setCamera(getActiveCamera());
    if(m_sceneAttributes && m_sceneAttributes->getAttributeAsBool("PhysicsEnabled"))
        getPlayerController()->setMode(pcmFirstPerson);
    else
        getPlayerController()->setMode(pcmGod);

    addHelpText("  Esc - Quit");

    return 0;
}

//-----------------------------------------------------------------------
//                              m a i n
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
#pragma comment(lib, "Irrlicht.lib") 
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 
#endif
int main(int argc, const char **argv)
{
    TWalktest app;

    app.setArgs(argc,argv);

    if(!app.initialize())
        app.run();

    return 0;
}
