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
#ifndef __TCOLLIDERMESH_H_
#define __TCOLLIDERMESH_H_

namespace Tubras
{

    class TColliderMesh : public TColliderShape
    {
    private:
        size_t          m_cvi,m_cti;
        size_t          m_vertexCount;
        size_t          m_indexCount;
        size_t          m_triCount;
        size_t          m_entityCount;
        size_t          m_submeshCount;
        btTriangleMesh* m_triMesh;
        size_t*         m_indices;
        float*          m_vertices;

    private:
        void addTri(TVector3* vertices);

    protected:
        size_t extractTriangles(IMeshSceneNode* snode);

    public:
        TColliderMesh(IMeshSceneNode* snode,bool optimize=false);
        virtual ~TColliderMesh();

    };

}


#endif
