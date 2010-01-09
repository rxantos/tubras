//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _SANDBOX_H_
#define _SANDBOX_H_
#include "tubras.h"

using namespace Tubras;
class TSandbox : public TApplication
{
protected:
    TGUIScreen*         m_screen;
    TSound*             m_fire;
    TSound*             m_shot;
    TSound*             m_slide;
    TSound*             m_guiEnterSound;
    TSound*             m_guiExitSound;
    TSound*             m_guiClickSound;
    TSound*             m_guiClickSound2;
    f32                 m_velocity;
    u32                 m_fireCount;
    u32                 m_upID;
    TLineNode*          m_shooterLine;
    TTextOverlay*       m_irrInfo;
    TTextOverlay*       m_bulletInfo;
    TTask*              m_infoTask;
    TNodePosInterval*   m_openDoor;

    CGUISceneNode*      m_guiNode;
    CGUISceneNode*      m_guiNode2;
    IGUIImage*          m_crossHair;
    IGUIButton*         m_doorBell;
    IGUIScrollBar*      m_fireVelocity;
    IGUIScrollBar*      m_gxForce;
    IGUIScrollBar*      m_gyForce;
    IGUIScrollBar*      m_gzForce;
    IGUIStaticText*     m_sxForce;
    IGUIStaticText*     m_syForce;
    IGUIStaticText*     m_szForce;
    IGUIStaticText*     m_stVelocity;
    IGUICheckBox*       m_gravityEnabled;
    bool                m_guiNodeActivated;
    int                 m_doorState; // 0 - open, 1 - closed
    IMeshSceneNode*     m_door;
    TPhysicsObject*     m_poDoor;
    IMeshSceneNode*     m_wall;
    TPhysicsObject*     m_poWall;
    TRotateController*  m_guiNodeRot;
    TParticleNode*      m_particleNode;
    u32                 m_opMode; // 0 - 3d movement & gui, 1 - gui only

protected:
    void setupMatrixInfo();

public:
    TSandbox();
    ~TSandbox();
    int initialize();
    int toggleDebug(const TEvent* event);
    int cycleDebug(const TEvent* event);
    int togglePhysicsDebug(const TEvent* event);
    int toggleHelp(const TEvent* event);
    int toggleWire(const TEvent* event);
    int toggleTransform(const TEvent* event);
    int toggleCursor(const TEvent* event);
    int toggleGodMode(const TEvent* event);
    int toggleOpMode(const TEvent* event);
    int doorActionDone(const TEvent* event);
    int captureScreen(const TEvent* event);
    int quit(const TEvent* event);
    int onClick(const TEvent* event);
    int shootNode(const TEvent* event);
    int shootRay(const TEvent* event);
    void testInterval(double T, void* userData);
    int updateMatInfo(TTask* task);
    void setUserDebugInfo(TStringVector& debugStrings);

    bool OnEvent(const SEvent &  event);

    void preRender(f32 m_deltaTime);

	void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData);

    int testTask(TTask* task);

    io::IAttributes* createUserData(ISceneNode* forSceneNode) {return 0;}

};

#endif

