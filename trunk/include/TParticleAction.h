//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
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
    protected:

    public:
        TParticleAction() {};
        virtual ~TParticleAction() {};
        virtual void stepAction(PAPI::ParticleContext_t* pc) = 0;
    };

    //-----------------------------------------------------------------------
    //                       T S o u r c e A c t i o n
    //-----------------------------------------------------------------------
    class TSourceAction : public TParticleAction
    {
    protected:
        float           m_rate;
        TParticleDomain m_dom;
    public:
        TSourceAction(float rate, TParticleDomain& dom) : 
            m_rate(rate),
            m_dom(dom)
        {
        }

        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->Source(m_rate,m_dom.dom());
        }
    };

    //-----------------------------------------------------------------------
    //                        T G r a v i t y A c t i o n
    //-----------------------------------------------------------------------
    class TGravityAction : public TParticleAction
    {
    protected:
        PAPI::pVec          m_dir;

    public:
        TGravityAction(TVector3 direction)
        {
            PAPI::pVec v0(direction.x,direction.y,direction.z);
            m_dir = v0;
        }

        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->Gravity(m_dir);
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


    public:
        TBounceAction(float friction, float resilience, float cutoff, TParticleDomain& dom) :
            m_friction(friction),
            m_resilience(resilience),
            m_cutoff(cutoff),
            m_dom(dom)
        {
        }
        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->Bounce(m_friction,m_resilience,m_cutoff,m_dom.dom());
        }
    };

    //-----------------------------------------------------------------------
    //                         T S i n k A c t i o n
    //-----------------------------------------------------------------------
    class TSinkAction : public TParticleAction
    {
        bool            m_kill;
        TParticleDomain m_dom;

    public:
        TSinkAction(bool killInside,TParticleDomain& dom) :
              m_kill(killInside),
              m_dom(dom)
          {
          }

        void stepAction(PAPI::ParticleContext_t* pc)
        {
            pc->Sink(m_kill,m_dom.dom());
        }
    };


}
#endif