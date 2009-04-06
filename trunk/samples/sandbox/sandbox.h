//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
    TSound*             m_guiEnterSound;
    TSound*             m_guiExitSound;
    f32                 m_velocity;
    u32                 m_fireCount;
    u32                 m_upID;
    TLineNode*          m_shooterLine;
    TTextOverlay*       m_irrInfo;
    TTextOverlay*       m_bulletInfo;
    TTask*              m_infoTask;
    CGUISceneNode*      m_guiNode;
    IGUIImage*          m_crossHair;
    bool                m_guiNodeActivated;



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
    int captureScreen(const TEvent* event);
    int quit(const TEvent* event);
    int onClick(const TEvent* event);
    int shootNode(const TEvent* event);
    int shootRay(const TEvent* event);
    void testInterval(double T, void* userData);
    int updateMatInfo(TTask* task);
    void setUserDebugInfo(TStringVector& debugStrings);

    bool OnEvent(const SEvent &  event);


	void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData);

    int testTask(TTask* task);

    io::IAttributes* createUserData(ISceneNode* forSceneNode) {return 0;}

};

#endif

