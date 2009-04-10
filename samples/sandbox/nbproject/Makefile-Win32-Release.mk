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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Win32-Release
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
LDLIBSOPTIONS=../../libs/release/libTubras.a ../../deps/irrlicht/lib/Win32-gcc/Irrlicht_static.a ../../deps/irrklang/lib/Win32-gcc/libirrKlang.a -lgdi32 -lopengl32 -lwinmm

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Release.mk /c/gdev/tubras/bin/sandbox.exe

/c/gdev/tubras/bin/sandbox.exe: ../../libs/release/libTubras.a

/c/gdev/tubras/bin/sandbox.exe: ../../deps/irrlicht/lib/Win32-gcc/Irrlicht_static.a

/c/gdev/tubras/bin/sandbox.exe: ../../deps/irrklang/lib/Win32-gcc/libirrKlang.a

/c/gdev/tubras/bin/sandbox.exe: ${OBJECTFILES}
	${MKDIR} -p /c/gdev/tubras/bin
	${LINK.cc} -o /c/gdev/tubras/bin/sandbox -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/sandbox.o: sandbox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -DWIN32 -DNDEBUG -D__GNUWIN32__ -D_IRR_STATIC_LIB_ -DSTATIC_LINKED -I../../include -I../../src/lua -I../../deps/bullet/src -I../../deps/irrlicht/include -I../../deps/irrlicht/source/Irrlicht -I../../deps/irrklang/include -I../../deps/particle2/Particle2/ParticleLib -I../../deps/particle2/Particle2/Particle -MMD -MP -MF $@.d -o ${OBJECTDIR}/sandbox.o sandbox.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Release
	${RM} /c/gdev/tubras/bin/sandbox.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
