#
# Gererated Makefile - do not edit!
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

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Win32-Shared-Debug/MinGW-Windows

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/source/Irrlicht/CD3D9NormalMapRenderer.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcmainct.o \
	${OBJECTDIR}/source/Irrlicht/CParticleBoxEmitter.o \
	${OBJECTDIR}/source/Irrlicht/CParticlePointEmitter.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jidctred.o \
	${OBJECTDIR}/source/Irrlicht/COBJMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CZipReader.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAdd2.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jidctint.o \
	${OBJECTDIR}/source/Irrlicht/CTRFlat.o \
	${OBJECTDIR}/source/Irrlicht/os.o \
	${OBJECTDIR}/source/Irrlicht/irrXML.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jidctfst.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jutils.o \
	${OBJECTDIR}/source/Irrlicht/COpenGLNormalMapRenderer.o \
	${OBJECTDIR}/source/Irrlicht/CGUIListBox.o \
	${OBJECTDIR}/source/Irrlicht/CGUISkin.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAlpha.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcapistd.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M2.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcomapi.o \
	${OBJECTDIR}/source/Irrlicht/CImageLoaderPSD.o \
	${OBJECTDIR}/source/Irrlicht/CGUIToolBar.o \
	${OBJECTDIR}/source/Irrlicht/CZBuffer.o \
	${OBJECTDIR}/source/Irrlicht/CSceneCollisionManager.o \
	${OBJECTDIR}/source/Irrlicht/CGUIFont.o \
	${OBJECTDIR}/source/Irrlicht/CNullDriver.o \
	${OBJECTDIR}/source/Irrlicht/CBoneSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CFileList.o \
	${OBJECTDIR}/source/Irrlicht/CAnimatedMeshSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CDefaultSceneNodeAnimatorFactory.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCameraMaya.o \
	${OBJECTDIR}/source/Irrlicht/CMY3DMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureWire2.o \
	${OBJECTDIR}/source/Irrlicht/CImageLoaderPNG.o \
	${OBJECTDIR}/source/Irrlicht/CParticleCylinderEmitter.o \
	${OBJECTDIR}/source/Irrlicht/CAnimatedMeshMD2.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jquant1.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCameraFPS.o \
	${OBJECTDIR}/source/Irrlicht/COpenGLExtensionHandler.o \
	${OBJECTDIR}/source/Irrlicht/CGUIComboBox.o \
	${OBJECTDIR}/source/Irrlicht/CColorConverter.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M1.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdpostct.o \
	${OBJECTDIR}/source/Irrlicht/CTriangleBBSelector.o \
	${OBJECTDIR}/source/Irrlicht/CImageLoaderWAL.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureLightMapGouraud2_M4.o \
	${OBJECTDIR}/source/Irrlicht/CSTLMeshWriter.o \
	${OBJECTDIR}/source/Irrlicht/CGUITable.o \
	${OBJECTDIR}/source/Irrlicht/CGUICheckBox.o \
	${OBJECTDIR}/source/Irrlicht/CTRGouraudAlphaNoZ2.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngwrite.o \
	${OBJECTDIR}/source/Irrlicht/CMemoryReadFile.o \
	${OBJECTDIR}/source/Irrlicht/COpenGLSLMaterialRenderer.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngset.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcmaster.o \
	${OBJECTDIR}/source/Irrlicht/COctTreeSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CCameraSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/IBurningShader.o \
	${OBJECTDIR}/source/Irrlicht/CFPSCounter.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorRotation.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorTexture.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jchuff.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudNoZ2.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraud.o \
	${OBJECTDIR}/source/Irrlicht/CLogger.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdinput.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFollowSpline.o \
	${OBJECTDIR}/source/Irrlicht/CGUIFileOpenDialog.o \
	${OBJECTDIR}/source/Irrlicht/CTerrainTriangleSelector.o \
	${OBJECTDIR}/source/Irrlicht/Irrlicht.o \
	${OBJECTDIR}/source/Irrlicht/CIrrDeviceWin32.o \
	${OBJECTDIR}/source/Irrlicht/CSkyDomeSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jerror.o \
	${OBJECTDIR}/source/Irrlicht/CImageLoaderTGA.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdmainct.o \
	${OBJECTDIR}/source/Irrlicht/CSkyBoxSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/zlib/compress.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdmerge.o \
	${OBJECTDIR}/source/Irrlicht/zlib/deflate.o \
	${OBJECTDIR}/source/Irrlicht/CParticleGravityAffector.o \
	${OBJECTDIR}/source/Irrlicht/CParticleRingEmitter.o \
	${OBJECTDIR}/source/Irrlicht/CDummyTransformationSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CMeshSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CImageLoaderPPM.o \
	${OBJECTDIR}/source/Irrlicht/zlib/zutil.o \
	${OBJECTDIR}/source/Irrlicht/COgreMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CParticleAnimatedMeshSceneNodeEmitter.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraud2.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcinit.o \
	${OBJECTDIR}/source/Irrlicht/CB3DMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CImageWriterJPG.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdtrans.o \
	${OBJECTDIR}/source/Irrlicht/CTRFlatWire.o \
	${OBJECTDIR}/source/Irrlicht/CGUIEnvironment.o \
	${OBJECTDIR}/source/Irrlicht/libpng/png.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jctrans.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctint.o \
	${OBJECTDIR}/source/Irrlicht/CD3D8NormalMapRenderer.o \
	${OBJECTDIR}/source/Irrlicht/CLWOMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CParticleAttractionAffector.o \
	${OBJECTDIR}/source/Irrlicht/CGUISpriteBank.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcmarker.o \
	${OBJECTDIR}/source/Irrlicht/CCSMLoader.o \
	${OBJECTDIR}/source/Irrlicht/CD3D8ShaderMaterialRenderer.o \
	${OBJECTDIR}/source/Irrlicht/CXMLWriter.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jmemnobs.o \
	${OBJECTDIR}/source/Irrlicht/CGUIStaticText.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jquant2.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngrtran.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudNoZ.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcphuff.o \
	${OBJECTDIR}/source/Irrlicht/CGUIMenu.o \
	${OBJECTDIR}/source/Irrlicht/CTRGouraudWire.o \
	${OBJECTDIR}/source/Irrlicht/CGUIColorSelectDialog.o \
	${OBJECTDIR}/source/Irrlicht/CIrrDeviceSDL.o \
	${OBJECTDIR}/source/Irrlicht/COCTLoader.o \
	${OBJECTDIR}/source/Irrlicht/CGUIContextMenu.o \
	${OBJECTDIR}/source/Irrlicht/CDMFLoader.o \
	${OBJECTDIR}/source/Irrlicht/CLightSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CTRGouraud2.o \
	${OBJECTDIR}/source/Irrlicht/CColladaFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngread.o \
	${OBJECTDIR}/source/Irrlicht/CIrrMeshWriter.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorDelete.o \
	${OBJECTDIR}/source/Irrlicht/CLMTSMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CFileSystem.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFlyStraight.o \
	${OBJECTDIR}/source/Irrlicht/CD3D9ParallaxMapRenderer.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdapimin.o \
	${OBJECTDIR}/source/Irrlicht/CGUIMessageBox.o \
	${OBJECTDIR}/source/Irrlicht/CXMLReader.o \
	${OBJECTDIR}/source/Irrlicht/CTerrainSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jidctflt.o \
	${OBJECTDIR}/source/Irrlicht/COpenGLShaderMaterialRenderer.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctfst.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdsample.o \
	${OBJECTDIR}/source/Irrlicht/CSphereSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngrutil.o \
	${OBJECTDIR}/source/Irrlicht/zlib/adler32.o \
	${OBJECTDIR}/source/Irrlicht/CD3D8Texture.o \
	${OBJECTDIR}/source/Irrlicht/CWaterSurfaceSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CSceneManager.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureDetailMap2.o \
	${OBJECTDIR}/source/Irrlicht/CImageLoaderBMP.o \
	${OBJECTDIR}/source/Irrlicht/CGUIMeshViewer.o \
	${OBJECTDIR}/source/Irrlicht/CImageWriterTGA.o \
	${OBJECTDIR}/source/Irrlicht/CD3D8Driver.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctflt.o \
	${OBJECTDIR}/source/Irrlicht/CIrrDeviceLinux.o \
	${OBJECTDIR}/source/Irrlicht/CQ3LevelMesh.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngmem.o \
	${OBJECTDIR}/source/Irrlicht/CImageLoaderJPG.o \
	${OBJECTDIR}/source/Irrlicht/CSoftwareDriver2.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jccolor.o \
	${OBJECTDIR}/source/Irrlicht/CVolumeLightSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/COctTreeTriangleSelector.o \
	${OBJECTDIR}/source/Irrlicht/CMS3DMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CSkinnedMesh.o \
	${OBJECTDIR}/source/Irrlicht/CDefaultGUIElementFactory.o \
	${OBJECTDIR}/source/Irrlicht/CMeshManipulator.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_Add.o \
	${OBJECTDIR}/source/Irrlicht/CIrrDeviceStub.o \
	${OBJECTDIR}/source/Irrlicht/CPakReader.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudWire.o \
	${OBJECTDIR}/source/Irrlicht/CAnimatedMeshMD3.o \
	${OBJECTDIR}/source/Irrlicht/CCubeSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CDepthBuffer.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M4.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jmemmgr.o \
	${OBJECTDIR}/source/Irrlicht/CQuake3ShaderSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngwtran.o \
	${OBJECTDIR}/source/Irrlicht/CParticleFadeOutAffector.o \
	${OBJECTDIR}/source/Irrlicht/CD3D9ShaderMaterialRenderer.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFlyCircle.o \
	${OBJECTDIR}/source/Irrlicht/CGUIScrollBar.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdcolor.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jddctmgr.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngwutil.o \
	${OBJECTDIR}/source/Irrlicht/CD3D9HLSLMaterialRenderer.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jccoefct.o \
	${OBJECTDIR}/source/Irrlicht/CImage.o \
	${OBJECTDIR}/source/Irrlicht/CSTLMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAdd.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdmaster.o \
	${OBJECTDIR}/source/Irrlicht/CGeometryCreator.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdphuff.o \
	${OBJECTDIR}/source/Irrlicht/CGUIEditBox.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAlphaNoZ.o \
	${OBJECTDIR}/source/Irrlicht/zlib/inffast.o \
	${OBJECTDIR}/source/Irrlicht/COSOperator.o \
	${OBJECTDIR}/source/Irrlicht/CMetaTriangleSelector.o \
	${OBJECTDIR}/source/Irrlicht/CMD3MeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureFlat.o \
	${OBJECTDIR}/source/Irrlicht/CDefaultSceneNodeFactory.o \
	${OBJECTDIR}/source/Irrlicht/CReadFile.o \
	${OBJECTDIR}/source/Irrlicht/CTriangleSelector.o \
	${OBJECTDIR}/source/Irrlicht/CImageWriterPNG.o \
	${OBJECTDIR}/source/Irrlicht/CD3D8ParallaxMapRenderer.o \
	${OBJECTDIR}/source/Irrlicht/CAttributes.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdmarker.o \
	${OBJECTDIR}/source/Irrlicht/CGUIModalScreen.o \
	${OBJECTDIR}/source/Irrlicht/CParticleRotationAffector.o \
	${OBJECTDIR}/source/Irrlicht/CTextSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/zlib/crc32.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureBlend.o \
	${OBJECTDIR}/source/Irrlicht/CBurningShader_Raster_Reference.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngwio.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdapistd.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdatasrc.o \
	${OBJECTDIR}/source/Irrlicht/CGUITabControl.o \
	${OBJECTDIR}/source/Irrlicht/CEmptySceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CParticleSphereEmitter.o \
	${OBJECTDIR}/source/Irrlicht/CColladaMeshWriter.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdcoefct.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcdctmgr.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcparam.o \
	${OBJECTDIR}/source/Irrlicht/COpenGLParallaxMapRenderer.o \
	${OBJECTDIR}/source/Irrlicht/CParticleSystemSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdatadst.o \
	${OBJECTDIR}/source/Irrlicht/CMeshCache.o \
	${OBJECTDIR}/source/Irrlicht/CLimitReadFile.o \
	${OBJECTDIR}/source/Irrlicht/CD3D9Driver.o \
	${OBJECTDIR}/source/Irrlicht/CSoftwareTexture2.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcapimin.o \
	${OBJECTDIR}/source/Irrlicht/CGUIButton.o \
	${OBJECTDIR}/source/Irrlicht/zlib/inftrees.o \
	${OBJECTDIR}/source/Irrlicht/CImageWriterBMP.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngtrans.o \
	${OBJECTDIR}/source/Irrlicht/CSoftwareDriver.o \
	${OBJECTDIR}/source/Irrlicht/CGUIInOutFader.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngerror.o \
	${OBJECTDIR}/source/Irrlicht/CD3D9Texture.o \
	${OBJECTDIR}/source/Irrlicht/CParticleMeshEmitter.o \
	${OBJECTDIR}/source/Irrlicht/CIrrMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcsample.o \
	${OBJECTDIR}/source/Irrlicht/CMD2MeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/zlib/trees.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jcprepct.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAddNoZ2.o \
	${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCollisionResponse.o \
	${OBJECTDIR}/source/Irrlicht/jpeglib/jdhuff.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudVertexAlpha2.o \
	${OBJECTDIR}/source/Irrlicht/CBillboardSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/COpenGLTexture.o \
	${OBJECTDIR}/source/Irrlicht/CVideoModeList.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngget.o \
	${OBJECTDIR}/source/Irrlicht/CTRGouraud.o \
	${OBJECTDIR}/source/Irrlicht/CImageWriterPPM.o \
	${OBJECTDIR}/source/Irrlicht/CGUIImage.o \
	${OBJECTDIR}/source/Irrlicht/zlib/uncompr.o \
	${OBJECTDIR}/source/Irrlicht/CShadowVolumeSceneNode.o \
	${OBJECTDIR}/source/Irrlicht/CImageWriterPSD.o \
	${OBJECTDIR}/source/Irrlicht/CTRTextureFlatWire.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngpread.o \
	${OBJECTDIR}/source/Irrlicht/CTRGouraudAlpha2.o \
	${OBJECTDIR}/source/Irrlicht/C3DSMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CGUISpinBox.o \
	${OBJECTDIR}/source/Irrlicht/CXMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/CBSPMeshFileLoader.o \
	${OBJECTDIR}/source/Irrlicht/zlib/inflate.o \
	${OBJECTDIR}/source/Irrlicht/COpenGLDriver.o \
	${OBJECTDIR}/source/Irrlicht/CImageLoaderPCX.o \
	${OBJECTDIR}/source/Irrlicht/CSoftwareTexture.o \
	${OBJECTDIR}/source/Irrlicht/libpng/pngrio.o \
	${OBJECTDIR}/source/Irrlicht/CImageWriterPCX.o \
	${OBJECTDIR}/source/Irrlicht/CWriteFile.o \
	${OBJECTDIR}/source/Irrlicht/CGUIWindow.o

# C Compiler Flags
CFLAGS=-fcheck-new

# CC Compiler Flags
CCFLAGS=-fcheck-new
CXXFLAGS=-fcheck-new

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lopengl32 -lgdi32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} lib/Win32-gcc/Irrlicht_d.dll

lib/Win32-gcc/Irrlicht_d.dll: ${OBJECTFILES}
	${MKDIR} -p lib/Win32-gcc
	g++.exe -shared -o lib/Win32-gcc/Irrlicht_d.dll ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/source/Irrlicht/CD3D9NormalMapRenderer.o: source/Irrlicht/CD3D9NormalMapRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D9NormalMapRenderer.o source/Irrlicht/CD3D9NormalMapRenderer.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jcmainct.o: source/Irrlicht/jpeglib/jcmainct.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcmainct.o source/Irrlicht/jpeglib/jcmainct.c

${OBJECTDIR}/source/Irrlicht/CParticleBoxEmitter.o: source/Irrlicht/CParticleBoxEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleBoxEmitter.o source/Irrlicht/CParticleBoxEmitter.cpp

${OBJECTDIR}/source/Irrlicht/CParticlePointEmitter.o: source/Irrlicht/CParticlePointEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticlePointEmitter.o source/Irrlicht/CParticlePointEmitter.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jidctred.o: source/Irrlicht/jpeglib/jidctred.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jidctred.o source/Irrlicht/jpeglib/jidctred.c

${OBJECTDIR}/source/Irrlicht/COBJMeshFileLoader.o: source/Irrlicht/COBJMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COBJMeshFileLoader.o source/Irrlicht/COBJMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CZipReader.o: source/Irrlicht/CZipReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CZipReader.o source/Irrlicht/CZipReader.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAdd2.o: source/Irrlicht/CTRTextureGouraudAdd2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAdd2.o source/Irrlicht/CTRTextureGouraudAdd2.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jidctint.o: source/Irrlicht/jpeglib/jidctint.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jidctint.o source/Irrlicht/jpeglib/jidctint.c

${OBJECTDIR}/source/Irrlicht/CTRFlat.o: source/Irrlicht/CTRFlat.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRFlat.o source/Irrlicht/CTRFlat.cpp

${OBJECTDIR}/source/Irrlicht/os.o: source/Irrlicht/os.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/os.o source/Irrlicht/os.cpp

${OBJECTDIR}/source/Irrlicht/irrXML.o: source/Irrlicht/irrXML.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/irrXML.o source/Irrlicht/irrXML.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jidctfst.o: source/Irrlicht/jpeglib/jidctfst.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jidctfst.o source/Irrlicht/jpeglib/jidctfst.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jutils.o: source/Irrlicht/jpeglib/jutils.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jutils.o source/Irrlicht/jpeglib/jutils.c

${OBJECTDIR}/source/Irrlicht/COpenGLNormalMapRenderer.o: source/Irrlicht/COpenGLNormalMapRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COpenGLNormalMapRenderer.o source/Irrlicht/COpenGLNormalMapRenderer.cpp

${OBJECTDIR}/source/Irrlicht/CGUIListBox.o: source/Irrlicht/CGUIListBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIListBox.o source/Irrlicht/CGUIListBox.cpp

${OBJECTDIR}/source/Irrlicht/CGUISkin.o: source/Irrlicht/CGUISkin.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUISkin.o source/Irrlicht/CGUISkin.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAlpha.o: source/Irrlicht/CTRTextureGouraudAlpha.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAlpha.o source/Irrlicht/CTRTextureGouraudAlpha.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jcapistd.o: source/Irrlicht/jpeglib/jcapistd.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcapistd.o source/Irrlicht/jpeglib/jcapistd.c

${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M2.o: source/Irrlicht/CTRTextureLightMap2_M2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M2.o source/Irrlicht/CTRTextureLightMap2_M2.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jcomapi.o: source/Irrlicht/jpeglib/jcomapi.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcomapi.o source/Irrlicht/jpeglib/jcomapi.c

${OBJECTDIR}/source/Irrlicht/CImageLoaderPSD.o: source/Irrlicht/CImageLoaderPSD.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageLoaderPSD.o source/Irrlicht/CImageLoaderPSD.cpp

${OBJECTDIR}/source/Irrlicht/CGUIToolBar.o: source/Irrlicht/CGUIToolBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIToolBar.o source/Irrlicht/CGUIToolBar.cpp

${OBJECTDIR}/source/Irrlicht/CZBuffer.o: source/Irrlicht/CZBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CZBuffer.o source/Irrlicht/CZBuffer.cpp

${OBJECTDIR}/source/Irrlicht/CSceneCollisionManager.o: source/Irrlicht/CSceneCollisionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneCollisionManager.o source/Irrlicht/CSceneCollisionManager.cpp

${OBJECTDIR}/source/Irrlicht/CGUIFont.o: source/Irrlicht/CGUIFont.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIFont.o source/Irrlicht/CGUIFont.cpp

${OBJECTDIR}/source/Irrlicht/CNullDriver.o: source/Irrlicht/CNullDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CNullDriver.o source/Irrlicht/CNullDriver.cpp

${OBJECTDIR}/source/Irrlicht/CBoneSceneNode.o: source/Irrlicht/CBoneSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CBoneSceneNode.o source/Irrlicht/CBoneSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CFileList.o: source/Irrlicht/CFileList.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CFileList.o source/Irrlicht/CFileList.cpp

${OBJECTDIR}/source/Irrlicht/CAnimatedMeshSceneNode.o: source/Irrlicht/CAnimatedMeshSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CAnimatedMeshSceneNode.o source/Irrlicht/CAnimatedMeshSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CDefaultSceneNodeAnimatorFactory.o: source/Irrlicht/CDefaultSceneNodeAnimatorFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CDefaultSceneNodeAnimatorFactory.o source/Irrlicht/CDefaultSceneNodeAnimatorFactory.cpp

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCameraMaya.o: source/Irrlicht/CSceneNodeAnimatorCameraMaya.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCameraMaya.o source/Irrlicht/CSceneNodeAnimatorCameraMaya.cpp

${OBJECTDIR}/source/Irrlicht/CMY3DMeshFileLoader.o: source/Irrlicht/CMY3DMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMY3DMeshFileLoader.o source/Irrlicht/CMY3DMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureWire2.o: source/Irrlicht/CTRTextureWire2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureWire2.o source/Irrlicht/CTRTextureWire2.cpp

${OBJECTDIR}/source/Irrlicht/CImageLoaderPNG.o: source/Irrlicht/CImageLoaderPNG.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageLoaderPNG.o source/Irrlicht/CImageLoaderPNG.cpp

${OBJECTDIR}/source/Irrlicht/CParticleCylinderEmitter.o: source/Irrlicht/CParticleCylinderEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleCylinderEmitter.o source/Irrlicht/CParticleCylinderEmitter.cpp

${OBJECTDIR}/source/Irrlicht/CAnimatedMeshMD2.o: source/Irrlicht/CAnimatedMeshMD2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CAnimatedMeshMD2.o source/Irrlicht/CAnimatedMeshMD2.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jquant1.o: source/Irrlicht/jpeglib/jquant1.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jquant1.o source/Irrlicht/jpeglib/jquant1.c

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCameraFPS.o: source/Irrlicht/CSceneNodeAnimatorCameraFPS.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCameraFPS.o source/Irrlicht/CSceneNodeAnimatorCameraFPS.cpp

${OBJECTDIR}/source/Irrlicht/COpenGLExtensionHandler.o: source/Irrlicht/COpenGLExtensionHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COpenGLExtensionHandler.o source/Irrlicht/COpenGLExtensionHandler.cpp

${OBJECTDIR}/source/Irrlicht/CGUIComboBox.o: source/Irrlicht/CGUIComboBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIComboBox.o source/Irrlicht/CGUIComboBox.cpp

${OBJECTDIR}/source/Irrlicht/CColorConverter.o: source/Irrlicht/CColorConverter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CColorConverter.o source/Irrlicht/CColorConverter.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M1.o: source/Irrlicht/CTRTextureLightMap2_M1.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M1.o source/Irrlicht/CTRTextureLightMap2_M1.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdpostct.o: source/Irrlicht/jpeglib/jdpostct.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdpostct.o source/Irrlicht/jpeglib/jdpostct.c

${OBJECTDIR}/source/Irrlicht/CTriangleBBSelector.o: source/Irrlicht/CTriangleBBSelector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTriangleBBSelector.o source/Irrlicht/CTriangleBBSelector.cpp

${OBJECTDIR}/source/Irrlicht/CImageLoaderWAL.o: source/Irrlicht/CImageLoaderWAL.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageLoaderWAL.o source/Irrlicht/CImageLoaderWAL.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureLightMapGouraud2_M4.o: source/Irrlicht/CTRTextureLightMapGouraud2_M4.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureLightMapGouraud2_M4.o source/Irrlicht/CTRTextureLightMapGouraud2_M4.cpp

${OBJECTDIR}/source/Irrlicht/CSTLMeshWriter.o: source/Irrlicht/CSTLMeshWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSTLMeshWriter.o source/Irrlicht/CSTLMeshWriter.cpp

${OBJECTDIR}/source/Irrlicht/CGUITable.o: source/Irrlicht/CGUITable.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUITable.o source/Irrlicht/CGUITable.cpp

${OBJECTDIR}/source/Irrlicht/CGUICheckBox.o: source/Irrlicht/CGUICheckBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUICheckBox.o source/Irrlicht/CGUICheckBox.cpp

${OBJECTDIR}/source/Irrlicht/CTRGouraudAlphaNoZ2.o: source/Irrlicht/CTRGouraudAlphaNoZ2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRGouraudAlphaNoZ2.o source/Irrlicht/CTRGouraudAlphaNoZ2.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngwrite.o: source/Irrlicht/libpng/pngwrite.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngwrite.o source/Irrlicht/libpng/pngwrite.c

${OBJECTDIR}/source/Irrlicht/CMemoryReadFile.o: source/Irrlicht/CMemoryReadFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMemoryReadFile.o source/Irrlicht/CMemoryReadFile.cpp

${OBJECTDIR}/source/Irrlicht/COpenGLSLMaterialRenderer.o: source/Irrlicht/COpenGLSLMaterialRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COpenGLSLMaterialRenderer.o source/Irrlicht/COpenGLSLMaterialRenderer.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngset.o: source/Irrlicht/libpng/pngset.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngset.o source/Irrlicht/libpng/pngset.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jcmaster.o: source/Irrlicht/jpeglib/jcmaster.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcmaster.o source/Irrlicht/jpeglib/jcmaster.c

${OBJECTDIR}/source/Irrlicht/COctTreeSceneNode.o: source/Irrlicht/COctTreeSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COctTreeSceneNode.o source/Irrlicht/COctTreeSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CCameraSceneNode.o: source/Irrlicht/CCameraSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CCameraSceneNode.o source/Irrlicht/CCameraSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/IBurningShader.o: source/Irrlicht/IBurningShader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/IBurningShader.o source/Irrlicht/IBurningShader.cpp

${OBJECTDIR}/source/Irrlicht/CFPSCounter.o: source/Irrlicht/CFPSCounter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CFPSCounter.o source/Irrlicht/CFPSCounter.cpp

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorRotation.o: source/Irrlicht/CSceneNodeAnimatorRotation.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorRotation.o source/Irrlicht/CSceneNodeAnimatorRotation.cpp

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorTexture.o: source/Irrlicht/CSceneNodeAnimatorTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorTexture.o source/Irrlicht/CSceneNodeAnimatorTexture.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jchuff.o: source/Irrlicht/jpeglib/jchuff.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jchuff.o source/Irrlicht/jpeglib/jchuff.c

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudNoZ2.o: source/Irrlicht/CTRTextureGouraudNoZ2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudNoZ2.o source/Irrlicht/CTRTextureGouraudNoZ2.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraud.o: source/Irrlicht/CTRTextureGouraud.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraud.o source/Irrlicht/CTRTextureGouraud.cpp

${OBJECTDIR}/source/Irrlicht/CLogger.o: source/Irrlicht/CLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CLogger.o source/Irrlicht/CLogger.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdinput.o: source/Irrlicht/jpeglib/jdinput.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdinput.o source/Irrlicht/jpeglib/jdinput.c

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFollowSpline.o: source/Irrlicht/CSceneNodeAnimatorFollowSpline.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFollowSpline.o source/Irrlicht/CSceneNodeAnimatorFollowSpline.cpp

${OBJECTDIR}/source/Irrlicht/CGUIFileOpenDialog.o: source/Irrlicht/CGUIFileOpenDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIFileOpenDialog.o source/Irrlicht/CGUIFileOpenDialog.cpp

${OBJECTDIR}/source/Irrlicht/CTerrainTriangleSelector.o: source/Irrlicht/CTerrainTriangleSelector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTerrainTriangleSelector.o source/Irrlicht/CTerrainTriangleSelector.cpp

${OBJECTDIR}/source/Irrlicht/Irrlicht.o: source/Irrlicht/Irrlicht.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/Irrlicht.o source/Irrlicht/Irrlicht.cpp

${OBJECTDIR}/source/Irrlicht/CIrrDeviceWin32.o: source/Irrlicht/CIrrDeviceWin32.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CIrrDeviceWin32.o source/Irrlicht/CIrrDeviceWin32.cpp

${OBJECTDIR}/source/Irrlicht/CSkyDomeSceneNode.o: source/Irrlicht/CSkyDomeSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSkyDomeSceneNode.o source/Irrlicht/CSkyDomeSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jerror.o: source/Irrlicht/jpeglib/jerror.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jerror.o source/Irrlicht/jpeglib/jerror.c

${OBJECTDIR}/source/Irrlicht/CImageLoaderTGA.o: source/Irrlicht/CImageLoaderTGA.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageLoaderTGA.o source/Irrlicht/CImageLoaderTGA.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdmainct.o: source/Irrlicht/jpeglib/jdmainct.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdmainct.o source/Irrlicht/jpeglib/jdmainct.c

${OBJECTDIR}/source/Irrlicht/CSkyBoxSceneNode.o: source/Irrlicht/CSkyBoxSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSkyBoxSceneNode.o source/Irrlicht/CSkyBoxSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/zlib/compress.o: source/Irrlicht/zlib/compress.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/compress.o source/Irrlicht/zlib/compress.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jdmerge.o: source/Irrlicht/jpeglib/jdmerge.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdmerge.o source/Irrlicht/jpeglib/jdmerge.c

${OBJECTDIR}/source/Irrlicht/zlib/deflate.o: source/Irrlicht/zlib/deflate.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/deflate.o source/Irrlicht/zlib/deflate.c

${OBJECTDIR}/source/Irrlicht/CParticleGravityAffector.o: source/Irrlicht/CParticleGravityAffector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleGravityAffector.o source/Irrlicht/CParticleGravityAffector.cpp

${OBJECTDIR}/source/Irrlicht/CParticleRingEmitter.o: source/Irrlicht/CParticleRingEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleRingEmitter.o source/Irrlicht/CParticleRingEmitter.cpp

${OBJECTDIR}/source/Irrlicht/CDummyTransformationSceneNode.o: source/Irrlicht/CDummyTransformationSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CDummyTransformationSceneNode.o source/Irrlicht/CDummyTransformationSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CMeshSceneNode.o: source/Irrlicht/CMeshSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMeshSceneNode.o source/Irrlicht/CMeshSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CImageLoaderPPM.o: source/Irrlicht/CImageLoaderPPM.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageLoaderPPM.o source/Irrlicht/CImageLoaderPPM.cpp

${OBJECTDIR}/source/Irrlicht/zlib/zutil.o: source/Irrlicht/zlib/zutil.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/zutil.o source/Irrlicht/zlib/zutil.c

${OBJECTDIR}/source/Irrlicht/COgreMeshFileLoader.o: source/Irrlicht/COgreMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COgreMeshFileLoader.o source/Irrlicht/COgreMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CParticleAnimatedMeshSceneNodeEmitter.o: source/Irrlicht/CParticleAnimatedMeshSceneNodeEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleAnimatedMeshSceneNodeEmitter.o source/Irrlicht/CParticleAnimatedMeshSceneNodeEmitter.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraud2.o: source/Irrlicht/CTRTextureGouraud2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraud2.o source/Irrlicht/CTRTextureGouraud2.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jcinit.o: source/Irrlicht/jpeglib/jcinit.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcinit.o source/Irrlicht/jpeglib/jcinit.c

${OBJECTDIR}/source/Irrlicht/CB3DMeshFileLoader.o: source/Irrlicht/CB3DMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CB3DMeshFileLoader.o source/Irrlicht/CB3DMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CImageWriterJPG.o: source/Irrlicht/CImageWriterJPG.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageWriterJPG.o source/Irrlicht/CImageWriterJPG.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdtrans.o: source/Irrlicht/jpeglib/jdtrans.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdtrans.o source/Irrlicht/jpeglib/jdtrans.c

${OBJECTDIR}/source/Irrlicht/CTRFlatWire.o: source/Irrlicht/CTRFlatWire.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRFlatWire.o source/Irrlicht/CTRFlatWire.cpp

${OBJECTDIR}/source/Irrlicht/CGUIEnvironment.o: source/Irrlicht/CGUIEnvironment.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIEnvironment.o source/Irrlicht/CGUIEnvironment.cpp

${OBJECTDIR}/source/Irrlicht/libpng/png.o: source/Irrlicht/libpng/png.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/png.o source/Irrlicht/libpng/png.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jctrans.o: source/Irrlicht/jpeglib/jctrans.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jctrans.o source/Irrlicht/jpeglib/jctrans.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctint.o: source/Irrlicht/jpeglib/jfdctint.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctint.o source/Irrlicht/jpeglib/jfdctint.c

${OBJECTDIR}/source/Irrlicht/CD3D8NormalMapRenderer.o: source/Irrlicht/CD3D8NormalMapRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D8NormalMapRenderer.o source/Irrlicht/CD3D8NormalMapRenderer.cpp

${OBJECTDIR}/source/Irrlicht/CLWOMeshFileLoader.o: source/Irrlicht/CLWOMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CLWOMeshFileLoader.o source/Irrlicht/CLWOMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CParticleAttractionAffector.o: source/Irrlicht/CParticleAttractionAffector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleAttractionAffector.o source/Irrlicht/CParticleAttractionAffector.cpp

${OBJECTDIR}/source/Irrlicht/CGUISpriteBank.o: source/Irrlicht/CGUISpriteBank.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUISpriteBank.o source/Irrlicht/CGUISpriteBank.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jcmarker.o: source/Irrlicht/jpeglib/jcmarker.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcmarker.o source/Irrlicht/jpeglib/jcmarker.c

${OBJECTDIR}/source/Irrlicht/CCSMLoader.o: source/Irrlicht/CCSMLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CCSMLoader.o source/Irrlicht/CCSMLoader.cpp

${OBJECTDIR}/source/Irrlicht/CD3D8ShaderMaterialRenderer.o: source/Irrlicht/CD3D8ShaderMaterialRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D8ShaderMaterialRenderer.o source/Irrlicht/CD3D8ShaderMaterialRenderer.cpp

${OBJECTDIR}/source/Irrlicht/CXMLWriter.o: source/Irrlicht/CXMLWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CXMLWriter.o source/Irrlicht/CXMLWriter.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jmemnobs.o: source/Irrlicht/jpeglib/jmemnobs.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jmemnobs.o source/Irrlicht/jpeglib/jmemnobs.c

${OBJECTDIR}/source/Irrlicht/CGUIStaticText.o: source/Irrlicht/CGUIStaticText.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIStaticText.o source/Irrlicht/CGUIStaticText.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jquant2.o: source/Irrlicht/jpeglib/jquant2.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jquant2.o source/Irrlicht/jpeglib/jquant2.c

${OBJECTDIR}/source/Irrlicht/libpng/pngrtran.o: source/Irrlicht/libpng/pngrtran.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngrtran.o source/Irrlicht/libpng/pngrtran.c

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudNoZ.o: source/Irrlicht/CTRTextureGouraudNoZ.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudNoZ.o source/Irrlicht/CTRTextureGouraudNoZ.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jcphuff.o: source/Irrlicht/jpeglib/jcphuff.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcphuff.o source/Irrlicht/jpeglib/jcphuff.c

${OBJECTDIR}/source/Irrlicht/CGUIMenu.o: source/Irrlicht/CGUIMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIMenu.o source/Irrlicht/CGUIMenu.cpp

${OBJECTDIR}/source/Irrlicht/CTRGouraudWire.o: source/Irrlicht/CTRGouraudWire.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRGouraudWire.o source/Irrlicht/CTRGouraudWire.cpp

${OBJECTDIR}/source/Irrlicht/CGUIColorSelectDialog.o: source/Irrlicht/CGUIColorSelectDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIColorSelectDialog.o source/Irrlicht/CGUIColorSelectDialog.cpp

${OBJECTDIR}/source/Irrlicht/CIrrDeviceSDL.o: source/Irrlicht/CIrrDeviceSDL.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CIrrDeviceSDL.o source/Irrlicht/CIrrDeviceSDL.cpp

${OBJECTDIR}/source/Irrlicht/COCTLoader.o: source/Irrlicht/COCTLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COCTLoader.o source/Irrlicht/COCTLoader.cpp

${OBJECTDIR}/source/Irrlicht/CGUIContextMenu.o: source/Irrlicht/CGUIContextMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIContextMenu.o source/Irrlicht/CGUIContextMenu.cpp

${OBJECTDIR}/source/Irrlicht/CDMFLoader.o: source/Irrlicht/CDMFLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CDMFLoader.o source/Irrlicht/CDMFLoader.cpp

${OBJECTDIR}/source/Irrlicht/CLightSceneNode.o: source/Irrlicht/CLightSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CLightSceneNode.o source/Irrlicht/CLightSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CTRGouraud2.o: source/Irrlicht/CTRGouraud2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRGouraud2.o source/Irrlicht/CTRGouraud2.cpp

${OBJECTDIR}/source/Irrlicht/CColladaFileLoader.o: source/Irrlicht/CColladaFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CColladaFileLoader.o source/Irrlicht/CColladaFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngread.o: source/Irrlicht/libpng/pngread.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngread.o source/Irrlicht/libpng/pngread.c

${OBJECTDIR}/source/Irrlicht/CIrrMeshWriter.o: source/Irrlicht/CIrrMeshWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CIrrMeshWriter.o source/Irrlicht/CIrrMeshWriter.cpp

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorDelete.o: source/Irrlicht/CSceneNodeAnimatorDelete.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorDelete.o source/Irrlicht/CSceneNodeAnimatorDelete.cpp

${OBJECTDIR}/source/Irrlicht/CLMTSMeshFileLoader.o: source/Irrlicht/CLMTSMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CLMTSMeshFileLoader.o source/Irrlicht/CLMTSMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CFileSystem.o: source/Irrlicht/CFileSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CFileSystem.o source/Irrlicht/CFileSystem.cpp

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFlyStraight.o: source/Irrlicht/CSceneNodeAnimatorFlyStraight.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFlyStraight.o source/Irrlicht/CSceneNodeAnimatorFlyStraight.cpp

${OBJECTDIR}/source/Irrlicht/CD3D9ParallaxMapRenderer.o: source/Irrlicht/CD3D9ParallaxMapRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D9ParallaxMapRenderer.o source/Irrlicht/CD3D9ParallaxMapRenderer.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdapimin.o: source/Irrlicht/jpeglib/jdapimin.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdapimin.o source/Irrlicht/jpeglib/jdapimin.c

${OBJECTDIR}/source/Irrlicht/CGUIMessageBox.o: source/Irrlicht/CGUIMessageBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIMessageBox.o source/Irrlicht/CGUIMessageBox.cpp

${OBJECTDIR}/source/Irrlicht/CXMLReader.o: source/Irrlicht/CXMLReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CXMLReader.o source/Irrlicht/CXMLReader.cpp

${OBJECTDIR}/source/Irrlicht/CTerrainSceneNode.o: source/Irrlicht/CTerrainSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTerrainSceneNode.o source/Irrlicht/CTerrainSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jidctflt.o: source/Irrlicht/jpeglib/jidctflt.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jidctflt.o source/Irrlicht/jpeglib/jidctflt.c

${OBJECTDIR}/source/Irrlicht/COpenGLShaderMaterialRenderer.o: source/Irrlicht/COpenGLShaderMaterialRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COpenGLShaderMaterialRenderer.o source/Irrlicht/COpenGLShaderMaterialRenderer.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctfst.o: source/Irrlicht/jpeglib/jfdctfst.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctfst.o source/Irrlicht/jpeglib/jfdctfst.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jdsample.o: source/Irrlicht/jpeglib/jdsample.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdsample.o source/Irrlicht/jpeglib/jdsample.c

${OBJECTDIR}/source/Irrlicht/CSphereSceneNode.o: source/Irrlicht/CSphereSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSphereSceneNode.o source/Irrlicht/CSphereSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngrutil.o: source/Irrlicht/libpng/pngrutil.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngrutil.o source/Irrlicht/libpng/pngrutil.c

${OBJECTDIR}/source/Irrlicht/zlib/adler32.o: source/Irrlicht/zlib/adler32.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/adler32.o source/Irrlicht/zlib/adler32.c

${OBJECTDIR}/source/Irrlicht/CD3D8Texture.o: source/Irrlicht/CD3D8Texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D8Texture.o source/Irrlicht/CD3D8Texture.cpp

${OBJECTDIR}/source/Irrlicht/CWaterSurfaceSceneNode.o: source/Irrlicht/CWaterSurfaceSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CWaterSurfaceSceneNode.o source/Irrlicht/CWaterSurfaceSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CSceneManager.o: source/Irrlicht/CSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneManager.o source/Irrlicht/CSceneManager.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureDetailMap2.o: source/Irrlicht/CTRTextureDetailMap2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureDetailMap2.o source/Irrlicht/CTRTextureDetailMap2.cpp

${OBJECTDIR}/source/Irrlicht/CImageLoaderBMP.o: source/Irrlicht/CImageLoaderBMP.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageLoaderBMP.o source/Irrlicht/CImageLoaderBMP.cpp

${OBJECTDIR}/source/Irrlicht/CGUIMeshViewer.o: source/Irrlicht/CGUIMeshViewer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIMeshViewer.o source/Irrlicht/CGUIMeshViewer.cpp

${OBJECTDIR}/source/Irrlicht/CImageWriterTGA.o: source/Irrlicht/CImageWriterTGA.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageWriterTGA.o source/Irrlicht/CImageWriterTGA.cpp

${OBJECTDIR}/source/Irrlicht/CD3D8Driver.o: source/Irrlicht/CD3D8Driver.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D8Driver.o source/Irrlicht/CD3D8Driver.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctflt.o: source/Irrlicht/jpeglib/jfdctflt.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jfdctflt.o source/Irrlicht/jpeglib/jfdctflt.c

${OBJECTDIR}/source/Irrlicht/CIrrDeviceLinux.o: source/Irrlicht/CIrrDeviceLinux.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CIrrDeviceLinux.o source/Irrlicht/CIrrDeviceLinux.cpp

${OBJECTDIR}/source/Irrlicht/CQ3LevelMesh.o: source/Irrlicht/CQ3LevelMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CQ3LevelMesh.o source/Irrlicht/CQ3LevelMesh.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngmem.o: source/Irrlicht/libpng/pngmem.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngmem.o source/Irrlicht/libpng/pngmem.c

${OBJECTDIR}/source/Irrlicht/CImageLoaderJPG.o: source/Irrlicht/CImageLoaderJPG.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageLoaderJPG.o source/Irrlicht/CImageLoaderJPG.cpp

${OBJECTDIR}/source/Irrlicht/CSoftwareDriver2.o: source/Irrlicht/CSoftwareDriver2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSoftwareDriver2.o source/Irrlicht/CSoftwareDriver2.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jccolor.o: source/Irrlicht/jpeglib/jccolor.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jccolor.o source/Irrlicht/jpeglib/jccolor.c

${OBJECTDIR}/source/Irrlicht/CVolumeLightSceneNode.o: source/Irrlicht/CVolumeLightSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CVolumeLightSceneNode.o source/Irrlicht/CVolumeLightSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/COctTreeTriangleSelector.o: source/Irrlicht/COctTreeTriangleSelector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COctTreeTriangleSelector.o source/Irrlicht/COctTreeTriangleSelector.cpp

${OBJECTDIR}/source/Irrlicht/CMS3DMeshFileLoader.o: source/Irrlicht/CMS3DMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMS3DMeshFileLoader.o source/Irrlicht/CMS3DMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CSkinnedMesh.o: source/Irrlicht/CSkinnedMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSkinnedMesh.o source/Irrlicht/CSkinnedMesh.cpp

${OBJECTDIR}/source/Irrlicht/CDefaultGUIElementFactory.o: source/Irrlicht/CDefaultGUIElementFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CDefaultGUIElementFactory.o source/Irrlicht/CDefaultGUIElementFactory.cpp

${OBJECTDIR}/source/Irrlicht/CMeshManipulator.o: source/Irrlicht/CMeshManipulator.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMeshManipulator.o source/Irrlicht/CMeshManipulator.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_Add.o: source/Irrlicht/CTRTextureLightMap2_Add.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_Add.o source/Irrlicht/CTRTextureLightMap2_Add.cpp

${OBJECTDIR}/source/Irrlicht/CIrrDeviceStub.o: source/Irrlicht/CIrrDeviceStub.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CIrrDeviceStub.o source/Irrlicht/CIrrDeviceStub.cpp

${OBJECTDIR}/source/Irrlicht/CPakReader.o: source/Irrlicht/CPakReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CPakReader.o source/Irrlicht/CPakReader.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudWire.o: source/Irrlicht/CTRTextureGouraudWire.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudWire.o source/Irrlicht/CTRTextureGouraudWire.cpp

${OBJECTDIR}/source/Irrlicht/CAnimatedMeshMD3.o: source/Irrlicht/CAnimatedMeshMD3.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CAnimatedMeshMD3.o source/Irrlicht/CAnimatedMeshMD3.cpp

${OBJECTDIR}/source/Irrlicht/CCubeSceneNode.o: source/Irrlicht/CCubeSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CCubeSceneNode.o source/Irrlicht/CCubeSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CDepthBuffer.o: source/Irrlicht/CDepthBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CDepthBuffer.o source/Irrlicht/CDepthBuffer.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M4.o: source/Irrlicht/CTRTextureLightMap2_M4.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureLightMap2_M4.o source/Irrlicht/CTRTextureLightMap2_M4.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jmemmgr.o: source/Irrlicht/jpeglib/jmemmgr.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jmemmgr.o source/Irrlicht/jpeglib/jmemmgr.c

${OBJECTDIR}/source/Irrlicht/CQuake3ShaderSceneNode.o: source/Irrlicht/CQuake3ShaderSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CQuake3ShaderSceneNode.o source/Irrlicht/CQuake3ShaderSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngwtran.o: source/Irrlicht/libpng/pngwtran.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngwtran.o source/Irrlicht/libpng/pngwtran.c

${OBJECTDIR}/source/Irrlicht/CParticleFadeOutAffector.o: source/Irrlicht/CParticleFadeOutAffector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleFadeOutAffector.o source/Irrlicht/CParticleFadeOutAffector.cpp

${OBJECTDIR}/source/Irrlicht/CD3D9ShaderMaterialRenderer.o: source/Irrlicht/CD3D9ShaderMaterialRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D9ShaderMaterialRenderer.o source/Irrlicht/CD3D9ShaderMaterialRenderer.cpp

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFlyCircle.o: source/Irrlicht/CSceneNodeAnimatorFlyCircle.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorFlyCircle.o source/Irrlicht/CSceneNodeAnimatorFlyCircle.cpp

${OBJECTDIR}/source/Irrlicht/CGUIScrollBar.o: source/Irrlicht/CGUIScrollBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIScrollBar.o source/Irrlicht/CGUIScrollBar.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdcolor.o: source/Irrlicht/jpeglib/jdcolor.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdcolor.o source/Irrlicht/jpeglib/jdcolor.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jddctmgr.o: source/Irrlicht/jpeglib/jddctmgr.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jddctmgr.o source/Irrlicht/jpeglib/jddctmgr.c

${OBJECTDIR}/source/Irrlicht/libpng/pngwutil.o: source/Irrlicht/libpng/pngwutil.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngwutil.o source/Irrlicht/libpng/pngwutil.c

${OBJECTDIR}/source/Irrlicht/CD3D9HLSLMaterialRenderer.o: source/Irrlicht/CD3D9HLSLMaterialRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D9HLSLMaterialRenderer.o source/Irrlicht/CD3D9HLSLMaterialRenderer.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jccoefct.o: source/Irrlicht/jpeglib/jccoefct.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jccoefct.o source/Irrlicht/jpeglib/jccoefct.c

${OBJECTDIR}/source/Irrlicht/CImage.o: source/Irrlicht/CImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImage.o source/Irrlicht/CImage.cpp

${OBJECTDIR}/source/Irrlicht/CSTLMeshFileLoader.o: source/Irrlicht/CSTLMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSTLMeshFileLoader.o source/Irrlicht/CSTLMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAdd.o: source/Irrlicht/CTRTextureGouraudAdd.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAdd.o source/Irrlicht/CTRTextureGouraudAdd.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdmaster.o: source/Irrlicht/jpeglib/jdmaster.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdmaster.o source/Irrlicht/jpeglib/jdmaster.c

${OBJECTDIR}/source/Irrlicht/CGeometryCreator.o: source/Irrlicht/CGeometryCreator.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGeometryCreator.o source/Irrlicht/CGeometryCreator.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdphuff.o: source/Irrlicht/jpeglib/jdphuff.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdphuff.o source/Irrlicht/jpeglib/jdphuff.c

${OBJECTDIR}/source/Irrlicht/CGUIEditBox.o: source/Irrlicht/CGUIEditBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIEditBox.o source/Irrlicht/CGUIEditBox.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAlphaNoZ.o: source/Irrlicht/CTRTextureGouraudAlphaNoZ.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAlphaNoZ.o source/Irrlicht/CTRTextureGouraudAlphaNoZ.cpp

${OBJECTDIR}/source/Irrlicht/zlib/inffast.o: source/Irrlicht/zlib/inffast.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/inffast.o source/Irrlicht/zlib/inffast.c

${OBJECTDIR}/source/Irrlicht/COSOperator.o: source/Irrlicht/COSOperator.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COSOperator.o source/Irrlicht/COSOperator.cpp

${OBJECTDIR}/source/Irrlicht/CMetaTriangleSelector.o: source/Irrlicht/CMetaTriangleSelector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMetaTriangleSelector.o source/Irrlicht/CMetaTriangleSelector.cpp

${OBJECTDIR}/source/Irrlicht/CMD3MeshFileLoader.o: source/Irrlicht/CMD3MeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMD3MeshFileLoader.o source/Irrlicht/CMD3MeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureFlat.o: source/Irrlicht/CTRTextureFlat.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureFlat.o source/Irrlicht/CTRTextureFlat.cpp

${OBJECTDIR}/source/Irrlicht/CDefaultSceneNodeFactory.o: source/Irrlicht/CDefaultSceneNodeFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CDefaultSceneNodeFactory.o source/Irrlicht/CDefaultSceneNodeFactory.cpp

${OBJECTDIR}/source/Irrlicht/CReadFile.o: source/Irrlicht/CReadFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CReadFile.o source/Irrlicht/CReadFile.cpp

${OBJECTDIR}/source/Irrlicht/CTriangleSelector.o: source/Irrlicht/CTriangleSelector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTriangleSelector.o source/Irrlicht/CTriangleSelector.cpp

${OBJECTDIR}/source/Irrlicht/CImageWriterPNG.o: source/Irrlicht/CImageWriterPNG.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageWriterPNG.o source/Irrlicht/CImageWriterPNG.cpp

${OBJECTDIR}/source/Irrlicht/CD3D8ParallaxMapRenderer.o: source/Irrlicht/CD3D8ParallaxMapRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D8ParallaxMapRenderer.o source/Irrlicht/CD3D8ParallaxMapRenderer.cpp

${OBJECTDIR}/source/Irrlicht/CAttributes.o: source/Irrlicht/CAttributes.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CAttributes.o source/Irrlicht/CAttributes.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdmarker.o: source/Irrlicht/jpeglib/jdmarker.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdmarker.o source/Irrlicht/jpeglib/jdmarker.c

${OBJECTDIR}/source/Irrlicht/CGUIModalScreen.o: source/Irrlicht/CGUIModalScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIModalScreen.o source/Irrlicht/CGUIModalScreen.cpp

${OBJECTDIR}/source/Irrlicht/CParticleRotationAffector.o: source/Irrlicht/CParticleRotationAffector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleRotationAffector.o source/Irrlicht/CParticleRotationAffector.cpp

${OBJECTDIR}/source/Irrlicht/CTextSceneNode.o: source/Irrlicht/CTextSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTextSceneNode.o source/Irrlicht/CTextSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/zlib/crc32.o: source/Irrlicht/zlib/crc32.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/crc32.o source/Irrlicht/zlib/crc32.c

${OBJECTDIR}/source/Irrlicht/CTRTextureBlend.o: source/Irrlicht/CTRTextureBlend.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureBlend.o source/Irrlicht/CTRTextureBlend.cpp

${OBJECTDIR}/source/Irrlicht/CBurningShader_Raster_Reference.o: source/Irrlicht/CBurningShader_Raster_Reference.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CBurningShader_Raster_Reference.o source/Irrlicht/CBurningShader_Raster_Reference.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngwio.o: source/Irrlicht/libpng/pngwio.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngwio.o source/Irrlicht/libpng/pngwio.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jdapistd.o: source/Irrlicht/jpeglib/jdapistd.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdapistd.o source/Irrlicht/jpeglib/jdapistd.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jdatasrc.o: source/Irrlicht/jpeglib/jdatasrc.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdatasrc.o source/Irrlicht/jpeglib/jdatasrc.c

${OBJECTDIR}/source/Irrlicht/CGUITabControl.o: source/Irrlicht/CGUITabControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUITabControl.o source/Irrlicht/CGUITabControl.cpp

${OBJECTDIR}/source/Irrlicht/CEmptySceneNode.o: source/Irrlicht/CEmptySceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CEmptySceneNode.o source/Irrlicht/CEmptySceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CParticleSphereEmitter.o: source/Irrlicht/CParticleSphereEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleSphereEmitter.o source/Irrlicht/CParticleSphereEmitter.cpp

${OBJECTDIR}/source/Irrlicht/CColladaMeshWriter.o: source/Irrlicht/CColladaMeshWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CColladaMeshWriter.o source/Irrlicht/CColladaMeshWriter.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdcoefct.o: source/Irrlicht/jpeglib/jdcoefct.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdcoefct.o source/Irrlicht/jpeglib/jdcoefct.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jcdctmgr.o: source/Irrlicht/jpeglib/jcdctmgr.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcdctmgr.o source/Irrlicht/jpeglib/jcdctmgr.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jcparam.o: source/Irrlicht/jpeglib/jcparam.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcparam.o source/Irrlicht/jpeglib/jcparam.c

${OBJECTDIR}/source/Irrlicht/COpenGLParallaxMapRenderer.o: source/Irrlicht/COpenGLParallaxMapRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COpenGLParallaxMapRenderer.o source/Irrlicht/COpenGLParallaxMapRenderer.cpp

${OBJECTDIR}/source/Irrlicht/CParticleSystemSceneNode.o: source/Irrlicht/CParticleSystemSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleSystemSceneNode.o source/Irrlicht/CParticleSystemSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdatadst.o: source/Irrlicht/jpeglib/jdatadst.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdatadst.o source/Irrlicht/jpeglib/jdatadst.c

${OBJECTDIR}/source/Irrlicht/CMeshCache.o: source/Irrlicht/CMeshCache.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMeshCache.o source/Irrlicht/CMeshCache.cpp

${OBJECTDIR}/source/Irrlicht/CLimitReadFile.o: source/Irrlicht/CLimitReadFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CLimitReadFile.o source/Irrlicht/CLimitReadFile.cpp

${OBJECTDIR}/source/Irrlicht/CD3D9Driver.o: source/Irrlicht/CD3D9Driver.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D9Driver.o source/Irrlicht/CD3D9Driver.cpp

${OBJECTDIR}/source/Irrlicht/CSoftwareTexture2.o: source/Irrlicht/CSoftwareTexture2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSoftwareTexture2.o source/Irrlicht/CSoftwareTexture2.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jcapimin.o: source/Irrlicht/jpeglib/jcapimin.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcapimin.o source/Irrlicht/jpeglib/jcapimin.c

${OBJECTDIR}/source/Irrlicht/CGUIButton.o: source/Irrlicht/CGUIButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIButton.o source/Irrlicht/CGUIButton.cpp

${OBJECTDIR}/source/Irrlicht/zlib/inftrees.o: source/Irrlicht/zlib/inftrees.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/inftrees.o source/Irrlicht/zlib/inftrees.c

${OBJECTDIR}/source/Irrlicht/CImageWriterBMP.o: source/Irrlicht/CImageWriterBMP.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageWriterBMP.o source/Irrlicht/CImageWriterBMP.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngtrans.o: source/Irrlicht/libpng/pngtrans.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngtrans.o source/Irrlicht/libpng/pngtrans.c

${OBJECTDIR}/source/Irrlicht/CSoftwareDriver.o: source/Irrlicht/CSoftwareDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSoftwareDriver.o source/Irrlicht/CSoftwareDriver.cpp

${OBJECTDIR}/source/Irrlicht/CGUIInOutFader.o: source/Irrlicht/CGUIInOutFader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIInOutFader.o source/Irrlicht/CGUIInOutFader.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngerror.o: source/Irrlicht/libpng/pngerror.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngerror.o source/Irrlicht/libpng/pngerror.c

${OBJECTDIR}/source/Irrlicht/CD3D9Texture.o: source/Irrlicht/CD3D9Texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CD3D9Texture.o source/Irrlicht/CD3D9Texture.cpp

${OBJECTDIR}/source/Irrlicht/CParticleMeshEmitter.o: source/Irrlicht/CParticleMeshEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CParticleMeshEmitter.o source/Irrlicht/CParticleMeshEmitter.cpp

${OBJECTDIR}/source/Irrlicht/CIrrMeshFileLoader.o: source/Irrlicht/CIrrMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CIrrMeshFileLoader.o source/Irrlicht/CIrrMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jcsample.o: source/Irrlicht/jpeglib/jcsample.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcsample.o source/Irrlicht/jpeglib/jcsample.c

${OBJECTDIR}/source/Irrlicht/CMD2MeshFileLoader.o: source/Irrlicht/CMD2MeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CMD2MeshFileLoader.o source/Irrlicht/CMD2MeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/zlib/trees.o: source/Irrlicht/zlib/trees.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/trees.o source/Irrlicht/zlib/trees.c

${OBJECTDIR}/source/Irrlicht/jpeglib/jcprepct.o: source/Irrlicht/jpeglib/jcprepct.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jcprepct.o source/Irrlicht/jpeglib/jcprepct.c

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAddNoZ2.o: source/Irrlicht/CTRTextureGouraudAddNoZ2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudAddNoZ2.o source/Irrlicht/CTRTextureGouraudAddNoZ2.cpp

${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCollisionResponse.o: source/Irrlicht/CSceneNodeAnimatorCollisionResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSceneNodeAnimatorCollisionResponse.o source/Irrlicht/CSceneNodeAnimatorCollisionResponse.cpp

${OBJECTDIR}/source/Irrlicht/jpeglib/jdhuff.o: source/Irrlicht/jpeglib/jdhuff.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/jpeglib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/jpeglib/jdhuff.o source/Irrlicht/jpeglib/jdhuff.c

${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudVertexAlpha2.o: source/Irrlicht/CTRTextureGouraudVertexAlpha2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureGouraudVertexAlpha2.o source/Irrlicht/CTRTextureGouraudVertexAlpha2.cpp

${OBJECTDIR}/source/Irrlicht/CBillboardSceneNode.o: source/Irrlicht/CBillboardSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CBillboardSceneNode.o source/Irrlicht/CBillboardSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/COpenGLTexture.o: source/Irrlicht/COpenGLTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COpenGLTexture.o source/Irrlicht/COpenGLTexture.cpp

${OBJECTDIR}/source/Irrlicht/CVideoModeList.o: source/Irrlicht/CVideoModeList.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CVideoModeList.o source/Irrlicht/CVideoModeList.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngget.o: source/Irrlicht/libpng/pngget.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngget.o source/Irrlicht/libpng/pngget.c

${OBJECTDIR}/source/Irrlicht/CTRGouraud.o: source/Irrlicht/CTRGouraud.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRGouraud.o source/Irrlicht/CTRGouraud.cpp

${OBJECTDIR}/source/Irrlicht/CImageWriterPPM.o: source/Irrlicht/CImageWriterPPM.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageWriterPPM.o source/Irrlicht/CImageWriterPPM.cpp

${OBJECTDIR}/source/Irrlicht/CGUIImage.o: source/Irrlicht/CGUIImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIImage.o source/Irrlicht/CGUIImage.cpp

${OBJECTDIR}/source/Irrlicht/zlib/uncompr.o: source/Irrlicht/zlib/uncompr.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/uncompr.o source/Irrlicht/zlib/uncompr.c

${OBJECTDIR}/source/Irrlicht/CShadowVolumeSceneNode.o: source/Irrlicht/CShadowVolumeSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CShadowVolumeSceneNode.o source/Irrlicht/CShadowVolumeSceneNode.cpp

${OBJECTDIR}/source/Irrlicht/CImageWriterPSD.o: source/Irrlicht/CImageWriterPSD.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageWriterPSD.o source/Irrlicht/CImageWriterPSD.cpp

${OBJECTDIR}/source/Irrlicht/CTRTextureFlatWire.o: source/Irrlicht/CTRTextureFlatWire.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRTextureFlatWire.o source/Irrlicht/CTRTextureFlatWire.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngpread.o: source/Irrlicht/libpng/pngpread.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngpread.o source/Irrlicht/libpng/pngpread.c

${OBJECTDIR}/source/Irrlicht/CTRGouraudAlpha2.o: source/Irrlicht/CTRGouraudAlpha2.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CTRGouraudAlpha2.o source/Irrlicht/CTRGouraudAlpha2.cpp

${OBJECTDIR}/source/Irrlicht/C3DSMeshFileLoader.o: source/Irrlicht/C3DSMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/C3DSMeshFileLoader.o source/Irrlicht/C3DSMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CGUISpinBox.o: source/Irrlicht/CGUISpinBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUISpinBox.o source/Irrlicht/CGUISpinBox.cpp

${OBJECTDIR}/source/Irrlicht/CXMeshFileLoader.o: source/Irrlicht/CXMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CXMeshFileLoader.o source/Irrlicht/CXMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/CBSPMeshFileLoader.o: source/Irrlicht/CBSPMeshFileLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CBSPMeshFileLoader.o source/Irrlicht/CBSPMeshFileLoader.cpp

${OBJECTDIR}/source/Irrlicht/zlib/inflate.o: source/Irrlicht/zlib/inflate.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/zlib
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/zlib/inflate.o source/Irrlicht/zlib/inflate.c

${OBJECTDIR}/source/Irrlicht/COpenGLDriver.o: source/Irrlicht/COpenGLDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/COpenGLDriver.o source/Irrlicht/COpenGLDriver.cpp

${OBJECTDIR}/source/Irrlicht/CImageLoaderPCX.o: source/Irrlicht/CImageLoaderPCX.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageLoaderPCX.o source/Irrlicht/CImageLoaderPCX.cpp

${OBJECTDIR}/source/Irrlicht/CSoftwareTexture.o: source/Irrlicht/CSoftwareTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CSoftwareTexture.o source/Irrlicht/CSoftwareTexture.cpp

${OBJECTDIR}/source/Irrlicht/libpng/pngrio.o: source/Irrlicht/libpng/pngrio.c 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht/libpng
	$(COMPILE.c) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -DIRR_DX9_PLEASE -Iinclude -Isource/Irrlicht/zlib -IC\:/Program\ Files/Microsoft\ DirectX\ SDK/include -o ${OBJECTDIR}/source/Irrlicht/libpng/pngrio.o source/Irrlicht/libpng/pngrio.c

${OBJECTDIR}/source/Irrlicht/CImageWriterPCX.o: source/Irrlicht/CImageWriterPCX.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CImageWriterPCX.o source/Irrlicht/CImageWriterPCX.cpp

${OBJECTDIR}/source/Irrlicht/CWriteFile.o: source/Irrlicht/CWriteFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CWriteFile.o source/Irrlicht/CWriteFile.cpp

${OBJECTDIR}/source/Irrlicht/CGUIWindow.o: source/Irrlicht/CGUIWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/Irrlicht
	$(COMPILE.cc) -g -DIRRLICHT_EXPORTS -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -D_IRR_COMPILE_WITH_DIRECT3D_9_ -Iinclude -Isource/Irrlicht/zlib -I${D3D9_SDK}/include -o ${OBJECTDIR}/source/Irrlicht/CGUIWindow.o source/Irrlicht/CGUIWindow.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Shared-Debug
	${RM} lib/Win32-gcc/Irrlicht_d.dll

# Subprojects
.clean-subprojects:
