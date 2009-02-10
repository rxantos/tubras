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
OBJECTDIR=build/Win32-Shared-Release/${PLATFORM}

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
LDLIBSOPTIONS=-lgdi32 -lopengl32 ../../deps/irrlicht/lib/Win32-gcc/Irrlicht.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Shared-Release.mk ../../bin/nbtest.exe

../../bin/nbtest.exe: ../../deps/irrlicht/lib/Win32-gcc/Irrlicht.dll

../../bin/nbtest.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin
	${LINK.cc} -o ../../bin/nbtest -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/CTextOverlay.o: CTextOverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -s -DWIN32 -D_WINDOWS -D__GNUWIN32__ -DNDEBUG -I../../deps/irrlicht/include -o ${OBJECTDIR}/CTextOverlay.o CTextOverlay.cpp

${OBJECTDIR}/COverlay.o: COverlay.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -s -DWIN32 -D_WINDOWS -D__GNUWIN32__ -DNDEBUG -I../../deps/irrlicht/include -o ${OBJECTDIR}/COverlay.o COverlay.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -s -DWIN32 -D_WINDOWS -D__GNUWIN32__ -DNDEBUG -I../../deps/irrlicht/include -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Shared-Release
	${RM} ../../bin/nbtest.exe

# Subprojects
.clean-subprojects:
