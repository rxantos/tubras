#
# Generated Makefile - do not edit!
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
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Linux-Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/sandbox.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../libs/debug -lGL -lXext -lXxf86vm -lX11 -lpthread -lIrrKlang ../../libs/debug/libTubras.a ../../deps/irrlicht/lib/Linux/libIrrlicht_d.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Linux-Debug.mk ../../bin/sandbox

../../bin/sandbox: ../../libs/debug/libTubras.a

../../bin/sandbox: ../../deps/irrlicht/lib/Linux/libIrrlicht_d.a

../../bin/sandbox: ${OBJECTFILES}
	${MKDIR} -p ../../bin
	${LINK.cc} -o ../../bin/sandbox ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/sandbox.o: nbproject/Makefile-${CND_CONF}.mk sandbox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB -D_DEBUG -I../../include -I../../tools/irrlicht/extensions -I../../src/lua -I../../deps/bullet/src -I../../deps/irrlicht/include -I../../source/irrlicht -I../../deps/irrklang/include -I../../deps/irrlicht/source/Irrlicht -I../../deps/particle2/Particle2/Particle -I../../deps/particle2/Particle2/ParticleLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/sandbox.o sandbox.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Linux-Debug
	${RM} ../../bin/sandbox

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
