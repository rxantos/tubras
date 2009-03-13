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
CC=gcc
CCC=g++
CXX=g++
FC=

# Macros
PLATFORM=MinGW-Windows

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Win32-Debug/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.o \
	${OBJECTDIR}/src/TSceneNode.o \
	${OBJECTDIR}/src/TEventManager.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.o \
	${OBJECTDIR}/src/TTask.o \
	${OBJECTDIR}/src/TObject.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.o \
	${OBJECTDIR}/tools/lsl/src/lua/ldebug.o \
	${OBJECTDIR}/src/TColliderCylinder.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.o \
	${OBJECTDIR}/tools/lsl/src/lua/lcode.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.o \
	${OBJECTDIR}/src/TColliderPlane.o \
	${OBJECTDIR}/tools/lsl/src/lua/ldump.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.o \
	${OBJECTDIR}/tools/lsl/src/lua/lundump.o \
	${OBJECTDIR}/src/TInputHandler.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.o \
	${OBJECTDIR}/src/Tubras.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.o \
	${OBJECTDIR}/src/TMotionState.o \
	${OBJECTDIR}/src/TShakeController.o \
	${OBJECTDIR}/src/TEvent.o \
	${OBJECTDIR}/tools/lsl/src/lua/lapi.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.o \
	${OBJECTDIR}/src/TGUISkin2.o \
	${OBJECTDIR}/tools/lsl/src/lua/lmathlib.o \
	${OBJECTDIR}/tools/lsl/src/lua/loadlib.o \
	${OBJECTDIR}/tools/lsl/src/lua/lgc.o \
	${OBJECTDIR}/src/TTextOverlay.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.o \
	${OBJECTDIR}/tools/lsl/src/lua/lfunc.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.o \
	${OBJECTDIR}/deps/bullet/src/LinearMath/btQuickprof.o \
	${OBJECTDIR}/src/TAxisNode.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.o \
	${OBJECTDIR}/tools/lsl/src/lua/lstring.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.o \
	${OBJECTDIR}/src/TNullSound.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.o \
	${OBJECTDIR}/src/TColor.o \
	${OBJECTDIR}/src/TColliderShape.o \
	${OBJECTDIR}/src/TLineNode.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.o \
	${OBJECTDIR}/src/TTaskManager.o \
	${OBJECTDIR}/tools/lsl/src/lua/ltable.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.o \
	${OBJECTDIR}/tools/lsl/src/lua/lopcodes.o \
	${OBJECTDIR}/src/TRayResult.o \
	${OBJECTDIR}/src/TFMSound.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.o \
	${OBJECTDIR}/src/TGUISlider.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.o \
	${OBJECTDIR}/src/TVector2.o \
	${OBJECTDIR}/src/CIrrBMeshFileLoader.o \
	${OBJECTDIR}/src/CIrrBMeshWriter.o \
	${OBJECTDIR}/src/TTaskDelegate.o \
	${OBJECTDIR}/src/TOverlay.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.o \
	${OBJECTDIR}/src/TGUISkin.o \
	${OBJECTDIR}/src/TLogger.o \
	${OBJECTDIR}/src/getopt.o \
	${OBJECTDIR}/src/TVector3.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.o \
	${OBJECTDIR}/tools/lsl/src/lua/lauxlib.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.o \
	${OBJECTDIR}/src/TController.o \
	${OBJECTDIR}/src/TEmptyNode.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.o \
	${OBJECTDIR}/src/TBackgroundNode.o \
	${OBJECTDIR}/deps/bullet/src/LinearMath/btGeometryUtil.o \
	${OBJECTDIR}/tools/lsl/src/lua/lstate.o \
	${OBJECTDIR}/src/TDynamicWorld.o \
	${OBJECTDIR}/src/TColliderSphere.o \
	${OBJECTDIR}/tools/lsl/src/lua/ldblib.o \
	${OBJECTDIR}/tools/lsl/src/lua/lstrlib.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.o \
	${OBJECTDIR}/src/TRigidBody.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.o \
	${OBJECTDIR}/src/TControllerFunction.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.o \
	${OBJECTDIR}/src/TSoundManager.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.o \
	${OBJECTDIR}/src/TIrrSoundManager.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.o \
	${OBJECTDIR}/src/TEventQueue.o \
	${OBJECTDIR}/src/TInputBinder.o \
	${OBJECTDIR}/tools/lsl/src/lua/ltm.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.o \
	${OBJECTDIR}/src/TIntervalDelegate.o \
	${OBJECTDIR}/src/TMemory.o \
	${OBJECTDIR}/src/TVertex.o \
	${OBJECTDIR}/src/TAABBox.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.o \
	${OBJECTDIR}/tools/lsl/src/lua/lobject.o \
	${OBJECTDIR}/src/TPlaneNode.o \
	${OBJECTDIR}/tools/lsl/src/CSceneNodeAnimatorMaterialLayer.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.o \
	${OBJECTDIR}/src/TPlayerController.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.o \
	${OBJECTDIR}/src/TIrrSound.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.o \
	${OBJECTDIR}/src/TCameraNode.o \
	${OBJECTDIR}/tools/lsl/src/lua/ltablib.o \
	${OBJECTDIR}/src/TRotateController.o \
	${OBJECTDIR}/tools/lsl/src/lua/print.o \
	${OBJECTDIR}/src/TSceneLoader.o \
	${OBJECTDIR}/src/TNullSoundManager.o \
	${OBJECTDIR}/tools/lsl/src/lua/lzio.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.o \
	${OBJECTDIR}/src/TSound.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.o \
	${OBJECTDIR}/src/TGUIButton.o \
	${OBJECTDIR}/src/TGUIWindow.o \
	${OBJECTDIR}/src/TOscillateController.o \
	${OBJECTDIR}/tools/lsl/src/lua/lparser.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.o \
	${OBJECTDIR}/src/TFMSoundManager.o \
	${OBJECTDIR}/src/TEventDelegate.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.o \
	${OBJECTDIR}/src/TControllerManager.o \
	${OBJECTDIR}/tools/lsl/src/lua/loslib.o \
	${OBJECTDIR}/src/TColliderMesh.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.o \
	${OBJECTDIR}/src/TState.o \
	${OBJECTDIR}/src/TPhysicsManager.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.o \
	${OBJECTDIR}/src/TRay.o \
	${OBJECTDIR}/tools/lsl/src/lua/linit.o \
	${OBJECTDIR}/src/TGUIDialogs.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.o \
	${OBJECTDIR}/src/swig/tubras_wrap_lua.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.o \
	${OBJECTDIR}/src/TTimer.o \
	${OBJECTDIR}/tools/lsl/src/lua/llex.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.o \
	${OBJECTDIR}/src/TGUIScreen.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.o \
	${OBJECTDIR}/src/TGUIFactory.o \
	${OBJECTDIR}/src/TFile.o \
	${OBJECTDIR}/src/TColliderCone.o \
	${OBJECTDIR}/src/TDynamicNode.o \
	${OBJECTDIR}/src/TScript.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.o \
	${OBJECTDIR}/src/TNodeFactory.o \
	${OBJECTDIR}/src/TSoundNode.o \
	${OBJECTDIR}/src/TRandom.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.o \
	${OBJECTDIR}/tools/lsl/src/lua/liolib.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.o \
	${OBJECTDIR}/tools/lsl/src/lua/ldo.o \
	${OBJECTDIR}/src/TApplication.o \
	${OBJECTDIR}/src/TColliderBox.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.o \
	${OBJECTDIR}/src/TDebugNode.o \
	${OBJECTDIR}/tools/lsl/src/lua/lmem.o \
	${OBJECTDIR}/src/TInputManager.o \
	${OBJECTDIR}/tools/lsl/src/lua/lvm.o \
	${OBJECTDIR}/src/TScriptManager.o \
	${OBJECTDIR}/tools/lsl/src/lua/lbaselib.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/LinearMath/btConvexHull.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.o \
	${OBJECTDIR}/src/TMath.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.o \
	${OBJECTDIR}/src/TIntervalController.o \
	${OBJECTDIR}/deps/bullet/src/LinearMath/btAlignedAllocator.o \
	${OBJECTDIR}/src/TRenderer.o \
	${OBJECTDIR}/tools/lsl/src/clsl.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.o \
	${OBJECTDIR}/src/TQuaternion.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.o

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
	${MAKE}  -f nbproject/Makefile-Win32-Debug.mk libs/debug/libTubras.a

libs/debug/libTubras.a: ${OBJECTFILES}
	${MKDIR} -p libs/debug
	${RM} libs/debug/libTubras.a
	${AR} rv libs/debug/libTubras.a ${OBJECTFILES} 
	$(RANLIB) libs/debug/libTubras.a

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.o: deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.o deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp

${OBJECTDIR}/src/TSceneNode.o: src/TSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSceneNode.o src/TSceneNode.cpp

${OBJECTDIR}/src/TEventManager.o: src/TEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEventManager.o src/TEventManager.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp

${OBJECTDIR}/src/TTask.o: src/TTask.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTask.o src/TTask.cpp

${OBJECTDIR}/src/TObject.o: src/TObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TObject.o src/TObject.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.o deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.cpp

${OBJECTDIR}/tools/lsl/src/lua/ldebug.o: tools/lsl/src/lua/ldebug.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/ldebug.o tools/lsl/src/lua/ldebug.c

${OBJECTDIR}/src/TColliderCylinder.o: src/TColliderCylinder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderCylinder.o src/TColliderCylinder.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.o: deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.o deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.cpp

${OBJECTDIR}/tools/lsl/src/lua/lcode.o: tools/lsl/src/lua/lcode.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lcode.o tools/lsl/src/lua/lcode.c

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.o: deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.o deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.cpp

${OBJECTDIR}/src/TColliderPlane.o: src/TColliderPlane.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderPlane.o src/TColliderPlane.cpp

${OBJECTDIR}/tools/lsl/src/lua/ldump.o: tools/lsl/src/lua/ldump.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/ldump.o tools/lsl/src/lua/ldump.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp

${OBJECTDIR}/tools/lsl/src/lua/lundump.o: tools/lsl/src/lua/lundump.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lundump.o tools/lsl/src/lua/lundump.c

${OBJECTDIR}/src/TInputHandler.o: src/TInputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TInputHandler.o src/TInputHandler.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.o: deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.o deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.o deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.o: deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.o deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp

${OBJECTDIR}/src/Tubras.o: src/Tubras.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/Tubras.o src/Tubras.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.o deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.o deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.cpp

${OBJECTDIR}/src/TMotionState.o: src/TMotionState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TMotionState.o src/TMotionState.cpp

${OBJECTDIR}/src/TShakeController.o: src/TShakeController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TShakeController.o src/TShakeController.cpp

${OBJECTDIR}/src/TEvent.o: src/TEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEvent.o src/TEvent.cpp

${OBJECTDIR}/tools/lsl/src/lua/lapi.o: tools/lsl/src/lua/lapi.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lapi.o tools/lsl/src/lua/lapi.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.o: deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.o deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp

${OBJECTDIR}/src/TGUISkin2.o: src/TGUISkin2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUISkin2.o src/TGUISkin2.cpp

${OBJECTDIR}/tools/lsl/src/lua/lmathlib.o: tools/lsl/src/lua/lmathlib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lmathlib.o tools/lsl/src/lua/lmathlib.c

${OBJECTDIR}/tools/lsl/src/lua/loadlib.o: tools/lsl/src/lua/loadlib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/loadlib.o tools/lsl/src/lua/loadlib.c

${OBJECTDIR}/tools/lsl/src/lua/lgc.o: tools/lsl/src/lua/lgc.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lgc.o tools/lsl/src/lua/lgc.c

${OBJECTDIR}/src/TTextOverlay.o: src/TTextOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTextOverlay.o src/TTextOverlay.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp

${OBJECTDIR}/tools/lsl/src/lua/lfunc.o: tools/lsl/src/lua/lfunc.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lfunc.o tools/lsl/src/lua/lfunc.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp

${OBJECTDIR}/deps/bullet/src/LinearMath/btQuickprof.o: deps/bullet/src/LinearMath/btQuickprof.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/LinearMath
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/LinearMath/btQuickprof.o deps/bullet/src/LinearMath/btQuickprof.cpp

${OBJECTDIR}/src/TAxisNode.o: src/TAxisNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TAxisNode.o src/TAxisNode.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.o deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.cpp

${OBJECTDIR}/tools/lsl/src/lua/lstring.o: tools/lsl/src/lua/lstring.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lstring.o tools/lsl/src/lua/lstring.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.o: deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.o deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.o: deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.o deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.cpp

${OBJECTDIR}/src/TNullSound.o: src/TNullSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TNullSound.o src/TNullSound.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.o deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.o: deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.o deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.cpp

${OBJECTDIR}/src/TColor.o: src/TColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColor.o src/TColor.cpp

${OBJECTDIR}/src/TColliderShape.o: src/TColliderShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderShape.o src/TColliderShape.cpp

${OBJECTDIR}/src/TLineNode.o: src/TLineNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TLineNode.o src/TLineNode.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp

${OBJECTDIR}/src/TTaskManager.o: src/TTaskManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTaskManager.o src/TTaskManager.cpp

${OBJECTDIR}/tools/lsl/src/lua/ltable.o: tools/lsl/src/lua/ltable.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/ltable.o tools/lsl/src/lua/ltable.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp

${OBJECTDIR}/tools/lsl/src/lua/lopcodes.o: tools/lsl/src/lua/lopcodes.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lopcodes.o tools/lsl/src/lua/lopcodes.c

${OBJECTDIR}/src/TRayResult.o: src/TRayResult.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRayResult.o src/TRayResult.cpp

${OBJECTDIR}/src/TFMSound.o: src/TFMSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TFMSound.o src/TFMSound.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.o deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.cpp

${OBJECTDIR}/src/TGUISlider.o: src/TGUISlider.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUISlider.o src/TGUISlider.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.o: deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.o deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.cpp

${OBJECTDIR}/src/TVector2.o: src/TVector2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TVector2.o src/TVector2.cpp

${OBJECTDIR}/src/CIrrBMeshFileLoader.o: src/CIrrBMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/CIrrBMeshFileLoader.o src/CIrrBMeshFileLoader.cpp

${OBJECTDIR}/src/CIrrBMeshWriter.o: src/CIrrBMeshWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/CIrrBMeshWriter.o src/CIrrBMeshWriter.cpp

${OBJECTDIR}/src/TTaskDelegate.o: src/TTaskDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTaskDelegate.o src/TTaskDelegate.cpp

${OBJECTDIR}/src/TOverlay.o: src/TOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TOverlay.o src/TOverlay.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.o deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.o deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp

${OBJECTDIR}/src/TGUISkin.o: src/TGUISkin.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUISkin.o src/TGUISkin.cpp

${OBJECTDIR}/src/TLogger.o: src/TLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TLogger.o src/TLogger.cpp

${OBJECTDIR}/src/getopt.o: src/getopt.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/getopt.o src/getopt.cpp

${OBJECTDIR}/src/TVector3.o: src/TVector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TVector3.o src/TVector3.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp

${OBJECTDIR}/tools/lsl/src/lua/lauxlib.o: tools/lsl/src/lua/lauxlib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lauxlib.o tools/lsl/src/lua/lauxlib.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.o deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.o deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp

${OBJECTDIR}/src/TController.o: src/TController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TController.o src/TController.cpp

${OBJECTDIR}/src/TEmptyNode.o: src/TEmptyNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEmptyNode.o src/TEmptyNode.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp

${OBJECTDIR}/src/TBackgroundNode.o: src/TBackgroundNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TBackgroundNode.o src/TBackgroundNode.cpp

${OBJECTDIR}/deps/bullet/src/LinearMath/btGeometryUtil.o: deps/bullet/src/LinearMath/btGeometryUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/LinearMath
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/LinearMath/btGeometryUtil.o deps/bullet/src/LinearMath/btGeometryUtil.cpp

${OBJECTDIR}/tools/lsl/src/lua/lstate.o: tools/lsl/src/lua/lstate.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lstate.o tools/lsl/src/lua/lstate.c

${OBJECTDIR}/src/TDynamicWorld.o: src/TDynamicWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TDynamicWorld.o src/TDynamicWorld.cpp

${OBJECTDIR}/src/TColliderSphere.o: src/TColliderSphere.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderSphere.o src/TColliderSphere.cpp

${OBJECTDIR}/tools/lsl/src/lua/ldblib.o: tools/lsl/src/lua/ldblib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/ldblib.o tools/lsl/src/lua/ldblib.c

${OBJECTDIR}/tools/lsl/src/lua/lstrlib.o: tools/lsl/src/lua/lstrlib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lstrlib.o tools/lsl/src/lua/lstrlib.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.o: deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.o: deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.cpp

${OBJECTDIR}/src/TRigidBody.o: src/TRigidBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRigidBody.o src/TRigidBody.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.o deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.cpp

${OBJECTDIR}/src/TControllerFunction.o: src/TControllerFunction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TControllerFunction.o src/TControllerFunction.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp

${OBJECTDIR}/src/TSoundManager.o: src/TSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSoundManager.o src/TSoundManager.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.o deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.o deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp

${OBJECTDIR}/src/TIrrSoundManager.o: src/TIrrSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TIrrSoundManager.o src/TIrrSoundManager.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.o: deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.o deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.cpp

${OBJECTDIR}/src/TEventQueue.o: src/TEventQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEventQueue.o src/TEventQueue.cpp

${OBJECTDIR}/src/TInputBinder.o: src/TInputBinder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TInputBinder.o src/TInputBinder.cpp

${OBJECTDIR}/tools/lsl/src/lua/ltm.o: tools/lsl/src/lua/ltm.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/ltm.o tools/lsl/src/lua/ltm.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.o: deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.o deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.cpp

${OBJECTDIR}/src/TIntervalDelegate.o: src/TIntervalDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TIntervalDelegate.o src/TIntervalDelegate.cpp

${OBJECTDIR}/src/TMemory.o: src/TMemory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TMemory.o src/TMemory.cpp

${OBJECTDIR}/src/TVertex.o: src/TVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TVertex.o src/TVertex.cpp

${OBJECTDIR}/src/TAABBox.o: src/TAABBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TAABBox.o src/TAABBox.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.o: deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.o deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp

${OBJECTDIR}/tools/lsl/src/lua/lobject.o: tools/lsl/src/lua/lobject.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lobject.o tools/lsl/src/lua/lobject.c

${OBJECTDIR}/src/TPlaneNode.o: src/TPlaneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TPlaneNode.o src/TPlaneNode.cpp

${OBJECTDIR}/tools/lsl/src/CSceneNodeAnimatorMaterialLayer.o: tools/lsl/src/CSceneNodeAnimatorMaterialLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/tools/lsl/src/CSceneNodeAnimatorMaterialLayer.o tools/lsl/src/CSceneNodeAnimatorMaterialLayer.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.o deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp

${OBJECTDIR}/src/TPlayerController.o: src/TPlayerController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TPlayerController.o src/TPlayerController.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp

${OBJECTDIR}/src/TIrrSound.o: src/TIrrSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TIrrSound.o src/TIrrSound.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp

${OBJECTDIR}/src/TCameraNode.o: src/TCameraNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TCameraNode.o src/TCameraNode.cpp

${OBJECTDIR}/tools/lsl/src/lua/ltablib.o: tools/lsl/src/lua/ltablib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/ltablib.o tools/lsl/src/lua/ltablib.c

${OBJECTDIR}/src/TRotateController.o: src/TRotateController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRotateController.o src/TRotateController.cpp

${OBJECTDIR}/tools/lsl/src/lua/print.o: tools/lsl/src/lua/print.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/print.o tools/lsl/src/lua/print.c

${OBJECTDIR}/src/TSceneLoader.o: src/TSceneLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSceneLoader.o src/TSceneLoader.cpp

${OBJECTDIR}/src/TNullSoundManager.o: src/TNullSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TNullSoundManager.o src/TNullSoundManager.cpp

${OBJECTDIR}/tools/lsl/src/lua/lzio.o: tools/lsl/src/lua/lzio.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lzio.o tools/lsl/src/lua/lzio.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.o deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.cpp

${OBJECTDIR}/src/TSound.o: src/TSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSound.o src/TSound.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.o: deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.o deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp

${OBJECTDIR}/src/TGUIButton.o: src/TGUIButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIButton.o src/TGUIButton.cpp

${OBJECTDIR}/src/TGUIWindow.o: src/TGUIWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIWindow.o src/TGUIWindow.cpp

${OBJECTDIR}/src/TOscillateController.o: src/TOscillateController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TOscillateController.o src/TOscillateController.cpp

${OBJECTDIR}/tools/lsl/src/lua/lparser.o: tools/lsl/src/lua/lparser.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lparser.o tools/lsl/src/lua/lparser.c

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp

${OBJECTDIR}/src/TFMSoundManager.o: src/TFMSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TFMSoundManager.o src/TFMSoundManager.cpp

${OBJECTDIR}/src/TEventDelegate.o: src/TEventDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TEventDelegate.o src/TEventDelegate.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.o: deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.o deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp

${OBJECTDIR}/src/TControllerManager.o: src/TControllerManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TControllerManager.o src/TControllerManager.cpp

${OBJECTDIR}/tools/lsl/src/lua/loslib.o: tools/lsl/src/lua/loslib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/loslib.o tools/lsl/src/lua/loslib.c

${OBJECTDIR}/src/TColliderMesh.o: src/TColliderMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderMesh.o src/TColliderMesh.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp

${OBJECTDIR}/src/TState.o: src/TState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TState.o src/TState.cpp

${OBJECTDIR}/src/TPhysicsManager.o: src/TPhysicsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TPhysicsManager.o src/TPhysicsManager.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.o deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.cpp

${OBJECTDIR}/src/TRay.o: src/TRay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRay.o src/TRay.cpp

${OBJECTDIR}/tools/lsl/src/lua/linit.o: tools/lsl/src/lua/linit.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/linit.o tools/lsl/src/lua/linit.c

${OBJECTDIR}/src/TGUIDialogs.o: src/TGUIDialogs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIDialogs.o src/TGUIDialogs.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.o deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp

${OBJECTDIR}/src/swig/tubras_wrap_lua.o: src/swig/tubras_wrap_lua.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/swig
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/swig/tubras_wrap_lua.o src/swig/tubras_wrap_lua.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp

${OBJECTDIR}/src/TTimer.o: src/TTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TTimer.o src/TTimer.cpp

${OBJECTDIR}/tools/lsl/src/lua/llex.o: tools/lsl/src/lua/llex.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/llex.o tools/lsl/src/lua/llex.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.o deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.o: deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.o deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp

${OBJECTDIR}/src/TGUIScreen.o: src/TGUIScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIScreen.o src/TGUIScreen.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.o deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.o deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp

${OBJECTDIR}/src/TGUIFactory.o: src/TGUIFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TGUIFactory.o src/TGUIFactory.cpp

${OBJECTDIR}/src/TFile.o: src/TFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TFile.o src/TFile.cpp

${OBJECTDIR}/src/TColliderCone.o: src/TColliderCone.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderCone.o src/TColliderCone.cpp

${OBJECTDIR}/src/TDynamicNode.o: src/TDynamicNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TDynamicNode.o src/TDynamicNode.cpp

${OBJECTDIR}/src/TScript.o: src/TScript.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TScript.o src/TScript.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.o: deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.o deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.o: deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.o deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.cpp

${OBJECTDIR}/src/TNodeFactory.o: src/TNodeFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TNodeFactory.o src/TNodeFactory.cpp

${OBJECTDIR}/src/TSoundNode.o: src/TSoundNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TSoundNode.o src/TSoundNode.cpp

${OBJECTDIR}/src/TRandom.o: src/TRandom.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRandom.o src/TRandom.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.o: deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.o deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.o: deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.o deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp

${OBJECTDIR}/tools/lsl/src/lua/liolib.o: tools/lsl/src/lua/liolib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/liolib.o tools/lsl/src/lua/liolib.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp

${OBJECTDIR}/tools/lsl/src/lua/ldo.o: tools/lsl/src/lua/ldo.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/ldo.o tools/lsl/src/lua/ldo.c

${OBJECTDIR}/src/TApplication.o: src/TApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TApplication.o src/TApplication.cpp

${OBJECTDIR}/src/TColliderBox.o: src/TColliderBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TColliderBox.o src/TColliderBox.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.o: deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.o deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.cpp

${OBJECTDIR}/src/TDebugNode.o: src/TDebugNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TDebugNode.o src/TDebugNode.cpp

${OBJECTDIR}/tools/lsl/src/lua/lmem.o: tools/lsl/src/lua/lmem.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lmem.o tools/lsl/src/lua/lmem.c

${OBJECTDIR}/src/TInputManager.o: src/TInputManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TInputManager.o src/TInputManager.cpp

${OBJECTDIR}/tools/lsl/src/lua/lvm.o: tools/lsl/src/lua/lvm.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lvm.o tools/lsl/src/lua/lvm.c

${OBJECTDIR}/src/TScriptManager.o: src/TScriptManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TScriptManager.o src/TScriptManager.cpp

${OBJECTDIR}/tools/lsl/src/lua/lbaselib.o: tools/lsl/src/lua/lbaselib.c 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src/lua
	$(COMPILE.c) -g -o ${OBJECTDIR}/tools/lsl/src/lua/lbaselib.o tools/lsl/src/lua/lbaselib.c

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.o: deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/LinearMath/btConvexHull.o: deps/bullet/src/LinearMath/btConvexHull.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/LinearMath
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/LinearMath/btConvexHull.o deps/bullet/src/LinearMath/btConvexHull.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.cpp

${OBJECTDIR}/src/TMath.o: src/TMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TMath.o src/TMath.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.o deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.o: deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.o: deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp

${OBJECTDIR}/src/TIntervalController.o: src/TIntervalController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TIntervalController.o src/TIntervalController.cpp

${OBJECTDIR}/deps/bullet/src/LinearMath/btAlignedAllocator.o: deps/bullet/src/LinearMath/btAlignedAllocator.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/LinearMath
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/LinearMath/btAlignedAllocator.o deps/bullet/src/LinearMath/btAlignedAllocator.cpp

${OBJECTDIR}/src/TRenderer.o: src/TRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TRenderer.o src/TRenderer.cpp

${OBJECTDIR}/tools/lsl/src/clsl.o: tools/lsl/src/clsl.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools/lsl/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/tools/lsl/src/clsl.o tools/lsl/src/clsl.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.o: deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.cpp

${OBJECTDIR}/src/TQuaternion.o: src/TQuaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/src/TQuaternion.o src/TQuaternion.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.o: deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.o: deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Itools/lsl/include -Itools/lsl/src/lua -Ideps/irrlicht/source/Irrlicht -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.o deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Debug
	${RM} libs/debug/libTubras.a

# Subprojects
.clean-subprojects:
