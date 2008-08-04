#-----------------------------------------------------------------------------
# Blender to Irrlicht Exporter
# url: http://www.tubras.com
#
# Copyright (C) 2008 Keith Murray -- <pc0de@tubras.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# this export script is assumed to be used with the latest blender version.
#-----------------------------------------------------------------------------
import Blender, iGUI
import iMaterials, iMeshBuffer, iUtils, time

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
        

