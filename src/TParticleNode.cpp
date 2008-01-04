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
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                        T P a r t i c l e N o d e
    //-----------------------------------------------------------------------
    TParticleNode::TParticleNode(TString name, int maxParticles, 
        TSceneNode* parent) : TSceneNode(name,parent)
    {
        m_group = getParticleManager()->createParticleGroup(name,maxParticles);
        m_node->attachObject(m_group);
    }

    //-----------------------------------------------------------------------
    //                       ~ T P a r t i c l e N o d e
    //-----------------------------------------------------------------------
    TParticleNode::~TParticleNode()
    {

        getApplication()->getRenderEngine()->getSceneManager()->destroyMovableObject(m_group->getName(),"TParticleNode");
    }

    //-----------------------------------------------------------------------
    //                          a d d A c t i o n 
    //-----------------------------------------------------------------------
    void TParticleNode::addAction(TParticleAction* action)
    {
        m_group->addAction(action);
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o u r
    //-----------------------------------------------------------------------
    void TParticleNode::setColour(TColour colour)
    {
        m_group->setColour(colour);
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o u r
    //-----------------------------------------------------------------------
    void TParticleNode::setColour(TParticleDomain colorDomain)
    {
        m_group->setColour(colorDomain);
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o u r
    //-----------------------------------------------------------------------
    void TParticleNode::setColour(TParticleDomain colorDomain, TParticleDomain alphaDomain)
    {
        m_group->setColour(colorDomain,alphaDomain);
    }

    //-----------------------------------------------------------------------
    //                           s e t S i z e 
    //-----------------------------------------------------------------------
    void TParticleNode::setSize(TVector3 size)
    {
        m_group->setSize(size);
    }

    //-----------------------------------------------------------------------
    //                           s e t S i z e 
    //-----------------------------------------------------------------------
    void TParticleNode::setSize(TParticleDomain size)
    {
        m_group->setSize(size);
    }

    //-----------------------------------------------------------------------
    //                           s e t M a s s
    //-----------------------------------------------------------------------
    void TParticleNode::setMass(float mass)
    {
        m_group->setMass(mass);
    }

    //-----------------------------------------------------------------------
    //                      s e t R o t V e l o c i t y 
    //-----------------------------------------------------------------------
    void TParticleNode::setRotVelocity(TParticleDomain dom)
    {
        m_group->setRotVelocity(dom);
    }

    //-----------------------------------------------------------------------
    //                      s e t S t a r t i n g A g e
    //-----------------------------------------------------------------------
    void TParticleNode::setStartingAge(float age, float sigma)
    {
        m_group->setStartingAge(age,sigma);
    }

    //-----------------------------------------------------------------------
    //                        s e t U p V e c t o r
    //-----------------------------------------------------------------------
    void TParticleNode::setUpVector(TVector3 vec)
    {
        m_group->setUpVector(vec);
    }

    //-----------------------------------------------------------------------
    //                        s e t V e l o c i t y
    //-----------------------------------------------------------------------
    void TParticleNode::setVelocity(TVector3 vel)
    {
        m_group->setVelocity(vel);
    }

    //-----------------------------------------------------------------------
    //                        s e t V e l o c i t y
    //-----------------------------------------------------------------------
    void TParticleNode::setVelocity(TParticleDomain dom)
    {
        m_group->setVelocity(dom);
    }

    //-----------------------------------------------------------------------
    //                        s e t V e r t e x B 
    //-----------------------------------------------------------------------
    void TParticleNode::setVertexB(TVector3 vec)
    {
        m_group->setVertexB(vec);
    }

    //-----------------------------------------------------------------------
    //                        s e t V e r t e x B 
    //-----------------------------------------------------------------------
    void TParticleNode::setVertexB(TParticleDomain dom)
    {
        m_group->setVertexB(dom);
    }

    //-----------------------------------------------------------------------
    //                   s e t V e r t e x B T r a c k s
    //-----------------------------------------------------------------------
    void TParticleNode::setVertexBTracks(bool value)
    {
        m_group->setVertexBTracks(value);
    }

    //-----------------------------------------------------------------------
    //                       s e t T i m e S t e p
    //-----------------------------------------------------------------------
    void TParticleNode::setTimeStep(float dt)
    {
        m_group->setTimeStep(dt);
    }

    //-----------------------------------------------------------------------
    //                       g e t T i m e S t e p
    //-----------------------------------------------------------------------
    float TParticleNode::getTimeStep()
    {
        return m_group->getTimeStep();
    }

    //-----------------------------------------------------------------------
    //                       s e t P o i n t S i z e
    //-----------------------------------------------------------------------
    void TParticleNode::setPointSize(float size)
    {
        m_group->setPointSize(size);
    }

    //-----------------------------------------------------------------------
    //                       s e t M a t e r i a l N a m e
    //-----------------------------------------------------------------------
    void TParticleNode::setMaterialName(TString name, TString resourceGroup)
    {
        m_group->setMaterialName(name,resourceGroup);
    }

    //-----------------------------------------------------------------------
    //                      s e t S p r i t e I m a g e
    //-----------------------------------------------------------------------
    void TParticleNode::setSpriteImage(TString name, TString resourceGroup, bool alphaBlend)
    {
        m_group->setSpriteImage(name,resourceGroup,alphaBlend);
    }

    //-----------------------------------------------------------------------
    //                      g e t M a x P a r t i c l e s
    //-----------------------------------------------------------------------
    size_t TParticleNode::getMaxParticles()
    {
        return m_group->getMaxParticles();
    }

    //-----------------------------------------------------------------------
    //                      s e t M a x P a r t i c l e s
    //-----------------------------------------------------------------------
    void TParticleNode::setMaxParticles(size_t value)
    {
        m_group->setMaxParticles(value);
    }


}