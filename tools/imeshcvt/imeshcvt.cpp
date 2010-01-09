//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
	// find last forward or backslash
	s32 lastSlash = fileName.findLast('/');
	const s32 lastBackSlash = fileName.findLast('\\');
	lastSlash = lastSlash > lastBackSlash ? lastSlash : lastBackSlash;

	if ((u32)lastSlash < fileName.size())
		return fileName.subString(0, lastSlash);
	else
		return ".";
}

//-----------------------------------------------------------------------------
//                           g e t E x t e n s i o n
//-----------------------------------------------------------------------------
stringc getExtension(const stringc fileName)
{

    s32 lastDot = fileName.findLast('.');
    if(lastDot)
        return fileName.subString(lastDot,fileName.size()-lastDot);
    else
        return "";
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
    printf("   AFrame Count: %d\n", frameCount);
    printf("  ABuffer Count: %d\n", bufferCount);
    printf(" Material Count: %d\n", gMaterials);
    printf("   Buffer Count: %d\n", gBuffers);
    printf("   Vertex Count: %d\n", gVerts);
    printf(" Triangle Count: %d\n", gTris);
}

//-----------------------------------------------------------------------------
//                            s t r T o V e r s i o n
//-----------------------------------------------------------------------------
u16 strToVersion(const char *sversion)
{
    u16 result=IRRB_VERSION;
    stringc temp=sversion,hi,lo;
    s32 pos;

    pos = temp.findFirst('.');
    if(pos < 0)
        return result;

    hi = temp.subString(0,pos);
    lo = temp.subString(pos+1, temp.size());

    result = (atoi(hi.c_str()) << 8) | atoi(lo.c_str());


    return result;
}

//-----------------------------------------------------------------------------
//                               s h o w U s a g e
//-----------------------------------------------------------------------------
void showUsage()
{
    printf("usage: imeshcvt <options> -i[input file] -o<output file>\n\n");
    printf("       <options> - Generic options:\n");
    printf("                     -a : folder archive\n");
    printf("                     -v : target mesh version\n");
    printf("       <options> - Mesh Manipulator options:\n");
    printf("                     -f : flip surfaces\n");
    printf("                     -n : recalculate normals\n");
    printf("                     -s : recalculate normals smooth\n");
    printf("                     -t : create tangents\n");
    printf("\n");
    printf("    [input file] - Input mesh file to convert or report on.\n");
    printf("                   if no output mesh is specified, info is \n");
    printf("                   displayed for the input mesh. Required.\n\n");
    printf("   <output file> - Output mesh file to convert to.\n\n");
}

//-----------------------------------------------------------------------------
//                                  m a i n
//-----------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
    bool oRecalcNormals=false;
    bool oSmooth=false;
    bool oFlipSurfaces=false;
    bool oCreateTangents=false;
    u16  oIrrbVersion=IRRB_VERSION;
    TArray<stringc> folderArchives;
    stringc baseDirectory="";


    printf("imeshcvt 0.4\n\n");

    if(argc < 2)
    {
        showUsage();
        return 1;
    }

    int c;
    while ((c = getopt(argc, argv, "9nstfi:o:a:v:")) != EOF)
    {
        switch (c)
        {
        case 'a':
            folderArchives.push_back(optarg);
            baseDirectory = optarg;
            break;
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
        case 't':
            oCreateTangents = true;
            break;
        case 'i':
            m_iMeshName = optarg;
            break;
        case 'o':
            m_oMeshName = optarg;
            break;
        case 'v':
            oIrrbVersion = strToVersion(optarg);
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

    EventReceiver *er = new EventReceiver();
    SIrrlichtCreationParameters cp;
    cp.DriverType = EDT_NULL;
    cp.WindowSize = dimension2du(640,480);
    cp.Bits = 16;
    cp.Fullscreen = false;
    cp.Vsync = false;
    cp.Stencilbuffer = false;
    cp.AntiAlias = false;
    cp.EventReceiver = er;
    cp.WindowId = 0;

    m_device = createDeviceEx(cp);

    m_logger = m_device->getLogger();
    m_logger->setLogLevel(ELL_NONE);
    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();

    // add folder archives specified on the command line
    for(u32 i=0;i<folderArchives.size();i++)
    {
        stringc folder = folderArchives[i];
        m_fileSystem->addFileArchive(folder.c_str(), false, false, EFAT_FOLDER);
    }

    //
    // add our experimental binary mesh loader (.irrbmesh)
    //
    CIrrBMeshFileLoader* loader = new CIrrBMeshFileLoader(m_sceneManager,m_fileSystem);
    m_sceneManager->addExternalMeshLoader(loader);
    loader->drop();

    er->suppressEvents = false;
    ITimer* timer = m_device->getTimer();
    u32 start = timer->getRealTime();


    stringc saveDir = m_fileSystem->getWorkingDirectory();
    m_fileSystem->changeWorkingDirectoryTo(baseDirectory);

    m_inputMesh = m_sceneManager->getMesh(m_iMeshName.c_str());

    m_fileSystem->changeWorkingDirectoryTo(saveDir);


    if(!m_inputMesh)
    {

        printf("\nError: Unable To Open Input Mesh\n");
        delete er;
        m_device->drop();
        return 1;
    }

    m_loadTime = timer->getRealTime() - start;

    //
    // input mesh only?
    //

    if(!m_oMeshName.size())
    {
        showMeshInfo();
        m_device->drop();
        delete er;
        return 0;
    }

    stringc ext = getExtension(m_oMeshName);

    IMeshWriter*    writer=0;

    m_meshManipulator = m_sceneManager->getMeshManipulator();

    if(ext == ".irrmesh")
        writer = m_sceneManager->createMeshWriter(EMWT_IRR_MESH);
    else if(ext == ".irrbmesh")
    {
        // explicitly create for now...
        writer = new CIrrBMeshWriter(m_videoDriver,m_fileSystem);
        ((CIrrBMeshWriter*)writer)->setVersion(oIrrbVersion);
        ((CIrrBMeshWriter*)writer)->setCreator("imeshcvt 0.4");
    }
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
            if(oCreateTangents)
            {
                mesh = m_meshManipulator->createMeshWithTangents(mesh);
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
    delete er;
    return 0;
}

