# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Linux-Static-Release.mk lib/Linux/libIrrlicht.a

lib/Linux/libIrrlicht.a: ${OBJECTFILES}
	${MKDIR} -p lib/Linux
	${RM} lib/Linux/libIrrlicht.a
	${AR} rv lib/Linux/libIrrlicht.a ${OBJECTFILES} 
	$(RANLIB) lib/Linux/libIrrlicht.a

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Linux-Static-Release
	${RM} lib/Linux/libIrrlicht.a

# Subprojects
.clean-subprojects:
