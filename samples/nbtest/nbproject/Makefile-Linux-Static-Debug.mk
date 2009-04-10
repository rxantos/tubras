.build-conf:
	@echo Tool collection not found.
	@echo Please specify existing tool collection in project properties
	@exit 1

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Linux-Static-Debug
	${RM} ../../bin/nbtest

# Subprojects
.clean-subprojects:
	cd ../../deps/irrlicht && ${MAKE}  -f Makefile CONF=Linux-Static-Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
