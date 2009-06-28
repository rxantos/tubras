.build-conf:
	@echo Tool collection not found.
	@echo Please specify existing tool collection in project properties
	@exit 1

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Static-Debug
	${RM} lib/Win32-gcc/Irrlicht_static_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
