import os, sys

#
# setup include paths
#
path = []
includePath = []
try:
    envTubras = os.environ['ITUBRAS']
    if envTubras[len(envTubras)-1] != '/':
        envTubras += '/'
except:
    envTubras = './'

iTubras = envTubras + 'include'
iBullet = envTubras + 'deps/bullet/src'
iOIS = envTubras + 'deps/ois/includes'
iIrrlicht = envTubras + 'deps/irrlicht/include'
iIrrlichtDev = envTubras + 'deps/irrlicht/source/irrlicht'
iIrrKlang = envTubras + 'deps/irrklang/include'

includePath.append(iTubras)
includePath.append(iBullet)
includePath.append(iOIS)
includePath.append(iIrrlicht)
includePath.append(iIrrlichtDev)
includePath.append(iIrrKlang)
env = Environment(CPPPATH = includePath)

#
# setup output library based on build type
#
env.Append(TubrasLibrary = '../libs/release/Tubras')

#
# setup compiler flags based on platform type
#
ccFlags = ''
if sys.platform == 'win32':
    ccFlags = ' -DWIN32 /EHsc'

env.Append(CCFLAGS = ccFlags)

Export('env')
env.SConscript('src/SConscript')
