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

#ifndef _TPARTICLEDOMAIN_H_
#define _TPARTICLEDOMAIN_H_

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                      T P a r t i c l e D o m a i n
    //-----------------------------------------------------------------------
    class TParticleDomain
    {
    protected:

        PAPI::pDomain*      m_domain;

    public:
        TParticleDomain() : m_domain(0) {};
        inline PAPI::pDomain& dom() {return *m_domain;}
    };

    //-----------------------------------------------------------------------
    //                         T L i n e D o m a i n
    //-----------------------------------------------------------------------
    class TLineDomain : public TParticleDomain
    {
    public:
        TLineDomain(TVector3 start, TVector3 end) : TParticleDomain()
        {
            PAPI::pVec  v0(start.x,start.y,start.z);
            PAPI::pVec  v1(end.x,end.y,end.z);

            m_domain = new PAPI::PDLine(v0,v1);
        }
    };

    //-----------------------------------------------------------------------
    //                         T D i s c D o m a i n
    //-----------------------------------------------------------------------
    class TDiscDomain : public TParticleDomain
    {
    public:
        TDiscDomain(TVector3 center, TVector3 normal, float outerRadius, float innerRadius = 0.0f)
        {
            PAPI::pVec  v0(center.x,center.y,center.z);
            PAPI::pVec  v1(normal.x,normal.y,normal.z);
            m_domain = new PAPI::PDDisc(v0,v1,outerRadius,innerRadius);
        }
    };

    //-----------------------------------------------------------------------
    //                         T P l a n e D o m a i n
    //-----------------------------------------------------------------------
    class TPlaneDomain : public TParticleDomain
    {
    public:
        TPlaneDomain(TVector3 center, TVector3 normal)
        {
            PAPI::pVec  v0(center.x,center.y,center.z);
            PAPI::pVec  v1(normal.x,normal.y,normal.z);
            m_domain = new PAPI::PDPlane(v0,v1);
        }
    };

    //-----------------------------------------------------------------------
    //                      T C y l i n d e r D o m a i n
    //-----------------------------------------------------------------------
    class TCylinderDomain : public TParticleDomain
    {
    public:
        TCylinderDomain(TVector3 e0, TVector3 e1, float outerRadius, float innerRadius = 0.0f)
        {
            PAPI::pVec  v0(e0.x,e0.y,e0.z);
            PAPI::pVec  v1(e1.x,e1.y,e1.z);
            m_domain = new PAPI::PDCylinder(v0,v1,outerRadius,innerRadius);
        }
    };

    //-----------------------------------------------------------------------
    //                        T B o x D o m a i n
    //-----------------------------------------------------------------------
    class TBoxDomain : public TParticleDomain
    {
    public:
        TBoxDomain(TVector3 e0, TVector3 e1)
        {
            PAPI::pVec  v0(e0.x,e0.y,e0.z);
            PAPI::pVec  v1(e1.x,e1.y,e1.z);
            m_domain = new PAPI::PDBox(v0,v1);
        }
    };


}
#endif