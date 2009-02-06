#------------------------------------------------------------------------------------
# E_COLOR_PLANE - 'ColorMask' enums
#------------------------------------------------------------------------------------
# No color enabled
ECP_NONE=0
# Alpha enabled
ECP_ALPHA=1
# Red enabled
ECP_RED=2
# Green enabled
ECP_GREEN=4
# Blue enabled
ECP_BLUE=8
# All colors, no alpha
ECP_RGB=14
# All planes enabled
ECP_ALL=15

#------------------------------------------------------------------------------------
# E_ANTI_ALIASING_MODE - 'AnitAliasing' enums
#------------------------------------------------------------------------------------
# Use to turn off anti-aliasing for this material
EAAM_OFF=0
# Default anti-aliasing mode
EAAM_SIMPLE=1
# High-quality anti-aliasing, not always supported, automatically enables SIMPLE mode
EAAM_QUALITY=3
# Line smoothing
EAAM_LINE_SMOOTH=4
# point smoothing, often in software and slow, only with OpenGL
EAAM_POINT_SMOOTH=8
# All typical anti-alias and smooth modes
EAAM_FULL_BASIC=15
# Enhanced anti-aliasing for transparent materials
# Usually used with EMT_TRANSPARENT_ALPHA_REF and multisampling. 
EAAM_ALPHA_TO_COVERAGE=16


StandardAttributes = {'Id':-1, 
                      'AutomaticCulling':1,
                      'Visible':1,
                      'DebugDataVisible':0,
                      'IsDebugObject':0,
                      'ReadOnlyMaterials':0}

CameraAttributes = {'Fovy' : 0.857556,
                    'Aspect' : 1.25,
                    'ZNear' : 0.1,
                    'ZFar' : 100.0}

BillboardAttributes = {'Shade_Top': '255 255 255 255',
                       'Shade_Down': '255 255 255 255'}

MaterialAttributes = {'Type':'solid',                       
                      'AmbientColor':'255 255 255 255',     # rgba
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
                      'FogEnable':0,
                      'NormalizeNormals':0,
                      'ZBuffer':1,
                      'AntiAliasing':EAAM_SIMPLE | EAAM_LINE_SMOOTH,
                      'ColorMask':ECP_ALL,
                      'Layer1': {'Texture':'',
                          'TextureWrap':'texture_clamp_repeat',
                          'BilinearFilter':1,
                          'TrilinearFilter':0,
                          'AnisotropicFilter':0,
                          'LODBias':0},
                      'Layer2': {'Texture':'',
                          'TextureWrap':'texture_clamp_repeat',
                          'BilinearFilter':1,
                          'TrilinearFilter':0,
                          'AnisotropicFilter':0,
                          'LODBias':0},
                      'Layer3': {'Texture':'',
                          'TextureWrap':'texture_clamp_repeat',
                          'BilinearFilter':1,
                          'TrilinearFilter':0,
                          'AnisotropicFilter':0,
                          'LODBias':0},
                      'Layer4': {'Texture':'',
                          'TextureWrap':'texture_clamp_repeat',
                          'BilinearFilter':1,
                          'TrilinearFilter':0,
                          'AnisotropicFilter':0,
                          'LODBias':0}}
