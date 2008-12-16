# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Linux-Static-Debug.mk lib/Linux/libIrrlicht_d.a

lib/Linux/libIrrlicht_d.a: ${OBJECTFILES}
	${MKDIR} -p lib/Linux
	${RM} lib/Linux/libIrrlicht_d.a
	${AR} rv lib/Linux/libIrrlicht_d.a ${OBJECTFILES} 
	$(RANLIB) lib/Linux/libIrrlicht_d.a

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Linux-Static-Debug
	${RM} lib/Linux/libIrrlicht_d.a

# Subprojects
.clean-subprojects:
