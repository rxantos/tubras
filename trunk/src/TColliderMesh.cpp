//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T C o l l i d e r M e s h
    //-----------------------------------------------------------------------
    TColliderMesh::TColliderMesh(IMesh* mesh,bool optimize) : TColliderShape()
    {

        m_triMesh = new btTriangleMesh();

        extractTriangles(mesh);

        

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
    void TColliderMesh::extractTriangles(IMesh* mesh)
    {

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

                btVector3 b1,b2,b3;
                TIBConvert::IrrToBullet(v1->Pos,b1);
                TIBConvert::IrrToBullet(v2->Pos,b2);
                TIBConvert::IrrToBullet(v3->Pos,b3);

                m_triMesh->addTriangle(b1,b2,b3);
            }

        }
    }
}

