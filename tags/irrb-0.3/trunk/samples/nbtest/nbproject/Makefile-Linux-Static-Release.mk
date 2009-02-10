# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Linux-Static-Release.mk ../../bin/nbtest

../../bin/nbtest: ../../deps/irrlicht/lib/Linux/libIrrlicht.a

../../bin/nbtest: ${OBJECTFILES}
	${MKDIR} -p ../../bin
	${LINK.cc} -o ../../bin/nbtest -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

# Subprojects
.build-subprojects:
	cd ../../deps/irrlicht && ${MAKE}  -f Makefile CONF=Linux-Static-Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Linux-Static-Release
	${RM} ../../bin/nbtest

# Subprojects
.clean-subprojects:
	cd ../../deps/irrlicht && ${MAKE}  -f Makefile CONF=Linux-Static-Release clean
