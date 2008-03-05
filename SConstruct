import os, sys, subprocess, glob


gPlatform = Environment()['PLATFORM']
gDepsDir = 'deps/'
gDebug  = False
gHelpOnly = False
#
# dependencies
#

gDeps = {\
    'bullet':('http://prdownloads.sourceforge.net/bullet/bullet-2.66A.zip','bullet-2.66'),\
    'irrlicht':('http://prdownloads.sourceforge.net/irrlicht/irrlicht-1.4.zip','irrlicht-1.4'),\
    'irrklang':('http://irrlicht.piskernig.at/irrKlang-1.0.4.zip','irrKlang-1.0.4'),\
    'ois':('http://prdownloads.sourceforge.net/wgois/ois-1.0RC1_Win32.zip','ois-1.0RC1')
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
#                         u n z i p D e p
#--------------------------------------------------------------------
def unzipDep(libName, libLocal, renameFrom):
    rc = True
    dname = libLocal + '.zip'
    print 'Unzipping ' + libName + '...'

    commandline = 'unzip -o -qq ' + dname + ' -d ' + gDepsDir
    p = subprocess.Popen(commandline.split())    
    p.wait()
    rc = p.returncode

    os.rename(gDepsDir + renameFrom, gDepsDir + libName);

    return rc
    

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
            dname = libLocal + '.zip'
            if not os.path.exists(dname):
                rc = downloadDep(libName, libLocal, libRemote)

            unzipDep(libName,libLocal, info[1])
            
    return True

#--------------------------------------------------------------------
#                            m a i n
#--------------------------------------------------------------------
Help("""
      Type: 'scons debug=1' to build the debug version.
      """)

args = sys.argv[1:]
if '-h' in args:
    gHelpOnly = True

if int(ARGUMENTS.get('debug',0)):
    gDebug = True

if not gHelpOnly:
    if not checkDeps():
        sys.exit(0)

#
# setup include paths
#
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
iTubras = iPrefix + envTubras + 'include'
iBullet = iPrefix + envTubras + gDepsDir + 'bullet/src'
iOIS = iPrefix + envTubras + gDepsDir + 'ois/includes'
iIrrlicht = iPrefix + envTubras + gDepsDir + 'irrlicht/include'
iIrrlichtDev = iPrefix + envTubras + gDepsDir + 'irrlicht/source/Irrlicht'
iIrrKlang = iPrefix + envTubras + gDepsDir + 'irrklang/include'

includePath.append(iTubras)
includePath.append(iBullet)
includePath.append(iOIS)
includePath.append(iIrrlicht)
includePath.append(iIrrlichtDev)
includePath.append(iIrrKlang)

env = Environment(CPPPATH = includePath)
envProgs = Environment(CPPPATH = includePath)
envProgsC = Environment(CPPPATH = includePath)

#
# setup output library based on build type
#
tLibName = 'libs/release/Tubras'
LibPath = 'libs/release'
if gDebug:
    tLibName = 'libs/debug/Tubras'
    LibPath = 'libs/debug'

#
# setup compiler flags based on platform type
#
libCCFlags = ''
libLNFlags = ''
progCCFlags = ''
progLNFlags = ''
progLNCFlags = ''

if gPlatform == 'win32':
    defines = ' /D "WIN32" /D "_LIB" /D "_UNICODE" /D "UNICODE"'
    if gDebug:
        libCCFlags = '/Od /Gm /EHsc /RTC1 /MTd /W3 /c /Wp64 /ZI /TP'
        progCCFlags = '/Od /Gm /EHsc /RTC1 /MTd /W3 /c /Wp64 /ZI /TP'
        defines = defines + ' /D "_DEBUG"'
        progLNFlags = '/DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86'
        progLNCFlags = '/DEBUG /SUBSYSTEM:CONSOLE /MACHINE:X86'
    else:
        libCCFlags = '/O2 /GL /FD /EHsc /MT /W3 /c /Wp64 /Zi /TP'
        progCCFlags = '/Od /Gm /FD /EHsc /MT /W3 /c /Wp64 /Zi /TP'
        defines = defines + ' /D "NDEBUG"'
        libLNFlags = '/LTCG'
        progLNFlags = '/LTCG /SUBSYSTEM:WINDOWS /MACHINE:X86'
        progLNCFlags = '/LTCG /SUBSYSTEM:CONSOLE /MACHINE:x86'

    libCCFlags += defines
    progCCFlags += defines
    
        
elif gPlatform == 'posix':
    if gDebug:
        libCCFlags = '-g'
        progCCFlags = '-g'

env.Append(CCFLAGS = libCCFlags)
env.Append(LINKFLAGS = libLNFlags)

envProgs.Append(CCFLAGS = progCCFlags)
envProgs.Append(LINKFLAGS = progLNFlags)
envProgsC.Append(CCFLAGS = progCCFlags)
envProgsC.Append(LINKFLAGS = progLNCFlags)

cppFiles = glob.glob('src/*.cpp')

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
    if gDebug:
        Libraries = ['Tubras','Irrlicht','libbulletdynamics_d','libbulletcollision_d',\
            'libbulletmath_d','irrklang','ois_static_d','user32','gdi32']
    else:
        Libraries = ['Tubras','Irrlicht','libbulletdynamics','libbulletcollision',\
            'libbulletmath','irrklang','ois_static','user32','gdi32']    
else:
    Libraries = ['pthread','IrrKlang','Tubras','Irrlicht','bulletdynamics','bulletcollision',\
        'bulletmath','OIS','GL','Xxf86vm']

sandbox = envProgs.Program('bin/sandbox','samples/sandbox/sandbox.cpp',\
        LIBS=Libraries, LIBPATH=LibPath)
Default(sandbox)

guidemo = envProgs.Program('bin/guidemo','samples/guidemo/guidemo.cpp',\
        LIBS=Libraries, LIBPATH=LibPath)
Default(guidemo)

iwalktest = envProgs.Program('bin/iwalktest','tools/iwalktest/iwalktest.cpp',\
        LIBS=Libraries, LIBPATH=LibPath)
Default(iwalktest)

imeshcvt = envProgsC.Program('bin/imeshcvt','tools/imeshcvt/imeshcvt.cpp',\
        LIBS=Libraries, LIBPATH=LibPath)
Default(imeshcvt)

