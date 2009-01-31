#ifndef __IRR_IRRB_MESH_WRITER_H_INCLUDED__
#define __IRR_IRRB_MESH_WRITER_H_INCLUDED__

#include "IMeshWriter.h"
#include "S3DVertex.h"
#include "IVideoDriver.h"
#include "IFileSystem.h"

namespace irr
{
    namespace io
    {
        class IXMLWriter;
    }
    namespace scene
    {

        /* v 1.6
        [header]
        [animated mesh]
        [mesh]
        [mesh info]
        [verts]
        [indices]
        [buf1]
        [meshbuffer info]
        [material1]
        [material2]
        ...
        [bufx]
        ...
        [mesh]
        ...

        */

        class IMeshBuffer;

        // byte-align structures
        #if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined (__BCPLUSPLUS__) 
        #	pragma pack( push, packing )
        #	pragma pack( 1 )
        #	define PACK_STRUCT
        #elif defined( __GNUC__ )
        #	define PACK_STRUCT	__attribute__((packed))
        #else
        #	define PACK_STRUCT
        #endif

        #define IRRB_VERSION    0x0106  // coincides with Irrlicht version: IRRLICHT_SDK_VERSION

        #define INFO_ANIMATION_SKINNED  0x0001
        #define INFO_ANIMATION_VERTEX   0x0002

        #define CID_MESH     100
        #define CID_MATERIAL 110
        #define CID_MESHBUF  111
        #define CID_VBUFFER  112
        #define CID_IBUFFER  113
        #define CID_TEXTURE  114
        #define CID_SKEL     115
        #define CID_MORPH    116

        // irrb header
        struct IrrbHeader
        {
            u32     hSig;
            u8      hEOF;
            u8      hFill1;
            u16     hFill2;            
            u32     hVersion;
            c8      hCreator[32];
            u32     hInfoFlags;
            u32     hMeshCount;
            u32     hMeshBufferCount;
            u32     hCRC;
        } PACK_STRUCT;

        struct IrrbChunkInfo
        {
            u32     iId;
            u32     iSize;
        } PACK_STRUCT;

        struct Irrb3f
        {
            f32     x;
            f32     y;
            f32     z;
        } PACK_STRUCT;

        struct Irrb2f
        {
            f32     x;
            f32     y;
        } PACK_STRUCT;

        struct IrrbMeshInfo
        {
            u32     iMeshBufferCount;
            u32     iVertexCount;
            u32     iIndexCount;
            u32     iMaterialCount;
            Irrb3f  ibbMin;
            Irrb3f  ibbMax;
        } PACK_STRUCT;

        struct IrrbVertex
        {
            struct Irrb3f   vPos;
            struct Irrb3f   vNormal;
            u32             vColor;
            struct Irrb2f   vUV1;
            struct Irrb2f   vUV2;
            struct Irrb3f   vTangent;
            struct Irrb3f   vBiNormal;
        } PACK_STRUCT;

        struct IrrbMaterial
        {
            u32     mType;
            u32     mAmbient;
            u32     mDiffuse;
            u32     mEmissive;
            u32     mSpecular;
            f32     mShininess;
            f32     mParm1;
            f32     mParm2;
            c8      mTexture1[256];
            c8      mTexture2[256];
            c8      mTexture3[256];
            c8      mTexture4[256];
            bool    mWireframe;
            bool    mGrouraudShading;
            bool    mLighting;
            bool    mZWriteEnabled;
            u32     mZBuffer;
            bool    mBackfaceCulling;
            bool    mFogEnable;
            bool    mNormalizeNormals;
            bool    mBilinearFilter1;
            bool    mBilinearFilter2;
            bool    mBilinearFilter3;
            bool    mBilinearFilter4;
            bool    mTrilinearFilter1;
            bool    mTrilinearFilter2;
            bool    mTrilinearFilter3;
            bool    mTrilinearFilter4;
            u8      mAnisotropicFilter1;
            u8      mAnisotropicFilter2;
            u8      mAnisotropicFilter3;
            u8      mAnisotropicFilter4;
            u32     mTextureWrap1;
            u32     mTextureWrap2;
            u32     mTextureWrap3;
            u32     mTextureWrap4;
            f32     mMatrix1[16];
            f32     mMatrix2[16];
            f32     mMatrix3[16];
            f32     mMatrix4[16];
        } PACK_STRUCT;

        struct IrrbMeshBufInfo
        {
            u32     iVertexType;
            u32     iVertCount;
            u32     iVertStart;
            u32     iIndexCount;
            u32     iIndexStart;
            u32     iFaceCount;
            u32     iMaterialIndex;
            Irrb3f  ibbMin;
            Irrb3f  ibbMax;
        } PACK_STRUCT;



        // Default alignment
#if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined (__BCPLUSPLUS__) 
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT


        //! class to write meshes, implementing a IrrMesh (.irrmesh, .xml) writer
        /** This writer implementation has been originally developed for irrEdit and then
        merged out to the Irrlicht Engine */
        class CIrrBMeshWriter : public IMeshWriter
        {
        public:

            CIrrBMeshWriter(video::IVideoDriver* driver, io::IFileSystem* fs);
            virtual ~CIrrBMeshWriter();

            //! Returns the type of the mesh writer
            virtual EMESH_WRITER_TYPE getType() const;

            //! writes a mesh 
            virtual bool writeMesh(io::IWriteFile* file, scene::IMesh* mesh, s32 flags=EMWF_NONE);

        protected:

            void writeHeader(const scene::IMesh* mesh);

            void updateMaterial(const video::SMaterial& material,struct IrrbMaterial& mat);

            bool _writeMesh(const scene::IMesh* mesh);

            u32 _writeChunkInfo(u32 id, u32 size);
            void _updateChunkSize(u32 id, u32 offset);
            void updateBuffers(const scene::IMesh* mesh, struct IrrbVertex* vbuffer, u16* ibuffer);


            bool addMaterial(irr::video::SMaterial& material);
            u32 getMaterialIndex(irr::video::SMaterial& material);

            // member variables:
            irr::core::array<irr::video::SMaterial> Materials;
            struct IrrbVertex*   VBuffer;
            u16*    IBuffer;
            io::IFileSystem* FileSystem;
            video::IVideoDriver* VideoDriver;
            io::IWriteFile* Writer;
        };

    } // end namespace
} // end namespace

#endif

