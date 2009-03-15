# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Shared-Debug.mk lib/Win32-gcc/Irrlicht_d.dll

lib/Win32-gcc/Irrlicht_d.dll: ${OBJECTFILES}
	${MKDIR} -p lib/Win32-gcc
	g++.exe -o lib/Win32-gcc/Irrlicht_d.dll ${OBJECTFILES} ${LDLIBSOPTIONS} 

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Shared-Debug
	${RM} lib/Win32-gcc/Irrlicht_d.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
