//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "iwalktest.h"

//-----------------------------------------------------------------------
//                           T W a l k t e s t
//-----------------------------------------------------------------------
TWalktest::TWalktest() : TApplication("iwalktest")
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
    bool visible = m_debugOverlay->getVisible();
    for(u32 i=0; i<m_lights.size(); i++)
    {
        m_lights[i]->setVisible(visible);
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

    if( (type==ESNT_CAMERA) || (type==ESNT_CAMERA_MAYA) ||
        (type==ESNT_CAMERA_FPS) || (type==(ESCENE_NODE_TYPE)TSNT_TCAM))
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

        IBillboardSceneNode* bnode = getSceneManager()->addBillboardSceneNode();
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

        // create direction line
        if(ldata.Type != ELT_POINT)
        {
            TLineNode* dline = (TLineNode*)getSceneManager()->addSceneNode("TLineNode", bnode);
            // direction is already normalized.
            TVector3 dir = ldata.Direction * ldata.Radius;
            TColor dcolor = ldata.DiffuseColor.toSColor();
            dline->initialize(TVector3::ZERO, dir, dcolor);
            dline->setVisible(true);
        }
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
    bool value=false;

    if(userData->existsAttribute("collider"))
        value = userData->getAttributeAsBool("collider");

    if(value)
    {
        ESCENE_NODE_TYPE type = forSceneNode->getType();
        if(type == ESNT_MESH)
        {
            IMeshSceneNode* mnode = reinterpret_cast<IMeshSceneNode*>(forSceneNode);
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
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TWalktest::initialize()
{
    TArray<TString> folderArchives;

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
    while ((c = getopt(m_argc,m_argv, "i:f:")) != EOF)
    {
        switch (c)
        {
        case 'i':
            m_sceneFileName = optarg;
            break;
        case 'f':
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

    TString caption = "iwalktest - ";
    caption += m_sceneFileName;
    setWindowCaption(caption);

    addHelpText(" wasd - Camera movement");
    addHelpText("   ec - Camera elevation");
    addHelpText("arrow - Camera rotation");
    addHelpText("shift - Camera velocity+");
    addHelpText("    i - Invert mouse");
    addHelpText("  prt - Screen capture");
    addHelpText("   F1 - Toggle help");
    addHelpText("   F2 - Toggle debug");
    addHelpText("   F3 - Cycle wire/pts");
    addHelpText("   F4 - Toggle Phys dbg");
    addHelpText("   F5 - Cycle dbg data");

    acceptEvent("help",EVENT_DELEGATE(TWalktest::toggleHelp));
    acceptEvent("idbg",EVENT_DELEGATE(TWalktest::toggleDebug));      
    acceptEvent("wire",EVENT_DELEGATE(TWalktest::toggleWire));  
    acceptEvent("pdbg",EVENT_DELEGATE(TWalktest::togglePhysicsDebug));      
    acceptEvent("cdbg",EVENT_DELEGATE(TWalktest::cycleDebug));
    acceptEvent("sprt",EVENT_DELEGATE(TWalktest::captureScreen));
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
            TString folder = folderArchives[i];
            TFile   file(folder.c_str());
            TString dir = file.get_dirname().c_str();
            if(dir.size())
                getFileSystem()->addFolderFileArchive(dir.c_str());
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
        acceptEvent("key.down.f9",EVENT_DELEGATE(TWalktest::cycleCamera));
    }
    getPlayerController()->setCamera(getActiveCamera());
    addHelpText("  Esc - Quit");

    return 0;
}

//-----------------------------------------------------------------------
//                              m a i n
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    const char  **argv=(const char**)__argv;
    int         argc=__argc;
#else
extern "C" {
    int main(int argc, const char **argv)
    {
#endif
        TWalktest app;

        app.setArgs(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }
#ifndef TUBRAS_PLATFORM_WIN32
}
#endif

