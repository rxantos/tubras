//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _WALKTEST_H_
#define _WALKTEST_H_
#include "tubras.h"

using namespace Tubras;

typedef struct 
{
    ISceneNode*     node;
    E_MATERIAL_TYPE orgType;
    u32             idx;
} LMInfo, *PLMInfo;

class TWalktest : public TApplication
{
protected:
    Tubras::TString                 m_sceneFileName;
    TArray<ISceneNode*>             m_cameras;
    TArray<IBillboardSceneNode*>    m_lights;
    TArray<PLMInfo>                 m_lightMaps;
    bool                            m_lightsVisible;
    bool                            m_lightMapsVisible;
    bool                            m_useIrrlichtCollision;
    io::IAttributes*                m_sceneAttributes;
    u32                             m_dbgTriggerIndex;
public:
    TWalktest();
    ~TWalktest();
    int initialize();
    int toggleDebug(const TEvent* event);
    int toggleDebugLights(const TEvent* event);
    int toggleLightMaps(const TEvent* event);
    int togglePhysicsDebug(const TEvent* event);
    int toggleHelp(const TEvent* event);
    int toggleWire(const TEvent* event);
    int cycleDebug(const TEvent* event);
    int cycleCamera(const TEvent* event);
    int toggleGod(const TEvent* event);
    int captureScreen(const TEvent* event);
    int quit(const TEvent* event);
    int handleTrigger(const TEvent* event);
    void testInterval(double T, void* userData);

    void buildCameraList(ISceneNode* node);
    void buildLightList(ISceneNode* node);
    void buildLMList(ISceneNode* node);

    void createPhysicsObject(IMeshSceneNode* mnode, io::IAttributes* userData);

	void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData);

    int testTask(TTask* task);

    io::IAttributes* createUserData(ISceneNode* forSceneNode) {return 0;}

};
#endif

