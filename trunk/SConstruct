import os, sys
platform = Environment()['PLATFORM']
#
# dependencies
#

deps = {\
    'bullet':{'deps/bullet':'http://downloads.sourceforge.net/bullet/bullet-2.66A.zip'},\
    'irrlicht':{'deps/irrlicht':'http://prdownloads.sourceforge.net/irrlicht/irrlicht-1.4.zip'}
    }

def checkDeps():
    print 'checkDeps()'
    for lib,info in deps.items():
        print lib,info
    return False

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
iBullet = iPrefix + envTubras + 'deps/bullet/src'
iOIS = iPrefix + envTubras + 'deps/ois/includes'
iIrrlicht = iPrefix + envTubras + 'deps/irrlicht/include'
iIrrlichtDev = iPrefix + envTubras + 'deps/irrlicht/source/irrlicht'
iIrrKlang = iPrefix + envTubras + 'deps/irrklang/include'

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



