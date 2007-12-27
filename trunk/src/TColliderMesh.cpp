//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T C o l l i d e r M e s h
    //-----------------------------------------------------------------------
    TColliderMesh::TColliderMesh(IMeshSceneNode* snode,bool optimize) : TColliderShape()
    {

        m_triMesh = new btTriangleMesh();

        extractTriangles(snode);

        m_shape = new btConvexTriangleMeshShape(m_triMesh);

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
    void TColliderMesh::extractTriangles(IMeshSceneNode* snode)
    {

        IMesh* mesh = snode->getMesh();

        u32 bufCount = mesh->getMeshBufferCount();

        for(u32 i=0;i<bufCount;i++)
        {
            IMeshBuffer* mbuf = mesh->getMeshBuffer(i);
            void* vp = mbuf->getVertices();
            E_VERTEX_TYPE vtype = mbuf->getVertexType();
            S3DVertex           *vstd = (S3DVertex*) vp;
            S3DVertex2TCoords   *v2t = (S3DVertex2TCoords*) vp;
            S3DVertexTangents   *vtan = (S3DVertexTangents*)vp;
            const u16* ip = mbuf->getIndices();
            u32 ic = mbuf->getIndexCount();
            u32 fi = 0;
            while(fi < ic)
            {
                S3DVertex *v1,*v2,*v3;
                TVector3 v[3];
                switch(vtype)
                {
                case EVT_2TCOORDS:
                    v1 = &v2t[ip[fi++]];
                    v2 = &v2t[ip[fi++]];
                    v3 = &v2t[ip[fi++]];
                    break;
                case EVT_TANGENTS:
                    v1 = &vtan[ip[fi++]];
                    v2 = &vtan[ip[fi++]];
                    v3 = &vtan[ip[fi++]];
                    break;
                default:
                    v1 = &vstd[ip[fi++]];
                    v2 = &vstd[ip[fi++]];
                    v3 = &vstd[ip[fi++]];
                    break;
                }

                m_triMesh->addTriangle(TIBConvert::IrrToBullet(v1->Pos),
                    TIBConvert::IrrToBullet(v2->Pos),
                    TIBConvert::IrrToBullet(v3->Pos));
            }

        }
    }
}