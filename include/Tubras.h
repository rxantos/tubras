//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#ifndef _TUBRAS_H_
#define _TUBRAS_H_

#define TUBRAS_VERSION_MAJOR 0
#define TUBRAS_VERSION_MINOR 1
#define TUBRAS_VERSION_STRING "0.1"
#define TUBRAS_VERSION_NAME "Abby"

#define _CRT_SECURE_NO_WARNINGS 1

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ios>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>


//
// Bullet
//
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btDefaultMotionState.h"
#include "LinearMath/btIDebugDraw.h"


//
//ois
//
//
// OIS
//
#include "ois.h"


//
// Irrlicht
//
#include <irrlicht.h>
#include <irrXML.h>
#define _IRR_COMPILE_WITH_IRRB_MESH_LOADER_ 1
#include "CIrrBMeshFileLoader.h"
#include "CIrrBMeshWriter.h"

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;
#include "TMemory.h"
#include "getopt.h"


#define TMap irr::core::map
#define TMapIterator irr::core::map::iterator
#define TList irr::core::list
#define TArray irr::core::array
typedef std::ostringstream TStrStream;
typedef std::string TStdString;
typedef irr::f32 TReal;

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 
#include "windows.h"
#endif

//#include "getopt.h"
#include <time.h>

namespace Tubras
{
    class TObject;
    class TState;
    class TApplication;
    class TXMLConfig;
    class TSceneNode;
    class TEventDelegate;
    class TSound;
    class TDynamicNode;
}

#include "TCompileConfig.h"
#include "TEnums.h"
#include "TSingleton.h"
#include "TString.h"
#include "TRandom.h"
#include "TTimer.h"
#include "TDimension.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TMatrix4.h"
#include "TAABBox.h"
#include "TRect.h"
#include "TMath.h"
#include "TIBConvert.h"
#include "TColour.h"
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
#include "TControllerManager.h"
#include "TInputBinder.h"
#include "TInputHandler.h"
#include "TInputManager.h"
#include "TXMLConfig.h"
#include "TSceneNode.h"
#include "TEmptyNode.h"
#include "TPlaneNode.h"
#include "TSoundNode.h"
#include "TCameraNode.h"
#include "TDynamicNode.h"
#include "TDebugNode.h"
#include "TNodeFactory.h"
#include "TState.h"
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
#include "TApplication.h"

#endif
