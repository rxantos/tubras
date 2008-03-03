//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay() : line3df()
    {
        m_magnitude = 1.f;
        m_endPoint = start + (end * m_magnitude);
    }

    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay(const TVector3& origin, const TVector3& direction, const TReal magnitude)
        : line3df(origin, direction)
    {
        m_magnitude = magnitude;
        m_endPoint  = start + (end * magnitude);
    }

    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay(const line3df& oRay,const TReal magnitude)
        : line3df(oRay.start,oRay.end)
    {
        m_magnitude = magnitude;
        m_endPoint = start + (end * m_magnitude);
    }

    //-----------------------------------------------------------------------
    //                            ~ T R a y 
    //-----------------------------------------------------------------------
    TRay::~TRay()
    {
    }

    //-----------------------------------------------------------------------
    //                              T R a y 
    //-----------------------------------------------------------------------
    TRay::TRay(core::position2d<s32> screenPos, ICameraSceneNode* camera)
    {
        const scene::SViewFrustum* f = camera->getViewFrustum();

        core::vector3df farLeftUp = f->getFarLeftUp();
        core::vector3df lefttoright = f->getFarRightUp() - farLeftUp;
        core::vector3df uptodown = f->getFarLeftDown() - farLeftUp;

        core::rect<s32> viewPort = getApplication()->getRenderer()->getVideoDriver()->getViewPort();
        core::dimension2d<s32> screenSize(viewPort.getWidth(), viewPort.getHeight());

        f32 dx = screenPos.X / (f32)screenSize.Width;
        f32 dy = screenPos.Y / (f32)screenSize.Height;

        if (camera->isOrthogonal())
            start = f->cameraPosition + (lefttoright * (dx-0.5f)) + (uptodown * (dy-0.5f));
        else
            start = f->cameraPosition;

        end = farLeftUp + (lefttoright * dx) + (uptodown * dy);
    }

}

