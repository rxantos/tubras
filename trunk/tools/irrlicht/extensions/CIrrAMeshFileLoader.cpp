// Copyright (C) 2002-2011 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "IrrCompileConfig.h"
#ifdef _IRR_COMPILE_WITH_IRR_MESH_LOADER_

#include "CIrrAMeshFileLoader.h"
#include "os.h"
#include "IXMLReader.h"
#include "SAnimatedMesh.h"
#include "fast_atof.h"
#include "IReadFile.h"
#include "IAttributes.h"
#include "IMeshSceneNode.h"
#include "CDynamicMeshBuffer.h"
#include "SMeshBufferLightMap.h"

namespace irr
{
namespace scene
{


//! Constructor
CIrrAMeshFileLoader::CIrrAMeshFileLoader(scene::ISceneManager* smgr,
		io::IFileSystem* fs)
	: IMeshLoader(), SceneManager(smgr), FileSystem(fs)
{

	#ifdef _DEBUG
	setDebugName("CIrrAMeshFileLoader");
	#endif

}

CIrrAMeshFileLoader::~CIrrAMeshFileLoader()
{
}

//! Returns true if the file maybe is able to be loaded by this class.
/** This decision should be based only on the file extension (e.g. ".cob") */
bool CIrrAMeshFileLoader::isALoadableFileExtension(const io::path& filename) const
{
	return core::hasFileExtension ( filename, "xml", "irrmesh" );
}


//! creates/loads an animated mesh from the file.
//! \return Pointer to the created mesh. Returns 0 if loading failed.
//! If you no longer need the mesh, you should call IAnimatedMesh::drop().
//! See IReferenceCounted::drop() for more information.
IAnimatedMesh* CIrrAMeshFileLoader::createMesh(io::IReadFile* file)
{
	io::IXMLReader* reader = FileSystem->createXMLReader(file);
	if (!reader)
		return 0;

    MeshFileName = file->getFileName();

	// read until mesh section, skip other parts
	const core::stringc meshTagName = "mesh";

	while(reader->read())
	{
		if (reader->getNodeType() == io::EXN_ELEMENT)
		{
			if (meshTagName == reader->getNodeName())
			{
				readMesh(reader);
				break;
			}
			else
				skipSection(reader, true); // unknown section
		}
	}

	reader->drop();

    AnimatedMesh->finalize();

	return AnimatedMesh;
}


//! reads a mesh sections and creates a mesh from it
IAnimatedMesh* CIrrAMeshFileLoader::readMesh(io::IXMLReader* reader)
{
    AnimatedMesh = new scene::CSkinnedMesh();
    AnimatedMesh->setAnimationSpeed(30);

	core::stringc bbSectionName = "boundingBox";
	core::stringc bufferSectionName = "buffer";
	core::stringc meshSectionName = "mesh";

	if (!reader->isEmptyElement())
	while(reader->read())
	{
		if (reader->getNodeType() == io::EXN_ELEMENT)
		{
			const wchar_t* nodeName = reader->getNodeName();
			if (bbSectionName == nodeName)
			{
				// inside a bounding box, ignore it for now because
				// we are calculating this anyway ourselves later.
			}
			else
			if (bufferSectionName == nodeName)
			{
				// we've got a mesh buffer
				readMeshBuffer(reader);
			}
			else
				skipSection(reader, true); // unknown section

		} // end if node type is element
		else
		if (reader->getNodeType() == io::EXN_ELEMENT_END)
		{
			if (meshSectionName == reader->getNodeName())
			{
				// end of mesh section reached, cancel out
				break;
			}
		}
	} // end while reader->read();

	return AnimatedMesh;
}


//! reads a mesh sections and creates a mesh buffer from it
IMeshBuffer* CIrrAMeshFileLoader::readMeshBuffer(io::IXMLReader* reader)
{
	SSkinMeshBuffer* buffer = 0;

	core::stringc verticesSectionName = "vertices";
	core::stringc bbSectionName = "boundingBox";
	core::stringc materialSectionName = "material";
	core::stringc indicesSectionName = "indices";
	core::stringc bufferSectionName = "buffer";
	core::stringc swSectionName = "skinWeights";
    // inside <buffer>
    //  <skinWeights weightCount="?" link="ref.irrskel">
    //      vidx jidx weight
    //  </skinWeights>


	bool insideVertexSection = false;
	bool insideIndexSection = false;
    bool insideJointWeightSection = false;
    bool insideSkinWeightSection = false;    

	int vertexCount = 0;
	int indexCount = 0;
    int weightCount = 0;
    core::stringc skelLink;


	video::SMaterial material;

	if (!reader->isEmptyElement())
	while(reader->read())
	{
		if (reader->getNodeType() == io::EXN_ELEMENT)
		{
			const wchar_t* nodeName = reader->getNodeName();
			if (bbSectionName == nodeName)
			{
				// inside a bounding box, ignore it for now because
				// we are calculating this anyway ourselves later.
			}
			else
			if (materialSectionName == nodeName)
			{
				//we've got a material

				io::IAttributes* attributes = FileSystem->createEmptyAttributes(SceneManager->getVideoDriver());
				attributes->read(reader, true, L"material");

				SceneManager->getVideoDriver()->fillMaterialStructureFromAttributes(material, attributes);
				attributes->drop();
			}
			else
			if (verticesSectionName == nodeName)
			{
				// vertices section

				const core::stringc vertexTypeName1 = "standard";
				const core::stringc vertexTypeName2 = "2tcoords";
				const core::stringc vertexTypeName3 = "tangents";

				const wchar_t* vertexType = reader->getAttributeValue(L"type");
				vertexCount = reader->getAttributeValueAsInt(L"vertexCount");

				insideVertexSection = true;

				video::E_INDEX_TYPE itype = (vertexCount > 65536)?irr::video::EIT_32BIT:irr::video::EIT_16BIT;
                buffer = AnimatedMesh->addMeshBuffer();
                
				if (vertexTypeName1 == vertexType)
                {
                    buffer->Vertices_Standard.reallocate(vertexCount);
                }
                else
				if (vertexTypeName2 == vertexType)
				{
                    buffer->convertTo2TCoords();
                    buffer->Vertices_2TCoords.reallocate(vertexCount);
				}
				else
				if (vertexTypeName3 == vertexType)
				{
                    buffer->convertToTangents();
                    buffer->Vertices_Tangents.reallocate(vertexCount);
				}
				buffer->Material = material;
			}
			else
			if (indicesSectionName == nodeName)
			{
				// indices section

				indexCount = reader->getAttributeValueAsInt(L"indexCount");
				insideIndexSection = true;
			}
            else
            if (swSectionName == nodeName)
            {
                // skinWeight section
                weightCount = reader->getAttributeValueAsInt(L"weightCount");
                skelLink = reader->getAttributeValue(L"link");

                // not all weights may reference all bones, so we read the .irrskel
                // file data here.
                if(!loadSkelLink(skelLink))
                {
                    // todo error & skip weights...
                }

                insideSkinWeightSection = true;
            }

		} // end if node type is element
		else
		if (reader->getNodeType() == io::EXN_TEXT)
		{
			// read vertex data
			if (insideVertexSection)
			{
				readMeshBuffer(reader, vertexCount, buffer);
				insideVertexSection = false;

			} // end reading vertex array
			else
			if (insideIndexSection)
			{
                readIndices(reader, indexCount, buffer->Indices);
				insideIndexSection = false;
			}
            else
            if (insideSkinWeightSection)
            {
                readSkinWeights(reader, weightCount, skelLink);
                insideSkinWeightSection = false;
            }
            

		} // end if node type is text
		else
		if (reader->getNodeType() == io::EXN_ELEMENT_END)
		{
			if (bufferSectionName == reader->getNodeName())
			{
				// end of buffer section reached, cancel out
				break;
			}
		}
	} // end while reader->read();

	if (buffer)
		buffer->recalculateBoundingBox();

	return buffer;
}


//! read indices
void CIrrAMeshFileLoader::readIndices(io::IXMLReader* reader, int indexCount, core::array<u16>& indices)
{
	indices.reallocate(indexCount);

	core::stringc data = reader->getNodeData();
	const c8* p = &data[0];

	for (int i=0; i<indexCount && *p; ++i)
	{
		findNextNoneWhiteSpace(&p);
		indices.push_back(readInt(&p));
	}
}

scene::ISkinnedMesh::SJoint* CIrrAMeshFileLoader::jointFromIndex(const core::stringc skelLink, u32 index,
                                                                 bool createIfNotFound)
{
    scene::ISkinnedMesh::SJoint* result=0;

    JOINT_MAP* jmap;
    core::map<core::stringc, JOINT_MAP*>::Node* sn = SkelMap.find(skelLink);

    if(sn)
        jmap = sn->getValue();
    else
    {
        jmap = new JOINT_MAP();
        SkelMap[skelLink] = jmap;
    }

    JOINT_MAP::Node* jnode = jmap->find(index);

	if (jnode)
		return jnode->getValue();

    if(createIfNotFound)
    {
        result = AnimatedMesh->addJoint();
        jmap->set(index, result);
    }

    return result;
}

scene::ISkinnedMesh::SJoint* CIrrAMeshFileLoader::jointFromName(const core::stringc skelLink, const core::stringc name)
{
    scene::ISkinnedMesh::SJoint* result=0;

    JOINT_MAP* jmap;
    core::map<core::stringc, JOINT_MAP*>::Node* sn = SkelMap.find(skelLink);

    if(sn)
        jmap = sn->getValue();
    else
    {
        return 0;
    }

    JOINT_MAP::Iterator itr = jmap->getIterator();

    while(!itr.atEnd())
    {
        JOINT_MAP::Node* n = itr.getNode();
        result = n->getValue();
        if(result->Name == name)
            return result;
        itr++;
    }

    return 0;
}

void CIrrAMeshFileLoader::readCurveData(io::IXMLReader* reader, const core::stringc skelLink, 
                                        const core::stringc animationName, f32 animationLength)
{
	core::stringc animationSectionName = "animation";
	core::stringc curveSectionName = "curve";
    core::stringc keyframeSectionName = "keyframe";

    f32 TotalFrames = animationLength * AnimatedMesh->getAnimationSpeed();
    f32 FrameBase = (f32) FrameCount;

    io::IAttributes* attr = FileSystem->createEmptyAttributes();

    attr->addString("animationName", animationName.c_str());
    attr->addInt("startFrame", FrameBase);
    attr->addInt("endFrame", FrameBase + TotalFrames);

    AnimatedMesh->addNamedAnimationData(animationName.c_str(), attr);    

	while(reader->read())
	{
		if (reader->getNodeType() == io::EXN_ELEMENT)
		{
			const wchar_t* nodeName = reader->getNodeName();
			if (curveSectionName == nodeName)
			{
                core::stringc jointName = reader->getAttributeValueSafe(L"joint");
                scene::ISkinnedMesh::SJoint* joint = jointFromName(skelLink, jointName);
                // inside <curve> section
                while(reader->read())
                {
                    if (reader->getNodeType() == io::EXN_ELEMENT)
                    {
			            const wchar_t* nodeName = reader->getNodeName();
                        if(keyframeSectionName == nodeName)
                        {
                            f32 time = reader->getAttributeValueAsFloat(L"time");
                            core::stringc interpolation = reader->getAttributeValueSafe(L"interpolation");
                            if(!interpolation.size())
                                interpolation = "LINEAR";

                            io::IAttributes* attr = FileSystem->createEmptyAttributes();

                            attr->read(reader, false, nodeName);

                            f32 frame = FrameBase + (TotalFrames * time / animationLength);
                            if(attr->existsAttribute("Position"))
                            {
                                scene::ISkinnedMesh::SPositionKey pk;
                                pk.frame = frame;
                                pk.position = attr->getAttributeAsVector3d("Position");
                                joint->PositionKeys.push_back(pk);
                            }
                            if(attr->existsAttribute("Rotation"))
                            {
                                scene::ISkinnedMesh::SRotationKey rk;
                                rk.frame = frame;
                                rk.rotation = attr->getAttributeAsQuaternion("Rotation");
                                joint->RotationKeys.push_back(rk);
                            }
                            if(attr->existsAttribute("Scale"))
                            {
                                scene::ISkinnedMesh::SScaleKey sk;
                                sk.frame = frame;
                                sk.scale = attr->getAttributeAsVector3d("Scale");
                                joint->ScaleKeys.push_back(sk);
                            }
                        }
                        else
				            skipSection(reader, true); // unknown section                       
                    }
                    else
                    {
                        if (reader->getNodeType() == io::EXN_ELEMENT_END)
                        {
                            if (curveSectionName == reader->getNodeName())
                                break;
                        }
                    }
                }
			}
            /*  look for embedded <animation>
			else
			if (animationsSectionName == nodeName)
			{
				// inside <animations> section
                while(reader->read())
                {
	                core::stringc animationSectionName = "animation";
                    if (reader->getNodeType() == io::EXN_ELEMENT)
                    {
			            const wchar_t* nodeName = reader->getNodeName();
                        if(animationSectionName == nodeName)
                        {
                            core::stringc name = reader->getAttributeValueSafe(L"name");
                            f32 length = reader->getAttributeValueAsFloat(L"length");
                            readCurveData(reader, name, length);
                        }
                        else
				            skipSection(reader, true); // unknown section                       
                    }
                    else
                    {
                        if (reader->getNodeType() == io::EXN_ELEMENT_END)
                        {
                            if (animationsSectionName == reader->getNodeName())
                                break;
                        }
                    }
                }

			}
            */
			else
				skipSection(reader, true); // unknown section

		} // end if node type is element
		else
		if (reader->getNodeType() == io::EXN_ELEMENT_END)
		{
			if (animationSectionName == reader->getNodeName())
			{
				// end of curve section reached, cancel out
				break;
			}
		}
	} // end while reader->read();
    FrameCount += core::round32(TotalFrames);
}

bool CIrrAMeshFileLoader::isChildJoint(scene::ISkinnedMesh::SJoint* joint, 
                                       const core::array<scene::ISkinnedMesh::SJoint*> &allJoints)
{
    for(u32 i=0; i < allJoints.size(); i++)
    {
        scene::ISkinnedMesh::SJoint* ajoint = allJoints[i];

        if(joint == ajoint)
            continue;

        if(ajoint->Children.size())
        {
            for(u32 j=0; j<ajoint->Children.size(); j++)
            {
                scene::ISkinnedMesh::SJoint* cjoint = ajoint->Children[j];
                if(joint == cjoint)
                    return true;
            }
        }
    }
    
    return false;
}

void CIrrAMeshFileLoader::readSkeletonData(io::IXMLReader* reader, const core::stringc skelLink)
{

	core::stringc jointsSectionName = "joints";
    core::stringc jointSectionName = "joint";
	core::stringc animationsSectionName = "animations";
    core::stringc animationSectionName = "animation";
	core::stringc skeletonSectionName = "skeleton";
    core::map<core::stringc, core::stringc> parentMap;

    reader->read();
    if(reader->getNodeType() == io::EXN_ELEMENT)
    {
        const wchar_t* nodeName = reader->getNodeName();
        if(!skeletonSectionName.equals_ignore_case(nodeName))
        {
            return;
        }
    }
    else
    {
        return;
    }       

	while(reader->read())
	{
		if (reader->getNodeType() == io::EXN_ELEMENT)
		{
			const wchar_t* nodeName = reader->getNodeName();
			if (jointsSectionName == nodeName)
			{
                u32 jidx=0;
                // inside <joints> section (0 based index order)

                while(reader->read())
                {
                    if (reader->getNodeType() == io::EXN_ELEMENT)
                    {
			            const wchar_t* nodeName = reader->getNodeName();
                        if(jointSectionName == nodeName)
                        {
                            core::stringc name = reader->getAttributeValueSafe(L"name");
                            core::stringc parent = reader->getAttributeValueSafe(L"parent");
                            io::IAttributes* attr = FileSystem->createEmptyAttributes();

                            scene::ISkinnedMesh::SJoint* joint = jointFromIndex(skelLink, jidx, true);
                            if(joint)
                            {
                                joint->Name = name;
                                if(parent.size())
                                {
                                    parentMap[name] = parent;
                                }
                            }
                            else
                            {
                                os::Printer::log("irrSkel invalid id:", name);
                                continue;
                            }

                            attr->read(reader, false, nodeName);

                            joint->LocalMatrix.makeIdentity();
                            if(attr->existsAttribute("Rotation"))
                            {
                                core::vector3df rot = attr->getAttributeAsVector3d("Rotation");
                                joint->LocalMatrix = core::quaternion(rot).getMatrix();
                            }

                            if(attr->existsAttribute("Scale"))
                            {
                                core::vector3df scale = attr->getAttributeAsVector3d("Scale");
                                if(scale != core::vector3df(1,1,1))
                                {
                                    core::matrix4 scaleMatrix;
                                    scaleMatrix.setScale( scale );
                                    joint->LocalMatrix *= scaleMatrix;
                                }
                            }

                            if(attr->existsAttribute("Position"))
                            {
                                core::vector3df position = attr->getAttributeAsVector3d("Position");
                                joint->LocalMatrix.setTranslation(position);
                            }
                            ++jidx;
                        }
                        else
				            skipSection(reader, true); // unknown section                       
                    }
                    else
                    {
                        if (reader->getNodeType() == io::EXN_ELEMENT_END)
                        {
                            if (jointsSectionName == reader->getNodeName())
                                break;
                        }
                    }
                }
			}
			else
			if (animationsSectionName == nodeName)
			{
				// inside <animations> section
                while(reader->read())
                {
                    if (reader->getNodeType() == io::EXN_ELEMENT)
                    {
			            const wchar_t* nodeName = reader->getNodeName();
                        if(animationSectionName == nodeName)
                        {
                            core::stringc name = reader->getAttributeValueSafe(L"name");
                            f32 length = reader->getAttributeValueAsFloat(L"length");
                            readCurveData(reader, skelLink, name, length);
                        }
                        else
				            skipSection(reader, true); // unknown section                       
                    }
                    else
                    {
                        if (reader->getNodeType() == io::EXN_ELEMENT_END)
                        {
                            if (animationsSectionName == reader->getNodeName())
                                break;
                        }
                    }
                }
			}
			else
				skipSection(reader, true); // unknown section

		} // end if node type is element
		else
		if (reader->getNodeType() == io::EXN_ELEMENT_END)
		{
			if (skeletonSectionName == reader->getNodeName())
			{
				// end of mesh section reached, cancel out
				break;
			}
		}
	} // end while reader->read();

    // fixup parent/child relationships
    if(parentMap.size())
    {
        core::map<core::stringc, core::stringc>::Iterator itr = parentMap.getIterator();
        while(!itr.atEnd())
        {
            core::map<core::stringc, core::stringc>::Node* n = itr.getNode();
            core::stringc cname = n->getKey();
            core::stringc pname = n->getValue();
            scene::ISkinnedMesh::SJoint* cjoint = jointFromName(skelLink, cname);
            scene::ISkinnedMesh::SJoint* pjoint = jointFromName(skelLink, pname);
            if(pjoint && cjoint)
                pjoint->Children.push_back(cjoint);
            itr++;
        }
    }

}


bool CIrrAMeshFileLoader::loadSkelLink(core::stringc skelLink)
{
    // already loaded?
    core::map<core::stringc, JOINT_MAP*>::Node* sn = SkelMap.find(skelLink);
    if(sn)
        return true;

    // create joint map
    JOINT_MAP* jmap;
    jmap = new JOINT_MAP();
    SkelMap[skelLink] = jmap;

    FrameCount = 0;

    io::path MeshDir = FileSystem->getFileDir(MeshFileName);
    MeshDir += "/";
    io::IReadFile* file=0;
    // look for .irrskel in the same directory as the mesh file
    core::stringc SkelFileName = MeshDir + skelLink;
    if(FileSystem->existFile(SkelFileName))
        file = FileSystem->createAndOpenFile(SkelFileName);

    // if not found, then look in mounted file systems
    if(!file)
        file = FileSystem->createAndOpenFile(skelLink);

    if(file)
    {
        io::IXMLReader* reader = FileSystem->createXMLReader(file);
        readSkeletonData(reader, skelLink);
        reader->drop();
        file->drop();
    }
    else 
    {
        os::Printer::log("irrMesh missing skeleton link:", skelLink);
        return false;
    }

    return true;
}


void CIrrAMeshFileLoader::readSkinWeights(io::IXMLReader* reader, int weightCount, const core::stringc skelLink)
{
    core::stringc data = reader->getNodeData();
    const c8* p = &data[0];
    int vidx,jidx,meshBufferIndex;
    float w;

    u32 meshBufferIdx = AnimatedMesh->getMeshBufferCount()-1;

    for (int i=0; i<weightCount && *p; ++i)
    {
        // vertex index
        findNextNoneWhiteSpace(&p);
        vidx = readInt(&p);

        // joint index
        findNextNoneWhiteSpace(&p);
        jidx = readInt(&p);
        // weight
        findNextNoneWhiteSpace(&p);
        w = readFloat(&p);

        scene::ISkinnedMesh::SJoint* joint = jointFromIndex(skelLink, jidx);

        if(joint)
        {
            scene::ISkinnedMesh::SWeight* weight = AnimatedMesh->addWeight(joint);
            weight->buffer_id = meshBufferIdx;
            weight->vertex_id = vidx;
            weight->strength = w;
        }
    }
}

void CIrrAMeshFileLoader::readMeshBuffer(io::IXMLReader* reader, int vertexCount, SSkinMeshBuffer* sbuffer)
{
	core::stringc data = reader->getNodeData();
	const c8* p = &data[0];

    video::E_VERTEX_TYPE vType = sbuffer->getVertexType();

	if (sbuffer)
	{
		for (int i=0; i<vertexCount && *p; ++i)
		{
			switch(vType)
			{
			case video::EVT_STANDARD:
			{
				video::S3DVertex vtx;
				// position

				findNextNoneWhiteSpace(&p);
				vtx.Pos.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Pos.Y = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Pos.Z = readFloat(&p);

				// normal

				findNextNoneWhiteSpace(&p);
				vtx.Normal.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Normal.Y = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Normal.Z = readFloat(&p);

				// color

				u32 col;
				findNextNoneWhiteSpace(&p);
				sscanf(p, "%08x", &col);
				vtx.Color.set(col);
				skipCurrentNoneWhiteSpace(&p);

				// tcoord1

				findNextNoneWhiteSpace(&p);
				vtx.TCoords.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.TCoords.Y = readFloat(&p);

				sbuffer->Vertices_Standard.push_back(vtx);
			}
			break;
			case video::EVT_2TCOORDS:
			{
				video::S3DVertex2TCoords vtx;
				// position

				findNextNoneWhiteSpace(&p);
				vtx.Pos.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Pos.Y = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Pos.Z = readFloat(&p);

				// normal

				findNextNoneWhiteSpace(&p);
				vtx.Normal.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Normal.Y = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Normal.Z = readFloat(&p);

				// color

				u32 col;
				findNextNoneWhiteSpace(&p);
				sscanf(p, "%08x", &col);
				vtx.Color.set(col);
				skipCurrentNoneWhiteSpace(&p);

				// tcoord1

				findNextNoneWhiteSpace(&p);
				vtx.TCoords.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.TCoords.Y = readFloat(&p);

				// tcoord2

				findNextNoneWhiteSpace(&p);
				vtx.TCoords2.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.TCoords2.Y = readFloat(&p);

                sbuffer->Vertices_2TCoords.push_back(vtx);
			}
			break;

			case video::EVT_TANGENTS:
			{
				video::S3DVertexTangents vtx;
				// position

				findNextNoneWhiteSpace(&p);
				vtx.Pos.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Pos.Y = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Pos.Z = readFloat(&p);

				// normal

				findNextNoneWhiteSpace(&p);
				vtx.Normal.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Normal.Y = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Normal.Z = readFloat(&p);

				// color

				u32 col;
				findNextNoneWhiteSpace(&p);
				sscanf(p, "%08x", &col);
				vtx.Color.set(col);
				skipCurrentNoneWhiteSpace(&p);

				// tcoord1

				findNextNoneWhiteSpace(&p);
				vtx.TCoords.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.TCoords.Y = readFloat(&p);

				// tangent

				findNextNoneWhiteSpace(&p);
				vtx.Tangent.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Tangent.Y = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Tangent.Z = readFloat(&p);

				// binormal

				findNextNoneWhiteSpace(&p);
				vtx.Binormal.X = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Binormal.Y = readFloat(&p);
				findNextNoneWhiteSpace(&p);
				vtx.Binormal.Z = readFloat(&p);

                sbuffer->Vertices_Tangents.push_back(vtx);
			}
			break;
			};

		}
	}
}


//! skips an (unknown) section in the irrmesh document
void CIrrAMeshFileLoader::skipSection(io::IXMLReader* reader, bool reportSkipping)
{
#ifdef _DEBUG
	os::Printer::log("irrMesh skipping section", core::stringc(reader->getNodeName()).c_str());
#endif

	// skip if this element is empty anyway.
	if (reader->isEmptyElement())
		return;

	// read until we've reached the last element in this section
	u32 tagCounter = 1;

	while(tagCounter && reader->read())
	{
		if (reader->getNodeType() == io::EXN_ELEMENT &&
			!reader->isEmptyElement())
		{
			#ifdef _DEBUG
			if (reportSkipping)
				os::Printer::log("irrMesh unknown element:", core::stringc(reader->getNodeName()).c_str());
			#endif

			++tagCounter;
		}
		else
		if (reader->getNodeType() == io::EXN_ELEMENT_END)
			--tagCounter;
	}
}


//! parses a float from a char pointer and moves the pointer
//! to the end of the parsed float
inline f32 CIrrAMeshFileLoader::readFloat(const c8** p)
{
	f32 ftmp;
	*p = core::fast_atof_move(*p, ftmp);
	return ftmp;
}


//! parses an int from a char pointer and moves the pointer to
//! the end of the parsed float
inline s32 CIrrAMeshFileLoader::readInt(const c8** p)
{
	return (s32)readFloat(p);
}


//! places pointer to next begin of a token
void CIrrAMeshFileLoader::skipCurrentNoneWhiteSpace(const c8** start)
{
	const c8* p = *start;

	while(*p && !(*p==' ' || *p=='\n' || *p=='\r' || *p=='\t'))
		++p;

	// TODO: skip comments <!-- -->

	*start = p;
}

//! places pointer to next begin of a token
void CIrrAMeshFileLoader::findNextNoneWhiteSpace(const c8** start)
{
	const c8* p = *start;

	while(*p && (*p==' ' || *p=='\n' || *p=='\r' || *p=='\t'))
		++p;

	// TODO: skip comments <!-- -->

	*start = p;
}


//! reads floats from inside of xml element until end of xml element
void CIrrAMeshFileLoader::readFloatsInsideElement(io::IXMLReader* reader, f32* floats, u32 count)
{
	if (reader->isEmptyElement())
		return;

	while(reader->read())
	{
		// TODO: check for comments inside the element
		// and ignore them.

		if (reader->getNodeType() == io::EXN_TEXT)
		{
			// parse float data
			core::stringc data = reader->getNodeData();
			const c8* p = &data[0];

			for (u32 i=0; i<count; ++i)
			{
				findNextNoneWhiteSpace(&p);
				if (*p)
					floats[i] = readFloat(&p);
				else
					floats[i] = 0.0f;
			}
		}
		else
		if (reader->getNodeType() == io::EXN_ELEMENT_END)
			break; // end parsing text
	}
}




} // end namespace scene
} // end namespace irr

#endif // _IRR_COMPILE_WITH_IRR_MESH_LOADER_
