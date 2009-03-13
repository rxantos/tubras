# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Linux-Debug.mk libs/debug/libTubras.a

libs/debug/libTubras.a: ${OBJECTFILES}
	${MKDIR} -p libs/debug
	${RM} libs/debug/libTubras.a
	${AR} rv libs/debug/libTubras.a ${OBJECTFILES} 
	$(RANLIB) libs/debug/libTubras.a

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Linux-Debug
	${RM} libs/debug/libTubras.a

# Subprojects
.clean-subprojects:
