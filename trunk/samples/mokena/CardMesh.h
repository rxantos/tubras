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
#ifndef _CARD_H_
#define _CARD_H_

struct TCardVertexDef
{
    TReal x, y, z;          // The position for the vertex.
    TReal nx,ny,nz;         // vertex normal
    Ogre::RGBA diffuse;     // colour of the vertex
};

struct TCardUVDef
{
    TReal   u,v;            // uv coordinates
};



class TCardMesh
{
private:
    Tubras::TString     m_name;
    Ogre::MeshPtr       m_mesh;
    Ogre::HardwareVertexBufferSharedPtr m_vBuf;
    Ogre::HardwareVertexBufferSharedPtr m_uvBuf;

    Ogre::SubMesh*      m_back;
    Ogre::HardwareIndexBufferSharedPtr  m_backIBuf;

    Ogre::SubMesh*      m_front;
    Ogre::HardwareIndexBufferSharedPtr  m_frontIBuf;

public:
    TCardMesh(Tubras::TString meshName);
    virtual ~TCardMesh();
    int initialize();
};

#endif
