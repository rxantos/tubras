# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Debug.mk libs/debug/libTubras_d.a

libs/debug/libTubras_d.a: ${OBJECTFILES}
	${MKDIR} -p libs/debug
	${RM} libs/debug/libTubras_d.a
	${AR} rv libs/debug/libTubras_d.a ${OBJECTFILES} 
	$(RANLIB) libs/debug/libTubras_d.a

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
