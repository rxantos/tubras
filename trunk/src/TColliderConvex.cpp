//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T C o l l i d e r C o n v e x 
    //-----------------------------------------------------------------------
    TColliderConvex::TColliderConvex(TNodeDecomposer* decomposer) : TColliderShape()
    {

		btTriangleMesh* trimesh = new btTriangleMesh();

		btVector3 localScaling(1.0,1.0,1.0);
        size_t* mIndices = decomposer->getIndicesPtr();
        float* mVertices = decomposer->getVerticesPtr();
		
        for (size_t i=0;i<decomposer->getTriangleCount();i++)
		{
            size_t index0 = mIndices[i*3];
			size_t index1 = mIndices[i*3+1];
			size_t index2 = mIndices[i*3+2];

			btVector3 vertex0(mVertices[index0*3], mVertices[index0*3+1],mVertices[index0*3+2]);
			btVector3 vertex1(mVertices[index1*3], mVertices[index1*3+1],mVertices[index1*3+2]);
			btVector3 vertex2(mVertices[index2*3], mVertices[index2*3+1],mVertices[index2*3+2]);
			
			vertex0 *= localScaling;
			vertex1 *= localScaling;
			vertex2 *= localScaling;

			trimesh->addTriangle(vertex0,vertex1,vertex2);
		}

		m_shape = new btConvexTriangleMeshShape(trimesh);
		bool isDynamic = true;
		float mass = 1.f;
		
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(20,2,0));

		createRigidBody(mass, startTransform,m_shape);
    }

    //-----------------------------------------------------------------------
    //                      ~ T C o l l i d e r C o n v e x 
    //-----------------------------------------------------------------------
    TColliderConvex::~TColliderConvex()
    {
    }


}