// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_MESH_FILE_LOADER_H_INCLUDED__
#define __C_IRR_MESH_FILE_LOADER_H_INCLUDED__

#include "IMeshLoader.h"
#include "IFileSystem.h"
#include "IVideoDriver.h"
#include "irrString.h"
#include "SMesh.h"
#include "SMeshBuffer.h"
#include "ISceneManager.h"

namespace irr
{
namespace scene
{


//! Meshloader capable of loading .irrbmesh meshes, the Irrlicht Engine binary mesh format for static meshes
class CIrrBMeshFileLoader : public IMeshLoader
{
public:

	//! Constructor
	CIrrBMeshFileLoader(video::IVideoDriver* driver,
		scene::ISceneManager* smgr, io::IFileSystem* fs);

	//! destructor
	virtual ~CIrrBMeshFileLoader();

	//! returns true if the file maybe is able to be loaded by this class
	//! based on the file extension (e.g. ".cob")
	virtual bool isALoadableFileExtension(const c8* fileName) const;

	//! creates/loads an animated mesh from the file.
	//! \return Pointer to the created mesh. Returns 0 if loading failed.
	//! If you no longer need the mesh, you should call IAnimatedMesh::drop().
	//! See IReferenceCounted::drop() for more information.
	virtual IAnimatedMesh* createMesh(io::IReadFile* file);

private:

	//! reads a mesh sections and creates a mesh from it
	IAnimatedMesh* readMesh(io::IReadFile* reader);

    u32 readChunk(struct IrrbChunkInfo& chunk);

    SMesh* _readMesh(u32 index);
	IMeshBuffer* readMeshBuffer();
    void setMaterial(video::SMaterial& material, struct IrrbMaterial& mat);

	// member variables

	video::IVideoDriver* Driver;
	scene::ISceneManager* SceneManager;
	io::IFileSystem* FileSystem;
    io::IReadFile* Reader;

};


} // end namespace scene
} // end namespace irr

#endif

