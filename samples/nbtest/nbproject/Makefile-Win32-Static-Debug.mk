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
CND_CONF=Win32-Static-Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

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

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../deps/irrlicht/lib/Win32-gcc/Irrlicht_static_d.a -lgdi32 -lopengl32 -lwinmm

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Static-Debug.mk ../../bin/nbtest.exe

../../bin/nbtest.exe: ../../deps/irrlicht/lib/Win32-gcc/Irrlicht_static_d.a

../../bin/nbtest.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin
	${LINK.cc} -o ../../bin/nbtest ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/COverlay.o: COverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -DWIN32 -D_WINDOWS -D__GNUWIN32__ -D_DEBUG -I../../deps/irrlicht/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/COverlay.o COverlay.cpp

${OBJECTDIR}/CTextOverlay.o: CTextOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -DWIN32 -D_WINDOWS -D__GNUWIN32__ -D_DEBUG -I../../deps/irrlicht/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/CTextOverlay.o CTextOverlay.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -DWIN32 -D_WINDOWS -D__GNUWIN32__ -D_DEBUG -I../../deps/irrlicht/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Static-Debug
	${RM} ../../bin/nbtest.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
