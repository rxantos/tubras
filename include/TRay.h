//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TRAY_H_
#define _TRAY_H_

namespace Tubras
{
    class TRay : public line3df
    {
        TReal               m_magnitude;

        TVector3            m_endPoint;

    public:
        TRay();
        TRay(const TVector3& origin, const TVector3& direction, const TReal magnitude=1.f);
        TRay(const line3d<f32>& oRay,const TReal magnitude=1.f);
        TRay(core::position2d<s32> pos, ICameraSceneNode* camera);

        ~TRay();

        TVector3 getEndPoint() {return m_endPoint;}
        TReal getMagnitude() {return m_magnitude;}
    };
}

#endif

