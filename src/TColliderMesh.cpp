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
    TColliderMesh::TColliderMesh(IMesh* mesh, const matrix4& transform, bool isConvex, 
        bool optimize) : TColliderShape(),
        m_hullCount(0),
        m_baseCount(0)
    {
        btQuaternion q(TMath::HALF_PI,0.f,0.f);
        m_localTransform = transform;
        m_localScale = transform.getScale();

        if(isConvex)
        {
            m_triMesh = extractTriangles(mesh, optimize);        
            btConvexShape* shape = new btConvexTriangleMeshShape(m_triMesh);
            m_shape = shape;
            if(optimize)
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
            m_triMesh = extractTriangles(mesh, optimize);        
            if(optimize)
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
    btTriangleMesh* TColliderMesh::extractTriangles(IMesh* mesh,   
        bool removeDupVertices)
    {
        // 32 bit indices, 3 component vertices - allows for use in decomposition.
        vector3df p1, p2, p3;

        //matrix4 transform = sceneNode->getRelativeTransformation();
        //vector3df scale = transform.getScale();

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

                
                /*
                m_localTransform.transformVect(p1, v1->Pos);
                m_localTransform.transformVect(p2, v2->Pos);
                m_localTransform.transformVect(p3, v3->Pos);
                */
                                
                p1 = v1->Pos * m_localScale;
                p2 = v2->Pos * m_localScale;
                p3 = v3->Pos * m_localScale;
                
                /*
                p1 = v1->Pos;
                p2 = v2->Pos;
                p3 = v3->Pos;
                */

                btVector3 b1(p1.X, p1.Y, p1.Z);
                btVector3 b2(p2.X, p2.Y, p2.Z);
                btVector3 b3(p3.X, p3.Y, p3.Z);

                triMesh->addTriangle(b1,b2,b3,removeDupVertices);
            }
        }
        return triMesh;
    }


    //-----------------------------------------------------------------------
    //                     C o n v e x D e c o m p R e s u l t
    //-----------------------------------------------------------------------
    void TColliderMesh::ConvexDecompResult(ConvexResult &result)
    {

        btTriangleMesh* trimesh = new btTriangleMesh();
        m_triMeshes.push_back(trimesh);

        btVector3 localScaling(1.f,1.f,1.f);
        btVector3	centroid(0,0,0);
        btVector3   convexDecompositionObjectOffset(0,0,0);


        btAlignedObjectArray<btVector3> vertices;
        //const unsigned int *src = result.mHullIndices;
        for (unsigned int i=0; i<result.mHullVcount; i++)
        {
            btVector3 vertex(result.mHullVertices[i*3],result.mHullVertices[i*3+1],result.mHullVertices[i*3+2]);
            vertex *= localScaling;
            centroid += vertex;

        }
        centroid *= 1.f/(float(result.mHullVcount) );

        //const unsigned int *src = result.mHullIndices;
        for (unsigned int i=0; i<result.mHullVcount; i++)
        {
            btVector3 vertex(result.mHullVertices[i*3],result.mHullVertices[i*3+1],result.mHullVertices[i*3+2]);
            vertex *= localScaling;
            vertex -= centroid ;
            vertices.push_back(vertex);
        }

        const unsigned int *src = result.mHullIndices;
        for (unsigned int i=0; i<result.mHullTcount; i++)
        {
            unsigned int index0 = *src++;
            unsigned int index1 = *src++;
            unsigned int index2 = *src++;


            btVector3 vertex0(result.mHullVertices[index0*3], result.mHullVertices[index0*3+1],result.mHullVertices[index0*3+2]);
            btVector3 vertex1(result.mHullVertices[index1*3], result.mHullVertices[index1*3+1],result.mHullVertices[index1*3+2]);
            btVector3 vertex2(result.mHullVertices[index2*3], result.mHullVertices[index2*3+1],result.mHullVertices[index2*3+2]);
            vertex0 *= localScaling;
            vertex1 *= localScaling;
            vertex2 *= localScaling;

            vertex0 -= centroid;
            vertex1 -= centroid;
            vertex2 -= centroid;


            trimesh->addTriangle(vertex0,vertex1,vertex2);

            index0+=m_baseCount;
            index1+=m_baseCount;
            index2+=m_baseCount;
        }


        btConvexHullShape* convexShape = new btConvexHullShape(&(vertices[0].getX()),vertices.size());
        convexShape->setMargin(0.01f);
        m_convexShapes.push_back(convexShape);
        m_convexCentroids.push_back(centroid);
        m_baseCount+=result.mHullVcount; // advance the 'base index' counter.

        /*
        btConvexHullShape* chShape = new btConvexHullShape();
        unsigned int vidx=0;
        getApplication()->logMessage(LOG_INFO, "ConvexDecompResult() mHullVcount: %d, "
            "mHullTcount: %d ", result.mHullVcount, result.mHullTcount);
        
        
        while (vidx < result.mHullVcount)
        {
            btVector3 v;
            v.setX(result.mHullVertices[vidx]);
            vidx++;
            v.setY(result.mHullVertices[vidx]);
            vidx++;
            v.setZ(result.mHullVertices[vidx]);
            vidx++;
            chShape->addPoint(v);	
        }
        
        
        m_compound->addChildShape(m_localTransform, chShape);
        */
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

        getApplication()->logMessage(LOG_INFO, "_decomposeTriMesh() subparts=%d", subparts);

        for(int part=0; part < subparts; part++)
        {
            m_triMesh->getLockedReadOnlyVertexIndexBase(&vertexbase, numverts, 
                vtype, vstride, &indexbase, istride, numfaces, itype, part);

            getApplication()->logMessage(LOG_INFO, "getLockedReadOnlyVertexIndexBase "
                "numverts=%d, numfaces=%d" , numverts, numfaces);

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

        btTransform trans;
        trans.setIdentity();
        for (u32 i=0;i<m_convexShapes.size();i++)
        {

            btVector3 centroid = m_convexCentroids[i];
            trans.setOrigin(centroid);
            btConvexHullShape* convexShape = m_convexShapes[i];
            m_compound->addChildShape(trans,convexShape);
        }

        return m_compound;
    }
}

