//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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

