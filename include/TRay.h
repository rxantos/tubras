//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
        ~TRay();

        TRay(core::position2d<s32> pos, TCameraNode* camera);

        TVector3 getEndPoint() {return m_endPoint;}
        TReal getMagnitude() {return m_magnitude;}
    };
}

#endif

