#include "CPhysicsManager.h"

#define TRIGGER_ENTER   0xFFCE0001
#define TRIGGER_EXIT    0xFFCE0000

namespace irr 
{
    //-------------------------------------------------------------------------
    //                        s e t A t t r i b u t e s
    //-------------------------------------------------------------------------
    void CPhysicsManager::setAttributes(irr::io::IAttributes* userData, struct CPhysicsAttributes& attr)
    {
        EShapeType bodyShape=stConcaveMesh;
        EBodyType bodyType=btStatic;

        core::stringc sBodyType = userData->getAttributeAsString("Physics.BodyType");
        if(sBodyType == "none")
            return;

        core::stringc sBodyShape = userData->getAttributeAsString("Physics.BodyShape");
        attr.visible = true;
        if(userData->existsAttribute("Physics.Visible"))
            attr.visible = userData->getAttributeAsBool("Physics.Visible");

        attr.ghost = userData->getAttributeAsBool("Physics.Ghost");  
        attr.trigger = userData->getAttributeAsBool("Physics.Trigger"); // collision without restitution

        attr.mass = userData->getAttributeAsFloat("Physics.Mass");
        attr.friction = userData->getAttributeAsFloat("Physics.Friction");
        attr.restitution = userData->getAttributeAsFloat("Physics.Restitution");
        attr.radius=0.f;
        if(userData->existsAttribute("Physics.Radius"))
            attr.radius = userData->getAttributeAsFloat("Physics.Radius");

        if(sBodyShape.equals_ignore_case("box"))
        {
            bodyShape = stBox;               
        }
        else if(sBodyShape.equals_ignore_case("sphere"))
        {
            bodyShape = stSphere;
        }
        else if(sBodyShape.equals_ignore_case("cylinder"))
        {
            bodyShape = stCylinder;
        }
        else if(sBodyShape.equals_ignore_case("cone"))
        {
            bodyShape = stCone;
        }
        else if(sBodyShape.equals_ignore_case("convexmesh"))
        {
            bodyShape = stConvexMesh;
        }
        else if(sBodyShape.equals_ignore_case("concavemesh"))
        {
            bodyShape = stConcaveMesh;
        }

        if(sBodyType == "rigid")
            bodyType = btKinematic;
        else if(sBodyType == "dynamic")
            bodyType = btDynamic;
        else if(sBodyType == "sensor")
            attr.trigger = true;

    }

    //-------------------------------------------------------------------------
    //                        p r o c e s s E v e n t
    //-------------------------------------------------------------------------
    bool CPhysicsManager::processEvent(const SEvent&  event)
    {
        if(event.EventType == EET_USER_EVENT)
        {
            if(event.UserEvent.UserData1 == TRIGGER_ENTER)
            {
                scene::ISceneNode* node = (scene::ISceneNode*)event.UserEvent.UserData2;
                printf("Entered Trigger: %s\n", node->getName());
                return true;
            }
            else if(event.UserEvent.UserData1 == TRIGGER_EXIT)
            {
                scene::ISceneNode* node = (scene::ISceneNode*)event.UserEvent.UserData2;
                printf("Exited Trigger: %s\n", node->getName());
                return true;
            }
        }

        return false;
    }

#ifdef USE_BULLET
    //-------------------------------------------------------------------------
    //               a d d P h y s i c s O b j e c t - (Bullet)
    //-------------------------------------------------------------------------
    void CPhysicsManager::addPhysicsObject(irr::scene::ISceneNode* node, 
        irr::io::IAttributes* userData)
    {
        struct CPhysicsAttributes attr;
        IMesh* mesh=0;

        switch(snode->getType())
        {
            case ESNT_ANIMATED_MESH:
                mesh =  static_cast<IAnimatedMeshSceneNode*>(node)->getMesh();
                break;
            case ESNT_MESH:
                mesh =  static_cast<IMeshSceneNode*>(node)->getMesh();
                break;
        } 
        if(!mesh)
        {
            printf("Error creating physics object - Mesh is NULL for %s\n", node->getName());
            return;
        }
        setAttributes(userData, attr);
    }
#elif USE_IRRPHYSX
    //-------------------------------------------------------------------------
    //               a d d P h y s i c s O b j e c t - (IrrPhysx)
    //-------------------------------------------------------------------------
    void CPhysicsManager::addPhysicsObject(irr::scene::ISceneNode* node, 
        irr::io::IAttributes* userData)
    {
        struct CPhysicsAttributes attr;
        IMesh* mesh=0;

        switch(snode->getType())
        {
            case ESNT_ANIMATED_MESH:
                mesh =  static_cast<IAnimatedMeshSceneNode*>(node)->getMesh();
                break;
            case ESNT_MESH:
                mesh =  static_cast<IMeshSceneNode*>(node)->getMesh();
                break;
        } 
        if(!mesh)
        {
            printf("Error creating physics object - Mesh is NULL for %s\n", node->getName());
            return;
        }
        setAttributes(userData, attr);
    }
#else
    //-------------------------------------------------------------------------
    //               a d d P h y s i c s O b j e c t - (Irrlicht)
    //-------------------------------------------------------------------------
    void CPhysicsManager::addPhysicsObject(irr::scene::ISceneNode* node, 
        irr::io::IAttributes* userData)
    {
        struct CPhysicsAttributes attr;
        scene::IMesh* mesh=0;

        switch(node->getType())
        {
            case scene::ESNT_ANIMATED_MESH:
                mesh =  static_cast<scene::IAnimatedMeshSceneNode*>(node)->getMesh();
                break;
            case scene::ESNT_MESH:
                mesh =  static_cast<scene::IMeshSceneNode*>(node)->getMesh();
                break;
        } 
        if(!mesh)
        {
            printf("Error creating physics object - Mesh is NULL for %s\n", node->getName());
            return;
        }
        setAttributes(userData, attr);

        irr::scene::ITriangleSelector* selector = m_sceneManager->createTriangleSelector(mesh, node);
        if(!attr.trigger)
            m_world->addTriangleSelector(selector);
        else
            m_triggers->addTriangleSelector(selector);

        // collision only ?
        if(!attr.visible)
        {
            // turn off visibility
            node->setVisible(false);
        }
    }

    //-------------------------------------------------------------------------
    //                        d i s p l a y D e b u g
    //-------------------------------------------------------------------------
    void CPhysicsManager::displayDebug()
    {
        irr::core::triangle3df* tris, *tri;
        video::IVideoDriver* driver = m_sceneManager->getVideoDriver();
        s32 outCount;
        s32 tcount  = m_world->getTriangleCount();

        // collision (green)
        if(tcount)
        {
        tri = 
        tris = (irr::core::triangle3df*) malloc(sizeof(irr::core::triangle3df) * tcount);
        m_world->getTriangles(tris, tcount, outCount);
        video::SColor color(255, 0, 255, 0);
        
        for(int i=0; i<outCount; i++)
        {            
            driver->draw3DLine(tri->pointA, tri->pointB, color);
            driver->draw3DLine(tri->pointB, tri->pointC, color);
            driver->draw3DLine(tri->pointA, tri->pointC, color);
            ++tri;
        }
        free(tris);
        }

        // triggers (yellow)
        tcount  = m_triggers->getTriangleCount();
        if(!tcount)
            return;

        tri = 
        tris = (irr::core::triangle3df*) malloc(sizeof(irr::core::triangle3df) * tcount);
        m_triggers->getTriangles(tris, tcount, outCount);
        video::SColor color(255, 255, 255, 0);
        
        for(int i=0; i<outCount; i++)
        {
            driver->draw3DLine(tri->pointA, tri->pointB, color);
            driver->draw3DLine(tri->pointB, tri->pointC, color);
            driver->draw3DLine(tri->pointA, tri->pointC, color);
            ++tri;
        }
        free(tris);
    }

    //-------------------------------------------------------------------------
    //                         s t e p I r r l i c h t
    //-------------------------------------------------------------------------
    void CPhysicsManager::stepIrrlicht(irr::u32 deltaMS)
    {
        static bool firstUpdate=true;
        static core::vector3df lastPosition;
        static scene::ISceneNode* activeTrigger=0;

        // update the camera position
        //m_response->animateNode(m_sceneManager->getActiveCamera(),
        //    m_timer->getTime());

        // check for collision against "trigger" geometry
        const scene::ISceneNode* node=0;
        core::vector3df directionAndSpeed;
        core::triangle3df triout;
        core::vector3df hitPosition;
        bool falling;
        core::vector3df currentPosition = m_sceneManager->getActiveCamera()->getAbsolutePosition();
        if(firstUpdate)
        {
            lastPosition = currentPosition;
            firstUpdate = false;
        }

        directionAndSpeed.set(0.1f, 0.1f, 0.f); // ...
        lastPosition  = currentPosition;

        m_collisionManager->getCollisionResultPosition(
            m_triggers, 
            currentPosition,
            m_response->getEllipsoidRadius(),
            directionAndSpeed,
            triout,
            hitPosition,
            falling,
            node);

        // hit?
        if(node)
        {
            if(node != activeTrigger)
            {
                // enter event
                SEvent event;
                event.UserEvent.UserData1 = TRIGGER_ENTER;
                event.UserEvent.UserData2 = (s32)node;
                m_sceneManager->postEventFromUser(event);
                activeTrigger = (scene::ISceneNode*) node;
            }
        }
        else if(activeTrigger)  // no collisions and previous = exit
        {
            // exit event
            SEvent event;
            event.UserEvent.UserData1 = TRIGGER_EXIT;
            event.UserEvent.UserData2 = (s32)activeTrigger;
            m_sceneManager->postEventFromUser(event);
            activeTrigger = 0;
        }
    }
#endif

    //-------------------------------------------------------------------------
    //                         s t e p S i m u l a t i o n
    //-------------------------------------------------------------------------
    void CPhysicsManager::stepSimulation(irr::u32 deltaMS)
    {
#ifdef USE_BULLET
        stepBullet(deltaMS);
#elif USE_IRRPHYSX
        stepIrrPhysx(deltaMS);
#else // Irrlicht
        stepIrrlicht(deltaMS);
#endif
    }

}
