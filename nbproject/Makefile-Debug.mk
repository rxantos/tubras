#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=

# Macros
PLATFORM=MinGW-Windows

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/TSceneNode.o \
	${OBJECTDIR}/src/TEventQueue.o \
	${OBJECTDIR}/src/TNullSound.o \
	${OBJECTDIR}/src/swig/tubras_wrap_lua.o \
	${OBJECTDIR}/src/TEventManager.o \
	${OBJECTDIR}/src/TColor.o \
	${OBJECTDIR}/src/TInputBinder.o \
	${OBJECTDIR}/src/TTimer.o \
	${OBJECTDIR}/src/TColliderShape.o \
	${OBJECTDIR}/src/TLineNode.o \
	${OBJECTDIR}/src/TTask.o \
	${OBJECTDIR}/src/TObject.o \
	${OBJECTDIR}/src/TGUIScreen.o \
	${OBJECTDIR}/src/TIntervalDelegate.o \
	${OBJECTDIR}/src/TMemory.o \
	${OBJECTDIR}/src/TLUAScript.o \
	${OBJECTDIR}/src/TVertex.o \
	${OBJECTDIR}/src/TAABBox.o \
	${OBJECTDIR}/src/TGUIFactory.o \
	${OBJECTDIR}/src/TPlaneNode.o \
	${OBJECTDIR}/src/TFile.o \
	${OBJECTDIR}/src/TTaskManager.o \
	${OBJECTDIR}/src/TColliderCylinder.o \
	${OBJECTDIR}/src/TColliderCone.o \
	${OBJECTDIR}/src/TDynamicNode.o \
	${OBJECTDIR}/src/TPlayerController.o \
	${OBJECTDIR}/src/TNodeFactory.o \
	${OBJECTDIR}/src/TRayResult.o \
	${OBJECTDIR}/src/TFMSound.o \
	${OBJECTDIR}/src/TSoundNode.o \
	${OBJECTDIR}/src/TIrrSound.o \
	${OBJECTDIR}/src/TCameraNode.o \
	${OBJECTDIR}/src/TRandom.o \
	${OBJECTDIR}/src/TColliderPlane.o \
	${OBJECTDIR}/src/TGUISlider.o \
	${OBJECTDIR}/src/TVector2.o \
	${OBJECTDIR}/src/CIrrBMeshFileLoader.o \
	${OBJECTDIR}/src/CIrrBMeshWriter.o \
	${OBJECTDIR}/src/TTaskDelegate.o \
	${OBJECTDIR}/src/TRotateController.o \
	${OBJECTDIR}/src/TApplication.o \
	${OBJECTDIR}/src/TOverlay.o \
	${OBJECTDIR}/src/TSceneLoader.o \
	${OBJECTDIR}/src/TNullSoundManager.o \
	${OBJECTDIR}/src/TColliderBox.o \
	${OBJECTDIR}/src/TGUISkin.o \
	${OBJECTDIR}/src/TLogger.o \
	${OBJECTDIR}/src/TInputHandler.o \
	${OBJECTDIR}/src/TSound.o \
	${OBJECTDIR}/src/getopt.o \
	${OBJECTDIR}/src/TVector3.o \
	${OBJECTDIR}/src/TDebugNode.o \
	${OBJECTDIR}/src/TInputManager.o \
	${OBJECTDIR}/src/Tubras.o \
	${OBJECTDIR}/src/TMotionState.o \
	${OBJECTDIR}/src/TShakeController.o \
	${OBJECTDIR}/src/TGUIButton.o \
	${OBJECTDIR}/src/TScriptManager.o \
	${OBJECTDIR}/src/TGUIWindow.o \
	${OBJECTDIR}/src/TOscillateController.o \
	${OBJECTDIR}/src/TController.o \
	${OBJECTDIR}/src/TEmptyNode.o \
	${OBJECTDIR}/src/TEvent.o \
	${OBJECTDIR}/src/TBackgroundNode.o \
	${OBJECTDIR}/src/TGUISkin2.o \
	${OBJECTDIR}/src/TDynamicWorld.o \
	${OBJECTDIR}/src/TColliderSphere.o \
	${OBJECTDIR}/src/TFMSoundManager.o \
	${OBJECTDIR}/src/TEventDelegate.o \
	${OBJECTDIR}/src/TTextOverlay.o \
	${OBJECTDIR}/src/TMath.o \
	${OBJECTDIR}/src/TControllerManager.o \
	${OBJECTDIR}/src/TRigidBody.o \
	${OBJECTDIR}/src/TColliderMesh.o \
	${OBJECTDIR}/src/TControllerFunction.o \
	${OBJECTDIR}/src/TAxisNode.o \
	${OBJECTDIR}/src/TState.o \
	${OBJECTDIR}/src/TPhysicsManager.o \
	${OBJECTDIR}/src/TIntervalController.o \
	${OBJECTDIR}/src/TRay.o \
	${OBJECTDIR}/src/TRenderer.o \
	${OBJECTDIR}/src/TSoundManager.o \
	${OBJECTDIR}/src/TQuaternion.o \
	${OBJECTDIR}/src/TIrrSoundManager.o \
	${OBJECTDIR}/src/TGUIDialogs.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/${PLATFORM}/libTubras.a

dist/Debug/${PLATFORM}/libTubras.a: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/${PLATFORM}
	${RM} dist/Debug/${PLATFORM}/libTubras.a
	${AR} rv dist/Debug/${PLATFORM}/libTubras.a ${OBJECTFILES} 
	$(RANLIB) dist/Debug/${PLATFORM}/libTubras.a

${OBJECTDIR}/src/TSceneNode.o: src/TSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSceneNode.o src/TSceneNode.cpp

${OBJECTDIR}/src/TEventQueue.o: src/TEventQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEventQueue.o src/TEventQueue.cpp

${OBJECTDIR}/src/TNullSound.o: src/TNullSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TNullSound.o src/TNullSound.cpp

${OBJECTDIR}/src/swig/tubras_wrap_lua.o: src/swig/tubras_wrap_lua.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/swig
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/swig/tubras_wrap_lua.o src/swig/tubras_wrap_lua.cpp

${OBJECTDIR}/src/TEventManager.o: src/TEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEventManager.o src/TEventManager.cpp

${OBJECTDIR}/src/TColor.o: src/TColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColor.o src/TColor.cpp

${OBJECTDIR}/src/TInputBinder.o: src/TInputBinder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TInputBinder.o src/TInputBinder.cpp

${OBJECTDIR}/src/TTimer.o: src/TTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTimer.o src/TTimer.cpp

${OBJECTDIR}/src/TColliderShape.o: src/TColliderShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderShape.o src/TColliderShape.cpp

${OBJECTDIR}/src/TLineNode.o: src/TLineNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TLineNode.o src/TLineNode.cpp

${OBJECTDIR}/src/TTask.o: src/TTask.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTask.o src/TTask.cpp

${OBJECTDIR}/src/TObject.o: src/TObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TObject.o src/TObject.cpp

${OBJECTDIR}/src/TGUIScreen.o: src/TGUIScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIScreen.o src/TGUIScreen.cpp

${OBJECTDIR}/src/TIntervalDelegate.o: src/TIntervalDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TIntervalDelegate.o src/TIntervalDelegate.cpp

${OBJECTDIR}/src/TMemory.o: src/TMemory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TMemory.o src/TMemory.cpp

${OBJECTDIR}/src/TLUAScript.o: src/TLUAScript.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TLUAScript.o src/TLUAScript.cpp

${OBJECTDIR}/src/TVertex.o: src/TVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TVertex.o src/TVertex.cpp

${OBJECTDIR}/src/TAABBox.o: src/TAABBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TAABBox.o src/TAABBox.cpp

${OBJECTDIR}/src/TGUIFactory.o: src/TGUIFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIFactory.o src/TGUIFactory.cpp

${OBJECTDIR}/src/TPlaneNode.o: src/TPlaneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TPlaneNode.o src/TPlaneNode.cpp

${OBJECTDIR}/src/TFile.o: src/TFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TFile.o src/TFile.cpp

${OBJECTDIR}/src/TTaskManager.o: src/TTaskManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTaskManager.o src/TTaskManager.cpp

${OBJECTDIR}/src/TColliderCylinder.o: src/TColliderCylinder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderCylinder.o src/TColliderCylinder.cpp

${OBJECTDIR}/src/TColliderCone.o: src/TColliderCone.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderCone.o src/TColliderCone.cpp

${OBJECTDIR}/src/TDynamicNode.o: src/TDynamicNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TDynamicNode.o src/TDynamicNode.cpp

${OBJECTDIR}/src/TPlayerController.o: src/TPlayerController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TPlayerController.o src/TPlayerController.cpp

${OBJECTDIR}/src/TNodeFactory.o: src/TNodeFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TNodeFactory.o src/TNodeFactory.cpp

${OBJECTDIR}/src/TRayResult.o: src/TRayResult.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRayResult.o src/TRayResult.cpp

${OBJECTDIR}/src/TFMSound.o: src/TFMSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TFMSound.o src/TFMSound.cpp

${OBJECTDIR}/src/TSoundNode.o: src/TSoundNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSoundNode.o src/TSoundNode.cpp

${OBJECTDIR}/src/TIrrSound.o: src/TIrrSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TIrrSound.o src/TIrrSound.cpp

${OBJECTDIR}/src/TCameraNode.o: src/TCameraNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TCameraNode.o src/TCameraNode.cpp

${OBJECTDIR}/src/TRandom.o: src/TRandom.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRandom.o src/TRandom.cpp

${OBJECTDIR}/src/TColliderPlane.o: src/TColliderPlane.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderPlane.o src/TColliderPlane.cpp

${OBJECTDIR}/src/TGUISlider.o: src/TGUISlider.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUISlider.o src/TGUISlider.cpp

${OBJECTDIR}/src/TVector2.o: src/TVector2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TVector2.o src/TVector2.cpp

${OBJECTDIR}/src/CIrrBMeshFileLoader.o: src/CIrrBMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/CIrrBMeshFileLoader.o src/CIrrBMeshFileLoader.cpp

${OBJECTDIR}/src/CIrrBMeshWriter.o: src/CIrrBMeshWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/CIrrBMeshWriter.o src/CIrrBMeshWriter.cpp

${OBJECTDIR}/src/TTaskDelegate.o: src/TTaskDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTaskDelegate.o src/TTaskDelegate.cpp

${OBJECTDIR}/src/TRotateController.o: src/TRotateController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRotateController.o src/TRotateController.cpp

${OBJECTDIR}/src/TApplication.o: src/TApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TApplication.o src/TApplication.cpp

${OBJECTDIR}/src/TOverlay.o: src/TOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TOverlay.o src/TOverlay.cpp

${OBJECTDIR}/src/TSceneLoader.o: src/TSceneLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSceneLoader.o src/TSceneLoader.cpp

${OBJECTDIR}/src/TNullSoundManager.o: src/TNullSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TNullSoundManager.o src/TNullSoundManager.cpp

${OBJECTDIR}/src/TColliderBox.o: src/TColliderBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderBox.o src/TColliderBox.cpp

${OBJECTDIR}/src/TGUISkin.o: src/TGUISkin.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUISkin.o src/TGUISkin.cpp

${OBJECTDIR}/src/TLogger.o: src/TLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TLogger.o src/TLogger.cpp

${OBJECTDIR}/src/TInputHandler.o: src/TInputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TInputHandler.o src/TInputHandler.cpp

${OBJECTDIR}/src/TSound.o: src/TSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSound.o src/TSound.cpp

${OBJECTDIR}/src/getopt.o: src/getopt.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/getopt.o src/getopt.cpp

${OBJECTDIR}/src/TVector3.o: src/TVector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TVector3.o src/TVector3.cpp

${OBJECTDIR}/src/TDebugNode.o: src/TDebugNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TDebugNode.o src/TDebugNode.cpp

${OBJECTDIR}/src/TInputManager.o: src/TInputManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TInputManager.o src/TInputManager.cpp

${OBJECTDIR}/src/Tubras.o: src/Tubras.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/Tubras.o src/Tubras.cpp

${OBJECTDIR}/src/TMotionState.o: src/TMotionState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TMotionState.o src/TMotionState.cpp

${OBJECTDIR}/src/TShakeController.o: src/TShakeController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TShakeController.o src/TShakeController.cpp

${OBJECTDIR}/src/TGUIButton.o: src/TGUIButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIButton.o src/TGUIButton.cpp

${OBJECTDIR}/src/TScriptManager.o: src/TScriptManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TScriptManager.o src/TScriptManager.cpp

${OBJECTDIR}/src/TGUIWindow.o: src/TGUIWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIWindow.o src/TGUIWindow.cpp

${OBJECTDIR}/src/TOscillateController.o: src/TOscillateController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TOscillateController.o src/TOscillateController.cpp

${OBJECTDIR}/src/TController.o: src/TController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TController.o src/TController.cpp

${OBJECTDIR}/src/TEmptyNode.o: src/TEmptyNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEmptyNode.o src/TEmptyNode.cpp

${OBJECTDIR}/src/TEvent.o: src/TEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEvent.o src/TEvent.cpp

${OBJECTDIR}/src/TBackgroundNode.o: src/TBackgroundNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TBackgroundNode.o src/TBackgroundNode.cpp

${OBJECTDIR}/src/TGUISkin2.o: src/TGUISkin2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUISkin2.o src/TGUISkin2.cpp

${OBJECTDIR}/src/TDynamicWorld.o: src/TDynamicWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TDynamicWorld.o src/TDynamicWorld.cpp

${OBJECTDIR}/src/TColliderSphere.o: src/TColliderSphere.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderSphere.o src/TColliderSphere.cpp

${OBJECTDIR}/src/TFMSoundManager.o: src/TFMSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TFMSoundManager.o src/TFMSoundManager.cpp

${OBJECTDIR}/src/TEventDelegate.o: src/TEventDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEventDelegate.o src/TEventDelegate.cpp

${OBJECTDIR}/src/TTextOverlay.o: src/TTextOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTextOverlay.o src/TTextOverlay.cpp

${OBJECTDIR}/src/TMath.o: src/TMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TMath.o src/TMath.cpp

${OBJECTDIR}/src/TControllerManager.o: src/TControllerManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TControllerManager.o src/TControllerManager.cpp

${OBJECTDIR}/src/TRigidBody.o: src/TRigidBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRigidBody.o src/TRigidBody.cpp

${OBJECTDIR}/src/TColliderMesh.o: src/TColliderMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderMesh.o src/TColliderMesh.cpp

${OBJECTDIR}/src/TControllerFunction.o: src/TControllerFunction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TControllerFunction.o src/TControllerFunction.cpp

${OBJECTDIR}/src/TAxisNode.o: src/TAxisNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TAxisNode.o src/TAxisNode.cpp

${OBJECTDIR}/src/TState.o: src/TState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TState.o src/TState.cpp

${OBJECTDIR}/src/TPhysicsManager.o: src/TPhysicsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TPhysicsManager.o src/TPhysicsManager.cpp

${OBJECTDIR}/src/TIntervalController.o: src/TIntervalController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TIntervalController.o src/TIntervalController.cpp

${OBJECTDIR}/src/TRay.o: src/TRay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRay.o src/TRay.cpp

${OBJECTDIR}/src/TRenderer.o: src/TRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRenderer.o src/TRenderer.cpp

${OBJECTDIR}/src/TSoundManager.o: src/TSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSoundManager.o src/TSoundManager.cpp

${OBJECTDIR}/src/TQuaternion.o: src/TQuaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TQuaternion.o src/TQuaternion.cpp

${OBJECTDIR}/src/TIrrSoundManager.o: src/TIrrSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TIrrSoundManager.o src/TIrrSoundManager.cpp

${OBJECTDIR}/src/TGUIDialogs.o: src/TGUIDialogs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIDialogs.o src/TGUIDialogs.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/${PLATFORM}/libTubras.a

# Subprojects
.clean-subprojects:
