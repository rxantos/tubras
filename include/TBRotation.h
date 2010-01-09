//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TBROTATION_H_
#define _TBROTATION_H_

namespace Tubras
{
    class TBRotation : public TBehavior
    {
        friend class TBehaviorFactory;
    private:
        TString             m_target;

        float               m_velocity;
        TVector3            m_axis;
        ISceneNode*         m_node;
        TRotateController*  m_controller;
        u32                 m_behaviorAddedID;

    protected:
        TBRotation() : TBehavior("rotation") {}
        virtual ~TBRotation();

    public:
        int initialize(TEntity* owner, TProperties& properties);
        void update(TEvent& event);
    };
}

#endif
