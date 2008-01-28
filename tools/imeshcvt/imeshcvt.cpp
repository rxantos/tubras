//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include <errno.h>

static IrrlichtDevice*      m_device;
static IVideoDriver*        m_videoDriver;
static ISceneManager*       m_sceneManager;
static IAnimatedMesh*       m_inputMesh;
static stringc              m_iMeshName;
static stringc              m_oMeshName;
static IFileSystem*         m_fileSystem;
static ILogger*             m_logger;
static s32                  m_meshIndex=0;
static u32                  m_loadTime;
static array<SMaterial>     m_materials;
static IMeshManipulator*    m_meshManipulator;
static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;

//-----------------------------------------------------------------------------
//                             E v e n t R e c e i v er
//-----------------------------------------------------------------------------
// used to suppress/enable engine debug messages
class EventReceiver : public IEventReceiver
{
    bool OnEvent(const SEvent& event)
    {
        return suppressEvents;
    }

public:
    bool suppressEvents;
    EventReceiver() : IEventReceiver(), suppressEvents(true) {}

};

//-----------------------------------------------------------------------------
//                              f i l e E x i s t s
//-----------------------------------------------------------------------------
bool fileExists(const stringc fileName)
{
    struct stat buf;
    if(stat(fileName.c_str(),&buf) != 0)
    {
        if(errno == ENOENT)
        {
            return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------------
//                           g e t P a t h
//-----------------------------------------------------------------------------
stringc getPath(const stringc fileName)
{
    stringc result;
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath( fileName.c_str(), drive, dir, fname, ext ); 

    result = drive;
    result += dir;

    return result;
}

//-----------------------------------------------------------------------------
//                           g e t E x t e n s i o n
//-----------------------------------------------------------------------------
stringc getExtension(const stringc fileName)
{
    stringc result;
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath( fileName.c_str(), drive, dir, fname, ext ); // C4996

    result = ext;
    result.make_lower();

    return result;
}

//-----------------------------------------------------------------------------
//                             a d d M a t e r i a l
//-----------------------------------------------------------------------------
bool addMaterial(SMaterial material)
{
    for(u32 i=0; i<m_materials.size();i++)
    {
        if(material == m_materials[i])
            return false;
    }
    m_materials.push_back(material);
    return true;
}

//-----------------------------------------------------------------------------
//                             s h o w M e s h I n f o
//-----------------------------------------------------------------------------
void showMeshInfo()
{
    u32 frameCount,bufferCount;
    u32 gVerts=0, gTris=0, gBuffers=0, gMaterials=0;
    E_ANIMATED_MESH_TYPE mType;
    aabbox3d<f32> bbox;
    IMesh*  mesh;



    mType = m_inputMesh->getMeshType();
    frameCount = m_inputMesh->getFrameCount();
    bufferCount = m_inputMesh->getMeshBufferCount();
    bbox = m_inputMesh->getBoundingBox();

    for(u32 i=0; i<frameCount; i++)
    {
        mesh = m_inputMesh->getMesh(i);
        u32 bCount = mesh->getMeshBufferCount();
        gBuffers += bCount;
        for(u32 j=0; j<bCount; j++)
        {
            IMeshBuffer* buffer = mesh->getMeshBuffer(j);
            gVerts += buffer->getVertexCount();
            gTris += (buffer->getIndexCount() / 3);
            if(addMaterial(buffer->getMaterial()))
                ++gMaterials;
        }

    }

    printf("\n--------------- Mesh Info ----------------\n");
    printf("      Load Time: %dms\n", m_loadTime);
    printf("      Mesh Type: ");
    switch(mType)
    {
    case EAMT_UNKNOWN: printf("UNKNOWN\n"); break;
    case EAMT_MD2: printf("MD2\n"); break;
    case EAMT_MD3: printf("MD3\n"); break;
    case EAMT_OBJ: printf("OBJ\n"); break;
    case EAMT_BSP: printf("BSP\n"); break;
    case EAMT_3DS: printf("3DS\n"); break;
    case EAMT_MY3D: printf("MY3D\n"); break;
    case EAMT_LMTS: printf("LMTS\n"); break;
    case EAMT_CSM: printf("CSM\n"); break;
    case EAMT_OCT: printf("OCT\n"); break;
    case EAMT_SKINNED: printf("SKINNED\n"); break;
    default: printf("UNDEFINED\n");
    }
    printf("   AFrame Count: %d\n",frameCount);
    printf("  ABuffer Count: %d\n", bufferCount);
    printf(" Material Count: %d\n", gMaterials);
    printf("   Buffer Count: %d\n", gBuffers);
    printf("   Vertex Count: %d\n", gVerts);
    printf(" Triangle Count: %d\n", gTris);
}

#ifdef WIN32
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}
#endif


//-----------------------------------------------------------------------------
//                    c r e a t e H i d d e n W i n d o w
//-----------------------------------------------------------------------------
void* createHiddenWindow()
{
    void* id = 0;
#ifdef WIN32
    const c8* ClassName = "CIrrDeviceWin32";
    HWND    HWnd;
    HINSTANCE hInstance=0;

    // Register Class
    WNDCLASSEX wcex;
    wcex.cbSize		= sizeof(WNDCLASSEX);
    wcex.style		= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= (WNDPROC)WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= 0;
    wcex.hIcon		= NULL;
    wcex.hCursor		= 0;
    wcex.hbrBackground	= 0;
    wcex.lpszMenuName	= 0;
    wcex.lpszClassName	= ClassName;
    wcex.hIconSm		= 0;
    RegisterClassEx(&wcex);

    // calculate client size

    RECT clientSize;
    clientSize.top = 0;
    clientSize.left = 0;
    clientSize.right = 640;
    clientSize.bottom = 480;

    DWORD style = WS_POPUP;

    style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;


    u32 windowLeft = 0;
    u32 windowTop = 0;

    // create window

    HWnd = CreateWindow( ClassName, "", style, windowLeft, windowTop,
        clientSize.right, clientSize.bottom,	NULL, NULL, hInstance, NULL);

    ShowWindow(HWnd , SW_HIDE);
    UpdateWindow(HWnd);
    id = (void *) HWnd;

#endif
    return id;

}

//-----------------------------------------------------------------------------
//                           d e s t r o y W i n d o w
//-----------------------------------------------------------------------------
void destroyWindow(void *id)
{
#ifdef WIN32
    CloseWindow((HWND)id);
#endif
}

//-----------------------------------------------------------------------------
//                               s h o w U s a g e
//-----------------------------------------------------------------------------
void showUsage()
{
    printf("usage: imeshcvt <options> -i[input file] -o<output file>\n\n");
    printf("       <options> - Mesh Manipulator options:\n");
    printf("                     -n : recalculate normals\n");
    printf("                     -s : recalculate normals smooth\n");
    printf("                     -f : flip surfaces\n");
    printf("                     -9 : use D3D9 device\n");
    printf("    [input file] - input mesh file to convert or report on.\n");
    printf("                   if no output mesh is specified, info is \n");
    printf("                   displayed for the input mesh. Required.\n\n");
    printf("   <output file> - output mesh file to convert to.\n\n");
}

//-----------------------------------------------------------------------------
//                                  m a i n
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    bool oRecalcNormals=false;
    bool oSmooth=false;
    bool oFlipSurfaces=false;

    printf("imeshcvt 0.1 Copyright(C) 2008 Tubras Software, Ltd\n\n");

    if(argc < 2)
    {
        showUsage();
        return 1;
    }

    int c;
    while ((c = getopt(argc, argv, "9nsfi:o:")) != EOF)
    {
        switch (c)
        {
        case 'n':
            oRecalcNormals = true;
            break;
        case 's':
            oRecalcNormals = true;
            oSmooth = true;
            break;
        case 'f':
            oFlipSurfaces = true;
            break;
        case 'i':
            m_iMeshName = optarg;
            break;
        case 'o':
            m_oMeshName = optarg;
            break;
        case '9':
            m_driverType = EDT_DIRECT3D9;
            break;
        }        
    }

    if(!m_iMeshName.size())
    {
        if(optind >= argc)
        {
            showUsage();
            return 1;
        }
        m_iMeshName = argv[optind++];
    }

    if(!m_oMeshName.size() && (optind < argc))
        m_oMeshName = argv[optind++];

    printf(" Input Mesh: %s\n",m_iMeshName.c_str());
    printf("Output Mesh: %s\n",m_oMeshName.c_str());

    if(!fileExists(m_iMeshName))
    {
        printf("\nError: Input Mesh Doesn't Exist\n");
        return 1;
    }

    //
    // we need to use a "real" renderer otherwise the 
    // material conversions won't work properly (all will
    // be set to EMT_SOLID with the null renderer).
    //
    // because of this, we create/use a hidden window to
    // maintain the appearence of a command line program.
    //
    EventReceiver *er = new EventReceiver();
    SIrrlichtCreationParameters cp;
    cp.DriverType = m_driverType;
    cp.WindowSize = dimension2d<s32>(640,480);
    cp.Bits = 16;
    cp.Fullscreen = false;
    cp.Vsync = false;
    cp.Stencilbuffer = false;
    cp.AntiAlias = false;
    cp.EventReceiver = er;
    cp.WindowId = createHiddenWindow();

    m_device = createDeviceEx(cp);

    m_logger = m_device->getLogger();
    m_logger->setLogLevel(ELL_NONE);
    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();

    //
    // add location of input mesh path to the file system
    //
    m_fileSystem->addFolderFileArchive(getPath(m_iMeshName).c_str());

    //
    // add our experiment binary mesh loader (.irrbmesh)
    //
    m_sceneManager->addExternalMeshLoader(new CIrrBMeshFileLoader(m_videoDriver,m_sceneManager,m_fileSystem));

    er->suppressEvents = false;
    ITimer* timer = m_device->getTimer();
    u32 start = timer->getRealTime();

    m_inputMesh = m_sceneManager->getMesh(m_iMeshName.c_str());

    m_loadTime = timer->getRealTime() - start;

    //
    // input mesh only?
    //

    if(!m_oMeshName.size())
    {
        showMeshInfo();
        m_device->drop();
        destroyWindow(cp.WindowId);
        return 0;
    }

    stringc ext = getExtension(m_oMeshName);

    IMeshWriter*    writer=0;

    m_meshManipulator = m_sceneManager->getMeshManipulator();

    if(ext == ".irrmesh")
        writer = m_sceneManager->createMeshWriter(EMWT_IRR_MESH);
    else if(ext == ".irrbmesh")
        // explicitly create for now...
        writer = new CIrrBMeshWriter(m_videoDriver,m_fileSystem);
    else if(ext == ".dae")
        writer = m_sceneManager->createMeshWriter(EMWT_COLLADA);
    else if(ext == ".stl")
        writer = m_sceneManager->createMeshWriter(EMWT_STL);

    if(writer)
    {
        IWriteFile* file;
        file = m_fileSystem->createAndWriteFile(m_oMeshName.c_str());
        if((m_meshIndex >= 0) && (m_meshIndex < (s32)m_inputMesh->getFrameCount()))
        {
            IMesh* mesh = m_inputMesh->getMesh(m_meshIndex);
            if(oFlipSurfaces)
            {
                printf("Flipping Mesh Surfaces...\n");
                m_meshManipulator->flipSurfaces(mesh);
            }
            if(oRecalcNormals)
            {
                printf("Recalculating Normals, Smooth: %i\n",oSmooth);
                m_meshManipulator->recalculateNormals(mesh,oSmooth);
            }
            writer->writeMesh(file,mesh);
        }
        else
        {
            printf("Error: Invalid Mesh Index\n");
        }
        writer->drop();
    }
    else
    {
        printf("Error: Unable To Create Writer For Output Mesh\n");
    }

    m_device->drop();
    destroyWindow(cp.WindowId);
    return 0;
}

