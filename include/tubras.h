//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// To the loving memory of my mother - Barbara Murray. She peacefully left this
// earthly life on June 13, 2009. Love you always. 
//-----------------------------------------------------------------------------
#ifndef _TUBRAS_H_
#define _TUBRAS_H_

#define TUBRAS_VERSION_MAJOR 0
#define TUBRAS_VERSION_MINOR 1
#define TUBRAS_VERSION_STRING "0.1"
#define TUBRAS_VERSION_NAME "Abby"
#define VERSION 0x0001

#define _CRT_SECURE_NO_WARNINGS 1

#define LOG_ERROR   1
#define LOG_WARNING 2
#define LOG_INFO    4
#define LOG_EVENT   8

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
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btConvexHull.h>
#include <../Extras/ConvexDecomposition/ConvexDecomposition.h>
#include <../Extras/ConvexDecomposition/ConvexBuilder.h>

//
// Irrlicht
//
#include <irrlicht.h>
#include <irrXML.h>

#ifdef _IRR_WINDOWS_
#define TUBRAS_PLATFORM_WINDOWS
#endif

#ifdef _IRR_LINUX_PLATFORM_
#define TUBRAS_PLATFORM_LINUX
#endif

#ifdef _IRR_OSX_PLATFORM_
#define TUBRAS_PLATFORM_OSX
#endif

// LUA
#define luac_c
#define LUA_CORE
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

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

#include "TLuaProxy.h"

#define _IRR_COMPILE_WITH_IRRB_MESH_LOADER_ 1
#include "CIrrBMeshFileLoader.h"
#include "CIrrBMeshWriter.h"
#include "CIrrMeshFileLoader.h"
#include "CGUISceneNode.h"
#include "CSceneNodeAnimatorCollisionResponse.h"

// timing framework includes
#include "ITimingEventListener.h"
#include "ITimingSource.h"
#include "IEvaluator.h"
#include "IInterpolator.h"
#include "ITimingTarget.h"
#include "IAnimator.h"
#include "CTimingSource.h"
#include "CKeyTimes.h"
#include "CKeyValues.h"
#include "CLinearInterpolator.h"
#include "CKeyInterpolators.h"
#include "CDiscreteInterpolator.h"  
#include "CSplineInterpolator.h"
#include "CSineInterpolator.h"
#include "CKeyFrames.h"
#include "CAnimator.h"
#include "CPropertySetter.h"
#include "CTimingManager.h"

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

#ifdef TUBRAS_PLATFORM_WINDOWS
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
    class TState;
    class TApplication;
    class TSceneNode;
    class TCameraNode;
    class TEventDelegate;
    class TSound;
    class TPhysicsObject;
    class TControllerManager;
    class TRenderer;
    class TGUIFactory;
    class TSceneNodeAnimatorMaterialLayer;
    class IBehavior;
    class TEntity;
    class TGUICursor;
    class TGUIImage;
    class TKinematicCharacter;
    class TKinematicCharacterTest;
    class TCollisionShape;
    class TParticleManager;
}
#include "TEnums.h"
#include "TString.h"
#include "TConfig.h"
#include "TRandom.h"
#include "TTimer.h"
#include "TProfile.h"
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
#include "TParticleManager.h"
#include "TSceneNode.h"
#include "TEmptyNode.h"
#include "TPlaneNode.h"
#include "TBackgroundNode.h"
#include "TLineNode.h"
#include "TAxisNode.h"
#include "TSoundNode.h"
#include "TCameraNode.h"
#include "TDebugNode.h"
#include "TSceneNodeAnimatorMaterialLayer.h"
#include "TState.h"
#include "TGUIImage.h"
#include "TGUICursor.h"
#include "TGUIButton.h"
#include "TGUISlider.h"
#include "TGUICmdEdit.h"
#include "TGUIWindow.h"
#include "TGUIDialogs.h"
#include "TGUIConsole.h"
#include "TGUIInfo.h"
#include "TGUIFactory.h"
#include "TGUISkin.h"
#include "TGUIScreen.h"
#include "TRenderer.h"
#include "TOverlay.h"
#include "TTextOverlay.h"
#include "TCharacterController.h"
#include "TSound.h"
#include "TSoundManager.h"
#include "TNullSound.h"
#include "TNullSoundManager.h"
#ifdef USE_SOUND_FMOD
#include "TFMSound.h"
#include "TFMSoundManager.h"
#elif USE_SOUND_IRR
#include "TIrrSound.h"
#include "TIrrSoundManager.h"
#endif
#include "TPhysicsObject.h"
#include "TKinematicCharacter.h"
#include "TKinematicCharacterTest.h"
#include "TCollisionShapes.h"
#include "TPhysicsManager.h"

#include "IListener.h"
#include "TProperties.h"
#include "IBehavior.h"
#include "TBehavior.h"
#include "IBehaviorFactory.h"
#include "TBehaviorFactory.h"
#include "TEntity.h"
#include "TEntityManager.h"
#include "TBStaticMesh.h"
#include "TBView.h"
#include "TBRotation.h"

#include "TScriptState.h"
#include "TScript.h"
#include "TScriptManager.h"
#include "TSceneLoader.h"
#include "TApplication.h"


#ifdef TUBRAS_PLATFORM_WINDOWS
#ifdef _DEBUG
#pragma comment(lib, "Tubras_d.lib")
#else
#pragma comment(lib, "Tubras.lib")
#endif
#endif

#endif
