//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TROTATECONTROLLER_H_
#define _TROTATECONTROLLER_H_

namespace Tubras
{

    class TRotateController : public TController
    {
    protected:
        TVector3                m_axis;
        float                   m_velocity;

    public:
        TRotateController(TString name, ISceneNode* node, float velocity=5.0f,
            TVector3 axis=TVector3::UNIT_Y);

        virtual ~TRotateController();

        virtual void update(float deltaTime);
    };

}

#endif

