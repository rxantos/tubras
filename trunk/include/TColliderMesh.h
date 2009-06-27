//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TCOLLIDERMESH_H_
#define __TCOLLIDERMESH_H_

namespace Tubras
{

    class TColliderMesh : public TColliderShape, public ConvexDecompInterface
    {
    private:
        btTriangleMesh*     m_triMesh;
        btCompoundShape*    m_compound;
        matrix4             m_localTransform;

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
        TColliderMesh(IMesh* mesh, const matrix4& transform, bool isConvex, bool optimize=true);
        virtual ~TColliderMesh();

        virtual void ConvexDebugTri(const float *p1,const float *p2,const float *p3,unsigned int color) {}
        virtual void ConvexDebugOBB(const float *sides, const float *matrix,unsigned int color) {}
        virtual void ConvexDebugPoint(const float *p,float dist,unsigned int color) {}
        virtual void ConvexDebugBound(const float *bmin,const float *bmax,unsigned int color) {}

        virtual void ConvexDecompResult(ConvexResult &result);
    };
}
#endif
