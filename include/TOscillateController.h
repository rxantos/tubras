//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TOSCILLATECONTROLLER_H_
#define _TOSCILLATECONTROLLER_H_

namespace Tubras
{

    class TOscillateController : public TController
    {
    protected:
        TVector3                m_axis;
        TVector3                m_currentPos;
        float                   m_velocity;
        float                   m_amplitude;

    public:
        TOscillateController(const TString& name, ISceneNode* node, float velocity=1.0f,
            float amplitude=3.0, TVector3 axis=TVector3::UNIT_Y);

        virtual ~TOscillateController();

        virtual void update(float deltaTime);
    };

}

#endif

