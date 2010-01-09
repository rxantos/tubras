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
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Win32-Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.o \
	${OBJECTDIR}/src/lua/ldebug.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.o \
	${OBJECTDIR}/src/TBStaticMesh.o \
	${OBJECTDIR}/src/lua/llex.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.o \
	${OBJECTDIR}/src/TScriptManager.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/planetri.o \
	${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/OtherAPI.o \
	${OBJECTDIR}/src/TRay.o \
	${OBJECTDIR}/src/TSound.o \
	${OBJECTDIR}/src/TIntervalController.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.o \
	${OBJECTDIR}/src/TApplication.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.o \
	${OBJECTDIR}/src/TParticle.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.o \
	${OBJECTDIR}/src/TParticleAction.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/ConvexBuilder.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.o \
	${OBJECTDIR}/src/TKinematicCharacterTest.o \
	${OBJECTDIR}/src/lua/lstrlib.o \
	${OBJECTDIR}/src/TOscillateController.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/fitsphere.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.o \
	${OBJECTDIR}/src/TState.o \
	${OBJECTDIR}/src/TGUICursor.o \
	${OBJECTDIR}/src/lua/ltm.o \
	${OBJECTDIR}/src/lua/linit.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.o \
	${OBJECTDIR}/tools/irrlicht/extensions/CGUISceneNode.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.o \
	${OBJECTDIR}/src/TSceneLoader.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.o \
	${OBJECTDIR}/src/TMemory.o \
	${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/PInternalState.o \
	${OBJECTDIR}/src/TLogger.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.o \
	${OBJECTDIR}/src/TGUISlider.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.o \
	${OBJECTDIR}/src/TGUISkin.o \
	${OBJECTDIR}/deps/bullet/src/LinearMath/btConvexHull.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/bestfit.o \
	${OBJECTDIR}/src/TColliderShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.o \
	${OBJECTDIR}/src/TColliderCone.o \
	${OBJECTDIR}/src/TTaskDelegate.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.o \
	${OBJECTDIR}/src/TBRotation.o \
	${OBJECTDIR}/src/lua/lcode.o \
	${OBJECTDIR}/src/TRayResult.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.o \
	${OBJECTDIR}/src/lua/lmathlib.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.o \
	${OBJECTDIR}/src/TBackgroundNode.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.o \
	${OBJECTDIR}/src/TSceneNode.o \
	${OBJECTDIR}/src/lua/lauxlib.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.o \
	${OBJECTDIR}/src/TKinematicCharacter.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/concavity.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/ConvexDecomposition.o \
	${OBJECTDIR}/src/TTextOverlay.o \
	${OBJECTDIR}/src/getopt.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/splitplane.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.o \
	${OBJECTDIR}/src/lua/ldump.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.o \
	${OBJECTDIR}/src/Tubras.o \
	${OBJECTDIR}/src/TEventQueue.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.o \
	${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/Actions.o \
	${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/ActionsAPI.o \
	${OBJECTDIR}/src/TIrrSound.o \
	${OBJECTDIR}/src/TParticleManager.o \
	${OBJECTDIR}/src/TGUIWindow.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.o \
	${OBJECTDIR}/src/TDynamicWorld.o \
	${OBJECTDIR}/src/TOverlay.o \
	${OBJECTDIR}/src/TPhysicsObject.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.o \
	${OBJECTDIR}/src/TTask.o \
	${OBJECTDIR}/src/TNullSoundManager.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.o \
	${OBJECTDIR}/src/TShakeController.o \
	${OBJECTDIR}/src/TPhysicsManager.o \
	${OBJECTDIR}/src/lua/lparser.o \
	${OBJECTDIR}/src/TFMSoundManager.o \
	${OBJECTDIR}/src/TVector2.o \
	${OBJECTDIR}/src/TInputBinder.o \
	${OBJECTDIR}/src/lua/lzio.o \
	${OBJECTDIR}/src/TSoundManager.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.o \
	${OBJECTDIR}/src/TQuaternion.o \
	${OBJECTDIR}/tools/irrlicht/extensions/CIrrBMeshWriter.o \
	${OBJECTDIR}/src/TNullSound.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.o \
	${OBJECTDIR}/src/TEventDelegate.o \
	${OBJECTDIR}/deps/bullet/src/LinearMath/btAlignedAllocator.o \
	${OBJECTDIR}/src/swig/tubras_wrap_lua.o \
	${OBJECTDIR}/src/lua/lapi.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.o \
	${OBJECTDIR}/src/TEventManager.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.o \
	${OBJECTDIR}/src/TColliderCylinder.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.o \
	${OBJECTDIR}/src/TGUIImage.o \
	${OBJECTDIR}/src/TVertex.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/raytri.o \
	${OBJECTDIR}/src/TProperties.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.o \
	${OBJECTDIR}/src/TLineNode.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.o \
	${OBJECTDIR}/src/TRandom.o \
	${OBJECTDIR}/src/TColor.o \
	${OBJECTDIR}/src/lua/ldo.o \
	${OBJECTDIR}/src/TControllerManager.o \
	${OBJECTDIR}/src/lua/loslib.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.o \
	${OBJECTDIR}/src/TInputManager.o \
	${OBJECTDIR}/src/lua/lopcodes.o \
	${OBJECTDIR}/src/lua/loadlib.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/vlookup.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.o \
	${OBJECTDIR}/src/lua/lvm.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.o \
	${OBJECTDIR}/src/TEmptyNode.o \
	${OBJECTDIR}/src/TAxisNode.o \
	${OBJECTDIR}/src/TInputHandler.o \
	${OBJECTDIR}/src/lua/ltable.o \
	${OBJECTDIR}/src/lua/lstring.o \
	${OBJECTDIR}/src/TGUIFactory.o \
	${OBJECTDIR}/src/TEvent.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/meshvolume.o \
	${OBJECTDIR}/src/TCameraNode.o \
	${OBJECTDIR}/src/TColliderSphere.o \
	${OBJECTDIR}/src/TPlayerController.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.o \
	${OBJECTDIR}/src/lua/ldblib.o \
	${OBJECTDIR}/src/lua/lfunc.o \
	${OBJECTDIR}/src/lua/lbaselib.o \
	${OBJECTDIR}/src/lua/lstate.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.o \
	${OBJECTDIR}/src/TDebugNode.o \
	${OBJECTDIR}/src/TEntity.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.o \
	${OBJECTDIR}/src/TTaskManager.o \
	${OBJECTDIR}/src/TParticleDomain.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.o \
	${OBJECTDIR}/deps/bullet/src/LinearMath/btGeometryUtil.o \
	${OBJECTDIR}/src/TMath.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.o \
	${OBJECTDIR}/src/TVector3.o \
	${OBJECTDIR}/src/lua/lgc.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Character/btKinematicCharacterController.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.o \
	${OBJECTDIR}/src/TFile.o \
	${OBJECTDIR}/src/TRotateController.o \
	${OBJECTDIR}/src/TControllerFunction.o \
	${OBJECTDIR}/src/TGUIScreen.o \
	${OBJECTDIR}/src/TColliderPlane.o \
	${OBJECTDIR}/src/TPlaneNode.o \
	${OBJECTDIR}/src/lua/lmem.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/cd_hull.o \
	${OBJECTDIR}/src/TGUIButton.o \
	${OBJECTDIR}/src/TController.o \
	${OBJECTDIR}/src/TBehaviorFactory.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/bestfitobb.o \
	${OBJECTDIR}/src/TParticleNode.o \
	${OBJECTDIR}/src/TRenderer.o \
	${OBJECTDIR}/src/lua/liolib.o \
	${OBJECTDIR}/src/lua/lobject.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.o \
	${OBJECTDIR}/src/TBView.o \
	${OBJECTDIR}/src/TColliderMesh.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.o \
	${OBJECTDIR}/src/lua/lundump.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.o \
	${OBJECTDIR}/src/TSL.o \
	${OBJECTDIR}/src/TEntityManager.o \
	${OBJECTDIR}/src/TGUIDialogs.o \
	${OBJECTDIR}/deps/bullet/src/LinearMath/btQuickprof.o \
	${OBJECTDIR}/src/TIntervalDelegate.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.o \
	${OBJECTDIR}/src/TScript.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.o \
	${OBJECTDIR}/src/TSceneNodeAnimatorMaterialLayer.o \
	${OBJECTDIR}/tools/irrlicht/extensions/CIrrBMeshFileLoader.o \
	${OBJECTDIR}/src/TAABBox.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.o \
	${OBJECTDIR}/src/TIrrSoundManager.o \
	${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/float_math.o \
	${OBJECTDIR}/src/TColliderBox.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.o \
	${OBJECTDIR}/src/TScriptState.o \
	${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.o \
	${OBJECTDIR}/src/TTimer.o \
	${OBJECTDIR}/src/TSoundNode.o \
	${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.o \
	${OBJECTDIR}/src/lua/ltablib.o \
	${OBJECTDIR}/src/TFMSound.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Debug.mk libs/debug/libTubras_d.a

libs/debug/libTubras_d.a: ${OBJECTFILES}
	${MKDIR} -p libs/debug
	${RM} libs/debug/libTubras_d.a
	${AR} rv libs/debug/libTubras_d.a ${OBJECTFILES} 
	$(RANLIB) libs/debug/libTubras_d.a

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp

${OBJECTDIR}/src/lua/ldebug.o: nbproject/Makefile-${CND_CONF}.mk src/lua/ldebug.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/ldebug.o src/lua/ldebug.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.o deps/bullet/src/BulletCollision/CollisionShapes/btTetrahedronShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.o deps/bullet/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.o deps/bullet/src/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp

${OBJECTDIR}/src/TBStaticMesh.o: nbproject/Makefile-${CND_CONF}.mk src/TBStaticMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TBStaticMesh.o src/TBStaticMesh.cpp

${OBJECTDIR}/src/lua/llex.o: nbproject/Makefile-${CND_CONF}.mk src/lua/llex.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/llex.o src/lua/llex.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp

${OBJECTDIR}/src/TScriptManager.o: nbproject/Makefile-${CND_CONF}.mk src/TScriptManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TScriptManager.o src/TScriptManager.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/planetri.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/planetri.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/planetri.o deps/bullet/Extras/ConvexDecomposition/planetri.cpp

${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/OtherAPI.o: nbproject/Makefile-${CND_CONF}.mk deps/particle2/Particle2/ParticleLib/OtherAPI.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/particle2/Particle2/ParticleLib
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/OtherAPI.o deps/particle2/Particle2/ParticleLib/OtherAPI.cpp

${OBJECTDIR}/src/TRay.o: nbproject/Makefile-${CND_CONF}.mk src/TRay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TRay.o src/TRay.cpp

${OBJECTDIR}/src/TSound.o: nbproject/Makefile-${CND_CONF}.mk src/TSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TSound.o src/TSound.cpp

${OBJECTDIR}/src/TIntervalController.o: nbproject/Makefile-${CND_CONF}.mk src/TIntervalController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TIntervalController.o src/TIntervalController.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp

${OBJECTDIR}/src/TApplication.o: nbproject/Makefile-${CND_CONF}.mk src/TApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TApplication.o src/TApplication.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.o deps/bullet/src/BulletDynamics/Dynamics/btRigidBody.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.o deps/bullet/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp

${OBJECTDIR}/src/TParticle.o: nbproject/Makefile-${CND_CONF}.mk src/TParticle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TParticle.o src/TParticle.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.o deps/bullet/src/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.o deps/bullet/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.o deps/bullet/src/BulletCollision/CollisionShapes/btUniformScalingShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.o deps/bullet/src/BulletDynamics/Vehicle/btWheelInfo.cpp

${OBJECTDIR}/src/TParticleAction.o: nbproject/Makefile-${CND_CONF}.mk src/TParticleAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TParticleAction.o src/TParticleAction.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/ConvexBuilder.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/ConvexBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/ConvexBuilder.o deps/bullet/Extras/ConvexDecomposition/ConvexBuilder.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp

${OBJECTDIR}/src/TKinematicCharacterTest.o: nbproject/Makefile-${CND_CONF}.mk src/TKinematicCharacterTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TKinematicCharacterTest.o src/TKinematicCharacterTest.cpp

${OBJECTDIR}/src/lua/lstrlib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lstrlib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lstrlib.o src/lua/lstrlib.c

${OBJECTDIR}/src/TOscillateController.o: nbproject/Makefile-${CND_CONF}.mk src/TOscillateController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TOscillateController.o src/TOscillateController.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/fitsphere.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/fitsphere.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/fitsphere.o deps/bullet/Extras/ConvexDecomposition/fitsphere.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.o deps/bullet/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.o deps/bullet/src/BulletCollision/CollisionShapes/btMultiSphereShape.cpp

${OBJECTDIR}/src/TState.o: nbproject/Makefile-${CND_CONF}.mk src/TState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TState.o src/TState.cpp

${OBJECTDIR}/src/TGUICursor.o: nbproject/Makefile-${CND_CONF}.mk src/TGUICursor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUICursor.o src/TGUICursor.cpp

${OBJECTDIR}/src/lua/ltm.o: nbproject/Makefile-${CND_CONF}.mk src/lua/ltm.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/ltm.o src/lua/ltm.c

${OBJECTDIR}/src/lua/linit.o: nbproject/Makefile-${CND_CONF}.mk src/lua/linit.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/linit.o src/lua/linit.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.o deps/bullet/src/BulletCollision/CollisionShapes/btCapsuleShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp

${OBJECTDIR}/tools/irrlicht/extensions/CGUISceneNode.o: nbproject/Makefile-${CND_CONF}.mk tools/irrlicht/extensions/CGUISceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools/irrlicht/extensions
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/tools/irrlicht/extensions/CGUISceneNode.o tools/irrlicht/extensions/CGUISceneNode.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleCallback.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp

${OBJECTDIR}/src/TSceneLoader.o: nbproject/Makefile-${CND_CONF}.mk src/TSceneLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TSceneLoader.o src/TSceneLoader.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.o deps/bullet/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp

${OBJECTDIR}/src/TMemory.o: nbproject/Makefile-${CND_CONF}.mk src/TMemory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TMemory.o src/TMemory.cpp

${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/PInternalState.o: nbproject/Makefile-${CND_CONF}.mk deps/particle2/Particle2/ParticleLib/PInternalState.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/particle2/Particle2/ParticleLib
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/PInternalState.o deps/particle2/Particle2/ParticleLib/PInternalState.cpp

${OBJECTDIR}/src/TLogger.o: nbproject/Makefile-${CND_CONF}.mk src/TLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TLogger.o src/TLogger.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp

${OBJECTDIR}/src/TGUISlider.o: nbproject/Makefile-${CND_CONF}.mk src/TGUISlider.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUISlider.o src/TGUISlider.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.o deps/bullet/src/BulletCollision/CollisionShapes/btBoxShape.cpp

${OBJECTDIR}/src/TGUISkin.o: nbproject/Makefile-${CND_CONF}.mk src/TGUISkin.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUISkin.o src/TGUISkin.cpp

${OBJECTDIR}/deps/bullet/src/LinearMath/btConvexHull.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/LinearMath/btConvexHull.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/LinearMath
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/LinearMath/btConvexHull.o deps/bullet/src/LinearMath/btConvexHull.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/bestfit.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/bestfit.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/bestfit.o deps/bullet/Extras/ConvexDecomposition/bestfit.cpp

${OBJECTDIR}/src/TColliderShape.o: nbproject/Makefile-${CND_CONF}.mk src/TColliderShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TColliderShape.o src/TColliderShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp

${OBJECTDIR}/src/TColliderCone.o: nbproject/Makefile-${CND_CONF}.mk src/TColliderCone.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TColliderCone.o src/TColliderCone.cpp

${OBJECTDIR}/src/TTaskDelegate.o: nbproject/Makefile-${CND_CONF}.mk src/TTaskDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TTaskDelegate.o src/TTaskDelegate.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp

${OBJECTDIR}/src/TBRotation.o: nbproject/Makefile-${CND_CONF}.mk src/TBRotation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TBRotation.o src/TBRotation.cpp

${OBJECTDIR}/src/lua/lcode.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lcode.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lcode.o src/lua/lcode.c

${OBJECTDIR}/src/TRayResult.o: nbproject/Makefile-${CND_CONF}.mk src/TRayResult.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TRayResult.o src/TRayResult.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp

${OBJECTDIR}/src/lua/lmathlib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lmathlib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lmathlib.o src/lua/lmathlib.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp

${OBJECTDIR}/src/TBackgroundNode.o: nbproject/Makefile-${CND_CONF}.mk src/TBackgroundNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TBackgroundNode.o src/TBackgroundNode.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.o deps/bullet/src/BulletCollision/BroadphaseCollision/btDispatcher.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp

${OBJECTDIR}/src/TSceneNode.o: nbproject/Makefile-${CND_CONF}.mk src/TSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TSceneNode.o src/TSceneNode.cpp

${OBJECTDIR}/src/lua/lauxlib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lauxlib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lauxlib.o src/lua/lauxlib.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.o deps/bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp

${OBJECTDIR}/src/TKinematicCharacter.o: nbproject/Makefile-${CND_CONF}.mk src/TKinematicCharacter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TKinematicCharacter.o src/TKinematicCharacter.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConcaveShape.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/concavity.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/concavity.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/concavity.o deps/bullet/Extras/ConvexDecomposition/concavity.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/ConvexDecomposition.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/ConvexDecomposition.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/ConvexDecomposition.o deps/bullet/Extras/ConvexDecomposition/ConvexDecomposition.cpp

${OBJECTDIR}/src/TTextOverlay.o: nbproject/Makefile-${CND_CONF}.mk src/TTextOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TTextOverlay.o src/TTextOverlay.cpp

${OBJECTDIR}/src/getopt.o: nbproject/Makefile-${CND_CONF}.mk src/getopt.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/getopt.o src/getopt.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/splitplane.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/splitplane.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/splitplane.o deps/bullet/Extras/ConvexDecomposition/splitplane.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.o deps/bullet/src/BulletCollision/CollisionShapes/btCompoundShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.o deps/bullet/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp

${OBJECTDIR}/src/lua/ldump.o: nbproject/Makefile-${CND_CONF}.mk src/lua/ldump.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/ldump.o src/lua/ldump.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.o deps/bullet/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp

${OBJECTDIR}/src/Tubras.o: nbproject/Makefile-${CND_CONF}.mk src/Tubras.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Tubras.o src/Tubras.cpp

${OBJECTDIR}/src/TEventQueue.o: nbproject/Makefile-${CND_CONF}.mk src/TEventQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TEventQueue.o src/TEventQueue.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.o deps/bullet/src/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp

${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/Actions.o: nbproject/Makefile-${CND_CONF}.mk deps/particle2/Particle2/ParticleLib/Actions.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/particle2/Particle2/ParticleLib
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/Actions.o deps/particle2/Particle2/ParticleLib/Actions.cpp

${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/ActionsAPI.o: nbproject/Makefile-${CND_CONF}.mk deps/particle2/Particle2/ParticleLib/ActionsAPI.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/particle2/Particle2/ParticleLib
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/particle2/Particle2/ParticleLib/ActionsAPI.o deps/particle2/Particle2/ParticleLib/ActionsAPI.cpp

${OBJECTDIR}/src/TIrrSound.o: nbproject/Makefile-${CND_CONF}.mk src/TIrrSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TIrrSound.o src/TIrrSound.cpp

${OBJECTDIR}/src/TParticleManager.o: nbproject/Makefile-${CND_CONF}.mk src/TParticleManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TParticleManager.o src/TParticleManager.cpp

${OBJECTDIR}/src/TGUIWindow.o: nbproject/Makefile-${CND_CONF}.mk src/TGUIWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUIWindow.o src/TGUIWindow.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.o deps/bullet/src/BulletCollision/CollisionShapes/btEmptyShape.cpp

${OBJECTDIR}/src/TDynamicWorld.o: nbproject/Makefile-${CND_CONF}.mk src/TDynamicWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TDynamicWorld.o src/TDynamicWorld.cpp

${OBJECTDIR}/src/TOverlay.o: nbproject/Makefile-${CND_CONF}.mk src/TOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TOverlay.o src/TOverlay.cpp

${OBJECTDIR}/src/TPhysicsObject.o: nbproject/Makefile-${CND_CONF}.mk src/TPhysicsObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TPhysicsObject.o src/TPhysicsObject.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.o deps/bullet/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp

${OBJECTDIR}/src/TTask.o: nbproject/Makefile-${CND_CONF}.mk src/TTask.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TTask.o src/TTask.cpp

${OBJECTDIR}/src/TNullSoundManager.o: nbproject/Makefile-${CND_CONF}.mk src/TNullSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TNullSoundManager.o src/TNullSoundManager.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.o deps/bullet/src/BulletCollision/CollisionShapes/btCylinderShape.cpp

${OBJECTDIR}/src/TShakeController.o: nbproject/Makefile-${CND_CONF}.mk src/TShakeController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TShakeController.o src/TShakeController.cpp

${OBJECTDIR}/src/TPhysicsManager.o: nbproject/Makefile-${CND_CONF}.mk src/TPhysicsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TPhysicsManager.o src/TPhysicsManager.cpp

${OBJECTDIR}/src/lua/lparser.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lparser.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lparser.o src/lua/lparser.c

${OBJECTDIR}/src/TFMSoundManager.o: nbproject/Makefile-${CND_CONF}.mk src/TFMSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TFMSoundManager.o src/TFMSoundManager.cpp

${OBJECTDIR}/src/TVector2.o: nbproject/Makefile-${CND_CONF}.mk src/TVector2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TVector2.o src/TVector2.cpp

${OBJECTDIR}/src/TInputBinder.o: nbproject/Makefile-${CND_CONF}.mk src/TInputBinder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TInputBinder.o src/TInputBinder.cpp

${OBJECTDIR}/src/lua/lzio.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lzio.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lzio.o src/lua/lzio.c

${OBJECTDIR}/src/TSoundManager.o: nbproject/Makefile-${CND_CONF}.mk src/TSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TSoundManager.o src/TSoundManager.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.o deps/bullet/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.o deps/bullet/src/BulletCollision/CollisionDispatch/btUnionFind.cpp

${OBJECTDIR}/src/TQuaternion.o: nbproject/Makefile-${CND_CONF}.mk src/TQuaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TQuaternion.o src/TQuaternion.cpp

${OBJECTDIR}/tools/irrlicht/extensions/CIrrBMeshWriter.o: nbproject/Makefile-${CND_CONF}.mk tools/irrlicht/extensions/CIrrBMeshWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools/irrlicht/extensions
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/tools/irrlicht/extensions/CIrrBMeshWriter.o tools/irrlicht/extensions/CIrrBMeshWriter.cpp

${OBJECTDIR}/src/TNullSound.o: nbproject/Makefile-${CND_CONF}.mk src/TNullSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TNullSound.o src/TNullSound.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.o deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp

${OBJECTDIR}/src/TEventDelegate.o: nbproject/Makefile-${CND_CONF}.mk src/TEventDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TEventDelegate.o src/TEventDelegate.cpp

${OBJECTDIR}/deps/bullet/src/LinearMath/btAlignedAllocator.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/LinearMath/btAlignedAllocator.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/LinearMath
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/LinearMath/btAlignedAllocator.o deps/bullet/src/LinearMath/btAlignedAllocator.cpp

${OBJECTDIR}/src/swig/tubras_wrap_lua.o: nbproject/Makefile-${CND_CONF}.mk src/swig/tubras_wrap_lua.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/swig
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/swig/tubras_wrap_lua.o src/swig/tubras_wrap_lua.cpp

${OBJECTDIR}/src/lua/lapi.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lapi.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lapi.o src/lua/lapi.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexInternalShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.o deps/bullet/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp

${OBJECTDIR}/src/TEventManager.o: nbproject/Makefile-${CND_CONF}.mk src/TEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TEventManager.o src/TEventManager.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.o deps/bullet/src/BulletCollision/CollisionShapes/btSphereShape.cpp

${OBJECTDIR}/src/TColliderCylinder.o: nbproject/Makefile-${CND_CONF}.mk src/TColliderCylinder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TColliderCylinder.o src/TColliderCylinder.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleBuffer.cpp

${OBJECTDIR}/src/TGUIImage.o: nbproject/Makefile-${CND_CONF}.mk src/TGUIImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUIImage.o src/TGUIImage.cpp

${OBJECTDIR}/src/TVertex.o: nbproject/Makefile-${CND_CONF}.mk src/TVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TVertex.o src/TVertex.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/raytri.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/raytri.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/raytri.o deps/bullet/Extras/ConvexDecomposition/raytri.cpp

${OBJECTDIR}/src/TProperties.o: nbproject/Makefile-${CND_CONF}.mk src/TProperties.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TProperties.o src/TProperties.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.o deps/bullet/src/BulletCollision/CollisionShapes/btOptimizedBvh.cpp

${OBJECTDIR}/src/TLineNode.o: nbproject/Makefile-${CND_CONF}.mk src/TLineNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TLineNode.o src/TLineNode.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConeShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.o deps/bullet/src/BulletCollision/CollisionDispatch/btManifoldResult.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp

${OBJECTDIR}/src/TRandom.o: nbproject/Makefile-${CND_CONF}.mk src/TRandom.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TRandom.o src/TRandom.cpp

${OBJECTDIR}/src/TColor.o: nbproject/Makefile-${CND_CONF}.mk src/TColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TColor.o src/TColor.cpp

${OBJECTDIR}/src/lua/ldo.o: nbproject/Makefile-${CND_CONF}.mk src/lua/ldo.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/ldo.o src/lua/ldo.c

${OBJECTDIR}/src/TControllerManager.o: nbproject/Makefile-${CND_CONF}.mk src/TControllerManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TControllerManager.o src/TControllerManager.cpp

${OBJECTDIR}/src/lua/loslib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/loslib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/loslib.o src/lua/loslib.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp

${OBJECTDIR}/src/TInputManager.o: nbproject/Makefile-${CND_CONF}.mk src/TInputManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TInputManager.o src/TInputManager.cpp

${OBJECTDIR}/src/lua/lopcodes.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lopcodes.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lopcodes.o src/lua/lopcodes.c

${OBJECTDIR}/src/lua/loadlib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/loadlib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/loadlib.o src/lua/loadlib.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.o deps/bullet/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.o deps/bullet/src/BulletDynamics/Vehicle/btRaycastVehicle.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/vlookup.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/vlookup.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/vlookup.o deps/bullet/Extras/ConvexDecomposition/vlookup.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.o deps/bullet/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp

${OBJECTDIR}/src/lua/lvm.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lvm.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lvm.o src/lua/lvm.c

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.o deps/bullet/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp

${OBJECTDIR}/src/TEmptyNode.o: nbproject/Makefile-${CND_CONF}.mk src/TEmptyNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TEmptyNode.o src/TEmptyNode.cpp

${OBJECTDIR}/src/TAxisNode.o: nbproject/Makefile-${CND_CONF}.mk src/TAxisNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TAxisNode.o src/TAxisNode.cpp

${OBJECTDIR}/src/TInputHandler.o: nbproject/Makefile-${CND_CONF}.mk src/TInputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TInputHandler.o src/TInputHandler.cpp

${OBJECTDIR}/src/lua/ltable.o: nbproject/Makefile-${CND_CONF}.mk src/lua/ltable.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/ltable.o src/lua/ltable.c

${OBJECTDIR}/src/lua/lstring.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lstring.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lstring.o src/lua/lstring.c

${OBJECTDIR}/src/TGUIFactory.o: nbproject/Makefile-${CND_CONF}.mk src/TGUIFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUIFactory.o src/TGUIFactory.cpp

${OBJECTDIR}/src/TEvent.o: nbproject/Makefile-${CND_CONF}.mk src/TEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TEvent.o src/TEvent.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/meshvolume.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/meshvolume.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/meshvolume.o deps/bullet/Extras/ConvexDecomposition/meshvolume.cpp

${OBJECTDIR}/src/TCameraNode.o: nbproject/Makefile-${CND_CONF}.mk src/TCameraNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TCameraNode.o src/TCameraNode.cpp

${OBJECTDIR}/src/TColliderSphere.o: nbproject/Makefile-${CND_CONF}.mk src/TColliderSphere.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TColliderSphere.o src/TColliderSphere.cpp

${OBJECTDIR}/src/TPlayerController.o: nbproject/Makefile-${CND_CONF}.mk src/TPlayerController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TPlayerController.o src/TPlayerController.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btContactConstraint.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.o deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionObject.cpp

${OBJECTDIR}/src/lua/ldblib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/ldblib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/ldblib.o src/lua/ldblib.c

${OBJECTDIR}/src/lua/lfunc.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lfunc.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lfunc.o src/lua/lfunc.c

${OBJECTDIR}/src/lua/lbaselib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lbaselib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lbaselib.o src/lua/lbaselib.c

${OBJECTDIR}/src/lua/lstate.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lstate.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lstate.o src/lua/lstate.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp

${OBJECTDIR}/src/TDebugNode.o: nbproject/Makefile-${CND_CONF}.mk src/TDebugNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TDebugNode.o src/TDebugNode.cpp

${OBJECTDIR}/src/TEntity.o: nbproject/Makefile-${CND_CONF}.mk src/TEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TEntity.o src/TEntity.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp

${OBJECTDIR}/src/TTaskManager.o: nbproject/Makefile-${CND_CONF}.mk src/TTaskManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TTaskManager.o src/TTaskManager.cpp

${OBJECTDIR}/src/TParticleDomain.o: nbproject/Makefile-${CND_CONF}.mk src/TParticleDomain.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TParticleDomain.o src/TParticleDomain.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp

${OBJECTDIR}/deps/bullet/src/LinearMath/btGeometryUtil.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/LinearMath/btGeometryUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/LinearMath
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/LinearMath/btGeometryUtil.o deps/bullet/src/LinearMath/btGeometryUtil.cpp

${OBJECTDIR}/src/TMath.o: nbproject/Makefile-${CND_CONF}.mk src/TMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TMath.o src/TMath.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.o deps/bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.cpp

${OBJECTDIR}/src/TVector3.o: nbproject/Makefile-${CND_CONF}.mk src/TVector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TVector3.o src/TVector3.cpp

${OBJECTDIR}/src/lua/lgc.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lgc.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lgc.o src/lua/lgc.c

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Character/btKinematicCharacterController.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/Character/btKinematicCharacterController.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Character
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Character/btKinematicCharacterController.o deps/bullet/src/BulletDynamics/Character/btKinematicCharacterController.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.o deps/bullet/src/BulletCollision/CollisionDispatch/btGhostObject.cpp

${OBJECTDIR}/src/TFile.o: nbproject/Makefile-${CND_CONF}.mk src/TFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TFile.o src/TFile.cpp

${OBJECTDIR}/src/TRotateController.o: nbproject/Makefile-${CND_CONF}.mk src/TRotateController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TRotateController.o src/TRotateController.cpp

${OBJECTDIR}/src/TControllerFunction.o: nbproject/Makefile-${CND_CONF}.mk src/TControllerFunction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TControllerFunction.o src/TControllerFunction.cpp

${OBJECTDIR}/src/TGUIScreen.o: nbproject/Makefile-${CND_CONF}.mk src/TGUIScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUIScreen.o src/TGUIScreen.cpp

${OBJECTDIR}/src/TColliderPlane.o: nbproject/Makefile-${CND_CONF}.mk src/TColliderPlane.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TColliderPlane.o src/TColliderPlane.cpp

${OBJECTDIR}/src/TPlaneNode.o: nbproject/Makefile-${CND_CONF}.mk src/TPlaneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TPlaneNode.o src/TPlaneNode.cpp

${OBJECTDIR}/src/lua/lmem.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lmem.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lmem.o src/lua/lmem.c

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/cd_hull.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/cd_hull.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/cd_hull.o deps/bullet/Extras/ConvexDecomposition/cd_hull.cpp

${OBJECTDIR}/src/TGUIButton.o: nbproject/Makefile-${CND_CONF}.mk src/TGUIButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUIButton.o src/TGUIButton.cpp

${OBJECTDIR}/src/TController.o: nbproject/Makefile-${CND_CONF}.mk src/TController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TController.o src/TController.cpp

${OBJECTDIR}/src/TBehaviorFactory.o: nbproject/Makefile-${CND_CONF}.mk src/TBehaviorFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TBehaviorFactory.o src/TBehaviorFactory.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/bestfitobb.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/bestfitobb.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/bestfitobb.o deps/bullet/Extras/ConvexDecomposition/bestfitobb.cpp

${OBJECTDIR}/src/TParticleNode.o: nbproject/Makefile-${CND_CONF}.mk src/TParticleNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TParticleNode.o src/TParticleNode.cpp

${OBJECTDIR}/src/TRenderer.o: nbproject/Makefile-${CND_CONF}.mk src/TRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TRenderer.o src/TRenderer.cpp

${OBJECTDIR}/src/lua/liolib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/liolib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/liolib.o src/lua/liolib.c

${OBJECTDIR}/src/lua/lobject.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lobject.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lobject.o src/lua/lobject.c

${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.o deps/bullet/src/BulletDynamics/Dynamics/btContinuousDynamicsWorld.cpp

${OBJECTDIR}/src/TBView.o: nbproject/Makefile-${CND_CONF}.mk src/TBView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TBView.o src/TBView.cpp

${OBJECTDIR}/src/TColliderMesh.o: nbproject/Makefile-${CND_CONF}.mk src/TColliderMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TColliderMesh.o src/TColliderMesh.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp

${OBJECTDIR}/src/lua/lundump.o: nbproject/Makefile-${CND_CONF}.mk src/lua/lundump.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/lundump.o src/lua/lundump.c

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.o deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp

${OBJECTDIR}/src/TSL.o: nbproject/Makefile-${CND_CONF}.mk src/TSL.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TSL.o src/TSL.cpp

${OBJECTDIR}/src/TEntityManager.o: nbproject/Makefile-${CND_CONF}.mk src/TEntityManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TEntityManager.o src/TEntityManager.cpp

${OBJECTDIR}/src/TGUIDialogs.o: nbproject/Makefile-${CND_CONF}.mk src/TGUIDialogs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TGUIDialogs.o src/TGUIDialogs.cpp

${OBJECTDIR}/deps/bullet/src/LinearMath/btQuickprof.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/LinearMath/btQuickprof.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/LinearMath
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/LinearMath/btQuickprof.o deps/bullet/src/LinearMath/btQuickprof.cpp

${OBJECTDIR}/src/TIntervalDelegate.o: nbproject/Makefile-${CND_CONF}.mk src/TIntervalDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TIntervalDelegate.o src/TIntervalDelegate.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.o deps/bullet/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMesh.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.o deps/bullet/src/BulletCollision/CollisionShapes/btConvexHullShape.cpp

${OBJECTDIR}/src/TScript.o: nbproject/Makefile-${CND_CONF}.mk src/TScript.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TScript.o src/TScript.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.o deps/bullet/src/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.o deps/bullet/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp

${OBJECTDIR}/src/TSceneNodeAnimatorMaterialLayer.o: nbproject/Makefile-${CND_CONF}.mk src/TSceneNodeAnimatorMaterialLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TSceneNodeAnimatorMaterialLayer.o src/TSceneNodeAnimatorMaterialLayer.cpp

${OBJECTDIR}/tools/irrlicht/extensions/CIrrBMeshFileLoader.o: nbproject/Makefile-${CND_CONF}.mk tools/irrlicht/extensions/CIrrBMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools/irrlicht/extensions
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/tools/irrlicht/extensions/CIrrBMeshFileLoader.o tools/irrlicht/extensions/CIrrBMeshFileLoader.cpp

${OBJECTDIR}/src/TAABBox.o: nbproject/Makefile-${CND_CONF}.mk src/TAABBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TAABBox.o src/TAABBox.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.o deps/bullet/src/BulletCollision/BroadphaseCollision/btDbvt.cpp

${OBJECTDIR}/src/TIrrSoundManager.o: nbproject/Makefile-${CND_CONF}.mk src/TIrrSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TIrrSoundManager.o src/TIrrSoundManager.cpp

${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/float_math.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/Extras/ConvexDecomposition/float_math.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/Extras/ConvexDecomposition/float_math.o deps/bullet/Extras/ConvexDecomposition/float_math.cpp

${OBJECTDIR}/src/TColliderBox.o: nbproject/Makefile-${CND_CONF}.mk src/TColliderBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TColliderBox.o src/TColliderBox.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.o deps/bullet/src/BulletCollision/CollisionShapes/btShapeHull.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.o deps/bullet/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp

${OBJECTDIR}/src/TScriptState.o: nbproject/Makefile-${CND_CONF}.mk src/TScriptState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TScriptState.o src/TScriptState.cpp

${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.o deps/bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.o deps/bullet/src/BulletCollision/CollisionShapes/btCollisionShape.cpp

${OBJECTDIR}/src/TTimer.o: nbproject/Makefile-${CND_CONF}.mk src/TTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TTimer.o src/TTimer.cpp

${OBJECTDIR}/src/TSoundNode.o: nbproject/Makefile-${CND_CONF}.mk src/TSoundNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TSoundNode.o src/TSoundNode.cpp

${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.o: nbproject/Makefile-${CND_CONF}.mk deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.o deps/bullet/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp

${OBJECTDIR}/src/lua/ltablib.o: nbproject/Makefile-${CND_CONF}.mk src/lua/ltablib.c 
	${MKDIR} -p ${OBJECTDIR}/src/lua
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua/ltablib.o src/lua/ltablib.c

${OBJECTDIR}/src/TFMSound.o: nbproject/Makefile-${CND_CONF}.mk src/TFMSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_DEBUG -D_LIB -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -D__GNUWIN32__ -Iinclude -Itools/irrlicht/extensions -Isrc/lua -Ideps/bullet/src -Ideps/irrlicht/include -Isource/irrlicht -Ideps/irrklang/include -Ideps/irrlicht/source/Irrlicht -Ideps/particle2/Particle2/Particle -Ideps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TFMSound.o src/TFMSound.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Debug
	${RM} libs/debug/libTubras_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
