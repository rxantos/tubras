//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TMEMORYARCHIVE_H_
#define _TMEMORYARCHIVE_H_
namespace Tubras
{
    class TMemoryArchive : public io::IArchiveLoader
    {
    public:
        struct TMemFileInfo : public IReferenceCounted
        {
            irr::core::stringc      FileName;
            void*                   Memory;
            irr::u32                Size;
            bool                    DeleteOnDrop;
        };

    protected:
        IrrlichtDevice*             m_device;
        core::array<TMemFileInfo*>  m_fileInfo;

    public:

        TMemoryArchive(irr::IrrlichtDevice* device);

        ~TMemoryArchive();

        u32 addFileInfo(TMemFileInfo* fileInfo);

        bool isALoadableFileFormat(const path& filename) const;

        bool isALoadableFileFormat(io::IReadFile* file) const;

        bool isALoadableFileFormat(E_FILE_ARCHIVE_TYPE t) const;

        IFileArchive* createArchive(const path& filename, bool ignoreCase, bool ignorePaths) const;

        IFileArchive* createArchive(io::IReadFile* file, bool ignoreCase, bool ignorePaths) const;
    };
}
#endif
