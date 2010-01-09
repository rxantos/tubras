#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
# Notes:
#
# Coordinate Systems
#
# Irrlicht uses a left-handed coordinate system (y-up):
#
#           +Y  +Z          Positive rotation is clockwise around the
#            |  /           axis of rotation.
#            | /
#            |/             Euler rotation order -> x, y, z.
#  -X--------0--------+X
#           /|
#          / |
#         /  |
#       -Z  -Y
#
#
# Blender uses a right-handed coordinate system (z-up):
#
#           +Z  +Y          Positive rotation is counter-clockwise
#            |  /           around the axis of rotation.
#            | /
#            |/
#  -X--------0---------+X
#           /|
#          / |
#         /  |
#       -Y  -Z
#
import irrbmodules.iUtils

#-----------------------------------------------------------------------------
#                                 d e b u g
#-----------------------------------------------------------------------------
def debug(msg):
    iUtils.debug(msg)

def addWarning(msg):
    iUtils.addWarning(msg)

#-----------------------------------------------------------------------------
#                               E x p o r t e r
#-----------------------------------------------------------------------------
class Exporter:

    #-----------------------------------------------------------------------------
    #                               _ i n i t _
    #-----------------------------------------------------------------------------
    def __init__(self,CreateScene, BaseDir, SceneDir, MeshDir, TexDir, TexExtension,
            SelectedMeshesOnly, ExportLights, ExportCameras, ExportPhysics,
            Binary, Debug, IrrlichtVersion):
        pass

