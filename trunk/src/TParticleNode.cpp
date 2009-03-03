//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                        T P a r t i c l e N o d e
    //-----------------------------------------------------------------------
    TParticleNode::TParticleNode(int maxParticles, 
        ISceneNode* parent) : ISceneNode(parent, 0)
    {
        m_handle = m_pc.GenParticleGroups(1, maxParticles);
        m_pc.CurrentGroup(m_handle);

        _createBuffers();
    }

    //-----------------------------------------------------------------------
    //                       ~ T P a r t i c l e N o d e
    //-----------------------------------------------------------------------
    TParticleNode::~TParticleNode()
    {
        //getApplication()->getRenderEngine()->getSceneManager()->destroyMovableObject(m_group->getName(),"TParticleNode");
    }

    //-----------------------------------------------------------------------
    //                      _ c r e a t e B u f f e r s
    //-----------------------------------------------------------------------
    void TParticleNode::_createBuffers(void)
    {
    }

    //-----------------------------------------------------------------------
    //                          a d d A c t i o n 
    //-----------------------------------------------------------------------
    void TParticleNode::addAction(TParticleAction* action)
    {
        m_actions.push_back(action);
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o r
    //-----------------------------------------------------------------------
    void TParticleNode::setColor(TColor color)
    {
        m_pc.Color(PAPI::pVec(color.getRed()/255.f, color.getGreen()/255.f, 
            color.getBlue()/255.f),color.getAlpha()/255.f);
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o r
    //-----------------------------------------------------------------------
    void TParticleNode::setColor(TParticleDomain colorDomain)
    {
        m_pc.Color(colorDomain.dom());
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o r
    //-----------------------------------------------------------------------
    void TParticleNode::setColor(TParticleDomain colorDomain, 
        TParticleDomain alphaDomain)
    {
        m_pc.Color(colorDomain.dom(),alphaDomain.dom());
    }

    //-----------------------------------------------------------------------
    //                           s e t S i z e 
    //-----------------------------------------------------------------------
    void TParticleNode::setSize(TVector3 size)
    {
        m_pc.Size(PAPI::pVec(size.X,size.Y,size.Z));
    }

    //-----------------------------------------------------------------------
    //                           s e t S i z e 
    //-----------------------------------------------------------------------
    void TParticleNode::setSize(TParticleDomain size)
    {
        m_pc.Size(size.dom());
    }

    //-----------------------------------------------------------------------
    //                           s e t M a s s
    //-----------------------------------------------------------------------
    void TParticleNode::setMass(float mass)
    {
        m_pc.Mass(mass);
    }

    //-----------------------------------------------------------------------
    //                      s e t R o t V e l o c i t y 
    //-----------------------------------------------------------------------
    void TParticleNode::setRotVelocity(TParticleDomain dom)
    {
        m_pc.RotVelocity(dom.dom());
    }

    //-----------------------------------------------------------------------
    //                      s e t S t a r t i n g A g e
    //-----------------------------------------------------------------------
    void TParticleNode::setStartingAge(float age, float sigma)
    {
        m_pc.StartingAge(age,sigma);
    }

    //-----------------------------------------------------------------------
    //                        s e t U p V e c t o r
    //-----------------------------------------------------------------------
    void TParticleNode::setUpVector(TVector3 vec)
    {
        m_pc.UpVec(PAPI::pVec(vec.X,vec.Y,vec.Z));
    }

    //-----------------------------------------------------------------------
    //                        s e t V e l o c i t y
    //-----------------------------------------------------------------------
    void TParticleNode::setVelocity(TVector3 vel)
    {
        m_pc.Velocity(PAPI::pVec(vel.X,vel.Y,vel.Z));
    }

    //-----------------------------------------------------------------------
    //                        s e t V e l o c i t y
    //-----------------------------------------------------------------------
    void TParticleNode::setVelocity(TParticleDomain dom)
    {
        m_pc.Velocity(dom.dom());
    }

    //-----------------------------------------------------------------------
    //                        s e t V e r t e x B 
    //-----------------------------------------------------------------------
    void TParticleNode::setVertexB(TVector3 vec)
    {
        m_pc.VertexB(PAPI::pVec(vec.X,vec.Y,vec.Z));
    }

    //-----------------------------------------------------------------------
    //                        s e t V e r t e x B 
    //-----------------------------------------------------------------------
    void TParticleNode::setVertexB(TParticleDomain dom)
    {
        m_pc.VertexB(dom.dom());
    }

    //-----------------------------------------------------------------------
    //                   s e t V e r t e x B T r a c k s
    //-----------------------------------------------------------------------
    void TParticleNode::setVertexBTracks(bool value)
    {
        m_pc.VertexBTracks(value);
    }

    //-----------------------------------------------------------------------
    //                       s e t T i m e S t e p
    //-----------------------------------------------------------------------
    void TParticleNode::setTimeStep(float dt)
    {
        m_timeStep = dt;
        m_pc.TimeStep(m_timeStep);
    }

    //-----------------------------------------------------------------------
    //                       s e t P o i n t S i z e
    //-----------------------------------------------------------------------
    void TParticleNode::setPointSize(float size)
    {
        // m_mat->getTechnique(0)->getPass(0)->setPointSize(size);
    }

    //-----------------------------------------------------------------------
    //                       s e t M a t e r i a l N a m e
    //-----------------------------------------------------------------------
    void TParticleNode::setMaterialName(TString name)
    {
        //m_group->setMaterialName(name,resourceGroup);
    }

    //-----------------------------------------------------------------------
    //                      s e t S p r i t e I m a g e
    //-----------------------------------------------------------------------
    void TParticleNode::setSpriteImage(TString name, bool alphaBlend)
    {
        //m_group->setSpriteImage(name,resourceGroup,alphaBlend);
    }

    //-----------------------------------------------------------------------
    //                      s e t M a x P a r t i c l e s
    //-----------------------------------------------------------------------
    void TParticleNode::setMaxParticles(size_t value)
    {
        //m_group->setMaxParticles(value);
    }

    //-----------------------------------------------------------------------
    //                   O n R e g i s t e r S c e n e N o d e
    //-----------------------------------------------------------------------
    void TParticleNode::OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();        
    }

    //-----------------------------------------------------------------------
    //                       g e t M a t e r i a l C o u n t
    //-----------------------------------------------------------------------
    u32 TParticleNode::getMaterialCount() const
	{
		return 1;
	}

    //-----------------------------------------------------------------------
    //                          g e t M a t e r i a l 
    //-----------------------------------------------------------------------
    SMaterial& TParticleNode::getMaterial(u32 i)
	{
		return m_material;
	}	

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TParticleNode::render()
    {
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

        /*
		driver->setMaterial(m_material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        driver->draw3DLine(m_start,m_end,m_color);
        */
    }

}
