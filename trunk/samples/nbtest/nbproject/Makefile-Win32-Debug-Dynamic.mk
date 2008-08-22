#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Win32-Debug-Dynamic/MinGW-Windows

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/COverlay.o \
	${OBJECTDIR}/CTextOverlay.o \
	${OBJECTDIR}/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lgdi32 -lopengl32 ../../deps/irrlicht/lib/Win32-gcc/Irrlicht_d.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Win32-Debug-Dynamic/MinGW-Windows/nbtest.exe

dist/Win32-Debug-Dynamic/MinGW-Windows/nbtest.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Win32-Debug-Dynamic/MinGW-Windows
	${LINK.cc} -o dist/Win32-Debug-Dynamic/MinGW-Windows/nbtest ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/COverlay.o: COverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I../../deps/irrlicht/include -o ${OBJECTDIR}/COverlay.o COverlay.cpp

${OBJECTDIR}/CTextOverlay.o: CTextOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I../../deps/irrlicht/include -o ${OBJECTDIR}/CTextOverlay.o CTextOverlay.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I../../deps/irrlicht/include -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Debug-Dynamic
	${RM} dist/Win32-Debug-Dynamic/MinGW-Windows/nbtest.exe

# Subprojects
.clean-subprojects:
