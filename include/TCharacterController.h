//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TCHARACTERCONTROLLER_H_
#define _TCHARACTERCONTROLLER_H_

namespace Tubras
{
    /**
    TCharacterController Class.
    @remarks
    Controller class.

    Creating a controller automatically registers it with the Controller Manager.  The manager 
    automatically deletes registered controllers when the manager itself is destroyed.

    If you would like to remove a controller that is no longer needed:
    1. Invoke TControllerManager::remove()
    2. Delete the controller manually
    */

    class TCharacterController : public TController
    {
        friend class TPhysicsManager;
        typedef void (TCharacterController::*TPCUpdateDelegate)(const f32);
    public:
        enum Actions {
            A_FRWD=0,           // move forward
            A_BACK=1,           // move backward
            A_LEFT=2,           // move left
            A_RGHT=3,           // move right
            A_ROTR=4,           // rotate right
            A_ROTL=5,           // rotate left
            A_MVUP=6,           // move up
            A_MVDN=7,           // move down
            A_ROTF=8,           // rotate forward
            A_ROTB=9,           // rotate backward
            A_AVEL=10,          // adjust velocity
            A_JUMP=11,          // jump
            A_LAST
        };
    private:
        TCharacterControllerMode   m_mode;
        TPCUpdateDelegate       m_updater;
        ICameraSceneNode*       m_camera;
        TEventDelegate*         m_cmdDelegate;
        TEventDelegate*         m_mouseMoveDelegate;
        TEventDelegate*         m_mouseButtonDelegate;
        TVector3                m_targetVector;
        TVector3                m_translate;
        btVector3               m_ghostWalkDirection;
        TKinematicCharacter*    m_character;
        btPairCachingGhostObject* m_ghostObject;
        TInputHandler*          m_inputHandler;
        f32					    m_pitch;
        f32					    m_rotate;
        f32                     m_velocity;
        f32                     m_velDamp;
        f32                     m_orgVelocity;
        f32                     m_shift;
        f32					    m_angularVelocity;
        f32                     m_mouseX;
        f32                     m_mouseY;
        f32                     m_inverted;
        f32                     m_maxVertAngle;
        f32                     m_characterWidth;
        f32                     m_characterHeight;
        f32                     m_characterStepHeight;
        f32                     m_characterJumpSpeed;
        f32                     m_fDampTime,m_bDampTime;
        u32                     m_fDampDir,m_bDampDir;
        bool                    m_fDamping,m_bDamping;
        bool                    m_lButtonDown;
        bool                    m_irrlichtCollision;
        bool					m_translating;
        bool					m_pitching;
        bool					m_rotating;
        bool                    m_mouseMoved;
        bool                    m_zoomed;
        bool                    m_actions[A_LAST];
        bool                    m_movementEnabled;
        bool                    m_mouseMovementEnabled;

        size_t                  m_frwdID,m_backID;
        size_t                  m_leftID, m_rghtID;
        size_t                  m_mvupID, m_mvdnID;
        size_t                  m_rotfID, m_rotbID;
        size_t                  m_rotrID, m_rotlID;
        size_t                  m_jumpID;
        size_t                  m_zoomID;
        size_t                  m_avelID;
        size_t                  m_invertMouseID,m_toggleMouseID;
        size_t                  m_zoomedInID, m_zoomedOutID;

    private:
        int procCmd(TEvent* event);
        int procMouseMove(TEvent* event);
        int procMouseButton(TEvent* event);
        void procZoom(double T, void* userData);
        void updateFPS(f32 deltaFrameTime);
        void updateUR(f32 deltaFrameTime);
        void updatePlayerFromGhost();
        const btVector3& getGhostWalkDirection() {return m_ghostWalkDirection;}

    public:

        TCharacterController(const TString& controllerName,
            ICameraSceneNode* camera,  TCharacterControllerMode mode=ccmFirstPerson, 
            ISceneNode* playerNode=0);
        virtual ~TCharacterController();

        virtual void enableMovement(bool value);
        virtual void enableMouseMovement(bool enable);

        virtual TCharacterControllerMode getMode() {return m_mode;}
        virtual void setMode(TCharacterControllerMode value);

        virtual void setPosition(TVector3 value);

        void setVelocity(f32 value) {m_velocity = value;};
        f32 getVelocity() {return m_velocity;};

        void setAngularVelocity(f32 value) {m_angularVelocity = value;};
        f32 getAngularVelocity() {return m_angularVelocity;};

        ICameraSceneNode* setCamera(ICameraSceneNode* camera);

        f32 getJumpSpeed() {return m_characterJumpSpeed;}

        TKinematicCharacter* getCharacter() {return m_character;}
        btPairCachingGhostObject* getGhostObject() {return m_ghostObject;}

        ISceneNode* getCharacterSceneNode() {return m_camera;}

        void update(f32 deltaFrameTime);
    };
}
#endif
