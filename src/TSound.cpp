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
    //                            T S o u n d
    //-----------------------------------------------------------------------
    TSound::TSound() 
    {
        m_node = 0;
    }

    //-----------------------------------------------------------------------
    //                           ~T S o u n d
    //-----------------------------------------------------------------------
    TSound::~TSound() 
    {
    }

    //-----------------------------------------------------------------------
    //                     s e t 3 D A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TSound::set3DAttributes(float px, float py, float pz, 
        float vx, float vy, float vz) 
    {
    }

    //-----------------------------------------------------------------------
    //                     g e t 3 D A t t r i b u t e s
    //-----------------------------------------------------------------------
    void TSound::get3DAttributes(float *px, float *py, float *pz, 
        float *vx, float *vy, float *vz) 
    {
    }

    //-----------------------------------------------------------------------
    //                    s e t 3 D M i n D i s t a n c e
    //-----------------------------------------------------------------------
    void TSound::set3DMinDistance(float dist) 
    {
    }

    //-----------------------------------------------------------------------
    //                    g e t 3 D M i n D i s t a n c e
    //-----------------------------------------------------------------------
    float TSound::get3DMinDistance() const 
    {
        return 0.0f;
    }

    //-----------------------------------------------------------------------
    //                    s e t 3 D M a x D i s t a n c e
    //-----------------------------------------------------------------------
    void TSound::set3DMaxDistance(float dist) 
    {
        // Intentionally blank.
    }

    //-----------------------------------------------------------------------
    //                    g e t 3 D M a x D i s t a n c e
    //-----------------------------------------------------------------------
    float TSound::get3DMaxDistance() const 
    {
        // Intentionally blank.
        return 0.0f;
    }

}