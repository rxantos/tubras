import os, sys, subprocess

platform = Environment()['PLATFORM']
depsDir = 'deps/'
#
# dependencies
#

deps = {\
    'bullet':('http://prdownloads.sourceforge.net/bullet/bullet-2.66A.zip','bullet-2.66'),\
    'irrlicht':('http://prdownloads.sourceforge.net/irrlicht/irrlicht-1.4.zip','irrlicht-1.4'),\
    'irrklang':('http://irrlicht.piskernig.at/irrKlang-1.0.4.zip','irrKlang-1.0.4'),\
    'irrxml':('http://prdownloads.sourceforge.net/irrlicht/irrxml-1.2.zip','irrxml-1.2'),\
    'ois':('http://prdownloads.sourceforge.net/wgois/ois-1.0RC1_Win32.zip','ois-1.0RC1')
    }

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

def unzipDep(libName, libLocal, renameFrom):
    rc = True
    dname = libLocal + '.zip'
    print 'Unzipping ' + libName + '...'

    commandline = 'unzip -o -qq ' + dname + ' -d ' + depsDir
    p = subprocess.Popen(commandline.split())    
    p.wait()
    rc = p.returncode

    os.rename(depsDir + renameFrom, depsDir + libName);

    return rc
    

def checkDeps():
    print 'checkDeps()'
    if not os.path.exists(depsDir):
        os.mkdir(depsDir)
    for libName,info in deps.items():
        libLocal = depsDir + libName
        libRemote = info[0]

        exists = os.path.exists(libLocal)
        print 'Dependency (%s) Exists=%d' % (libName,exists)
        if not exists:
            dname = libLocal + '.zip'
            if not os.path.exists(dname):
                rc = downloadDep(libName, libLocal, libRemote)

            unzipDep(libName,libLocal, info[1])
            
    return True

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
if platform == 'posix':
    iPrefix = ''
iTubras = iPrefix + envTubras + 'include'
iBullet = iPrefix + envTubras + depsDir + 'bullet/src'
iOIS = iPrefix + envTubras + depsDir + 'ois/includes'
iIrrlicht = iPrefix + envTubras + depsDir + 'irrlicht/include'
iIrrlichtDev = iPrefix + envTubras + depsDir + 'irrlicht/source/irrlicht'
iIrrKlang = iPrefix + envTubras + depsDir + 'irrklang/include'

includePath.append(iTubras)
includePath.append(iBullet)
includePath.append(iOIS)
includePath.append(iIrrlicht)
includePath.append(iIrrlichtDev)
includePath.append(iIrrKlang)

print includePath

env = Environment(CPPPATH = includePath)

#
# setup output library based on build type
#
env.Append(TubrasLibrary = '../libs/release/Tubras')

#
# setup compiler flags based on platform type
#
ccFlags = ''

if platform == 'win32':
    ccFlags = ' -DWIN32 /EHsc'
elif platform == 'posix':
    ccFlags = ''

env.Append(CCFLAGS = ccFlags)

Export('env')
env.SConscript('src/SConscript')



