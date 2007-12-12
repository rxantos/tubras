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

#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T C o l l i d e r M e s h
    //-----------------------------------------------------------------------
    TColliderMesh::TColliderMesh(IMeshSceneNode* snode,bool optimize) : TColliderShape()
    {
        m_cvi = 0;
        m_cti = 0;
        m_vertexCount = 0;
        m_triCount = 0;
        m_indexCount = 0;
        m_entityCount = 0;
        m_submeshCount = 0;
        m_indices = NULL;
        m_vertices = NULL;

        m_triMesh = new btTriangleMesh();

        extractTriangles(snode);

        m_shape = new btConvexTriangleMeshShape(m_triMesh);

        if(m_indices)
            free(m_indices);
        if(m_vertices)
            free(m_vertices);

        m_indices = NULL;
        m_vertices = NULL;
    }

    //-----------------------------------------------------------------------
    //                       ~ T C o l l i d e r M e s h
    //-----------------------------------------------------------------------
    TColliderMesh::~TColliderMesh()
    {
        if(m_triMesh)
            delete m_triMesh;
    }

    //-----------------------------------------------------------------------
    //                     e x t r a c t T r i a n g l e s
    //-----------------------------------------------------------------------
    size_t TColliderMesh::extractTriangles(IMeshSceneNode* snode)
    {

        //
        // code ripped from OgreNewt and altered to work with Bullet.
        //

        // parse this scene node.
        // do children first.

        /*
        Ogre::SceneNode*  node = snode->getNode();
        Ogre::Quaternion thisOrient = node->getOrientation();
        Ogre::Vector3 thisPos = (node->getPosition() * node->getScale());
        Ogre::Vector3 thisScale = node->getScale();

        TSceneNode::TChildNodeIterator child_it = snode->getChildIterator();

        while (child_it.hasMoreElements())
        {
            extractTriangles( (TSceneNode*)child_it.getNext());
        }


        // now add the polys from this node.
        //now get the mesh!
        unsigned int num_obj = node->numAttachedObjects();
        for (unsigned int co=0; co<num_obj; co++)
        {
            Ogre::MovableObject* obj = node->getAttachedObject(co);
            if (obj->getMovableType() != "Entity")
                continue;

            ++m_entityCount;

            Ogre::Entity* ent = (Ogre::Entity*)obj;

            Ogre::MeshPtr mesh = ent->getMesh();

            //find number of sub-meshes
            unsigned short sub = mesh->getNumSubMeshes();

            m_submeshCount += sub;

            for (unsigned short cs=0;cs<sub;cs++)
            {
                Ogre::SubMesh* sub_mesh = mesh->getSubMesh(cs);

                //vertex data!
                Ogre::VertexData* v_data;

                if (sub_mesh->useSharedVertices)
                {	
                    v_data = mesh->sharedVertexData;
                }
                else
                {
                    v_data = sub_mesh->vertexData;
                }

                //let's find more information about the Vertices...
                Ogre::VertexDeclaration* v_decl = v_data->vertexDeclaration;
                const Ogre::VertexElement* p_elem = v_decl->findElementBySemantic( Ogre::VES_POSITION );

                // get pointer!
                Ogre::HardwareVertexBufferSharedPtr v_sptr = v_data->vertexBufferBinding->getBuffer( p_elem->getSource() );
                unsigned char* v_ptr = static_cast<unsigned char*>(v_sptr->lock( Ogre::HardwareBuffer::HBL_READ_ONLY ));

                //now find more about the index!!
                Ogre::IndexData* i_data = sub_mesh->indexData;
                size_t index_count = i_data->indexCount;
                size_t poly_count = index_count / 3;

                m_indexCount += index_count;
                m_vertexCount += index_count;
                m_triCount += poly_count;

                // get pointer!
                Ogre::HardwareIndexBufferSharedPtr i_sptr = i_data->indexBuffer;

                // 16 or 32 bit indices?
                bool uses32bit = ( i_sptr->getType() == Ogre::HardwareIndexBuffer::IT_32BIT );
                unsigned long* i_Longptr;
                unsigned short* i_Shortptr;

                if ( uses32bit)
                {
                    i_Longptr = static_cast<unsigned long*>(i_sptr->lock( Ogre::HardwareBuffer::HBL_READ_ONLY ));
                }
                else
                {
                    i_Shortptr = static_cast<unsigned short*>(i_sptr->lock( Ogre::HardwareBuffer::HBL_READ_ONLY ));
                }

                //now loop through the indices, getting polygon info!
                int i_offset = 0;

                if(!m_vertices)
                    m_vertices = (float*)malloc(3 * m_vertexCount * sizeof(float));
                else m_vertices = (float*)realloc(m_vertices,3 * m_vertexCount * sizeof(float));

                if(!m_indices)
                    m_indices = (size_t*)malloc(m_indexCount * sizeof(size_t));
                else m_indices = (size_t*)realloc(m_indices,m_indexCount * sizeof(size_t));

                for (size_t i=0; i<poly_count; i++)
                {
                    Ogre::Vector3 poly_verts[3];
                    unsigned char* v_offset;
                    float* v_Posptr;
                    int idx;


                    if (uses32bit)
                    {
                        for (int j=0;j<3;j++)
                        {
                            idx = i_Longptr[i_offset+j];		// index to first vertex!
                            v_offset = v_ptr + (idx * v_sptr->getVertexSize());
                            p_elem->baseVertexPointerToElement( v_offset, &v_Posptr );
                            //now get vertex position from v_Posptr!
                            poly_verts[j].x = *v_Posptr; v_Posptr++;
                            poly_verts[j].y = *v_Posptr; v_Posptr++;
                            poly_verts[j].z = *v_Posptr; v_Posptr++;

                            poly_verts[j] = thisPos + (thisOrient * (poly_verts[j] * thisScale));
                        }
                    }
                    else
                    {
                        for (int j=0;j<3;j++)
                        {
                            idx = i_Shortptr[i_offset+j];		// index to first vertex!
                            v_offset = v_ptr + (idx * v_sptr->getVertexSize());
                            p_elem->baseVertexPointerToElement( v_offset, &v_Posptr );
                            //now get vertex position from v_Posptr!

                            // switch poly winding.
                            poly_verts[j].x = *v_Posptr; v_Posptr++;
                            poly_verts[j].y = *v_Posptr; v_Posptr++;
                            poly_verts[j].z = *v_Posptr; v_Posptr++;

                            poly_verts[j] = thisPos + (thisOrient * (poly_verts[j] * thisScale));
                        }
                    }

                    addTri(poly_verts);
                    i_offset += 3;
                }

                //unlock the buffers!
                v_sptr->unlock();
                i_sptr->unlock();

            }
        }
        */
        return m_vertexCount;
    }

    //-----------------------------------------------------------------------
    //                              a d d T r i
    //-----------------------------------------------------------------------
    void TColliderMesh::addTri(TVector3 *vertices)
    {
        m_indices[m_cti] = m_cvi;
        for(int i=0;i<3;i++)
        {
            m_vertices[m_cvi] = vertices[i].X; m_cvi++;
            m_vertices[m_cvi] = vertices[i].Y; m_cvi++;
            m_vertices[m_cvi] = vertices[i].Z; m_cvi++;
        }
        m_triMesh->addTriangle(TIBConvert::IrrToBullet(vertices[0]),
                               TIBConvert::IrrToBullet(vertices[1]),
                               TIBConvert::IrrToBullet(vertices[2]));
        ++m_cti;
    }

}