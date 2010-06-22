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

        int get_endianess(void)  // 1-big, 0-lil
        {
            union {
                int i;
                char c[sizeof(int)];
            } t;
            t.i = 1;
            return t.c[0] == 0;
        }

        CIrrBMeshWriter::CIrrBMeshWriter(video::IVideoDriver* driver,
            io::IFileSystem* fs)
            : FileSystem(fs), VideoDriver(driver), Writer(0), Version(IRRB_VERSION), 
            VMajor(IRRLICHT_VERSION_MAJOR), VMinor(IRRLICHT_VERSION_MINOR), Creator("unknown")
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

        void CIrrBMeshWriter::_writeStringChunk(irr::core::stringc value)
        {
            struct IrrbChunkInfo ci;
            ci.iId = CID_STRING;
            ci.iSize = value.size() + 1;
            Writer->write(&ci,sizeof(ci));
            Writer->write(value.c_str(),ci.iSize);
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

        bool CIrrBMeshWriter::addMaterial(irr::video::SMaterial& material)
        {
            irr::video::SMaterial amat;

            for(u32 i=0; i<Materials.size(); i++)
            {
                if(material == Materials[i])
                    return false;
            }
            Materials.push_back(material);
            return true;
        }

        u32 CIrrBMeshWriter::getMaterialIndex(irr::video::SMaterial& material)
        {
            irr::video::SMaterial amat;

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
            core::aabbox3d<f32> mbb;
            mbb.reset(0.f,0.f,0.f);
            for (int i=0; i<(int)mesh->getMeshBufferCount(); ++i)
            {
                scene::IMeshBuffer* buffer = mesh->getMeshBuffer(i);
                buffer->recalculateBoundingBox();
                mbb.addInternalBox(buffer->getBoundingBox());
                voffsets[i] = vcount;
                ioffsets[i] = icount;
                vcount += buffer->getVertexCount();
                icount += buffer->getIndexCount();

                irr::video::SMaterial& material = buffer->getMaterial();
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
            mi.ibbMin.x = mbb.MinEdge.X;
            mi.ibbMin.y = mbb.MinEdge.Y;
            mi.ibbMin.z = mbb.MinEdge.Z;
            mi.ibbMax.x = mbb.MaxEdge.X;
            mi.ibbMax.y = mbb.MaxEdge.Y;
            mi.ibbMax.z = mbb.MaxEdge.Z;

            Writer->write(&mi,sizeof(mi));

            //
            // build and write vertex & index buffers
            // 
            u32 vbufsize,ibufsize;
            vbufsize = sizeof(struct IrrbVertex) * vcount;
            ibufsize = sizeof(u32) * icount;

            VBuffer = (struct IrrbVertex*)malloc(vbufsize);
            IBuffer = (u32 *)malloc(ibufsize);

            updateBuffers(mesh, VBuffer, IBuffer);
            Writer->write(VBuffer,vbufsize);
            Writer->write(IBuffer,ibufsize);

            //
            // write materials
            //
            for(u32 i=0; i<Materials.size(); i++)
            {
                struct IrrbMaterial_1_6 iMat;

                struct IrrbMaterialLayer_1_6 iLayer_1_6;
                struct IrrbMaterialLayer_1_7 iLayer_1_7;

                updateMaterial(Materials[i],iMat);
                u32 tCount=0;

                for(tCount=0;tCount < 4; tCount++)
                {
                    irr::video::ITexture* texture = Materials[i].getTexture(tCount);
                    if(!texture)
                        break;
                }
                iMat.mLayerCount = tCount;
                Writer->write(&iMat,sizeof(iMat));

                for(u8 t=0; t<tCount; t++)
                {
                    irr::core::stringc textureName;
                    if(VMajor == 1)
                    {
                        if(VMinor <= 6)
                        {
                            updateMaterialLayer(Materials[i],t,textureName,iLayer_1_6);
                            _writeStringChunk(textureName);
                            Writer->write(&iLayer_1_6,sizeof(iLayer_1_6));
                        }
                        else
                        {
                            updateMaterialLayer(Materials[i],t,textureName,iLayer_1_7);
                            _writeStringChunk(textureName);
                            Writer->write(&iLayer_1_7,sizeof(iLayer_1_7));
                        }
                    }
                }
            }

            //
            // write mesh buffers info
            //
            _writeChunkInfo(CID_MESHBUF,0);
            for (int i=0; i<(int)mesh->getMeshBufferCount(); ++i)
            {
                scene::IMeshBuffer* buffer = mesh->getMeshBuffer(i);
                if (buffer)
                {

                    struct IrrbMeshBufInfo_1_6 mbi;

                    // write meshbuffer info

                    mbi.iVertexType = buffer->getVertexType();
                    mbi.iVertCount = buffer->getVertexCount();
                    mbi.iVertStart = voffsets[i];
                    mbi.iIndexCount = buffer->getIndexCount();
                    mbi.iIndexStart = ioffsets[i];
                    mbi.iFaceCount = buffer->getIndexCount() / 3;
                    mbi.iMaterialIndex = getMaterialIndex(buffer->getMaterial());
                    buffer->recalculateBoundingBox();
                    mbb = buffer->getBoundingBox();
                    mbi.ibbMin.x = mbb.MinEdge.X;
                    mbi.ibbMin.y = mbb.MinEdge.Y;
                    mbi.ibbMin.z = mbb.MinEdge.Z;
                    mbi.ibbMax.x = mbb.MaxEdge.X;
                    mbi.ibbMax.y = mbb.MaxEdge.Y;
                    mbi.ibbMax.z = mbb.MaxEdge.Z;

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

            // include version is visible portion
            sprintf(h.hSig,"irrb %d.%d",Version >> 8,Version & 0xFF);
            *(h.hSig+strlen(h.hSig)) = 0x1a;

            h.hSigCheck = MAKE_IRR_ID('i','r','r','b');
            h.hVersion = Version;
            h.hFlags = (get_endianess() << 16) | (sizeof(int) * 8);
            strcpy(h.hCreator,Creator.c_str());
            h.hMeshCount = 1;  // 1 mesh for now, todo: add ability to include lod mesh data...
            h.hMeshBufferCount = mesh->getMeshBufferCount();
            Writer->write(&h,sizeof(h));            
        }

        void CIrrBMeshWriter::updateBuffers(const scene::IMesh* mesh,
            struct IrrbVertex* VBuffer,u32* IBuffer)
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
                    const u16* idx16 = buffer->getIndices();
                    const u32* idx32 = (u32 *)buffer->getIndices();

                    video::E_INDEX_TYPE iType = buffer->getIndexType();

                    for(u32 j=0; j<indexCount; j++)
                    {
                        if(iType == video::EIT_16BIT)
                            IBuffer[iidx++] = idx16[j];
                        else
                            IBuffer[iidx++] = idx32[j];
                    }
                }
            }
        }

        void CIrrBMeshWriter::updateMaterialLayer(const video::SMaterial& material,u8 layerNumber, irr::core::stringc& textureName, struct IrrbMaterialLayer_1_6& layer)
        {
            if(layerNumber > 3)
                return;

            memset(&layer,0,sizeof(layer));

            textureName = material.TextureLayer[layerNumber].Texture->getName().getPath().c_str();
            layer.mBilinearFilter = material.TextureLayer[layerNumber].BilinearFilter;
            layer.mTrilinearFilter = material.TextureLayer[layerNumber].TrilinearFilter;
            layer.mAnisotropicFilter = material.TextureLayer[layerNumber].AnisotropicFilter;
#if IRRLICHT_VERSION_MAJOR == 1 && IRRLICHT_VERSION_MINOR <= 6
            layer.mTextureWrap = material.TextureLayer[layerNumber].TextureWrap;
#elif IRRLICHT_VERSION_MAJOR == 1 && IRRLICHT_VERSION_MINOR == 7
            layer.mTextureWrap = material.TextureLayer[layerNumber].TextureWrapU;
#endif
            memcpy(&layer.mMatrix,material.TextureLayer[layerNumber].getTextureMatrix().pointer(),sizeof(f32)*16);
        }

        void CIrrBMeshWriter::updateMaterialLayer(const video::SMaterial& material,u8 layerNumber, irr::core::stringc& textureName, struct IrrbMaterialLayer_1_7& layer)
        {
            if(layerNumber > 3)
                return;

            memset(&layer,0,sizeof(layer));

            textureName = material.TextureLayer[layerNumber].Texture->getName().getPath().c_str();
            layer.mBilinearFilter = material.TextureLayer[layerNumber].BilinearFilter;
            layer.mTrilinearFilter = material.TextureLayer[layerNumber].TrilinearFilter;
            layer.mAnisotropicFilter = material.TextureLayer[layerNumber].AnisotropicFilter;
#if IRRLICHT_VERSION_MAJOR == 1 && IRRLICHT_VERSION_MINOR <= 6
            layer.mTextureWrapU = material.TextureLayer[layerNumber].TextureWrap;
            layer.mTextureWrapV = layer.mTextureWrapU;
#elif IRRLICHT_VERSION_MAJOR == 1 && IRRLICHT_VERSION_MINOR == 7
            layer.mTextureWrapU = material.TextureLayer[layerNumber].TextureWrapU;
            layer.mTextureWrapV = material.TextureLayer[layerNumber].TextureWrapV;
#endif
            memcpy(&layer.mMatrix,material.TextureLayer[layerNumber].getTextureMatrix().pointer(),sizeof(f32)*16);
        }

        void CIrrBMeshWriter::updateMaterial(const video::SMaterial& material, struct IrrbMaterial_1_6& mat)
        {

            memset(&mat,0,sizeof(mat));

            mat.mType = material.MaterialType;
            mat.mAmbient = material.AmbientColor.color;
            mat.mDiffuse = material.DiffuseColor.color;
            mat.mEmissive = material.EmissiveColor.color;
            mat.mSpecular = material.SpecularColor.color;
            mat.mShininess = material.Shininess;
            mat.mParm1 = material.MaterialTypeParam;
            mat.mParm2 = material.MaterialTypeParam2;
            mat.mThickness = material.Thickness;
            mat.mZBuffer = material.ZBuffer;
            mat.mAntiAliasing = material.AntiAliasing;
            mat.mColorMask = material.ColorMask;

            mat.mWireframe = material.Wireframe;
            mat.mPointCloud = material.PointCloud;
            mat.mGrouraudShading = material.GouraudShading;
            mat.mLighting = material.Lighting;
            mat.mZWriteEnabled = material.ZWriteEnable;
            mat.mBackfaceCulling = material.BackfaceCulling;
            mat.mFrontfaceCulling = material.FrontfaceCulling;
            mat.mFogEnable = material.FogEnable;
            mat.mNormalizeNormals = material.NormalizeNormals;
        }
    } // end namespace
} // end namespace