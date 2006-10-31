//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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

#ifndef __TDYNAMICWORLD_H_
#define __TDYNAMICWORLD_H_

namespace Tubras
{
    class TRigidBody;

	enum TDebugPhysicsMode
	{
		PDM_NoDebug=0,
		PDM_DrawWireframe = 1,
		PDM_DrawAabb=2,
		PDM_DrawFeaturesText=4,
		PDM_DrawContactPoints=8,
		PDM_NoDeactivation=16,
		PDM_NoHelpText = 32,
		PDM_DrawText=64,
		PDM_ProfileTimings = 128,
		PDM_EnableSatComparison = 256,
		PDM_DisableBulletLCP = 512,
		PDM_EnableCCD = 1024,
		PDM_MAX_DEBUG_DRAW_MODE
	};

    typedef std::list<TRigidBody*>       TBodyList;

    class TDynamicWorld :   public btIDebugDraw, public TObject
    {
    protected:
        btDiscreteDynamicsWorld*    m_world;
        btCollisionDispatcher*      m_dispatcher;
        btOverlappingPairCache*     m_broadPhase;
        btConstraintSolver*         m_solver;
        float                       m_gravity;
        int                         m_maxProxies;
        int                         m_maxOverlap;
        TDebugPhysicsMode           m_debugMode;
        TBodyList                   m_bodies;

        Ogre::ManualObject*         m_debugObject;


    public:
        TDynamicWorld();
        virtual ~TDynamicWorld();

        //
        // debug functionality
        //
	    void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
	    void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,float distance,int lifeTime,const btVector3& color);
	    void setDebugMode(int debugMode);
	    int	 getDebugMode() const { return m_debugMode;}
		void toggleDebug();

        TBodyList getBodies() {return m_bodies;};

		btDiscreteDynamicsWorld* getBulletWorld() {return m_world;};

        void setGravity(float value);
        float getGravity();

		void allowDeactivation(bool value);

        void addRigidBody(TRigidBody* body);
		void destroyRigidBody(TRigidBody* body);

        void step(float delta);
    };

}


#endif
