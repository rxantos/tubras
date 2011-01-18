//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
            TVector3 axis=TVector3_UNIT_Y);

        virtual ~TRotateController();

        virtual void update(float deltaTime);
    };

}

#endif

