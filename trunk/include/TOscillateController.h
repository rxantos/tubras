//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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

