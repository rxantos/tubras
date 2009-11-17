//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TCOLLISIONSHAPES_H_
#define __TCOLLISIONSHAPES_H_

namespace Tubras
{

    class TCollisionShape 
    {
    protected:
        btCollisionShape*       m_shape;
    public:
        TCollisionShape();
        virtual ~TCollisionShape();
        virtual void setShape(btCollisionShape* shape) {m_shape = shape;};
        virtual btCollisionShape* getShape() {return m_shape;};

        void setScale(const TVector3& value);
        void getScale(TVector3& value);

        virtual void calculateLocalInertia(float mass,btVector3& inertia);
    };

    class TBoxShape : public TCollisionShape
    {
    public:
        TBoxShape(TVector3 extents)
        {
            TVector3 hs = extents / 2.f;
            const btVector3 halfExtents(hs.X,hs.Y,hs.Z);
            m_shape = new btBoxShape(halfExtents);
        }

        TBoxShape(ISceneNode* node)
        {
            TAABBox aabb = node->getBoundingBox();
            TVector3 hs = aabb.getHalfSize();
            btVector3 halfExtents(hs.X,hs.Y,hs.Z);
            m_shape = new btBoxShape(halfExtents);
        }
    };

    class TConeShape : public TCollisionShape
    {
    public:
        TConeShape(ISceneNode* node)
        {
            TAABBox aabb = node->getBoundingBox();
            TVector3 hs = aabb.getHalfSize();
            btScalar radius=hs.X;
            btScalar height=hs.Y * 2.f;
            m_shape = new btConeShape(radius, height);
        }
    };

    class TSphereShape : public TCollisionShape
    {
    protected:

    public:
        TSphereShape(TAABBox aabb)
        {
            TVector3 hs = aabb.getHalfSize();
            m_shape = new btSphereShape(hs.Y);
        }
        TSphereShape(ISceneNode* node, f32 radius)
        {
            TAABBox aabb = node->getBoundingBox();
            
            if(radius == 0.f)
                radius = aabb.getExtent().Y;

            m_shape = new btSphereShape(radius/2.f);
        }
    };

    class TCylinderShape : public TCollisionShape
    {
    public:
        TCylinderShape(TVector3 halfExtents)
        {
            btVector3 bvec(halfExtents.X, halfExtents.Y, halfExtents.Z);
            m_shape = new btCylinderShape(bvec);
        }
        TCylinderShape(ISceneNode* node)
        {
            TAABBox aabb = node->getBoundingBox();
            TVector3 hs = aabb.getHalfSize();
            btVector3 halfExtents(hs.X,hs.Y,hs.Z);
            m_shape = new btCylinderShape(halfExtents);
        }
    };

    class TPlanShape : public TCollisionShape
    {    
        btStaticPlaneShape*     m_plane;

    public:
        TPlanShape(TVector3 normal, float constant=0.f)
        {
            btVector3 bvec(normal.X, normal.Y, normal.Z);

            m_shape =
                m_plane = new btStaticPlaneShape(bvec,constant);
            m_plane->setLocalScaling(btVector3(1,1,1));
        }
    };

    class TMeshShape : public TCollisionShape, public ConvexDecompInterface
    {
    private:
        btTriangleMesh*     m_triMesh;
        btCompoundShape*    m_compound;
        matrix4             m_localTransform;
        TVector3            m_localScale;
        TVector3            m_localTranslate;
        TVector3            m_localRotation;

        // for concave decomposition
        TArray<btTriangleMesh*> m_triMeshes;
		TArray<btConvexHullShape*> m_convexShapes;
		TArray<btVector3>   m_convexCentroids;
        int   	            m_baseCount;
  		int		            m_hullCount;

    protected:
        btTriangleMesh* extractTriangles(IMesh* mesh, bool removeDupVertices);
        btCompoundShape* _decomposeTriMesh();

    public:
        TMeshShape(IMesh* mesh, const matrix4& transform, bool isConvex, bool optimize=true);
        virtual ~TMeshShape();

        virtual void ConvexDebugTri(const float *p1,const float *p2,const float *p3,unsigned int color) {}
        virtual void ConvexDebugOBB(const float *sides, const float *matrix,unsigned int color) {}
        virtual void ConvexDebugPoint(const float *p,float dist,unsigned int color) {}
        virtual void ConvexDebugBound(const float *bmin,const float *bmax,unsigned int color) {}

        virtual void ConvexDecompResult(ConvexResult &result);
    };

}


#endif
