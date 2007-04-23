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

#ifndef _TPARTICLEGROUP_H_
#define _TPARTICLEGROUP_H_

namespace Tubras
{
    //class TParticleGroup : public Ogre::SimpleRenderable 
    // pattern after ogrebillboardset using point sprite rendering
    typedef std::vector<TParticleAction*> TActions;
    typedef TActions::iterator  TActionsIterator;

    class TParticleGroup : public Ogre::MovableObject, public Ogre::Renderable
    {
        friend class TParticleManager;
    private:
        PAPI::ParticleContext_t     m_pc;
        int                         m_handle;
        TVector3                    m_pos;
        Ogre::MaterialPtr           m_mat;

        static Ogre::String         m_movableType;
        Ogre::AxisAlignedBox        m_bb;
        Ogre::VertexData*           m_vertexData;
        Ogre::HardwareVertexBufferSharedPtr m_hvBuf;
        TActions                    m_actions;
        bool                        m_pointRendering;

    protected:
        TParticleGroup(size_t maxParticles);
        virtual ~TParticleGroup();
        void _createBuffers(void);

        //
        // movable object overrides
        //
        const Ogre::String& getMovableType(void) const;
        const Ogre::AxisAlignedBox& getBoundingBox(void) const;
        Ogre::Real getBoundingRadius(void) const;
        void _updateRenderQueue(Ogre::RenderQueue* queue);

        //
        // renderable overrides
        //
        virtual const Ogre::MaterialPtr& getMaterial(void) const;
        virtual void getRenderOperation(Ogre::RenderOperation& op);
        virtual void getWorldTransforms(Ogre::Matrix4* xform) const;
        const Ogre::Quaternion& getWorldOrientation(void) const;
        const Ogre::Vector3& getWorldPosition(void) const;
        const Ogre::LightList& getLights(void) const;
        Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const;

    public:
        void step();
        void setPos(TVector3 value) {m_pos = value;}
        TVector3 getPos() {return m_pos;}

        void addAction(TParticleAction *action);
        
        // particle state settings

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

    };

}
#endif