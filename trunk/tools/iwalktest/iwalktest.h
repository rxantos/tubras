//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _WALKTEST_H_
#define _WALKTEST_H_
#include "tubras.h"

using namespace Tubras;
class TWalktest : public TApplication
{
protected:
    TString                         m_sceneFileName;
    TArray<ISceneNode*>             m_cameras;
    TArray<IBillboardSceneNode*>    m_lights;
public:
    TWalktest();
    ~TWalktest();
    int initialize();
    int toggleDebug(const TEvent* event);
    int togglePhysicsDebug(const TEvent* event);
    int toggleHelp(const TEvent* event);
    int toggleWire(const TEvent* event);
    int cycleDebug(const TEvent* event);
    int cycleCamera(const TEvent* event);
    int captureScreen(const TEvent* event);
    int quit(const TEvent* event);
    void testInterval(double T, void* userData);

    void buildCameraList(ISceneNode* node);
    void buildLightList(ISceneNode* node);

	void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData);

    int testTask(TTask* task);

    io::IAttributes* createUserData(ISceneNode* forSceneNode) {return 0;}

};
#endif

