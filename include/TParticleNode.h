//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TPARTICLENODE_H_
#define _TPARTICLENODE_H_

namespace Tubras
{
    typedef TList<TParticleAction*> TParticleActions;
    typedef TParticleActions::Iterator  TParticleActionsItr;

    class TParticleNode : public ISceneNode
    {
        friend class TParticleManager;
        friend class TNodeFactory;
    private:
        PAPI::ParticleContext_t     m_pc;
        int                         m_handle;
        int                         m_maxParticles;
        TVector3                    m_pos;
        TParticleActions            m_actions;
        bool                        m_pointRendering;
        float                       m_timeStep;
        bool                        m_enabled;
        const TAABBox               m_aabb;
        SMaterial                   m_material;
        CDynamicMeshBuffer*         m_buffer;
        TParticlePrimitive          m_primitive;

    private:
        TParticleNode(ISceneNode* parent=0, int maxParticles = 256, 
            TParticlePrimitive primitive=PP_BILLBOARD);
        void _updateBuffer(void);

    public:
        virtual ~TParticleNode();

        void addAction(TParticleAction* action);
        void setColor(TColor color);
        void setColor(TParticleDomain colorDomain);
        void setColor(TParticleDomain colorDomain, TParticleDomain alphaDomain);

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
        float getTimeStep() {return m_timeStep;}
        void setPointSize(float size);
        void setMaterialName(TString name);
        void setSpriteImage(TString name, bool alphaBlend=true);
        size_t getMaxParticles() {return m_pc.GetMaxParticles();}
        void setMaxParticles(size_t value);

        void step();

        //! node funcs
        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;
        SMaterial& getMaterial(u32 i);
    };

}
#endif
