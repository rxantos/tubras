#include "idebug.h"
#include <assert.h>

#define WINDOW_SIZE_X       800
#define WINDOW_SIZE_Y       600
#define DEVICE_BPP          24

static IrrlichtDevice*      m_device;
static IVideoDriver*        m_videoDriver;
static ISceneManager*       m_sceneManager;
static IFileSystem*         m_fileSystem;
static IEventReceiver*      m_eventReceiver;
static IGUIEnvironment*     m_gui;
static IGUIFont*            m_defaultFont=0;
static IGUIFont*            m_monoFont=0;
static ICameraSceneNode*    m_camera;
static bool                 m_running=true;
static CTextOverlay*        m_debugOverlay;
static int                  m_capNumber=1;

static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
//static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 

IGUIEnvironment* getGUI()
{
    return m_gui;
}

void logTestString(irr::core::stringc str)
{
    printf(str.c_str());
}

//-----------------------------------------------------------------------------
//                             E v e n t R e c e i v e r
//-----------------------------------------------------------------------------
// used to suppress/enable engine debug messages
class EventReceiver : public IEventReceiver
{
    bool OnEvent(const SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            if( !event.KeyInput.PressedDown ) // key up?
            {
                switch(event.KeyInput.Key)
                {
                case KEY_ESCAPE:
                    m_running = false;
                    return true;
                case KEY_SNAPSHOT:
                    {
                        IImage* image = m_videoDriver->createScreenShot();
                        char buf[32];

                        sprintf(buf,"cap%.2d.png",m_capNumber++);

                        m_videoDriver->writeImageToFile(image,buf);

                        image->drop();
                        break;
                    }
                default:
                    break;
                }

            }
            return false;
    }

public:
    bool suppressEvents;
    EventReceiver() : IEventReceiver() {}

};

//-----------------------------------------------------------------------------
//                           _ c r e a t e D e v i c e
//-----------------------------------------------------------------------------
static IrrlichtDevice* _createDevice()
{
    m_eventReceiver = new EventReceiver();
    SIrrlichtCreationParameters cp;
    cp.DriverType = m_driverType;
    cp.WindowSize = dimension2du(WINDOW_SIZE_X,WINDOW_SIZE_Y);
    cp.Bits = DEVICE_BPP;
    cp.Fullscreen = false;
    cp.Vsync = false;
    cp.Stencilbuffer = false;
    cp.AntiAlias = false;
    cp.EventReceiver = m_eventReceiver;
    cp.WindowId = 0;

    return createDeviceEx(cp);
}

//-----------------------------------------------------------------------------
//                               _ i n i t
//-----------------------------------------------------------------------------
static void _init()
{

    //
    // set up the default font
    //        


    stringc fontFolder = "data/fnt/";
    stringc defFonts = fontFolder + "defaults.zip";
    if(m_fileSystem->existFile(defFonts.c_str()))
    {
        m_fileSystem->addZipFileArchive(defFonts.c_str());
        m_defaultFont = m_gui->getFont("tdeffont.xml");
        if(m_defaultFont)
        {
            m_defaultFont->grab();
            m_gui->getSkin()->setFont(m_defaultFont);
        }
        m_monoFont = m_gui->getFont("monospace.xml");
        if(m_monoFont)
        {
            m_monoFont->grab();
            //m_gui->getSkin()->setFont(m_monoFont);
        }
    }




    //
    // setup debug overlay
    //


    m_debugOverlay = new CTextOverlay("DebugInfo",rectf(0.25f,0.005f,0.75f,0.05f));
    m_debugOverlay->addItem("Node: Pos(x,y,z) Hpr(x,y,z) Dir(x,y,z)", EGUIA_CENTER);
    m_debugOverlay->addItem("Frame: Avg(0.0) Min(0.0) Max(0.0)", EGUIA_CENTER);
    m_debugOverlay->addItem("Visible Debug Data:", EGUIA_CENTER);

    m_debugOverlay->setVisible(true);


}

//-----------------------------------------------------------------------------
//                                  t e s t 1
//-----------------------------------------------------------------------------
void test1()
{


    m_device = _createDevice();
    if(!m_device)
        return;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    _init();

    m_device->setWindowCaption(L"idebug");

    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 100.0f, 100.0f);
    m_camera->setPosition(vector3df(0,10,0));

    /*
    scene::ISceneNode* n = m_sceneManager->addCubeSceneNode();
    if (n)
    {
    n->setMaterialTexture(0, m_videoDriver->getTexture("data/tex/t351sml.jpg"));
    n->setMaterialFlag(video::EMF_LIGHTING, false);
    scene::ISceneNodeAnimator* anim =
    m_sceneManager->createFlyCircleAnimator(core::vector3df(0,0,30), 20.0f);
    if (anim)
    {
    n->addAnimator(anim);
    anim->drop();
    }
    }
    */


    IGUIStaticText* stext = getGUI()->addStaticText(L" ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 ",
        rect<s32>(50,200,350,225),false,false,0,true);
    stext->setBackgroundColor(SColor(129,128,0,0));
    stext->setOverrideColor(SColor(255,255,255,255));

    stext = getGUI()->addStaticText(L" ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 ",
        rect<s32>(50,250,350,275),false,false,0,true);
    stext->setBackgroundColor(SColor(128,0,255,0));
    stext->setOverrideColor(SColor(255,255,255,255));

    IAnimatedMesh* pmesh;
    /*
    pmesh  = m_sceneManager->getMesh("data/mdl/Cube.irrmesh");
    if(pmesh)
    {
    IAnimatedMeshSceneNode* node = m_sceneManager->addAnimatedMeshSceneNode(pmesh, 0);   
    pmesh->setMaterialFlag(EMF_LIGHTING,false);
    node->setPosition(vector3df(0,0,30));
    node->setVisible(true);
    } 
    */

    SMaterial* mat = new SMaterial();
    ITexture* tex = m_videoDriver->getTexture("data/tex/grid.tga");
    mat->setTexture(0,tex);
    // causes static text background to disappear.
    mat->MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;

    mat->setFlag(EMF_LIGHTING,false);
    mat->getTextureMatrix(0).setTextureScale(50.0,50.0);

    dimension2d<f32> tileSize(50,50);
    dimension2d<u32> tileCount(6,6);
    pmesh = m_sceneManager->addHillPlaneMesh("testHillPlane"
        ,tileSize,tileCount,mat);
    IAnimatedMeshSceneNode* pnode;
    pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);


    while(m_device->run() && m_running)
    {
        m_videoDriver->beginScene(true, true, SColor(255,100,101,140));

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();
    }

    if(m_defaultFont)
        m_defaultFont->drop();
    if(m_monoFont)
        m_monoFont->drop();
    m_device->drop();
    delete m_eventReceiver;    

}

void test2()
{
    irr::IrrlichtDevice *device = irr::createDevice( irr::video::EDT_BURNINGSVIDEO);
    if(device)
        device->drop();
    device = irr::createDevice( irr::video::EDT_OPENGL);
    if(device)
        device->drop(); // exits here with code 1

    printf("reached.\n");
    // ... never reached 
}

bool materialAttributes(void)
{
    bool result = true;

    IrrlichtDevice *device =
        createDevice(video::EDT_OPENGL, dimension2du(160, 120), 32);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();

    //IAnimatedMesh* mesh = smgr->getMesh("../media/cube.irrmesh");

    IAnimatedMesh* mesh = smgr->getMesh("c:/gdev/scenes/meshes/cube.irrmesh");

    SMaterial& mat = mesh->getMeshBuffer(0)->getMaterial();
    if(mat.AntiAliasing != EAAM_FULL_BASIC)
    {
        logTestString("Invalid AntiAliasing Attribute.\n");
        result = false;
    }

    if(mat.ColorMask != ECP_RGB)
    {
        logTestString("Invalid ColorMask Attribute.\n");
        result = false;
    }

    for(int i=0; i<4; i++)
        if(mat.TextureLayer[i].LODBias != (i+1))
        {
            logTestString("Invalid Layer LODBias.\n");
            result = false;
        }

        device->run();
        smgr->drawAll();


        device->drop();
        return result;
}

void setScaleByMul( core::matrix4& mat, const vector3d<f32>& scale )
{

        mat(0,0) *= scale.X;
        mat(0,1) *= scale.X;
        mat(0,2) *= scale.X;

        mat(1,0) *= scale.Y;
        mat(1,1) *= scale.Y;
        mat(1,2) *= scale.Y;

        mat(2,0) *= scale.Z;
        mat(2,1) *= scale.Z;
        mat(2,2) *= scale.Z; 
}

core::vector3df getRotationDegrees(const core::matrix4& tmat ) 
{
    core::matrix4 mat = tmat;
    vector3df scale = mat.getScale();

    f64 Y = -asin(mat(0,2)/scale.X);
    const f64 C = cos(Y);
    Y *= RADTODEG64;

    f64 rotx, roty, X, Z;

    if (fabs(C)>ROUNDING_ERROR_f64)
    {
        const f32 invC = (f32)(1.0/C);
        rotx = mat(2,2) / scale.Z * invC;
        roty = mat(1,2) / scale.Y * invC;
        X = atan2( roty, rotx ) * RADTODEG64;
        rotx = mat(0,0) / scale.X * invC;
        roty = mat(0,1) / scale.X * invC;
        Z = atan2( roty, rotx ) * RADTODEG64;
    }
    else
    {
        X = 0.0;
        rotx = mat(1,1) / scale.Y;
        roty = -mat(1,0) / scale.Y;
        Z = atan2( roty, rotx ) * RADTODEG64;
    }

    // fix values that get below zero
    // before it would set (!) values to 360
    // that where above 360:
    if (X < 0.0) X += 360.0;
    if (Y < 0.0) Y += 360.0;
    if (Z < 0.0) Z += 360.0;

    return vector3d<f32>((f32)X,(f32)Y,(f32)Z);
}

void test3(const core::vector3df& Rotation, 
           const core::vector3df& Scale) 
{
    core::vector3df temp;

    printf("----------------------------------------------------------------------------\n");
    printf("                   org Scale: (%f, %f, %f)\n", Scale.X, Scale.Y, Scale.Z);
    printf("                org Rotation: (%f, %f, %f)\n\n", Rotation.X, Rotation.Y, Rotation.Z);

    // set scale via multiplication (this is what ISceneNode->getAbsoluteTransformation does)
    core::matrix4 mat;
    mat.setRotationDegrees(Rotation);
    temp = mat.getRotationDegrees();
    core::matrix4 smat;
    smat.setScale(Scale);
    mat *= smat;

    temp = mat.getRotationDegrees();
    printf("        getRotationDegrees(): (%f, %f, %f)\n", temp.X, temp.Y, temp.Z);
    temp = mat.getRotationDegreesDivScale();
    printf("getRotationDegreesDivScale(): (%f, %f, %f)\n", temp.X, temp.Y, temp.Z);
    core::quaternion q(mat);
    q.toEuler(temp);
    temp *= RADTODEG;
    //printf("quatRotation: (%f, %f, %f)\n", temp.X, temp.Y, temp.Z);
    temp = mat.getScale();
    printf("                     Scale(): (%f, %f, %f)\n\n", temp.X, temp.Y, temp.Z);
}

void test4()
{
    IrrlichtDevice* nd;
    IFileSystem* fs;
    IReadFile* rf;
    IFileArchive* fa;
    const IFileList* fl;
    bool rc;

    // CMountPointReader test
    nd = createDevice(EDT_NULL);

    fs = nd->getFileSystem();

    rc = fs->addFileArchive("/data/", true, false);

    fa = fs->getFileArchive(0);

    fl = fa->getFileList();

    u32 count = fl->getFileCount();
    for(u32 i=0; i<count; i++)
    {
        printf("       fileName: %s\n", fl->getFileName(i).c_str());
        printf("          isDir: %d\n", fl->isDirectory(i));
        printf("   FullFileName: %s\n", fl->getFullFileName(i).c_str());
        printf("           Path: %s\n", fl->getPath().c_str());
        printf("\n");
    }


    rf = fs->createAndOpenFile("media/plane.irrmesh");
    if(rf)
        printf("open media/plane.irrmesh success.\n");
    else
        printf("open media/plane.irrmesh failed.\n");
    if(rf)
        rf->drop();

    nd->drop();
}

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib") 
#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup") 
#endif
int main(int argc, char* argv[])
{

    //test1();

    /*
    core::vector3df Scale(10.f, 10.f, 10.f);

    test3(core::vector3df(25.f, 25.f, 25.f), Scale);
    test3(core::vector3df(25.f, 0.f, 0.f), Scale);
    test3(core::vector3df(0.f, 25.f, 0.f), Scale);
    test3(core::vector3df(0.f, 0.f, 25.f), Scale);

    test3(core::vector3df(10.5f, 25.5f, 60.f), core::vector3df(1.f,1.f,1.f));
    */

    test4();

    //materialAttributes();
    return 0;
}

