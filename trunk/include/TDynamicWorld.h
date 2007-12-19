//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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

    typedef std::list<TDynamicNode*>       TDynamicNodeList;

    class TDynamicWorld :   public btIDebugDraw, public TObject
    {
    protected:
        btDiscreteDynamicsWorld*    m_world;
        btCollisionDispatcher*      m_dispatcher;
        btDefaultCollisionConfiguration* m_collisionConfig;
        btBroadphaseInterface*      m_broadPhase;
        btConstraintSolver*         m_solver;
        TVector3                    m_gravity;
        int                         m_maxProxies;
        int                         m_maxOverlap;
        TDebugPhysicsMode           m_debugMode;
        TDynamicNodeList            m_nodes;

        //Ogre::ManualObject*         m_debugObject;


    public:
        TDynamicWorld();
        virtual ~TDynamicWorld();

        //
        // debug functionality
        //
        void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
        void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,float distance,int lifeTime,const btVector3& color);
	    void draw3dText(const btVector3& location,const char* textString);

        void setDebugMode(int debugMode);
        int	 getDebugMode() const { return m_debugMode;}
        void reportErrorWarning(const char* warningString);
        void toggleDebug();

        TDynamicNodeList getDynamicNodes() {return m_nodes;};

        btDiscreteDynamicsWorld* getBulletWorld() {return m_world;};

        void setGravity(const TVector3& value);
        TVector3 getGravity();

        void allowDeactivation(bool value);

        void addDynamicNode(TDynamicNode* node);
        void destroyDynamicNode(TDynamicNode* node);

        TRayResult rayTest(const TRay& ray);

        void step(u32 delta);
    };

}


#endif
