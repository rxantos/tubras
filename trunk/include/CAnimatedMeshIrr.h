// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_ANIMATED_MESH_IRR_H_INCLUDED__
#define __C_ANIMATED_MESH_IRR_H_INCLUDED__

#include "IMesh.h"
#include "CSkinnedMesh.h"
#include "CMeshBuffer.h"
#include "IReadFile.h"
#include "S3DVertex.h"
#include "irrArray.h"
#include "irrString.h"
#include "irrMap.h"

namespace irr
{
namespace scene
{

    typedef struct {
        s32     buffer;
        s32     index;
        f32     x,y,z;
    } MorphTargetVertex, *PMorphTargetVertex;

    typedef core::array<PMorphTargetVertex> MorphTargetVertexArray;
    typedef struct {
        MorphTargetVertexArray    verts;
    } MorphTargetKey, *PMorphTargetKey;

    typedef core::map<irr::core::stringc,PMorphTargetKey> MorphTargetMap;

	class CAnimatedMeshIrr : public CSkinnedMesh
	{
	public:

		//! constructor
		CAnimatedMeshIrr(scene::IMesh* mesh=0, scene::E_ANIMATED_MESH_TYPE type=scene::EAMT_SKINNED) : CSkinnedMesh(), Type(type)
		{
			#ifdef _DEBUG
			setDebugName("SAnimatedMesh");
			#endif
			addMesh(mesh);
			recalculateBoundingBox();
		}


		//! destructor
		virtual ~CAnimatedMeshIrr()
		{
            // destroy shapes
            MorphTargetMap::Iterator cur;
            while(MorphTargets.size() > 0)
            {
                cur=MorphTargets.getIterator();
                PMorphTargetKey pkey = cur->getValue();
                for(u32 i=0;i<pkey->verts.size();i++)
                {
                    PMorphTargetVertex pskey = pkey->verts[i];
                    delete pskey;
                }
                MorphTargetMap::Node* p = MorphTargets.delink(cur->getKey());
                delete p;
                delete pkey;
            }

			// drop meshes
			for (u32 i=0; i<Meshes.size(); ++i)
				Meshes[i]->drop();
		};


		//! Gets the frame count of the animated mesh.
		/** \return Amount of frames. If the amount is 1, it is a static, non animated mesh. */
		virtual u32 getFrameCount() const
		{
			return Meshes.size();
		}


		//! Returns the IMesh interface for a frame.
		/** \param frame: Frame number as zero based index. The maximum frame number is
		getFrameCount() - 1;
		\param detailLevel: Level of detail. 0 is the lowest,
		255 the highest level of detail. Most meshes will ignore the detail level.
		\param startFrameLoop: start frame
		\param endFrameLoop: end frame
		\return The animated mesh based on a detail level. */
		virtual IMesh* getMesh(s32 frame, s32 detailLevel, s32 startFrameLoop=-1, s32 endFrameLoop=-1)
		{
			if (Meshes.empty())
				return 0;

			return Meshes[frame];
		}

		//! Animates this mesh's joints based on frame input
		//! blend: {0-old position, 1-New position}
		virtual void animateMesh(f32 frame, f32 blend);


		//! adds a Mesh
		void addMesh(IMesh* mesh)
		{
			if (mesh)
			{
				mesh->grab();
				Meshes.push_back(mesh);
			}
		}


		//! Returns an axis aligned bounding box of the mesh.
		/** \return A bounding box of this mesh is returned. */
		virtual const core::aabbox3d<f32>& getBoundingBox() const
		{
			return Box;
		}


		//! set user axis aligned bounding box
		virtual void setBoundingBox( const core::aabbox3df& box)
		{
			Box = box;
		}

		//! Recalculates the bounding box.
		void recalculateBoundingBox()
		{
			Box.reset(0,0,0);

			if (Meshes.empty())
				return;

			Box = Meshes[0]->getBoundingBox();

			for (u32 i=1; i<Meshes.size(); ++i)
				Box.addInternalBox(Meshes[i]->getBoundingBox());
		}


		//! Returns the type of the animated mesh.
		virtual E_ANIMATED_MESH_TYPE getMeshType() const
		{
			return Type;
		}


		//! returns amount of mesh buffers.
		virtual u32 getMeshBufferCount() const
		{
			if (Meshes.empty())
				return 0;

			return Meshes[0]->getMeshBufferCount();
		}


		//! returns pointer to a mesh buffer
		virtual IMeshBuffer* getMeshBuffer(u32 nr) const
		{
			if (Meshes.empty())
				return 0;

			return Meshes[0]->getMeshBuffer(nr);
		}


		//! Returns pointer to a mesh buffer which fits a material
		/** \param material: material to search for
		\return Returns the pointer to the mesh buffer or
		NULL if there is no such mesh buffer. */
		virtual IMeshBuffer* getMeshBuffer( const video::SMaterial &material) const
		{
			if (Meshes.empty())
				return 0;

			return Meshes[0]->getMeshBuffer(material);
		}


		//! Set a material flag for all meshbuffers of this mesh.
		virtual void setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue)
		{
			for (u32 i=0; i<Meshes.size(); ++i)
				Meshes[i]->setMaterialFlag(flag, newvalue);
		}

        virtual void addMorphTargetVertex(const core::stringc targetName, const PMorphTargetVertex vtx)
        {
            PMorphTargetKey skey;
            MorphTargetMap::Node* snode;
            snode = MorphTargets.find(targetName);
            if(!snode)
            {
                skey = new MorphTargetKey();
                MorphTargets[targetName] = skey;
            }
            else skey = snode->getValue();

            skey->verts.push_back(vtx);
        }

		//! The bounding box of this mesh
		core::aabbox3d<f32> Box;
		//! All meshes defining the animated mesh
		core::array<IMesh*> Meshes;
		//! Tyhe type fo the mesh.
		E_ANIMATED_MESH_TYPE Type;

    
    protected:
        friend class CIrrMeshFileLoader;
        
        MorphTargetMap    MorphTargets;

	};

} // end namespace scene
} // end namespace irr

#endif

