#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
import bpy
import os
import mathutils
import math
import sys
from struct import pack
import time
import subprocess
import shutil
import math
import copy
import traceback
import configparser
from bpy.props import *

bl_addon_info = {
    'name': 'I/O: Irrlicht Scene/Mesh Exporter',
    'author': 'Keith Murray (pc0de)',
    'version': '0.6',
    'blender': '2.5.3',
    'location': 'File > Export > Irrlicht ',
    'url': 'http://code.google.com/p/tubras/wiki/irrb',
    'category': 'Export'}

__author__ = ['Keith Murray (pc0de)']
__version__ = '0.6'
__url__ = ['Irrlicht, http://irrlicht.sourceforge.net/',
    'irrb, http://code.google.com/p/tubras/wiki/irrb']
__bpydoc__ = """\
Exports selected objects to Irrlicht.

Read the script manual for further information.
"""

gHavePlatform = False
try:
    import platform
    gHavePlatform = True
except:
    pass

gVersionList = (0, '1.6', '1.7')
gIrrlichtVersion = 2
sVersionList = "1.6 %x1|1.7 %x2"
gMeshCvtPath = None
gWalkTestPath = None
gUserConfig = os.path.expanduser('~') + os.sep + '.irrb'
gConfig = None

gWTCmdLine = ''
gWTDirectory = ''


# configurable UI properties
gPropExportScene = True
gPropExportSelected = False
gPropExportLights = True
gPropExportCameras = True
gPropExportAnimations = True
gPropExportPhysics = False
gPropExportBinary = False
gPropUseBlenderMaterials = False
gPropDebug = True
gPropWalktest = True

gOutDirectory = ''

iversion = '0.6'

_logFile = None

_StartMessages = []

# node types
NT_DEFAULT = 0
NT_BILLBOARD = 1
NT_SKYBOX = 2

# property material types
EMT_SOLID = 0
EMT_SOLID_2_LAYER = 1
EMT_LIGHTMAP = 2
EMT_LIGHTMAP_ADD = 3
EMT_LIGHTMAP_M2 = 4
EMT_LIGHTMAP_M4 = 5
EMT_LIGHTMAP_LIGHTING = 6
EMT_LIGHTMAP_LIGHTING_M2 = 7
EMT_LIGHTMAP_LIGHTING_M4 = 8
EMT_DETAIL_MAP = 9
EMT_SPHERE_MAP = 10
EMT_REFLECTION_2_LAYER = 11
EMT_TRANSPARENT_ADD_COLOR = 12
EMT_TRANSPARENT_ALPHA_CHANNEL = 13
EMT_TRANSPARENT_ALPHA_CHANNEL_REF = 14
EMT_TRANSPARENT_VERTEX_ALPHA = 15
EMT_TRANSPARENT_REFLECTION_2_LAYER = 16
EMT_NORMAL_MAP_SOLID = 17
EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR = 18
EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA = 19
EMT_PARALLAX_MAP_SOLID = 20
EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR = 21
EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA = 22
EMT_ONETEXTURE_BLEND = 23
EMT_CUSTOM = 24

RAD2DEG = 180.0 / math.pi
DEG2RAD = math.pi / 180.0
EVT_STANDARD = 0
EVT_2TCOORDS = 1
EVT_TANGENTS = 2

# (material name, expected texture count)
irrMaterialTypes=(
    ('solid', 1, EVT_STANDARD),
    ('solid_2layer', 2, EVT_2TCOORDS),
    ('lightmap', 2, EVT_2TCOORDS),
    ('lightmap_add', 2, EVT_2TCOORDS),
    ('lightmap_m2', 2, EVT_2TCOORDS),
    ('lightmap_m4', 2, EVT_2TCOORDS),
    ('lightmap_light', 2, EVT_2TCOORDS),
    ('lightmap_light_m2', 2, EVT_2TCOORDS),
    ('lightmap_light_m4', 2, EVT_2TCOORDS),
    ('detail_map', 2, EVT_2TCOORDS),
    ('sphere_map', 1, EVT_STANDARD),
    ('reflection_2layer', 2, EVT_2TCOORDS),
    ('trans_add', 1, EVT_STANDARD),
    ('trans_alphach', 1, EVT_STANDARD),
    ('trans_alphach_ref', EVT_STANDARD),
    ('trans_vertex_alpha', 1, EVT_STANDARD),
    ('trans_reflection_2layer', 2, EVT_2TCOORDS),
    ('normalmap_solid', 2, EVT_TANGENTS),
    ('normalmap_trans_add', 2, EVT_TANGENTS),
    ('normalmap_trans_vertexalpha', 2, EVT_TANGENTS),
    ('parallaxmap_solid', 2, EVT_TANGENTS),
    ('parallaxmap_trans_add', 2, EVT_TANGENTS),
    ('parallaxmap_trans_vertexalpha', 2, EVT_TANGENTS),
    ('onetexture_blend', 1, EVT_STANDARD)
    )

class iConfig:
    #---------------------------------------------------------------------------
    # E_COLOR_PLANE - 'ColorMask' enums
    #---------------------------------------------------------------------------
    # No color enabled
    ECP_NONE = 0
    # Alpha enabled
    ECP_ALPHA = 1
    # Red enabled
    ECP_RED = 2
    # Green enabled
    ECP_GREEN = 4
    # Blue enabled
    ECP_BLUE = 8
    # All colors, no alpha
    ECP_RGB = 14
    # All planes enabled
    ECP_ALL = 15

    #---------------------------------------------------------------------------
    # E_ANTI_ALIASING_MODE - 'AnitAliasing' enums
    #---------------------------------------------------------------------------
    # Use to turn off anti-aliasing for this material
    EAAM_OFF = 0
    # Default anti-aliasing mode
    EAAM_SIMPLE = 1
    # High-quality anti-aliasing, not always supported, automatically enables SIMPLE mode
    EAAM_QUALITY = 3
    # Line smoothing
    EAAM_LINE_SMOOTH = 4
    # point smoothing, often in software and slow, only with OpenGL
    EAAM_POINT_SMOOTH = 8
    # All typical anti-alias and smooth modes
    EAAM_FULL_BASIC = 15
    # Enhanced anti-aliasing for transparent materials
    # Usually used with EMT_TRANSPARENT_ALPHA_REF and multisampling.
    EAAM_ALPHA_TO_COVERAGE = 16

    #---------------------------------------------------------------------------
    # E_FOG_TYPE - Fog type enumbs
    #---------------------------------------------------------------------------
    EFT_FOG_EXP = 0
    EFT_FOG_LINEAR = 1
    EFT_FOG_EXP2 = 0

    # absolute or relative to out/working directory
    ScriptOptions = {'meshOutDir': 'mdl',
        'texOutDir': 'tex',
        'sceneOutDir': '.',
        'copyExternalImages': True}

    StandardAttributes = {'Id':-1,
        'AutomaticCulling':1,
        'Visible':1,
        'DebugDataVisible':0,
        'IsDebugObject':0,
        'ReadOnlyMaterials':0}

    SceneAttributes = {'Exporter': 'irrb',
        'Exporter.Version': 'x.x',
        'OccludesLight': 0
        }

    CameraAttributes = {'Fovy': 0.857556,
        'Aspect': 1.25,
        'ZNear': 0.1,
        'ZFar': 100.0}

    LightAttributes = {'LightType':'Point',
        'AmbientColor':'255 255 255 255',
        'SpecularColor':'255 255 255 255',
        'Attenuation':10.0,
        'Radius':50.0,
        'CastShadows':1}

    MeshAttributes = {}
    # iwalktest uses
    #{'HWHint':'static',
    # 'HWType':'vertexindex'}

    BillboardAttributes = {'Shade_Top': '255 255 255 255',
        'Shade_Down': '255 255 255 255'}

    # note that 'bool' values are 'int' values - 1 or 0.
    # version notes:
    #      1.7 separates TextureWrap mode into U & V. 1.7 SDK still honors (precedence)
    #          'TextureWrap'. We'll remove it after 1.7 is released.
    MaterialAttributes = {'Type':'solid',
        'AmbientColor':'255 255 255 255', # rgba
        'DiffuseColor':'255 255 255 255',
        'EmissiveColor':'0 0 0 255',
        'SpecularColor':'255 255 255 255',
        'Shininess':0.0,
        'MaterialTypeParam':0.0,
        'MaterialTypeParam2':0.0,
        'Thickness':1.0,
        'WireFrame':0,
        'PointCloud':0,
        'Lighting':0,
        'GouraudShading':1,
        'ZWriteEnable':1,
        'BackfaceCulling':1,
        'FrontfaceCulling':0,
        'FogEnable':1,
        'NormalizeNormals':0,
        'ZBuffer':1,
        'AntiAliasing':EAAM_SIMPLE | EAAM_LINE_SMOOTH,
        'ColorMask':ECP_ALL,
        'Layer1': {'Texture':'',
            'TextureWrap':'texture_clamp_repeat', # <= 1.6
            'TextureWrapU':'texture_clamp_repeat', # 1.7
            'TextureWrapV':'texture_clamp_repeat', # 1.7
            'BilinearFilter':1,
            'TrilinearFilter':0,
            'AnisotropicFilter':0,
            'LODBias':0},
        'Layer2': {'Texture':'',
            'TextureWrap':'texture_clamp_repeat',
            'TextureWrapU':'texture_clamp_repeat',
            'TextureWrapV':'texture_clamp_repeat',
            'BilinearFilter':1,
            'TrilinearFilter':0,
            'AnisotropicFilter':0,
            'LODBias':0},
        'Layer3': {'Texture':'',
            'TextureWrap':'texture_clamp_repeat',
            'TextureWrapU':'texture_clamp_repeat',
            'TextureWrapV':'texture_clamp_repeat',
            'BilinearFilter':1,
            'TrilinearFilter':0,
            'AnisotropicFilter':0,
            'LODBias':0},
        'Layer4': {'Texture':'',
            'TextureWrap':'texture_clamp_repeat',
            'TextureWrapU':'texture_clamp_repeat',
            'TextureWrapV':'texture_clamp_repeat',
            'BilinearFilter':1,
            'TrilinearFilter':0,
            'AnisotropicFilter':0,
            'LODBias':0}}

defScriptOptions = iConfig.ScriptOptions
defStandardAttributes = iConfig.StandardAttributes
defSceneAttributes = iConfig.SceneAttributes
defMeshAttributes = iConfig.MeshAttributes
defCameraAttributes = iConfig.CameraAttributes
defLightAttributes = iConfig.LightAttributes
defMaterialAttributes = iConfig.MaterialAttributes

# Attributes in UserConfig module (UserConfig.py) overrides iConfig if it exists
try:
    import UserConfig
    reload(UserConfig)

    addStartMessage('UserConfig exists.')

    if hasattr(UserConfig, 'ScriptOptions'):
        _updateDict(defScriptOptions, UserConfig.ScriptOptions)
        addStartMessage('ScriptOptions overridden.')

    if hasattr(UserConfig, 'StandardAttributes'):
        _updateDict(defStandardAttributes, UserConfig.StandardAttributes)
        addStartMessage('StandardAttributes overridden.')

    if hasattr(UserConfig, 'SceneAttributes'):
        _updateDict(defSceneAttributes, UserConfig.SceneAttributes)
        addStartMessage('SceneAttributes overridden.')

    if hasattr(UserConfig, 'MeshAttributes'):
        _updateDict(defMeshAttributes, UserConfig.MeshAttributes)
        addStartMessage('MeshAttributes overridden.')

    if hasattr(UserConfig, 'CameraAttributes'):
        _updateDict(defCameraAttributes, UserConfig.CameraAttributes)
        addStartMessage('CameraAttributes overridden.')

    if hasattr(UserConfig, 'LightAttributes'):
        _updateDict(defLightAttributes, UserConfig.LightAttributes)
        addStartMessage('LightAttributes overridden.')

    if hasattr(UserConfig, 'MaterialAttributes'):
        _updateDict(defMaterialAttributes, UserConfig.MaterialAttributes)
        addStartMessage('MaterialAttributes overridden.')
except:
    pass

defSceneAttributes['Exporter.Version'] = iversion

#-----------------------------------------------------------------------------
#                            i S t d A t t r i b u t es
#-----------------------------------------------------------------------------
class  iStdAttributes:
    def __init__(self):
        self.attributes = {}
        self.attributes['Id'] = -1
        self.attributes['AutomaticCulling'] = 'frustum_box'
        self.attributes['Visible'] = 1
        self.attributes['DebugDataVisible'] = 0
        self.attributes['IsDebugObject'] = 0
        self.attributes['ReadOnlyMaterials'] = 0

    def inheritFromObject(self, bObject):
        dataBlock = bObject.data

        # update from datablock if exists
        if (dataBlock != None and
            'irrb' in dataBlock and
            'stdAttributes' in dataBlock['irrb']):
            props = dataBlock['irrb']['stdAttributes']
            self._updateFromIDProperties(props)

        # update from object if exists
        if ('irrb' in bObject and
            'stdAttributes' in bObject['irrb']):
            props = bObject['irrb']['stdAttributes']
            self._updateFromIDProperties(props)

    def _updateFromIDProperties(self, props):
        for k,v in props.iteritems():
            self.attributes[k] = v


class IGUIDebug:

    def __init__(self):
        self.canceled = False


    def setStatus(self, status):
        print('GUI.setStatus()', status)

    def updateStatus(self, status):
        print('GUI.updateStatus()', status)

    def isExportCanceled(self):
        #print('GUI.isExportCanceled()')
        return self.canceled


class IGUIPanel(IGUIDebug):

    def __init__(self):
        pass


class IGUIFilePanel(IGUIDebug):

    def __init__(self):
        pass


def getGUIInterface(itype):
    if type == 'debug':
        return IGUIDebug()
    elif type == 'panel':
        return IGUIPanel()
    elif type == 'filepanel':
        return IGUIFilePanel()
    else:
        return IGUIDebug()

#-----------------------------------------------------------------------------
#                         _ l o a d C o n f i g
#-----------------------------------------------------------------------------
def _loadConfig():
    global gConfig, gOutDirectory, gPropExportScene, gPropExportSelected
    global gPropExportLights, gPropExportCameras, gPropExportPhysics
    global gPropExportBinary, gPropDebug, gPropWalktest, gExportAnimations
    global gPropUseBlenderMaterials

    gConfig = configparser.RawConfigParser()
    gConfig.read(gUserConfig)

    if not gConfig.has_section('options'):
        gConfig.add_section('options')

    try:
        gOutDirectory = gConfig.get('options', 'OutDirectory')
    except:
        pass

    try:
        gPropExportScene = gConfig.getboolean('options', 'ExportScene')
    except:
        pass

    try:
        gPropExportSelected = gConfig.getboolean('options', 'ExportSelected')
    except:
        pass

    try:
        gPropExportLights = gConfig.getboolean('options', 'ExportLights')
    except:
        pass

    try:
        gPropExportCameras = gConfig.getboolean('options', 'ExportCameras')
    except:
        pass

    try:
        gPropExportAnimations = gConfig.getboolean('options', 'ExportAnimations')
    except:
        pass

    try:
        gPropExportPhysics = gConfig.getboolean('options', 'ExportPhysics')
    except:
        pass

    try:
        gPropExportBinary = gConfig.getboolean('options', 'ExportBinary')
    except:
        pass

    try:
        gPropUseBlenderMaterials = gConfig.getboolean('options', 'UseBlenderMaterials')
    except:
        pass

    try:
        gPropDebug = gConfig.getboolean('options', 'Debug')
    except:
        pass

    try:
        gPropWalktest = gConfig.getboolean('options', 'Walktest')
    except:
        pass

#-----------------------------------------------------------------------------
#                         _ s a v e C o n f i g
#-----------------------------------------------------------------------------
def _saveConfig():

    if not gConfig.has_section('options'):
        gConfig.add_section('options')

    gConfig.set('options', 'OutDirectory', gOutDirectory)
    gConfig.set('options', 'ExportScene', gPropExportScene)
    gConfig.set('options', 'ExportSelected', gPropExportSelected)
    gConfig.set('options', 'ExportLights', gPropExportLights)
    gConfig.set('options', 'ExportCameras', gPropExportCameras)
    gConfig.set('options', 'ExportAnimations', gPropExportAnimations)
    gConfig.set('options', 'ExportPhysics', gPropExportPhysics)
    gConfig.set('options', 'ExportBinary', gPropExportBinary)
    gConfig.set('options', 'Debug', gPropDebug)
    gConfig.set('options', 'Walktest', gPropWalktest)
    gConfig.set('options', 'UseBlenderMaterials', gPropUseBlenderMaterials)
    
    fp = open(gUserConfig, 'w')
    gConfig.write(fp)
    fp.close()

#-----------------------------------------------------------------------------
#                         g e t I r r M a t e r i a l
#-----------------------------------------------------------------------------
def getIrrMaterial(name):
    try:
        lname = name.lower()
        for info in irrMaterialTypes:
            if lname == info[0]:
                return info
    except:
        pass

    return None

#-----------------------------------------------------------------------------
#                               w r i t e T G A
#-----------------------------------------------------------------------------
def writeTGA(bImage, outFilename, RLE=True, callBack=None):
    file = open(outFilename, 'wb')

    width, height = bImage.size
    bpp = bImage.depth

    if bpp < 24:
        file.close()
        print('writeTGA only handles 24 or 32 bit images')
        return 1

    header = []
    for i in range(18):
        header.append(chr(0))
    if RLE:
        header[2] = chr(10)     # rle bgra image
    else:
        header[2] = chr(2)      # bgra image
    header[13] = chr(width / 256)
    header[12] = chr(width % 256)
    header[15] = chr(height / 256)
    header[14] = chr(height % 256)
    header[16] = chr(bpp)       # 24 or 32 bpp
    if bpp == 32:
        header[17] = chr(3)    # 00vhaaaa - useful alpha data

    #
    # write header
    #
    for byte in header:
        file.write(byte)

    #
    # write data
    #
    for y in range(height):
        if (callBack != None) and ((y % 10) == 0):
            callBack(y)
        runLength = 1
        first = True
        lastPixel = ''
        for x in range(width):
            p = bImage.getPixelI(x, y)   # rgba
            pixel = chr(p[2]) + chr(p[1]) + chr(p[0])
            if bpp == 32:
                pixel += chr(p[3])

            if not RLE:
                file.write(pixel)
            else:
                if first:
                    lastPixel = pixel
                    first = False
                else:
                    if (pixel != lastPixel) or (runLength == 128):
                        packet = chr(128 + runLength-1)
                        rleData = packet + lastPixel
                        file.write(rleData)
                        lastPixel = pixel
                        runLength = 1
                    else:
                        runLength += 1
        #
        # write last run
        #
        if RLE:
            packet = chr(128 + runLength-1)
            rleData = packet + lastPixel
            file.write(rleData)

    file.close()
    return 0

#-----------------------------------------------------------------------------
#                         a d d S t a r t M e s s a g e
#-----------------------------------------------------------------------------
def addStartMessage(msg):
    _StartMessages.append(msg)

#-----------------------------------------------------------------------------
#                           _ u p d a t e D i c t
#-----------------------------------------------------------------------------
def _updateDict(tdict, fdict):
    for a in fdict:
        if type(fdict[a]).__name__ == 'dict':
            _updateDict(fdict[a], tdict[a])
        else:
            tdict[a] = fdict[a]
            
#---------------------------------------------------------------------------
#             _ a c t i o n C o n t a i n s L o c R o t S c a l e
#---------------------------------------------------------------------------
def _actionContainsLocRotScale(bAction):
    for curve in bAction.fcurves:
        if curve.data_path in ('location', 'rotation', 'scale'):
            return True

    return False

#---------------------------------------------------------------------------
#                       _ h a s N o d e A n i m a t i o n s
#---------------------------------------------------------------------------
def _hasNodeAnimations(bObject):
    if not bObject.animation_data:
        return False

    # check the selected action if any
    if bObject.animation_data.action:
        if _actionContainsLocRotScale(bObject.animation_data.action):
            return True
        
    # check NLA Tracks
    if bObject.animation_data.nla_tracks:
        for track in bObject.animation_data.nla_tracks:
            for strip in track.strips:
                if _actionContainsLocRotScale(strip.action):
                    return True

    return False

#-----------------------------------------------------------------------------
#                           s e t I D P r o p e r t i e s
#-----------------------------------------------------------------------------
def setIDProperties():
    #
    # update selected objects in the current scene
    #
    editMode = Blender.Window.EditMode()
    if editMode:
        Blender.Window.EditMode(0)

    status = ['Updating irrb ID Properties For Selected Objects...']
    iGUI.setStatus(status)

    gScene = Blender.Scene.GetCurrent()

    sceneUpdated = False

    if not 'irrb' in gScene.properties:
        gScene.properties['irrb'] = {'stdAttributes' : defStandardAttributes,
        'userAttributes': defSceneAttributes}
        sceneUpdated = True

    sSelectedCount = 0
    sObjectCount = 0
    sDataBlockCount = 0
    for object in gScene.objects:
        if not object.sel:
            continue

        otype = object.type
        sSelectedCount += 1

        if not 'irrb' in object.properties:
            object.properties['irrb'] = {'inodetype':'default',
                    'stdAttributes':defStandardAttributes,
                    'userAttributes':{},
                    }
            if otype == 'Camera':
                object.properties['irrb']['stdAttributes'].update(defCameraAttributes)
            elif otype == 'Lamp':
                object.properties['irrb']['stdAttributes'].update(defLightAttributes)
            elif otype == 'Mesh':
                object.properties['irrb']['userAttributes'].update(defMeshAttributes)


            sObjectCount += 1

        if otype == 'Mesh':   # data block for Mesh geometry only.
            dataBlock = object.getData(False, True)
            if not 'irrb' in dataBlock.properties:
                dataBlock.properties['irrb'] = {'inodetype':'default',
                        'stdAttributes':defStandardAttributes,
                        'userAttributes':defMeshAttributes,
                        }
                sDataBlockCount += 1

    #
    # Update materials
    #
    sMaterialCount = 0
    materials = Blender.Material.Get()
    for material in materials:
        if not 'irrb' in material.properties:
            material.properties['irrb'] = defMaterialAttributes
            sMaterialCount += 1

    status = ['Updated irrb ID Properties For Selected Objects.']
    status.append('{0} Object(s) Selected'.format(sSelectedCount))
    status.append('{0} Object(s) Updated'.format(sObjectCount))
    status.append('{0} DataBlock(s) Updated'.format(sDataBlockCount))
    status.append('{0} Material(s) Updated'.format(sMaterialCount))
    if sceneUpdated:
        status.append('Scene Updated')

    iGUI.setStatus(status)
    if editMode:
        Blender.Window.EditMode(1)
    Blender.Window.Redraw(Blender.Window.Types.SCRIPT)

#-----------------------------------------------------------------------------
#                               o p e n L o g
#-----------------------------------------------------------------------------
def openLog(fileName):
    global _logFile
    if os.path.exists(fileName):
        os.unlink(fileName)
    _logFile = open(fileName,'w')

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

#-----------------------------------------------------------------------------
#                            c o l o u r 2 s t r
#-----------------------------------------------------------------------------
def colour2str(value):
    return '{0:08x}'.format(value)

#-----------------------------------------------------------------------------
#                       d u m p S t a r t M e s s a g e s
#-----------------------------------------------------------------------------
def dumpStartMessages():
    if len(_StartMessages) == 0:
        return

    debug('\n[start messages]')
    for msg in _StartMessages:
        debug(msg)

#-----------------------------------------------------------------------------
#                            f u z z y Z e r o
#-----------------------------------------------------------------------------
def fuzzyZero(fval):
    v = math.fabs(fval)

    if v < 0.000001:
        return True

    return False

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
#                            r g b a 2 S C o l o r
#-----------------------------------------------------------------------------
def rgba2SColor(value):
    if type(value[0]).__name__ == 'float':
        r = int(value[0] * 255.0)
        g = int(value[1] * 255.0)
        b = int(value[2] * 255.0)
        a = int(value[3] * 255.0)
    else:
        r = value[0]
        g = value[1]
        b = value[2]
        a = value[3]

    SColor = (a << 24) | (r << 16) | (g << 8) | b
    return SColor

#-----------------------------------------------------------------------------
#                            r g b 2 D e l S t r
#-----------------------------------------------------------------------------
def rgb2DelStr(value):
    r = int(value[0] * 255.0)
    g = int(value[1] * 255.0)
    b = int(value[2] * 255.0)
    return '{0} {1} {2} 255'.format(r,g,b)

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
    return '{0:08x}'.format(value)

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
    return '{0:.6f}'.format(value)

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
    rval = '{0:02d}/{1:02d}/{2} {3:02d}:{4:02d}'.format(mm,dd,yyyy,hh,nn)
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
    if path == None:
        return out
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
def getProperty(pname, bObject, caseSensitive=False):

    if 'irrb' in bObject:
        group = bObject['irrb']
        for name in group:
            if caseSensitive:
                if name == pname:
                    return group[name]
            else:
                if name.lower() == pname.lower():
                    return group[name]

    # not in object properties
    if bObject.data == None:
        return None

    if 'irrb' in bObject.data:
        group = bObject.data['irrb']
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
    return mathutils.Vector((bVector.x, bVector.z, bVector.y))

#-----------------------------------------------------------------------------
#                             b 2 i P o s i t i o n
#-----------------------------------------------------------------------------
# flip y <-> z
def b2iPosition(bNode):
    bVector = bNode.location
    if bNode.parent != None:
        # set position relative to parent for Irrlicht .irr
        bVector = bVector - bNode.parent.location

    return mathutils.Vector((bVector.x, bVector.z, bVector.y))

#-----------------------------------------------------------------------------
#                            b 2 i R o t a t i o n
#-----------------------------------------------------------------------------
def b2iRotation(bNode, toDegrees=True):

    x = 'X'
    y = 'Z'
    z = 'Y'
    bEuler = bNode.rotation_euler.copy()
    crot = mathutils.Matrix().identity()

    if bNode.parent != None and bNode.parent.type == 'CAMERA':
        crot = mathutils.Matrix.Rotation(-math.pi/2.0, 4, 'X')

    if bNode.type == 'CAMERA' or bNode.type == 'LAMP':
        crot = mathutils.Matrix.Rotation(math.pi/2.0, 4, 'X')
        bEuler.z = -bEuler.z
        y = 'Y'
        z = 'Z'

    xrot = mathutils.Matrix.Rotation(-bEuler.x, 4, x)
    yrot = mathutils.Matrix.Rotation(-bEuler.y, 4, y)
    zrot = mathutils.Matrix.Rotation(-bEuler.z, 4, z)
    rot = crot * zrot * yrot * xrot

    bEuler = rot.to_euler()
    if toDegrees:
        bEuler = mathutils.Euler((bEuler.x*RAD2DEG,
            bEuler.y*RAD2DEG, bEuler.z*RAD2DEG))

    return bEuler

#-----------------------------------------------------------------------------
#                           w r i t e U s e r D a t a
#-----------------------------------------------------------------------------
def writeUserData(file,i1,i2,bObject,writeClose=True):

    file.write(i1 + '<userData>\n')
    file.write(i2 + '<attributes>\n')
    i3 = i2 + '   '

    # extract from irrb:userAttributes namespace
    if 'irrb' in bObject and 'userAttributes' in bObject['irrb']:
        userAttributes = bObject['irrb']['userAttributes']
        keys = userAttributes.keys()
        keys.sort()
        for name in keys:
            data = userAttributes[name]
            dtype = type(data)
            stype = None
            if dtype == int:
                stype = 'int'
                svalue = str(data)
            elif dtype == str:
                stype = 'string'
                svalue = data
            elif dtype == float:
                stype = 'float'
                svalue = float2str(data)

            if name.lower().find('color') >= 0:
                stype = 'colorf'

            if stype != None:
                pout = '<{0} name="{1}" value="{2}"/>\n'.format(stype,name,svalue)
                file.write(i3 + pout)

    #
    # write game properties
    #
    try:
        gprops = bObject.game.properties
        for p in gprops:
            dtype = p.type
            name = p.name
            data = p.value

            stype = None
            svalue = ''
            if dtype == 'STRING':
                stype = 'string'
                svalue = data
            elif dtype == 'INT':
                stype = 'int'
                svalue = str(data)
            elif dtype == 'BOOL':
                stype = 'bool'
                svalue = 'false'
                if data == True:
                    svalue = 'true'
            elif dtype == 'FLOAT':
                stype = 'float'
                svalue = float2str(data)
            if stype != None:
                pout = '<{0} name="{1}" value="{2}"/>\n'.format(stype,name,svalue)
                file.write(i3 + pout)
    except:
        pass

    if writeClose:
        file.write(i2 + '</attributes>\n')
        file.write(i1 + '</userData>\n')

#-----------------------------------------------------------------------------
#                            i F i l e N a m e
#-----------------------------------------------------------------------------
class iFilename:
    def __init__(self,fullPath):
        self.fullPath = fullPath
        self.dirPath = Blender.sys.dirname(fullPath)
        self.fileName = Blender.sys.basename(fullPath)
        self.file, self.ext = Blender.sys.splitext(self.fileName)
        if self.file == 'Untitled':
            self.file += self.ext
            self.ext = ''

        self.dirParts = []
        part = ''
        for c in self.dirPath:
            if (c == '/') or (c == '\\'):
                self.dirParts.append(part)
                part = ''
            else:
                part += c

    def printDebug(self):
        print('fullPath',self.fullPath)
        print('dirPath',self.dirPath)
        print('fileName',self.fileName)
        print('file', self.file)
        print('ext',self.ext)
        print('dirParts',self.dirParts)

    def getBaseName(self):
        return self.file

    def setExtension(self,ext):
        self.ext = ext

#-----------------------------------------------------------------------------
#                        i D e f a u l t M a t e r i a l
#-----------------------------------------------------------------------------
class iDefaultMaterial:

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self,bobject,name,exporter,bmaterial):
        self.bobject = bobject
        self.bmesh = bobject.data
        self.bmaterial = bmaterial
        self.bimages = []
        self.name = name
        self.exporter = exporter
        self.useVertexColor = True
        self.vtCustom = None

        #
        # Default attributes originally defined in "iConfig.py".  May be
        # overridden in "UserConfig.py".
        #
        self.attributes = copy.deepcopy(defMaterialAttributes)

        self.attributes['FogEnable'] = 0
        if exporter.gContext.scene.world and exporter.gContext.scene.world.mist_settings.use_mist:
            self.attributes['FogEnable'] = 1

        self._updateFromMaterial(self.bmaterial)

    #-------------------------------------------------------------------------
    #                 _ u p d a t e F r o m M a t e r i a l
    #-------------------------------------------------------------------------
    # Inheritence order -> "Object" -> "Mesh DataBlock" -> "Defaults"
    # Upon entry it is expected that "self.attributes" has already been
    # set to "Defaults".
    def _updateFromMaterial(self, bmaterial):
        if bmaterial == None:
            return

        # update from material ID properties if it exists.
        if 'irrb' in bmaterial:
            props = bmaterial['irrb']
            self._updateFromIDProperties(props)
        else: # examine assigned blender material
            if bmaterial.use_shadeless:
                self.attributes['Lighting'] = 0
            else:
                self.attributes['Lighting'] = 1

            # this will have been turned on if enabled globally, so turn off
            # if explicitly set.
            if not bmaterial.use_mist:
                self.attributes['FogEnable'] = 0

    #-------------------------------------------------------------------------
    #             _ u p d a t e F r o m I D P r o p e r t i e s
    #-------------------------------------------------------------------------
    def _updateFromIDProperties(self, props):
        for k,v in props.iteritems():
            self.attributes[k] = v

    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'DefaultMaterial'

    #-------------------------------------------------------------------------
    #                         g e t V e r t e x T y p e
    #-------------------------------------------------------------------------
    def getVertexType(self):
        if self.vtCustom != None:
            return self.vtCustom

        info = getIrrMaterial(self.attributes['Type'])
        if info != None:
            return info[2]
        else:
            return EVT_STANDARD

    #-------------------------------------------------------------------------
    #                              _ i w r i t e
    #-------------------------------------------------------------------------
    def _iwrite(self,file,tag,name,value):
        svalue = '?enum?'
        if tag == 'enum':
            svalue = value
        elif tag == 'color':
            svalue = del2SColor(value)
        elif tag == 'float':
            svalue = float2str(value)
        elif tag == 'texture':
            svalue = value
        elif tag == 'int':
            svalue = int2str(value)
        elif tag == 'bool':
            svalue = bool2str(value)

        out = '         <{0} name="{1}" value="{2}"/>\n'.format(tag,name,svalue)
        file.write(out)

    #-------------------------------------------------------------------------
    #                             g e t D i f f u s e
    #-------------------------------------------------------------------------
    def getDiffuse(self):
        return self.attributes['DiffuseColor']

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        file.write('      <material bmat="{0}">\n'.format(self.name))
        self._iwrite(file,'enum','Type',self.attributes['Type'])
        self._iwrite(file,'color','Ambient',self.attributes['AmbientColor'])
        self._iwrite(file,'color','Diffuse',self.attributes['DiffuseColor'])
        self._iwrite(file,'color','Emissive',self.attributes['EmissiveColor'])
        self._iwrite(file,'color','Specular',self.attributes['SpecularColor'])
        self._iwrite(file,'float','Shininess',self.attributes['Shininess'])
        self._iwrite(file,'float','Param1',self.attributes['MaterialTypeParam'])
        self._iwrite(file,'float','Param2',self.attributes['MaterialTypeParam2'])
        self._iwrite(file,'bool','Wireframe',self.attributes['WireFrame'])
        self._iwrite(file,'bool','GouraudShading',self.attributes['GouraudShading'])
        self._iwrite(file,'bool','Lighting',self.attributes['Lighting'])
        self._iwrite(file,'bool','ZWriteEnable',self.attributes['ZWriteEnable'])
        self._iwrite(file,'int','ZBuffer',self.attributes['ZBuffer'])
        self._iwrite(file,'bool','BackfaceCulling',self.attributes['BackfaceCulling'])
        self._iwrite(file,'bool','FrontfaceCulling',self.attributes['FrontfaceCulling'])
        self._iwrite(file,'bool','FogEnable',self.attributes['FogEnable'])
        self._iwrite(file,'bool','NormalizeNormals',self.attributes['NormalizeNormals'])
        self._iwrite(file,'int','AntiAliasing',self.attributes['AntiAliasing'])
        self._iwrite(file,'int','ColorMask',self.attributes['ColorMask'])

        stype = 'bool'
        if self.exporter.gIrrlichtVersion != '1.6':
            stype = 'int'

        tex = flattenPath(self.attributes['Layer1']['Texture'])
        self._iwrite(file,'texture','Texture1',tex)
        self._iwrite(file,'enum','TextureWrap1',self.attributes['Layer1']['TextureWrap'])
        self._iwrite(file,'bool','BilinearFilter1',self.attributes['Layer1']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter1',self.attributes['Layer1']['TrilinearFilter'])
        self._iwrite(file,stype,'AnisotropicFilter1',self.attributes['Layer1']['AnisotropicFilter'])
        self._iwrite(file,'int','LODBias1',self.attributes['Layer1']['LODBias'])

        tex = flattenPath(self.attributes['Layer2']['Texture'])
        self._iwrite(file,'texture','Texture2',tex)
        self._iwrite(file,'enum','TextureWrap2',self.attributes['Layer2']['TextureWrap'])
        self._iwrite(file,'bool','BilinearFilter2',self.attributes['Layer2']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter2',self.attributes['Layer2']['TrilinearFilter'])
        self._iwrite(file,stype,'AnisotropicFilter2',self.attributes['Layer2']['AnisotropicFilter'])
        self._iwrite(file,'int','LODBias2',self.attributes['Layer2']['LODBias'])

        tex = flattenPath(self.attributes['Layer3']['Texture'])
        self._iwrite(file,'texture','Texture3',tex)
        self._iwrite(file,'enum','TextureWrap3',self.attributes['Layer3']['TextureWrap'])
        self._iwrite(file,'bool','BilinearFilter3',self.attributes['Layer3']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter3',self.attributes['Layer3']['TrilinearFilter'])
        self._iwrite(file,stype,'AnisotropicFilter3',self.attributes['Layer3']['AnisotropicFilter'])
        self._iwrite(file,'int','LODBias3',self.attributes['Layer3']['LODBias'])

        tex = flattenPath(self.attributes['Layer4']['Texture'])
        self._iwrite(file,'texture','Texture4',tex)
        self._iwrite(file,'enum','TextureWrap4',self.attributes['Layer4']['TextureWrap'])
        self._iwrite(file,'bool','BilinearFilter4',self.attributes['Layer4']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter4',self.attributes['Layer4']['TrilinearFilter'])
        self._iwrite(file,stype,'AnisotropicFilter4',self.attributes['Layer4']['AnisotropicFilter'])
        self._iwrite(file,'int','LODBias4',self.attributes['Layer4']['LODBias'])

        file.write('      </material>\n')

    #-------------------------------------------------------------------------
    #                          _ s e t T e x t u r e
    #-------------------------------------------------------------------------
    def _setTexture(self, bImage, layerNumber):
        self.bimages.append(bImage)

        try:
            texFile = self.exporter.getImageFileName(self.bmesh.name,bImage,0)
        except:
            texFile = '** error accessing {0} **'.format(bImage.name)

        layerName = 'Layer' + str(layerNumber)
        self.attributes[layerName]['Texture'] = texFile

#-----------------------------------------------------------------------------
#                            i U V M a t e r i a l
#-----------------------------------------------------------------------------
class iUVMaterial(iDefaultMaterial):

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, imesh, bobject, name, exporter, face,bmaterial):
        iDefaultMaterial.__init__(self,bobject,name,exporter,bmaterial)
        self.imesh = imesh

        matName = imesh.uvMatName
        if matName != None:
            #
            # custom name?
            #
            if matName[0] == '$':
                vtpos = matName.find(':')
                if vtpos < 0:
                    self.attributes['Type'] = matName[1:]
                else:
                    self.attributes['Type'] = matName[1:vtpos]
                    svt = matName[vtpos+1:].lower()
                    self.vtCustom = EVT_STANDARD
                    if svt == '2tcoords':
                        self.vtCustom = EVT_2TCOORDS
                    elif svt == 'tangents':
                        self.vtCustom = EVT_TANGENTS

            else:
                self.attributes['Type'] = matName

        layerNumber = 1
        for layerNumber in range(len(self.bmesh.uv_textures)):
            #self.bmesh.active_uv_texture_index = layerNumber
            uvFaceData = self.bmesh.uv_textures[layerNumber].data[face.index]
            if uvFaceData.image != None:
                self._setTexture(uvFaceData.image,layerNumber+1)

        if self.attributes['Type'].lower() == 'trans_alphach':
            self.attributes['MaterialTypeParam'] = 0.000001

    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'UVMaterial'

    #-------------------------------------------------------------------------
    #                             g e t I m a g e s
    #-------------------------------------------------------------------------
    def getImages(self):
        return self.bimages

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        iDefaultMaterial.write(self,file)

#-----------------------------------------------------------------------------
#                       i B l e n d e r M a t e r i a l
#-----------------------------------------------------------------------------
class iBlenderMaterial(iDefaultMaterial):

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bmesh, name, exporter, bmaterial):
        iDefaultMaterial.__init__(self,bmesh,name,exporter,bmaterial)
        self.attributes['DiffuseColor'] = '255, 255, 255, 255'
        if self.bmaterial != None:
            self.attributes['DiffuseColor'] = rgb2DelStr(self.bmaterial.diffuse_color)
            if self.bmaterial.use_vertex_color_paint:
                self.useVertexColor = True
            else:
                self.useVertexColor = False

    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'BlenderMaterial'

#-----------------------------------------------------------------------------
#                                i S c e n e
#-----------------------------------------------------------------------------
class iScene:

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self,exporter):
        self.exporter = exporter

    #-------------------------------------------------------------------------
    #                       w r i t e S c e n e H e a d e r
    #-------------------------------------------------------------------------
    def writeSceneHeader(self,file,scene, physicsEnabled):

        amb = (0.0, 0.0, 0.0)
        if scene.world:
            amb = scene.world.ambient_color

        scolor = '{0:.6f}, {1:.6f}, {2:.6f}, {3:.6f}'.format(amb[0],amb[1],amb[2],1.0)

        file.write('<?xml version="1.0"?>\n')
        file.write('<!-- Created {0} by irrb {1} - "Irrlicht/Blender ' \
                'Exporter" -->\n'.format(datetime2str(time.localtime()),
                getversion()))
        file.write('<irr_scene>\n')
        file.write('   <attributes>\n')
        file.write('      <string name="Name" value="root"/>\n')
        file.write('      <int name="Id" value="-1"/>\n')
        file.write('      <vector3d name="Position" value="0.000000, ' +
                '0.000000, 0.000000"/>\n')
        file.write('      <vector3d name="Rotation" value="0.000000, ' +
                '0.000000, 0.000000"/>\n')
        file.write('      <vector3d name="Scale" value="1.000000, '
                + '1.000000, 1.000000"/>\n')
        file.write('      <colorf name="AmbientLight" value="{0}"/>\n'.format(scolor))
        file.write('      <bool name="AutomaticCulling" value="true"/>\n')
        file.write('      <bool name="DebugDataVisible" value="false"/>\n')
        file.write('      <bool name="IsDebugObject" value="false"/>\n')
        file.write('      <bool name="Visible" value="true"/>\n')

        # mist/fog enabled


        if scene.world and scene.world.mist_settings.use_mist:
            mist = scene.world.mist_settings
            mistType = mist.falloff
            if mistType == 'QUADRATIC':
                sMistType = 'FogExp'
            elif mistType == 'LINEAR':
                sMistType = 'FogLinear'
            else: # 'INVERSE_QUADRATIC'
                sMistType = 'FogExp2'
            file.write('      <enum name="FogType" value="{0}"/>\n'.format(sMistType))
            file.write('      <float name="FogStart" value="{0:.6f}"/>\n'.format(mist.start))
            file.write('      <float name="FogEnd" value="{0:.6f}"/>\n'.format(mist.depth))
            file.write('      <float name="FogHeight" value="{0:.6f}"/>\n'.format(mist.height))
            file.write('      <float name="FogDensity" value="{0:.6f}"/>\n'.format(mist.intensity))
            fcolor = scene.world.horizon_color
            file.write('      <colorf name="FogColor" ' \
                'value="{0:.6f}, {1:.6f}, {2:.6f}, {3:.6f}"/>' \
                '\n'.format(fcolor[0],fcolor[1],fcolor[2],1.0))
            file.write('      <bool name="FogPixel" value="false"/>\n')
            file.write('      <bool name="FogRange" value="false"/>\n')

        file.write('   </attributes>\n')

        if not 'irrb' in scene:
            scene['irrb'] = {'userAttributes': defSceneAttributes}

        try:
            scene['irrb']['userAttributes']['Gravity'] = -scene.world.gravity
        except:
            pass

        scene['irrb']['userAttributes']['Physics.Enabled'] = physicsEnabled

        writeUserData(file, '   ', 2*'   ', scene, False)

        col = (0.0, 0.0, 0.0)
        try:
            col = scene.world.horizon_color
        except:
            pass
        file.write('         <colorf name="BackgroundColor" ' \
            'value="{0:.6f}, {1:.6f}, {2:.6f}, {3:.6f}"/>' \
            '\n'.format(col[0],col[1],col[2],1.0))

        file.write('      </attributes>\n')
        file.write('   </userData>\n')

    #-------------------------------------------------------------------------
    #                      w r i t e S c e n e F o o t e r
    #-------------------------------------------------------------------------
    def writeSceneFooter(self,file):
        file.write('</irr_scene>\n')

    #-------------------------------------------------------------------------
    #                     w r i t e S T D A t t r i b u t e s
    #-------------------------------------------------------------------------
    def writeSTDAttributes(self,file,i1,i2,bObject,spos,srot,sscale,cullDefault='frustum_box'):

        file.write(i1 + '<attributes>\n')

        #
        # std attribute defaults
        #
        sa = iStdAttributes()
        sa.AutomaticCulling = cullDefault
        sa.inheritFromObject(bObject);

        file.write(i2 + '<string name="Name" value="{0}"/>\n'.format(bObject.name))

        self._iwrite(file,'int','Id',sa.attributes['Id'],i2)

        file.write(i2 + '<vector3d name="Position" value="{0}"/>\n'.format(spos))
        file.write(i2 + '<vector3d name="Rotation" value="{0}"/>\n'.format(srot))
        file.write(i2 + '<vector3d name="Scale" value="{0}"/>\n'.format(sscale))
        self._iwrite(file,'bool','Visible',sa.attributes['Visible'],i2)
        self._iwrite(file,'enum','AutomaticCulling',sa.attributes['AutomaticCulling'],i2)
        self._iwrite(file,'bool','DebugDataVisible',sa.attributes['DebugDataVisible'],i2)
        self._iwrite(file,'bool','IsDebugObject',sa.attributes['IsDebugObject'],i2)
        self._iwrite(file,'bool','ReadOnlyMaterials',sa.attributes['ReadOnlyMaterials'],i2)


    #-------------------------------------------------------------------------
    #                       w r i t e M e s h O b j e c t
    #-------------------------------------------------------------------------
    def writeMeshObject(self, file, meshFileName, bObject, level, physicsEnabled):

        i1 = getIndent(level,3)
        i2 = getIndent(level,6)

        ipos = b2iPosition(bObject)
        irot = b2iRotation(bObject)
        iscale = b2iVector(bObject.scale)

        spos = '{0:.6f}, {1:.6f}, {2:.6f}'.format(ipos.x, ipos.y, ipos.z)
        srot = '{0:.6f}, {1:.6f}, {2:.6f}'.format(irot.x, irot.y, irot.z)
        sscale = '{0:.6f}, {1:.6f}, {2:.6f}'.format(iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale)

        file.write(i2 + '<string name="Mesh" value="{0}"/>\n'.format
                (flattenPath(meshFileName)))
        file.write(i1 + '</attributes>\n')

        if physicsEnabled == 0:
            writeUserData(file,i1,i2,bObject, True)
            return

        writeUserData(file,i1,i2,bObject, False)
        ctype = 'none'
        hasBounds = False

        # from DNA_Object_types.h
        OB_OCCLUDER		= 0x40000
        OB_SENSOR		= 0x80000

        ctype = bObject.game.physics_type


        i3 = i2 + '   '
        sout = '<string name="Physics.BodyType" value="{0}"/>\n'.format(ctype)
        file.write(i3 + sout)

        sShapeType = bObject.game.collision_bounds_type

        sout = '<string name="Physics.BodyShape" value="{0}"/>\n'.format(sShapeType)
        file.write(i3 + sout)

        """
        todo - find this...
        if bObject.restrictRender:
            sout = '<bool name="Physics.Visible" value="false"/>\n'
        else:
            sout = '<bool name="Physics.Visible" value="true"/>\n'
        file.write(i3 + sout)
        """

        sout = '<float name="Physics.Mass" value="{0:.2f}"/>\n'.format(bObject.game.mass)
        file.write(i3 + sout)

        sout = '<float name="Physics.Radius" value="{0:.2f}"/>\n'.format(bObject.game.radius)
        file.write(i3 + sout)


        if bObject.game.use_ghost:
            sout = '<bool name="Physics.Ghost" value="true"/>\n'
            file.write(i3 + sout)

        if bObject.game.use_actor:
            sout = '<bool name="Physics.Actor" value="true"/>\n'
            file.write(i3 + sout)

        # extract friction & restitution from 1st material
        # may need to use bObject.game.material_physics...
        mesh =  bObject.data
        if (mesh.materials != None) and (len(mesh.materials) == 1):
            try:
                mat = mesh.materials[0]
                if mat != None:
                    sout = '<float name="Physics.Friction" value="{0:.2f}"/>\n'.format(mat.physics.friction)
                    file.write(i3 + sout)

                    sout = '<float name="Physics.Restitution" value="{0:.2f}"/>\n'.format(mat.physics.elasticity)
                    file.write(i3 + sout)
            except:
                pass

        file.write(i2 + '</attributes>\n')
        file.write(i1 + '</userData>\n')

    #-------------------------------------------------------------------------
    #                       w r i t e E m p t y O b j e c t
    #-------------------------------------------------------------------------
    def writeEmptyObject(self,file,bObject,level):
        i1 = getIndent(level,3)
        i2 = getIndent(level,6)

        ipos = b2iPosition(bObject)
        irot = b2iRotation(bObject)
        iscale = b2iVector(bObject.scale)

        spos = '{0:.6f}, {1:.6f}, {2:.6f}'.format(ipos.x, ipos.y, ipos.z)

        srot = '{0:.6f}, {1:.6f}, {2:.6f}'.format(irot.x, irot.y, irot.z)

        sscale = '{0:.6f}, {1:.6f}, {2:.6f}'.format(iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale)

        file.write(i1 + '</attributes>\n')

        writeUserData(file,i1,i2,bObject)

    #-------------------------------------------------------------------------
    #                     w r i t e N o d e H e a d
    #-------------------------------------------------------------------------
    def writeNodeHead(self,file,level,ntype):
        indent = getIndent(level)
        file.write(indent + '<node type="{0}">\n'.format(ntype))

    #-------------------------------------------------------------------------
    #                     w r i t e N o d e T a i l
    #-------------------------------------------------------------------------
    def writeNodeTail(self,file,level):
        indent = getIndent(level)
        file.write(indent + '</node>\n')

    #-------------------------------------------------------------------------
    #                      w r i t e L i g h t N o d e D a t a
    #-------------------------------------------------------------------------
    def writeLightNodeData(self,file,bObject,level):
        i1 = getIndent(level,3)
        i2 = getIndent(level,6)

        ipos = b2iPosition(bObject)
        irot = b2iRotation(bObject)
        iscale = b2iVector(bObject.scale)

        spos = '{0:.6f}, {1:.6f}, {2:.6f}'.format(ipos.x, ipos.y, ipos.z)

        srot = '{0:.6f}, {1:.6f}, {2:.6f}'.format(irot.x, irot.y, irot.z)

        sscale = '{0:.6f}, {1:.6f}, {2:.6f}'.format(iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale)


        light = bObject.data

        lightType = 'Point'
        if light.type == 'AREA':
            lightType = 'Directional'
        elif light.type == 'SPOT':
            lightType = 'Spot'
        elif light.type == 'SUN':
            lightType = 'Directional'
        elif light.type == 'HEMI':
            lightType = 'Directional'

        file.write(i2 + '<enum name="LightType" value="{0}"/>\n'.format(lightType))

        diffuse = '{0:.6f}, {1:.6f}, {2:.6f}, {3:.6f}'.format(light.color[0],light.color[1],light.color[2],1.0)

        file.write(i2 + '<colorf name="AmbientColor" value="0.000000,' +
                '0.000000, 0.000000, 1.000000"/>\n')
        file.write(i2 + '<colorf name="DiffuseColor" value="{0}"/>\n'.format(diffuse))
        file.write(i2 + '<colorf name="SpecularColor" value="1.000000,' +
                '1.000000, 1.000000, 1.000000"/>\n')

        attvalue = 0.0
        if light.energy != 0.000000:
            attvalue = 0.5 / light.energy
        satt = '0.000000 {0:.6f} 0.000000'.format(attvalue)
        file.write(i2 + '<vector3d name="Attenuation" value="{0}"/>\n'.format(satt))

        file.write(i2 + '<float name="Radius" value="{0:.2f}"/>\n'.format
                (light.distance * 2.0))
        file.write(i2 + '<bool name="CastShadows" value="true"/>\n')
        file.write(i1 + '</attributes>\n')

        writeUserData(file,i1,i2,bObject)

    #-------------------------------------------------------------------------
    #                      w r i t e C a m e r a N o d e D a t a
    #-------------------------------------------------------------------------
    def writeCameraNodeData(self,file,bObject,level):
        i1 = getIndent(level,3)
        i2 = getIndent(level,6)

        ipos = b2iPosition(bObject)
        irot = b2iRotation(bObject)
        iscale = b2iVector(bObject.scale)

        spos = '{0:.6f}, {1:.6f}, {2:.6f}'.format(ipos.x, ipos.y, ipos.z)
        srot = '{0:.6f}, {1:.6f}, {2:.6f}'.format(irot.x, irot.y, irot.z)
        sscale = '{0:.6f}, {1:.6f}, {2:.6f}'.format(iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale)

        camera = bObject.data

        #
        # calculate target based on x,z rotation
        #

        target = mathutils.Vector()
        #target.normalize()
        #target = target * 100.0

        rpos = mathutils.Vector((ipos.x,ipos.y,ipos.z))
        #target = target + rpos

        starget = '{0:.6f}, {1:.6f}, {2:.6f}'.format(target.x, target.z, target.y)

        #
        # override fov & aspect with logic properties if defined
        #
        fov = 2 * math.atan(16.0 / camera.lens )
        aspect = 1.25

        prop = getProperty('fov',bObject)
        if prop != None and type(prop) == float:
            fov = prop

        prop = getProperty('aspect',bObject)
        if prop != None and type(prop) == float:
            aspect = prop

        file.write(i2 + '<vector3d name="Target" value="{0}"/>\n'.format(starget))
        file.write(i2 + '<vector3d name="UpVector" value="0.000000,' +
                ' 1.000000, 0.000000"/>\n')
        file.write(i2 + '<float name="Fovy" value="{0:.6f}"/>\n'.format(fov))
        file.write(i2 + '<float name="Aspect" value="{0:.6f}"/>\n'.format(aspect))
        file.write(i2 + '<float name="ZNear" value="{0:.2f}"/>\n'.format
                (camera.clip_start))
        file.write(i2 + '<float name="ZFar" value="{0:.2f}"/>\n'.format
                (camera.clip_end))

        file.write(i1 + '</attributes>\n')

        writeUserData(file,i1,i2,bObject)

    #-------------------------------------------------------------------------
    #                              _ i w r i t e
    #-------------------------------------------------------------------------
    def _iwrite(self,file,tag,name,value,indent):
        svalue = '?enum?'
        if tag == 'enum':
            svalue = value
        elif tag == 'color':
            svalue = del2SColor(value)
        elif tag == 'float':
            svalue = float2str(value)
        elif tag == 'texture':
            svalue = value
        elif tag == 'int':
            svalue = int2str(value)
        elif tag == 'bool':
            svalue = bool2str(value)

        out = indent + '<{0} name="{1}" value="{2}"/>\n'.format(tag,name,svalue)
        file.write(out)

    #-----------------------------------------------------------------------------
    #                    _ w r i t e S B I m a g e A t t r i b u t e s
    #-----------------------------------------------------------------------------
    def _writeSBImageAttributes(self,file,indent,mat,matType,bImage,bObject,lightingOverride=None):

        i2 = indent + '    '
        imageName = self.exporter.getImageFileName(bObject.data.name,bImage,0)
        file.write(indent + '<attributes>\n')
        self._iwrite(file,'enum','Type',matType, i2)
        self._iwrite(file,'color','Ambient',mat.attributes['AmbientColor'],i2)
        self._iwrite(file,'color','Diffuse',mat.attributes['DiffuseColor'],i2)
        self._iwrite(file,'color','Emissive',mat.attributes['EmissiveColor'],i2)
        self._iwrite(file,'color','Specular',mat.attributes['SpecularColor'],i2)
        self._iwrite(file,'float','Shininess',mat.attributes['Shininess'],i2)
        self._iwrite(file,'float','Param1',mat.attributes['MaterialTypeParam'],i2)
        self._iwrite(file,'float','Param2',mat.attributes['MaterialTypeParam2'],i2)
        self._iwrite(file,'bool','Wireframe',mat.attributes['WireFrame'],i2)
        self._iwrite(file,'bool','GouraudShading',mat.attributes['GouraudShading'],i2)
        if lightingOverride == None:
            self._iwrite(file,'bool','Lighting',mat.attributes['Lighting'],i2)
        else:
            self._iwrite(file,'bool','Lighting',lightingOverride,i2)

        self._iwrite(file,'bool','ZWriteEnable',mat.attributes['ZWriteEnable'],i2)
        self._iwrite(file,'int','ZBuffer',mat.attributes['ZBuffer'],i2)
        self._iwrite(file,'bool','BackfaceCulling',mat.attributes['BackfaceCulling'],i2)
        self._iwrite(file,'bool','FogEnable',mat.attributes['FogEnable'],i2)
        self._iwrite(file,'bool','NormalizeNormals',mat.attributes['NormalizeNormals'],i2)
        self._iwrite(file,'int','ColorMask',mat.attributes['ColorMask'],i2)
        self._iwrite(file,'int','AntiAliasing',mat.attributes['AntiAliasing'],i2)

        self._iwrite(file,'texture','Texture1',flattenPath(imageName),i2)
        self._iwrite(file,'enum','TextureWrap1','texture_clamp_clamp',i2)
        self._iwrite(file,'bool','BilinearFilter1',mat.attributes['Layer1']['BilinearFilter'],i2)
        self._iwrite(file,'bool','TrilinearFilter1',mat.attributes['Layer1']['TrilinearFilter'],i2)
        if self.exporter.gIrrlichtVersion >= '1.7':
            self._iwrite(file,'int','AnisotropicFilter1',mat.attributes['Layer1']['AnisotropicFilter'],i2)
        else:
            self._iwrite(file,'bool','AnisotropicFilter1',mat.attributes['Layer1']['AnisotropicFilter'],i2)
        file.write(indent + '</attributes>\n')

    #-----------------------------------------------------------------------------
    #                     w r i t e S k y B o x N o d e D a t a
    #-----------------------------------------------------------------------------
    def writeSkyBoxNodeData(self,file,bObject,sImages,level):

        if bObject.type != 'MESH':
            return

        mesh = bObject.data
        bMaterial = mesh.materials[0]
        material = iDefaultMaterial(bObject,'skybox',
                self.exporter,None)

        topImage = sImages[0]
        botImage = sImages[1]
        leftImage = sImages[2]
        rightImage = sImages[3]
        frontImage = sImages[4]
        backImage = sImages[5]

        i1 = getIndent(level,3)
        i2 = getIndent(level,6)

        spos = '{0:.6f}, {1:.6f}, {2:.6f}'.format(0.0, 0.0, 0.0)
        srot = '{0:.6f}, {1:.6f}, {2:.6f}'.format(0.0, 0.0, 0.0)
        sscale = '{0:.6f}, {1:.6f}, {2:.6f}'.format(1.0, 1.0, 1.0)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale,'false')

        file.write(i1 + '</attributes>\n')
        file.write(i1 + '<materials>\n')

        self._writeSBImageAttributes(file, i2, material, 'solid',
                frontImage, bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', rightImage,
                bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', backImage,
                bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', leftImage,
                bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', topImage,
                bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', botImage,
                bObject, False)

        file.write(i1 + '</materials>\n')

    #-----------------------------------------------------------------------------
    #                          w r i t e A n i m a t i o n
    #-----------------------------------------------------------------------------
    def writeAnimation(self, file, bAction):
        if bAction.name in self.exporter.gExportedNodeAnimations:
            return

        self.exporter.gExportedNodeAnimations.append(bAction.name)

        i1 = getIndent(0)
        i2 = getIndent(1)
        i3 = getIndent(2)

        file.write(i1 + '<animation name="{0}" length="{1:.6f}">\n'.format(bAction.name,
            self.exporter.gAnimationLength))

        parms = ('x', 'y', 'z', 'w')
        for curve in bAction.fcurves:
            dpath = curve.data_path
            target = 'unknown'
            if dpath in ('location', 'rotation_euler', 'scale'):
                target = '{0}.{1}'.format(dpath, parms[curve.array_index])
            else:
                target = '{0}.{1}'.format(dpath, curve.array_index)

            file.write(i2 + '<keyframes target="{0}">\n'.format(target))

            for keyframe in curve.keyframe_points:
                file.write(i3 + '<keyframe time="{0:.6f}" value="{1:.6f}" ipol="{2}"/>\n'.format(\
                    (keyframe.co.x - self.exporter.gBScene.frame_start) / self.exporter.gBScene.render.fps,
                    keyframe.co.y, keyframe.interpolation))

            file.write(i2 + '</keyframes>\n')

        file.write(i1 + '</animation>\n')

    #-----------------------------------------------------------------------------
    #                   w r i t e B i l l b o a r d N o d e D a t a
    #-----------------------------------------------------------------------------
    def writeBillboardNodeData(self,file,bObject,bbImage,level):

        if bObject.type != 'MESH':
            return

        bMaterial = None
        mesh = bObject.data
        if len(mesh.materials) > 0:
            bMaterial = mesh.materials[0]

        material = iDefaultMaterial(bObject,'billboard',
                self.exporter,bMaterial)
        i1 = getIndent(level,3)
        i2 = getIndent(level,6)

        ipos = b2iPosition(bObject)

        spos = '{0:.6f}, {1:.6f}, {2:.6f}'.format(ipos.x, ipos.y, ipos.z)
        srot = '{0:.6f}, {1:.6f}, {2:.6f}'.format(0.0, 0.0, 0.0)
        sscale = '{0:.6f}, {1:.6f}, {2:.6f}'.format(1.0, 1.0, 1.0)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale,'false')

        # billboard quad vertex positions: ul:3, ur:0, lr:1, ll:2

        ul = mesh.vertices[3].co
        ur = mesh.vertices[0].co
        lr = mesh.vertices[1].co

        scale = bObject.scale
        dx = (ul.x - ur.x) * scale[0]
        dy = (ul.y - ur.y) * scale[1]
        dz = (ul.z - ur.z) * scale[2]
        width = math.fabs(math.sqrt((dx * dx) + (dy * dy) + (dz * dz)))

        dx = (ur.x - lr.x) * scale[0]
        dy = (ur.y - lr.y) * scale[1]
        dz = (ur.z - lr.z) * scale[2]
        height = math.fabs(math.sqrt((dx * dx) + (dy * dy) + (dz * dz)))

        file.write(i2 + '<int name="Width" value="{0:.6f}" />\n'.format(width))
        file.write(i2 + '<int name="Height" value="{0:.6f}" />\n'.format(height))
        file.write(i2 + '<color name="Shade_Top" value="ffffffff" />\n')
        file.write(i2 + '<color name="Shade_Down" value="ffffffff" />\n')

        file.write(i1 + '</attributes>\n')
        file.write(i1 + '<materials>\n')

        # extract material type based on irrb UV layer rules
        bMesh = bObject.data
        uvLayerNames = [tex.name for tex in bMesh.uv_textures]
        irrMatInfo = None
        for name in uvLayerNames:
            irrMatInfo = getIrrMaterial(name)
            if irrMatInfo != None:
                break
        if irrMatInfo == None:
            irrMatInfo = ('solid',1)

        self._writeSBImageAttributes(file, i2, material, irrMatInfo[0], bbImage,
                bObject)

        file.write(i1 + '</materials>\n')



#-----------------------------------------------------------------------------
#                               i M e s h
#-----------------------------------------------------------------------------
class iMesh:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bObject, exporter, debug):
        self.bObject = bObject
        self.name = bObject.name
        self.exporter = exporter
        self.gui = exporter.gGUI
        self.bKeyBlocks = None
        self.armatures = []
        self.shapes = []

        # get 'Mesh' - not deprecated 'NMesh'
        self.bMesh =  bObject.data

        # get mesh shape keys
        self.bKey = self.bMesh.shape_keys
        if self.bKey:
            self.bKeyBlocks = self.bKey.keys

        # get mesh armatures
        mods = self.bObject.modifiers
        if mods:
            for mod in mods:
                if mod.type == 'ARMATURE':
                    try:
                        armature = mod.object
                        self.armatures.append(armature)
                    except:
                        pass

        self.meshBuffers = []

        # dict of {mangled material name, MeshBuffer()}
        self.materials = {}
        self.hasFaceUV = len(self.bMesh.uv_textures) > 0
        self.debug = debug

        self.uvMatName = None                # Irrlicht material name
        self.findMatName()

    #-------------------------------------------------------------------------
    #                        f i n d M a t N a m e
    #-------------------------------------------------------------------------
    def findMatName(self):
        if len(self.bMesh.uv_textures) == 0:
            return

        #
        # search for matching Irrlicht material name
        #
        for uv in self.bMesh.uv_textures:
            if getIrrMaterial(uv.name) != None:
                self.uvMatName = uv.name
                return

        #
        # if not found look for custom name: '$' prefix
        #
        for uv in self.bMesh.uv_textures:
            if uv.name[0] == '$':
                self.uvMatName = uv.name
                return

    #-------------------------------------------------------------------------
    #                         g e t M a t e r i a l s
    #-------------------------------------------------------------------------
    def getMaterials(self):
        return self.materials

    #-------------------------------------------------------------------------
    #                       g e t V e r t e x C o u n t
    #-------------------------------------------------------------------------
    def getVertexCount(self):
        count = 0

        for buf in self.meshBuffers:
            count += len(buf.vertices)

        return count

    #-------------------------------------------------------------------------
    #                          g e t F a c e C o u n t
    #-------------------------------------------------------------------------
    def getFaceCount(self):
        count = 0
        for buf in self.meshBuffers:
            count += len(buf.faces)

        return count

    #-------------------------------------------------------------------------
    #                     _ g e t F a c e I m a g e N a m e s
    #-------------------------------------------------------------------------
    def _getFaceImageNames(self,face):
        names = ''
        for uvlayer in self.bMesh.uv_textures:

            if uvlayer.data[face.index].image == None:
                names += 'none:'
            else:
                names += (uvlayer.data[face.index].image.name + ':')
        if names == '':
            names = 'none:'
        return names

    #-------------------------------------------------------------------------
    #                    c r e a t e M e s h B u f f e r s
    #-------------------------------------------------------------------------
    def createMeshBuffers(self):
        if self.debug:
            if self.bObject.parent == None:
                debug('Parent: None')
            else:
                debug('Parent: {0}'.format(self.bObject.parent.name))

            debug('Rotation Mode: {0}'.format(self.bObject.rotation_mode))
            debug('Rotation Euler: {0}'.format(self.bObject.rotation_euler))

            debug('Hide: ' + str(self.bObject.hide))
            debug('Hide Render: ' + str(self.bObject.hide_render))

            lnames = ''
            for uv in self.bMesh.uv_textures:
                if len(uv.name):
                    lnames += ', '
                lnames += uv.name
            debug('UV Layers ({0}): {1}'.format(len(self.bMesh.uv_textures), lnames))
            mname = 'None'
            if self.uvMatName != None:
                mname = self.uvMatName
            debug('Primary UV Layer: '  + mname)
            val = 'False'
            if self.bMesh.show_double_sided:
                val = 'True'
            debug('Double Sided: ' + val)

            if len(self.bMesh.vertex_colors) > 0:
                val = 'True'
            else:
                val = 'False'
            debug('Mesh VertexColors: ' + val)

            #
            # dump shape keys
            #
            #if self.bKey:
            #    debug('Mesh Key: True')
            #    debug('Mesh Key Blocks Count: %d' % len(self.bKeyBlocks))
            #    i = 1
            #    for block in self.bKeyBlocks:
            #        debug('   Block %d, Name: %s, Length: %d' % (i,block.name,
            #            len(block.data)))
            #        i += 1
            #    debug('Mesh Key IPO: %s' % str(self.bKey.ipo))
            #else:
            #    debug('Mesh Key: None')

            #
            # dump ipo's
            #
            #ipos = self.bObject.ipo
            #if ipos:
            #    debug('Mesh ipo: %s' % str(ipos))
            #else:
            #    debug('Mesh ipo: None')

            #
            # dump modifiers
            #
            if len(self.bObject.modifiers) > 0:
                debug('Modifiers:')
                for mod in self.bObject.modifiers:
                    debug('   Name: {0}, Type: {1}'.format(mod.name,mod.type))
            else:
                debug('Modifiers: None')

            #
            # dump armatures
            #
            if len(self.armatures) > 0:
                debug('Armatures:')
                for arm in self.armatures:
                    debug('   Name: {0}, Bone Count: {1}'.format
                            (arm.name,len(arm.pose.bones)))
            else:
                debug('Armatures: None')

            #
            # dump actions
            #
            '''
            act = self.bObject.action
            print 'bObject.action', act, type(act)
            if act != None:
                print '   Action Name', act.name

            strips = self.bObject.actionStrips
            print 'bObject.actionstrips', strips, type(strips)
            if strips != None:
                print '   ActionStrips size: ', len(strips)
                print '   ActionStrips __len__: ', strips.__len__()
            '''

            #
            # dump physics
            #
            debug('physics_type: ' + self.bObject.game.physics_type)
            debug('collision_bounds: ' + self.bObject.game.collision_bounds_type)

            debug('mass: {0:.2f}'.format(self.bObject.game.mass))
            debug('radius: {0:.2f}'.format(self.bObject.game.radius))

        #
        # Loop through faces and create a new "MeshBuffer" class for each unique
        # material assigned to a face.  Also add the corresponding face/vertex
        # info into the MeshBuffer.
        #
        result = True
        faces = self.bMesh.faces
        hasUVTexture = len(self.bMesh.uv_textures) > 0

        fcount = 0
        tfaces = len(faces)
        mcount = 100

        #tangents = self.bMesh.getTangents()

        for face in faces:

            if self.gui.isExportCanceled():
                break;

            fcount += 1
            if (fcount % mcount) == 0:
                self.gui.updateStatus('Analyzing Mesh Faces: {0}, ({1} of {2})'.format
                        (self.bMesh.name, fcount, tfaces))

            # Get the Blender "Procedural" Material for this face.  Will be used
            # for vertex color if a UV texture isn't assigned.  Will also be used
            # in the material name.
            try:
                bMaterial = self.bMesh.materials[face.material_index]
            except:
                bMaterial = None


            matType = 0
            # UV Material (game engine)?
            if hasUVTexture:
                matType = 1
                #
                # UV/game materials allow options (two-sided, lighting,
                # alpha etc.) per face. This is why we include these
                # settings in the material name - differing options will
                # create seperate mesh buffers..
                #
                stwosided = '0'
                # face "light"
                slighting = '0'
                # face "alpha"
                salpha = '0'
                # face blender material index
                sBlenderMat = '00'

                # mesh "Double Sided"
                if self.bMesh.show_double_sided:
                    stwosided = '1'

                if (bMaterial != None):
                    # face blender material index
                    sBlenderMat = '{0:02d}'.format(face.material_index)

                    # face "light"
                    if bMaterial.use_shadeless == False:
                        slighting = '1'

                    # face "alpha"
                    if bMaterial.use_transparency:
                        salpha = '1'

                # face uvlayer image names
                faceImageName = self._getFaceImageNames(face)


                matName = ('uvmat:' + faceImageName + sBlenderMat + stwosided +
                        slighting + salpha)

            # Blender Material
            elif bMaterial != None:
                matType = 2
                matName = 'blender:{0}:{1:02d}'.format(bMaterial.name, face.material_index)
            # Unassigned Material
            else:
                matType = 3
                matName = 'unassigned'

            if matName in self.materials:
                meshBuffer = self.materials[matName]
            else:
                # create the material and mesh buffer
                if matType == 1:    # uv material
                    material = iUVMaterial(self, self.bObject,matName,
                            self.exporter,face,bMaterial)
                elif matType == 2:  # blender material
                    material = iBlenderMaterial(self.bObject,matName,
                            self.exporter,bMaterial)
                else:               # unassigned / default material
                    material = iDefaultMaterial(self.bObject,matName,
                            self.exporter,bMaterial)

                # create the meshbuffer and update the material dict & mesh
                # buffer list
                meshBuffer = iMeshBuffer(self.exporter, self.bMesh, material,
                        self.uvMatName,len(self.meshBuffers))
                self.materials[matName] = meshBuffer
                self.meshBuffers.append(meshBuffer)


            #meshBuffer.addFace(face, tangents[face.index], self.bKeyBlocks)
            #todo - figure if tangents exist or need to be calculated
            tangent = mathutils.Vector()
            tangents = [tangent, tangent, tangent, tangent]
            meshBuffer.addFace(face, tangents, self.bKeyBlocks)

        self.gui.updateStatus('Analyzing Mesh Faces: {0}, Done.'.format
                        (self.bMesh.name))
        if self.debug:
            debug('\n[Buffers]')
            debug('Count: {0}'.format(len(self.materials)))
            for key,val in self.materials.items():
                debug('   ' + key + ' : ' + val.getMaterialType())

        #
        # restore the active uv layer if necessary
        #
        #if self.activeUVLayer != self.bMesh.activeUVLayer:
        #    self.bMesh.activeUVLayer = self.activeUVLayer

        return result

    #-------------------------------------------------------------------------
    #                       w r i t e M e s h D a t a
    #-------------------------------------------------------------------------
    def writeMeshData(self, file):

        file.write('<?xml version="1.0"?>\n')
        file.write('<mesh xmlns="http://irrlicht.sourceforge.net/' \
            'IRRMESH_09_2007" version="1.0">\n')
        file.write('<!-- Created {0} by irrb {1} - ' \
                '"Irrlicht/Blender Exporter" -->\n'.format(datetime2str(time.localtime()),
                    getversion()))

        for buffer in self.meshBuffers:
            buffer.writeBufferData(file)

        file.write('</mesh>\n')

#-----------------------------------------------------------------------------
#                                 i V e r t e x
#-----------------------------------------------------------------------------
class iVertex:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bVertex, irrIdx, bKeyBlocks, color, tangent):
        self.bVertex = bVertex
        self.index = bVertex.index
        self.irrIdx = irrIdx
        self.vcolor = color
        self.UV1 = (0.0, 0.0)
        self.UV2 = None
        #
        # if shape keys exist, use the position from the "basis" key.
        #
        self.pos = []
        if bKeyBlocks != None:
            self.pos = []
            for i in range(len(bKeyBlocks)):
                self.pos.append(bKeyBlocks[i].data[bVertex.index].co)
        else:
            self.pos.append(self.bVertex.co)
        n = self.bVertex.normal
        self.normal = mathutils.Vector((n.x,n.y,n.z))
        if tangent != None:
            self.tangent = mathutils.Vector((tangent.x, tangent.y, tangent.z))
        else:
            self.tangent = mathutils.Vector()

        self.binormal = self.normal.cross(self.tangent)
        self.binormal.normalize()

#-----------------------------------------------------------------------------
#                              i M e s h B u f f e r
#-----------------------------------------------------------------------------
class iMeshBuffer:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, exporter, bMesh, material, uvMatName, bufNumber):
        self.bMesh = bMesh

        #self.bKey = self.bMesh.key
        #self.bKeyBlocks = None
        #if self.bKey:
        #    self.bKeyBlocks = self.bKey.blocks

        self.bufNumber = bufNumber
        self.exporter = exporter
        self.gui = exporter.gGUI

        self.material = material
        self.uvMatName = uvMatName
        self.vertices = []  # list of vertices
        self.faces = []     # list of irr indexes {{i0,i1,i2},{},...}
        self.vertDict = {}  # blender vert index : internal Vertex()
        self.hasUVTextures = len(bMesh.uv_textures) > 0

    #-------------------------------------------------------------------------
    #                         g e t M a t e r i a l T y p e
    #-------------------------------------------------------------------------
    def getMaterialType(self):
        return self.material.getType()

    #-------------------------------------------------------------------------
    #                            g e t M a t e r i a l
    #-------------------------------------------------------------------------
    def getMaterial(self):
        return self.material

    #-------------------------------------------------------------------------
    #                             a d d V e r t e x
    #-------------------------------------------------------------------------
    def addVertex(self, bVertex):

        vertex = Vertex(bVertex)

        self.vertices.append(vertex)

        # return our index
        return len(self.vertices)

    #-------------------------------------------------------------------------
    #                             g e t V e r t e x
    #-------------------------------------------------------------------------
    def getVertex(self,bFace,idx,bKeyBlocks,tangent):

        #
        # extract the Blender vertex data
        #
        bVertex = self.bMesh.vertices[bFace.vertices[idx]]
        vColor = None
        if len(self.bMesh.vertex_colors) > 0:
            # todo extract vertex colors from bMesh.vertex_colors
            #fColor = bFace.col[idx]
            #vColor = rgba2SColor((fColor.r, fColor.g, fColor.b,
            #    fColor.a))
            pass

        # if uv's present - every vertex is unique.  should check for
        # equal uv's...
        if self.hasUVTextures:
            vertex = iVertex(bVertex,len(self.vertices),bKeyBlocks, vColor,
                    tangent)

            uvFaceData = self.bMesh.uv_textures[0].data[bFace.index]
            vertex.UV1 = tuple(uvFaceData.uv[idx])

            if len(self.bMesh.uv_textures) > 1:
                uvFaceData = self.bMesh.uv_textures[1].data[bFace.index]
                vertex.UV2 = tuple(uvFaceData.uv[idx])

            self.vertices.append(vertex)
        else:
            if bVertex.index in self.vertDict:
                vertex = self.vertDict[bVertex.index]
            else:
                vertex = iVertex(bVertex,len(self.vertices),bKeyBlocks,
                        vColor, None)
                self.vertDict[bVertex.index] = vertex
                self.vertices.append(vertex)

        return vertex

    #-------------------------------------------------------------------------
    #                              a d d F a c e
    #-------------------------------------------------------------------------
    def addFace(self, bFace, faceTangents, bKeyBlocks):

        if (len(bFace.vertices) == 3):
            v1 = self.getVertex(bFace,0,bKeyBlocks,faceTangents[0])
            v2 = self.getVertex(bFace,1,bKeyBlocks,faceTangents[1])
            v3 = self.getVertex(bFace,2,bKeyBlocks,faceTangents[2])
            self.faces.append((v1.irrIdx, v2.irrIdx,
                v3.irrIdx))
        elif (len(bFace.vertices) == 4):
            v1 = self.getVertex(bFace,0,bKeyBlocks,faceTangents[0])
            v2 = self.getVertex(bFace,1,bKeyBlocks,faceTangents[1])
            v3 = self.getVertex(bFace,2,bKeyBlocks,faceTangents[2])
            v4 = self.getVertex(bFace,3,bKeyBlocks,faceTangents[3])
            self.faces.append((v1.irrIdx, v2.irrIdx, v3.irrIdx))
            self.faces.append((v4.irrIdx, v1.irrIdx, v3.irrIdx))
        else:
            print('Ignored face with {0} edges.'.format(len(bFace.vertices)))

    #-------------------------------------------------------------------------
    #                        _ w r i t e V e r t e x
    #-------------------------------------------------------------------------
    def _writeVertex(self, file, vert, vtype, idx=0):
        pos = vert.pos[idx]
        normal = vert.normal
        color = vert.vcolor
        uv1 = vert.UV1
        uv2 = vert.UV2
        if uv2 == None:
            uv2 = uv1
            
        tangent = vert.tangent
        binormal = vert.binormal

        spos = '{0:.6f} {1:.6f} {2:.6f} '.format(pos.x, pos.z, pos.y)
        snormal = '{0:.6f} {1:.6f} {2:.6f} '.format(normal.x, normal.z, normal.y)

        if color != None and self.material.useVertexColor:
            scolor = colour2str(color) + ' '
        else:
            scolor = del2SColor(self.material.getDiffuse()) + ' '
        suv = '{0:.6f} {1:.6f} '.format(uv1[0], 1-uv1[1])

        if vtype == EVT_STANDARD:
            file.write('         ' + spos + snormal + scolor + suv + '\n')
            return

        if vtype == EVT_2TCOORDS:
            suv2 = '{0:.6f} {1:.6f} '.format(uv2[0], 1-uv2[1])
            file.write((9*' ') + spos + snormal + scolor + suv + suv2 + '\n')
            return

        stangent = '{0:.6f} {1:.6f} {2:.6f} '.format(tangent.x, tangent.z, tangent.y)
        sbinormal = '{0:.6f} {1:.6f} {2:.6f} '.format(binormal.x, binormal.z, binormal.y)
        file.write( (9*' ') + spos + snormal + scolor + suv + stangent + sbinormal + '\n')

    #-------------------------------------------------------------------------
    #                       _ w r i t e V e r t i c e s
    #-------------------------------------------------------------------------
    def _writeVertices(self, file):
        vtype = self.material.getVertexType()

        if vtype == EVT_STANDARD:
            svtype = 'standard'
        elif vtype == EVT_2TCOORDS:
            svtype = '2tcoords'
        elif vtype == EVT_TANGENTS:
            svtype = 'tangents'

        file.write('      <vertices type="{0}" vertexCount="{1}">\n'.format
                (svtype, len(self.vertices)))

        meshName = self.bMesh.name
        tverts = len(self.vertices)
        vcount = 0
        mcount = 100
        bnum = self.bufNumber
        if tverts > 10000:
            mcount = 1000
        for vert in self.vertices:
            if self.gui.isExportCanceled():
                return

            self._writeVertex(file, vert, vtype)
            vcount += 1
            if (vcount % mcount) == 0:
                self.gui.updateStatus('Exporting Mesh: {0}, buf: {1} writing ' \
                    'vertices({2} of {3})'.format(meshName, bnum, vcount, tverts))
        file.write('      </vertices>\n')

    #-------------------------------------------------------------------------
    #                         _ w r i t e F a c e s
    #-------------------------------------------------------------------------
    def _writeFaces(self, file):
        file.write('      <indices indexCount="{0}">\n'.format(len(self.faces)*3))
        line = 8 * ' '
        iCount = 0

        meshName = self.bMesh.name
        tfaces = len(self.faces)
        fcount = 0
        bnum = self.bufNumber
        for face in self.faces:
            if self.gui.isExportCanceled():
                return
            line += (' {0} {1} {2}'.format(face[2], face[1], face[0]))
            iCount += 1
            if iCount == 12:
                file.write(line+'\n')
                line = 8 * ' '
                iCount = 0
            fcount += 1
            if (fcount % 100) == 0:
                self.gui.updateStatus('Exporting Mesh: {0}, buf: {1} writing faces({2} of {3}'.format 
                        (meshName, bnum, fcount, tfaces))

        if iCount > 0:
            file.write(line+'\n')

        file.write('      </indices>\n')

    #-------------------------------------------------------------------------
    #                     _ w r i t e M o r p h T a r g e t
    #-------------------------------------------------------------------------
    def _writeMorphTarget(self, file, idx):
        block = self.bKeyBlocks[idx]

        #
        # first, count the number of vertices we'll be writing
        #

        vidx = 0
        for vert in self.vertices:
            if iGUI.exportCancelled():
                return

            bvert = vert.pos[0]
            pos = vert.pos[idx]

            if (bvert.x != pos.x) or (bvert.y != pos.y) or (bvert.z != pos.z):
                vidx += 1

        file.write('      <morph-target name="{0}" vertexCount="{1}">\n'.format(block.name,vidx))

        meshName = self.bMesh.name
        tverts = len(self.vertices)
        vcount = 0
        mcount = 100
        bnum = self.bufNumber
        if tverts > 10000:
            mcount = 1000
        vidx = 0
        for vert in self.vertices:
            if iGUI.exportCancelled():
                return

            bvert = vert.pos[0]

            pos = vert.pos[idx]

            if (bvert.x != pos.x) or (bvert.y != pos.y) or (bvert.z != pos.z):
                spos = '{0} {1:.6f} {2:.6f} {3:.6f} '.format(vidx, pos.x, pos.z, pos.y)
                file.write(9*' ' + spos + '\n')
            vidx += 1
            vcount += 1
            if (vcount % mcount) == 0:
                iGUI.updateStatus('Exporting Mesh: {0}, buf: {1} writing vertices({2} of {3})'.format
                        (meshName, bnum, vcount, tverts))

        file.write('      </morph-target>\n')

    #-------------------------------------------------------------------------
    #                              w r i t e
    #-------------------------------------------------------------------------
    def writeBufferData(self, file):
        file.write('   <buffer>\n')

        self.material.write(file)

        self._writeVertices(file)

        self._writeFaces(file)

        # todo
        #if self.bKeyBlocks:
        #    for i in range(1,len(self.bKeyBlocks)):
        #        self._writeMorphTarget(file,i)

        file.write('   </buffer>\n')


#-------------------------------------------------------------------------------
#                              i E x p o r t e r
#-------------------------------------------------------------------------------
class iExporter:

    #---------------------------------------------------------------------------
    #                               _ i n i t _
    #---------------------------------------------------------------------------
    def __init__(self, Context, Operator, GUIInterface,
            CreateScene, BaseDir, SceneDir, MeshDir, TexDir, SelectedObjectsOnly,
            ExportLights, ExportCameras, ExportAnimations, ExportPhysics,
            Binary, UseBlenderMaterials, Debug, runWalkTest, IrrlichtVersion,
            MeshCvtPath, WalkTestPath):

        # Load the default/saved configuration values
        self.gOperator = Operator

        self.loadConfig()

        if len(BaseDir):
            if BaseDir[len(BaseDir)-1] != os.path.sep:
                BaseDir += os.path.sep

        if len(MeshDir):
            if MeshDir[len(MeshDir)-1] != os.path.sep:
                MeshDir += os.path.sep
        if len(TexDir):
            if TexDir[len(TexDir)-1] != os.path.sep:
                TexDir += os.path.sep

        self.gContext = Context
        self.gGUI = GUIInterface
        self.gCreateScene = CreateScene
        self.gBaseDir = BaseDir
        self.gBlendFileName = bpy.data.filepath
        self.gBlendRoot = os.path.dirname(self.gBlendFileName)
        self.gMeshDir = MeshDir
        self.gTexDir = TexDir
        self.gSceneDir = SceneDir
        self.gTexExtension = '.???'
        self.gSelectedObjectsOnly = SelectedObjectsOnly
        self.gExportLights = ExportLights
        self.gExportCameras = ExportCameras
        self.gExportAnimations = ExportAnimations
        self.gExportPhysics = ExportPhysics
        self.gCopyImages = defScriptOptions['copyExternalImages']
        self.gActions = {}
        self.gBinary = Binary
        self.gUseBlenderMaterials = UseBlenderMaterials
        self.gDebug = Debug
        self.gRunWalkTest = runWalkTest
        self.gRootObjects = []
        self.gMeshFileName = ''
        self.gSceneFileName = ''
        self.gObjectLevel = 0
        self.gIrrlichtVersion = IrrlichtVersion
        self.gMeshCvtPath = MeshCvtPath
        self.gWalkTestPath = WalkTestPath
        self.gBScene = None
        self.gIScene = None
        self.sfile = None
        self.gAnimationLength = 0.0

    #---------------------------------------------------------------------------
    #                               l o a d C o n f i g
    #---------------------------------------------------------------------------
    def loadConfig(self):
        pass

    #---------------------------------------------------------------------------
    #                              g e t T e x P a t h
    #---------------------------------------------------------------------------
    def getTexPath(self):
        if self.gTexPath.strip() == '':
            return self.gTexDir
        return self.gTexPath

    #---------------------------------------------------------------------------
    #                              g e t T e x E x t
    #---------------------------------------------------------------------------
    def getTexExt(self):
        return self.gTexExtension

    #---------------------------------------------------------------------------
    #                           _ d u m p O p t i o n s
    #---------------------------------------------------------------------------
    def _dumpOptions(self):
        debug('\n[options]')
        debug('     Create Scene: ' + ('True' if self.gCreateScene else 'False'))
        debug('   Base Directory: ' + self.gBaseDir)
        debug('  Scene Directory: ' + self.gSceneDir)
        debug('   Mesh Directory: ' + self.gMeshDir)
        debug('  Image Directory: ' + self.gTexDir)
        debug('       meshOutDir: ' + defScriptOptions['meshOutDir'])
        debug('        texOutDir: ' + defScriptOptions['texOutDir'])
        debug('           Binary: ' + ('True' if self.gBinary else 'False'))
        debug('Blender Materials: ' + ('True' if self.gUseBlenderMaterials else 'False'))
        debug('   Export Cameras: ' + ('True' if self.gExportCameras else 'False'))
        debug('    Export Lights: ' + ('True' if self.gExportLights else 'False'))
        debug('   Export Physics: ' + ('True' if self.gExportPhysics else 'False'))
        debug('      Copy Images: ' + ('True' if self.gCopyImages else 'False'))
        debug('     Run WalkTest: ' + ('True' if self.gRunWalkTest else 'False'))
        debug('  Image Extension: ' + ('Original' if self.gTexExtension ==
            '.???' else self.gTexExtension))
        debug('    Selected Only: ' + ('True' if self.gSelectedObjectsOnly else
            'False'))
        debug('     Irrlicht Ver: ' + str(self.gIrrlichtVersion))
        debug('    iwalktest Env: {0}'.format(self.gWalkTestPath))
        debug('     imeshcvt Env: {0}'.format(self.gMeshCvtPath))
        if self.gWalkTestPath:
            debug('    iwalktest Cmd: ' + self.gWalkTestPath.replace('$1',
                flattenPath(self.gSceneFileName)).replace('$2',filterPath(self.gBaseDir)))

    #---------------------------------------------------------------------------
    #                             _ d u m p S t a t s
    #---------------------------------------------------------------------------
    def _dumpStats(self, stats):
        debug('\n[stats]')
        for stat in stats:
            debug(stat)

    #---------------------------------------------------------------------------
    #                      _ d u m p G e n e r a l I n f o
    #---------------------------------------------------------------------------
    def _dumpGeneralInfo(self):
        debug('\n[general info]')
        if gHavePlatform:
            p = platform.uname()
            debug('               OS: {0} {1} {2}'.format(p[0], p[2], p[3]))
        else:
            debug('               OS: [no platform]')
        debug('  Blender Version: {0[0]}.{0[1]}.{0[2]}'.format(bpy.app.version))
        debug('      .blend File: ' + self.gBlendFileName)
        debug('      .blend Root: ' + self.gBlendRoot)
        debug('   Python Version: {0}.{1}.{2} {3}'.format(sys.version_info[0],
            sys.version_info[1], sys.version_info[2], sys.version_info[3]))

    #---------------------------------------------------------------------------
    #                       _ d u m p S c e n e I n f o
    #---------------------------------------------------------------------------
    def _dumpSceneInfo(self):
        debug('\n[scene info]')
        debug('Scene Name:' + self.gBScene.name)
        vlayers = [i for i in range(len(self.gSceneLayers)) if self.gSceneLayers[i]]
        debug('Visible Layers: ' + str(vlayers))
        debug('Horizon Color: ' + str(self.gBScene.world.horizon_color))

    #---------------------------------------------------------------------------
    #                         _ d u m p O b j e c t I n f o
    #---------------------------------------------------------------------------
    def _dumpRootObjectInfo(self):
        idx = 0
        debug('\n[object info]')
        for bObject in self.gRootObjects:
            olayers = [i for i in range(len(bObject.layers)) if bObject.layers[i]]
            debug('Object ({0}): Name={1}, Type={2}, Layers={3}, NodeAnim={4}'.format(idx,
                bObject.name, bObject.type, str(olayers), _hasNodeAnimations(bObject)))
            idx += 1

    #---------------------------------------------------------------------------
    #                       _ d u m p A n i m a t i o n I n f o
    #---------------------------------------------------------------------------
    def _dumpAnimationInfo(self):
        debug('\n[animation info]')
        debug('fpsbase: {0:.4f}'.format(self.gBScene.render.fps_base))
        debug('    fps: {0}'.format(self.gBScene.render.fps))
        debug(' sFrame: {0}'.format(self.gBScene.frame_start))
        debug(' eFrame: {0}'.format(self.gBScene.frame_end))


    #---------------------------------------------------------------------------
    #                           _ r u n W a l k T e s t
    #---------------------------------------------------------------------------
    def _runWalkTest(self):
        global gWTDirectory, gWTCmdLine

        gWTDirectory = os.path.dirname(self.gWalkTestPath)

        gWTCmdLine = self.gWalkTestPath.replace('$1',
             flattenPath(self.gSceneFileName)).replace('$2', filterPath(self.gBaseDir))

        subprocess.Popen(gWTCmdLine, shell=True, cwd=gWTDirectory)

    #---------------------------------------------------------------------------
    #                              d o E x p o r t
    #---------------------------------------------------------------------------
    def doExport(self):

        self.gFatalError = None
        self.gImageInfo = {}

        self.gGUI.updateStatus('Exporting...')
        start = time.clock()

        # exit edit mode if necessary
        editMode = False
        active_obj = self.gContext.active_object
        if active_obj != None:
            editMode = (active_obj.mode == 'EDIT')
        if editMode:
            bpy.ops.object.mode_set(mode='OBJECT', toggle=False)

        #
        # use this to track exported mesh data.  multiple mesh objects may
        # reference the same mesh data. irrb only export's a single copy
        #
        self.gExportedMeshes = []
        self.gExportedMeshesLC = []
        self.gMeshNameConflicts = []

        #
        # export objects from the current scene
        #
        self.gBScene = self.gContext.scene
        self.gSceneLayers = self.gBScene.layers
        
        self.gAnimationLength = float(self.gBScene.frame_end - self.gBScene.frame_start) / self.gBScene.render.fps

        #self.gActions = Blender.Armature.NLA.GetActions()

        #
        # initialize .irr scene file if requested
        #
        logName = ''
        if self.gCreateScene:
            try:
                if not self.gSceneDir.endswith(os.path.sep):
                    self.gSceneDir += os.path.sep

                self.gSceneFileName = (self.gSceneDir +
                    self.gBScene.name + '.irr')
                self.sfile = open(self.gSceneFileName,'w')
                self.gIScene = iScene(self)
                self.gIScene.writeSceneHeader(self.sfile, self.gBScene, self.gExportPhysics)
            except:
                self.sfile = None
                self.gSceneFileName = None
                print('write Scene error:', sys.exc_info()[0])
                raise


        logName = self.gBaseDir
        if not logName.endswith(os.path.sep):
            logName += os.path.sep
        logName += 'irrb.log'

        try:
            openLog(logName)
        except:
            self.gFatalError = 'Error Opening (+w) Log File: {0}'.format(logName)
            stats = ['Export Failed!']
            stats.append(self.gFatalError)
            self.gGUI.setStatus(stats)
            return

        debug('irrb log ' + iversion)

        self._dumpGeneralInfo()
        self._dumpOptions()
        self._dumpSceneInfo()
        dumpStartMessages()

        self._dumpAnimationInfo()

        for object in self.gBScene.objects:
            pObject = object.parent
            if pObject is None:
                self.gRootObjects.append(object)

        self._dumpRootObjectInfo()

        self.gObjectLevel = 0
        self.gObjectCount = 0
        self.gLightCount = 0
        self.gCameraCount = 0
        self.gVertCount = 0
        self.gFaceCount = 0
        self.copiedImages = []
        self.gExportedNodeAnimations = []

        # export object/node animations (loc/rot/scale) to scene file.
        if self.gExportAnimations and self.gCreateScene and self.sfile:
            for bObject in self.gRootObjects:
                self._exportNodeAnimations(bObject)

        for bObject in self.gRootObjects:
            self._exportObject(bObject)
            if (self.gFatalError != None) or (self.gGUI.isExportCanceled()):
                break

        if self.sfile != None:
            self.gIScene.writeSceneFooter(self.sfile)
            self.sfile.close()
            self.sfile = None

        if editMode:
            bpy.ops.object.mode_set(mode='EDIT', toggle=False)

        end = time.clock()
        etime = time.strftime('%X %x')
        stats = ['Export Complete - {0:.2f} seconds - {1}'.format(end-start,etime)]
        stats.append('{0} Object(s)'.format(self.gObjectCount))
        mcount = len(self.gExportedMeshes)
        if mcount == 1:
            temp = '{0} Mesh'
        else:
            temp = '{0} Meshes'
        stats.append(temp.format(mcount))
        stats.append('{0} Light(s)'.format(self.gLightCount))
        stats.append('{0} Image(s)'.format(len(self.copiedImages)))
        stats.append('{0}/{1} Verts/Tris'.format(self.gVertCount,self.gFaceCount))
        if len(self.gMeshNameConflicts) > 0:
            stats.append('Error: The following meshes contained naming conflicts:')
            for name in self.gMeshNameConflicts:
                stats.append('   ' + name)

        if self.gFatalError != None:
            stats = ['Export Failed!']
            stats.append(self.gFatalError)

        self._dumpStats(stats)
        closeLog()

        self.gGUI.setStatus(stats)

        if (self.gFatalError == None) and self.gRunWalkTest:
            self._runWalkTest()

    #---------------------------------------------------------------------------
    #                        _ g e t C h i l d r e n
    #---------------------------------------------------------------------------
    def _getChildren(self,obj):
        obs = self.gBScene.objects
        return [ ob for ob in obs if ob.parent == obj ]
    
    #---------------------------------------------------------------------------
    #                 _ o b j e c t I n V i s i b l e L a y e r
    #---------------------------------------------------------------------------
    def _objectInVisibleLayer(self, obj):
        visibleLayer = -1
        for l in range(len(obj.layers)):
            if obj.layers[l] and self.gSceneLayers[l]:
                visibleLayer = l
                return True

        return False

    #---------------------------------------------------------------------------
    #                  _ e x p o r t N o d e A n i m a t i o n s
    #---------------------------------------------------------------------------
    def _exportNodeAnimations(self, bObject):
        if not self._objectInVisibleLayer(bObject):
            return

        if self.gSelectedObjectsOnly == 1 and not bObject.selected:
            return

        if not bObject.animation_data:
            return

        # export active
        if bObject.animation_data.action:
            if _actionContainsLocRotScale(bObject.animation_data.action):
                self.gIScene.writeAnimation(self.sfile, bObject.animation_data.action)

        # export NLA Tracks
        if bObject.animation_data.nla_tracks:
            for track in bObject.animation_data.nla_tracks:
                for strip in track.strips:
                    if _actionContainsLocRotScale(strip.action):
                        self.gIScene.writeAnimation(self.sfile, strip.action)

    #---------------------------------------------------------------------------
    #                          _ e x p o r t O b j e c t
    #---------------------------------------------------------------------------
    def _exportObject(self,bObject):

        if not self._objectInVisibleLayer(bObject):
            return

        type = bObject.type

        writeObject = True
        if self.gSelectedObjectsOnly == 1 and not bObject.selected:
            writeObject = False

        #
        # Look for an assigned blender ID property named "inodetype" (Irrlicht
        # node type).  If it exists, use it to determine the type of node
        # we should export. If it doesn't exist or it is set to "default", use the
        # Blender object type.
        #

        itype = NT_DEFAULT
        if 'irrb.NodeType' in bObject:
            itype = bObject['irrb.NodeType']
            
        writeTail = True

        if writeObject:
            if itype != NT_DEFAULT:
                if itype == NT_SKYBOX:
                    if self.sfile != None:
                        sImages = self._validateSkyBox(bObject)
                        if sImages == None:
                            writeTail = False
                        else:
                            self.gIScene.writeNodeHead(self.sfile,self.gObjectLevel,'skyBox')
                            self.gIScene.writeSkyBoxNodeData(self.sfile, bObject,
                                    sImages, self.gObjectLevel)
                            for image in sImages:
                                self._saveImage(image)

                elif itype == NT_BILLBOARD:
                    if self.sfile != None:
                        bbImage = self._validateBillboard(bObject)
                        if bbImage == None:
                            writeTail = False
                        else:
                            self.gIScene.writeNodeHead(self.sfile,self.gObjectLevel,'billBoard')
                            self.gIScene.writeBillboardNodeData(self.sfile, bObject,
                                    bbImage, self.gObjectLevel)
                            self._saveImage(bbImage)

                else:
                    # display invalid "inodetype" warning
                    addWarning('Object "{0}", has invalid "inodetype."'.format(bObject.name))
                    writeTail = False
            elif type == 'MESH':
                if self.sfile != None:
                    #
                    # should check if mesh actually contains animations...
                    #
                    self.gIScene.writeNodeHead(self.sfile,self.gObjectLevel,'mesh')
                self._exportMesh(bObject)
                self.gObjectCount += 1
            elif (type == 'LAMP'):
                if (self.sfile != None) and self.gExportLights:
                    self.gIScene.writeNodeHead(self.sfile,self.gObjectLevel,'light')
                    self.gIScene.writeLightNodeData(self.sfile,bObject,self.gObjectLevel)
                    self.gLightCount += 1
                else:
                    writeTail = False
            elif (type == 'CAMERA'):
                if (self.sfile != None) and self.gExportCameras:
                    self.gIScene.writeNodeHead(self.sfile,self.gObjectLevel,'camera')
                    self.gIScene.writeCameraNodeData(self.sfile,bObject,self.gObjectLevel)
                    self.gCameraCount += 1
                else:
                    writeTail = False
            elif (type == 'EMPTY' or type == 'ARMATURE'):
                if (self.sfile != None):
                    self.gIScene.writeNodeHead(self.sfile,self.gObjectLevel,'empty')
                    self.gIScene.writeEmptyObject(self.sfile,bObject,self.gObjectLevel)
                else:
                    writeTail = False
            else:
                writeTail = False

        #
        # If the object contains children, then export using a recursive
        # call to _exportObject().  This effectively links the children in the
        # scene (.irr) file:
        #   <parent node header>
        #       <parent node data>
        #       <child node header>
        #           <child node data>
        #       <child node tail>
        #   <parent node tail>
        #
        self.gObjectLevel += 1
        cObjects = self._getChildren(bObject)
        for cObject in cObjects:
            self._exportObject(cObject)
        self.gObjectLevel -= 1

        if writeObject and (self.sfile != None) and writeTail:
            self.gIScene.writeNodeTail(self.sfile,self.gObjectLevel)


    #---------------------------------------------------------------------------
    #                     _ v a l i d a t e B i l l b o a r d
    #---------------------------------------------------------------------------
    def _validateBillboard(self, bObject):
        mesh = bObject.data

        if bObject.type != 'MESH':
            msg = 'Ignoring billboard: {0}, not a mesh object.'.format(mesh.name)
            addWarning(msg)
            return None

        if len(mesh.uv_textures) == 0:
            msg = 'Ignoring billboard: {0}, no UV Map.'.format(mesh.name)
            addWarning(msg)
            return None

        faces = mesh.faces
        if len(faces) != 1:
            msg = 'Ignoring billboard: {0}, invalid face count: {1}'.format(mesh.name, len(faces))
            addWarning(msg)
            return None

        bImage = mesh.uv_textures[0].data[faces[0].index].image
        return bImage

    #---------------------------------------------------------------------------
    #                        _ v a l i d a t e S k y B o x
    #---------------------------------------------------------------------------
    def _validateSkyBox(self, bObject):
        mesh = bObject.data

        if bObject.type != 'MESH':
            msg = 'Ignoring skybox: {0}, not a mesh object.'.format(mesh.name)
            addWarning(msg)
            return None

        if len(mesh.uv_textures) == 0:
            msg = 'Ignoring skybox: {0}, no UV Map.'.format(mesh.name)
            addWarning(msg)
            return None

        faces = mesh.faces
        if len(faces) != 6:
            msg = 'Ignoring skybox: {0}, invalid face count: {1}'.format(mesh.name, len(faces))
            addWarning(msg)
            return None

        topImage = None
        botImage = None
        leftImage = None
        rightImage = None
        frontImage = None
        backImage = None
        for face in faces:
            no = face.normal

            no.x = float('{0:.2f'.format(no.x))
            no.y = float('{0:.2f'.format(no.y))
            no.z = float('{0:.2f'.format(no.z))

            # top / bottom?
            fimage = mesh.uv_textures[0].data[face.index].image

            if fuzzyZero(no.x) and fuzzyZero(no.y):
                if no.z == -1.0:
                    topImage = fimage
                elif no.z == 1.0:
                    botImage = fimage
            # left / right?
            elif fuzzyZero(no.y) and fuzzyZero(no.z):
                if no.x == -1.0:
                    rightImage = fimage
                elif no.x == 1.0:
                    leftImage = fimage
            #front / back?
            elif fuzzyZero(no.x) and fuzzyZero(no.z):
                if no.y == -1.0:
                    frontImage = fimage
                elif no.y == 1.0:
                    backImage = fimage

        if (topImage == None or botImage == None or
            leftImage == None or rightImage == None or
            frontImage == None or backImage == None):
            msg = 'Ignoring skybox: {0}, not all faces assigned images'.format(mesh.name)
            addWarning(msg)
            return None

        return (topImage, botImage, leftImage, rightImage, frontImage,
                backImage)

    #---------------------------------------------------------------------------
    #                    _ h a s M e s h B e e n E x p o r t e d
    #---------------------------------------------------------------------------
    # Blender treats object/datablock names that only differ in case as
    # NOT equal.  Therefore 'Cube' is not the same as 'cube'.  This doesn't work
    # for exporters running on windows without internally renaming the mesh
    # to Cube.001.  Our choice is to display an error message - the
    # generated scene/meshes will likely NOT be correct.
    #
    def _hasMeshBeenExported(self, meshName):
        result = meshName in self.gExportedMeshes
        if not result:
            result = meshName.lower() in self.gExportedMeshesLC
            if result:
                self.gMeshNameConflicts.append(meshName)
        return result

    #---------------------------------------------------------------------------
    #                 _ a d d T o M e s h E x p o r t e d L i s t
    #---------------------------------------------------------------------------
    def _addToMeshExportedList(self, meshName):
        if self._hasMeshBeenExported(meshName):
            return

        self.gExportedMeshes.append(meshName)
        self.gExportedMeshesLC.append(meshName.lower())

    #---------------------------------------------------------------------------
    #                           _ c o n v e r t M e s h
    #---------------------------------------------------------------------------
    def _convertMesh(self,iname,oname):

        self.gGUI.updateStatus('Creating Binary Mesh: ' + oname)

        meshcvt = self.gMeshCvtPath
        directory = os.path.dirname(meshcvt)

        cmdline =  meshcvt + ' -v ' + self.gIrrlichtVersion + ' -i "' + iname + '"  -o "' + oname
        cmdline +=  '" -a "' + filterPath(self.gBaseDir) + '"'

        try:
            subprocess.call(cmdline, shell=True, cwd=directory)
        except:
            self.gFatalError = 'Error Converting To Binary Mesh.  Check imeshcvt setup.'

    #---------------------------------------------------------------------------
    #                            _ e x p o r t M e s h
    #---------------------------------------------------------------------------
    def _exportMesh(self, bObject):

        meshData = bObject.data
        oName = bObject.name
        debug('\n[Mesh - ob:{0}, me:{1}]'.format(oName,meshData.name))

        self.gMeshFileName = self.gMeshDir + meshData.name + '.irrmesh'
        binaryMeshFileName = ''
        if self.gBinary:
            binaryMeshFileName = (self.gMeshDir +
                    meshData.name + '.irrbmesh')

        self.gGUI.updateStatus('Exporting Mesh: ' + meshData.name + ', Object: ' + oName)

        alreadyExported = self._hasMeshBeenExported(meshData.name)

        if len(meshData.vertices) == 0:
            msg = 'ignoring mesh: {0}, no vertices'.format(meshData.name)
            addWarning(msg)
            return

        #
        # write scene node data to scene (.irr) file
        #
        meshFileName = self.gMeshFileName

        if self.sfile != None:
            meshFileName = relpath(self.gMeshFileName, self.gBaseDir)

            sceneMeshFileName = meshFileName
            if self.gBinary:
                fname,fext = os.path.splitext(meshFileName)
                sceneMeshFileName = fname + '.irrbmesh'

            self.gIScene.writeMeshObject(self.sfile,sceneMeshFileName,bObject,
                    self.gObjectLevel, self.gExportPhysics)

        #
        # have we already exported this mesh data block?
        #
        if alreadyExported:
            return

        self._addToMeshExportedList(meshData.name)

        try:
            file = open(self.gMeshFileName,'w')
        except:
            pass

        irrMesh = iMesh(bObject,self,True)
        if irrMesh.createMeshBuffers() == True:
            if self.gGUI.isExportCanceled():
                file.close()
                return

            irrMesh.writeMeshData(file)

            if self.gGUI.isExportCanceled():
                file.close()
                return

            self.gVertCount += irrMesh.getVertexCount()
            self.gFaceCount += irrMesh.getFaceCount()

            # write image(s) if any
            for k,v in irrMesh.getMaterials().items():
                if self.gGUI.isExportCanceled():
                    file.close()
                    return

                if v.getMaterialType() == 'UVMaterial':
                    mat = v.getMaterial()
                    images = mat.getImages()
                    for image in images:
                        self._saveImage(image)

        file.close()
        file = None

        #
        # if requested, convert to binary (.irrbmesh) using "imeshcvt".
        #
        if self.gBinary:
            self._convertMesh(self.gMeshFileName, binaryMeshFileName)

    #---------------------------------------------------------------------------
    #                       g e t I m a g e F i l e N a m e
    #---------------------------------------------------------------------------
    # which: 0-texture path, full filename
    def getImageFileName(self,meshName,bImage,which):
        imageName = bImage.name
        if imageName in self.gImageInfo:
            return self.gImageInfo[imageName][which]

        fullFileName = bImage.filepath

        #
        # check for relative path and expand if necessary
        #
        if fullFileName[0:2] == '//':
            fullFileName = bpy.path.abspath(fullFileName)
        dirname = os.path.dirname(fullFileName)
        exists = False
        try:
            file = open(fullFileName,'r')
            file.close()
            exists = True
        except:
            pass

        #
        # it is possible that a blender gen'd image was saved without an
        # extension.  in this case the full filename won't contain the
        # extension but the image name will...
        #
        ext = os.path.splitext(fullFileName)[1]
        if not exists and (ext == ''):
            checkName = dirname + os.path.sep + imageName
            try:
                file = open(checkName,'r')
                file.close()
                exists = True
                fullFileName = checkName
            except:
                pass

        if (bImage.packed_file != None) or not exists:
            fileName = bImage.name
            fileExt = ''
        else:
            fileName,fileExt = os.path.splitext(os.path.basename(fullFileName))

        debug('\n[Image]')
        debug('imageName: ' + imageName)
        debug('org fullFileName: ' + bImage.filepath)
        debug('fullFileName: ' + fullFileName)
        debug('dirname: ' + dirname)
        debug('fileName: ' + fileName)
        debug('fileExt: ' + fileExt)

        try:
            debug('bImage.file_format: {0}'.format(bImage.file_format))
            debug('bImage.depth: {0}'.format(bImage.depth))
            debug('bImage.source: {0}'.format(bImage.source))
            debug('bImage.packed_file: {0}'.format(bImage.packed_file))
            debug('bImage.library: {0}'.format(bImage.library))
            debug('exists on disk: {0}'.format(exists))
        except:
            debug('error accessing image properties for: {0}'.format(bImage.name))
            return None

        #
        #
        result = '???'
        ext = fileExt
        if self.gTexExtension != '.???':
            ext = self.gTexExtension

        if (bImage.packed_file != None) or self.gCopyImages:
            result = relpath(self.gTexDir + fileName + ext,
                     self.gBaseDir)
        else:
            result = relpath(fullFileName, self.gBaseDir)

        result0 = result

        result = fullFileName
        if self.gTexExtension != '.???':
            result = self.gTexDir + fileName + ext
        else:
            result = self.gTexDir + fileName + fileExt
        debug('result0: {0}'.format(result0))
        debug('result1: {0}'.format(result))
        self.gImageInfo[imageName] = (result0,result)
        if which == 0:
            return result0
        return result

    #---------------------------------------------------------------------------
    #                      _ s a v e P a c k e d T e x t u r e
    #---------------------------------------------------------------------------
    def _savePackedTexture(self, bImage):

        if bImage in self.copiedImages:
            return

        filename = self.getImageFileName('',bImage,1)
        if filename == None:
            return

        self.gGUI.updateStatus('Saving Packed Texture ' + filename + '...')
        self.copiedImages.append(bImage)

        if self.gTexExtension != '.???':
            iTGAWriter.writeTGA(bImage,filename,True)
        else:
            if os.path.exists(filename):
                os.unlink(filename)
            saveName =  bImage.filepath
            bImage.filepath = filename
            bImage.save()
            bImage.filepath = saveName

    #---------------------------------------------------------------------------
    #                      _ c o p y E x t e r n a l I m a g e
    #---------------------------------------------------------------------------
    def _copyExternalImage(self, bImage):
        if bImage in self.copiedImages:
            return

        self.copiedImages.append(bImage)

        filename = self.getImageFileName('',bImage,1)
        if filename == None:
            return

        ofilename = bImage.filepath

        self.gGUI.updateStatus('Copying external image ' + ofilename + '...')
        try:
            shutil.copy2(ofilename, filename)
        except:
            self.gGUI.updateStatus('Error copying external image ' + ofilename + '...')


    #---------------------------------------------------------------------------
    #                            _ s a v e I m a g e
    #---------------------------------------------------------------------------
    def _saveImage(self, bImage):
        if bImage.packed_file != None:
            self._savePackedTexture(bImage)
        elif self.gCopyImages:
            self._copyExternalImage(bImage)

#-----------------------------------------------------------------------------
#                          c h e c k D i r e c t o r y
#-----------------------------------------------------------------------------
def checkDirectory(dirVal):
    tempDir = filterDirPath(dirVal)
    if not os.path.isdir(tempDir):
        os.makedirs(tempDir)
    return tempDir

#-----------------------------------------------------------------------------
#                          s e t D i r e c t o r y
#-----------------------------------------------------------------------------
def setDirectory(base, option):
    result = defScriptOptions[option]
    if (result[0] == '/') or (result.find(':') >= 0): # absolute?
        result = filterDirPath(result)
    else:
        result = os.path.abspath(base + result)
    checkDirectory(result)
    return result

#-----------------------------------------------------------------------------
#                                   w r i t e
#-----------------------------------------------------------------------------
def write(filename, operator, context, OutDirectory, CreateSceneFile, SelectedOnly,
    ExportLights, ExportCameras, ExportAnimations, ExportPhysics, ExportBinary,
    UseBlenderMaterials, Debug, runWalkTest, IrrlichtVersion):
        
    global gOutDirectory

    gOutDirectory = OutDirectory

    _saveConfig()

    scene = context.scene
    if not filename.lower().endswith('.irr'):
        filename += '.irr'
	
    OutDirectory = filterDirPath(OutDirectory)
    checkDirectory(OutDirectory)

    # setup and check scene directory
    SceneDirectory = setDirectory(OutDirectory, 'sceneOutDir')
    MeshDirectory = setDirectory(OutDirectory, 'meshOutDir')
    ImageDirectory = setDirectory(OutDirectory, 'texOutDir')

    operator.report({'INFO'}, 'irrb Export')
    exporter = iExporter(context, operator, getGUIInterface('filepanel'),
                CreateSceneFile, OutDirectory,
                SceneDirectory, MeshDirectory, ImageDirectory, SelectedOnly,
                ExportLights, ExportCameras, ExportAnimations, ExportPhysics,
                ExportBinary, UseBlenderMaterials, Debug, runWalkTest,
                gVersionList[IrrlichtVersion],
                gMeshCvtPath, gWalkTestPath)

    exporter.doExport()
    operator.report({'INFO'}, 'irrb Export Done.')

#-----------------------------------------------------------------------------
#                           I r r b E x p o r t O p
#-----------------------------------------------------------------------------
class IrrbExportOp(bpy.types.Operator):
    global gMeshCvtPath, gWalkTestPath

    '''Export scene and object info to the native Irrlicht scene (.irr) and mesh (.irrmesh) formats'''
    bl_idname = "export.irrb"
    bl_label = "Export .irr/.irrmesh"
	
    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    filepath = StringProperty(name="File Path",
        description="File path used for exporting the .irr file",
        maxlen= 1024, default= "")

    exportScene = BoolProperty(name="Export Scene",
        description="Export Scene", default=True)

    exportLights = BoolProperty(name="Export Light(s)",
        description="Export Lights", default=True)

    exportCameras = BoolProperty(name="Export Camera(s)",
        description="Export Cameras", default=True)

    exportAnimations = BoolProperty(name="Export Animation(s)",
        description="Export Animations", default=True)

    exportPhysics = BoolProperty(name="Export Collision/Physics Data",
        description="Export Collision/Physics Data", default=False)

    exportBinary = BoolProperty(name="Export Binary",
        description="Convert Meshes To Binary (.irrbmesh)", default=False)

    useBlenderMaterials = BoolProperty(name="Use Blender Materials",
        description="Use Blender Materials", default=False)

    exportSelected = BoolProperty(name="Selected Object(s) Only",
        description="Export Selected Object(s) Only", default=False)

    debug = BoolProperty(name="Generate Debug Data",
        description="Generate Debug Data in irrb.log", default=True)

    # update meshcvt & walktest paths
    gMeshCvtPath = None
    if 'IMESHCVT' in os.environ:
        gMeshCvtPath = os.environ['IMESHCVT']
        exportBinary = BoolProperty(name="Generate Binary Mesh Data",
            description="Generate Binary Mesh Data (.irrbmesh)", default=False)

    gWalkTestPath = None
    if 'IWALKTEST' in os.environ:
        gWalkTestPath = os.environ['IWALKTEST']
        walktest = BoolProperty(name="Walk Test After Export",
            description="Walk Test", default=True)

    #---------------------------------------------------------------------------
    #                                p o l l
    #---------------------------------------------------------------------------
    @classmethod
    def poll(cls, context):
        return {'PASS_THROUGH'}
	
    #---------------------------------------------------------------------------
    #                              e x e c u t e
    #---------------------------------------------------------------------------
    def execute(self, context):
        global gPropExportScene, gPropExportSelected, gPropUseBlenderMaterials
        global gPropExportLights, gPropExportCameras, gPropExportPhysics
        global gPropExportBinary, gPropDebug, gPropWalktest, gPropExportAnimations

        if not self.properties.filepath:
            raise Exception("filename not set")

        try:
            print('filename: ' + self.filename)
            print('directory: ' + self.directory)
        except:
            pass

        # save UI properties
        gPropExportScene = self.properties.exportScene
        gPropExportSelected = self.properties.exportSelected
        gPropExportLights = self.properties.exportLights
        gPropExportCameras = self.properties.exportCameras
        gPropExportAnimations = self.properties.exportAnimations
        gPropExportPhysics = self.properties.exportPhysics
        gPropUseBlenderMaterials = self.properties.useBlenderMaterials
        gPropDebug = self.properties.debug
        if 'IMESHCVT' in os.environ:
            gPropExportBinary = self.properties.exportBinary
        if 'IWALKTEST' in os.environ:
            gPropWalktest = self.properties.walktest 

        OutDirectory = os.path.dirname(self.properties.filepath)

        runWalkTest = False
        if gWalkTestPath != None:
            runWalkTest = self.properties.walktest

        self.report('INFO', 'irrb Exporter Start.')
        write(self.properties.filepath, self, context,
              OutDirectory,
              self.properties.exportScene,
              self.properties.exportSelected,
              self.properties.exportLights,
              self.properties.exportCameras,
              self.properties.exportAnimations,
              self.properties.exportPhysics,
              self.properties.exportBinary,
              self.properties.useBlenderMaterials,
              self.properties.debug,
              runWalkTest,
              1 # irrlicht version index
             )

        return {'FINISHED'}
	
    def invoke(self, context, event):

        self.properties.filepath = gOutDirectory + os.sep + '{0}.irr'.format(context.scene.name)
        self.properties.exportScene = gPropExportScene

        self.properties.exportSelected = gPropExportSelected
        self.properties.exportLights = gPropExportLights
        self.properties.exportCameras = gPropExportCameras
        self.properties.exportPhysics = gPropExportPhysics
        self.properties.exportAnimations = gPropExportAnimations
        self.properties.useBlenderMaterials = gPropUseBlenderMaterials
        self.properties.debug = gPropDebug
        if 'IMESHCVT' in os.environ:
            self.properties.exportBinary = gPropExportBinary
        if 'IWALKTEST' in os.environ:
            self.properties.walktest = gPropWalktest

        wm = context.manager
        wm.add_fileselect(self)
        return {'RUNNING_MODAL'}

#-----------------------------------------------------------------------------
#                       I r r b W a l k t e s t O p
#-----------------------------------------------------------------------------
class IrrbWalktestOp(bpy.types.Operator):
    ''''''
    bl_idname = "scene.irrb_walktest"
    bl_label = "irrb Walktest"

    @classmethod
    def poll(cls, context):
        return {'PASS_THROUGH'}

    def execute(self, context):

        if len(gWTCmdLine) > 0:
            subprocess.Popen(gWTCmdLine, shell=True, cwd=gWTDirectory)

        return {'RUNNING_MODAL'}

#-----------------------------------------------------------------------------
#                      I r r b S c e n e P r o p s
#-----------------------------------------------------------------------------
class IrrbSceneProps(bpy.types.Panel):
    bl_label = 'irrb'
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = 'scene'

    def draw(self, context):
        layout = self.layout

        rd = context.scene.render
        row = layout.row()
        layout.operator("export.irrb", icon='RENDER_STILL')
        if len(gWTCmdLine) > 0:
            row = layout.row()
            layout.operator("scene.irrb_walktest", icon='RENDER_STILL')

#-----------------------------------------------------------------------------
#                     I r r b M a t e r i a l P r o p s
#-----------------------------------------------------------------------------
class IrrbMaterialProps(bpy.types.Panel):
    bl_label = 'irrb'
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = 'material'

    def draw(self, context):
        layout = self.layout

        obj = context.object

        row = layout.row()
        row.label(text='Type')
        row.prop(obj.active_material, 'irrb.MaterialType', '')

        mtype = EMT_SOLID
        if 'irrb.MaterialType' in obj.active_material:
            mtype = obj.active_material['irrb.MaterialType']

        if mtype == EMT_CUSTOM:
            row = layout.row()
            row.label(text='Custom Name')
            row.prop(obj.active_material, 'irrb.CustomName', '')

        row = layout.row()
        row.label(text='Ambient')
        row.prop(obj.active_material, 'irrb.Ambient', '')
        row.label(text='Diffuse')
        row.prop(obj.active_material, 'irrb.Diffuse', '')
        row = layout.row()
        row.label(text='Emissive')
        row.prop(obj.active_material, 'irrb.Emissive', '')
        row.label(text='Specular')
        row.prop(obj.active_material, 'irrb.Specular', '')

        row = layout.row()
        row.prop(obj.active_material, 'irrb.Lighting')
        row.prop(obj.active_material, 'irrb.Gouraud')

        row = layout.row()
        row.prop(obj.active_material, 'irrb.BackCull')
        row.prop(obj.active_material, 'irrb.FrontCull')

        row = layout.row()
        row.prop(obj.active_material, 'irrb.ZWrite')
        row.prop(obj.active_material, 'irrb.Fog')

        row = layout.row()
        row.prop(obj.active_material, 'irrb.Param1')
        row.prop(obj.active_material, 'irrb.Param2')

#-----------------------------------------------------------------------------
#                       I r r b O b j e c t P r o p s
#-----------------------------------------------------------------------------
class IrrbObjectProps(bpy.types.Panel):
    bl_label = 'irrb'
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = 'object'

    def draw(self, context):
        layout = self.layout

        obj = context.object

        #row = layout.row()
        #row.label(text="Active object is: " + obj.name, icon='OBJECT_DATA')
        row = layout.row()
        row.label(text='ID')
        row.prop(obj, "irrb.ID")

        if obj.type in ('MESH', 'EMPTY'):
            row = layout.row()
            row.label(text='Type')
            row.prop(obj, "irrb.NodeType", '')
            row = layout.row()
            row.label(text='Automatic Culling')
            row.prop(obj, 'irrb.NodeCulling', '')

#-----------------------------------------------------------------------------
#                            m e n u _ e x p o r t
#-----------------------------------------------------------------------------
# this is invoked everytime the "Export | Irrlicht" menu item is selected.
def menu_export(self, context):
    default_path = bpy.data.filepath.replace('.blend', '.irr')
    self.layout.operator(IrrbExportOp.bl_idname, text='Irrlicht (.irr/.irrmesh)').filepath = default_path

#-----------------------------------------------------------------------------
#                _ r e g i s t e r I r r b P r o p e r t i e s
#-----------------------------------------------------------------------------
def _registerIrrbProperties():
    emptySet = set([])
    bpy.types.Object.IntProperty(attr='irrb.ID',options=emptySet,default=-1)

    bpy.types.Object.EnumProperty(attr='irrb.NodeType',
        items=(('DEFAULT','Default', 'default type'),
        ('BILLBOARD','Billboard', 'billboard type'),
        ('SKYBOX','Skybox','skybox type')),
        default='DEFAULT',
        name='Scene Node Type',
        description='Irrlicht Scene Node Type',
        options=emptySet)

    bpy.types.Object.EnumProperty(attr='irrb.NodeCulling',
        items=(('CULL_OFF','Off', ''),
        ('CULL_BOX','Box', ''),
        ('CULL_FRUSTUM_BOX','Frustum Box',''),
        ('CULL_FRUSTUM_SPHERE','Frustum Sphere','')
        ),
        default='CULL_FRUSTUM_BOX',
        name='Automatic Culling',
        description='Irrlicht Scene Node Culling',
        options=emptySet)

    bpy.types.Material.EnumProperty(attr='irrb.MaterialType',
        items=(('EMT_SOLID', 'Solid', 'standard type'),
        ('EMT_SOLID_2_LAYER','Solid 2 Layer', ''),
        ('EMT_LIGHTMAP', 'LightMap', ''),
        ('EMT_LIGHTMAP_ADD', 'LightMap Add', ''),
        ('EMT_LIGHTMAP_M2', 'LightMap M2', ''),
        ('EMT_LIGHTMAP_M4', 'LightMap M4', ''),
        ('EMT_LIGHTMAP_LIGHTING', 'LightMap Lighting', ''),
        ('EMT_LIGHTMAP_LIGHTING_M2', 'LightMap Lighting M2', ''),
        ('EMT_LIGHTMAP_LIGHTING_M4', 'LightMap Lighting M4', ''),
        ('EMT_DETAIL_MAP', 'Detail Map', ''),
        ('EMT_SPHERE_MAP', 'Sphere Map', ''),
        ('EMT_REFLECTION_2_LAYER', 'Reflection Map', ''),
        ('EMT_TRANSPARENT_ADD_COLOR', 'Transparent Add Color', ''),
        ('EMT_TRANSPARENT_ALPHA_CHANNEL', 'Transparent Alpha Channel', ''),
        ('EMT_TRANSPARENT_ALPHA_CHANNEL_REF', 'Transparent Alpha Channel Ref', ''),
        ('EMT_TRANSPARENT_VERTEX_ALPHA', 'Transparent Alpha Vertex', ''),
        ('EMT_TRANSPARENT_REFLECTION_2_LAYER', 'Transparent Alpha Reflection', ''),
        ('EMT_NORMAL_MAP_SOLID', 'Normal Map Solid', ''),
        ('EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR', 'Normal Map Transparent Color', ''),
        ('EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA', 'Normal Map Transparent Vertex', ''),
        ('EMT_PARALLAX_MAP_SOLID', 'Parallax Map Solid', ''),
        ('EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR', 'Parallax Map Transparent Color', ''),
        ('EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA', 'Parallax Map Transparent Vertex', ''),
        ('EMT_ONETEXTURE_BLEND', 'One Texture Blend', ''),
        ('EMT_CUSTOM', 'Custom Material', '')
        ),
        default='EMT_SOLID',
        name='Material Type',
        description='Irrlicht Material Type',
        options=emptySet)


    bpy.types.Material.StringProperty(attr='irrb.CustomName',
        name='CustomName', description='Custom Material Name',
        default='?', maxlen=64,  options=emptySet, subtype='NONE')

    bpy.types.Material.FloatVectorProperty(attr='irrb.Ambient',
        name="Ambient", description="Ambient Color",
        default=(1.0, 1.0, 1.0),
        min=0.0, max=1.0,
        soft_min=0.0, soft_max=1.0,
        step=0.01, precision=2,
        options=emptySet, subtype='COLOR', size=3)

    bpy.types.Material.FloatVectorProperty(attr='irrb.Diffuse',
        name="Diffuse", description="Diffuse Color",
        default=(1.0, 1.0, 1.0),
        min=0.0, max=1.0,
        soft_min=0.0, soft_max=1.0,
        step=0.01, precision=2,
        options=emptySet, subtype='COLOR', size=3)

    bpy.types.Material.FloatVectorProperty(attr='irrb.Emissive',
        name="Emissive", description="Emissive Color",
        default=(0.0, 0.0, 0.0),
        min=0.0, max=1.0,
        soft_min=0.0, soft_max=1.0,
        step=0.01, precision=2,
        options=emptySet, subtype='COLOR', size=3)

    bpy.types.Material.FloatVectorProperty(attr='irrb.Specular',
        name="Specular", description="Specular Color",
        default=(1.0, 1.0, 1.0),
        min=0.0, max=1.0,
        soft_min=0.0, soft_max=1.0,
        step=0.01, precision=2,
        options=emptySet, subtype='COLOR', size=3)

    bpy.types.Material.BoolProperty(attr='irrb.Lighting',
        name='Lighting', description='Enable Lighting', default=True,
        options=emptySet, subtype='NONE')

    bpy.types.Material.BoolProperty(attr='irrb.Gouraud',
        name='Gouraud', description='Enable Gouraud Shading', default=True,
        options=emptySet, subtype='NONE')

    bpy.types.Material.BoolProperty(attr='irrb.BackCull',
        name='Backface Culling', description='Enable Backface Culling', default=True,
        options=emptySet, subtype='NONE')

    bpy.types.Material.BoolProperty(attr='irrb.FrontCull',
        name='Frontface Culling', description='Enable Frontface Culling', default=False,
        options=emptySet, subtype='NONE')

    bpy.types.Material.BoolProperty(attr='irrb.ZWrite',
        name='ZWrite', description='Enable ZBuffer Writing', default=True,
        options=emptySet, subtype='NONE')

    bpy.types.Material.BoolProperty(attr='irrb.Fog',
        name='Fog', description='Enable Fog', default=True,
        options=emptySet, subtype='NONE')

    bpy.types.Material.FloatProperty(attr='irrb.Param1',
        name='Param1', description='Type Param1', default=0.0,
        min=sys.float_info.min, max=sys.float_info.max,
        soft_min=sys.float_info.min, soft_max=sys.float_info.max,
        step=3, precision=2,
        options=emptySet, subtype='NONE')

    bpy.types.Material.FloatProperty(attr='irrb.Param2',
        name='Param2', description='Type Param2', default=0.0,
        min=sys.float_info.min, max=sys.float_info.max,
        soft_min=sys.float_info.min, soft_max=sys.float_info.max,
        step=3, precision=2,
        options=emptySet, subtype='NONE')

#-----------------------------------------------------------------------------
#                              r e g i s t e r
#-----------------------------------------------------------------------------
def register():
    _loadConfig()
    _registerIrrbProperties()

    bpy.types.INFO_MT_file_export.append(menu_export)

#-----------------------------------------------------------------------------
#                            u n r e g i s t e r
#-----------------------------------------------------------------------------
def unregister():

    bpy.types.INFO_MT_file_export.remove(menu_export)
