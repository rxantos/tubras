# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Static-Release.mk lib/Win32-gcc/Irrlicht_static.a

lib/Win32-gcc/Irrlicht_static.a: ${OBJECTFILES}
	${MKDIR} -p lib/Win32-gcc
	${RM} lib/Win32-gcc/Irrlicht_static.a
	${AR} rv lib/Win32-gcc/Irrlicht_static.a ${OBJECTFILES} 
	$(RANLIB) lib/Win32-gcc/Irrlicht_static.a

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Static-Release
	${RM} lib/Win32-gcc/Irrlicht_static.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
