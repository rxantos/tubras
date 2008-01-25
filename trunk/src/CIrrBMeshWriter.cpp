#include "tubras.h"
#include "CIrrBMeshWriter.h"
#include "os.h"
#include "IWriteFile.h"
#include "IXMLWriter.h"
#include "IMesh.h"
#include "IAttributes.h"

namespace irr
{
    namespace scene
    {

		//! to be included EMESH_WRITER_TYPE enum
		u32 EMWT_IRRB_MESH     = MAKE_IRR_ID('i','r','r','b');

        CIrrBMeshWriter::CIrrBMeshWriter(video::IVideoDriver* driver,
            io::IFileSystem* fs)
            : FileSystem(fs), VideoDriver(driver), Writer(0)
        {
            if (VideoDriver)
                VideoDriver->grab();

            if (FileSystem)
                FileSystem->grab();
        }


        CIrrBMeshWriter::~CIrrBMeshWriter()
        {
            if (VideoDriver)
                VideoDriver->drop();

            if (FileSystem)
                FileSystem->drop();
        }


        //! Returns the type of the mesh writer
        EMESH_WRITER_TYPE CIrrBMeshWriter::getType() const
        {
            return (irr::scene::EMESH_WRITER_TYPE)EMWT_IRRB_MESH;
        }


        //! writes a mesh
        bool CIrrBMeshWriter::writeMesh(io::IWriteFile* file, scene::IMesh* mesh, s32 flags)
        {
            bool rc = false;

            if (!file)
                return false;

            Writer = file;

            if (!Writer)
            {
                //os::Printer::log("Could not write file", file->getFileName());
                return false;
            }


            //os::Printer::log("Writing mesh", file->getFileName());

            // write IRRB MESH header

            writeHeader(mesh);

            // write mesh
            // todo: check the mesh type, cast it, 
            // and add appropriate animation extensions...

            rc = _writeMesh(mesh);


            Writer->drop();
            return rc;
        }

        u32 CIrrBMeshWriter::_writeChunkInfo(u32 id, u32 size)
        {
            u32 offset;
            struct IrrbChunkInfo ci;

            offset = Writer->getPos();

            ci.iId = id;
            ci.iSize = size;
            Writer->write(&ci,sizeof(ci));

            return offset;
        }

        void CIrrBMeshWriter::_updateChunkSize(u32 id, u32 offset)
        {
            struct IrrbChunkInfo ci;
            u32 cpos=Writer->getPos();

            ci.iId = id;
            ci.iSize = cpos - offset + sizeof(ci);
            Writer->seek(offset);
            Writer->write(&ci,sizeof(ci));
            Writer->seek(cpos);
        }

        bool CIrrBMeshWriter::addMaterial(SMaterial& material)
        {
            SMaterial amat;

            for(u32 i=0; i<Materials.size(); i++)
            {
                if(material == Materials[i])
                    return false;
            }
            Materials.push_back(material);
            return true;
        }

        u32 CIrrBMeshWriter::getMaterialIndex(SMaterial& material)
        {
            SMaterial amat;

            for(u32 i=0; i<Materials.size(); i++)
            {
                if(material == Materials[i])
                    return i;
            }
            return 0;
        }

        bool CIrrBMeshWriter::_writeMesh(const scene::IMesh* mesh)
        {
            bool rc = false;
            u32  offset;
            struct IrrbMeshInfo mi;
            u32  vcount=0;
            u32  icount=0;
            u32  mcount=0;
            u32* voffsets;
            u32* ioffsets;
            u32  bcount=0;


            offset = _writeChunkInfo(CID_MESH,0);

            bcount = mesh->getMeshBufferCount();

            voffsets = (u32*) malloc(bcount * sizeof(u32));
            ioffsets = (u32*) malloc(bcount * sizeof(u32));

            //
            // count vertices, indices, & materials across all mesh buffers
            //
            for (int i=0; i<(int)mesh->getMeshBufferCount(); ++i)
            {
                scene::IMeshBuffer* buffer = mesh->getMeshBuffer(i);
                voffsets[i] = vcount;
                ioffsets[i] = icount;
                vcount += buffer->getVertexCount();
                icount += buffer->getIndexCount();

                SMaterial& material = buffer->getMaterial();
                if(addMaterial(material))
                    ++mcount;
            }

            //
            // write mesh info struct
            //
            mi.iMeshBufferCount = mesh->getMeshBufferCount();
            mi.iVertexCount = vcount;
            mi.iIndexCount = icount;
            mi.iMaterialCount = mcount;
            Writer->write(&mi,sizeof(mi));

            //
            // build and write vertex & index buffers
            // 
            u32 vbufsize,ibufsize;
            vbufsize = sizeof(struct IrrbVertex) * vcount;
            ibufsize = sizeof(u16) * icount;

            VBuffer = (struct IrrbVertex*)malloc(vbufsize);
            IBuffer = (u16 *)malloc(ibufsize);

            updateBuffers(mesh, VBuffer, IBuffer);
            Writer->write(VBuffer,vbufsize);
            Writer->write(IBuffer,ibufsize);

            //
            // write materials
            //
            for(u32 i=0; i<Materials.size(); i++)
            {
                struct IrrbMaterial iMat;
                updateMaterial(Materials[i],iMat);
                Writer->write(&iMat,sizeof(iMat));
            }

            //
            // write mesh buffers info
            //
            u32 mbOffset = _writeChunkInfo(CID_MESHBUF,0);
            for (int i=0; i<(int)mesh->getMeshBufferCount(); ++i)
            {
                scene::IMeshBuffer* buffer = mesh->getMeshBuffer(i);
                if (buffer)
                {

                    struct IrrbMeshBufInfo mbi;

                    // write meshbuffer info

                    mbi.iVertexType = buffer->getVertexType();
                    mbi.iVertCount = buffer->getVertexCount();
                    mbi.iVertStart = voffsets[i];
                    mbi.iIndexCount = buffer->getIndexCount();
                    mbi.iIndexStart = ioffsets[i];
                    mbi.iFaceCount = buffer->getIndexCount() / 3;
                    mbi.iMaterialIndex = getMaterialIndex(buffer->getMaterial());

                    Writer->write(&mbi,sizeof(mbi));
                }
            }
            _updateChunkSize(CID_MESHBUF,offset);

            _updateChunkSize(CID_MESH,offset);

            free(voffsets);
            free(VBuffer);
            free(ioffsets);
            free(IBuffer);

            return rc;
        }


        void CIrrBMeshWriter::writeHeader(const scene::IMesh* mesh)
        {
            struct IrrbHeader h;
            memset(&h,0,sizeof(h));
            h.hSig = MAKE_IRR_ID('i','r','r','b');
            h.hEOF = 0x1a;
            h.hVersion = IRRB_VERSION;
            strcpy(h.hCreator,"iconvert");
            h.hMeshCount = 1;
            h.hMeshBufferCount = mesh->getMeshBufferCount();
            Writer->write(&h,sizeof(h));            
        }

        void CIrrBMeshWriter::updateBuffers(const scene::IMesh* mesh,
            struct IrrbVertex* VBuffer,u16* IBuffer)
        {
            u32 vidx=0,iidx=0;

            for (int i=0; i<(int)mesh->getMeshBufferCount(); ++i)
            {
                scene::IMeshBuffer* buffer = mesh->getMeshBuffer(i);
                if (buffer)
                {
                    u32 vertexCount = buffer->getVertexCount();

                    switch(buffer->getVertexType())
                    {
                    case video::EVT_STANDARD:
                        {
                            video::S3DVertex* vtx = (video::S3DVertex*)buffer->getVertices();
                            for (u32 j=0; j<vertexCount; ++j)
                            {
                                VBuffer[vidx].vPos.x = vtx[j].Pos.X;
                                VBuffer[vidx].vPos.y = vtx[j].Pos.Y;
                                VBuffer[vidx].vPos.z = vtx[j].Pos.Z;

                                VBuffer[vidx].vNormal.x = vtx[j].Normal.X;
                                VBuffer[vidx].vNormal.y = vtx[j].Normal.Y;
                                VBuffer[vidx].vNormal.z = vtx[j].Normal.Z;

                                VBuffer[vidx].vColor = vtx[j].Color.color;

                                VBuffer[vidx].vUV1.x = vtx[j].TCoords.X;
                                VBuffer[vidx].vUV1.y = vtx[j].TCoords.Y;
                                ++vidx;
                            }
                        }
                        break;
                    case video::EVT_2TCOORDS:
                        {
                            video::S3DVertex2TCoords* vtx = (video::S3DVertex2TCoords*)buffer->getVertices();
                            for (u32 j=0; j<vertexCount; ++j)
                            {
                                VBuffer[vidx].vPos.x = vtx[j].Pos.X;
                                VBuffer[vidx].vPos.y = vtx[j].Pos.Y;
                                VBuffer[vidx].vPos.z = vtx[j].Pos.Z;

                                VBuffer[vidx].vNormal.x = vtx[j].Normal.X;
                                VBuffer[vidx].vNormal.y = vtx[j].Normal.Y;
                                VBuffer[vidx].vNormal.z = vtx[j].Normal.Z;

                                VBuffer[vidx].vColor = vtx[j].Color.color;

                                VBuffer[vidx].vUV1.x = vtx[j].TCoords.X;
                                VBuffer[vidx].vUV1.y = vtx[j].TCoords.Y;
                                VBuffer[vidx].vUV2.x = vtx[j].TCoords2.X;
                                VBuffer[vidx].vUV2.y = vtx[j].TCoords2.Y;
                                ++vidx;

                            }
                        }
                        break;
                    case video::EVT_TANGENTS:
                        {
                            video::S3DVertexTangents* vtx = (video::S3DVertexTangents*)buffer->getVertices();
                            for (u32 j=0; j<vertexCount; ++j)
                            {
                                VBuffer[vidx].vPos.x = vtx[j].Pos.X;
                                VBuffer[vidx].vPos.y = vtx[j].Pos.Y;
                                VBuffer[vidx].vPos.z = vtx[j].Pos.Z;

                                VBuffer[vidx].vNormal.x = vtx[j].Normal.X;
                                VBuffer[vidx].vNormal.y = vtx[j].Normal.Y;
                                VBuffer[vidx].vNormal.z = vtx[j].Normal.Z;

                                VBuffer[vidx].vColor = vtx[j].Color.color;

                                VBuffer[vidx].vUV1.x = vtx[j].TCoords.X;
                                VBuffer[vidx].vUV1.y = vtx[j].TCoords.Y;

                                VBuffer[vidx].vTangent.x = vtx[j].Tangent.X;
                                VBuffer[vidx].vTangent.y = vtx[j].Tangent.Y;
                                VBuffer[vidx].vTangent.z = vtx[j].Tangent.Z;

                                VBuffer[vidx].vBiNormal.x = vtx[j].Binormal.X;
                                VBuffer[vidx].vBiNormal.y = vtx[j].Binormal.Y;
                                VBuffer[vidx].vBiNormal.z = vtx[j].Binormal.Z;
                                ++vidx;

                            }
                        }
                        break;
                    }


                    // update indices

                    u32 indexCount = buffer->getIndexCount();
                    const u16* idx = buffer->getIndices();
                    for(u32 j=0; j<indexCount; j++)
                    {
                        IBuffer[iidx++] = idx[j];
                    }
                }
            }
        }


        void CIrrBMeshWriter::updateMaterial(const video::SMaterial& material, struct IrrbMaterial& mat)
        {

            u32 tCount=0;

            for(tCount=0;tCount < 4; tCount++)
                if(!material.getTexture(tCount))
                    break;


            memset(&mat,0,sizeof(mat));

            mat.mType = material.MaterialType;
            mat.mAmbient = material.AmbientColor.color;
            mat.mDiffuse = material.DiffuseColor.color;
            mat.mEmissive = material.EmissiveColor.color;
            mat.mSpecular = material.SpecularColor.color;
            mat.mShininess = material.Shininess;
            mat.mParm1 = material.MaterialTypeParam;
            mat.mParm2 = material.MaterialTypeParam2;
            mat.mWireframe = material.Wireframe;
            mat.mGrouraudShading = material.GouraudShading;
            mat.mLighting = material.Lighting;
            mat.mZWriteEnabled = material.ZWriteEnable;
            mat.mZBuffer = material.ZBuffer;
            mat.mBackfaceCulling = material.BackfaceCulling;
            mat.mFogEnable = material.FogEnable;
            mat.mNormalizeNormals = material.NormalizeNormals;
            if(tCount > 0)
            {
                strcpy(mat.mTexture1,material.TextureLayer[0].Texture->getName().c_str());
                mat.mBilinearFilter1 = material.TextureLayer[0].BilinearFilter;
                mat.mTrilinearFilter1 = material.TextureLayer[0].TrilinearFilter;
                mat.mAnisotropicFilter1 = material.TextureLayer[0].AnisotropicFilter;
                mat.mTextureWrap1 = material.TextureLayer[0].TextureWrap;
                memcpy(&mat.mMatrix1,material.TextureLayer[0].getTextureMatrix().pointer(),sizeof(f32)*16);
            }
            if(tCount > 1)
            {
                strcpy(mat.mTexture2,material.TextureLayer[1].Texture->getName().c_str());
                mat.mBilinearFilter2 = material.TextureLayer[1].BilinearFilter;
                mat.mTrilinearFilter2 = material.TextureLayer[1].TrilinearFilter;
                mat.mAnisotropicFilter2 = material.TextureLayer[1].AnisotropicFilter;
                mat.mTextureWrap2 = material.TextureLayer[1].TextureWrap;
                memcpy(&mat.mMatrix2,material.TextureLayer[1].getTextureMatrix().pointer(),sizeof(f32)*16);
            }
            if(tCount > 2)
            {
                strcpy(mat.mTexture3,material.TextureLayer[2].Texture->getName().c_str());
                mat.mBilinearFilter3 = material.TextureLayer[2].BilinearFilter;
                mat.mTrilinearFilter3 = material.TextureLayer[2].TrilinearFilter;
                mat.mAnisotropicFilter3 = material.TextureLayer[2].AnisotropicFilter;
                mat.mTextureWrap3 = material.TextureLayer[2].TextureWrap;
                memcpy(&mat.mMatrix3,material.TextureLayer[2].getTextureMatrix().pointer(),sizeof(f32)*16);
            }
            if(tCount > 3)
            {
                strcpy(mat.mTexture4,material.TextureLayer[3].Texture->getName().c_str());
                mat.mBilinearFilter4 = material.TextureLayer[3].BilinearFilter;
                mat.mTrilinearFilter4 = material.TextureLayer[3].TrilinearFilter;
                mat.mAnisotropicFilter4 = material.TextureLayer[3].AnisotropicFilter;
                mat.mTextureWrap4 = material.TextureLayer[3].TextureWrap;
                memcpy(&mat.mMatrix4,material.TextureLayer[3].getTextureMatrix().pointer(),sizeof(f32)*16);
            }

        }


    } // end namespace
} // end namespace

