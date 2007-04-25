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
#include "particle.h"


namespace Tubras
{
    using namespace PAPI;
    using namespace Ogre;

    struct _BUFFER
    {
        float       x;
        float       y;
        float       z;
        ARGB        colour;
    };

    Ogre::String TParticleGroup::m_movableType = "TParticleGroup";

    //-----------------------------------------------------------------------
    //                       T P a r t i c l e G r o u p 
    //-----------------------------------------------------------------------
    TParticleGroup::TParticleGroup(size_t maxParticles)
    {
        m_pointRendering = true;
        m_handle = m_pc.GenParticleGroups(1, maxParticles);
        m_pc.CurrentGroup(m_handle);

        //
        // research if particle2 api provides this...
        //
        m_bb.setInfinite();

        m_timeStep = 1.f;

        //
        // default sprite material
        //
        m_mat = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting");

        _createBuffers();
    }

    //-----------------------------------------------------------------------
    //                       T P a r t i c l e G r o u p 
    //-----------------------------------------------------------------------
    TParticleGroup::~TParticleGroup()
    {
    }

    //-----------------------------------------------------------------------
    //                       _ c r e a t e B u f f e r s
    //-----------------------------------------------------------------------
    void TParticleGroup::_createBuffers(void)
    {
        m_vertexData = new Ogre::VertexData();
        m_vertexData->vertexCount = m_pc.GetMaxParticles();

        m_vertexData->vertexStart = 0;

        //
        // Vertex declaration
        //
        VertexDeclaration* decl = m_vertexData->vertexDeclaration;
        VertexBufferBinding* binding = m_vertexData->vertexBufferBinding;

        size_t offset = 0;
        decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
        offset += VertexElement::getTypeSize(VET_FLOAT3);
        decl->addElement(0, offset, VET_COLOUR, VES_DIFFUSE);
        offset += VertexElement::getTypeSize(VET_COLOUR);

        m_hvBuf =
            Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
            decl->getVertexSize(0),
            m_vertexData->vertexCount,
            HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
        // bind position and diffuses
        binding->setBinding(0, m_hvBuf);
    }

    //-----------------------------------------------------------------------
    //                       s e t M a x P a r t i c l e s
    //-----------------------------------------------------------------------
    void TParticleGroup::setMaxParticles(size_t value)
    {
        m_pc.SetMaxParticles(value);
        m_vertexData->vertexCount = value;

        m_hvBuf =
            Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
            m_vertexData->vertexDeclaration->getVertexSize(0),
            m_vertexData->vertexCount,
            HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
        // bind position and diffuses
        m_vertexData->vertexBufferBinding->setBinding(0, m_hvBuf);
    }

    //-----------------------------------------------------------------------
    //                       g e t M o v a b l e T y p e
    //-----------------------------------------------------------------------
    const Ogre::String& TParticleGroup::getMovableType(void) const
    {
        return m_movableType;
    }

    //-----------------------------------------------------------------------
    //                       g e t B o u n d i n g B o x
    //-----------------------------------------------------------------------
    const Ogre::AxisAlignedBox& TParticleGroup::getBoundingBox(void) const
    {
        return m_bb;
    }

    //-----------------------------------------------------------------------
    //                    g e t B o u n d i n g R a d i u s
    //-----------------------------------------------------------------------
    Ogre::Real TParticleGroup::getBoundingRadius(void) const
    {
        return 1.f;
    }

    //-----------------------------------------------------------------------
    //                          g e t M a t e r i a l
    //-----------------------------------------------------------------------
    const Ogre::MaterialPtr& TParticleGroup::getMaterial(void) const
    {
        return m_mat;
    }

    //-----------------------------------------------------------------------
    //                       s e t M a t e r i a l N a m e
    //-----------------------------------------------------------------------
    void TParticleGroup::setMaterialName(TString name, TString resourceGroup)
    {
        m_mat = MaterialManager::getSingleton().load(name,resourceGroup);
    }

    //-----------------------------------------------------------------------
    //                       s e t S p r i t e I m a g e
    //-----------------------------------------------------------------------
    void TParticleGroup::setSpriteImage(TString name, TString resourceGroup, bool alphaBlend)
    {
        m_mat = Ogre::MaterialManager::getSingleton().load(name,resourceGroup);
        m_mat->getTechnique(0)->getPass(0)->setPointSpritesEnabled(true);
        m_mat->getTechnique(0)->getPass(0)->setPointAttenuation(false);
        m_mat->getTechnique(0)->getPass(0)->createTextureUnitState(name);
        m_mat->getTechnique(0)->getPass(0)->setLightingEnabled(false); 
        if(alphaBlend)
            m_mat->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        m_mat->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);               
    }

    //-----------------------------------------------------------------------
    //                    g e t R e n d e r O p e r a t i o n
    //-----------------------------------------------------------------------
    void TParticleGroup::getRenderOperation(Ogre::RenderOperation& op)
    {

        op.vertexData = m_vertexData;
        op.vertexData->vertexStart = 0;

        if (m_pointRendering)
        {
            op.operationType = Ogre::RenderOperation::OT_POINT_LIST;
            op.useIndexes = false;
            op.indexData = 0;
            op.vertexData->vertexCount = m_pc.GetGroupCount();
        }
        else
        {
            /*
            op.operationType = RenderOperation::OT_TRIANGLE_LIST;
            op.useIndexes = true;

            op.vertexData->vertexCount = mNumVisibleBillboards * 4;

            op.indexData = mIndexData;
            op.indexData->indexCount = mNumVisibleBillboards * 6;
            op.indexData->indexStart = 0;
            */
        }

    }

    //-----------------------------------------------------------------------
    //                     g e t W o r l d T r a n s f o r m s
    //-----------------------------------------------------------------------
    void TParticleGroup::getWorldTransforms(Ogre::Matrix4* xform) const
    {
        *xform = _getParentNodeFullTransform();
    }

    //-----------------------------------------------------------------------
    //                  g e t W o r l d O r i e n t a t i o n
    //-----------------------------------------------------------------------
    const Ogre::Quaternion& TParticleGroup::getWorldOrientation(void) const
    {
        return getParentNode()->_getDerivedOrientation();
    }

    //-----------------------------------------------------------------------
    //                      g e t W o r l d P o s i t i o n
    //-----------------------------------------------------------------------
    const Ogre::Vector3& TParticleGroup::getWorldPosition(void) const
    {
        return getParentNode()->_getDerivedPosition();
    }

    //-----------------------------------------------------------------------
    //                           g e t L i g h t s 
    //-----------------------------------------------------------------------
    const Ogre::LightList& TParticleGroup::getLights(void) const
    {
        return queryLights();
    }

    //-----------------------------------------------------------------------
    //                       g e t S q u a r e d D e p t h
    //-----------------------------------------------------------------------
    Ogre::Real TParticleGroup::getSquaredViewDepth(const Ogre::Camera* cam) const
    {
        return getParentNode()->getSquaredViewDepth(cam);
    }

    //-----------------------------------------------------------------------
    //                              s t e p
    //-----------------------------------------------------------------------
    void TParticleGroup::step()
    {
        TActionsIterator ai = m_actions.begin();
        while(ai != m_actions.end())
        {
            (*ai)->stepAction(&m_pc);
            ++ai;
        }

        // Move particles to their new positions.
        m_pc.Move(true, false);
    }

    //-----------------------------------------------------------------------
    //                         s e t P o i n t S i z e
    //-----------------------------------------------------------------------
    void TParticleGroup::setPointSize(float size)
    {
        m_mat->getTechnique(0)->getPass(0)->setPointSize(size);
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o u r
    //-----------------------------------------------------------------------
    void TParticleGroup::setColour(TColour colour)
    {
        m_pc.Color(PAPI::pVec(colour.r,colour.g,colour.b),colour.a);
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o u r
    //-----------------------------------------------------------------------
    void TParticleGroup::setColour(TParticleDomain colorDomain)
    {
        m_pc.Color(colorDomain.dom());
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o u r
    //-----------------------------------------------------------------------
    void TParticleGroup::setColour(TParticleDomain colorDomain, TParticleDomain alphaDomain)
    {
        m_pc.Color(colorDomain.dom(),alphaDomain.dom());
    }

    //-----------------------------------------------------------------------
    //                           s e t S i z e 
    //-----------------------------------------------------------------------
    void TParticleGroup::setSize(TVector3 size)
    {
        m_pc.Size(PAPI::pVec(size.x,size.y,size.z));
    }

    //-----------------------------------------------------------------------
    //                           s e t S i z e 
    //-----------------------------------------------------------------------
    void TParticleGroup::setSize(TParticleDomain size)
    {
        m_pc.Size(size.dom());
    }

    //-----------------------------------------------------------------------
    //                           s e t M a s s
    //-----------------------------------------------------------------------
    void TParticleGroup::setMass(float mass)
    {
        m_pc.Mass(mass);
    }

    //-----------------------------------------------------------------------
    //                      s e t R o t V e l o c i t y 
    //-----------------------------------------------------------------------
    void TParticleGroup::setRotVelocity(TParticleDomain dom)
    {
        m_pc.RotVelocity(dom.dom());
    }

    //-----------------------------------------------------------------------
    //                      s e t S t a r t i n g A g e
    //-----------------------------------------------------------------------
    void TParticleGroup::setStartingAge(float age, float sigma)
    {
        m_pc.StartingAge(age,sigma);
    }

    //-----------------------------------------------------------------------
    //                        s e t U p V e c t o r
    //-----------------------------------------------------------------------
    void TParticleGroup::setUpVector(TVector3 vec)
    {
        m_pc.UpVec(PAPI::pVec(vec.x,vec.y,vec.z));
    }

    //-----------------------------------------------------------------------
    //                        s e t V e l o c i t y
    //-----------------------------------------------------------------------
    void TParticleGroup::setVelocity(TVector3 vel)
    {
        m_pc.Velocity(PAPI::pVec(vel.x,vel.y,vel.z));
    }

    //-----------------------------------------------------------------------
    //                        s e t V e l o c i t y
    //-----------------------------------------------------------------------
    void TParticleGroup::setVelocity(TParticleDomain dom)
    {
        m_pc.Velocity(dom.dom());
    }

    //-----------------------------------------------------------------------
    //                        s e t V e r t e x B 
    //-----------------------------------------------------------------------
    void TParticleGroup::setVertexB(TVector3 vec)
    {
        m_pc.VertexB(PAPI::pVec(vec.x,vec.y,vec.z));
    }

    //-----------------------------------------------------------------------
    //                        s e t V e r t e x B 
    //-----------------------------------------------------------------------
    void TParticleGroup::setVertexB(TParticleDomain dom)
    {
        m_pc.VertexB(dom.dom());
    }

    //-----------------------------------------------------------------------
    //                   s e t V e r t e x B T r a c k s
    //-----------------------------------------------------------------------
    void TParticleGroup::setVertexBTracks(bool value)
    {
        m_pc.VertexBTracks(value);
    }

    //-----------------------------------------------------------------------
    //                          a d d A c t i o n 
    //-----------------------------------------------------------------------
    void TParticleGroup::addAction(TParticleAction *action)
    {
        m_actions.push_back(action);
    }

    //-----------------------------------------------------------------------
    //                        s e t T i m e S t e p
    //-----------------------------------------------------------------------
    void TParticleGroup::setTimeStep(float dt)
    {
        m_timeStep = dt;
        m_pc.TimeStep(m_timeStep);
    }

    //-----------------------------------------------------------------------
    //                   _ u p d a t e R e n d e r Q u e u e
    //-----------------------------------------------------------------------
    void TParticleGroup::_updateRenderQueue(Ogre::RenderQueue* queue)
    {
        size_t flstride, pos3Ofs, posB3Ofs, size3Ofs, vel3Ofs, velB3Ofs;
        size_t color3Ofs, alpha1Ofs, age1Ofs, up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs;

        //
        // provides pointer/offsets to api's internal buffers
        //
        size_t pcnt = m_pc.GetMaxParticles();
        Particle_t *p0;
        struct _BUFFER* bp;
        Ogre::Root& root=Ogre::Root::getSingleton();
        Ogre::RenderSystem* renderSys = root.getRenderSystem();

        if (pcnt) 
		{
            
            m_pc.GetParticlePointer((float*&)p0, flstride, pos3Ofs, posB3Ofs,
                size3Ofs, vel3Ofs, velB3Ofs, color3Ofs, alpha1Ofs, age1Ofs,
                up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs);

			bp = static_cast<struct _BUFFER*>(
				m_hvBuf->lock(0, m_pc.GetMaxParticles() * m_hvBuf->getVertexSize(), 
				HardwareBuffer::HBL_DISCARD) );

            for(size_t i=0;i<pcnt;i++)
            {
                bp->x = p0->pos.x();
                bp->y = p0->pos.y();
                bp->z = p0->pos.z();

                TColour c(p0->color.x(),p0->color.y(),p0->color.z(),p0->alpha);
                renderSys->convertColourValue(c, &bp->colour);          

                ++p0;
                ++bp;
            }
            m_hvBuf->unlock();
            queue->addRenderable(this);
		}

        return;
    }

}