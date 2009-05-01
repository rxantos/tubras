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
    protected:
        btTriangleMesh* extractTriangles(IMesh* mesh);
        btCompoundShape* _decomposeTriMesh();

    public:
        TColliderMesh(IMesh* mesh, bool isConvex, bool convertToConvexHull=false,
            bool concaveDecomposition=true);
        virtual ~TColliderMesh();

        virtual void ConvexDebugTri(const float *p1,const float *p2,const float *p3,unsigned int color) {}
        virtual void ConvexDebugOBB(const float *sides, const float *matrix,unsigned int color) {}
        virtual void ConvexDebugPoint(const float *p,float dist,unsigned int color) {}
        virtual void ConvexDebugBound(const float *bmin,const float *bmax,unsigned int color) {}

        virtual void ConvexDecompResult(ConvexResult &result);
    };
}
#endif
