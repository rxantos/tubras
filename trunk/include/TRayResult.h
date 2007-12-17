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
#ifndef __TRAYRESULT_H_
#define __TRAYRESULT_H_

namespace Tubras
{
    typedef btCollisionWorld::ClosestRayResultCallback TBTRayCallback;

    class TRayResult 
    {
        friend class TDynamicWorld;

    protected:
        bool                m_hasHit;
        TReal               m_closestHitFraction;
        btCollisionObject*  m_collisionObject;
        TDynamicNode*       m_collisionNode;
        TVector3            m_hitNormalWorld;
        TVector3            m_hitPointWorld;
        TRayResult(TBTRayCallback& callback);

    public:
        virtual ~TRayResult();

        bool hasHit() {return m_hasHit;}
        TDynamicNode*       getCollisionNode() {return m_collisionNode;}
        btCollisionObject*  getCollisionObject() {return m_collisionObject;}
        TVector3 getHitNormalWorld() {return m_hitNormalWorld;}
        TVector3 getHitPointWorld() {return m_hitPointWorld;}
    };

}

#endif
