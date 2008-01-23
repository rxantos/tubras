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
#define IRRB_VERSION    0x0100

#define INFO_ANIMATION_SKINNED  0x0001
#define INFO_ANIMATION_VERTEX   0x0002

#define CID_MESH     100
#define CID_ATTR     101
#define CID_MATERIAL 110
#define CID_VBUFFER  111
#define CID_IBUFFER  112
#define CID_TEXTURE  113
#define CID_SKEL     114
#define CID_MORPH    115

        // irrb header
        struct IrrbHeader
        {
            u32     hSig;
            u8      hEOF;
            u8      hFill1;
            u16     hFill2;
            u32     hVersion;
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

            void writeHeader();

            void writeBoundingBox(const core::aabbox3df& box);

            void writeMeshBuffer(const scene::IMeshBuffer* buffer);

            void writeMaterial(const video::SMaterial& material);


            // member variables:

            io::IFileSystem* FileSystem;
            video::IVideoDriver* VideoDriver;
            io::IWriteFile* Writer;
        };

    } // end namespace
} // end namespace

#endif

