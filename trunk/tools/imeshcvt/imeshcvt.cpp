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

//-----------------------------------------------------------------------------
//                             E v e n t R e c e i v er
//-----------------------------------------------------------------------------
// used to suppress engine debug messages
class EventReceiver : public IEventReceiver
{
    bool suppressEvents;
	bool OnEvent(const SEvent& event)
    {
        return suppressEvents;
    }
public:
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
//                             s h o w M e s h I n f o
//-----------------------------------------------------------------------------
void showMeshInfo()
{
    // todo...
}

//-----------------------------------------------------------------------------
//                                   m a i n
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{

    printf("imeshcvt 0.1 Copyright(C) 2008 Tubras Software, Ltd\n\n");

    if(argc < 2)
    {
        printf("usage: imeshcvt [input file] <output file> <mesh index=0>\n\n");
        printf("    [input file] - input mesh file to convert or report on.\n");
        printf("                   if no output mesh is specified, info is \n");
        printf("                   displayed for the input mesh. Required.\n\n");
        printf("   <output file> - output mesh file to convert to.\n\n");
        printf("    <mesh index> - animated mesh index to convert.\n");
        return 1;
    }

    m_iMeshName = argv[1];

    if(argc >= 3)
        m_oMeshName = argv[2];

    if(argc == 4)
    {
        m_meshIndex = atoi(argv[3]);
    }

    printf(" Input Mesh: %s\n",m_iMeshName.c_str());
    printf("Output Mesh: %s\n",m_oMeshName.c_str());

    if(!fileExists(m_iMeshName))
    {
        printf("\nError: Input Mesh Doesn't Exist\n");
        return 1;
    }

    EventReceiver *er = new EventReceiver();
    m_device = createDevice( video::EDT_NULL, dimension2d<s32>(640, 480), 16,
        false, false, false, er);

    m_logger = m_device->getLogger();
    m_logger->setLogLevel(ELL_NONE);
    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();

    //
    // add location of input mesh path to the file system
    //
    m_fileSystem->addFolderFileArchive(getPath(m_iMeshName).c_str());

    m_sceneManager->addExternalMeshLoader(new CIrrBMeshFileLoader(m_videoDriver,m_sceneManager,m_fileSystem));

    m_inputMesh = m_sceneManager->getMesh(m_iMeshName.c_str());


    //
    // input mesh only?
    //

    if(argc < 3)
    {
        showMeshInfo();
        m_device->drop();
        return 0;
    }

    stringc ext = getExtension(m_oMeshName);

    IMeshWriter*    writer=0;

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
    return 0;
}

