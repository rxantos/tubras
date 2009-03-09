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
    TParticleNode::TParticleNode(ISceneNode* parent,  
        int maxParticles, TParticlesPrimitive primitive) : ISceneNode(parent, 0),
        m_maxParticles(maxParticles),
        m_buffer(0),
        m_primitive(primitive)
    {
        _updateBuffer();
    }

    //-----------------------------------------------------------------------
    //                       ~ T P a r t i c l e N o d e
    //-----------------------------------------------------------------------
    TParticleNode::~TParticleNode()
    {
        if(m_buffer)
            m_buffer->drop();
    }

    //-----------------------------------------------------------------------
    //                      _ u p d a t e B u f f e r
    //-----------------------------------------------------------------------
    void TParticleNode::_updateBuffer(void)
    {
        int verticesPerParticle=1;
        int vertexCount;
        u32 oldSize=0;

        if(!m_buffer)
            m_buffer = new CDynamicMeshBuffer(EVT_STANDARD, EIT_16BIT);
        else
            oldSize = m_buffer->getVertexBuffer().size();
       
        m_handle = m_pc.GenParticleGroups(1, m_maxParticles);
        m_pc.CurrentGroup(m_handle);

        if(m_primitive == PP_BILLBOARD)
        {
            verticesPerParticle = 6;
        }

        vertexCount = verticesPerParticle * m_maxParticles;

        m_buffer->getVertexBuffer().reallocate(vertexCount);

        if(vertexCount > 65535)
        {
            m_buffer->setIndexBuffer(new CIndexBuffer(EIT_32BIT));
        }
        m_buffer->getIndexBuffer().reallocate(vertexCount);

        if(m_primitive == PP_BILLBOARD)
        {
            IVertexBuffer& Vertices = m_buffer->getVertexBuffer();
            // initialize vertices
            for (u32 i=oldSize; i<Vertices.size(); i+=4)
            {
                Vertices[0+i].TCoords.set(0.0f, 0.0f);
                Vertices[1+i].TCoords.set(0.0f, 1.0f);
                Vertices[2+i].TCoords.set(1.0f, 1.0f);
                Vertices[3+i].TCoords.set(1.0f, 0.0f);
            }


            // initialize indices
            u32 oldIdxSize = m_buffer->getIndexCount();
            u32 oldvertices = oldSize;

            IIndexBuffer& Indices = m_buffer->getIndexBuffer();
            
            Indices.set_used(m_maxParticles * 6);

            u16*    pi16 = (u16*) Indices.pointer();
            u32*    pi32 = (u32*) Indices.pointer();
            E_INDEX_TYPE etype = Indices.getType();

            for (u32 i=oldIdxSize; Indices.size(); i+=6)
            {
                if(etype == EIT_16BIT)
                {
                    pi16[0+i] = 0+oldvertices;
                    pi16[1+i] = 2+oldvertices;
                    pi16[2+i] = 1+oldvertices;
                    pi16[3+i] = 0+oldvertices;
                    pi16[4+i] = 3+oldvertices;
                    pi16[5+i] = 2+oldvertices;
                }
                else 
                {
                    pi32[0+i] = 0+oldvertices;
                    pi32[1+i] = 2+oldvertices;
                    pi32[2+i] = 1+oldvertices;
                    pi32[3+i] = 0+oldvertices;
                    pi32[4+i] = 3+oldvertices;
                    pi32[5+i] = 2+oldvertices;
                }
                oldvertices += 4;
            }
        }
        else
        {
            // initialize indices
            u32 oldIdxSize = m_buffer->getIndexCount();
            IIndexBuffer& Indices = m_buffer->getIndexBuffer();            
            Indices.set_used(m_maxParticles);
            u16*    pi16 = (u16*) Indices.pointer();
            u32*    pi32 = (u32*) Indices.pointer();
            E_INDEX_TYPE etype = Indices.getType();

            for (u32 i=oldIdxSize; Indices.size(); ++i)
            {
                if(etype == EIT_16BIT)
                {
                    pi16[i] = i;
                }
                else 
                {
                    pi32[i] = i;
                }
            }
        }
        
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
        ICameraSceneNode* camera = SceneManager->getActiveCamera();

        if (!camera || !driver)
            return;

        const core::matrix4 &m = camera->getViewFrustum()->getTransform( video::ETS_VIEW );

        const core::vector3df view ( -m[2], -m[6] , -m[10] );

        // update particle vertex data

        size_t flstride, pos3Ofs, posB3Ofs, size3Ofs, vel3Ofs, velB3Ofs;
        size_t color3Ofs, alpha1Ofs, age1Ofs, up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs;

        //
        // provides pointer/offsets to api's internal buffers
        //
        size_t pcnt = m_pc.GetMaxParticles();
        if(!pcnt)
            return;

        float *p0;
        m_pc.GetParticlePointer((float*&)p0, flstride, pos3Ofs, posB3Ofs,
            size3Ofs, vel3Ofs, velB3Ofs, color3Ofs, alpha1Ofs, age1Ofs,
            up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs);


        s32 idx = 0;
        IVertexBuffer& Vertices = m_buffer->getVertexBuffer();

        if(m_primitive == PP_BILLBOARD)
        {
            for (u32 i=0; i<pcnt; ++i)
            {

                const vector3df pos (p0[pos3Ofs+i], p0[pos3Ofs+i+1], p0[pos3Ofs+i+2]);
                const SColor color((u32)(p0[alpha1Ofs+i]*255.f), 
                    (u32)(p0[color3Ofs+i]*255.f), 
                    (u32)(p0[color3Ofs+i+1]*255.f), 
                    (u32)(p0[color3Ofs+i+2]*255.f));

                f32 f;

                f = 0.5f * p0[size3Ofs+i];
                const core::vector3df horizontal ( m[0] * f, m[4] * f, m[8] * f );

                f = -0.5f * p0[size3Ofs+i+1];
                const core::vector3df vertical ( m[1] * f, m[5] * f, m[9] * f );
                Vertices[0+idx].Pos = pos + horizontal + vertical;
                Vertices[0+idx].Color = color;
                Vertices[0+idx].Normal = view;

                Vertices[1+idx].Pos = pos + horizontal - vertical;
                Vertices[1+idx].Color = color;
                Vertices[1+idx].Normal = view;

                Vertices[2+idx].Pos = pos - horizontal - vertical;
                Vertices[2+idx].Color = color;
                Vertices[2+idx].Normal = view;

                Vertices[3+idx].Pos = pos - horizontal + vertical;
                Vertices[3+idx].Color = color;
                Vertices[3+idx].Normal = view;

                idx +=4;
            }
        }
        else
        {
            for (u32 i=0; i<pcnt; ++i)
            {

                const vector3df pos (p0[pos3Ofs+i], p0[pos3Ofs+i+1], p0[pos3Ofs+i+2]);
                const SColor color((u32)(p0[alpha1Ofs+i]*255.f), 
                    (u32)(p0[color3Ofs+i]*255.f), 
                    (u32)(p0[color3Ofs+i+1]*255.f), 
                    (u32)(p0[color3Ofs+i+2]*255.f));

                Vertices[i].Pos = pos;
                Vertices[i].Color = color;
            }
        }

        // render all
        core::matrix4 mat;
        mat.setTranslation(AbsoluteTransformation.getTranslation());
        driver->setTransform(video::ETS_WORLD, mat);

        driver->setMaterial(m_buffer->Material);

        if(m_primitive == PP_BILLBOARD)
        {
            driver->drawVertexPrimitiveList(m_buffer->getVertices(), pcnt*4,
                m_buffer->getIndices(), pcnt*2, video::EVT_STANDARD, EPT_TRIANGLES,
                m_buffer->getIndexType());
        }
        else if (m_primitive == PP_POINTSPRITE)
        {
            driver->drawVertexPrimitiveList(m_buffer->getVertices(), pcnt,
                m_buffer->getIndices(), pcnt, video::EVT_STANDARD, 
                m_primitive == PP_POINTSPRITE ? EPT_POINT_SPRITES : EPT_POINTS,
                m_buffer->getIndexType());
        }

        // for debug purposes only:
        if ( DebugDataVisible & scene::EDS_BBOX )
        {
            driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
            video::SMaterial deb_m;
            deb_m.Lighting = false;
            driver->setMaterial(deb_m);
            driver->draw3DBox(m_buffer->BoundingBox, video::SColor(0,255,255,255));
        }

    }

}
