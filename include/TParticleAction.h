//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TPARTICLEACTION_H_
#define _TPARTICLEACTION_H_

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                     T P a r t i c l e A c t i o n
    //-----------------------------------------------------------------------
    class TParticleAction
    {
        friend class TParticleNode;
    protected:
        virtual void stepAction(PAPI::ParticleContext_t* pc) = 0;

    public:
        TParticleAction() {};
        virtual ~TParticleAction() {};
    };

    //-----------------------------------------------------------------------
    //                       T S o u r c e A c t i o n
    //-----------------------------------------------------------------------
    class TSourceAction : public TParticleAction
    {
    protected:
        float           m_rate;
        TParticleDomain m_dom;

        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->Source(m_rate,m_dom.dom());
        }

    public:
        TSourceAction(float rate, TParticleDomain& dom) : 
            m_rate(rate),
            m_dom(dom)
        {
        }

        void setRate(float rate) {m_rate = rate;}
    };

    //-----------------------------------------------------------------------
    //                        T G r a v i t y A c t i o n
    //-----------------------------------------------------------------------
    class TGravityAction : public TParticleAction
    {
    protected:
        PAPI::pVec          m_dir;
        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->Gravity(m_dir);
        }

    public:
        TGravityAction(TVector3 direction)
        {
            PAPI::pVec v0(direction.X, direction.Y, direction.Z);
            m_dir = v0;
        }
    };

    //-----------------------------------------------------------------------
    //                        T B o u n c e A c t i o n
    //-----------------------------------------------------------------------
    class TBounceAction : public TParticleAction
    {
        float   m_friction;
        float   m_resilience;
        float   m_cutoff;
        TParticleDomain m_dom;
        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->Bounce(m_friction,m_resilience,m_cutoff,m_dom.dom());
        }

    public:
        TBounceAction(float friction, float resilience, float cutoff, TParticleDomain& dom) :
            m_friction(friction),
            m_resilience(resilience),
            m_cutoff(cutoff),
            m_dom(dom)
        {
        }
    };

    //-----------------------------------------------------------------------
    //                         T S i n k A c t i o n
    //-----------------------------------------------------------------------
    class TSinkAction : public TParticleAction
    {
        bool            m_kill;
        TParticleDomain m_dom;
        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->Sink(m_kill,m_dom.dom());
        }

    public:
        TSinkAction(bool killInside,TParticleDomain& dom) :
              m_kill(killInside),
              m_dom(dom)
          {
          }

    };

    //-----------------------------------------------------------------------
    //                         T S i z e A c t i o n
    //-----------------------------------------------------------------------
    class TSizeAction : public TParticleAction
    {
    protected:
        PAPI::pVec          m_size;
        PAPI::pVec          m_scale;
        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->TargetSize(m_size, m_scale);
        }

    public:
        TSizeAction(TVector3 targetSize, TVector3 scale)
        {
            PAPI::pVec v0(targetSize.X, targetSize.Y, targetSize.Z);
            m_size = v0;
            PAPI::pVec v1(scale.X, scale.Y, scale.Z);
            m_scale = v1;
        }

    };
}
#endif
