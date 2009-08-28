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
    //                     T P l a y e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    TPlayerController::TPlayerController(const TString& controllerName,
        ICameraSceneNode* camera,
        TPlayerControllerMode mode,
        ISceneNode* playerNode) : TController(controllerName, 0, playerNode)
    {
        m_mode = mode;
        m_camera = camera;
        m_rotating = false;
        m_pitching = false;
        m_translating = false;
        m_fDamping = 
        m_bDamping = false;
        m_mouseMoved = false;
        m_zoomed = false;
        m_movementEnabled = true;
        m_mouseMovementEnabled = true;
        m_translate = TVector3::ZERO;
        m_pitch = 0.0f;
        m_rotate = 0.0f;
        m_shift = 1.0f;
        m_inverted = -1.0f;
        m_fDampDir = 0;
        m_bDampDir = 0;
        m_fDampTime =
        m_bDampTime = 0.f;
        memset(m_actions,0,sizeof(m_actions));

        TSL* config = getApplication()->getConfig();
        m_orgVelocity =
        m_velocity = config->getFloat("options.velocity",3.0);
        m_velDamp = config->getFloat("options.velocitydamp",1.0);
        m_angularVelocity = config->getFloat("options.angularvelocity",3.0);
        m_maxVertAngle = config->getFloat("options.maxvertangle",88.0);

        m_characterWidth = config->getFloat("physics.characterWidth", 1.f) / 2.f;
        m_characterHeight = config->getFloat("physics.characterHeight", 2.f) / 2.f;
        m_characterStepHeight = config->getFloat("physics.characterStepHeight", 0.35f);

        m_mouseDelegate = EVENT_DELEGATE(TPlayerController::procMouseMove);
        TApplication* app = getApplication();

        app->acceptEvent("input.mouse.move",m_mouseDelegate);

        m_cmdDelegate = EVENT_DELEGATE(TPlayerController::procCmd);

        m_frwdID = app->acceptEvent("frwd",m_cmdDelegate);
        m_backID = app->acceptEvent("back",m_cmdDelegate);
        m_leftID = app->acceptEvent("left",m_cmdDelegate);
        m_rghtID = app->acceptEvent("rght",m_cmdDelegate);
        m_rotlID = app->acceptEvent("rotl",m_cmdDelegate);
        m_rotrID = app->acceptEvent("rotr",m_cmdDelegate);
        m_mvupID = app->acceptEvent("mvup",m_cmdDelegate);
        m_mvdnID = app->acceptEvent("mvdn",m_cmdDelegate);
        m_rotfID = app->acceptEvent("rotf",m_cmdDelegate);
        m_rotbID = app->acceptEvent("rotb",m_cmdDelegate);
        m_avelID = app->acceptEvent("avel",m_cmdDelegate);
        m_jumpID = app->acceptEvent("jump",m_cmdDelegate);

        m_invertMouseID = app->acceptEvent("invert-mouse",m_cmdDelegate);
        m_toggleMouseID = app->acceptEvent("toggle-mouse",m_cmdDelegate);
        m_zoomedInID = app->acceptEvent("zoomed.in",m_cmdDelegate);
        m_zoomedOutID = app->acceptEvent("zoomed.out",m_cmdDelegate);

        
        // bullet character controller setup
        m_ghostObject= new btPairCachingGhostObject();
        btConvexShape* characterShape = new btCapsuleShape(m_characterWidth,m_characterHeight);
        btTransform trans;
        trans.setIdentity();
        TVector3 pos = m_camera->getAbsolutePosition();
        trans.setOrigin(btVector3(pos.X, pos.Y, pos.Z));
        m_ghostObject->setWorldTransform(trans);
        m_ghostObject->setCollisionShape(characterShape);
        int upAxis = 1;

        m_character = new btKinematicCharacterController(m_ghostObject, characterShape, m_characterStepHeight, upAxis);

        m_updater = &TPlayerController::updateFPS;
    }

    //-----------------------------------------------------------------------
    //                    ~ T P l a y e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    TPlayerController::~TPlayerController()
    {
        if(m_character)
        {
            getApplication()->getPhysicsManager()->getWorld()->getBulletWorld()->removeAction(m_character);
            delete m_character;
        }
    }

    //-----------------------------------------------------------------------
    //                         s e t C a m e r a
    //-----------------------------------------------------------------------
    ICameraSceneNode* TPlayerController::setCamera(ICameraSceneNode* camera)
    {
        ICameraSceneNode* oldCamera = m_camera;
        m_camera = camera;
        TVector3 pos = m_camera->getPosition();
        m_character->warp(btVector3(pos.X, pos.Y, pos.Z));
        return oldCamera;
    }

    //-----------------------------------------------------------------------
    //                            s e t M o d e
    //-----------------------------------------------------------------------
    void TPlayerController::setMode(TPlayerControllerMode value)
    {
        // if switching from God mode, update the bullet ghost object.
        if(m_mode == pcmGod)
        {
            TVector3 pos = m_camera->getPosition();
            m_character->warp(btVector3(pos.X, pos.Y, pos.Z));
            getApplication()->getPhysicsManager()->getWorld()->getBulletWorld()->addAction(m_character);
        }
        // if switching to God mode, suspend bullet action.
        if(value == pcmGod)
            getApplication()->getPhysicsManager()->getWorld()->getBulletWorld()->removeAction(m_character);

        m_mode = value;
    }

    //-----------------------------------------------------------------------
    //                         s e t P o s i t i o n
    //-----------------------------------------------------------------------
    void TPlayerController::setPosition(TVector3 value)
    {
        m_camera->setPosition(value);
        m_character->warp(btVector3(value.X, value.Y, value.Z));
    }

    //-----------------------------------------------------------------------
    //                       e n a b l e M o v e m e n t
    //-----------------------------------------------------------------------
    void TPlayerController::enableMovement(bool value)
    {
        m_movementEnabled = value;
    }

    //-----------------------------------------------------------------------
    //                   e n a b l e M o u s e M o v e m e n t
    //-----------------------------------------------------------------------
    void TPlayerController::enableMouseMovement(bool value)
    {
        m_mouseMovementEnabled = value;
    }

    //-----------------------------------------------------------------------
    //                         p r o c M o u s e M o v e
    //-----------------------------------------------------------------------
    int TPlayerController::procMouseMove(TEvent* event)
    {

        if(!m_mouseMovementEnabled)
            return 1;
        
        const irr::core::vector2di* pme;
        float zcoeff=1.0f;
        if(m_zoomed)
            zcoeff = 0.1f;
        //
        // parm(1) -> SEvent pointer
        // parm(2) -> relative movment vector
        //
        pme = (const irr::core::vector2di*) event->getParameter(1)->getPointerValue();
        m_mouseX = (f32)(-pme->X * 0.13 * zcoeff);
        m_mouseY = (f32) (m_inverted * pme->Y * 0.13 * zcoeff);
        m_mouseMoved = true;
        
        return 1;
    }

    //-----------------------------------------------------------------------
    //                            p r o c C m d
    //-----------------------------------------------------------------------
    int TPlayerController::procCmd(TEvent* event)
    {
        bool start = false;
        float famount = 0.0f;

        if(event->getNumParameters() > 0)
        {
            if(event->getParameter(0)->isInt())
                start = event->getParameter(0)->getIntValue() ? true : false;
            else if (event->getParameter(0)->isDouble())
                famount = (float) event->getParameter(0)->getDoubleValue();
        }
        size_t eid = event->getID();

        m_rotating = m_pitching = m_translating = false;

        if(eid == m_frwdID)
        {
            m_fDampDir = 
            m_actions[A_FRWD] = start;
            if(!m_fDamping && (m_velDamp != 0.f))
            {
                m_fDampTime = 0.f;
                m_fDamping = true;
            }
        }
        else if(eid == m_backID)
        {
            m_bDampDir = 
            m_actions[A_BACK] = start;
            if(!m_bDamping && (m_velDamp != 0.f))
            {
                m_bDampTime = 0.f;
                m_bDamping = true;
            }
        }
        else if(eid == m_leftID)
        {
            m_actions[A_LEFT] = start;
        }
        else if(eid == m_rghtID)
        {
            m_actions[A_RGHT] = start;
        }
        else if(eid == m_rotlID)
        {
            m_actions[A_ROTL] = start;
        }
        else if(eid == m_rotrID)
        {
            m_actions[A_ROTR] = start;
        }
        else if(eid == m_mvupID)
        {
            m_actions[A_MVUP] = start;
        }
        else if(eid == m_mvdnID)
        {
            m_actions[A_MVDN] = start;
        }
        else if(eid == m_jumpID)
        {
            if(m_character->onGround() && m_character->canJump())
                m_character->jump();
        }
        else if(eid == m_rotfID)
        {
            m_actions[A_ROTF] = start;
        }
        else if(eid == m_rotbID)
        {
            m_actions[A_ROTB] = start;
        }
        else if(eid == m_avelID)
        {
            m_velocity = m_orgVelocity * famount;
            printf("m_velocity %.2f\n", m_velocity);
        }
        else if(eid == m_invertMouseID)
        {
            if(m_inverted < 0)
                m_inverted = 1.0f;
            else m_inverted = -1.0f;
        }
        else if(eid == m_toggleMouseID)
        {
            m_mouseMovementEnabled = m_mouseMovementEnabled ? false : true;
        }
        else if(eid == m_zoomedInID)
        {
            m_zoomed = true;
        }
        else if(eid == m_zoomedOutID)
        {
            m_zoomed = false;
        }

        return 1;
    }

    //-----------------------------------------------------------------------
    //                          u p d a t e F P S
    //-----------------------------------------------------------------------
    void TPlayerController::updateFPS(f32 deltaFrameTime)
    {
        if(deltaFrameTime == 0.f)
            return;

        TVector3 target(0,0,1);
        TVector3 pos = m_camera->getPosition();
        TVector3 oldpos = pos;
        TVector3 rotation = m_camera->getRotation();
        TVector3 upVector = m_camera->getUpVector();
        f32 gPlayerForwardBackward=0.f, gPlayerSideways=0.f;

        m_camera->setTarget(target);
        rotation.X *= -1.0f;
        rotation.Y *= -1.0f;

        if(m_mouseMoved)
        {
            rotation.Y += m_mouseX;

            rotation.X += m_mouseY;
            rotation.X = clamp(rotation.X,
                -m_maxVertAngle, +m_maxVertAngle);
            m_mouseX = 0;
            m_mouseY = 0;
            m_mouseMoved = false;
        }

        if(m_movementEnabled)
        {
            if(m_actions[A_ROTR])
            {
                rotation.Y -= (deltaFrameTime * m_angularVelocity);
            }

            if(m_actions[A_ROTL])
            {
                rotation.Y += (deltaFrameTime * m_angularVelocity);
            }

            if(m_actions[A_ROTF])
            {
                rotation.X -= (deltaFrameTime * m_angularVelocity);
                rotation.X = clamp(rotation.X,
                    -m_maxVertAngle, +m_maxVertAngle);
            }

            if(m_actions[A_ROTB])
            {
                rotation.X += (deltaFrameTime * m_angularVelocity);
                rotation.X = clamp(rotation.X,
                    -m_maxVertAngle, +m_maxVertAngle);
            }

            rotation.X *= -1.0f;
            rotation.Y *= -1.0f;

            m_camera->setRotation(rotation);

            matrix4 mat;
            mat.setRotationDegrees(core::vector3df( rotation.X, rotation.Y, 0));
            mat.transformVect(target);

            vector3df movedir = target.normalize();

            if(m_actions[A_FRWD] || m_fDamping)
            {
                f32 damp = 1.f, velocity;
                if(m_fDamping)
                {
                    m_fDampTime += deltaFrameTime;
                    damp = m_fDampTime / m_velDamp;
                    if(m_fDampDir)
                    {
                        if(damp >= 1.f)                
                            m_fDamping = false;
                    }
                    else 
                    {
                        damp = 1.f - damp;
                        if(damp <= 0.f)                    
                            m_fDamping = false;
                    }
                }
                velocity = m_velocity * damp;
                pos += movedir * deltaFrameTime * velocity;
                gPlayerForwardBackward += (velocity * deltaFrameTime);
            }
            if(m_actions[A_BACK] || m_bDamping)
            {
                f32 damp = 1.f, velocity;
                if(m_bDamping)
                {
                    m_bDampTime += deltaFrameTime;
                    damp = m_bDampTime / m_velDamp;
                    if(m_bDampDir)
                    {
                        if(damp >= 1.f)                
                            m_bDamping = false;
                    }
                    else 
                    {
                        damp = 1.f - damp;
                        if(damp <= 0.f)                    
                            m_bDamping = false;
                    }
                }
                velocity = m_velocity * damp;
                pos -= movedir * deltaFrameTime * m_velocity;
                gPlayerForwardBackward -= (velocity * deltaFrameTime);
            }

            TVector3 strafeVector = target;
            strafeVector = strafeVector.crossProduct(upVector).normalize();
            if(m_actions[A_LEFT])
            {
                pos += strafeVector * deltaFrameTime * m_velocity;
                gPlayerSideways -= m_velocity * deltaFrameTime;
            }

            if(m_actions[A_RGHT])
            {
                pos -= strafeVector * deltaFrameTime * m_velocity;
                gPlayerSideways += m_velocity * deltaFrameTime;
            }

            if(m_actions[A_MVUP])
            {
                pos += TVector3::UNIT_Y * deltaFrameTime * m_velocity;
            }

            if(m_actions[A_MVDN])
            {
                pos -= TVector3::UNIT_Y * deltaFrameTime * m_velocity;
            }
        }

        m_targetVector = target;
        target += pos;

        m_camera->setPosition(pos);
        m_camera->setTarget(target);
        m_camera->updateAbsolutePosition();

        if(m_mode != pcmGod)
        {
            // dynamic world will accumulate...
            m_camera->setPosition(pos);
            m_camera->setTarget(target);
            m_camera->updateAbsolutePosition();
            m_ghostWalkDirection.setZero();
            core::matrix4 mat;
            mat.setRotationDegrees(rotation);
            if (gPlayerForwardBackward)
            {            
                btVector3 forwardDir(mat[8],mat[9],mat[10]);
                forwardDir.normalize();
                m_ghostWalkDirection += forwardDir*gPlayerForwardBackward;
            }
            if (gPlayerSideways)
            {
                btVector3 sideWays(mat[0],mat[1],mat[2]);
                sideWays.normalize();
                m_ghostWalkDirection += sideWays*gPlayerSideways;
            }            
        }

    }

    //-----------------------------------------------------------------------
    //                           u p d a t e U R
    //-----------------------------------------------------------------------
    void TPlayerController::updateUR(f32 deltaFrameTime)
    {
    }

    //-----------------------------------------------------------------------
    //                u p d a t e P l a y e r F r o m G h o s t
    //-----------------------------------------------------------------------
    void TPlayerController::updatePlayerFromGhost()
    {
        if(m_mode == pcmGod)
            return;

        btVector3 c = m_character->getGhostObject()->getWorldTransform().getOrigin();
        core::vector3df pos (c.getX(),c.getY()+m_characterHeight,c.getZ());
        m_camera->setPosition(pos);
        m_camera->setTarget(m_targetVector+pos);
	    m_camera->updateAbsolutePosition();
    }

    //-----------------------------------------------------------------------
    //                            u p d a t e
    //-----------------------------------------------------------------------
    void TPlayerController::update(float deltaFrameTime)
    {
        (this->*m_updater)(deltaFrameTime);
    }

}

