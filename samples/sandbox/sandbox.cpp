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

    TDynamicNode* dnode;
    TPlaneNode* pnode = (TPlaneNode*)addSceneNode("TPlaneNode",getRootSceneNode());
    pnode->initialize(300.0,TVector3::UNIT_Y);
    pnode->setPosition(TVector3(0,0,0));
    SMaterial& mat = pnode->getMaterial(0);
    ITexture* tex = getTexture("data/tex/grid.tga");
    mat.setTexture(0,tex);
    mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    mat.setFlag(EMF_LIGHTING,false);
    mat.getTextureMatrix(0).setTextureScale(20.0,20.0);

    TColliderPlane* planeShape = new TColliderPlane(TVector3::UNIT_Y,300.0);
    /*
    dnode = new TDynamicNode("Viewer_ZXPlane::pnode",pnode,planeShape,0.0f);
    dnode->setFriction(1);
    dnode->setRestitution(0.0);
    */

    //
    // turn gravity on
    //
    getPhysicsManager()->getWorld()->setGravity(TVector3(0,-9.68f,0));


    //
    // create a kinematic node and attach controllers
    //
    ISceneNode* m_cube = loadModel("data/mdl/Cube.mesh");
    if(!m_cube)
    {
        m_cube = getSceneManager()->addCubeSceneNode(3.0f);
    }

    m_cube->setPosition(TVector3(0,8,0));
    m_cube->setMaterialFlag(EMF_LIGHTING,false);

    
    TColliderShape* shape = new TColliderBox(m_cube);
    dnode = new TDynamicNode("cube1::pnode",m_cube,shape,0.0,btKinematic);
    dnode->allowDeactivation(false);
    
    new Tubras::TRotateController("cube::rotatorx",m_cube,200.0,TVector3::UNIT_Y);
    //new Tubras::TRotateController("cube::rotatorz",m_cube,100.0,TVector3::UNIT_Z);
    //new Tubras::TOscillateController("cube::oscillator",m_cube,0.6f,4.0f,TVector3::UNIT_Z);

    //
    // setup dynamic nodes
    //
    //m_cube = getSceneManager()->addCubeSceneNode(3.0f);
    //m_cube->setPosition(TVector3(0,20,0));
    //m_cube->setMaterialFlag(EMF_LIGHTING,false);
    //shape = new TColliderBox(m_cube);
    //new TDynamicNode("cube2::pnode",m_cube,shape,5.0);


    getCurrentCamera()->setPosition(TVector3(0.f,25.f,-50.f));

    /*
    TSound* sound = loadSound("whirl_mono.ogg","General",true);
    TSoundNode* snode = new TSoundNode("Cube::snode",m_cube,sound);

    sound->set3DMinDistance(2.0);
    sound->setLoop(true);
    sound->play();
    setSoundListener(getCamera("Camera::Default"));
    */


   

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

