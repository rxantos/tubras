#include "tubras.h"
// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "IrrCompileConfig.h"
#ifdef _IRR_COMPILE_WITH_IRRB_MESH_LOADER_

#include "CIrrBMeshFileLoader.h"
#include "os.h"
#include "IXMLReader.h"
#include "SAnimatedMesh.h"
#include "fast_atof.h"
#include "IReadFile.h"
#include "IAttributes.h"
#include "IMeshSceneNode.h"
#include "SMeshBufferLightMap.h"

namespace irr
{
namespace scene
{


//! Constructor
CIrrBMeshFileLoader::CIrrBMeshFileLoader(video::IVideoDriver* driver,
		scene::ISceneManager* smgr, io::IFileSystem* fs)
	: Driver(driver), SceneManager(smgr), FileSystem(fs)
{
}


//! destructor
CIrrBMeshFileLoader::~CIrrBMeshFileLoader()
{
}


//! Returns true if the file maybe is able to be loaded by this class.
/** This decision should be based only on the file extension (e.g. ".cob") */
bool CIrrBMeshFileLoader::isALoadableFileExtension(const c8* fileName) const
{
	return strstr(fileName, ".irrbmesh") != 0;
}


//! creates/loads an animated mesh from the file.
//! \return Pointer to the created mesh. Returns 0 if loading failed.
//! If you no longer need the mesh, you should call IAnimatedMesh::drop().
//! See IReferenceCounted::drop() for more information.
IAnimatedMesh* CIrrBMeshFileLoader::createMesh(io::IReadFile* file)
{
	IAnimatedMesh* mesh = readMesh(file);

	return mesh;
}


//! reads a mesh sections and creates a mesh from it
IAnimatedMesh* CIrrBMeshFileLoader::readMesh(io::IReadFile* reader)
{
    struct IrrbHeader ih;
    u32    sigCheck = MAKE_IRR_ID('i','r','r','b');

    Reader = reader;

    Reader->seek(0);
    if(Reader->read(&ih,sizeof(ih)) != sizeof(ih))
        return 0;

    // sanity checks

    if(ih.hSig != sigCheck)
        return 0;

    if(ih.hMeshCount < 1)
        return 0;

	SAnimatedMesh* animatedmesh = new SAnimatedMesh();

    for(u32 i=0; i<ih.hMeshCount; i++)
    {
        SMesh* mesh = _readMesh(i);
        if(mesh)
        {
            animatedmesh->addMesh(mesh);
            mesh->drop();
        }
    }


    animatedmesh->recalculateBoundingBox();

    return animatedmesh;
}

u32 CIrrBMeshFileLoader::readChunk(struct IrrbChunkInfo& chunk)
{
    return Reader->read(&chunk, sizeof(chunk));
}


SMesh* CIrrBMeshFileLoader::_readMesh(u32 index)
{

    u32 idx=0;
    struct IrrbChunkInfo ci;
    struct IrrbMeshInfo  mi;


    // position to the correct mesh
    Reader->seek(sizeof(struct IrrbHeader));
    readChunk(ci);

    while(idx < index)
    {
        u32 cpos = Reader->getPos();
        Reader->seek(cpos+ci.iSize);
        readChunk(ci);
        ++idx;
    }

    if(ci.iId != CID_MESH)
        return 0;

    Reader->read(&mi, sizeof(mi));
    if(mi.iMeshBufferCount == 0)
        return 0;

	SMesh* mesh = new SMesh();


    for(idx=0; idx<mi.iMeshBufferCount; idx++)
    {
        IMeshBuffer* buffer = readMeshBuffer();
        if(buffer)
        {
            mesh->addMeshBuffer(buffer);
            buffer->drop();
        }
    }

    //
    // todo add bounding box to irrbmesh format...
    // 
    mesh->recalculateBoundingBox();

	return mesh;
}

void CIrrBMeshFileLoader::setMaterial(video::SMaterial& material, struct IrrbMaterial& mat)
{

    
    material.MaterialType = (E_MATERIAL_TYPE)mat.mType;
    material.AmbientColor.color = mat.mAmbient;
    material.DiffuseColor.color= mat.mDiffuse;
    material.EmissiveColor.color = mat.mEmissive;
    material.SpecularColor.color = mat.mSpecular;
    material.Shininess = mat.mShininess;
    material.MaterialTypeParam = mat.mParm1;
    material.MaterialTypeParam2 = mat.mParm2;
    material.Wireframe = mat.mWireframe;
    material.GouraudShading = mat.mGrouraudShading;
    material.Lighting = mat.mLighting;
    material.ZWriteEnable = mat.mZWriteEnabled;
    material.ZBuffer = mat.mZBuffer;
    material.BackfaceCulling = mat.mBackfaceCulling;
    material.FogEnable = mat.mFogEnable;
    material.NormalizeNormals = mat.mNormalizeNormals;

    if(*mat.mTexture1)
    {
        IImage* img = Driver->createImageFromFile(mat.mTexture1);
        if(img)
        {
            ITexture* tex = Driver->addTexture(mat.mTexture1,img);
            material.TextureLayer[0].BilinearFilter = mat.mBilinearFilter1;
            material.TextureLayer[0].TrilinearFilter = mat.mTrilinearFilter1;
            material.TextureLayer[0].AnisotropicFilter = mat.mAnisotropicFilter1;
            material.TextureLayer[0].TextureWrap = (irr::video::E_TEXTURE_CLAMP)mat.mTextureWrap1;
            irr::core::matrix4 mat4;
            memcpy(mat4.pointer(),&mat.mMatrix1,sizeof(u16)*16);
            material.TextureLayer[0].setTextureMatrix(mat4);
        }
    }

    if(*mat.mTexture2)
    {
        IImage* img = Driver->createImageFromFile(mat.mTexture2);
        if(img)
        {
            ITexture* tex = Driver->addTexture(mat.mTexture2,img);
            material.TextureLayer[1].BilinearFilter = mat.mBilinearFilter2;
            material.TextureLayer[1].TrilinearFilter = mat.mTrilinearFilter2;
            material.TextureLayer[1].AnisotropicFilter = mat.mAnisotropicFilter2;
            material.TextureLayer[1].TextureWrap = (irr::video::E_TEXTURE_CLAMP)mat.mTextureWrap2;
            irr::core::matrix4 mat4;
            memcpy(mat4.pointer(),&mat.mMatrix2,sizeof(u16)*16);
            material.TextureLayer[1].setTextureMatrix(mat4);
        }
    }

    if(*mat.mTexture3)
    {
        IImage* img = Driver->createImageFromFile(mat.mTexture3);
        if(img)
        {
            ITexture* tex = Driver->addTexture(mat.mTexture3,img);
            material.TextureLayer[2].BilinearFilter = mat.mBilinearFilter3;
            material.TextureLayer[2].TrilinearFilter = mat.mTrilinearFilter3;
            material.TextureLayer[2].AnisotropicFilter = mat.mAnisotropicFilter3;
            material.TextureLayer[2].TextureWrap = (irr::video::E_TEXTURE_CLAMP)mat.mTextureWrap3;
            irr::core::matrix4 mat4;
            memcpy(mat4.pointer(),&mat.mMatrix3,sizeof(u16)*16);
            material.TextureLayer[2].setTextureMatrix(mat4);
        }
    }

    if(*mat.mTexture4)
    {
        IImage* img = Driver->createImageFromFile(mat.mTexture4);
        if(img)
        {
            ITexture* tex = Driver->addTexture(mat.mTexture4,img);
            material.TextureLayer[3].BilinearFilter = mat.mBilinearFilter4;
            material.TextureLayer[3].TrilinearFilter = mat.mTrilinearFilter4;
            material.TextureLayer[3].AnisotropicFilter = mat.mAnisotropicFilter4;
            material.TextureLayer[3].TextureWrap = (irr::video::E_TEXTURE_CLAMP)mat.mTextureWrap4;
            irr::core::matrix4 mat4;
            memcpy(mat4.pointer(),&mat.mMatrix4,sizeof(u16)*16);
            material.TextureLayer[3].setTextureMatrix(mat4);
        }
    }

}


IMeshBuffer* CIrrBMeshFileLoader::readMeshBuffer()
{
    IMeshBuffer* buffer = 0;
	SMeshBuffer* sbuffer1 = 0;
	SMeshBufferLightMap* sbuffer2 = 0;
	SMeshBufferTangents* sbuffer3 = 0;
    struct IrrbMeshBufInfo mbi;
	video::SMaterial material;
    struct IrrbMaterialInfo matinfo;
    struct IrrbMaterial mat;
    struct IrrbVertex*   ivb;
    u32 ivbSize,iSize, idx;
    u16*    indices;

    struct IrrbChunkInfo ci;

    // read chunk info
    readChunk(ci);
    if(ci.iId != CID_MESHBUF)
        return 0;
    
    // read meshbuffer info
    Reader->read(&mbi, sizeof(mbi));

    // read material info, only one type for now so ignore...
    Reader->read(&matinfo,sizeof(matinfo));

    // read material data
    Reader->read(&mat, sizeof(mat));
    setMaterial(material, mat);

    ivbSize = mbi.iVertCount * sizeof(struct IrrbVertex);
    ivb = (struct IrrbVertex*) malloc(ivbSize);
    iSize = mbi.iIndexCount * sizeof(u16);
    indices = (u16*) malloc(iSize);

    // read vertex & index data
    Reader->read(ivb, ivbSize);
    Reader->read(indices, iSize);


    // fvf? please!!!
    if(mbi.iVertexType == EVT_2TCOORDS)
    {
        sbuffer2 = new SMeshBufferLightMap();
        buffer = sbuffer2;
    }
    else if(mbi.iVertexType == EVT_TANGENTS)
    {
        sbuffer3 = new SMeshBufferTangents();
        buffer = sbuffer3;
    }
    else // EVT_STANDARD
    {
        sbuffer1 = new SMeshBuffer();
        buffer = sbuffer1;
    }

    for(idx=0; idx<mbi.iVertCount; idx++)
    {

        video::S3DVertex vtx0;
		video::S3DVertex2TCoords vtx1;
		video::S3DVertexTangents vtx2;

        video::S3DVertex* vtx=0;


        if(mbi.iVertexType == EVT_2TCOORDS)
            vtx = &vtx1;
        else if(mbi.iVertexType == EVT_TANGENTS)
            vtx = &vtx2;
        else vtx = &vtx0;

        // set common data
        vtx->Pos.X = ivb[idx].vPos.x;
        vtx->Pos.Y = ivb[idx].vPos.y;
        vtx->Pos.Z = ivb[idx].vPos.z;

        vtx->Normal.X = ivb[idx].vNormal.x;
        vtx->Normal.Y = ivb[idx].vNormal.y;
        vtx->Normal.Z = ivb[idx].vNormal.z;

        vtx->Color = ivb[idx].vColor;

        vtx->TCoords.X = ivb[idx].vUV1.x;
        vtx->TCoords.Y = ivb[idx].vUV1.y;

        if(mbi.iVertexType == EVT_2TCOORDS)
        {
            vtx1.TCoords2.X = ivb[idx].vUV2.x;
            vtx1.TCoords2.Y = ivb[idx].vUV2.y;
            sbuffer2->Vertices.push_back(vtx1);
        }
        else if(mbi.iVertexType == EVT_TANGENTS)
        {
            vtx2.Tangent.X = ivb[idx].vTangent.x;
            vtx2.Tangent.Y = ivb[idx].vTangent.y;
            vtx2.Tangent.Z = ivb[idx].vTangent.z;

            vtx2.Binormal.X = ivb[idx].vBiNormal.x;
            vtx2.Binormal.Y = ivb[idx].vBiNormal.y;
            vtx2.Binormal.Z = ivb[idx].vBiNormal.z;
            sbuffer3->Vertices.push_back(vtx2);
        }
        else
        {
            sbuffer1->Vertices.push_back(vtx0);

        }
    }

    for(idx=0; idx<mbi.iIndexCount; idx++)
    {
        if(mbi.iVertexType == EVT_2TCOORDS)
            sbuffer2->Indices.push_back(indices[idx]);
        else if(mbi.iVertexType == EVT_TANGENTS)
            sbuffer3->Indices.push_back(indices[idx]);
        else
            sbuffer1->Indices.push_back(indices[idx]);
    }


    free(indices);
    free(ivb);
    return buffer;
}

} // end namespace scene
} // end namespace irr

#endif // _IRR_COMPILE_WITH_IRRB_MESH_LOADER_
