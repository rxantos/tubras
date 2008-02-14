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
TSandbox::TSandbox(int argc,char **argv) : TApplication(argc,argv,"sandbox"),
m_screen(0)
{
}

//-----------------------------------------------------------------------
//                          ~ T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::~TSandbox()
{
    if(m_screen)
        m_screen->drop();
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
void TSandbox::OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
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
            TColliderMesh* cm = new TColliderMesh(mnode);
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
int TSandbox::initialize()
{
    if(TApplication::initialize())
        return 1;

    
    addHelpText("wasd - Camera movement");
    
    addHelpText("   i - Invert mouse");
    addHelpText(" prt - Screen capture");
    addHelpText("  F1 - Toggle help");
    addHelpText("  F2 - Toggle debug");
    addHelpText("  F3 - Cycle wire/pts");
    addHelpText("  F4 - Toggle Phys dbg");
    addHelpText("  F5 - Cycle dbg data");
    

    
    acceptEvent("key.down.f1",EVENT_DELEGATE(TSandbox::toggleHelp));
    acceptEvent("key.down.f2",EVENT_DELEGATE(TSandbox::toggleDebug));      
    acceptEvent("key.down.f3",EVENT_DELEGATE(TSandbox::toggleWire));  
    acceptEvent("key.down.f4",EVENT_DELEGATE(TSandbox::togglePhysicsDebug));      
    acceptEvent("key.down.f5",EVENT_DELEGATE(TSandbox::cycleDebug));
    acceptEvent("key.down.prtscr",EVENT_DELEGATE(TSandbox::captureScreen));
    acceptEvent("key.down.esc",EVENT_DELEGATE(TSandbox::quit));  
    acceptEvent("gui.clicked",EVENT_DELEGATE(TSandbox::onClick));
   
    /*
    TEmptyNode* enode = (TEmptyNode *)addSceneNode("TEmptyNode",getRootSceneNode());  

   
    
    TPlaneNode* pnode = (TPlaneNode*)addSceneNode("TPlaneNode",getRootSceneNode());


    pnode->initialize(300.0,TVector3::UNIT_Y);
    pnode->setPosition(TVector3(0,-5,0));
    SMaterial& mat = pnode->getMaterial(0);
    ITexture* tex = getTexture("data/tex/grid.tga");
    mat.setTexture(0,tex);    
    mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    mat.setFlag(EMF_LIGHTING,false);
    mat.getTextureMatrix(0).setTextureScale(20.0,20.0);
    
    
    
    ISceneNode* node = getSceneManager()->addCubeSceneNode(10);
	node->setPosition(TVector3(0,-15,-25));
    SMaterial& mat2 = node->getMaterial(0);
    mat2.setFlag(EMF_LIGHTING,false);
    mat2.AmbientColor = TColour(255,0,0);
    mat2.DiffuseColor = TColour(255,0,0);

    
    new TRotateController("testRot",node,180.0);
    new TOscillateController("testOsc",node,1.0,20.0);
    
    
    IAnimatedMesh* mesh = getSceneManager()->addArrowMesh("testArrow",
        SColor(255,255,0,0), SColor(255,255,255,0),16,256,10,8,1,3);
    node = getSceneManager()->addMeshSceneNode(mesh->getMesh(0));
    node->getMaterial(0).setFlag(EMF_LIGHTING,false);
    node->getMaterial(1).setFlag(EMF_LIGHTING,false);

    new TRotateController("testRot2",node,250.0,TVector3::UNIT_Z);
    new TOscillateController("testOsc2",node,1.0,10.0,TVector3::UNIT_Z);    
    

    
    TSound* sound = loadSound("data/snd/ambient.ogg");
    sound->setLoop(true);
    //sound->play();

    */
        

    TString scene = m_config->getString("loadscene","options");
    TString mesh = m_config->getString("loadmesh","options");
    bool rc=false;

    if(scene.size() > 0)
        rc = getSceneManager()->loadScene(scene.c_str(), this);
    if(!rc && (mesh.size() > 0))
    {
        IAnimatedMesh* pmesh  = getSceneManager()->getMesh(mesh.c_str());
        ISceneNode* node = getSceneManager()->addAnimatedMeshSceneNode(pmesh);
    }
    

    TCameraNode* cam = getCurrentCamera();

    cam->setPosition(TVector3(0.6f,1.4f,-13.f));


    /*

    TTaskDelegate* td = TASK_DELEGATE(TSandbox::testTask);
    TTask* task = new TTask("testTask",td,0,0,NULL,"");
    task->start();
    */
    s32 w=256,h=64,x,y;

    TDimension d = getRenderer()->getVideoDriver()->getScreenSize();
    x = d.Width - w - 3;
    y = 3;

    
    m_screen = new TGUIScreen(5);

    //IGUIButton* btn = getGUIFactory()->addButton(TRectd(x,y,x+w,y+h), m_screen, GID_QUIT, L"Quit");

    TGraphicsDlg* gd = getGUIFactory()->addGraphicsDlg(m_screen);    
    
    IGUIWindow* win = getGUIManager()->addWindow(TRectd(50,50,450,450),false,L"Test Window", m_screen);
    win->getCloseButton()->setVisible(false);

    w = 192;
    getGUIManager()->addButton(TRectd(50,50,50+w/2,50+h/2), win, -1, L"Save");
    

    m_screen->setVisible(true);
    

    //getGUIManager()->addCheckBox(false,TRectd(20,40,140,60),getGUIManager()->getRootGUIElement(),-1,L"Test Checkbox");

    
    //
    // interval 0.0-1.0 for a period of 4 seconds, ease in blending.
    //
    //TInterval* interval = new TInterval("testInterval",0.f,1.f,4.0f,INTERVAL_DELEGATE(TSandbox::testInterval),0,btEaseIn);

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
        //m_breakOnAlloc(1538);
        //m_breakOnAlloc(1545);
        TSandbox app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }
#ifndef TUBRAS_PLATFORM_WIN32
} // extern "C"
#endif

