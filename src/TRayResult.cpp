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
    //                       T R a y R e s u l t
    //-----------------------------------------------------------------------
    TRayResult::TRayResult(TBTRayCallback& callback) 
    {
        m_hasHit = callback.HasHit();
        if(m_hasHit)
        {
            m_collisionObject = callback.m_collisionObject;
            m_collisionNode = (TDynamicNode*) m_collisionObject->getUserPointer();
            m_closestHitFraction = callback.m_closestHitFraction;
            m_hitNormalWorld = TIBConvert::BulletToIrr(callback.m_hitNormalWorld);
            m_hitPointWorld = TIBConvert::BulletToIrr(callback.m_hitPointWorld);
        }
        else
        {
            m_closestHitFraction = 0.f;
            m_hitNormalWorld = TVector3::ZERO;
            m_hitPointWorld = TVector3::ZERO;
            m_collisionObject = 0;
            m_collisionNode = 0;
        }
    }

    //-----------------------------------------------------------------------
    //                      ~ T R a y R e s u l t
    //-----------------------------------------------------------------------
    TRayResult::~TRayResult()
    {
    }
}