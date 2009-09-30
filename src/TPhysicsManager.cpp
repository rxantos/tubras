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
    //                    T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::TPhysicsManager() : TDelegate(),
        m_playerController(0),
        m_timer(0),
        m_irrCollision(0)
    {
        m_mode = pmNone;
        m_irrWorld = 0;
        m_bulletWorld = 0;
        //m_debugOverlay = NULL;
        m_userDebugString = "";
        m_debugMode = PDM_NoDebug;
        m_maxProxies = 32766;
        m_maxOverlap = 65535;
        m_debugObject = 0;
        m_gravity = TVector3::ZERO;
        m_subSteps = 1;
        m_fixedTimeStep = 1.f / 60.f;
        m_orgTimeStep = m_fixedTimeStep;
        m_simulationSpeed = 1.f;
        m_dtHigh = -1.f;
        m_dtLow = 10000.f;
        m_dtRunning = 0.f;
    }

    //-----------------------------------------------------------------------
    //                   ~ T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::~TPhysicsManager()
    {
        if(m_bulletWorld)
        {
            m_bulletWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(0);
            delete m_ghostPairCallback;

            // delete dynamic nodes
            while(m_objects.getSize())
            {
                TPhysicsObjectList::Iterator itr = m_objects.begin();
                destroyPhysicsObject(*itr);
            }

            delete m_bulletWorld;

            if(m_dispatcher)
                delete m_dispatcher;
            if(m_broadPhase)
                delete m_broadPhase;
            if(m_solver)
                delete m_solver;
            if(m_collisionConfig)
                delete m_collisionConfig;
        }

        if(m_irrWorld)
            m_irrWorld->drop();
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TPhysicsManager::initialize()
    {
        m_timer = getApplication()->getGlobalClock();
        TString csType = getApplication()->getConfig()->getString("physics.collisionSystem","Bullet");
        if(csType.equals_ignore_case("bullet"))
        {
            m_csType = cstBullet;
            m_updater = &TPhysicsManager::updateBullet;
            m_subSteps  = getApplication()->getConfig()->getInteger("physics.maxSubSteps", 1);
            m_fixedTimeStep = 1.f / getApplication()->getConfig()->getFloat("physics.fixedTimeStep", 60.f);

            m_collisionConfig = new btDefaultCollisionConfiguration();
            m_collisionConfig->setConvexConvexMultipointIterations();
            m_dispatcher = new	btCollisionDispatcher(m_collisionConfig);

            btVector3 worldAabbMin(-1000,-1000,-1000);
            btVector3 worldAabbMax(1000,1000,1000);

            TString bpType = getApplication()->getConfig()->getString("physics.broadphase", "btAxisSweep3");
            if(bpType.equals_ignore_case("bt32BitAxisSweep3"))
                m_broadPhase = new bt32BitAxisSweep3(worldAabbMin, worldAabbMax);
            else if(bpType.equals_ignore_case("btDbvt"))
                m_broadPhase = new btDbvtBroadphase();
            else // default 
                m_broadPhase = new btAxisSweep3(worldAabbMin,worldAabbMax);

            m_solver = new btSequentialImpulseConstraintSolver;

            m_bulletWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadPhase,m_solver,m_collisionConfig);

            m_ghostPairCallback = new btGhostPairCallback();
            m_broadPhase->getOverlappingPairCache()->setInternalGhostPairCallback(m_ghostPairCallback);

            btVector3 bgravity(m_gravity.X, m_gravity.Y, m_gravity.Z);
            m_bulletWorld->setGravity(bgravity);
            m_bulletWorld->setDebugDrawer(this);
        }
        else
        {
            m_csType = cstIrrlicht;
            m_updater = &TPhysicsManager::updateIrrlicht;

            m_irrWorld = getApplication()->getSceneManager()->createMetaTriangleSelector();

            m_irrCollision = getApplication()->getSceneManager()->createCollisionResponseAnimator(m_irrWorld, 0);
            float width = getApplication()->getConfig()->getFloat("physics.characterWidth", 1.f);
            float height = getApplication()->getConfig()->getFloat("physics.characterHeight", 2.f);

            TVector3 radius(width,height,width);
            m_irrCollision->setEllipsoidRadius(radius);
            m_irrCollision->setGravity(vector3df(0.f, -0.1f, 0.f));
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    s e t U s e r D e b u g S t r i n g
    //-----------------------------------------------------------------------
    void TPhysicsManager::setUserDebugString(const TString& value)
    {
        m_userDebugString = value;
    }

    //-----------------------------------------------------------------------
    //                          s e t G r a v i t y
    //-----------------------------------------------------------------------
    void TPhysicsManager::setGravity(const TVector3& value)
    {
        m_gravity = value;
        btVector3 b(value.X, value.Y, value.Z);
        if(m_bulletWorld)
            m_bulletWorld->setGravity(b);
    }

    //-----------------------------------------------------------------------
    //                  s e t P l a y e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    void TPhysicsManager::setPlayerController(TPlayerController* value)
    {
        m_playerController = value;

        if(m_bulletWorld)
        {
            m_bulletWorld->addCollisionObject(m_playerController->getGhostObject(),
                btBroadphaseProxy::CharacterFilter, 
                btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

            m_bulletWorld->addAction(m_playerController->getCharacter());
        }
    }

    //-----------------------------------------------------------------------
    //                        t o g g l e D e b u g
    //-----------------------------------------------------------------------
    void TPhysicsManager::toggleDebug()
    {
        if(getDebugMode())
        {
            setDebugMode(PDM_NoDebug);
        }
        else
        {
            setDebugMode(PDM_DrawWireframe);
        }
    }

    //-----------------------------------------------------------------------
    //                    a d d P h y s i c s O b j e c t
    //-----------------------------------------------------------------------
    void TPhysicsManager::addPhysicsObject(TPhysicsObject* object)
    {
        if(m_bulletWorld)
        {
            m_bulletWorld->addRigidBody(object->getRigidBody(), object->getGroupMask(), 
                object->getCollisionMask());
        }

        m_objects.push_back(object);
        if(object->getBodyType() == btKinematic)
        {
            m_kinematicObjects.push_back(object);
        }
    }

    //-----------------------------------------------------------------------
    //                   d e s t r o y D y n a m i c N o d e
    //-----------------------------------------------------------------------
    void TPhysicsManager::destroyPhysicsObject(TPhysicsObject* object)
    {
        TPhysicsObjectList::Iterator itr = m_objects.begin();
        while(itr != m_objects.end())
        {
            if(*itr == object)
            {
                delete object;
                m_objects.erase(itr);
                break;
            }
            ++itr;
        }
    }

    //-----------------------------------------------------------------------
    //                           d r a w L i n e
    //-----------------------------------------------------------------------
    void TPhysicsManager::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
    {
        TVector3 v1(from.m_floats[0], from.m_floats[1], from.m_floats[2]);
        TVector3 v2(to.m_floats[0], to.m_floats[1], to.m_floats[2]);

        // handle bullet simplex debug color bug...
        u32 r = (u32)color.x(), g = (u32) color.y(), b = (u32) color.z();

        TColor scolor;
        if( (r > 1) || (g > 1) || (b > 1))
            scolor.set(255, r, g, b);
        else
            scolor.set(255, (u32)(color.x() * 255.f), (u32)(color.y() * 255.f), (u32)(color.z() * 255.f));

        TVertex vert1(v1,v1,scolor,TVector2f());
        TVertex vert2(v2,v2,scolor,TVector2f());
        m_debugObject->addLine(vert1,vert2);
    }

    //-----------------------------------------------------------------------
    //                      d r a w C o n t a c t P o i n t
    //-----------------------------------------------------------------------
    void TPhysicsManager::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,float distance,int lifeTime,const btVector3& color)
    {
    }

    //-----------------------------------------------------------------------
    //                          d r a w 3 d T e x t
    //-----------------------------------------------------------------------
    void TPhysicsManager::draw3dText(const btVector3& location,const char* textString)
    {
    }

    //-----------------------------------------------------------------------
    //                        s e t D e b u g M o d e
    //-----------------------------------------------------------------------
    void TPhysicsManager::setDebugMode(int debugMode)
    {
        
        m_debugMode = (TPhysicsDebugMode)debugMode;
        if(m_debugMode)
        {
            if(!m_debugObject)
            {
                m_debugObject =  new TDebugNode(0);
            }
        }
        if(m_debugObject)
        {
            if(m_debugMode)
                m_debugObject->setVisible(true);
            else 
            {
                if(m_debugObject)
                {
                    m_debugObject->reset();
                    m_debugObject->setVisible(false);
                }
            }
        }
        
    }

    //-----------------------------------------------------------------------
    //                        g e t D e b u g M o d e
    //-----------------------------------------------------------------------
    int	TPhysicsManager::getDebugMode() const 
    { 
        return m_debugMode;
    }

    //-----------------------------------------------------------------------
    //                              r a y T e s t
    //-----------------------------------------------------------------------
    TRayResult TPhysicsManager::rayTest(const TRay& ray)
    {
        if(m_bulletWorld)
        {
            btVector3 rayFrom(ray.start.X, ray.start.Y, ray.start.Z);
            btVector3 rayTo(ray.end.X, ray.end.Y, ray.end.Z);

            btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);
            m_bulletWorld->rayTest(rayFrom,rayTo,rayCallback);

            TRayResult rr(rayCallback);
            return TRayResult(rayCallback);
        }
        else  
        {

            return TRayResult();
        }
    }

    //-----------------------------------------------------------------------
    //                    a c t i v a t e A l l O b j e c ts
    //-----------------------------------------------------------------------
    void TPhysicsManager::activateAllObjects()
    {
        TPhysicsObjectList::Iterator itr = m_objects.begin();

        while(itr != m_objects.end())
        {
            TPhysicsObject* o = *itr;
            if(o->getBodyType() == btDynamic && !o->isActive())
                o->activate();
            ++itr;
        }        
    }

    //-----------------------------------------------------------------------
    //                          j u m p C h a r a c t e r
    //-----------------------------------------------------------------------
    void TPhysicsManager::jumpCharacter()
    {
        if(m_bulletWorld)
        {
            m_playerController->getCharacter()->jump();
            return;
        }

        if(m_irrCollision)
        {
            if(!m_irrCollision->isFalling())
                m_irrCollision->jump(m_playerController->getJumpSpeed());
        }

    }

    //-----------------------------------------------------------------------
    //                        r e p o r t W a r n i n g
    //-----------------------------------------------------------------------
    void TPhysicsManager::reportErrorWarning(const char* warningString)
    {
        getApplication()->logMessage(LOG_WARNING, "DynamicWorld: %s", warningString);
    }

    //-----------------------------------------------------------------------
    //                    d u m p B u l l e t P r o f i l e
    //-----------------------------------------------------------------------
    void TPhysicsManager::dumpBulletProfile(CProfileIterator* profileIterator, int spacing)
    {
        TApplication* app = getApplication();
        TString spaces="";

        if(!profileIterator) 
        {
            app->logMessage(LOG_INFO, " ");
            app->logMessage(LOG_INFO, "------------------ B u l l e t   P r o f i l e   D a t a --------------------");
            app->logMessage(LOG_INFO, "dtRunning: %.6f, dtHigh: %.6f, dtLow: %.6f, dtAvg: %.6f",
            m_dtRunning, m_dtHigh, m_dtLow, m_dtRunning / (f32)CProfileManager::Get_Frame_Count_Since_Reset());
            profileIterator = CProfileManager::Get_Iterator();
        }

        profileIterator->First();
        if (profileIterator->Is_Done())
            return;

        float accumulated_time=0,parent_time = profileIterator->Is_Root() ? CProfileManager::Get_Time_Since_Reset() : profileIterator->Get_Current_Parent_Total_Time();
        int i;
        int frames_since_reset = CProfileManager::Get_Frame_Count_Since_Reset();

        for (i=0;i<spacing;i++)
            spaces += ".";
        app->logMessage(LOG_INFO, " ");
        app->logMessage(LOG_INFO, "Profiling: %s (total running time: %.3f ms)",	profileIterator->Get_Current_Parent_Name(), parent_time );

        float totalTime = 0.f;


        int numChildren = 0;

        for (i = 0; !profileIterator->Is_Done(); i++,profileIterator->Next())
        {
            numChildren++;
            float current_total_time = profileIterator->Get_Current_Total_Time();
            accumulated_time += current_total_time;
            float fraction = parent_time > SIMD_EPSILON ? (current_total_time / parent_time) * 100 : 0.f;

            app->logMessage(LOG_INFO, "%s %d -- %s (%.2f %%) :: %.6f ms / frame (%d calls)", spaces.c_str(), 
                i, profileIterator->Get_Current_Name(), 
                fraction,(current_total_time / (f32)frames_since_reset),
                profileIterator->Get_Current_Total_Calls());

            totalTime += current_total_time;
            //recurse into children
        }

        if (parent_time < accumulated_time)
        {
            //printf("what's wrong\n");
        }
        app->logMessage(LOG_INFO, "%s %s (%.3f %%) :: %.6f ms", spaces.c_str(), "Unaccounted:",
            parent_time > SIMD_EPSILON ? ((parent_time - accumulated_time) / parent_time) * 100 : 0.f, 
            parent_time - accumulated_time);

        for (i=0;i<numChildren;i++)
        {
            profileIterator->Enter_Child(i);
            dumpBulletProfile(profileIterator,spacing+3);
            profileIterator->Enter_Parent();
        }
    }

    //-----------------------------------------------------------------------
    //                        u p d a t e B u l l e t
    //-----------------------------------------------------------------------
    void TPhysicsManager::updateBullet(const f32 deltaTime)
    {
        TPROFILE_START("updateBullet");
        int stepCount = m_bulletWorld->stepSimulation(deltaTime);

        if(stepCount && m_playerController)
            m_playerController->updatePlayerFromGhost();
        TPROFILE_STOP();

        //
        // report collisions
        //
        /*
        int numManifolds = m_world->getDispatcher()->getNumManifolds();
        for (int i=0;i<numManifolds;i++)
        {
            btPersistentManifold* contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);
            btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
            btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
            btRigidBody* rbA = btRigidBody::upcast(obA);
            btRigidBody* rbB = btRigidBody::upcast(obB);

            TPhysicsObject* oa = static_cast<TPhysicsObject*>(obA->getUserPointer());
            TPhysicsObject* ob = static_cast<TPhysicsObject*>(obB->getUserPointer());
            TString sdbg = "Collision:\n";

            if(oa)
            {
                sdbg += "   A: ";
                sdbg += oa->getName();
                if(rbA)
                {
                    sdbg += ", ActivationState=";
                    sdbg += rbA->getActivationState();
                }
                sdbg += "\n";
            }
            else 
            {
                sdbg += "   A: null\n";
            }

            if(ob)
            {
                sdbg += "   B: ";
                sdbg += ob->getName();
                if(rbB)
                {
                    sdbg += ", ActivationState=";
                    sdbg += rbB->getActivationState();
                }
                sdbg += "\n";
            }
            else 
            {
                sdbg += "   B: null\n";
            }
            */

            /*
            if(oa && (rbA->getActivationState() == ACTIVE_TAG)  &&
                ob && (rbB->getActivationState() == ACTIVE_TAG))
            {
                getApplication()->logMessage(LOG_INFO, "Collision: %s <-> %s", oa->getName().c_str(), 
                    ob->getName().c_str());
            }
            */

            //getApplication()->logMessage(LOG_INFO, sdbg.c_str());

        /*
            int numContacts = contactManifold->getNumContacts();
            for (int j=0;j<numContacts;j++)
            {
                btManifoldPoint& pt = contactManifold->getContactPoint(j);
                if (pt.getDistance()<0.f)
                {
                    const btVector3& ptA = pt.getPositionWorldOnA();
                    const btVector3& ptB = pt.getPositionWorldOnB();
                    const btVector3& normalOnB = pt.m_normalWorldOnB;
                }
            }
        }
        */
   

        if(m_debugObject)
        {
            m_debugObject->reset();
            m_bulletWorld->debugDrawWorld();
        }
    }

    //-----------------------------------------------------------------------
    //                       u p d a t e I r r l i c h t
    //-----------------------------------------------------------------------
    void TPhysicsManager::updateIrrlicht(const f32 deltaTime)
    {
        if(m_playerController->getMode() != pcmGod)
            m_irrCollision->animateNode(m_playerController->getCharacterSceneNode(),
            m_timer->getMilliSeconds());
    }

    //-----------------------------------------------------------------------
    //                            c r e a t e O b j e c t
    //-----------------------------------------------------------------------
    TPhysicsObject* TPhysicsManager::createObject(ISceneNode* snode, 
        TPhysicsShapeType shapeType, TPhysicsBodyType bodyType, f32 mass,
        bool isGhost, bool isTrigger,
        f32 friction, f32 restitution)
    {
        TPhysicsObject* result=0;
        IMesh* mesh=0;
        TColliderShape* colliderShape=0;

        switch(snode->getType())
        {
            case ESNT_ANIMATED_MESH:
                mesh =  static_cast<IAnimatedMeshSceneNode*>(snode)->getMesh();
                break;
            case ESNT_MESH:
                mesh =  static_cast<IMeshSceneNode*>(snode)->getMesh();
                break;
        } 

        if(!mesh)
        {
            getApplication()->logMessage(LOG_ERROR, "Error creating physics object - Mesh is NULL for %s", snode->getName());
            return 0;
        }

        if(m_csType == cstIrrlicht)
        {
            ITriangleSelector* selector = getApplication()->getSceneManager()->createTriangleSelector(mesh, snode);
            m_irrWorld->addTriangleSelector(selector);

            // check if ghost object (collision only)
            if(isGhost)
            {
                // turn off visibility, can't remove node.
                snode->setVisible(false);
            }
            // for irrlicht collision system we don't create physics objects...
            return 0;
        }

        // bullet

        switch(shapeType)
        {
            case stBox:
                colliderShape = new TColliderBox(snode); 
                break;
            case stSphere:
                colliderShape = new TColliderSphere(snode);
                break;
            case stCylinder:
                colliderShape = new TColliderCylinder(snode);
                break;
            case stCone:
                colliderShape = new TColliderCone(snode);
                break;
            default:
                bool convex=false;
                if(shapeType == stConvexMesh)
                    convex = true;
                else if((bodyType == btKinematic) || (bodyType == btDynamic))
                {
                    convex = true;
                    getApplication()->logMessage(LOG_WARNING, "Dynamic concave mesh not supported - using convex shape.");
                    getApplication()->logMessage(LOG_WARNING, "    mesh: %s", snode->getName());
                }
                colliderShape = new TColliderMesh(mesh,snode->getRelativeTransformation(), convex, false);
                break;
        }

        result = new TPhysicsObject(snode->getName(), snode, colliderShape, mass, bodyType);
        
        if(bodyType == btDynamic)
        {
            //result->setDamping(0.2f, 0.2f);
            result->allowDeactivation(true);
        }


        result->setFriction(friction);
        result->setRestitution(restitution);

        if(isGhost)
        {
            result->setSceneNode(0);
            snode->setVisible(false);
            getApplication()->getSceneManager()->addToDeletionQueue(snode);
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TPhysicsManager::update(const f32 deltaTime)
    {
        if(deltaTime == 0.f)
            return;

        m_dtRunning += deltaTime;
        if(deltaTime > m_dtHigh)
            m_dtHigh = deltaTime;
        else if(deltaTime < m_dtLow)
            m_dtLow = deltaTime;

        (this->*m_updater)(deltaTime);
    }
}

