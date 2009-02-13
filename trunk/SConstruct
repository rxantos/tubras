#-----------------------------------------------------------------------------
# This source file is part of the Tubras game engine.
#
# Copyright (c) 2006-2008 Tubras Software, Ltd
# Also see acknowledgements in docs/Readme.html
#
# This software is licensed under the zlib/libpng license. See the file
# "docs/license.html" for detailed information.
#-----------------------------------------------------------------------------
import os, sys, subprocess, glob

gPlatform = Environment()['PLATFORM']
gDepsDir = 'deps/'
gDebug  = True
gDepsOnly = False
gHelpOnly = False
gHavePySVN = False
gCleaning = False
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
    'irrklang':('http://www.ambiera.at/downloads/irrKlang-1.1.3.zip','wget','irrKlang-1.1.3')
    }

gTubrasVersionDeps = {
    'head':gDepsV01
    }

gDepsBuild = {
    'bullet debug':('devenv deps/bullet/msvc/8/wksbullet.sln /build Debug /project grplibs_bullet'),
    '':()
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

    if not os.path.exists("libs"):
        os.mkdir("libs")
        os.mkdir("libs/debug")
        os.mkdir("libs/release")

        
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

     script=?           Enable/Disable Scripting:
                           1 - Enabled (default)
                           0 - Disabled

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

gScript = int(ARGUMENTS.get('script',1))
if gScript != 1 and gScript != 0:
    gScript = 1 

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

        if gScript == 1:
            print('Scripting: Enabled')
        else:
            print('Scripting: Disabled')

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
SConscript(['tools/lsl/SConscript'])

path = []
includePath = []
try:
    envTubras = os.environ['ITUBRAS']
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

iLSL = iPrefix + envTubras + 'tools/lsl/include'
iTubras = iPrefix + envTubras + 'include'
iBullet = iPrefix + envTubras + gDepsDir + 'bullet/src'
iIrrlicht = iPrefix + envTubras + gDepsDir + 'irrlicht/include'
iIrrlichtDev = iPrefix + envTubras + gDepsDir + 'irrlicht/source/Irrlicht'
iIrrKlang = iPrefix + envTubras + gDepsDir + 'irrklang/include'

includePath.append(iTubras)
includePath.append(iLSL)
includePath.append(iBullet)
includePath.append(iIrrlicht)
includePath.append(iIrrlichtDev)
includePath.append(iIrrKlang)

env = Environment(CPPPATH = includePath, MSVS_VERSION='8.0')
envProgs = Environment(CPPPATH = includePath, MSVS_VERSION='8.0')
envProgsC = Environment(CPPPATH = includePath, MSVS_VERSION='8.0')

#
# setup output library based on build type
#
tLibName = 'libs/release/Tubras'
LibPath = ['libs/release','tools/lsl/libs']
if gDebug:
    tLibName = 'libs/debug/Tubras_d'
    LibPath = ['libs/debug','tools/lsl/libs']

#
# setup compiler flags based on platform type
#
libCCFlags = ''
libLNFlags = ''
progCCFlags = ''
progLNFlags = ''
progLNCFlags = ''

if gPlatform == 'win32':
    defines = ' /D "WIN32" /D "_LIB" /D "_IRR_STATIC_LIB_"'
    if gSound == 1:
        defines = defines + ' /D "USE_IRR_SOUND"'
    elif gSound == 2:
        defines = defines + ' /D "USE_FMOD_SOUND"'
    else:
        defines = defines + ' /D "USE_NULL_SOUND"'

    if gScript == 0:
        defines = defines + ' /D "DISABLE_SCRIPTING"'
        
    if gDebug:
        libCCFlags = '/Od /Gm /EHsc /RTC1 /MTd /W3 /c /Wp64 /ZI'
        progCCFlags = '/Od /Gm /EHsc /RTC1 /MTd /W3 /c /Wp64 /ZI'
        defines = defines + ' /D "_DEBUG"'
        progLNFlags = '/DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86'
        progLNCFlags = '/DEBUG /SUBSYSTEM:CONSOLE /MACHINE:X86'
    else:
        libCCFlags = '/O2 /GL /FD /EHsc /MT /W3 /c /Wp64 /Zi'
        progCCFlags = '/Od /Gm /FD /EHsc /MT /W3 /c /Wp64 /Zi'
        defines = defines + ' /D "NDEBUG"'
        libLNFlags = '/LTCG'
        progLNFlags = '/LTCG /SUBSYSTEM:WINDOWS /MACHINE:X86'
        progLNCFlags = '/LTCG /SUBSYSTEM:CONSOLE /MACHINE:x86'

    libCCFlags += defines
    progCCFlags += defines
    
elif gPlatform == 'posix':
    defines = ' -D_IRR_STATIC_LIB_'
    if gSound == 1:
        defines = defines + ' -DUSE_IRR_SOUND'
    elif gSound == 2:
        defines = defines + ' -DUSE_FMOD_SOUND'
    else:
        defines = defines + ' -DUSE_NULL_SOUND'
        
    if gScript == 0:
        defines = defines + ' -DDISABLE_SCRIPTING'
        
    if gDebug:
        libCCFlags = '-Wall -pipe -g' + defines
        progCCFlags = '-Wall -pipe -g' + defines
    else:
        libCCFlags = '-Wall -pipe -fexpensive-optimizations -O3' + defines
        progCCFlags = '-Wall -pipe -fexpensive-optimizations -O3' + defines


env.Append(CCFLAGS = libCCFlags)
env.Append(LINKFLAGS = libLNFlags)

envProgs.Append(CCFLAGS = progCCFlags)
envProgs.Append(LINKFLAGS = progLNFlags)
envProgsC.Append(CCFLAGS = progCCFlags)
envProgsC.Append(LINKFLAGS = progLNCFlags)

cppFiles = glob.glob('src/*.cpp')
cppFiles += ['deps/irrlicht/source/Irrlicht/CSkinnedMesh.cpp',
    'deps/irrlicht/source/Irrlicht/os.cpp',
    'deps/irrlicht/source/Irrlicht/CBoneSceneNode.cpp']

#
# update files to point at 'objs/{filename}' in order
# for the object files to be generated in the 'objs' directory.
#
# this looks like we are compiling against 'objs/{source}.cpp', 
# but we really aren't...
#
i = 0
for file in cppFiles:
    nfile = file.replace('src','objs')
    cppFiles[i] = nfile
    i += 1
env.Append(TubrasSourceFiles = cppFiles)

env.BuildDir('objs', 'src', duplicate=0)

Export('env')

library = env.StaticLibrary(tLibName,cppFiles)
Default(library)

#
# setup samples
#

# linux libraries 
if gPlatform == 'win32':
    Libraries = ['user32', 'gdi32', 'Advapi32']
else:
    if gDebug:
        Libraries = ['pthread','Tubras_d','Irrlicht','bulletdynamics','bulletcollision',\
            'bulletmath','GL','Xxf86vm','util', 'CLSL_d']
    else:
        Libraries = ['pthread','Tubras','Irrlicht','bulletdynamics','bulletcollision',\
            'bulletmath','GL','Xxf86vm', 'util', 'CLSL']
    if gSound == 1:
        Libraries.append('IrrKlang')

sandbox = envProgs.Program('bin/sandbox','samples/sandbox/sandbox.cpp',
        LIBS=Libraries, LIBPATH=LibPath)
Default(sandbox)

guidemo = envProgs.Program('bin/guidemo','samples/guidemo/guidemo.cpp',
        LIBS=Libraries, LIBPATH=LibPath)
Default(guidemo)

iwalktest = envProgs.Program('bin/iwalktest','tools/iwalktest/iwalktest.cpp',
        LIBS=Libraries, LIBPATH=LibPath)
Default(iwalktest)

imeshcvt = envProgsC.Program('bin/imeshcvt','tools/imeshcvt/imeshcvt.cpp',
        LIBS=Libraries, LIBPATH=LibPath)
Default(imeshcvt)

idebug = envProgsC.Program('bin/idebug',['tools/idebug/idebug.cpp',
        'tools/idebug/COverlay.cpp', 'tools/idebug/CTextOverlay.cpp'],
        LIBS=Libraries, LIBPATH=LibPath)
Default(idebug)

if gScript < 3:
    tse = envProgs.Program('bin/tse','tools/tse/tse.cpp',
            LIBS=Libraries, LIBPATH=LibPath)
    Default(tse)
