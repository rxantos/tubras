//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tsltest.h"
using namespace Tubras;

//-----------------------------------------------------------------------------
//                                T S L T e s t
//-----------------------------------------------------------------------------
TSLTest::TSLTest() : TApplication("TSLTest")
{
}

//-----------------------------------------------------------------------------
//                               ~ T S L T e s t
//-----------------------------------------------------------------------------
TSLTest::~TSLTest()
{
}

//-----------------------------------------------------------------------------
//                       h a n d l e S c r i p t E r r o r
//-----------------------------------------------------------------------------
int TSLTest::handleScriptError(irr::core::stringc fileName, int line, int code, 
                               irr::core::stringc errMessage)
{
    logMessage(LOG_ERROR, "TSL Error (%d), file: %s", code, fileName.c_str());
    logMessage(LOG_ERROR, "    line: %d, message: %s", line, errMessage.c_str());
    return 0;
}

//-----------------------------------------------------------------------------
//                                 q u i t
//-----------------------------------------------------------------------------
int TSLTest::quit(const TEvent* event)
{
    TApplication::stopRunning();
    return 1;
}

//-----------------------------------------------------------------------------
//                             t o g g l e W i r e
//-----------------------------------------------------------------------------
int TSLTest::toggleWire(const TEvent* event)
{
    TRenderer* renderer = getRenderer();

    if(renderer->getRenderMode() == rmNormal)
        renderer->setRenderMode(rmWire);
    else
        renderer->setRenderMode(rmNormal);
    return 1;
}

//-----------------------------------------------------------------------------
//                           _ c r e a t e S c e n e
//-----------------------------------------------------------------------------
void TSLTest::_createScene()
{
    dimension2df tileSize(50,50);
    dimension2d<u32> tileCount(6,6);

    SMaterial mat, mat2;

    ISceneManager* m_sceneManager = getSceneManager();
    IrrlichtDevice* m_device = getRenderer()->getDevice();
    IVideoDriver* m_videoDriver = getRenderer()->getVideoDriver();

    IAnimatedMesh* pmesh = m_sceneManager->addHillPlaneMesh("floorPlane"
        ,tileSize,tileCount);
    IAnimatedMeshSceneNode* pnode;
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0,-5, 0));
    //
    // this COPIES the materials and material layer parameters.  it doesn't set
    // a reference... so in order for animation (if any) to work we need to 
    // add a "ref" to the material owned by the node.  kludge, but it works
    // without having to modify the engine source.
    //
    if(m_config->getMaterial(m_device, "floor",pnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("floor"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("floor", pnode->getMaterial(0));
    }

    //
    // solid color using 2x2 image and "emissive"
    //
    u8* data = new u8[2 * 2 * 4]; 
    IImage* image = m_videoDriver->createImageFromData(ECF_A8R8G8B8, dimension2du(2,2), data);
    image->fill(SColor(255, 255, 255, 255));
    ITexture* tex = m_videoDriver->addTexture("__WHITE2X2__",image);
    image->drop();

    mat2.MaterialType = EMT_SOLID;
    mat2.setFlag(EMF_LIGHTING, true);
    mat2.setTexture(0,tex);
    mat2.setFlag(EMF_BACK_FACE_CULLING , false);
    mat2.EmissiveColor = SColor(255, 255, 0, 255);

    tileSize.Width = 30;
    tileSize.Height = 30;
    tileCount.Width = 2;
    tileCount.Height = 2;

    //
    // plane that contains a semi-transparent red pattern
    //
    pmesh = m_sceneManager->addHillPlaneMesh("redPattern" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0, 25, 100));
    pnode->setRotation(vector3df(-90, 0, 0));
    //
    // this COPIES the materials and material layer parameters.  it doesn't set
    // a reference... so in order for animation (if any) to work we need to 
    // add a "ref" to the material owned by the node.  kludge, but it works
    // without having to modify the engine source.
    //
    if(m_config->getMaterial(m_device, "redPattern", pnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("redPattern"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("redPattern", pnode->getMaterial(0));
    }

    //
    // cube
    //
    IMeshSceneNode* cnode = m_sceneManager->addCubeSceneNode();
    cnode->setScale(core::vector3df(10.0,10.0,10.0));
    cnode->setPosition(vector3df(0, -60, 0));
    if(m_config->getMaterial(m_device, "cubeMat",cnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("cubeMat"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("cubeMat", cnode->getMaterial(0));
    }

    //
    // left/right spheres
    //
    cnode = m_sceneManager->addSphereSceneNode();
    cnode->setScale(core::vector3df(2.0,2.0,2.0));
    cnode->setPosition(vector3df(-90, 40, 100));
    if(m_config->getMaterial(m_device, "leftSphere",cnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("leftSphere"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("leftSphere", cnode->getMaterial(0));
    }

    cnode = m_sceneManager->addSphereSceneNode();
    cnode->setScale(core::vector3df(2.0,2.0,2.0));
    cnode->setPosition(vector3df(90, 40, 100));
    if(m_config->getMaterial(m_device, "rightSphere",cnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("rightSphere"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("rightSphere", cnode->getMaterial(0));
    }

    //
    // left/right panel backgrounds
    //
    tileSize.Width = 20;
    tileSize.Height = 20;
    tileCount.Width = 1;
    tileCount.Height = 1;
    pmesh = m_sceneManager->addHillPlaneMesh("leftPanelBG" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(-45, 25, 100));
    pnode->setRotation(vector3df(-90, -45, 0));

    if(m_config->getMaterial(m_device, "leftPanelBG",pnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("leftPanelBG"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("leftPanelBG", pnode->getMaterial(0));
    }

    pmesh = m_sceneManager->addHillPlaneMesh("rightPanelBG" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(45, 25, 100));
    pnode->setRotation(vector3df(-90, 45, 0));

    if(m_config->getMaterial(m_device, "rightPanelBG",pnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("rightPanelBG"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("rightPanelBG", pnode->getMaterial(0));
    }

    //
    // left/right panel foregrounds
    //
    tileSize.Width = 15;
    tileSize.Height = 15;
    pmesh = m_sceneManager->addHillPlaneMesh("leftPanelFG" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(-44.6f, 25.f, 99.98f));
    pnode->setRotation(vector3df(-90, -45, 0));

    if(m_config->getMaterial(m_device, "leftPanelFG",pnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("leftPanelFG"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("leftPanelFG", pnode->getMaterial(0));
    }


    pmesh = m_sceneManager->addHillPlaneMesh("rightPanelFG" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(44.6f, 25.f, 99.98f));
    pnode->setRotation(vector3df(-90.f, 45.f, 0.f));

    if(m_config->getMaterial(m_device, "rightPanelFG",pnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("rightPanelFG"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("rightPanelFG", pnode->getMaterial(0));
    }

    //
    // leaf billboard
    //
    IBillboardSceneNode* bnode = m_sceneManager->addBillboardSceneNode();
    bnode->setSize(core::dimension2d<f32>(28, 28));
    bnode->setPosition(vector3df(0,8,15));
    mat2.EmissiveColor = SColor(255, 200, 128, 128);
    if(m_config->getMaterial(m_device, "leafBillBoard",bnode->getMaterial(0)) &&
        m_config->isAnimatedMaterial("leafBillBoard"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("leafBillBoard", bnode->getMaterial(0));
    }

    //
    // "the world is yours" background & foreground
    //
    tileSize.Width = 1;
    tileSize.Height = 1;
    tileCount.Width = 140;
    tileCount.Height = 40;
    pmesh = m_sceneManager->addHillPlaneMesh("twimbg" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0, 25, 150));
    pnode->setRotation(vector3df(-90, 0, 0));
    m_config->getMaterial(m_device, "twimbg",pnode->getMaterial(0));

    pmesh = m_sceneManager->addHillPlaneMesh("twimfg" ,tileSize, tileCount);
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
    pnode->setPosition(vector3df(0, 25, 149.f));
    pnode->setRotation(vector3df(-90, 0, 0));
    pnode->setScale(vector3df(0.96f, 1.f, 1.f));
    m_config->getMaterial(m_device, "twimfg",pnode->getMaterial(0));
    if(m_config->isAnimatedMaterial("twimfg"))
    {
        // add a ref to the universal material layer animator (scroll, scale, rotation).
        m_config->addAnimationRef("twimfg", pnode->getMaterial(0));
    }

    //
    // GUI element instantiation
    //
    irr::gui::IGUIElement* el = m_config->getGUIElement(m_device, "helpText");
    // make this scriptable
    if(el)
    {
        ((IGUIStaticText*)el)->setOverrideColor(SColor(255, 255, 255, 255));
    }

    el = m_config->getGUIElement(m_device, "testWindow");
}

//-----------------------------------------------------------------------------
//                              i n i t i a l i z e
//-----------------------------------------------------------------------------
int TSLTest::initialize()
{
    if(TApplication::initialize())
        return 1;

    acceptEvent("quit",EVENT_DELEGATE(TSLTest::quit)); 
    acceptEvent("input.key.down.f3", EVENT_DELEGATE(TSLTest::toggleWire));

    m_config = new TConfig();
    Tubras::TString sname = this->getConfig()->getString("options.loadscript");

    if(m_config->loadScript(sname, false, false, this) != E_OK)
    {
        printf("Error loading script.\n");
        return 1;
    }

    _createScene();

    delete m_config;

    return 0;
}

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
#ifdef _IRR_WINDOWS_
#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup")
#endif

int main(int argc, const char* argv[])
{

    TSLTest app;

    app.setArgs(argc,argv);

    if(!app.initialize())
        app.run();

    return 0;
}
