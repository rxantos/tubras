//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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
    TColliderMesh::TColliderMesh(IMesh* mesh, bool isConvex, 
        bool convertToConvexHull, bool concaveDecomposition) : TColliderShape()
    {
        m_triMesh = extractTriangles(mesh);        

        if(isConvex || convertToConvexHull)
        {
            btConvexShape* shape = new btConvexTriangleMeshShape(m_triMesh);
            m_shape = shape;
            if(convertToConvexHull)
            {
                btShapeHull* hull = new btShapeHull(shape);
                btScalar margin = shape->getMargin();
                hull->buildHull(margin);
                shape->setUserPointer(hull);

                btConvexHullShape* chShape = new btConvexHullShape();
                for (int i=0;i<hull->numVertices();i++)
                {
                    chShape->addPoint(hull->getVertexPointer()[i]);	
                }
                m_shape = chShape;
                delete hull;
                delete shape;
            }
        }
        else 
        {
            if(concaveDecomposition)
                m_shape = _decomposeTriMesh();
            else
                m_shape = new btBvhTriangleMeshShape(m_triMesh,true,true);
        }
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
    btTriangleMesh* TColliderMesh::extractTriangles(IMesh* mesh)
    {
        // 32 bit indices, 3 component vertices - allows for use in decomposition.
        btTriangleMesh* triMesh = new btTriangleMesh(true, false);
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

                btVector3 b1(v1->Pos.X, v1->Pos.Y, v1->Pos.Z);
                btVector3 b2(v2->Pos.X, v2->Pos.Y, v2->Pos.Z);
                btVector3 b3(v3->Pos.X, v3->Pos.Y, v3->Pos.Z);

                triMesh->addTriangle(b1,b2,b3);
            }
        }
        return triMesh;
    }


    //-----------------------------------------------------------------------
    //                     C o n v e x D e c o m p R e s u l t
    //-----------------------------------------------------------------------
    void TColliderMesh::ConvexDecompResult(ConvexResult &result)
    {
        btTransform transform;
        btConvexHullShape* chShape = new btConvexHullShape();
        unsigned int vidx=0;
        for (unsigned int i=0;i<result.mHullVcount;i++)
        {
            btVector3 v(result.mHullVertices[vidx++],
                result.mHullVertices[vidx++],
                result.mHullVertices[vidx++]);
            chShape->addPoint(v);	
        }

        transform.setIdentity();
        m_compound->addChildShape(transform, chShape);
    }

    //-----------------------------------------------------------------------
    //                     _ d e c o m p o s e T r i M e s h
    //-----------------------------------------------------------------------
    btCompoundShape* TColliderMesh::_decomposeTriMesh()
    {

        unsigned int depth = 5;
        float cpercent     = 5;
        float ppercent     = 15;
        unsigned int maxv  = 16;
        float skinWidth    = 0.0;
        const unsigned char* vertexbase;
        int numverts;
        PHY_ScalarType vtype;
        int vstride;
        const unsigned char* indexbase;
        int istride;
        int numfaces;
        PHY_ScalarType itype;

        int subparts = m_triMesh->getNumSubParts();

        m_compound = new btCompoundShape();

        for(int part=0; part < subparts; part++)
        {
            m_triMesh->getLockedReadOnlyVertexIndexBase(&vertexbase, numverts, 
                vtype, vstride, &indexbase, istride, numfaces, itype, part);
            ConvexDecomposition::DecompDesc desc;
            desc.mVcount        = numverts;
            desc.mVertices      = (const float *)vertexbase;
            desc.mTcount        = numfaces;
            desc.mIndices       = (unsigned int *)indexbase;
            desc.mDepth         = depth;
            desc.mCpercent      = cpercent;
            desc.mPpercent      = ppercent;
            desc.mMaxVertices   = maxv;
            desc.mSkinWidth     = skinWidth;
            desc.mCallback      = this;

            ConvexBuilder cb(desc.mCallback);
            cb.process(desc);

            m_triMesh->unLockReadOnlyVertexBase(part);
        }

        return m_compound;
    }
}

