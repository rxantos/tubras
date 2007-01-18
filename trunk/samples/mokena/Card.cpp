//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
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
#include "mokena.h"

using namespace Ogre;

const float sqrt13 = 0.577350269f; /* sqrt(1/3) */

#define CWIDTH  1.0f
#define CHEIGHT 1.5f
#define CDEPTH  0.1f
//#define CCOLOUR 0xffffffff
#define CCOLOUR 0x0

//
//      4-----------5
//      |\          |\
//      | 0-----------1
//      | |         | |
//      | |           |
//      | |         | |
//      | |           |
//      | |         | |
//      | |           |
//      7-|- - - - -6 |
//       \|          \|
//        3-----------2
//
//  8,9,10,11 = 4,5,6,7

/// Define the vertices (12 vertices)
const size_t nVertices = 12;

TCardVertexDef  verts[nVertices] =
{
    {
    -CWIDTH,  CHEIGHT,  CDEPTH, // 0 position
    -sqrt13,   sqrt13,  sqrt13, // 0 normal
    CCOLOUR                     // 0 diffuse (white)
    },

    {
     CWIDTH,  CHEIGHT,  CDEPTH, // 1 position
    -sqrt13,   sqrt13,  sqrt13, // 1 normal
    CCOLOUR                     // 1 diffuse (white)
    },

    {
     CWIDTH, -CHEIGHT,  CDEPTH, // 2 position
     sqrt13,  -sqrt13,  sqrt13, // 2 normal
    CCOLOUR                     // 2 diffuse (white)
    },

    {
    -CWIDTH, -CHEIGHT,  CDEPTH, // 3 position
    -sqrt13,  -sqrt13,  sqrt13, // 3 normal
    CCOLOUR                     // 3 diffuse (white)
    },

    {
    -CWIDTH,  CHEIGHT, -CDEPTH, // 4 position
    -sqrt13,   sqrt13, -sqrt13, // 4 normal
    CCOLOUR                     // 4 diffuse (white)
    },

    {
     CWIDTH,  CHEIGHT, -CDEPTH, // 5 position
     sqrt13,   sqrt13, -sqrt13, // 5 normal
    CCOLOUR                     // 5 diffuse (white)
    },

    {
     CWIDTH, -CHEIGHT, -CDEPTH, // 6 position
     sqrt13,  -sqrt13, -sqrt13, // 6 normal
    CCOLOUR                     // 6 diffuse (white)
    },

    {
    -CWIDTH, -CHEIGHT, -CDEPTH, // 7 position
    -sqrt13,  -sqrt13, -sqrt13, // 7 normal
    CCOLOUR                     // 7 diffuse (white)
    },

    //
    // identical to last 4 verts, but allows for different
    // uv coords on front sub-mesh
    //

    {
    -CWIDTH,  CHEIGHT, -CDEPTH, // 8 position
    -sqrt13,   sqrt13, -sqrt13, // 8 normal
    CCOLOUR                     // 8 diffuse (white)
    },

    {
     CWIDTH,  CHEIGHT, -CDEPTH, // 9 position
     sqrt13,   sqrt13, -sqrt13, // 9 normal
    CCOLOUR                     // 9 diffuse (white)
    },

    {
     CWIDTH, -CHEIGHT, -CDEPTH, // 10 position
     sqrt13,  -sqrt13, -sqrt13, // 10 normal
    CCOLOUR                     // 10 diffuse (white)
    },

    {
    -CWIDTH, -CHEIGHT, -CDEPTH, // 11 position
    -sqrt13,  -sqrt13, -sqrt13, // 11 normal
    CCOLOUR                     // 11 diffuse (white)
    }


};

unsigned short backFaces[30] =
{
    4,0,1,                      // top left
    4,1,5,                      // top right
    4,7,3,                      // left left
    4,3,0,                      // left right
    1,2,6,                      // right left
    1,6,5,                      // right right
    3,7,6,                      // bottom left
    3,6,2,                      // bottom right
    0,3,2,                      // front left
    0,2,1                       // front right
};


unsigned short frontFaces[6] =
{
    9,10,11,                    // front left
    9,11,8                      // front right
};

TReal uvCoords[nVertices*2] =
{
    -1.0f,  1.0f,               // 0
     1.0f,  1.0f,               // 1
     1.0f, -1.0f,               // 2
    -1.0f, -1.0f,               // 3
    0.0f, 0.0f,                 // 4
    0.0f, 0.0f,                 // 5
    0.0f, 0.0f,                 // 6
    0.0f, 0.0f,                 // 7
    0.0f, 0.0f,                 // 8
    0.0f, 0.0f,                 // 9
    0.0f, 0.0f,                 // 10
    0.0f, 0.0f                  // 11
};

//-----------------------------------------------------------------------
//                              T C a r d
//-----------------------------------------------------------------------
TCard::TCard(Tubras::TString meshName)
{
    m_name = meshName;
}


//-----------------------------------------------------------------------
//                             ~ T C a r d
//-----------------------------------------------------------------------
TCard::~TCard()
{
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TCard::initialize()
{
    m_mesh = Ogre::MeshManager::getSingleton().createManual(m_name, "General");

    //
    // Create front and back submeshes
    //
    m_back = m_mesh->createSubMesh("back");
    m_front = m_mesh->createSubMesh("front");

    //
    // Create vertex data structure for 8 vertices shared between submeshes
    //
    m_mesh->sharedVertexData = new Ogre::VertexData();
	m_mesh->sharedVertexData->vertexCount = nVertices;

    //
	// Create declaration (memory format) of vertex data
    //
    Ogre::VertexDeclaration* decl = m_mesh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;

    //
	// 1st buffer - pos, normal, and diffuse
    //
	decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
	offset += VertexElement::getTypeSize(VET_FLOAT3);
	decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
	offset += VertexElement::getTypeSize(VET_FLOAT3);
    decl->addElement(0, offset, VET_COLOUR, VES_DIFFUSE);
    offset += VertexElement::getTypeSize(VET_COLOUR);

    //
    // Allocate vertex buffer of the requested number of vertices (vertexCount) 
	// and bytes per vertex (offset)
    //
	m_vBuf = 
		HardwareBufferManager::getSingleton().createVertexBuffer(
		offset, m_mesh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    //
	// Upload the vertex data to the card
    //
	m_vBuf->writeData(0, m_vBuf->getSizeInBytes(), verts, true);

	// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
	VertexBufferBinding* bind = m_mesh->sharedVertexData->vertexBufferBinding; 
	bind->setBinding(0, m_vBuf);

    //
	// 2nd buffer - uv coordinates
    //
	offset = 0;
	decl->addElement(1, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
    offset += VertexElement::getTypeSize(VET_FLOAT2);
    //
	// Allocate uv buffer of the requested number of vertices (vertexCount) 
	// and bytes per uv coordinate
    //
	m_uvBuf = HardwareBufferManager::getSingleton().createVertexBuffer(
		offset, m_mesh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    //
	// Upload the uv data to the card
    //
	m_uvBuf->writeData(0, m_uvBuf->getSizeInBytes(), uvCoords, true);

	// Set vertex buffer binding so buffer 1 is bound to our uv coordinates
	bind->setBinding(1, m_uvBuf);

    //
	// Allocate index buffer for back sub mesh
    //
	m_backIBuf = HardwareBufferManager::getSingleton().
		createIndexBuffer(
		HardwareIndexBuffer::IT_16BIT, 
		30, 
		HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	/// Upload the index data to the card
	m_backIBuf->writeData(0, m_backIBuf->getSizeInBytes(), backFaces, true);

	/// Set parameters of the submesh
	m_back->useSharedVertices = true;
	m_back->indexData->indexBuffer = m_backIBuf;
	m_back->indexData->indexCount = 30;
	m_back->indexData->indexStart = 0;

    
    //
	// Allocate index buffer for front sub mesh
    //
	m_frontIBuf = HardwareBufferManager::getSingleton().
		createIndexBuffer(
		HardwareIndexBuffer::IT_16BIT, 
		6, 
		HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	/// Upload the index data to the card
	m_frontIBuf->writeData(0, m_frontIBuf->getSizeInBytes(), frontFaces, true);

	/// Set parameters of the submesh
	m_front->useSharedVertices = true;
	m_front->indexData->indexBuffer = m_frontIBuf;
	m_front->indexData->indexCount = 6;
	m_front->indexData->indexStart = 0;
    

	/// Set bounding information (for culling)
	m_mesh->_setBounds(AxisAlignedBox(-CWIDTH,-CHEIGHT,-CDEPTH,CWIDTH,CHEIGHT,CDEPTH));
	m_mesh->_setBoundingSphereRadius(Math::Sqrt(3*CHEIGHT*CHEIGHT));

	/// Notify Mesh object that it has been loaded
	m_mesh->load();

    return 0;
}



