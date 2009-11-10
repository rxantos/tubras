#-----------------------------------------------------------------------------
# This source file is part of the Tubras game engine.
#
# Copyright (c) 2006-2008 Tubras Software, Ltd
# Also see acknowledgements in docs/Readme.html
#
# This software is licensed under the zlib/libpng license. See the file
# "docs/license.html" for detailed information.
#-----------------------------------------------------------------------------
import os, sys, subprocess, glob, shutil

gPlatform = Environment()['PLATFORM']
gDepsDir = 'deps/'
gDebug  = True
gDepsOnly = False
gHelpOnly = False
gHavePySVN = False
gCleaning = False
gProfiling = False
gSound = 1
gScript = 1

try:
    import pysvn
    gHavePySVN = True
        
except:
    pass

#
# dependencies, based on Tubras version, will have their own "download" 
# locations/methods and build mechanics.
#
gDepVersionDefault = '0.1'

gDeps = None

#
# 'dependency name' : (info) where info is:
#    ('target url', 'get method', 'rename from')
#
# 'get method'
#       'svn' - get via subversion.
#      'wget' - get via wget.
#
# Note if wget url ends in '.zip', the retrieved file is unzipped and then
# if 'rename from' parameter exists, the directory is renamed from 
# 'rename from' to 'dependency name'.
#
gDepsV01 = {
    'bullet':('http://bullet.googlecode.com/svn/trunk/','svn'),
    'irrlicht':('https://irrlicht.svn.sourceforge.net/svnroot/irrlicht/trunk','svn'),
    'irrklang':('http://www.ambiera.at/downloads/irrKlang-1.1.3c.zip','wget','irrKlang-1.1.3'),
    }    

gTubrasVersionDeps = {
    'head':gDepsV01
    }

gDepsCopy = {
    'irrklang':(('win32', 'deps/irrklang/lib/Win32-visualStudio/irrKlang.lib',
        'libs/debug/irrKlang.lib'),
    ('win32', 'deps/irrklang/lib/Win32-visualStudio/irrKlang.lib',
        'libs/release/irrKlang.lib'),
    ('win32', 'deps/irrklang/bin/Win32-visualStudio/irrKlang.dll',
        'bin/irrKlang.dll'),
    ('win32', 'deps/irrklang/bin/Win32-visualStudio/ikpMP3.dll',
        'bin/ikpMP3.dll'))
}

#--------------------------------------------------------------------
#                      d o w n l o a d D e p
#--------------------------------------------------------------------
def downloadDep(libName, libLocal, libRemote):
    rc = True
    dname = libLocal + '.zip'

    print 'Downloading ' + libName + '...'
    commandline = 'wget -O ' + dname + ' ' + libRemote
    print 'cmd', commandline.split()
    p = subprocess.Popen(commandline.split())
    p.wait()
    rc = p.returncode

    return rc

#--------------------------------------------------------------------
#                    s v n C h e c k O u t D e p
#--------------------------------------------------------------------
def svnCheckOutDep(libName, libLocal, libRemote):
    print 'Subversion Checkout: ' + libName + '...'
    if gHavePySVN:
        client = pysvn.Client()
        client.checkout(libLocal, libRemote)
        return True

    # try command line svn
    commandline = 'svn co ' + libRemote + ' ' + libLocal
    print 'cmd', commandline.split()
    p = subprocess.Popen(commandline.split())
    p.wait()
    rc = p.returncode

    return False

#--------------------------------------------------------------------
#                    c v s C h e c k O u t D e p
#--------------------------------------------------------------------
def cvsCheckOutDep(libName, libLocal, libRemote):
    pass

#--------------------------------------------------------------------
#                        u n z i p D e p
#--------------------------------------------------------------------
def unzipDep(libName, libLocal, renameFrom):
    rc = True
    dname = libLocal + '.zip'
    print 'Unzipping ' + libName + '...'

    commandline = 'unzip -o -qq ' + dname + ' -d ' + gDepsDir
    p = subprocess.Popen(commandline.split())    
    p.wait()
    rc = p.returncode

    try:
        os.unlink(dname)
    except:
        pass

    if renameFrom == None:
        return rc

    try:
        if renameFrom != libName:
            os.rename(gDepsDir + renameFrom, gDepsDir + libName);
    except:
        print 'Rename Error:'
        print 'From: ',gDepsDir,renameFrom
        print 'To: ',gDepsDir,libName
        os._exit(0)

    return rc

#--------------------------------------------------------------------
#                     s e t D e p V e r s i o n
#--------------------------------------------------------------------
def setDepVersion(version):
    global gDeps

    for k,v in gTubrasVersionDeps.items():
        if k == version:
            gDeps = v
            return
    print 'Invalid Dependency Version Specified, Defaulting to "head"'
    gDeps = gTubrasVersionDeps['head']
    return

#--------------------------------------------------------------------
#                         c h e c k D e p s
#--------------------------------------------------------------------
def checkDeps():
    if not os.path.exists(gDepsDir):
        os.mkdir(gDepsDir)
    for libName,info in gDeps.items():
        libLocal = gDepsDir + libName
        libRemote = info[0]

        exists = os.path.exists(libLocal)
        print 'Dependency (%s) Exists=%d' % (libName,exists)
        if not exists:
            if info[1] != 'svn':
                dname = libLocal + '.zip'
                if not os.path.exists(dname):
                    rc = downloadDep(libName, libLocal, libRemote)
                renameFrom = None
                if len(info) == 3:
                    renameFrom = info[2]

                unzipDep(libName,libLocal, renameFrom)
            # subversion checkout
            else:
                svnCheckOutDep(libName, libLocal, libRemote)

    if not os.path.exists("bin"):
        os.mkdir("bin")

    if not os.path.exists("libs"):
        os.mkdir("libs")

    if not os.path.exists('libs/debug'):
        os.mkdir("libs/debug")

    if not os.path.exists('libs/release'):
        os.mkdir("libs/release")

    # Dependency file copies
    for libName, fileInfos in gDepsCopy.items():
        for fileInfo in fileInfos:
            plat = fileInfo[0]
            fname = fileInfo[1]            
            tname = fileInfo[2]
            if plat == gPlatform and not os.path.exists(tname):
                print('Dep Copy (%s) -> %s' % (libName, tname))
                shutil.copy(fname, tname)
        
    return True

#--------------------------------------------------------------------
#                            m a i n
#--------------------------------------------------------------------
Help("""
 Build Arguments/Options:
    release=1           Builds the release verion.

      sound=?           Selects the Sound System to use:
                           1 - irrKlang Sound System (default)
                           2 - FMOD Sound system
                           3 - NULL Sound System (no sound)

    profile=?           Enables/Disables profiling:
                           0 - Disable (default)
                           1 - Enable

     depver=x.x         Specify dependency version to use. Default is 'head'.
                        Use 'depver=?' for a list of available versions.

       deps=1           Retrieve Dependencies only.
      """)

args = sys.argv[1:]
if '-h' in args:
    gHelpOnly = True

if '-c' in args:
    gCleaning = True

if int(ARGUMENTS.get('release',0)):
    gDebug = False

gSound = int(ARGUMENTS.get('sound',1))
if gSound < 1 or gSound > 3:
    gSound = 1

if int(ARGUMENTS.get('profile',0)):
    gProfiling  = True

Export('gDebug')

if int(ARGUMENTS.get('deps',0)):
    gDepsOnly = True

if not gHelpOnly:
    if gDepsOnly:
        print('*')
        print('Checking dependencies...')
        print('*')
    elif gCleaning:
        print('*')
        print('Cleaning project...')
        print('*')
    else:
        print('*')
        print('Building %s Version Of The Tubras Library.' % ('Debug' if gDebug
            else 'Release'))

        smsg = 'Using Sound System: ' 
        if gSound == 1:
            smsg = smsg + 'irrKlang'
        elif gSound == 2:
            smsg = smsg + 'FMOD'
        else:
            smsg = smsg + 'Null Sound'
        print(smsg)

        smsg = 'Profiling: '
        if gProfiling:
            smsg += 'Enabled'
        else:
            smsg += 'Disabled'
        print(smsg)

        print('*')

    if not gCleaning:
        depVersion = ARGUMENTS.get('depver','head')
        setDepVersion(depVersion)

        if not checkDeps():
            sys.exit(0)

        if gDepsOnly:
            sys.exit(0)

#
# setup include paths
#
#
includePath = []
try:
    envTubras = os.environ['TUBRAS_SDK']
except:
    envTubras = os.getcwd()
   
envTubras = envTubras.strip()
if envTubras == '':
    envTubras = os.getcwd()

if envTubras[len(envTubras)-1] != '/':
    envTubras += '/'

iPrefix = ''
if gPlatform == 'posix':
    iPrefix = ''

iLUA = iPrefix + envTubras + 'src/lua'
iTubras = iPrefix + envTubras + 'include'
iBullet = iPrefix + envTubras + gDepsDir + 'bullet/src'
iIrrlicht = iPrefix + envTubras + gDepsDir + 'irrlicht/include'
iIrrlichtDev = iPrefix + envTubras + gDepsDir + 'irrlicht/source/Irrlicht'
iIrrKlang = iPrefix + envTubras + gDepsDir + 'irrklang/include'

includePath.append(iTubras)
includePath.append(iLUA)
includePath.append(iBullet)
includePath.append(iIrrlicht)
includePath.append(iIrrlichtDev)
includePath.append(iIrrKlang)

includePath.append(iPrefix + envTubras + 'tools/irrlicht/extensions')

env = Environment(CPPPATH = includePath, MSVS_VERSION='9.0')

envProgs = Environment(CPPPATH = includePath, MSVS_VERSION='9.0')
envProgsC = Environment(CPPPATH = includePath, MSVS_VERSION='9.0')

#
# setup output library based on build type
#
tLibName = 'libs/release/Tubras'
LibPath = ['libs/release']
if gDebug:
    tLibName = 'libs/debug/Tubras_d'
    LibPath = ['libs/debug']

#
# setup compiler flags based on platform type
#
libCCFlags = ''
libLNFlags = ''
progCCFlags = ''
progLNFlags = ''
progLNCFlags = ''

if gPlatform == 'win32':
    defines = ' /D "WIN32" /D "_LIB" /D "_IRR_STATIC_LIB_" /D "STATIC_LINKED"'
    defines += ' /D "_CRT_SECURE_NO_WARNINGS"'
    if gProfiling:
        defines += ' /D "PROFILING_ENABLED"'
    if gSound == 1:
        defines = defines + ' /D "USE_IRR_SOUND"'
    elif gSound == 2:
        defines = defines + ' /D "USE_FMOD_SOUND"'
    else:
        defines = defines + ' /D "USE_NULL_SOUND"'

    if gDebug:
        libCCFlags = '/Od /Gm /EHsc /RTC1 /MTd /W3 /c /ZI'
        progCCFlags = '/Od /Gm /EHsc /RTC1 /MTd /W3 /c /ZI'
        defines = defines + ' /D "_DEBUG"'
        progLNFlags = '/DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86'
        progLNCFlags = '/DEBUG /SUBSYSTEM:CONSOLE /MACHINE:X86'
        arFlags = ''
    else:
        libCCFlags = '/O2 /GL /FD /EHsc /MT /W3 /c /Zi'
        progCCFlags = '/Od /Gm /FD /EHsc /MT /W3 /c /Zi'
        defines = defines + ' /D "NDEBUG"'
        libLNFlags = '/LTCG'
        arFlags = '/LTCG'
        progLNFlags = '/LTCG /SUBSYSTEM:WINDOWS /MACHINE:X86'
        progLNCFlags = '/LTCG /SUBSYSTEM:CONSOLE /MACHINE:x86'

    libCCFlags += defines
    progCCFlags += defines
    
elif gPlatform == 'posix':
    defines = ' -D_IRR_STATIC_LIB_ -DSTATIC_LINKED'
    if gSound == 1:
        defines = defines + ' -DUSE_IRR_SOUND'
    elif gSound == 2:
        defines = defines + ' -DUSE_FMOD_SOUND'
    else:
        defines = defines + ' -DUSE_NULL_SOUND'

    if gProfiling:
        defines = ' -DPROFILING_ENABLED'

    if gDebug:
        libCCFlags = '-Wall -pipe -g' + defines
        progCCFlags = '-Wall -pipe -g' + defines
        arFlags = ''
    else:
        libCCFlags = '-Wall -pipe -fexpensive-optimizations -O3' + defines
        progCCFlags = '-Wall -pipe -fexpensive-optimizations -O3' + defines
        arFlags = ''

env.Append(CCFLAGS = libCCFlags)
env.Append(LINKFLAGS = libLNFlags)
env.Append(ARFLAGS = arFlags)

if not gCleaning and not gHelpOnly:
    print('Generating SWIG Wrapper...')
    swig = 'swig -lua -c++ -I' + iTubras + ' -I' + iIrrlicht + ' -o src/swig/tubras_wrap_lua.cpp src/swig/tubras.i'
    p = subprocess.Popen(swig.split())
    p.wait()
    rc = p.returncode
    if rc != 0:
        print('Error Generating SWIG Wrappers')
        sys.exit(1)

envProgs.Append(CCFLAGS = progCCFlags)
envProgs.Append(LINKFLAGS = progLNFlags)
envProgsC.Append(CCFLAGS = progCCFlags) 
envProgsC.Append(LINKFLAGS = progLNCFlags)

#
# Setup source files.  Non tubras files will be compiled using the Object()
# builder. The output (.obj) will be used as input along with the Tubras
# source file for generating the final "Tubras" library.  We separate these
# compiles in order to take advantage of precompile headers.
#
objCppFiles = []
cppFiles = []
extPrefix = 'tools/irrlicht/extensions/'

tnpchfiles = [extPrefix + 'CIrrBMeshFileLoader.cpp', 
    extPrefix + 'CIrrBMeshWriter.cpp',
    extPrefix + 'CGUISceneNode.cpp', 
    'src/swig/tubras_wrap_lua.cpp']
tubrasNonPCHFiles = []

for file in tnpchfiles:
    tubrasNonPCHFiles.append(file)

# Irrlicht source files
#cppFiles += ['deps/irrlicht/source/Irrlicht/CSkinnedMesh.cpp',
#    'deps/irrlicht/source/Irrlicht/os.cpp',
#    'deps/irrlicht/source/Irrlicht/CBoneSceneNode.cpp']
#

# Bullet source files
objCppFiles += glob.glob('deps/bullet/src/BulletCollision/BroadphaseCollision/*.cpp')
objCppFiles += glob.glob('deps/bullet/src/BulletCollision/CollisionDispatch/*.cpp')
objCppFiles += glob.glob('deps/bullet/src/BulletCollision/CollisionShapes/*.cpp')
objCppFiles += glob.glob('deps/bullet/src/BulletCollision/Gimpact/*.cpp')
objCppFiles += glob.glob('deps/bullet/src/BulletCollision/NarrowPhaseCollision/*.cpp')

objCppFiles += glob.glob('deps/bullet/src/BulletDynamics/Character/*.cpp')
objCppFiles += glob.glob('deps/bullet/src/BulletDynamics/ConstraintSolver/*.cpp')
objCppFiles += glob.glob('deps/bullet/src/BulletDynamics/Dynamics/*.cpp')
objCppFiles += glob.glob('deps/bullet/src/BulletDynamics/Vehicle/*.cpp')

objCppFiles += glob.glob('deps/bullet/src/LinearMath/*.cpp')
objCppFiles += glob.glob('deps/bullet/Extras/ConvexDecomposition/*.cpp')

# LUA source files
objCppFiles += ['src/lua/lapi.c',
	'src/lua/lauxlib.c',
	'src/lua/lbaselib.c',
    'src/lua/ldblib.c',
    'src/lua/liolib.c',
    'src/lua/lmathlib.c',
    'src/lua/loslib.c',
    'src/lua/lstrlib.c',
    'src/lua/ltablib.c',
	'src/lua/lcode.c',
	'src/lua/ldebug.c',
	'src/lua/ldo.c',
	'src/lua/ldump.c',
	'src/lua/lfunc.c',
	'src/lua/lgc.c',
	'src/lua/llex.c',
	'src/lua/lmem.c',
	'src/lua/loadlib.c',
	'src/lua/lobject.c',
	'src/lua/lopcodes.c',
	'src/lua/lparser.c',
	'src/lua/lstate.c',
	'src/lua/lstring.c',
	'src/lua/ltable.c',
	'src/lua/ltm.c',
	'src/lua/lua.c',
	'src/lua/lundump.c',
	'src/lua/lvm.c',
	'src/lua/lzio.c'
]


# Tubras non-pch files
objCppFiles += tubrasNonPCHFiles

# set the obj build
envObj = env.Clone()
Default(envObj.Object(source = objCppFiles))

objFiles = []
for file in objCppFiles:
    if gPlatform == 'win32':
        if file.find('.cpp') >= 0:
            objFiles.append(file.replace('.cpp','.obj'))
        else:
            objFiles.append(file.replace('.c','.obj'))
    else:
        if file.find('.cpp') >= 0:
            objFiles.append(file.replace('.cpp','.o'))
        else:
            objFiles.append(file.replace('.c','.o'))

# Tubras source files
cppFiles += glob.glob('src/*.cpp')

for file in tubrasNonPCHFiles:
    if file in cppFiles:
        cppFiles.remove(file)

cppFiles += objFiles

# PCH/GCH 
if gPlatform == 'win32':
    cppFiles.remove('src\\Tubras.cpp')
    cppFiles.append('src\\Tubras.obj')

    env['PCH'] = env.PCH('src/Tubras.cpp')[0] 
    env['PCHSTOP'] = 'tubras.h'

env.Append(TubrasSourceFiles = cppFiles)
Export('env')

library = env.StaticLibrary(tLibName,cppFiles)
Default(library)

# Libraries 
if gPlatform == 'win32':
    objExt = '.obj'
    Libraries = ['user32', 'gdi32', 'Advapi32']
    if gDebug:
        Libraries += ['Tubras_d']
    else:
        Libraries += ['Tubras']
    iLibraries = ['user32', 'gdi32', 'Advapi32']
else:
    objExt = '.o'
    if gDebug:
        Libraries = ['pthread','Tubras_d','Irrlicht', 'GL','Xxf86vm','util' ]
    else:
        Libraries = ['pthread','Tubras','Irrlicht', 'GL','Xxf86vm', 'util']
    iLibraries = ['pthread','Irrlicht', 'GL','Xxf86vm', 'util']
    if gSound == 1:
        Libraries.append('IrrKlang')

#
# Applications, Tools, & Tests
# 
Default(envProgs.Program('bin/sandbox','examples/sandbox/sandbox.cpp',
        LIBS=Libraries, LIBPATH=LibPath))

Default(envProgs.Program('bin/guidemo','examples/guidemo/guidemo.cpp',
        LIBS=Libraries, LIBPATH=LibPath))

Default(envProgs.Program('bin/tsltest','examples/tsltest/tsltest.cpp',
        LIBS=Libraries, LIBPATH=LibPath))

Default(envProgs.Program('bin/entitytest','examples/entitytest/entitytest.cpp',
        LIBS=Libraries, LIBPATH=LibPath))

Default(envProgs.Program('bin/iwalktest','tools/iwalktest/iwalktest.cpp',
        LIBS=Libraries, LIBPATH=LibPath))

Default(envProgsC.Program('bin/imeshcvt','tools/imeshcvt/imeshcvt.cpp',
        LIBS=Libraries, LIBPATH=LibPath))

Default(envProgs.Program('bin/tslcheck','tools/tslcheck/tslcheck.cpp',
        LIBS=Libraries, LIBPATH=LibPath))

Default(envProgsC.Program('bin/idebug',['tools/idebug/idebug.cpp',
        'tools/idebug/COverlay.cpp', 'tools/idebug/CTextOverlay.cpp'],
        LIBS=Libraries, LIBPATH=LibPath))

Default(envProgs.Program('bin/tse','tools/tse/tse.cpp',
        LIBS=Libraries, LIBPATH=LibPath))


Default(envProgs.Program('bin/isandbox',['tools/isandbox/main.cpp',
        'tools/irrlicht/extensions/CGUISceneNode' + objExt,
        'tools/irrlicht/extensions/CApplication.cpp',
        'tools/irrlicht/extensions/CGUITextPanel.cpp',
        'tools/irrlicht/extensions/CXMLConfig.cpp'],
        LIBS=iLibraries, LIBPATH=LibPath))

