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
OBJECTDIR=build/Win32-Debug/${PLATFORM}

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

# Link Libraries and Options
LDLIBSOPTIONS=../../libs/debug/libTubras.a ../../deps/irrlicht/lib/Win32-gcc/Irrlicht_static_d.a -lgdi32 -lopengl32 -lwinmm ../../deps/irrklang/lib/Win32-gcc/libirrKlang.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Win32-Debug.mk /c/gdev/tubras/bin/sandbox.exe

/c/gdev/tubras/bin/sandbox.exe: ../../libs/debug/libTubras.a

/c/gdev/tubras/bin/sandbox.exe: ../../deps/irrlicht/lib/Win32-gcc/Irrlicht_static_d.a

/c/gdev/tubras/bin/sandbox.exe: ../../deps/irrklang/lib/Win32-gcc/libirrKlang.a

/c/gdev/tubras/bin/sandbox.exe: ${OBJECTFILES}
	${MKDIR} -p /c/gdev/tubras/bin
	${LINK.cc} -o /c/gdev/tubras/bin/sandbox ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/sandbox.o: sandbox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -D__GNUWIN32__ -D_DEBUG -DWIN32 -D_WIN32 -DSTATIC_LINKED -D_IRR_STATIC_LIB_ -I../../include -I../../deps/bullet/src -I../../deps/irrlicht/include -I../../tools/lsl/include -I../../deps/irrlicht/source/Irrlicht -I../../deps/irrklang/include -o ${OBJECTDIR}/sandbox.o sandbox.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Win32-Debug
	${RM} /c/gdev/tubras/bin/sandbox.exe

# Subprojects
.clean-subprojects:
