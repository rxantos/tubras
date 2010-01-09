#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2010 Keith Murray -- <pc0der at gmail dot com>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
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
        

