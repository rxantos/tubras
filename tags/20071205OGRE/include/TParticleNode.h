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
#ifndef _TPARTICLENODE_H_
#define _TPARTICLENODE_H_

namespace Tubras
{
    class TParticleNode : public TSceneNode
    {
    protected:
        TParticleGroup*         m_group;

    public:
        TParticleNode(TString name, int maxParticles, TSceneNode* parent);
        virtual ~TParticleNode();

        TParticleGroup*	 getGroup(){return m_group;};

        void addAction(TParticleAction* action);
        void setColour(TColour colour);
        void setColour(TParticleDomain colorDomain);
        void setColour(TParticleDomain colorDomain, TParticleDomain alphaDomain);

        void setSize(TVector3 size);
        void setSize(TParticleDomain size);

        void setMass(float mass);
        void setRotVelocity(TParticleDomain dom);
        void setStartingAge(float age, float sigma);
        void setUpVector(TVector3 vec);

        void setVelocity(TVector3 vel);
        void setVelocity(TParticleDomain dom);

        void setVertexB(TVector3 vec);
        void setVertexB(TParticleDomain dom);
        void setVertexBTracks(bool value);
        void setTimeStep(float dt);
        float getTimeStep();
        void setPointSize(float size);
        void setMaterialName(TString name, TString resourceGroup="General");
        void setSpriteImage(TString name, TString resourceGroup="General", bool alphaBlend=true);
        size_t getMaxParticles();
        void setMaxParticles(size_t value);

    };

}

#endif