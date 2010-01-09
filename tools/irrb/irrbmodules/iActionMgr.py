#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------

class Action:
    def __init__(self):
        pass

class ShapeAction:
    def __init__(self, mesh):
        self.mesh = mesh

class ArmatureAction:
    def __init__(self, mesh, armature):
        self.mesh = mesh
        self.armature = armature

class ActionMgr:
    def __init__(self):

        self.shapeActions = {}
        self.armatureActions = {}
        

