# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Linux-Static-Debug.mk ../../bin/nbtest

../../bin/nbtest: ../../deps/irrlicht/lib/Linux/libIrrlicht_d.a

../../bin/nbtest: ${OBJECTFILES}
	${MKDIR} -p ../../bin
	${LINK.cc} -o ../../bin/nbtest ${OBJECTFILES} ${LDLIBSOPTIONS} 

# Subprojects
.build-subprojects:
	cd ../../deps/irrlicht && ${MAKE}  -f Makefile CONF=Linux-Static-Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Linux-Static-Debug
	${RM} ../../bin/nbtest

# Subprojects
.clean-subprojects:
	cd ../../deps/irrlicht && ${MAKE}  -f Makefile CONF=Linux-Static-Debug clean
