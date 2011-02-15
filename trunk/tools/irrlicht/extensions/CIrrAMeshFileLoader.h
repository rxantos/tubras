// Copyright (C) 2002-2011 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_MESHA_FILE_LOADER_H_INCLUDED__
#define __C_IRR_MESHA_FILE_LOADER_H_INCLUDED__

#include "IMeshLoader.h"
#include "IFileSystem.h"
#include "IVideoDriver.h"
#include "irrString.h"
#include "SMesh.h"
#include "SMeshBuffer.h"
#include "CDynamicMeshBuffer.h"
#include "ISceneManager.h"
#include "CSkinnedMesh.h"
#include "irrMap.h"

namespace irr
{
namespace scene
{


//! Meshloader capable of loading .irrmesh meshes, the Irrlicht Engine mesh format for static meshes
class CIrrAMeshFileLoader : public IMeshLoader
{
public:

	//! Constructor
	CIrrAMeshFileLoader(scene::ISceneManager* smgr, io::IFileSystem* fs);

	//! Destructor
	virtual ~CIrrAMeshFileLoader();

	//! returns true if the file maybe is able to be loaded by this class
	//! based on the file extension (e.g. ".cob")
	virtual bool isALoadableFileExtension(const io::path& filename) const;

	//! creates/loads an animated mesh from the file.
	//! \return Pointer to the created mesh. Returns 0 if loading failed.
	//! If you no longer need the mesh, you should call IAnimatedMesh::drop().
	//! See IReferenceCounted::drop() for more information.
	virtual IAnimatedMesh* createMesh(io::IReadFile* file);

private:

	//! reads a mesh sections and creates a mesh from it
	IAnimatedMesh* readMesh(io::IXMLReader* reader);

	//! reads a mesh sections and creates a mesh buffer from it
	IMeshBuffer* readMeshBuffer(io::IXMLReader* reader);

	//! skips an (unknown) section in the irrmesh file
	void skipSection(io::IXMLReader* reader, bool reportSkipping);

	//! reads a <material> element and stores it in the material section
	void readMaterial(io::IXMLReader* reader);

	//! parses a float from a char pointer and moves the pointer to
	//! the end of the parsed float
	inline f32 readFloat(const c8** p);

	//! parses an int from a char pointer and moves the pointer to
	//! the end of the parsed float
	inline s32 readInt(const c8** p);

	//! places pointer to next begin of a token
	void findNextNoneWhiteSpace(const c8** p);

	//! places pointer to next begin of a token
	void skipCurrentNoneWhiteSpace(const c8** p);

	//! reads floats from inside of xml element until end of xml element
	void readFloatsInsideElement(io::IXMLReader* reader, f32* floats, u32 count);

	//! read the mesh buffers
	void readMeshBuffer(io::IXMLReader* reader, int vertexCount, SSkinMeshBuffer* sbuffer);

	//! read indices
	void readIndices(io::IXMLReader* reader, int indexCount, core::array<u16>& indices);

	//! read skin weights
	void readSkinWeights(io::IXMLReader* reader, int weightCount);

    //! get joint based on unique internal id
    scene::ISkinnedMesh::SJoint* jointFromID(u32 id);

    //! read skeleton joint & animation data
    void readSkeletons();
    void readSkeletonData(io::IXMLReader* reader);

	// member variables
    typedef core::map<u32, scene::ISkinnedMesh::SJoint*> JOINT_MAP;
    core::map<core::stringc, JOINT_MAP*> SkelMap;
    core::stringc CurSkelLink;
	scene::ISceneManager* SceneManager;
	io::IFileSystem* FileSystem;
	CSkinnedMesh*	AnimatedMesh;
};


} // end namespace scene
} // end namespace irr

#endif

