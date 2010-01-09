//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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

