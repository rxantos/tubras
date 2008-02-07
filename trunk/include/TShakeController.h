//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TSHAKECONTROLLER_H_
#define _TSHAKECONTROLLER_H_

namespace Tubras
{

    class TShakeController : public TIntervalController
    {
    protected:
        float                   m_duration;
        float                   m_magnitude;
        float                   m_easeInOut;
        float                   m_shakeDelta;
        TVector3                m_nodeStartPos;
        TRandom                 m_random;

    public:
        TShakeController(TString name, ISceneNode* node, float duration=3.f,
            float magnitude=1.f, bool easeInOut=false);

        virtual ~TShakeController();

        virtual void start(u32 startTime);
        virtual void stop();

        virtual void update(float deltaTime);
    };

}

#endif

