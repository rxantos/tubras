# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Shared-Release.mk lib/Win32-gcc/Irrlicht.dll

lib/Win32-gcc/Irrlicht.dll: ${OBJECTFILES}
	${MKDIR} -p lib/Win32-gcc
	${LINK.cc} -o lib/Win32-gcc/Irrlicht.dll -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Shared-Release
	${RM} lib/Win32-gcc/Irrlicht.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
