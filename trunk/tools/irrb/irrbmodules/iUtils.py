#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2009 Keith Murray -- <pc0der at gmail dot com>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
#-----------------------------------------------------------------------------
import Blender, os, sys, iGUI, iConfig
from Blender.Mathutils import *
from struct import pack

iversion = '0.3'

_logFile = None

defStandardAttributes = iConfig.StandardAttributes
defMaterialAttributes = iConfig.MaterialAttributes

# Attributes in UserConfig module (UserConfig.py) overrides iConfig if it exists 
try:
    import UserConfig
    defStandardAttributes = UserConfig.StandardAttributes
    defMaterialAttributes = UserConfig.MaterialAttributes
except:
    pass




#-----------------------------------------------------------------------------
#                               M A K E _ I D 2
#-----------------------------------------------------------------------------
lilEndian = pack('<h',1) == pack('=h',1)
def MAKE_ID2(c,d):
    if lilEndian:
        return (ord(d) << 8) | ord(c)
    else:
        return (ord(c) << 8) | ord(d)
    
# Blender block type ID's from database 
ID_SCE		= MAKE_ID2('S', 'C')
ID_LI		= MAKE_ID2('L', 'I')
ID_OB		= MAKE_ID2('O', 'B')
ID_ME		= MAKE_ID2('M', 'E')
ID_CU		= MAKE_ID2('C', 'U')
ID_MB		= MAKE_ID2('M', 'B')
ID_MA		= MAKE_ID2('M', 'A')
ID_TE		= MAKE_ID2('T', 'E')
ID_IM		= MAKE_ID2('I', 'M')
ID_IK		= MAKE_ID2('I', 'K')
ID_WV		= MAKE_ID2('W', 'V')
ID_LT		= MAKE_ID2('L', 'T')
ID_SE		= MAKE_ID2('S', 'E')
ID_LF		= MAKE_ID2('L', 'F')
ID_LA		= MAKE_ID2('L', 'A')
ID_CA		= MAKE_ID2('C', 'A')
ID_IP		= MAKE_ID2('I', 'P')
ID_KE		= MAKE_ID2('K', 'E')
ID_WO		= MAKE_ID2('W', 'O')
ID_SCR		= MAKE_ID2('S', 'R')
ID_VF		= MAKE_ID2('V', 'F')
ID_TXT		= MAKE_ID2('T', 'X')
ID_SO		= MAKE_ID2('S', 'O')
ID_GR		= MAKE_ID2('G', 'R')
ID_ID		= MAKE_ID2('I', 'D')
ID_AR		= MAKE_ID2('A', 'R')
ID_AC		= MAKE_ID2('A', 'C')
ID_SCRIPT	= MAKE_ID2('P', 'Y')
ID_NT		= MAKE_ID2('N', 'T')
ID_BR		= MAKE_ID2('B', 'R')
ID_PA		= MAKE_ID2('P', 'A')


#-----------------------------------------------------------------------------
#                             S t d A t t r i b u t es
#-----------------------------------------------------------------------------
class  StdAttributes:
    def __init__(self):
        self.attributes = {}
        self.attributes['Id'] = -1
        self.attributes['AutomaticCulling'] = 'frustum_box'
        self.attributes['Visible'] = 1
        self.attributes['DebugDataVisible'] = 0
        self.attributes['IsDebugObject'] = 0
        self.attributes['ReadOnlyMaterials'] = 0

    def inheritFromObject(self, bObject):
        dataBlock = bObject.getData(False, True)

        # update from datablock if exists
        if ('irrb' in dataBlock.properties and
            'stdAttributes' in dataBlock.properties['irrb']):
            props = dataBlock.properties['irrb']['stdAttributes']
            self._updateFromIDProperties(props)

        # update from object if exists
        if ('irrb' in bObject.properties and
            'stdAttributes' in bObject.properties['irrb']):
            props = bObject.properties['irrb']['stdAttributes']
            self._updateFromIDProperties(props)

    def _updateFromIDProperties(self, props):
        for k,v in props.iteritems():
            self.attributes[k] = v        

                

#-----------------------------------------------------------------------------
#                           s e t I D P r o p e r t i e s
#-----------------------------------------------------------------------------
def setIDProperties():
    #
    # update selected objects in the current scene
    #
    gScene = Blender.Scene.GetCurrent()
    for object in gScene.objects:
        if not object.sel:
            continue

        otype = object.type

        if not 'irrb' in object.properties:
            object.properties['irrb'] = {'inodetype':'default',
                    'stdAttributes':defStandardAttributes,
                    'userAttributes':{},
                    'materials':{}
                    }

            if otype == 'Mesh':
                omaterials = object.getMaterials()
                print 'len(omaterials)', len(omaterials)

                # add to the object level
                for mat in object.getMaterials():
                    if not mat.name in object.properties['irrb']['materials']:
                        object.properties['irrb']['materials'][mat.name] = defMaterialAttributes

        dataBlock = object.getData(False, True)
        if not 'irrb' in dataBlock.properties:
            dataBlock.properties['irrb'] = {'inodetype':'default',
                    'stdAttributes':defStandardAttributes,
                    'userAttributes':{},
                    'materials':{}
                    }
            
            if otype == 'Mesh' and not 'irrb' in dataBlock.properties:
                # add to the mesh datablock level
                for mat in mesh.materials:
                    if (mat != None and not mat.name in
                        dataBlock.properties['irrb']['materials']):
                        dataBlock.properties['irrb']['materials'][mat.nam] = defMaterialAttributes


#-----------------------------------------------------------------------------
#                               o p e n L o g
#-----------------------------------------------------------------------------
def openLog(fileName):
    global _logFile
    if Blender.sys.exists(fileName):
        os.unlink(fileName)
    _logFile = open(fileName,'w')
    #print 'irrb - unable to open logfile:',fileName
    #print 'exception:',sys.exc_info()[0]

    return False

#-----------------------------------------------------------------------------
#                              c l o s e L o g
#-----------------------------------------------------------------------------
def closeLog():
    global _logFile
    if _logFile != None:
        _logFile.close()

#-----------------------------------------------------------------------------
#                              w r i t e L o g
#-----------------------------------------------------------------------------
def writeLog(msg):
    data = msg + '\n'
    if _logFile != None:
        _logFile.write(data)

#-----------------------------------------------------------------------------
#                                d e b u g
#-----------------------------------------------------------------------------
def debug(msg):
    writeLog(msg)

#-----------------------------------------------------------------------------
#                                d e b u g
#-----------------------------------------------------------------------------
def addWarning(msg):    
    writeLog(msg)
    iGUI.addWarning(msg)

#-----------------------------------------------------------------------------
#                            c o l o u r 2 s t r
#-----------------------------------------------------------------------------
def colour2str(value):
    rval = '%.8x' % value
    return rval

#-----------------------------------------------------------------------------
#                            r g b 2 S C o l o r
#-----------------------------------------------------------------------------
def rgb2SColor(value):
    r = int(value[0] * 255.0)
    g = int(value[1] * 255.0)
    b = int(value[2] * 255.0)

    SColor = 0xFF000000 | (r << 16) | (g << 8) | b
    return SColor

#-----------------------------------------------------------------------------
#                            r g b 2 D e l S t r
#-----------------------------------------------------------------------------
def rgb2DelStr(value):
    r = int(value[0] * 255.0)
    g = int(value[1] * 255.0)
    b = int(value[2] * 255.0)
    return '%d %d %d 255' % (r,g,b)

#-----------------------------------------------------------------------------
#                            d e l 2 S C o l o r
#-----------------------------------------------------------------------------
def del2SColor(value):
    vals = value.split()
    r,g,b,a = 0,0,0,255
    try:
        r = int(vals[0])
        g = int(vals[1])
        b = int(vals[2])
        a = int(vals[3])
    except:
        pass

    value = (a << 24) | (r << 16) | (g << 8) | b
    return '%.8x' % value

#-----------------------------------------------------------------------------
#                              r g b 2 s t r
#-----------------------------------------------------------------------------
def rgb2str(value):
    ival = rgb2SColor(value)
    return colour2str(ival)

#-----------------------------------------------------------------------------
#                             f l o a t 2 s t r 
#-----------------------------------------------------------------------------
def float2str(value):
    rval = '%.6f' % value
    return rval

#-----------------------------------------------------------------------------
#                               i n t 2 s t r
#-----------------------------------------------------------------------------
def int2str(value):
    rval = str(value)
    return rval

#-----------------------------------------------------------------------------
#                              b o o l 2 s t r
#-----------------------------------------------------------------------------
def bool2str(value):
    rval = 'false'
    if value:
        rval = 'true'
    return rval

#-----------------------------------------------------------------------------
#                           d a t e t i m e 2 s t r
#-----------------------------------------------------------------------------
def datetime2str(value):
    rval = 'mm/dd/yyyy hh:nn'
    yyyy = value[0]
    mm = value[1]
    dd = value[2]
    hh = value[3]
    nn = value[4]
    rval = '%.2d/%.2d/%d %.2d:%.2d' % (mm,dd,yyyy,hh,nn)
    return rval

#-----------------------------------------------------------------------------
#                             g e t v e r s i o n
#-----------------------------------------------------------------------------
def getversion():
    return 'v' + iversion

#-----------------------------------------------------------------------------
#                             g e t I n d e n t
#-----------------------------------------------------------------------------
def getIndent(level,extra=0):
    indent = ''
    for i in range(level+1):
        indent += '   '
    if extra > 0:
        for i in range(extra):
            indent += ' '
    return indent

#-----------------------------------------------------------------------------
#                            f l a t t e n P a t h
#-----------------------------------------------------------------------------
def flattenPath(path):
    out = ''
    path = path.strip()
    for c in path:
        if c == '/' or c == '\\':
            out = out + '/'
        else:
            out = out + c
    return out

#-----------------------------------------------------------------------------
#                            f i l t e r P a t h
#-----------------------------------------------------------------------------
def filterPath(path):
    out = flattenPath(path);
    if out[len(out)-1] != '/':
        out = out + '/'
    return out

#-----------------------------------------------------------------------------
#                          f i l t e r D i r P a t h
#-----------------------------------------------------------------------------
def filterDirPath(path):

    out = ''
    path = path.strip()

    for c in path:
        if c == '/' or c == '\\':
            out = out + os.sep
        else:
            out = out + c
    if out[len(out)-1] != os.sep:
        out = out + os.sep
        
    return out

#-----------------------------------------------------------------------------
#                           g e t P r o p e r t y
#-----------------------------------------------------------------------------
def getProperty(pname,plist,caseSensitive=False):
    if 'irrb' not in plist:
        return None

    group = plist['irrb']
    if type(group) != Blender.Types.IDGroupType:
        return None

    for name in group:
        if caseSensitive:
            if name == pname:
                return group[name]
        else:
            if name.lower() == pname.lower():
                return group[name]

    return None

#-----------------------------------------------------------------------------
#                              r e l p a t h
#-----------------------------------------------------------------------------
#  from python 2.6 also added to blender.sys 12/03 - 2.48a+ 
def relpath(path, start):

    if not path:
        raise ValueError("no path specified")


    # convert driver letter(s) to lower case...
    if sys.platform == 'win32':
        if start[1] == ':':
            start = start[0].lower() + start[1:]

        if path[1] == ':':
            path = path[0].lower() + path[1:]

    start_list = os.path.abspath(start).split(os.sep)
    path_list = os.path.abspath(path).split(os.sep)

    # Work out how much of the filepath is shared by start and path.
    i = len(os.path.commonprefix([start_list, path_list]))

    rel_list = [os.pardir] * (len(start_list)-i) + path_list[i:]
    if not rel_list:
        return curdir
    return os.path.join(*rel_list)


#-----------------------------------------------------------------------------
#                             b 2 i V e c t o r
#-----------------------------------------------------------------------------
# flip y <-> z
def b2iVector(bVector):
    return Vector(bVector.x, bVector.z, bVector.y)
    
#-----------------------------------------------------------------------------
#                             b 2 i P o s i t i o n
#-----------------------------------------------------------------------------
# flip y <-> z
def b2iPosition(mat, bNode):
    bVector = mat.translationPart()
    if bNode.parent != None and bNode.parent.type == 'Camera':
        crot = RotationMatrix(90, 3, 'x') 	
        bVector = VecMultMat(bVector,crot)
        
    return Vector(bVector.x, bVector.z, bVector.y)

#-----------------------------------------------------------------------------
#                            b 2 i R o t a t i o n
#-----------------------------------------------------------------------------
def b2iRotation(mat, bNode):

    x = 'x'
    y = 'z'
    z = 'y'
    bEuler = mat.toEuler()
    crot = Matrix().identity()

    if bNode.parent != None and bNode.parent.type == 'Camera':
        crot = RotationMatrix(-90, 4, 'x')
    
    if bNode.type == 'Camera' or bNode.type == 'Lamp':
        crot = RotationMatrix(90, 4, 'x')
        bEuler.z = -bEuler.z
        y = 'y'
        z = 'z'

    xrot = RotationMatrix(-bEuler.x, 4, x)
    yrot = RotationMatrix(-bEuler.y, 4, y)
    zrot = RotationMatrix(-bEuler.z, 4, z)
    rot = xrot * yrot * zrot * crot
    return rot.toEuler()

