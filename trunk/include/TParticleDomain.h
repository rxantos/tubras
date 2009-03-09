//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
        ::PAPI::pDomain*      m_domain;

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
            PAPI::pVec  v0(start.X,start.Y,start.Z);
            PAPI::pVec  v1(end.X,end.Y,end.Z);

            m_domain = new PAPI::PDLine(v0,v1);
        }
    };

    //-----------------------------------------------------------------------
    //                         T D i s c D o m a i n
    //-----------------------------------------------------------------------
    class TDiscDomain : public TParticleDomain
    {
    public:
        TDiscDomain(TVector3 center, TVector3 normal, float outerRadius, float innerRadius = 0.0f) : TParticleDomain()
        {
            PAPI::pVec  v0(center.X,center.Y,center.Z);
            PAPI::pVec  v1(normal.X,normal.Y,normal.Z);
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
            PAPI::pVec  v0(center.X,center.Y,center.Z);
            PAPI::pVec  v1(normal.X,normal.Y,normal.Z);
            m_domain = new PAPI::PDPlane(v0,v1);
        }
    };

    //-----------------------------------------------------------------------
    //                      T C y l i n d e r D o m a i n
    //-----------------------------------------------------------------------
    class TCylinderDomain : public TParticleDomain
    {
    public:
        TCylinderDomain(TVector3 e0, TVector3 e1, float outerRadius, float innerRadius = 0.0f) : TParticleDomain()
        {
            PAPI::pVec  v0(e0.X,e0.Y,e0.Z);
            PAPI::pVec  v1(e1.X,e1.Y,e1.Z);
            m_domain = new PAPI::PDCylinder(v0,v1,outerRadius,innerRadius);
        }
    };

    //-----------------------------------------------------------------------
    //                        T B o x D o m a i n
    //-----------------------------------------------------------------------
    class TBoxDomain : public TParticleDomain
    {
    public:
        TBoxDomain(TVector3 e0, TVector3 e1) : TParticleDomain()
        {
            PAPI::pVec  v0(e0.X,e0.Y,e0.Z);
            PAPI::pVec  v1(e1.X,e1.Y,e1.Z);
            m_domain = new PAPI::PDBox(v0,v1);
        }
    };


}
#endif
