//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                      T C o l l i s i o n S h a p e
    //-----------------------------------------------------------------------
    TCollisionShape::TCollisionShape() : m_shape(0)
    {
    }

    //-----------------------------------------------------------------------
    //                     ~ T C o l l i s i o n S h a p e
    //-----------------------------------------------------------------------
    TCollisionShape::~TCollisionShape()
    {
        if(m_shape)
            delete m_shape;
    }

    //-----------------------------------------------------------------------
    //                 c a l c u l a t e L o c a l I n e r t i a
    //-----------------------------------------------------------------------
    void TCollisionShape::calculateLocalInertia(float mass,btVector3& inertia)
    {
        m_shape->calculateLocalInertia(mass,inertia);
    }

    //-----------------------------------------------------------------------
    //                           s e t S c a l e
    //-----------------------------------------------------------------------
    void TCollisionShape::setScale(const TVector3& value)
    {
        btVector3 scaling(value.X, value.Y, value.Z);

        m_shape->setLocalScaling(scaling);

    }

    //-----------------------------------------------------------------------
    //                           g e t S c a l e
    //-----------------------------------------------------------------------
    void TCollisionShape::getScale(TVector3& value)
    {
        const btVector3& bscaling = m_shape->getLocalScaling();
        value.X = bscaling.getX();
        value.Y = bscaling.getY();
        value.Z = bscaling.getZ();      
    }


    //-----------------------------------------------------------------------
    //                          T M e s h S h a p e
    //-----------------------------------------------------------------------
    TMeshShape::TMeshShape(IMesh* mesh, const matrix4& transform, bool isConvex) : TCollisionShape(),        
        m_baseCount(0),
        m_hullCount(0)
    {
        TApplication* app = getApplication();
        app->logMessage(LOG_INFO, "TMeshShape isConvex: %d", isConvex);

        u32 vcount=0, tcount=0;
        for(u32 i=0; i<mesh->getMeshBufferCount(); i++)
        {
            tcount += mesh->getMeshBuffer(i)->getIndexCount() / 3;
            vcount += mesh->getMeshBuffer(i)->getVertexCount();
        }
        app->logMessage(LOG_INFO, "   org vert count: %d", vcount);
        app->logMessage(LOG_INFO, "   org  tri count: %d", tcount);

        btQuaternion q(TMath::HALF_PI,0.f,0.f);
        m_localTransform = transform;
        m_localScale = transform.getScale();

        m_triMesh = extractTriangles(mesh, true);        
        app->logMessage(LOG_INFO, "   ext  tri count: %d", m_triMesh->getNumTriangles());

        if(isConvex)
        {
            if(1)
            {   // using Bullet's btShapeHull class - faster, typically produces less verts/tris
                btConvexShape* tmpConvexShape = new btConvexTriangleMeshShape(m_triMesh);
                m_shape = tmpConvexShape;
                btShapeHull* hull = new btShapeHull(tmpConvexShape);
                btScalar margin = tmpConvexShape->getMargin();
                hull->buildHull(margin);
                tmpConvexShape->setUserPointer(hull);

                app->logMessage(LOG_INFO, "  hull vert count: %d", hull->numVertices());
                app->logMessage(LOG_INFO, "  hull  tri count: %d", hull->numTriangles());

                //btConvexHullShape* chShape = new btConvexHullShape((const btScalar *)hull->getVertexPointer(),hull->numVertices());
                btConvexHullShape* chShape = new btConvexHullShape();
                
                const btVector3* vp = hull->getVertexPointer();
                const unsigned int* ip = hull->getIndexPointer();
                for (int i=0;i<hull->numTriangles();i++)
                {
                    chShape->addPoint(vp[ip[i*3]]);     
                    chShape->addPoint(vp[ip[i*3+1]]);     
                    chShape->addPoint(vp[ip[i*3+2]]);     
                }
                
                m_shape = chShape;
                delete hull;
                delete tmpConvexShape;
            }
            else
            {   // using Bullet's hull library directly
                HullResult  result;
                HullLibrary hl;
                HullDesc    desc;

                desc.mMaxFaces = 256;
                desc.mMaxVertices = 256;
                desc.SetHullFlag(QF_TRIANGLES);
                PHY_ScalarType type, indicestype;
                const unsigned char* indexbase;
                int istride,numfaces;

                m_triMesh->getLockedReadOnlyVertexIndexBase((const unsigned char**)&desc.mVertices, (int&)desc.mVcount, type, 
                    (int&)desc.mVertexStride, &indexbase, istride, numfaces, indicestype);

                HullError ret = hl.CreateConvexHull(desc,result);
                if(ret == QE_OK)
                {
                    app->logMessage(LOG_INFO, "  hull vert count: %d", result.mNumOutputVertices);
                    app->logMessage(LOG_INFO, "  hull  tri count: %d", result.mNumFaces);
                    btConvexHullShape* chShape = new btConvexHullShape();

                    for (unsigned int i=0;i<result.mNumFaces;i++)
                    {             
                        chShape->addPoint(result.m_OutputVertices[result.m_Indices[i*3]]);
                        chShape->addPoint(result.m_OutputVertices[result.m_Indices[i*3+1]]);
                        chShape->addPoint(result.m_OutputVertices[result.m_Indices[i*3+2]]);
                    }

                    m_shape = chShape;
                }
                else
                {
                    m_shape = new btBvhTriangleMeshShape(m_triMesh,true,true);                
                }
                hl.ReleaseResult(result);
            }
        }
        else 
        {
            //m_shape = _decomposeTriMesh();
            m_shape = new btBvhTriangleMeshShape(m_triMesh,true,true);
        }
        btVector3 scale(m_localScale.X, m_localScale.Y, m_localScale.Z);
        m_shape->setLocalScaling(scale);
    }

    //-----------------------------------------------------------------------
    //                         ~ T M e s h S h a p e
    //-----------------------------------------------------------------------
    TMeshShape::~TMeshShape()
    {
        if(m_triMesh)
            delete m_triMesh;
    }

    //-----------------------------------------------------------------------
    //                     e x t r a c t T r i a n g l e s
    //-----------------------------------------------------------------------
    btTriangleMesh* TMeshShape::extractTriangles(IMesh* mesh,   
        bool removeDupVertices)
    {
        vector3df p1, p2, p3;

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

                p1 = v1->Pos;
                p2 = v2->Pos;
                p3 = v3->Pos;

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
    void TMeshShape::ConvexDecompResult(ConvexResult &result)
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
    btCompoundShape* TMeshShape::_decomposeTriMesh()
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

