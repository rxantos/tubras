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
    using namespace PAPI;
    using namespace Ogre;

    Ogre::String TParticleGroup::m_movableType = "TParticleGroup";

    //-----------------------------------------------------------------------
    //                       T P a r t i c l e G r o u p 
    //-----------------------------------------------------------------------
    TParticleGroup::TParticleGroup(size_t maxParticles)
    {
        m_pointRendering = true;
        m_handle = m_pc.GenParticleGroups(1, maxParticles);
        m_pc.CurrentGroup(m_handle);

        // Set up the state. hardcoded for now...
        m_pc.Velocity(PDCylinder(pVec(0.0f, 0.25f, -0.01f), pVec(0.0f, 0.27f, -0.01f), 0.021f, 0.019f));
        m_pc.Color(PDLine(pVec(0.8f, 0.9f, 1.0f), pVec(0.0f, 0.0f, 1.0f)));

        //
        // add some hardcode actions for testing
        //

        /*
        TParticleAction* a = new TSourceAction(50, TLineDomain(TVector3(0,0,0),TVector3(0,0.4f,0)));
        addAction(a);

        a = new TGravityAction(TVector3(0,-0.01f,0));
        addAction(a);

        a = new TBounceAction(-0.05f, 0.35, 0, TDiscDomain(TVector3(0,0,0),TVector3(0,1,0),5));
        addAction(a);

        a = new TSinkAction(false,TPlaneDomain(TVector3(0,-3,0), TVector3(0,1,0)));
        addAction(a);
        */

        m_bb.setInfinite();
        m_mat = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting");


        //m_mat = Ogre::MaterialManager::getSingleton().load("ready.png","General");
        //m_mat->getTechnique(0)->getPass(0)->setPointSpritesEnabled(true);

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

        // Vertex declaration
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

    void TParticleGroup::getWorldTransforms(Ogre::Matrix4* xform) const
    {
        *xform = _getParentNodeFullTransform();
    }

    const Ogre::Quaternion& TParticleGroup::getWorldOrientation(void) const
    {
        return getParentNode()->_getDerivedOrientation();
    }

    const Ogre::Vector3& TParticleGroup::getWorldPosition(void) const
    {
        return getParentNode()->_getDerivedPosition();
    }

    const Ogre::LightList& TParticleGroup::getLights(void) const
    {
        return queryLights();
    }

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
    //                          a d d A c t i o n 
    //-----------------------------------------------------------------------
    void TParticleGroup::addAction(TParticleAction *action)
    {
        m_actions.push_back(action);
    }

    //-----------------------------------------------------------------------
    //                   _ u p d a t e R e n d e r Q u e u e
    //-----------------------------------------------------------------------
    void TParticleGroup::_updateRenderQueue(Ogre::RenderQueue* queue)
    {
        //
        // todo: optimize...
        //
        float *ptr;
        size_t flstride, pos3Ofs, posB3Ofs, size3Ofs, vel3Ofs, velB3Ofs;
        size_t color3Ofs, alpha1Ofs, age1Ofs, up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs;

        //
        // provides pointer/offsets to api's internal buffers
        //
        size_t pcnt = m_pc.GetMaxParticles();

        if (pcnt) // optimal lock
		{
            m_pc.GetParticlePointer(ptr, flstride, pos3Ofs, posB3Ofs,
                size3Ofs, vel3Ofs, velB3Ofs, color3Ofs, alpha1Ofs, age1Ofs,
                up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs);

			float* mLockPtr = static_cast<float*>(
				m_hvBuf->lock(0, m_pc.GetMaxParticles() * m_hvBuf->getVertexSize(), 
				HardwareBuffer::HBL_DISCARD) );

            float *vp = ptr + pos3Ofs;
            float *vc = ptr + color3Ofs;
            for(size_t i=0;i<pcnt;i++)
            {
                //
                // position
                //
                *mLockPtr++ = *vp++;
                *mLockPtr++ = *vp++;
                *mLockPtr++ = *vp++;


                float r,g,b,a;
                r = *vc++;
                g = *vc++;
                b = *vc++;
                a = *vc++;

                RGBA colour;
                Root::getSingleton().convertColourValue(Ogre::ColourValue(r,g,b,a), &colour);

                RGBA* pdw = (RGBA*) mLockPtr++;

                *pdw = colour;
                //*pdw = *vc;
                vp = ptr+(flstride*i);
                vc = vp+color3Ofs;
            }
            m_hvBuf->unlock();

            queue->addRenderable(this);
		}

        return;
    }

}