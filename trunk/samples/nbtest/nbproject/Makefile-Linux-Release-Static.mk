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
CC=gcc
CCC=g++
CXX=g++
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Linux-Release-Static/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/COverlay.o \
	${OBJECTDIR}/CTextOverlay.o \
	${OBJECTDIR}/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-O3 -ffast-math
CXXFLAGS=-O3 -ffast-math

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../deps/irrlicht/lib/Linux/libIrrlicht.a -lGL -lXxf86vm -lXext -lX11

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} ../../bin/nbtest

../../bin/nbtest: ${OBJECTFILES}
	${MKDIR} -p ../../bin
	${LINK.cc} -o ../../bin/nbtest -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/COverlay.o: COverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -s -D_IRR_STATIC_LIB_ -DNDEBUG -I../../deps/irrlicht/include -o ${OBJECTDIR}/COverlay.o COverlay.cpp

${OBJECTDIR}/CTextOverlay.o: CTextOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -s -D_IRR_STATIC_LIB_ -DNDEBUG -I../../deps/irrlicht/include -o ${OBJECTDIR}/CTextOverlay.o CTextOverlay.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -s -D_IRR_STATIC_LIB_ -DNDEBUG -I../../deps/irrlicht/include -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Linux-Release-Static
	${RM} ../../bin/nbtest

# Subprojects
.clean-subprojects:
