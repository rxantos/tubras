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

# Macros
PLATFORM=MinGW-Windows

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Win32-Shared-Debug/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CTextOverlay.o \
	${OBJECTDIR}/COverlay.o \
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
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Shared-Debug.mk ../../bin/nbtest.exe

../../bin/nbtest.exe: ../../deps/irrlicht/lib/Win32-gcc/Irrlicht_d.dll

../../bin/nbtest.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin
	${LINK.cc} -o ../../bin/nbtest ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/CTextOverlay.o: CTextOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -I../../deps/irrlicht/include -o ${OBJECTDIR}/CTextOverlay.o CTextOverlay.cpp

${OBJECTDIR}/COverlay.o: COverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -I../../deps/irrlicht/include -o ${OBJECTDIR}/COverlay.o COverlay.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -DWIN32 -D_WINDOWS -D_DEBUG -D__GNUWIN32__ -I../../deps/irrlicht/include -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Shared-Debug
	${RM} ../../bin/nbtest.exe

# Subprojects
.clean-subprojects:
