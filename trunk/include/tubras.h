//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TUBRAS_H_
#define _TUBRAS_H_

#define TUBRAS_VERSION_MAJOR 0
#define TUBRAS_VERSION_MINOR 1
#define TUBRAS_VERSION_STRING "0.1"
#define TUBRAS_VERSION_NAME "Abby"
#define VERSION 0x0001

#define _CRT_SECURE_NO_WARNINGS 1

#include "TCompileConfig.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ios>
#include <algorithm>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>


//
// Bullet
//
#ifdef TUBRAS_INCLUDE_PHYSICS
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btIDebugDraw.h>
#endif

//
// Particle2
//
#include <pAPI.h>
#include <Particle.h>

//
// Irrlicht
//
#include <irrlicht.h>
#include <irrXML.h>
#include <clsl.h>
using namespace lsl;

#ifdef _IRR_WINDOWS_
#define TUBRAS_PLATFORM_WIN32
#endif

#ifdef _IRR_LINUX_PLATFORM_
#define TUBRAS_PLATFORM_LINUX
#endif

#ifdef _IRR_OSX_PLATFORM_
#define TUBRAS_PLATFORM_OSX
#endif

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

#define _IRR_COMPILE_WITH_IRRB_MESH_LOADER_ 1
#include "CIrrBMeshFileLoader.h"
#include "CIrrBMeshWriter.h"
#include "CIrrMeshFileLoader.h"

#ifdef _DEBUG
#include "TMemory.h"
#endif
#include "getopt.h"


#define TMap irr::core::map
#define TMapIterator irr::core::map::iterator
#define TList irr::core::list
#define TArray irr::core::array
typedef std::ostringstream TStrStream;
typedef std::string TStdString;
typedef irr::f32 TReal;

#ifdef TUBRAS_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "windows.h"
#endif

//#include "getopt.h"
#include <time.h>

namespace Tubras
{
    class TObject;
    class TState;
    class TApplication;
    class TSceneNode;
    class TCameraNode;
    class TEventDelegate;
    class TSound;
    class TDynamicNode;
    class TParticleNode;
    class TControllerManager;
    class TParticleManager;
    class TRenderer;
    class TGUIFactory;
}

#include "TEnums.h"
#include "TSingleton.h"
#include "TString.h"
#include "TRandom.h"
#include "TTimer.h"
#include "TDimension.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TMatrix4.h"
#include "TQuaternion.h"
#include "TAABBox.h"
#include "TRect.h"
#include "TMath.h"
#include "TIBConvert.h"
#include "TColor.h"
#include "TVertex.h"
#include "TRay.h"
#include "TRayResult.h"
#include "TObject.h"
#include "TFile.h"
#include "TLogger.h"
#include "TDelegate.h"
#include "TEventDelegate.h"
#include "TEventParameter.h"
#include "TEvent.h"
#include "TEventQueue.h"
#include "TEventManager.h"
#include "TEventDelegate.h"
#include "TTaskDelegate.h"
#include "TTask.h"
#include "TTaskManager.h"
#include "TControllerFunction.h"
#include "TController.h"
#include "TRotateController.h"
#include "TOscillateController.h"
#include "TIntervalDelegate.h"
#include "TIntervalController.h"
#include "TShakeController.h"
#include "TControllerManager.h"
#include "TInputBinder.h"
#include "TInputHandler.h"
#include "TInputManager.h"
#include "TParticle.h"
#include "TParticleDomain.h"
#include "TParticleAction.h"
#include "TParticleManager.h"
#include "TSceneNode.h"
#include "TEmptyNode.h"
#include "TPlaneNode.h"
#include "TBackgroundNode.h"
#include "TLineNode.h"
#include "TAxisNode.h"
#include "TSoundNode.h"
#include "TCameraNode.h"
#include "TDynamicNode.h"
#include "TDebugNode.h"
#include "TParticleNode.h"
#include "TNodeFactory.h"
#include "TState.h"
#include "TGUIButton.h"
#include "TGUISlider.h"
#include "TGUIWindow.h"
#include "TGUIDialogs.h"
#include "TGUIFactory.h"
#include "TGUISkin.h"
#include "TGUISkin2.h"
#include "TGUIScreen.h"
#include "TRenderer.h"
#include "TOverlay.h"
#include "TTextOverlay.h"
#include "TPlayerController.h"
#include "TSound.h"
#include "TSoundManager.h"
#include "TNullSound.h"
#include "TNullSoundManager.h"
#ifdef USE_FMOD_SOUND
#include "TFMSound.h"
#include "TFMSoundManager.h"
#elif USE_IRR_SOUND
#include "TIrrSound.h"
#include "TIrrSoundManager.h"
#endif
#include "TMotionState.h"
#include "TRigidBody.h"
#include "TDynamicWorld.h"
#include "TColliderShape.h"
#include "TColliderBox.h"
#include "TColliderPlane.h"
#include "TColliderSphere.h"
#include "TColliderCylinder.h"
#include "TColliderCone.h"
#include "TColliderMesh.h"
#include "TPhysicsManager.h"

// #include lua headers
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lapi.h"

#include "ldo.h"
#include "lfunc.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lstring.h"
#include "lundump.h"
}

#include "TScript.h"
#include "TScriptManager.h"
#include "TSceneLoader.h"
#include "TApplication.h"


#ifdef TUBRAS_PLATFORM_WIN32
#ifdef _DEBUG
#pragma comment(lib, "Tubras_d.lib")
#pragma comment(lib, "Irrlicht.lib") 
#else
#pragma comment(lib, "Tubras.lib")
#pragma comment(lib, "Irrlicht.lib")
#endif
#endif

#endif
