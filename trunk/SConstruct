#-----------------------------------------------------------------------------
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
import os, sys, subprocess, glob, shutil, platform

gPlatform = Environment()['PLATFORM']
gDepsDir = 'deps/'
gDebug  = False
gHelpOnly = False
gHavePySVN = False
gCleaning = False
gProfiling = False
gPerfHUD = False
gBuildDocs = 0
gSound = 0
gScript = 1
gExtras = 1
gIncludeD3D9 = 1
gTargetArch = 'x86'

gDocIn = 'doc/apiheaders.txt'
gDocOut = 'doc/src/api/'

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
#      'wget' - get via wget.
#
# Note if wget url ends in '.zip', the retrieved file is unzipped and then
# if 'rename from' parameter exists, the directory is renamed from 
# 'rename from' to 'dependency name'.
#
gDepsV01 = {
    'irrklang':['http://www.ambiera.at/downloads/irrKlang-1.3.0b.zip','wget','irrKlang-1.3.0', 
        False,  'irrklang Sound Library'],
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
        'bin/ikpMP3.dll'),
        )
}

gExtraNoDefs = ('NO__IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_',
    'NO__IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_',
    'NO__IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_',
    'NO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_',
    'NO_IRR_COMPILE_WITH_BZIP2_',
    'NO_IRR_USE_NON_SYSTEM_BZLIB_',
    'NO_IRR_COMPILE_WITH_LZMA_',
    'NO_IRR_COMPILE_WITH_BMP_WRITER_',
    'NO_IRR_COMPILE_WITH_JPG_WRITER_',
    'NO_IRR_COMPILE_WITH_PCX_WRITER_',
    'NO_IRR_COMPILE_WITH_PPM_WRITER_',
    'NO_IRR_COMPILE_WITH_PSD_WRITER_',
    'NO_IRR_COMPILE_WITH_TGA_WRITER_',
    'NO_IRR_COMPILE_WITH_RGB_LOADER_',
    'NO_IRR_COMPILE_WITH_LMP_LOADER_',
    'NO_IRR_COMPILE_WITH_WAL_LOADER_',
    'NO_IRR_COMPILE_WITH_DDS_LOADER_',
    'NO_IRR_COMPILE_WITH_PSD_LOADER_',
    'NO_IRR_COMPILE_WITH_PPM_LOADER_',
    'NO_IRR_COMPILE_WITH_PCX_LOADER_',
    'NO_IRR_COMPILE_WITH_JPG_LOADER_',
    'NO_IRR_COMPILE_WITH_RGB_LOADER_',
    'NO_IRR_COMPILE_WITH_IRR_WRITER_',
    'NO_IRR_COMPILE_WITH_COLLADA_WRITER_',
    'NO_IRR_COMPILE_WITH_STL_WRITER_',
    'NO_IRR_COMPILE_WITH_OBJ_WRITER_',
    'NO_IRR_COMPILE_WITH_PLY_WRITER_',
    'NO_IRR_COMPILE_WITH_IRR_WRITER_',
    'NO_IRR_COMPILE_WITH_PLY_LOADER_',
    'NO_IRR_COMPILE_WITH_STL_LOADER_',
    'NO_IRR_COMPILE_WITH_LWO_LOADER_',
    'NO_IRR_COMPILE_WITH_OCT_LOADER_',
    'NO_IRR_COMPILE_WITH_OBJ_LOADER_',
    'NO_IRR_COMPILE_WITH_MY3D_LOADER_',
    'NO_IRR_COMPILE_WITH_LMTS_LOADER_',
    'NO_IRR_COMPILE_WITH_DMF_LOADER_',
    'NO_IRR_COMPILE_WITH_BSP_LOADER_',
    'NO_IRR_COMPILE_WITH_CSM_LOADER_',
    'NO_IRR_COMPILE_WITH_COLLADA_LOADER_',
    'NO_IRR_COMPILE_WITH_3DS_LOADER_',
    'NO_IRR_COMPILE_WITH_MD3_LOADER_',
    'NO_IRR_COMPILE_WITH_MD2_LOADER_',
    'NO_IRR_COMPILE_WITH_HALFLIFE_LOADER_',
    'NO_IRR_COMPILE_WITH_OGRE_LOADER_',
    'NO_IRR_COMPILE_WITH_X_LOADER_',
    'NO_IRR_COMPILE_WITH_MS3d_LOADER_',
    'NO_IRR_COMPILE_WITH_B3D_LOADER_',
    'NO_IRR_COMPILE_WITH_SMF_LOADER_',
    )

# fix for nacl-ar on win32 (http://www.scons.org/wiki/LongCmdLinesOnWin32)
class ourSpawn:
    def ourspawn(self, sh, escape, cmd, args, env):
        newargs = ' '.join(args[1:])
        cmdline = cmd + " " + newargs
        startupinfo = subprocess.STARTUPINFO()
        startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        proc = subprocess.Popen(cmdline, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, startupinfo=startupinfo, shell = False, env = env)
        data, err = proc.communicate()
        rv = proc.wait()
        if rv:
            print "====="
            print err
            print "====="
        return rv

def SetupSpawn( env ):
    if sys.platform == 'win32':
        buf = ourSpawn()
        buf.ourenv = env
        env['SPAWN'] = buf.ourspawn

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
def checkDeps(deps):
    if not os.path.exists("bin"):
        os.mkdir("bin")

    if not os.path.exists("libs"):
        os.mkdir("libs")

    if not os.path.exists('libs/debug'):
        os.mkdir("libs/debug")

    if not os.path.exists('libs/debug64'):
        os.mkdir("libs/debug64")

    if not os.path.exists('libs/release'):
        os.mkdir("libs/release")

    if not os.path.exists('libs/release64'):
        os.mkdir("libs/release64")

    if not os.path.exists(gDepsDir):
        os.mkdir(gDepsDir)        

    if not deps:
        return True

    if not deps.lower() in gDeps:
        if deps != '?':
            print('Invalid dependency: "{0}"'.format(deps))
        print('Available Dependencies:')
        for libName, info in gDeps.items():
            print('  {0} - {1}'.format(libName, info[4]))            
        return False

    libName = deps
    info = gDeps[libName]
    
    libLocal = gDepsDir + libName
    libRemote = info[0]

    exists = os.path.exists(libLocal)
    info[2] = exists

    print('Dependency (%s) Exists=%d' % (libName, exists))
    if not exists:
        dname = libLocal + '.zip'
        if not os.path.exists(dname):
            rc = downloadDep(libName, libLocal, libRemote)
        renameFrom = None
        if len(info) == 3:
            renameFrom = info[2]

        unzipDep(libName,libLocal, renameFrom)

    # Dependency file copies
    fileInfos = gDepsCopy[libName]
    for fileInfo in fileInfos:
        plat = fileInfo[0]
        fname = fileInfo[1]            
        tname = fileInfo[2]
        if plat == gPlatform and os.path.exists(fname) and not os.path.exists(tname):
            print('Dep Copy ({0}) -> {1}'.format(libName, tname))
            shutil.copy(fname, tname)

    print('Dependency Updated.')
    return False

#--------------------------------------------------------------------
#                            m a i n
#--------------------------------------------------------------------
Help("""
 Build Arguments/Options:
      debug=1           Builds the debug version.

       d3d9=?           Include the DirectX 9 device:
                           0 - Do not include
                           1 - Include (default) DXSDK_DIR must be defined
                        
      sound=?           Selects the Sound System to use:
                           0 - NULL Sound System (default)
                           1 - irrKlang Sound System
                           2 - FMOD Sound system

       arch=?           Target architecture:       
                           0 - build arch (default)
                           1 - x86 
                           2 - x86_64
                           3 - nacl_32
                           4 - nacl_64

       docs=?           Enable/Disable documenation generation
                           0 - Disable (default)
                           1 - Enable
                           
     extras=?           Enable/Disable 'extra' image/mesh loaders/writers
                           0 - Disable extras
                           1 - Enable extras (default)

    profile=?           Enables/Disables profiling:
                           0 - Disable (default)
                           1 - Enable

    perfhud=?           Enable NVidia PerfHUD
                           0 - Disable (default)
                           1 - Enable

     depver=x.x         Specify dependency version to use. Default is 'head'.
                        Use 'depver=?' for a list of available versions.

       deps={name}      Retrieve Dependencies, 'deps=?' for a list of
                        available dependencies.                      
      """)

args = sys.argv[1:]
if '-h' in args:
    gHelpOnly = True

if '-c' in args:
    gCleaning = True

if int(ARGUMENTS.get('debug',0)):
    gDebug = True

gSound = int(ARGUMENTS.get('sound', gSound))
if gSound < 0 or gSound > 2:
    gSound = 0

gExtras = int(ARGUMENTS.get('extras', gExtras))
if gExtras < 0 or gExtras > 1:
    gExtras = 1

if gPlatform == 'win32':
    if 'DXSDK_DIR' in os.environ:
        gIncludeD3D9 = int(ARGUMENTS.get('d3d9', gIncludeD3D9))
        if gIncludeD3D9 < 0 or gIncludeD3D9 > 1:
            gIncludeD3D9 = 1
            print('DXSDK_DIR environment variable missing - disabling')
    else:
        gIncludeD3D9 = 0

tarch = int(ARGUMENTS.get('arch',0))

if tarch == 0: # use platform default
    is_64bit = (platform.architecture()[0] == '64bit')
    if is_64bit:
        gTargetArch = 'x86_64'
elif tarch == 2:
    gTargetArch = 'x86_64'
elif (tarch == 3) or (tarch == 4):
    gTargetArch = 'nacl'
    nacl_bits = '32'
    if tarch == 4:
        nacl_bits = '64'
    gIncludeD3D9 = 0

if int(ARGUMENTS.get('profile',0)):
    gProfiling  = True

if int(ARGUMENTS.get('perfhud',0)):
    gPerfHUD  = True

Export('gDebug')

deps = ARGUMENTS.get('deps', None)
if not gHelpOnly:
    if gCleaning:
        print('*')
        print('Cleaning project...')
        print('*')
    else:
        print('*')
        print('Building {0} Version Of The Tubras Library.'.format('Debug' if gDebug
            else 'Release'))

        print('Target Arch: {0} ({1} bit)'.format(gTargetArch, 32 if gTargetArch == 'x86' else 64))
        if gIncludeD3D9:
            print('Including Directx 9 device')

        if gExtras:
            print('Including extra image/mesh loaders')
        else:
            print('Excluding extra image/mesh loaders')

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

        if not checkDeps(deps):
            sys.exit(0)

#
# setup include paths
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
iIrrlichtDev = (iIrrlichtDev, iIrrlichtDev + '/zlib')
iIrrKlang = iPrefix + envTubras + gDepsDir + 'irrklang/include'
iFMOD = iPrefix + envTubras + gDepsDir + 'fmod/api/inc'

includePath.append(iTubras)
includePath.append(iLUA)
includePath.append(iBullet)
includePath.append(iIrrlicht)
includePath.append(iIrrlichtDev)
if gSound == 1:
    includePath.append(iIrrKlang)
elif gSound == 2:
    includePath.append(iFMOD)

includePath.append(iPrefix + envTubras + 'tools/irrlicht/extensions')
includePath.append(iPrefix + envTubras + 'tools/irrlicht/extensions/timing')

#
# setup output library based on build type
#
if gTargetArch == 'x86':
    tLibName = 'libs/release/Tubras'
    LibPath = ['libs/release']
    if gDebug:
        tLibName = 'libs/debug/Tubras_d'
        LibPath = ['libs/debug']
elif gTargetArch == 'x86_64':
    tLibName = 'libs/release64/Tubras'
    LibPath = ['libs/release64']
    if gDebug:
        tLibName = 'libs/debug64/Tubras_d'
        LibPath = ['libs/debug64']
elif gTargetArch == 'nacl':
    if 'NACL_SDK_ROOT' not in os.environ:
        print('NACL_SDK_ROOT Undefined')
        sys.exit(0)

    tLibName = 'libs/nacl/Tubras{0}'.format(nacl_bits)
    LibPath = ['libs/nacl']
    if gDebug:
        tLibName = 'libs/nacl/Tubra{0}_d'.format(nacl_bits)
        LibPath = ['libs/nacl']

if gPlatform == 'win32' and gIncludeD3D9 == 1:
    includePath.append(os.environ['DXSDK_DIR'] + '\\include')
    if gTargetArch == 'x86':
        LibPath.append(os.environ['DXSDK_DIR'] + '\\lib\\x86')
    else:
        LibPath.append(os.environ['DXSDK_DIR'] + '\\lib\\x64')    

if gTargetArch == 'nacl':
    nacl_root = os.environ['NACL_SDK_ROOT']
    import imp
    import SCons.Tool
    SCons.Tool.DefaultToolpath.append(os.path.join(nacl_root, 'build_tools', 'nacl_sdk_scons', 'site_tools'))


    nacl_utils = imp.load_source('nacl_utils', os.path.join(nacl_root, 'build_tools', 'nacl_sdk_scons', 'nacl_utils.py'))
    nacl_tools = imp.load_source('nacl_tools', os.path.join(nacl_root, 'build_tools', 'nacl_sdk_scons', 'site_tools', 'nacl_tools.py'))

    make_nacl_env = imp.load_source('make_nacl_env', os.path.join(nacl_root, 'build_tools', 'nacl_sdk_scons', 'make_nacl_env.py'))
    
    env = make_nacl_env.NaClEnvironment(use_c_plus_plus_libs=True)

    #env = Environment(CPPPATH = includePath)
    envProgs = Environment(CPPPATH = includePath)
    envProgsC = Environment(CPPPATH = includePath)
    
    gPlatform = 'nacl'

else:
    env = Environment(CPPPATH = includePath, MSVC_VERSION='9.0', TARGET_ARCH=gTargetArch)
    envProgs = Environment(CPPPATH = includePath, MSVC_VERSION='9.0', TARGET_ARCH=gTargetArch)
    envProgsC = Environment(CPPPATH = includePath, MSVC_VERSION='9.0', TARGET_ARCH=gTargetArch)

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
    if gTargetArch == 'x86_64':
        defines += ' /D "WIN64"'
    if gProfiling:
        defines += ' /D "PROFILING_ENABLED" /D "BT_NO_PROFILE"'
    if gPerfHUD:
        defines += ' /D "_IRR_USE_NVIDIA_PERFHUD_"'
    if gSound == 1:
        defines += ' /D "USE_SOUND_IRR"'
    elif gSound == 2:
        defines += ' /D "USE_SOUND_FMOD"'
    else:
        defines += ' /D "USE_SOUND_NULL"'

    defines += ' /D "NO_IRR_COMPILE_WITH_DIRECT3D_8_"'
    if gIncludeD3D9 == 0:
        defines += ' /D "NO_IRR_COMPILE_WITH_DIRECT3D_9_"'
    defines += ' /D "NO_IRR_COMPILE_WITH_SOFTWARE_"'
    defines += ' /D "NO_IRR_COMPILE_WITH_BURNINGSVIDEO_"'
    defines += ' /D "NO_IRR_COMPILE_WITH_JOYSTICK_EVENTS_"'

    if not gExtras:
        for define in gExtraNoDefs:
            defines += ' /D "{0}"'.format(define)
    
    if gDebug:
        if gTargetArch == 'x86':
            libCCFlags = '/Od /EHsc /RTC1 /MTd /W3 /c'
            progCCFlags = '/Od /EHsc /RTC1 /MTd /W3 /c'
            defines = defines + ' /D "_DEBUG"'
            progLNFlags = '/DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86'
            progLNCFlags = '/DEBUG /SUBSYSTEM:CONSOLE /MACHINE:X86'
            arFlags = ''
        else:
            libCCFlags = '/Od /EHsc /RTC1 /MTd /W3 /c'
            progCCFlags = '/Od /EHsc /RTC1 /MTd /W3 /c'
            defines = defines + ' /D "_DEBUG"'
            progLNFlags = '/DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X64'
            progLNCFlags = '/DEBUG /SUBSYSTEM:CONSOLE /MACHINE:X64'
            arFlags = ''        
    else:
        if gTargetArch == 'x86':
            libCCFlags = '/O2 /FD /EHsc /MT /W3 /c /GF /GS- /fp:fast'
            progCCFlags = '/O2 /FD /EHsc /MT /W3 /c /GF /GS- /fp:fast'
            defines = defines + ' /D "NDEBUG"'
            libLNFlags = ''
            arFlags = ''
            progLNFlags = '/SUBSYSTEM:WINDOWS /MACHINE:X86'
            progLNCFlags = '/SUBSYSTEM:CONSOLE /MACHINE:x86'
        else:
            libCCFlags = '/O2 /FD /EHsc /MT /W3 /c /GF /GS- /fp:fast'
            progCCFlags = '/O2 /FD /EHsc /MT /W3 /c /GF /GS- /fp:fast'
            defines = defines + ' /D "NDEBUG"'
            libLNFlags = ''
            arFlags = ''
            progLNFlags = '/SUBSYSTEM:WINDOWS /MACHINE:X64'
            progLNCFlags = '/SUBSYSTEM:CONSOLE /MACHINE:x64'

    libCCFlags += defines
    progCCFlags += defines
    
elif gPlatform == 'posix':
    defines = ' -D_IRR_STATIC_LIB_ -DSTATIC_LINKED'
    if gSound == 1:
        defines += ' -DUSE_SOUND_IRR'
    elif gSound == 2:
        defines += ' -DUSE_SOUND_FMOD'
    else:
        defines += ' -DUSE_SOUND_NULL'

    defines += ' -DNO_IRR_COMPILE_WITH_SOFTWARE_'
    defines += ' -DNO_IRR_COMPILE_WITH_BURNINGSVIDEO_'
    defines += ' -DNO_IRR_COMPILE_WITH_JOYSTICK_EVENTS_'
    defines += ' -DNO_IRR_COMPILE_WITH_DIRECT3D_8_'
    defines += ' -DNO_IRR_COMPILE_WITH_DIRECT3D_9_'
    defines += ' -DPNG_THREAD_UNSAFE_OK'
    defines += ' -DPNG_NO_MMX_CODE'
    defines += ' -DPNG_NO_MNG_FEATURES'
    defines += ' -DLUA_USE_MKSTEMP'

    if not gExtras:
        for define in gExtraNoDefs:
            defines += ' -D{0}'.format(define)

    if gProfiling:
        defines = ' -DPROFILING_ENABLED -DBT_NO_PROFILE'

    if gDebug:
        defines += ' -D_DEBUG'
        libCCFlags = '-Wall -pipe -g -fstrict-aliasing -fno-exceptions -fno-rtti' + defines
        progCCFlags = '-Wall -pipe -g -fstrict-aliasing -fno-exceptions -fno-rtti' + defines
        arFlags = ''
    else:
        libCCFlags = '-Wall -pipe -fstrict-aliasing -fno-exceptions -fno-rtti -fexpensive-optimizations -O3' + defines
        progCCFlags = '-Wall -pipe -fstrict-aliasing -fno-exceptions -fno-rtti -fexpensive-optimizations -O3' + defines
        arFlags = ''
elif gPlatform == 'nacl':
    defines = ' -D_IRR_STATIC_LIB_ -DSTATIC_LINKED'
    if gSound == 1:
        defines += ' -DUSE_SOUND_IRR'
    elif gSound == 2:
        defines += ' -DUSE_SOUND_FMOD'
    else:
        defines += ' -DUSE_SOUND_NULL'

    defines += ' -DNO_IRR_COMPILE_WITH_SOFTWARE_'
    defines += ' -DNO_IRR_COMPILE_WITH_BURNINGSVIDEO_'
    defines += ' -DNO_IRR_COMPILE_WITH_DIRECT3D_8_'
    defines += ' -DNO_IRR_COMPILE_WITH_DIRECT3D_9_'
    defines += ' -DNO_IRR_COMPILE_WITH_JOYSTICK_EVENTS_'
    defines += ' -DNO_IRR_COMPILE_WITH_CONSOLE_DEVICE_'
    defines += ' -DNO_IRR_COMPILE_WITH_OPENGL_'
    defines += ' -DPNG_THREAD_UNSAFE_OK'
    defines += ' -DPNG_NO_MMX_CODE'
    defines += ' -DPNG_NO_MNG_FEATURES'
    defines += ' -DLUA_USE_MKSTEMP'

    if not gExtras:
        for define in gExtraNoDefs:
            defines += ' -D{0}'.format(define)

    if gProfiling:
        defines = ' -DPROFILING_ENABLED -DBT_NO_PROFILE'

    if gDebug:
        defines += ' -D_DEBUG'
        libCCFlags = defines
        progCCFlags = defines
        #libCCFlags = '-Wall -pipe -g -fstrict-aliasing -fno-exceptions -fno-rtti' + defines
        #progCCFlags = '-Wall -pipe -g -fstrict-aliasing -fno-exceptions -fno-rtti' + defines
        arFlags = ''
    else:
        libCCFlags = '-pipe -fno-rtti -O2 -m{0}'.format(nacl_bits) + defines
        progCCFlags = '-pipe -fno-rtti -O2 -m{0}'.format(nacl_bits) + defines

        #libCCFlags = '-Wall -pipe -fstrict-aliasing -fno-exceptions -fno-rtti -fexpensive-optimizations -O3' + defines
        #progCCFlags = '-Wall -pipe -fstrict-aliasing -fno-exceptions -fno-rtti -fexpensive-optimizations -O3' + defines
        arFlags = ''

    env.Append(CPPPATH = includePath)

    SetupSpawn(env)

env.Replace(CCFLAGS = libCCFlags)
env.Append(LINKFLAGS = libLNFlags)
env.Append(ARFLAGS = arFlags)

envProgs.Replace(CCFLAGS = progCCFlags)
envProgs.Append(LINKFLAGS = progLNFlags)
envProgsC.Append(CCFLAGS = progCCFlags) 
envProgsC.Append(LINKFLAGS = progLNCFlags)

#
# Setup source files.  Non tubras files will be compiled using the Object()
# builder. The output (.obj) will be used as input along with the Tubras
# source file for generating the final "Tubras" library.  We separate these
# compiles in order to take advantage of precompiled headers.
#
objCppFiles = []
cppFiles = []
tubrasNonPCHFiles = []
extPrefix = 'tools/irrlicht/extensions/'

tnpchfiles = [extPrefix + 'CIrrAMeshFileLoader.cpp', 
    extPrefix + 'CIrrBMeshFileLoader.cpp',
    extPrefix + 'CIrrBMeshWriter.cpp',
    extPrefix + 'CGUISceneNode.cpp', 
    extPrefix + 'timing/CAnimator.cpp',
    extPrefix + 'timing/CTimingManager.cpp']
    
for file in tnpchfiles:
    tubrasNonPCHFiles.append(file)

# Irrlicht source files we use or inherit from.
irrFiles = ['deps/irrlicht/source/Irrlicht/CSkinnedMesh.cpp',
    'deps/irrlicht/source/Irrlicht/os.cpp',
    'deps/irrlicht/source/Irrlicht/CGUIEditBox.cpp',
    'deps/irrlicht/source/Irrlicht/CBoneSceneNode.cpp']
for file in irrFiles:
    tubrasNonPCHFiles.append(file)

cppFiles += irrFiles

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


# Irrlicht source files
objCppFiles += glob.glob('deps/irrlicht/source/Irrlicht/*.cpp')
objCppFiles += glob.glob('deps/irrlicht/source/Irrlicht/aesGladman/*.cpp')
objCppFiles += ['deps/irrlicht/source/Irrlicht/bzip2/blocksort.c',
    'deps/irrlicht/source/Irrlicht/bzip2/bzcompress.c',
    'deps/irrlicht/source/Irrlicht/bzip2/bzlib.c',
    'deps/irrlicht/source/Irrlicht/bzip2/crctable.c',
    'deps/irrlicht/source/Irrlicht/bzip2/decompress.c',
    'deps/irrlicht/source/Irrlicht/bzip2/huffman.c',
    'deps/irrlicht/source/Irrlicht/bzip2/randtable.c',
    ]
objCppFiles += glob.glob('deps/irrlicht/source/Irrlicht/lzma/*.c')
objCppFiles += glob.glob('deps/irrlicht/source/Irrlicht/zlib/*.c')

jpegFiles = ('jcapimin.c', 'jcapistd.c', 'jccoefct.c', 'jccolor.c',  'jcdctmgr.c', 'jchuff.c',
    'jcinit.c', 'jcmainct.c', 'jcmarker.c', 'jcmaster.c', 'jcomapi.c', 'jcparam.c', 'jcprepct.c',
    'jcsample.c', 'jctrans.c', 'jdapimin.c', 'jdapistd.c', 'jdatadst.c', 'jdatasrc.c', 
    'jdcoefct.c', 'jdcolor.c', 'jddctmgr.c', 'jdhuff.c', 'jdinput.c', 'jdmainct.c', 
    'jdmarker.c', 'jdmaster.c', 'jdmerge.c', 'jdpostct.c', 'jdsample.c', 'jdtrans.c', 
    'jerror.c', 'jfdctflt.c', 'jfdctfst.c', 'jfdctint.c', 'jidctflt.c', 'jidctfst.c', 
    'jidctint.c', 'jmemmgr.c', 'jmemnobs.c', 'jquant1.c', 'jquant2.c', 'jutils.c', 
    'jcarith.c', 'jdarith.c', 'jaricom.c')

for f in jpegFiles:
    objCppFiles.append('deps/irrlicht/source/Irrlicht/jpeglib' + os.sep + f)

objCppFiles += ['deps/irrlicht/source/Irrlicht/libpng/png.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngerror.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngget.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngmem.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngpread.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngread.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngrio.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngrtran.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngrutil.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngset.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngtrans.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngwio.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngwrite.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngwtran.c',
    'deps/irrlicht/source/Irrlicht/libpng/pngwutil.c',
    ]
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
    'src/lua/lzio.c',
    'src/lua/linit.c',
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

library = env.StaticLibrary(tLibName, cppFiles)
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
        Libraries = ['pthread', 'Tubras_d', 'GL', 'Xxf86vm', 'util', 'X11', 'Xext', 'Xcursor']
    else:
        Libraries = ['pthread','Tubras', 'GL', 'Xxf86vm', 'util', 'X11', 'Xext',  'Xcursor']
    iLibraries = ['pthread','Irrlicht', 'GL','Xxf86vm', 'util', 'X11', 'Xext', 'Xcursor']
    if gSound == 1:
        Libraries.append('IrrKlang')

#
# Applications, Tools, & Tests
# 
if gPlatform != 'nacl':

    Default(envProgs.Program('bin/sandbox','examples/sandbox/sandbox.cpp',
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgs.Program('bin/guidemo','examples/guidemo/guidemo.cpp',
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgs.Program('bin/tcstest','examples/tcstest/tcstest.cpp',
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgs.Program('bin/entitytest','examples/entitytest/entitytest.cpp',
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgs.Program('bin/iwalktest',['tools/iwalktest/iwalktest.cpp',
            'tools/iwalktest/cmdproc.cpp', 'tools/iwalktest/aboutdlg.cpp'],        
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgsC.Program('bin/imeshcvt','tools/imeshcvt/imeshcvt.cpp',
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgs.Program('bin/tcslint','tools/tcslint/tcslint.cpp',
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgs.Program('bin/tse','tools/tse/tse.cpp',
            LIBS=Libraries, LIBPATH=LibPath))
        
    Default(envProgsC.Program('bin/idebug',['tools/idebug/idebug.cpp',
            'tools/idebug/COverlay.cpp', 'tools/idebug/CTextOverlay.cpp'],
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgs.Program('bin/isandbox',['tools/isandbox/main.cpp',
            'tools/irrlicht/extensions/CGUISceneNode' + objExt,
            'tools/irrlicht/extensions/CApplication.cpp',
            'tools/irrlicht/extensions/CGUITextPanel.cpp',
            'tools/irrlicht/extensions/CPhysicsManager.cpp',
            'tools/irrlicht/extensions/CXMLConfig.cpp'],
            LIBS=Libraries, LIBPATH=LibPath))

    Default(envProgs.Program('bin/itiming',['tools/irrlicht/examples/itiming/main.cpp',
            'tools/irrlicht/examples/itiming/COverlay.cpp',
            'tools/irrlicht/examples/itiming/CTextOverlay.cpp',
            'tools/irrlicht/extensions/timing/CAnimator'  + objExt,
            'tools/irrlicht/extensions/timing/CTimingManager'  + objExt],
            LIBS=Libraries, LIBPATH=LibPath))

