# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Release.mk libs/release/libTubras.a

libs/release/libTubras.a: ${OBJECTFILES}
	${MKDIR} -p libs/release
	${RM} libs/release/libTubras.a
	${AR} rv libs/release/libTubras.a ${OBJECTFILES} 
	$(RANLIB) libs/release/libTubras.a

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Release
	${RM} libs/release/libTubras.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
