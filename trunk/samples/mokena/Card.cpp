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

#define HWIDTH  1.0f        // half width
#define HHEIGHT 1.5f        // half height
#define HDEPTH  0.1f        // half depth
#define CCOLOUR 0xffffffff  // diffuse colour

const TReal CWIDTH = HWIDTH*2.f;
const TReal CHEIGHT = HHEIGHT*2.f;
const TReal CDEPTH = HDEPTH*2.f;
const TReal CINSET = CDEPTH / CWIDTH;

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
//  8,9,10,11 = 4,5,6,7 - used for left/right panel uv coords
//  12,13,14,15 = 4,5,6,7 - use for front pane uv coords

/// Define the vertices (16 vertices)
const size_t nVertices = 16;

TCardVertexDef  verts[nVertices] =
{
    {-HWIDTH,  HHEIGHT,  HDEPTH,    // 0 position
    -sqrt13,   sqrt13,  sqrt13,     // 0 normal
    CCOLOUR                         // 0 diffuse (white)
    },

    {HWIDTH,  HHEIGHT,  HDEPTH,     // 1 position
    -sqrt13,   sqrt13,  sqrt13,     // 1 normal
    CCOLOUR                         // 1 diffuse (white)
    },

    {  HWIDTH, -HHEIGHT,  HDEPTH,   // 2 position
    sqrt13,  -sqrt13,  sqrt13,      // 2 normal
    CCOLOUR                         // 2 diffuse (white)
    },

    {-HWIDTH, -HHEIGHT,  HDEPTH,    // 3 position
    -sqrt13,  -sqrt13,  sqrt13,     // 3 normal
    CCOLOUR                         // 3 diffuse (white)
    },

    {-HWIDTH,  HHEIGHT, -HDEPTH,    // 4 position
    -sqrt13,   sqrt13, -sqrt13,     // 4 normal
    CCOLOUR                         // 4 diffuse (white)
    },

    {HWIDTH,  HHEIGHT, -HDEPTH,     // 5 position
    sqrt13,   sqrt13, -sqrt13,      // 5 normal
    CCOLOUR                         // 5 diffuse (white)
    },

    {HWIDTH, -HHEIGHT, -HDEPTH,     // 6 position
    sqrt13,  -sqrt13, -sqrt13,      // 6 normal
    CCOLOUR                         // 6 diffuse (white)
    },

    {-HWIDTH, -HHEIGHT, -HDEPTH,    // 7 position
    -sqrt13,  -sqrt13, -sqrt13,     // 7 normal
    CCOLOUR                         // 7 diffuse (white)
    },

    //
    // identical to last 4 verts, but allows for different
    // uv coords on side panels
    //

    {-HWIDTH,  HHEIGHT, -HDEPTH,    // 8 position
    -sqrt13,   sqrt13, -sqrt13,     // 8 normal
    CCOLOUR                         // 8 diffuse (white)
    },

    {HWIDTH,  HHEIGHT, -HDEPTH,     // 9 position
    sqrt13,   sqrt13, -sqrt13,      // 9 normal
    CCOLOUR                         // 9 diffuse (white)
    },

    {HWIDTH, -HHEIGHT, -HDEPTH,     // 10 position
    sqrt13,  -sqrt13, -sqrt13,      // 10 normal
    CCOLOUR                         // 10 diffuse (white)
    },

    {-HWIDTH, -HHEIGHT, -HDEPTH,    // 11 position
    -sqrt13,  -sqrt13, -sqrt13,     // 11 normal
    CCOLOUR                         // 11 diffuse (white)
    },

    //
    // identical to last 4 verts, but allows for different
    // uv coords on front sub-mesh
    //

    {-HWIDTH,  HHEIGHT, -HDEPTH,    // 12 position
    -sqrt13,   sqrt13, -sqrt13,     // 12 normal
    CCOLOUR                         // 12 diffuse (white)
    },

    {HWIDTH,  HHEIGHT, -HDEPTH,     // 13 position
    sqrt13,   sqrt13, -sqrt13,      // 13 normal
    CCOLOUR                         // 13 diffuse (white)
    },

    {HWIDTH, -HHEIGHT, -HDEPTH,     // 14 position
    sqrt13,  -sqrt13, -sqrt13,      // 14 normal
    CCOLOUR                         // 14 diffuse (white)
    },

    {-HWIDTH, -HHEIGHT, -HDEPTH,    // 15 position
    -sqrt13,  -sqrt13, -sqrt13,     // 15 normal
    CCOLOUR                         // 15 diffuse (white)
    }
};

unsigned short backFaces[30] =
{
    4,0,1,                      // top left
    4,1,5,                      // top right
    8,11,3,                     // left left
    8,3,0,                      // left right
    1,2,10,                     // right left
    1,10,9,                     // right right
    7,2,3,                      // bottom left
    7,6,2,                      // bottom right
    0,3,2,                      // back left
    0,2,1                       // back right
};


unsigned short frontFaces[6] =
{
    13,14,12,                   // front left
    14,15,12                    // front right
};

TReal uvCoords[nVertices*2] =
{
    CINSET, CINSET,            // 0
    1.0f-CINSET,  CINSET,      // 1
    1.0f-CINSET,  1.0f-CINSET, // 2
    CINSET,  1.0f-CINSET,      // 3
    CINSET,  0.0f,             // 4
    1.0f-CINSET, 0.0f,         // 5
    1.0f-CINSET, 1.0f,         // 6
    CINSET, 1.0f,              // 7
    0,  CINSET,                // 8
    1.0f, CINSET,              // 9
    1.0f, 1.0f-CINSET,         // 10
    0.0f, 1.0f-CINSET,         // 11
    1.0f, 0.0f,                // 12
    0.0f, 0.0f,                // 13
    0.0f, 1.0f,                // 14
    1.0f, 1.0f                 // 15
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

    // Upload the index data to the card
    m_backIBuf->writeData(0, m_backIBuf->getSizeInBytes(), backFaces, true);

    // Set parameters of the submesh
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

    // Upload the index data to the card
    m_frontIBuf->writeData(0, m_frontIBuf->getSizeInBytes(), frontFaces, true);

    // Set parameters of the submesh
    m_front->useSharedVertices = true;
    m_front->indexData->indexBuffer = m_frontIBuf;
    m_front->indexData->indexCount = 6;
    m_front->indexData->indexStart = 0;


    // Set bounding information (for culling)
    m_mesh->_setBounds(AxisAlignedBox(-HWIDTH,-HHEIGHT,-HDEPTH,HWIDTH,HHEIGHT,HDEPTH));
    m_mesh->_setBoundingSphereRadius(Math::Sqrt(3*HHEIGHT*HHEIGHT));

    // Notify Mesh object that it has been loaded
    m_mesh->load();

    return 0;
}



