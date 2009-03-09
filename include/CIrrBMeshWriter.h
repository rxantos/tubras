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
               [buffer count]
               [verts]        (all mesh buffers)
               [indices]      (all mesh buffers)
           [/mesh info]

           [mesh buffer]
              [meshbuffer info] (vertex/index offsets/counts)
              [material]
                 [common mat attributes]
                 [layer count]
                    [layer]
                       [texture name string chunk]
                       [layer attributes]
                    [/layer]
           [/mesh buffer]

           [mesh buffer]
              ...
           [/mesh buffer]
        [/mesh]

        [mesh]
        ...
        [/mesh]

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
        #define CID_STRING   117

        // irrb header
        struct IrrbHeader
        {
            c8      hSig[12];   // 'irrb vh.vl' eof
            u32     hSigCheck;
            u8      hFill1;
            u16     hFill2;            
            u16     hVersion;
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

        struct IrrbMaterialLayer_1_6
        {
            bool    mBilinearFilter;
            bool    mTrilinearFilter;
            u8      mAnisotropicFilter;
            u8      mLODBias;
            u32     mTextureWrap;
            f32     mMatrix[16];
        } PACK_STRUCT;

        struct IrrbMaterial_1_6
        {
            u32     mType;
            u32     mAmbient;
            u32     mDiffuse;
            u32     mEmissive;
            u32     mSpecular;
            f32     mShininess;
            f32     mParm1;
            f32     mParm2;
            bool    mWireframe;
            bool    mGrouraudShading;
            bool    mLighting;
            bool    mZWriteEnabled;
            u32     mZBuffer;
            bool    mBackfaceCulling;
            bool    mFogEnable;
            bool    mNormalizeNormals;
            u8      mAntiAliasing;
            u8      mColorMask;
            u8      mLayerCount;
        } PACK_STRUCT;

        struct IrrbMeshBufInfo_1_6
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

            void setVersion(u16 value) {Version = value;}
            void setCreator(irr::core::stringc value) {Creator = value;}

        protected:

            void writeHeader(const scene::IMesh* mesh);

            void updateMaterial(const video::SMaterial& material,struct IrrbMaterial_1_6& mat);
            void updateMaterialLayer(const video::SMaterial& material,u8 layerNumber, irr::core::stringc& textureName, struct IrrbMaterialLayer_1_6& layer);

            bool _writeMesh(const scene::IMesh* mesh);

            u32 _writeChunkInfo(u32 id, u32 size);
            void _writeStringChunk(irr::core::stringc value);
            void _updateChunkSize(u32 id, u32 offset);
            void updateBuffers(const scene::IMesh* mesh, struct IrrbVertex* vbuffer, u32* ibuffer);


            bool addMaterial(irr::video::SMaterial& material);
            u32 getMaterialIndex(irr::video::SMaterial& material);

            // member variables:
            irr::core::array<irr::video::SMaterial> Materials;
            struct IrrbVertex*   VBuffer;
            u32*    IBuffer;
            io::IFileSystem* FileSystem;
            video::IVideoDriver* VideoDriver;
            io::IWriteFile* Writer;
            u16 Version;
            irr::core::stringc Creator;
        };

    } // end namespace
} // end namespace

#endif

