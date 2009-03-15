# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Static-Debug.mk lib/Win32-gcc/Irrlicht_static_d.a

lib/Win32-gcc/Irrlicht_static_d.a: ${OBJECTFILES}
	${MKDIR} -p lib/Win32-gcc
	${RM} lib/Win32-gcc/Irrlicht_static_d.a
	${AR} rv lib/Win32-gcc/Irrlicht_static_d.a ${OBJECTFILES} 
	$(RANLIB) lib/Win32-gcc/Irrlicht_static_d.a

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Static-Debug
	${RM} lib/Win32-gcc/Irrlicht_static_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
