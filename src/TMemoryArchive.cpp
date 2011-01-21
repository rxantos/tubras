//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T M e m o r y A r c h i v e
    //-----------------------------------------------------------------------
    TMemoryArchive::TMemoryArchive(irr::IrrlichtDevice* device) : m_device(device)
    {
    }

    //-----------------------------------------------------------------------
    //                      ~ T M e m o r y A r c h i v e
    //-----------------------------------------------------------------------
    TMemoryArchive::~TMemoryArchive()
    {
        for(u32 i=0; i<m_fileInfo.size(); i++)
        {
            TMemFileInfo* fileInfo = m_fileInfo[i];
            fileInfo->drop();
        }
    }

    //-----------------------------------------------------------------------
    //                        a d d F i l e I n f o
    //-----------------------------------------------------------------------
    u32 TMemoryArchive::addFileInfo(TMemFileInfo* fileInfo)
    {
        fileInfo->grab();
        m_fileInfo.push_back(fileInfo);
        return m_fileInfo.size();
    }

    //-----------------------------------------------------------------------
    //                i s A L o a d a b l e F i l e F o r m a t
    //-----------------------------------------------------------------------
    bool TMemoryArchive::isALoadableFileFormat(const path& filename) const
    {
        io::IFileSystem* fs = m_device->getFileSystem();
        // archive loaders
        s32 i = fs->getArchiveLoaderCount()-1;
        for (;i>=0; --i)
        {
            if (fs->getArchiveLoader(i) != this)
            {
                if(fs->getArchiveLoader(i)->isALoadableFileFormat(filename))
                    return true;
            }
        }

        return false; 
    }

    //-----------------------------------------------------------------------
    //                i s A L o a d a b l e F i l e F o r m a t
    //-----------------------------------------------------------------------
    bool TMemoryArchive::isALoadableFileFormat(io::IReadFile* file) const
    {
        io::IFileSystem* fs = m_device->getFileSystem();
        u32 i = fs->getArchiveLoaderCount()-1;
        for (;i>=0; --i)
        {
            if (fs->getArchiveLoader(i) != this)
                if(fs->getArchiveLoader(i)->isALoadableFileFormat(file))
                    return true;
        }

        // no match
        return false; 
    }

    //-----------------------------------------------------------------------
    //                i s A L o a d a b l e F i l e F o r m a t
    //-----------------------------------------------------------------------
    bool TMemoryArchive::isALoadableFileFormat(E_FILE_ARCHIVE_TYPE t) const
    {
        io::IFileSystem* fs = m_device->getFileSystem();
        // archive loaders
        s32 i = fs->getArchiveLoaderCount()-1;
        for (;i>=0; --i)
            if (fs->getArchiveLoader(i) != this &&
                fs->getArchiveLoader(i)->isALoadableFileFormat(t))
                return true;

        return false; 
    }

    //-----------------------------------------------------------------------
    //                       c r e a t e A r c h i v e
    //-----------------------------------------------------------------------
    IFileArchive* TMemoryArchive::createArchive(const path& filename,
        bool ignoreCase, bool ignorePaths) const
    {
        io::IReadFile* f=0;
        io::IFileArchive* ret=0;

        if(filename.equalsn(":mem:", 5))
        {
            for(u32 i=0;i<m_fileInfo.size(); i++)
            {
                if(m_fileInfo[i]->FileName == filename)
                {
                    f = m_device->getFileSystem()->createMemoryReadFile(m_fileInfo[i]->Memory, m_fileInfo[i]->Size,
                        m_fileInfo[i]->FileName, m_fileInfo[i]->DeleteOnDrop);
                    break;
                }
            }
        }
        else 
        {
            f = m_device->getFileSystem()->createAndOpenFile(filename);
        }

        if(f)
        {
            ret = createArchive(f, ignoreCase, ignorePaths);
            f->drop();
        }
        return ret; 
    }

    //-----------------------------------------------------------------------
    //                       c r e a t e A r c h i v e
    //-----------------------------------------------------------------------
    IFileArchive* TMemoryArchive::createArchive(io::IReadFile* file,
        bool ignoreCase, bool ignorePaths) const
    {
        io::IFileArchive* ret = 0;

        io::IFileSystem* fs = m_device->getFileSystem();

        // find the correct loader
        for (s32 i=fs->getArchiveLoaderCount()-1; !ret && i >= 0; --i)
        {
            if (fs->getArchiveLoader(i) != this &&
                fs->getArchiveLoader(i)->isALoadableFileFormat(file))
            {
                // attempt to open
                ret = fs->getArchiveLoader(i)->createArchive(file, ignoreCase, ignorePaths);
            }
        }

        return ret; 
    }
}
